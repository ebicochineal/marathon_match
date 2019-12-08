import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.security.*;
import java.util.*;
import java.net.URL;
import javax.swing.*;
import javax.imageio.*;


public class GlowingBacteriaVis {

    //test parameters
    private static int minN = 8, maxN = 50;
    private static int minC = 2, maxC = 8;
    private static int minSteps = 1, maxSteps = 5;
    private static int minDist = 1, maxDist = 10;
    
    //inputs
    int N;      //grid size
    int C;      //number of colours
    int D;      //number of days
    int K;      //distance
    
    //grids
    int[][][] Grids;        //ground truth grids. Grids[0] is the starting grid, while Grids[D] is the input grid given to competitors
    int[][] PredictedGrid;     //grid predicted by competitors
    
    //outputs
    int Score;  
    
    // -----------------------------------------
    void generate(String seedStr) {
      try {
        // generate test case
        SecureRandom r1 = SecureRandom.getInstance("SHA1PRNG"); 
        long seed = Long.parseLong(seedStr);
        r1.setSeed(seed);
        
        //generate grid size
        N = r1.nextInt(maxN - minN + 1) + minN;
        
        //generate number of colours
        C = r1.nextInt(maxC - minC + 1) + minC;            
        
        //generate number of steps
        D = r1.nextInt(maxSteps - minSteps + 1) + minSteps;            
        
        //generate distance
        K = r1.nextInt(maxDist - minDist + 1) + minDist;
        if (seed > 0 && seed <= 100) {
          C = 2;
        }
        if (seed > 100 && seed <= 200) {
          C = 3;
        }
        if (seed > 200 && seed <= 300) {
          C = 4;
        }
        
        if (seed > 300 && seed <= 400) {
          C = 5;
        }
        if (seed > 400 && seed <= 500) {
          C = 6;
        }
        if (seed > 500 && seed <= 600) {
          C = 7;
        }
        
        if (seed > 600 && seed <= 700) {
          N = 8;
        }
        
        
        
        //set easiest/hardest seeds
        if (seed == 1)
        {
          N = minN;
          D = 1;
          K = 1;
        }
        if (seed == 2) N = maxN;                
        

        Grids=new int[D+1][N][N];
        
        //generate starting grid with random rectangles and random colours
        for (int i=0; i<N; i++) for (int k=0; k<N; k++) Grids[0][i][k]=-1;
        int left=N*N;
        while(left>0)
        {
          int r=r1.nextInt(N);
          int c=r1.nextInt(N);
          int width=r1.nextInt(N/4)+1;
          int height=r1.nextInt(N/4)+1;
          int col=r1.nextInt(C);
          for (int r2=r; r2<N && r2<r+height; r2++)
            for (int c2=c; c2<N && c2<c+width; c2++)
            {
              if (Grids[0][r2][c2]==-1) left--;
              Grids[0][r2][c2]=col;
            } 
        }
        
            
        int[] counts=new int[C];

        //simulate for some steps to get the input grid
        for (int step=0; step<D; step++)
        {
          for (int r=0; r<N; r++)
            for (int c=0; c<N; c++)
            {
              for (int i=0; i<C; i++) counts[i]=0;    //reset counts
              
              for (int r2=0; r2<N; r2++)
                for (int c2=0; c2<N; c2++)
                {
                  int dr=Math.abs(r2-r);
                  int dc=Math.abs(c2-c);
                  int dist=dr*dr+dc*dc;
                  if (dist>0 && dist<=K) counts[Grids[step][r2][c2]]++;
                }


              int min=Integer.MAX_VALUE;
              java.util.List<Integer> vals=new ArrayList<Integer>();
              
              for (int i=0; i<C; i++)
                if (counts[i]<=min && counts[i]>0)
                {
                  if (counts[i]<min) vals.clear();
                  vals.add(i);
                  min=counts[i];
                }                

              //if single frequency then use it's value
              if (vals.size()==1) Grids[step+1][r][c]=vals.get(0);
              //if multiple frequencies then keep the previous colour
              else Grids[step+1][r][c]=Grids[step][r][c];
            }
        }        
                   
        if (Debug) printTest(seedStr);        
      }
      catch (Exception e) {
        addFatalError("An exception occurred while generating test case.");
        e.printStackTrace(); 
      }
    }
    
