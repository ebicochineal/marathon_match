// package com.topcoder.ReviewTest;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.security.SecureRandom;
import java.util.*;
import java.util.List;


class TestCase {
    final Object worldLock = new Object();
    
    //test parameters
    public static final int minN = 5, maxN = 50;
    public static final double maxWallP = 0.5;    
    
    //constants
    public final static int[] dr={ 0,1,0,-1};
    public final static int[] dc={-1,0,1, 0};
    public final static char EMPTY='.';
    public final static char WALL='#';
    public final static char TARGET='X';
    public final static char PEG='P';

    //inputs
    public int N;    
    public int NumPegs;    
    public char[][] Grid;
    public char[][] GridCur;
    
    //outputs
    public int Score;  
    public int numMoves;
    public int[] lastX;
    public int[] lastY;
    
    //other
    public boolean Debug=false;
    public SecureRandom rnd = null;    


    public TestCase(long seed, boolean debug)
    {
      try {
          rnd = SecureRandom.getInstance("SHA1PRNG");
      } catch (Exception e) {
          System.err.println("ERROR: unable to generate test case.");
          System.exit(1);
      }
      
      Debug=debug;

      rnd.setSeed(seed);    
      
      
      while(true)
      {
        //generate grid size
        N = rnd.nextInt(maxN - minN + 1) + minN;

        if (seed == 1) N = minN;
        if (seed == 2) N = maxN;
        
        NumPegs=rnd.nextInt(N*N/4 - N + 1) + N;
        
        int[] ind=new int[N*N];
        for (int i=0; i<ind.length; i++) ind[i]=i;
        shuffle(ind);
        
        double wallP=rnd.nextDouble()*maxWallP;

        //generate grid
        Grid=new char[N][N];
        for (int i=0; i<N*N; i++)
        {
          char c='.';
          if (i<NumPegs) c='P';
          else if (i<2*NumPegs) c='X';
          else if (rnd.nextDouble()<wallP) c='#';

          Grid[ind[i]/N][ind[i]%N]=c;
        }
        
        if (everythingReachable()) break;
      }
      
      //make a copy of the grid for making moves
      GridCur=new char[N][N];
      for (int i=0; i<N; i++) for (int k=0; k<N; k++) GridCur[i][k]=Grid[i][k];
      
      numMoves=0;
                  
      if (Debug) printTest(seed);        
    }
    
    //shuffle the array randomly
    public void shuffle(int[] a)
    {
      for (int i=0; i<a.length; i++)
      {
        int k=(int)(rnd.nextDouble()*(a.length-i)+i);
        int temp=a[i];  
        a[i]=a[k];
        a[k]=temp;  
      }   
    }    
    
    public void printTest(long seed)
    {
        System.out.println("seed = "+seed);
        System.out.println("N = "+N);
        System.out.println("NumPegs = "+NumPegs);
        System.out.println("Grid:");
        for (int i=0; i<N; i++)
        {
          for (int k=0; k<N; k++) System.out.print(Grid[i][k]);
          System.out.println();
        }
    }    

    public boolean doSlideMove(int x, int y, char chMove) throws Exception {
      synchronized (worldLock) {
        lastX = new int[2];
        lastY = new int[2];
        lastX[0] = x;
        lastY[0] = y;

        int dx = 0;
        int dy = 0;
        if (chMove=='L') dx = -1;
        else if (chMove=='R') dx = 1;
        else if (chMove=='U') dy = -1;
        else if (chMove=='D') dy = 1;
        if (dx==0 && dy==0) {
            System.err.println("ERROR: Invalid move character ["+chMove+"].");
            return false;
        }
        
        int nx = x+dx;
        int ny = y+dy;
        if (nx>=0 && nx<N && ny>=0 && ny<N)
        {
          //slide move
          if (GridCur[ny][nx]!=WALL && GridCur[ny][nx]!=PEG)
          {
            lastX[1] = nx;
            lastY[1] = ny;                    
            GridCur[ny][nx]=PEG;
            GridCur[y][x]=EMPTY;
          }
          //cannot jump
          else
          {
            System.err.println("ERROR: Cannot do jump move in a slide sequence");
            return false;     
          }
        }
        else
        {
          System.err.println("ERROR: Trying to move outside the Grid.");
          return false;
        }
        numMoves++;
      }
      return true;
    }
    
