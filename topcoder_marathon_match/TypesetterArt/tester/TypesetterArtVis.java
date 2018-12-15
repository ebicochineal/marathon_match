import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.GraphicsEnvironment;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import javax.imageio.ImageIO;

public class TypesetterArtVis {
    
    private Process proc;
    private OutputStream os;
    private InputStream is;
    private BufferedReader br;
    
    private Random random;
    private String exec;
    private String save;
    private String orig;
    private long seed = 1;
    private boolean verbose = false;
    
    private int precision;
    private int nRenders;
    private final int nLayers = 4;
    private int nFonts;
    private Font[] fonts;
    
    private BufferedImage original;
    private int[][][] originalCmyk = new int[4][][];
    private int[][][] layers = new int[4][][];
    private Graphics2D graphics;
    private boolean valid = true;
    
    private long measuredMillis = 0;
	private static final long TIMEOUT_MILLIS = 10000;
    
    private int[] callRender() throws IOException {
        StringBuilder sb = new StringBuilder();
        sb.append(TIMEOUT_MILLIS - measuredMillis).append('\n');
        
        if (verbose) {
            debugTesterOut(sb.toString());
        }
        
        long startMillis = System.currentTimeMillis();
        
        os.write(sb.toString().getBytes());
        os.flush();

        int n = Integer.parseInt(br.readLine());
        int[] ret = new int[n];
        for (int i = 0; i < n; i++) {
            ret[i] = Integer.parseInt(br.readLine());
        }
        
        measuredMillis += System.currentTimeMillis() - startMillis;
        
        if (verbose) {
            System.out.printf("[CLIENT]\t%d\n", n);
            for (int i = 0; i < n; i++) {
                System.out.printf("[CLIENT]\t%d\n", ret[i]);
            }
        }
        
        return ret;
    }
    
    private void callInit() throws IOException {
        StringBuilder sb = new StringBuilder();
        sb.append(nRenders).append('\n');
        sb.append(nFonts).append('\n');
        sb.append(precision).append('\n');
        sb.append(original.getWidth()).append('\n');
        sb.append(original.getHeight()).append('\n');
        sb.append(nLayers * original.getWidth() * original.getHeight()).append('\n');
        
        for (int k = 0; k < nLayers; k++) {
            for (int i = 0; i < original.getHeight(); i++) {
                for (int j = 0; j < original.getWidth(); j++) {
                    sb.append(originalCmyk[k][i][j]).append('\n');
                }
            }
        }
        
        if (verbose) {
            String s = sb.toString();
            if (s.length() > 1000) {
                s = s.substring(0, 1000) + "...\n";
            }
            debugTesterOut(s);
        }
        
        long startMillis = System.currentTimeMillis();
        
        os.write(sb.toString().getBytes());
        os.flush();

        int d = Integer.parseInt(br.readLine());
        
        measuredMillis += System.currentTimeMillis() - startMillis;
        
        if (verbose) {
            System.out.printf("[CLIENT]\t%d\n", d);
        }
    }
    
