import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.security.*;
import java.util.*;
import java.net.URL;
import javax.swing.*;
import javax.imageio.*;


public class SnakeCharmerVis {

    //finals 
    final static int[] dr = { 0,1,0,-1};
    final static int[] dc = {-1,0,1, 0};  
    final static char EMPTY = '.';

    //test parameters
    private static int minN = 7, maxN = 49;
    private static int minV = 2, maxV = 8;
    private static int minVal = 2;
    
    //inputs
    int N;      //grid size
    int V;      //number of values
    String Snake;
        
    //outputs
    int Score;  
    char[][] Grid;   
    char[] Solution;     
    
    // -----------------------------------------
    void generate(String seedStr) {
      try {
        // generate test case
        SecureRandom r1 = SecureRandom.getInstance("SHA1PRNG"); 
        long seed = Long.parseLong(seedStr);
        r1.setSeed(seed);
        
        //generate grid size
        N = r1.nextInt((maxN - minN)/2 + 1)*2 + minN;
        
        //generate number of values
        V = r1.nextInt(maxV - minV + 1) + minV;       

        //set easiest/hardest seeds
        if (seed == 1)
        {
          N = minN;
          V = 3;
        }
        if (seed == 2)
        {
          N = maxN;            
          V = maxV;
        }

        //generate snake
        Snake="";
        int prev=-1;
        for (int i=0; i<N*N; )
        {
          int val=r1.nextInt(V - 1 + 1) + minVal;       

          Snake+=val;
          prev=val;
          i++;
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
        System.out.println("Values, V = "+V);
        System.out.println("Snake = "+Snake);      
    }
            
        
    // -----------------------------------------
    public double runTest(String seed) {
      try {
        generate(seed);        

        if (proc != null) {
            // call the solution
            try { 
                Solution = callSolution();
            } catch (Exception e) {
                addFatalError("Failed to get result from your solution.");
                return -1.0;
            }

            // check the return and score it
            if (Solution == null) {
                addFatalError("Your return contained an invalid number of elements.");
                return -1.0;
            }
            if (Solution.length > N*N-1) {
                addFatalError("Your return contained more than " + (N*N-1) + " elements.");
                return -1.0;
            }
            
            
            //construct output board and check for invalid characters
            Grid=new char[N][N];
            for (int i=0; i<N; i++) for (int k=0; k<N; k++) Grid[i][k]=EMPTY;
            int curR=N/2;
            int curC=N/2;
            Grid[curR][curC]=Snake.charAt(Solution.length);
            for (int i=0; i<Solution.length; i++)
            {
              char c=Solution[i];
              if (c=='L') curC--;
              else if (c=='R') curC++;
              else if (c=='U') curR--;
              else if (c=='D') curR++;
              else
              {
                addFatalError("Unknown direction "+c+" at move "+(i+1));
                return -1.0;                
              }

              if (!inGrid(curR,curC))
              {
                addFatalError("You stepped out of grid bounds at move "+(i+1));
                return -1.0;                                
              }
              if (Grid[curR][curC]!=EMPTY)
              {
                addFatalError("You've hit yourself at move "+(i+1));
                return -1.0;                                                
              }
              Grid[curR][curC]=Snake.charAt(Solution.length-(i+1));
            }



            if (Debug)
            {
              System.err.println("\nYour moves: "+new String(Solution));   
              for (int i=0; i<N; i++)
              {
                for (int k=0; k<N; k++) System.out.print(Grid[i][k]);
                System.out.println();
              }
            }
              
              
            //compute the raw score
            Score=0;          
            for (int r=0; r<N; r++)
              for (int c=0; c<N; c++)
              {
                if (Grid[r][c]==EMPTY) continue;

                int matches=0;
                for (int m=0; m<dr.length; m++)
                {
                  int r2=r+dr[m];
                  int c2=c+dc[m];
                  if (inGrid(r2,c2) && Grid[r][c]==Grid[r2][c2]) matches++;
                }

                int val=(int)(Grid[r][c]-'0');
                Score+=(int)Math.pow(val,matches+1);
              }
                                        
            
            if (vis) {
                //show seed in the title. Thank you wleite for the idea!
                jf.setTitle("SnakeCharmer, seed = " + seed);
                
                jf.setVisible(true);                
                
                //Calculate SZ to fit the window, if SZ is 0 (default). Thank you wleite for the idea!
                Insets frameInsets = jf.getInsets();
                int fw = frameInsets.left + frameInsets.right;
                int fh = frameInsets.top + frameInsets.bottom;
                Toolkit toolkit = Toolkit.getDefaultToolkit();
                Dimension screenSize = toolkit.getScreenSize();
                Insets screenInsets = toolkit.getScreenInsets(jf.getGraphicsConfiguration());
                screenSize.width -= screenInsets.left + screenInsets.right;
                screenSize.height -= screenInsets.top + screenInsets.bottom;
                if (SZ == 0) SZ = Math.min((screenSize.width - fw - 280) / N, (screenSize.height - fh - 20) / N);
                jf.setSize(N*SZ + 280 + fw, N*SZ + 20 + fh);                          

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


    public boolean inGrid(int r, int c)
    {
      return r>=0 && r<N && c>=0 && c<N;
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
    static int SZ=0;
    static boolean Debug;

    
    // -----------------------------------------
    private char[] callSolution() throws IOException, NumberFormatException {
        if (exec == null) return null;

        String s=N+"\n"+V+"\n"+Snake+"\n";
        os.write(s.getBytes());
        os.flush();

        // and get the return value
        char[] moves=new char[Integer.parseInt(br.readLine())];
        for (int i = 0; i < moves.length; i++)
            moves[i] = br.readLine().charAt(0);
        return moves;
    }
    // -----------------------------------------
    void draw() {
        if (!vis) return;
        v.repaint();
    }
    // -----------------------------------------
    public class Vis extends JPanel implements MouseListener, WindowListener {
        public void paint(Graphics g) {
        
          //Use antialiasing when painting. Thank you wleite for the idea!
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
                 
          Color[] colors={Color.WHITE,Color.GREEN,Color.CYAN,Color.ORANGE,Color.RED};
              
          int startX=20;
          int startY=20;
                    
          // gray background
          g.setColor(new Color(0xDDDDDD));
          g.fillRect(0,0,10000,10000);
          // white rectangle
          g.setColor(Color.WHITE);
          g.fillRect(startX,startY,N*SZ,N*SZ);
          

          //matches
          for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
            {
              if (Grid[r][c]==EMPTY) continue;

              int matches=0;
              for (int m=0; m<dr.length; m++)
              {
                int r2=r+dr[m];
                int c2=c+dc[m];
                if (inGrid(r2,c2) && Grid[r][c]==Grid[r2][c2]) matches++;
              }              
              g.setColor(colors[matches]);
              g.fillRect(startX+c*SZ,startY+r*SZ,SZ,SZ);  
            }               


          //path
          int curR=N/2;
          int curC=N/2;
          
          int borderSize=3;
          Graphics2D g2 = (Graphics2D) g;
          Stroke oldStroke = g2.getStroke();
          g2.setStroke(new BasicStroke(borderSize));
          g2.setColor(Color.BLACK);
          g2.drawRect(startX+curC*SZ,startY+curR*SZ,SZ,SZ);      //highlight starting number
          g2.setStroke(oldStroke);
          
          for (int i=0; i<Solution.length; i++)
          {
            char c=Solution[i];
            int newR=curR;
            int newC=curC;

            if (c=='L') newC--;
            else if (c=='R') newC++;
            else if (c=='U') newR--;
            else if (c=='D') newR++;

            g.setColor(Color.BLACK);
            g.drawLine(startX+curC*SZ+SZ/2,startY+curR*SZ+SZ/2,startX+newC*SZ+SZ/2,startY+newR*SZ+SZ/2);

            curR=newR;
            curC=newC;
          }
          g2.setStroke(new BasicStroke(borderSize));
          g2.setColor(Color.BLACK);
          g2.drawRect(startX+curC*SZ,startY+curR*SZ,SZ,SZ);      //highlight ending number
          g2.setStroke(oldStroke);


          //numbers                             
          for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
            {
              if (Grid[r][c]==EMPTY) continue;

              g.setColor(Color.BLACK);                    
              g.setFont(new Font("Arial",Font.PLAIN,14));  
              g.drawString(""+Grid[r][c],startX+c*SZ+SZ/2-5,startY+r*SZ+SZ/2+5);      
            }

              
          //display score and info
          g.setColor(Color.BLACK);                    
          g.setFont(new Font("Arial",Font.BOLD,18));                                                
          g.drawString("SCORE  "+Score,N*SZ+startX+30,30);            
          g.drawString("N = "+N,N*SZ+startX+30,80);  
          g.drawString("V = "+V,N*SZ+startX+30,100);  
        }
    
        
        // -------------------------------------
        public Vis()
        {
            jf.addWindowListener(this);             
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
    }
    // -----------------------------------------
    public SnakeCharmerVis(String seed) {
      try {
        if (vis)
        {
            jf = new JFrame();            
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
            
        SnakeCharmerVis f = new SnakeCharmerVis(seed);
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