    public boolean doJumpMove(int x, int y, String mv) throws Exception {
      synchronized (worldLock) {
        lastX = new int[mv.length()+1];
        lastY = new int[mv.length()+1];
        lastX[0] = x;
        lastY[0] = y;
        for (int i=0; i<mv.length();i++)
        {
          int dx = 0;
          int dy = 0;
          char chMove = mv.charAt(i);
          if (chMove=='L') dx = -1;
          else if (chMove=='R') dx = 1;
          else if (chMove=='U') dy = -1;
          else if (chMove=='D') dy = 1;
          if (dx==0 && dy==0) {
              System.err.println("ERROR: Invalid move character ["+chMove+"].");
              return false;
          }
          
          int nx = x+dx;
          int ny = y+dy;
          if (inGrid(ny,nx))
          {
              //cannot slide
              if (GridCur[ny][nx]!=WALL && GridCur[ny][nx]!=PEG)
              {
                System.err.println("ERROR: Cannot do slide move in a jump sequence");
                return false;                  
              }
              //jump move
              else
              {
                int nx2 = nx+dx;
                int ny2 = ny+dy;
                if (inGrid(ny2,nx2))
                {
                    if (GridCur[ny2][nx2]==PEG) {
                        System.err.println("ERROR: Trying to jump onto another peg.");
                        return false;
                    }
                    if (GridCur[ny2][nx2]==WALL) {
                        System.err.println("ERROR: Trying to jump onto to a wall.");
                        return false;
                    }                          
                    GridCur[y][x] = EMPTY;
                    GridCur[ny2][nx2] = PEG;
                    x = nx2;
                    y = ny2;
                    lastX[i+1] = x;
                    lastY[i+1] = y;
                } else {
                    System.err.println("ERROR: Trying to jump outside the Grid.");
                    return false;
                }
              }
          } else {
              System.err.println("ERROR: Trying to move outside the Grid.");
              return false;
          }
        }
        numMoves++;
      }
      return true;
    }    
    
    
    //returns false if some of the cells are not reachable, meaning the puzzle is possibly not solvable
    //otherwise returns true, which means the puzzle is definitely solvable
    public boolean everythingReachable()
    {      
      //get starting non-wall location
      int startR=-1;
      int startC=-1;
loop:      
      for (int r=0; r<N; r++)
        for (int c=0; c<N; c++)
          if (Grid[r][c]!=WALL)
          {
            startR=r;
            startC=c;
            break loop;
          }
     
      List<Loc> Q=new ArrayList<Loc>();     
      Q.add(new Loc(startR,startC));
          
      boolean[][] seen=new boolean[N][N];
          
      while(Q.size()>0)
      {
        Loc L=Q.remove(0);    
        if (seen[L.r][L.c]) continue;
        
        seen[L.r][L.c]=true;
        
        for (int m=0; m<dr.length; m++)
        {
          int r2=L.r+dr[m];
          int c2=L.c+dc[m];
          if (inGrid(r2,c2) && Grid[r2][c2]!=WALL) Q.add(new Loc(r2,c2));
            
          int r3=L.r+2*dr[m];
          int c3=L.c+2*dc[m];          
          if (inGrid(r3,c3) && Grid[r3][c3]!=WALL) Q.add(new Loc(r3,c3));
        }
      }
      
      for (int r=0; r<N; r++)
        for (int c=0; c<N; c++)
          if (Grid[r][c]!=WALL && !seen[r][c])
          {
            if (Debug) System.err.println("Location ("+r+","+c+") is not reachable from ("+startR+","+startC+")");
            return false;
          }
            
      return true;
    }
    
    //count number of uncovered targets
    public int countUncovered()
    {
      int count=0;
      for (int r=0; r<N; r++)
        for (int c=0; c<N; c++)
          if (Grid[r][c]==TARGET && GridCur[r][c]!=PEG)
            count++;
            
      return count;
    }
    
    public int score()
    {
      return numMoves+2*countUncovered()*N;
    }
    
    public boolean inGrid(int r, int c)
    {
      return (r>=0 && r<N && c>=0 && c<N);
    }
    
    static class Loc
    {
      int r;
      int c;
      
      public Loc(int R, int C)
      {
        r=R;
        c=C;
      }
    }
}

class Drawer extends JFrame {
    public static final int EXTRA_WIDTH = 200;
    public static final int EXTRA_HEIGHT = 50;

    public TestCase tc;
    public DrawerPanel panel;

    public int cellSize;
    public int width, height;

    public boolean pauseMode = false;

    class DrawerKeyListener extends KeyAdapter {
        public void keyPressed(KeyEvent e) {
            synchronized (keyMutex) {
                if (e.getKeyChar() == ' ') pauseMode = !pauseMode;
                keyPressed = true;
                
                keyMutex.notifyAll();
            }
        }
    }

