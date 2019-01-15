import java.io.*;
import java.util.*;
import java.security.*;
import javax.imageio.*;
import java.awt.image.*;

// --------------------------------------------------------
public class StainedGlassVis {
    static int maxN = 1000, minN = 20;
    static int border = 1000;
    int N;                          // number of pieces allowed
    int H, W;
    int[][] givenImage;
    int[] imgArg;
    
    int Np;                         // number of pieces used
    int[][] drawnImage;
    // ---------------------------------------------------
    String generate(String seedStr) {
      try {
        SecureRandom rnd = SecureRandom.getInstance("SHA1PRNG");
        long seed = Long.parseLong(seedStr);
        rnd.setSeed(seed);
        N = rnd.nextInt(maxN - minN + 1) + minN;
        if (seed == 1)
            N = minN;
        else if (seed == 2)
            N = maxN;

        // read image from file seedStr + ".jpg" (except for seed 1 which is .png)
        BufferedImage img = ImageIO.read(new File("images//" + seedStr + (seed == 1 ? ".png" : ".jpg")));
        H = img.getHeight();
        W = img.getWidth();
        givenImage = new int[H][W];
        for (int r = 0; r < H; ++r)
        for (int c = 0; c < W; ++c)
            givenImage[r][c] = img.getRGB(c, r) & 0xFFFFFF;

        // convert image to int[] argument
        imgArg = new int[H * W];
        for (int r = 0; r < H; ++r)
        for (int c = 0; c < W; ++c)
            imgArg[r * W + c] = givenImage[r][c];

        // generate test representation
        StringBuffer sb = new StringBuffer();
        sb.append("H = " + H + '\n');
        sb.append("W = " + W + '\n');
        sb.append("N = " + N + '\n');
        return sb.toString();
      }
      catch (Exception e) {
        addFatalError("An exception occurred while generating test case.");
        e.printStackTrace();
        return "";
      }
    }
    // ---------------------------------------------------
    int getComponent(int color, int index) {
        return (color >> (8 * index)) & 0xFF;
    }
    // ---------------------------------------------------
    int getDiff(int c1, int c2) {
        int d = 0;
        for (int i = 0; i < 3; ++i)
            d += Math.abs(getComponent(c1, i) - getComponent(c2, i));
        return d;
    }
    // ---------------------------------------------------
    int p2(int t) {
        return t*t;
    }
    // ---------------------------------------------------
    public double runTest(String seed) {
      try {
        String test = generate(seed);
        if (debug)
            System.out.println(test);

        // call user's solution and get return
        int[] pointRow, pointCol, color;
        HashSet<Integer> colors = new HashSet<>();
        if (proc != null) {
            int[] raw_points;
            try {
                raw_points = create(H, imgArg, N);
            } catch (Exception e) {
                addFatalError("Failed to get result from create.");
                return -1;
            }

            if (raw_points.length % 3 != 0) {
                addFatalError("The number of elements in your return must be divisible by 3, and your return contained " + raw_points.length + ".");
                return -1;
            }
            if (raw_points.length == 0) {
                addFatalError("Your return must have at least 3 elements, and it contained " + raw_points.length + ".");
                return -1;
            }
            if (raw_points.length > 3 * N) {
                addFatalError("Your return can have at most " + (3 * N) + " elements, and it contained " + raw_points.length + ".");
                return -1;
            }

            // check that this is a valid set of points
            Np = raw_points.length / 3;
            pointRow = new int[Np];
            pointCol = new int[Np];
            color = new int[Np];
            for (int i = 0; i < Np; ++i) {
                pointRow[i] = raw_points[3*i];
                pointCol[i] = raw_points[3*i + 1];
                color[i]    = raw_points[3*i + 2];
                if (pointRow[i] < -border || pointRow[i] > H-1 + border) {
                    addFatalError("Seed point " + i + " must be at row between " + (-border) + " and " + (H-1 + border) + ", inclusive.");
                    return -1;
                }
                if (pointCol[i] < -border || pointCol[i] > W-1 + border) {
                    addFatalError("Seed point " + i + " must be at column between " + (-border) + " and " + (W-1 + border) + ", inclusive.");
                    return -1;
                }
                if (color[i] < 0 || color[i] > 0xFFFFFF) {
                    addFatalError("Piece " + i + " can only have color between 0 and 0xFFFFFF.");
                    return -1;
                }

                colors.add(color[i]);
            }

            // check that no two points are the same
            for (int i = 0; i < Np; ++i)
            for (int j = i + 1; j < Np; ++j)
                if (pointRow[i] == pointRow[j] && pointCol[i] == pointCol[j]) {
                    addFatalError("Seed points " + i + " and " + j + " have the same coordinates.");
                    return -1;
                }
        }
        else {
            // one black point in the corner
            Np = 1;
            pointRow = new int[]{0};
            pointCol = new int[]{0};
            color = new int[]{0};
        }

        // build Voronoi diagram on the returned set of points
        // the color of each pixel is the color of the nearest point
        drawnImage = new int[H][W];
        for (int r = 0; r < H; ++r)
        for (int c = 0; c < W; ++c) {
            int minDist2 = -1;
            for (int ind = 0; ind < Np; ++ind) {
                int dist2 = p2(pointRow[ind] - r) + p2(pointCol[ind] - c);
                if (minDist2 == -1 || dist2 < minDist2) {
                    minDist2 = dist2;
                    drawnImage[r][c] = color[ind];
                }
            }
        }
        
        if (vis) {
            BufferedImage bi = new BufferedImage(W, H, BufferedImage.TYPE_INT_RGB);
            for (int r = 0; r < H; ++r)
            for (int c = 0; c < W; ++c)
                bi.setRGB(c, r, drawnImage[r][c]);
            if (mark)
                for (int ind = 0; ind < Np; ++ind) {
                    for (int dr = -3; dr <= 3; dr++)
                        if (pointRow[ind] + dr >= 0 && pointRow[ind] + dr < H)
                            for (int dc = -3; dc <= 3; dc++)
                                if (pointCol[ind] + dc >= 0 && pointCol[ind] + dc < W)
                                    bi.setRGB(pointCol[ind] + dc, pointRow[ind] + dr, 0);
                }
            ImageIO.write(bi,"png", new File(seed + ".png"));
        }

        // calculate difference between the given image and the stained glass one
        double diff = 0;
        for (int r = 0; r < H; ++r)
        for (int c = 0; c < W; ++c)
            diff += getDiff(givenImage[r][c], drawnImage[r][c]);

        // get the number of distinct colors used
        double distinctColors = colors.size();

        if (debug) {
            addFatalError("Difference between images = " + diff);
            addFatalError("Distinct colors used = " + colors.size());
            addFatalError("Pieces of glass used = " + Np);
        }

        return diff * Math.pow(1 + distinctColors / Np, 2);
      }
      catch (Exception e) {
        addFatalError("An exception occurred while trying to process your program's results.");
        e.printStackTrace();
        return -1.0;
      }
    }
// ------------- visualization part ----------------------
    static String exec;
    static boolean vis, debug, mark;
    static Process proc;
    InputStream is;
    OutputStream os;
    BufferedReader br;
    // ---------------------------------------------------
    int[] create(int H, int[] pixels, int N) throws IOException {
        // pass the params to the solution and get the return
        int i;
        StringBuffer sb = new StringBuffer();
        sb.append(H).append('\n');
        sb.append(pixels.length).append('\n');
        for (i = 0; i < pixels.length; ++i)
            sb.append(pixels[i]).append('\n');
        sb.append(N).append('\n');
        os.write(sb.toString().getBytes());
        os.flush();

        // get the return - an array of integers
        int nRet = Integer.parseInt(br.readLine());
        int[] ret = new int[nRet];
        for (i = 0; i < nRet; ++i)
            ret[i] = Integer.parseInt(br.readLine());
        return ret;
    }
    // ---------------------------------------------------
    public StainedGlassVis(String seed) {
        // interface for runTest
        Thread thread = null;
        if (exec != null) {
            try {
                Runtime rt = Runtime.getRuntime();
                proc = rt.exec(exec);
                os = proc.getOutputStream();
                is = proc.getInputStream();
                br = new BufferedReader(new InputStreamReader(is));
                thread = new ErrorReader(proc.getErrorStream());
                thread.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        double s = runTest(seed);

        if (thread != null)
            try { thread.join(1000); } 
            catch (Exception e) { e.printStackTrace(); }

        System.out.println("Score = " + s);

        if (proc != null)
            try { proc.destroy(); }
            catch (Exception e) { e.printStackTrace(); }
    }
    // ---------------------------------------------------
    public static void main(String[] args) {
        String seed = "1";
        vis = true;
        for (int i = 0; i < args.length; i++) {
            if (args[i].equals("-seed"))
                seed = args[++i];
            if (args[i].equals("-exec"))
                exec = args[++i];
            if (args[i].equals("-novis"))
                vis = false;
            if (args[i].equals("-debug"))
                debug = true;
            if (args[i].equals("-mark"))
                mark = true;
        }
        StainedGlassVis f = new StainedGlassVis(seed);
    }
    // ---------------------------------------------------
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