    void printTest(String seed)
    {
        System.out.println("seed = "+seed);
        System.out.println("Grid size, N = "+N);
        System.out.println("Colours, C = "+C);
        System.out.println("Days, D = "+D);
        System.out.println("Distance, K = "+K);        
        System.out.println();
        System.out.println("Start Grid (not visible to competitors):");
        for (int i=0; i<N; i++)
        {
          for (int k=0; k<N; k++) System.out.print(Grids[0][i][k]);
          System.out.println();
        }
        System.out.println();
        System.out.println("Input Grid (given to competitors):");
        for (int i=0; i<N; i++)
        {
          for (int k=0; k<N; k++) System.out.print(Grids[D][i][k]);
          System.out.println();
        }        
    }
            
        
    // -----------------------------------------
    public double runTest(String seed) {
      try {
        generate(seed);
        
        char[] solution;

        if (proc != null) {
            // call the solution
            try { 
                solution = callSolution();
            } catch (Exception e) {
                addFatalError("Failed to get result from your solution.");
                return -1.0;
            }

            // check the return and score it
            if (solution == null) {
                addFatalError("Your return contained an invalid number of elements.");
                return -1.0;
            }
            if (solution.length != N*N) {
                addFatalError("Your return did not contain " + (N*N) + " elements.");
                return -1.0;
            }
            
            
            //construct output board and check for invalid characters
            PredictedGrid=new int[N][N];
            for (int i=0,cur=0; i<N; i++)
              for (int k=0; k<N; k++,cur++)
              {
                if (solution[cur]<'0' || solution[cur]>='0'+C)
                {
                  addFatalError("Illegal colour "+solution[cur]+" at cell ("+i+","+k+")");
                  return -1.0;
                }
                
                PredictedGrid[i][k]=(int)(solution[cur]-'0');
              }


            if (Debug)
            {
              System.err.println("\nPredicted Grid");
              for (int i=0; i<N; i++)
              {
                for (int k=0; k<N; k++) System.err.print(PredictedGrid[i][k]);
                System.err.println();
              }              
            }
              
              
            //compute the raw score. One point for each correct prediction                    
            Score=0;          
            for (int i=0; i<N; i++)
              for (int k=0; k<N; k++)
                if (PredictedGrid[i][k]==Grids[0][i][k])
                  Score++;
                                        
            
            if (vis) {
                //show seed in the title. Thank you wleite for the idea!
                jf.setTitle("Glowing Bacteria, seed = " + seed);
                jf.setSize(2*N*SZ+300,N*SZ+120);
                
                
                jf.setVisible(true);
                draw();
            }   
        }
       
        return Score;
      }
      catch (Exception e) { 
        addFatalError("An exception occurred while trying to get your program's results.");
        e.printStackTrace(); 
        return -1.0;
      }
    }
       
       
    
// ------------- visualization part ------------
    JFrame jf;
    Vis v;
    static String exec;
    static boolean vis;
    static Process proc;
    InputStream is;
    OutputStream os;
    BufferedReader br;
    static int SZ;
    static boolean Debug;
    static int CurGrid=0;     //current grid to display, can be controlled by the user

    
    // -----------------------------------------
    private char[] callSolution() throws IOException, NumberFormatException {
        if (exec == null) return null;

        String s=N+"\n"+C+"\n"+D+"\n"+K+"\n";
        os.write(s.getBytes());
        for (int i=0; i<N; i++)
          for (int k=0; k<N; k++)
          {
            s=Grids[D][i][k]+"\n";
            os.write(s.getBytes());
          }          
        os.flush();

        // and get the return value
        char[] grid=new char[Integer.parseInt(br.readLine())];
        for (int i = 0; i < grid.length; i++)
            grid[i] = br.readLine().charAt(0);
        return grid;
    }
    // -----------------------------------------
    void draw() {
        if (!vis) return;
        v.repaint();
    }
    // -----------------------------------------
    public class Vis extends JPanel implements MouseListener, KeyListener, WindowListener {
        public void paint(Graphics g) {
        
          //Use antialiasing when painting. Thank you wleite for the idea!
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
                 
          Color[] colors={Color.BLUE,Color.MAGENTA,Color.GRAY,Color.RED,Color.CYAN,Color.PINK,Color.BLACK,Color.ORANGE};
              
          int startX=20;
          int startY=60;
          int gapX=20;      //gap between boards
          
          int shift=N*SZ+gapX;
                    
          // gray background
          g.setColor(new Color(0xDDDDDD));
          g.fillRect(0,0,10000,10000);
          // white rectangles
          g.setColor(Color.WHITE);
          g.fillRect(startX,startY,N*SZ,N*SZ);
          g.fillRect(startX+N*SZ+gapX,startY,N*SZ,N*SZ);
          
          //paint grid lines
          g.setColor(Color.BLACK);
          //true grid
          for (int i = 0; i <= N; i++)
            g.drawLine(startX,startY+i*SZ,startX+N*SZ,startY+i*SZ);
          for (int i = 0; i <= N; i++)
            g.drawLine(startX+i*SZ,startY,startX+i*SZ,startY+N*SZ);          
          //predicted grid
          for (int i = 0; i <= N; i++)
            g.drawLine(startX+shift,startY+i*SZ,startX+shift+N*SZ,startY+i*SZ);
          for (int i = 0; i <= N; i++)
            g.drawLine(startX+shift+i*SZ,startY,startX+shift+i*SZ,startY+N*SZ);                    
                        

          //paint bacteria
          //true grid
          for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
            {
              g.setColor(colors[Grids[CurGrid][r][c]]);
              g.fillOval(startX + c*SZ + SZ/4 +1, startY + r*SZ + SZ/4 +1, SZ/2, SZ/2);
            }
          //predicted grid
          for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
            {
              //draw a green square around correct guesses
              if (PredictedGrid[r][c]==Grids[0][r][c])
              {
                g.setColor(Color.GREEN);
                g.fillRect(startX+shift+c*SZ+1,startY+r*SZ+1,SZ-1,SZ-1);
              }
              g.setColor(colors[PredictedGrid[r][c]]);
              g.fillOval(startX + shift + c*SZ + SZ/4 +1, startY + r*SZ + SZ/4 +1, SZ/2, SZ/2);
            }            
           
              
          //display score and info
          g.setColor(Color.BLACK);                    
          g.setFont(new Font("Arial",Font.BOLD,18));                            
          g.drawString("Real grid at day "+CurGrid,startX+N*SZ/3,30);                              
          g.drawString("Predicted grid",startX+N*SZ+gapX+N*SZ/3,30);                              

          g.drawString("SCORE  "+Score+" / "+(N*N),2*N*SZ+startX+gapX+30,30);            
          g.drawString("N = "+N,2*N*SZ+startX+gapX+30,80);  
          g.drawString("C = "+C,2*N*SZ+startX+gapX+30,100);  
          g.drawString("D = "+D,2*N*SZ+startX+gapX+30,120);  
          g.drawString("K = "+K,2*N*SZ+startX+gapX+30,140);  
        }
    
        
        // -------------------------------------
        public Vis()
        {
            jf.addWindowListener(this);             
            jf.addKeyListener(this);   
        }
        // -------------------------------------
        //WindowListener
        public void windowClosing(WindowEvent e){ 
            if(proc != null)
                try { proc.destroy(); } 
                catch (Exception ex) { ex.printStackTrace(); }
            System.exit(0); 
        }
        public void windowActivated(WindowEvent e) { }
        public void windowDeactivated(WindowEvent e) { }
        public void windowOpened(WindowEvent e) { }
        public void windowClosed(WindowEvent e) { }
        public void windowIconified(WindowEvent e) { }
        public void windowDeiconified(WindowEvent e) { }
        // -------------------------------------
        //MouseListener
        public void mouseClicked(MouseEvent e) { }
        public void mousePressed(MouseEvent e) { }
        public void mouseReleased(MouseEvent e) { }
        public void mouseEntered(MouseEvent e) { }
        public void mouseExited(MouseEvent e) { }
        // -------------------------------------
        //KeyListener
        public void keyTyped(KeyEvent e) { }
        public void keyReleased(KeyEvent e) { }
        public void keyPressed(KeyEvent e)
        {
          if (e.getKeyCode() == KeyEvent.VK_LEFT && CurGrid>0)
          {
            CurGrid--;
            v.repaint();
          }
          if (e.getKeyCode() == KeyEvent.VK_RIGHT && CurGrid<D)
          {
            CurGrid++;
            v.repaint();
          }          
        }

    }
    // -----------------------------------------
    public GlowingBacteriaVis(String seed) {
      try {
        if (vis)
        {
            jf = new JFrame();
            
            //JButton prevButton = new JButton("<");
            //prevButton.setBounds(2*N*SZ, 30, 50, 30);   //x,y,width,height
            //prevButton.setSize(60, 40);
            //jf.getContentPane().add(prevButton);
            //jf.add(prevButton);
            
            v = new Vis();
            jf.getContentPane().add(v);
        }
        if (exec != null) {
            try {
                Runtime rt = Runtime.getRuntime();
                proc = rt.exec(exec);
                os = proc.getOutputStream();
                is = proc.getInputStream();
                br = new BufferedReader(new InputStreamReader(is));
                new ErrorReader(proc.getErrorStream()).start();
            } catch (Exception e) { e.printStackTrace(); }
        }
        System.out.println("Score = " + runTest(seed));
        if (proc != null)
            try { proc.destroy(); } 
            catch (Exception e) { e.printStackTrace(); }
      }
      catch (Exception e) { e.printStackTrace(); }
    }
       
    
    // -----------------------------------------
    public static void main(String[] args) {
        String seed = "1";
        vis = true;
        SZ = 15;
        Debug = false;
        for (int i = 0; i<args.length; i++)
        {   if (args[i].equals("-seed"))
                seed = args[++i];
            if (args[i].equals("-exec"))
                exec = args[++i];
            if (args[i].equals("-novis"))
                vis = false;
            if (args[i].equals("-size"))
                SZ = Integer.parseInt(args[++i]);
            if (args[i].equals("-debug"))
                Debug = true;
        }
        if (seed.equals("1")) SZ = 40;
            
        GlowingBacteriaVis f = new GlowingBacteriaVis(seed);
    }
    // -----------------------------------------
    void addFatalError(String message) {
        System.out.println(message);
    }
}

class ErrorReader extends Thread{
    InputStream error;
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
                System.out.flush();
            }
        } catch(Exception e) { }
    }
}