    class DrawerPanel extends JPanel {
        public void paint(Graphics g) {
            synchronized (tc.worldLock) {
              int startX=10;
              int startY=10;
              
              // background
              g.setColor(new Color(0xDDDDDD));
              g.fillRect(0,0,tc.N*cellSize+230,tc.N*cellSize+40);
              g.setColor(Color.WHITE);
              g.fillRect(startX,startY,tc.N*cellSize,tc.N*cellSize);
              
              //paint thin lines between cells
              g.setColor(Color.BLACK);
              for (int i = 0; i <= tc.N; i++)
                g.drawLine(startX,startY+i*cellSize,startX+tc.N*cellSize,startY+i*cellSize);
              for (int i = 0; i <= tc.N; i++)
                g.drawLine(startX+i*cellSize,startY,startX+i*cellSize,startY+tc.N*cellSize);   
                
                
              //draw grid contents
              for (int r = 0; r < tc.N; r++)
                for (int c = 0; c < tc.N; c++)              
                {
                  if (tc.Grid[r][c]==tc.WALL)
                  {
                    g.setColor(Color.GRAY);
                    g.fillRect(startX+c*cellSize+1,startY+r*cellSize+1,cellSize-1,cellSize-1);
                  }
                  if (tc.Grid[r][c]==tc.TARGET)
                  {
                    g.setColor(Color.GREEN);
                    g.fillRect(startX+c*cellSize+1,startY+r*cellSize+1,cellSize-1,cellSize-1);
                  }                  
                  if (tc.GridCur[r][c]==tc.PEG)
                  {
                    g.setColor(Color.BLUE);
                    g.fillOval(startX + c*cellSize + cellSize/4, startY + r*cellSize + cellSize/4, cellSize/2, cellSize/2);
                  }      
                }
                                 
                    
              if (tc.lastX!=null && tc.lastX.length>0)
              {
                for (int i=0;i<tc.lastX.length-1;i++)
                {
                  g.setColor(Color.RED);
                  g.drawLine(startX + tc.lastX[i] * cellSize + cellSize/2, startY + tc.lastY[i] * cellSize + cellSize/2,
                          startX + tc.lastX[i+1] * cellSize + cellSize/2, startY + tc.lastY[i+1] * cellSize + cellSize/2);
                }
              }                        
                  
              //display score and info
              g.setColor(Color.BLACK);                    
              g.setFont(new Font("Arial",Font.BOLD,14));
              g.drawString("Pegs "+tc.NumPegs,cellSize*tc.N+25,30);   
              g.drawString("Uncovered "+tc.countUncovered(),cellSize*tc.N+25,50);   
              g.drawString("Moves "+tc.numMoves,cellSize*tc.N+25,70);   
              g.drawString("SCORE "+tc.score(),cellSize*tc.N+25,120);   
            }
        }
    }

    class DrawerWindowListener extends WindowAdapter {
        public void windowClosing(WindowEvent event) {
            JumpAroundVis.stopSolution();
            System.exit(0);
        }
    }

    final Object keyMutex = new Object();
    boolean keyPressed;

    public void processPause() {
        synchronized (keyMutex) {
            if (!pauseMode) {
                return;
            }
            keyPressed = false;
            while (!keyPressed) {
                try {
                    keyMutex.wait();
                } catch (InterruptedException e) {
                    // do nothing
                }
            }
        }
    }

    public Drawer(TestCase tc_, int cellSize) {
        super();

        panel = new DrawerPanel();
        getContentPane().add(panel);

        addWindowListener(new DrawerWindowListener());

        this.tc = tc_;
        this.cellSize = cellSize;
        
        width = cellSize * tc.N + EXTRA_WIDTH;
        height = cellSize * tc.N + EXTRA_HEIGHT;

        addKeyListener(new DrawerKeyListener());

        setSize(width, height);
        setTitle("Visualizer tool for problem JumpAround");

        setResizable(false);
        setVisible(true);
    }
}


public class JumpAroundVis {
    public static String execCommand = null;
    public static long seed = 1;
    public static boolean vis = true;
    public static int cellSize = 20;
    public static int delay = 100;
    public static boolean startPaused = false;
    public static boolean debug = false;

    public static Process solution;