    private void callNextGlyphs() throws IOException {
        StringBuilder builder = new StringBuilder("0\n0\n0\n");
        
        builder.append(TIMEOUT_MILLIS - measuredMillis).append("\n");
        
        while (true) {
            if (verbose) {
                debugTesterOut(builder.toString());
            }
            
            long startMillis = System.currentTimeMillis();
            
            os.write(builder.toString().getBytes());
            os.flush();

            String s = br.readLine();
            
            measuredMillis += System.currentTimeMillis() - startMillis;
            
            if (verbose) {
                System.out.printf("[CLIENT]\t%s\n", s);
            }
            
            if (s.isEmpty()) {
                System.out.printf("[TESTER]\tNext glyph phase ended\n");
                break;
            }
            
            String[] parts = s.split(" ");
            
            if (parts.length != 3) {
                System.out.printf("[ERROR]\tNext Glyph should return 0 or 3 integers\n");
                valid = false;
                break;
            }
            
            int letterId = Integer.parseInt(parts[0]);
            int fontId = Integer.parseInt(parts[1]);
            int sizeId = Integer.parseInt(parts[2]);
            
            if (letterId < 32 || letterId > 126) {
                System.out.printf("[ERROR]\tChar ID: %d\n", letterId);
                valid = false;
            }
            if (fontId < 0 || fontId >= nFonts) {
                System.out.printf("[ERROR]\tFont ID: %d\n", fontId);
                valid = false;
            }
            if (sizeId < 8 || sizeId > 72) {
                System.out.printf("[ERROR]\tSize ID: %d\n", sizeId);
                valid = false;
            }
            
            if (!valid) {
                break;
            }
            
            Font f = fonts[fontId].deriveFont((float)sizeId);
            FontMetrics metrics = graphics.getFontMetrics(f);
            int h = metrics.getHeight();
            int w = (int)Math.ceil(metrics.getStringBounds("" + (char)letterId, graphics).getWidth());
            
            builder = new StringBuilder();
            builder.append(w).append("\n");
            builder.append(h).append("\n");
            builder.append((w + (32 - (w % 32)) % 32) * h / 32).append("\n");
            if (w > 0) {
                BufferedImage temp = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_BINARY);
                Graphics2D g = temp.createGraphics();

                g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
                g.setFont(f);
                g.setColor(Color.WHITE);
                g.fillRect(0, 0, w, h);

                g.setColor(Color.BLACK);
                g.drawString("" + (char)letterId, 0, h);
                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j += 32) {
                        int mask = 0;
                        for (int k = j; k < j + 32 && k < w; k++) {
                            if ((temp.getRGB(k, i) & 0XFF) == 0) {
                                mask |= 1 << (k - j);
                            }
                        }
                        builder.append(mask).append("\n");
                    }
                }
            }
            
            builder.append(TIMEOUT_MILLIS - measuredMillis).append("\n");
        }
    }
    
    private void createLayer(int iteration, int[] data) {
        if (data.length != 0) {
            int fontId = data[0];
            int sizeId = data[1];
            int colorId = data[2];
            int saturation = data[3];

            if (fontId < 0 || fontId >= nFonts) {
                System.out.printf("[ERROR]\tLayer: %d, Font ID: %d\n", iteration, fontId);
                valid = false;
            }
            else if (sizeId < 8 || sizeId > 72) {
                System.out.printf("[ERROR]\tLayer: %d, Size ID: %d\n", iteration, sizeId);
                valid = false;
            }
            else if (colorId < 0 || colorId >= nLayers) {
                System.out.printf("[ERROR]\tLayer: %d, Color ID: %d\n", iteration, colorId);
                valid = false;
            }
            else if (saturation < 0 || saturation > 255) {
                System.out.printf("[ERROR]\tLayer: %d, Saturation: %d\n", iteration, saturation);
                valid = false;
            }
            else {
                Font f = fonts[fontId].deriveFont((float)sizeId);
                for (int i = 4; i < data.length; i++) {
                    if (data[i] != (int)'\n' && (data[i] < 32 || data[i] > 126)) {
                        System.out.printf("[ERROR]\tLayer: %d, Index: %d, Char ID: %d\n", iteration, i - 3, data[i]);
                        valid = false;
                        return;
                    }
                }

                BufferedImage temp = new BufferedImage(original.getWidth(), original.getHeight(), BufferedImage.TYPE_BYTE_BINARY);
                Graphics2D tempG = temp.createGraphics();
                FontMetrics metrics = graphics.getFontMetrics(f);
                
                tempG.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
                tempG.setFont(f);
                tempG.setColor(Color.WHITE);
                tempG.fillRect(0, 0, temp.getWidth(), temp.getHeight());
                
                int lineNo = 0;
                int left = 0;
                Map<Integer, BufferedImage> letterCache = new HashMap<>();
                for (int i = 4; i < data.length; i++) {
                    if (data[i] != (int)'\n') {
                        int h = metrics.getHeight();
                        int w = (int)Math.ceil(metrics.getStringBounds("" + (char)data[i], graphics).getWidth());
                        
                        if (w > 0) {
                            if (!letterCache.containsKey(data[i])) {
                                BufferedImage letter = new BufferedImage(w, h, BufferedImage.TYPE_BYTE_BINARY);
                                Graphics2D letterG = letter.createGraphics();

                                letterG.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
                                letterG.setFont(f);
                                letterG.setColor(Color.WHITE);
                                letterG.fillRect(0, 0, w, h);

                                letterG.setColor(Color.BLACK);
                                letterG.drawString("" + (char)data[i], 0, h);

                                letterCache.put(data[i], letter);
                            }
                            tempG.drawImage(letterCache.get(data[i]), left, lineNo * h, null);
                            left += w;
                        }
                    }
                    else {
                        lineNo++;
                        left = 0;
                    }
                }
                
                for (int y = 0; y < temp.getHeight(); y++) {
                    for (int x = 0; x < temp.getWidth(); x++) {
                        if ((temp.getRGB(x, y) & 0XFF) == 0) {
                            int cmykComponent = layers[colorId][y][x] + saturation;

                            layers[colorId][y][x] = Math.min(255, cmykComponent);
                        }
                    }
                }
            }
        }
    }
    
    private double score() throws Exception {
        if (save != null) {
            BufferedImage mix = new BufferedImage(original.getWidth(), original.getHeight(), BufferedImage.TYPE_INT_RGB);

            for (int i = 0; i < original.getHeight(); i++) {
                for (int j = 0; j < original.getWidth(); j++) {
                    int rgbR = (int)Math.round(255 * (1 - layers[0][i][j] / 255.0) * (1 - layers[3][i][j] / 255.0));
                    int rgbG = (int)Math.round(255 * (1 - layers[1][i][j] / 255.0) * (1 - layers[3][i][j] / 255.0));
                    int rgbB = (int)Math.round(255 * (1 - layers[2][i][j] / 255.0) * (1 - layers[3][i][j] / 255.0));
                    
                    mix.setRGB(j, i, (rgbR << 16) | (rgbG << 8) | rgbB);
                }
            }
            
            ImageIO.write(mix, "png", new File(save));
        }
        
        if (!valid) {
            return -1;
        }

        double res = 0;
        int div = 0;
        for (int i = 0; i < original.getHeight(); i += precision) {
            for (int j = 0; j < original.getWidth(); j += precision) {
                for (int k = 0; k < nLayers; k++) {
                    double originalSum = 0;
                    double actualSum = 0;
                    int n = 0;
                    for (int top = 0; top < precision && top + i < original.getHeight(); top++) {
                        for (int left = 0; left < precision && left + j < original.getWidth(); left++) {
                            originalSum += originalCmyk[k][i + top][j + left];
                            actualSum += layers[k][i + top][j + left];
                            n++;
                        }
                    }
                    
                    if (n != 0) {
                        originalSum /= n * 255;
                        actualSum /= n * 255;

                        res += Math.pow(1 - Math.abs(actualSum - originalSum), 2);
                        div++;
                    }
                }
            }
        }

        res /= div;
        
        return res * 1000000;
    }
    
    public double runTest() {
        try {
            fonts = GraphicsEnvironment.getLocalGraphicsEnvironment().getAllFonts();
            random = SecureRandom.getInstance("SHA1PRNG"); 
            
            random.setSeed(seed);

            proc = Runtime.getRuntime().exec(exec);
            os = proc.getOutputStream();
            is = proc.getInputStream();
            br = new BufferedReader(new InputStreamReader(is));
            new ErrorReader(proc.getErrorStream()).start();

            if (nRenders == 0) {
                nRenders = 1 + random.nextInt(16);
            }
            if (nFonts == 0) {
                nFonts = 10 + random.nextInt(16);
            }
            if (precision == 0) {
                precision = 1 + random.nextInt(16);
            }
            if (orig == null) {
                orig = seed + ".jpg";
            }
            Collections.shuffle(Arrays.asList(fonts), random);

            original = ImageIO.read(new File(orig));
            graphics = original.createGraphics();

            for (int k = 0; k < nLayers; k++) {
                originalCmyk[k] = new int[original.getHeight()][original.getWidth()];
            }
            
            for (int i = 0; i < original.getHeight(); i++) {
                for (int j = 0; j < original.getWidth(); j++) {
                    int rgb = original.getRGB(j, i);
                    double r = ((rgb >> 16) & 0XFF) / 255.0;
                    double g = ((rgb >> 8) & 0XFF) / 255.0;
                    double b = (rgb & 0XFF) / 255.0;

                    double k = 1.0 - Math.max(Math.max(r, g), b);
                    double c = k > 1 - 1E-2 ? (r + k > 1 - 1E-2 ? 1 : 0) : (1 - r - k) / (1 - k);
                    double m = k > 1 - 1E-2 ? (g + k > 1 - 1E-2 ? 1 : 0) : (1 - g - k) / (1 - k);
                    double y = k > 1 - 1E-2 ? (b + k > 1 - 1E-2 ? 1 : 0) : (1 - b - k) / (1 - k);

                    originalCmyk[0][i][j] = (int)Math.round(c * 255);
                    originalCmyk[1][i][j] = (int)Math.round(m * 255);
                    originalCmyk[2][i][j] = (int)Math.round(y * 255);
                    originalCmyk[3][i][j] = (int)Math.round(k * 255);
                }
            }
            
            callInit();

            if (valid) {
                callNextGlyphs();
            }
            
            if (valid) {
                for (int k = 0; k < nLayers; k++) {
                    layers[k] = new int[original.getHeight()][original.getWidth()];
                }
                
                for (int i = 0; i < nRenders && valid; i++) {
                    createLayer(i, callRender());
                }
            }

            return score();
        }
        catch (Exception e) {
            System.out.printf("[ERROR]\tError interacting with the solution: %s\n", e.getClass().getName());
            return -1;
        }
        finally {            
            try {
                proc.destroy();
            }
            catch (Exception x) { }
        }
    }
    
    private static void debugTesterOut(String s) {
        String tester = "\n[TESTER]\t";
        s = s.replace("\n", tester);
        if (s.contains("\n")) {
            s = s.substring(0, s.length() - tester.length());
        }
        System.out.print(tester.substring(1) + s + "\n");
    }
    
    public TypesetterArtVis(String[] args) {
        int i = 0;
        
        while (i < args.length) {
            switch (args[i]) {
                case "-seed":
                    seed = Long.parseLong(args[++i]);
                    break;
                case "-renders":
                    nRenders = Integer.parseInt(args[++i]);
                    break;
                case "-fonts":
                    nFonts = Integer.parseInt(args[++i]);
                    break;
                case "-exec":
                    exec = args[++i];
                    break;
                case "-save":
                    save = args[++i];
                    break;
                case "-orig":
                    orig = args[++i];
                    break;
                case "-verbose":
                    verbose = true;
                    break;
                default:
                    break;
            }
            i++;
        }
    }
    
    public static void main(String[] args) throws Exception {
        TypesetterArtVis vis = new TypesetterArtVis(args);
        System.out.printf("Score: %.3f\n", vis.runTest());
    }
}

class ErrorReader extends Thread {

    private final InputStream error;

    public ErrorReader(InputStream is) {
        error = is;
    }

    @Override
    public void run() {
        try (Scanner scanner = new Scanner(error)) {
            while (scanner.hasNextLine()) {
                String s = scanner.nextLine();
                
                System.out.println("[STDERR]\t" + s);
                System.out.flush();
            }
        }
    }
}