    public double runTest() {
        solution = null;

        try {
            solution = Runtime.getRuntime().exec(execCommand);
        } catch (Exception e) {
            System.err.println("ERROR: Unable to execute your solution using the provided command: "
                    + execCommand + ".");
            return -1;
        }

        BufferedReader reader = new BufferedReader(new InputStreamReader(solution.getInputStream()));
        PrintWriter writer = new PrintWriter(solution.getOutputStream());
        output = new ErrorReader(solution.getErrorStream());
        output.start();

        TestCase tc = new TestCase(seed,debug);
       
        writer.println(tc.N);
        writer.println(tc.NumPegs);
        for (int i=0; i<tc.N; i++)
          for (int k=0; k<tc.N; k++)
            writer.println(tc.Grid[i][k]);
        writer.flush();    
        
                
        Drawer drawer = null;
        if (vis) {
            drawer = new Drawer(tc, cellSize);
            if (startPaused) drawer.pauseMode = true;
        }       
        
        int numMoves;
        String[] allMoves;
        
        long startTime = System.currentTimeMillis();
        
        try {
            numMoves = Integer.parseInt(reader.readLine());
        } catch (Exception e) {
            System.err.println("Invalid number of moves detected");
            return this.score = -1;
        }

        runTime += System.currentTimeMillis() - startTime;
        startTime = System.currentTimeMillis();

        allMoves = new String[numMoves];
        try {
          for (int i = 0; i < numMoves; i++)
            allMoves[i] = reader.readLine();
        } catch (Exception e) {
            System.err.println("Unable to read output.");
            return this.score = -1;
        }
        
        long readTime = System.currentTimeMillis() - startTime;
        if (readTime > 1000) runTime += readTime - 1000;
        
        if (runTime > 100000000) {
            System.err.println("Time limit exceeded.");
            return this.score = -1;
        }
        
        try {
            if (numMoves > tc.N*tc.NumPegs) {
                System.err.println("ERROR: Return array is too large.");
                return this.score = -1;
            }
            for (int i=0; i<numMoves; i++) {
                String smove = allMoves[i];
                if (debug) System.err.println("executing "+smove);
                String[] s = smove.split(" ");
                if (s.length!=4) {
                    System.err.println("ERROR: The move command with index "+i+" does not contain 4 space seperated values. Value is ["+smove+"]");
                    return this.score = -1;
                }
                int y = -1;
                int x = -1;
                try
                {
                  y = Integer.parseInt(s[0]);
                  x = Integer.parseInt(s[1]);
                } catch (Exception e) {
                  System.err.println("ERROR: invalid coordinates "+s[0]+" "+s[1]);
                  return this.score = -1;
                }
                if (x<0 || x>=tc.N || y<0 || y>=tc.N) {
                    System.err.println("ERROR: (" + y + "," + x + ") outside of bounds.");
                    return this.score = -1;
                }
                if (tc.GridCur[y][x]!=tc.PEG) {
                    System.err.println("ERROR: (" + y + "," + x + ") does not contain a peg.");
                    return this.score = -1;
                }
                // try to perform moves
                if (s[2].equals("S"))
                {
                  if (s[3].length()>1)
                  {
                    System.err.println("ERROR: slide move has too many instructions: "+s[3]);
                    return this.score = -1;                  
                  }
                  if (!tc.doSlideMove(x, y, s[3].charAt(0))) return -1;
                }
                else if (s[2].equals("J"))
                {
                  if (!tc.doJumpMove(x, y, s[3])) return -1;
                }
                else
                {
                  System.err.println("ERROR: unrecognised move type: "+s[2]);
                  return this.score = -1;                                    
                }
                
                if (vis) {
                    drawer.processPause();
                    drawer.repaint();
                    try {
                        Thread.sleep(delay);
                    } catch (Exception e) {
                        // do nothing
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("ERROR: Unable to process the move commands from your solution.");
            return this.score = -1;
        }

        stopSolution();
        
        return this.score = tc.score();
    }

    public static void stopSolution() {
        if (solution != null) {
            try {
                solution.destroy();
            } catch (Exception e) {
                // do nothing
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++)
            if (args[i].equals("-exec")) {
                execCommand = args[++i];
            } else if (args[i].equals("-seed")) {
                seed = Long.parseLong(args[++i]);
            } else if (args[i].equals("-novis")) {
                vis = false;
            } else if (args[i].equals("-debug")) {
                debug = true;                
            } else if (args[i].equals("-sz")) {
                cellSize = Integer.parseInt(args[++i]);
            } else if (args[i].equals("-delay")) {
                delay = Integer.parseInt(args[++i]);
            } else if (args[i].equals("-pause")) {
                startPaused = true;
            } else {
                System.out.println("WARNING: unknown argument " + args[i] + ".");
            }
            
        if (seed==1) cellSize = 50;

        if (execCommand == null) {
            System.err.println("ERROR: You did not provide the command to execute your solution." +
                    " Please use -exec <command> for this.");
            System.exit(1);
        }

        double score = -1.0;

        JumpAroundVis vis = new JumpAroundVis();
        try {
            score = vis.runTest();
            System.out.println("Score = " + score);
        } catch (RuntimeException e) {
            System.err.println("ERROR: Unexpected error while running your test case.");
            e.printStackTrace();
            JumpAroundVis.stopSolution();
        }
        // return score;
    }
    
    public static long runTime = 0;
    public double score = -1.0;
    public static ErrorReader output;    
}

class ErrorReader extends Thread{
    InputStream error;
    StringBuilder sb = new StringBuilder();
    public ErrorReader(InputStream is) {
        error = is;
    }
    public void run() {
        try {
            byte[] ch = new byte[50000];
            int read;
            while ((read = error.read(ch)) > 0)
            {   String s = new String(ch,0,read);
                System.out.print(s);
                sb.append(s);
                System.out.flush();
            }
        } catch(Exception e) { }
    }
}
