import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.awt.image.*;
import java.io.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.List;
import java.util.concurrent.atomic.*;
import javax.imageio.*;
import javax.swing.*;

public class ImageFromBlocksVis {
	private static long timeLimit = 10;
	private static final int minSize = 8, maxSize = 20; 
	private static final int minImageDimension = 300, maxImageDimension = 800;
	private static final int[][][] pieces = new int[][][] {{{1,1}},{{1,1,1}},{{1,0},{1,1}},{{1,1,1,1}},{{1,1},{1,1}},{{0,1,0},{1,1,1}},{{1,1,0},{0,1,1}},{{0,1,1},{1,1,0}},{{1,0,0},{1,1,1}},{{0,0,1},{1,1,1}}};
	private static String imagesFolder = "images";
	private int blockSize, maxDiscard, imageHeight, imageWidth, boardHeight, boardWidth, filled, discarded, currPieceIdx;
	private double score;
	private int[] pixels;
	private int[][] boardColors, boardPieces, currPiece;
	private BufferedImage image, errorImage;
	private SecureRandom rnd;

	public String generate(String seedStr) {
		try {
			rnd = SecureRandom.getInstance("SHA1PRNG");
			long seed = Long.parseLong(seedStr);
			rnd.setSeed(seed);

			// Size in pixels of each block
			blockSize = random(minSize, maxSize);
			if (seed == 1) blockSize = maxSize;
			else if (seed == 2) blockSize = minSize;

			// List images in the folder
			File folder = new File(imagesFolder);
			if (!folder.exists()) {
				addFatalError("ERROR: Images folder \"" + imagesFolder + "\" not found!");
				System.exit(-1);
			}
			File[] files = folder.listFiles();
			List<File> imageFiles = new ArrayList<File>();
			for (File file : files) {
				if (file.isFile() && file.getName().toLowerCase().endsWith(".jpg")) imageFiles.add(file);
			}
			if (imageFiles.isEmpty()) {
				addFatalError("ERROR: No JPG images in folder \"" + imagesFolder + "\\\"!");
				System.exit(-1);
			}
			Collections.sort(imageFiles);

			// Get one image based on the seed (seed=1 -> first image, seed=2 -> second one, and so on) 
			int idx = (int) ((seed - 1) % imageFiles.size());
			if (idx < 0) idx += imageFiles.size();
			File imageFile = imageFiles.get(idx);
			if (debug) System.out.println("Image File = " + imageFile);
			image = ImageIO.read(imageFile);
			if (image.getHeight() < minImageDimension || image.getWidth() < minImageDimension) {
				addFatalError("ERROR: Invalid image dimensions \"" + imageFile + "\"!");
				System.exit(-1);
			}
			boardHeight = Math.min(maxImageDimension, image.getHeight()) / blockSize;
			boardWidth = Math.min(maxImageDimension, image.getWidth()) / blockSize;
			imageHeight = boardHeight * blockSize;
			imageWidth = boardWidth * blockSize;
			if (vis) errorImage = new BufferedImage(imageWidth, imageHeight, BufferedImage.TYPE_INT_RGB);
			pixels = new int[imageHeight * imageWidth];
			for (int y = 0; y < imageHeight; y++) {
				int yw = y * imageWidth;
				for (int x = 0; x < imageWidth; x++) {
					pixels[yw + x] = image.getRGB(x, y) & 0xFFFFFF;
					if (vis) errorImage.setRGB(x, y, 0xFFFFFF);
				}
			}
			boardColors = new int[boardHeight][boardWidth];
			boardPieces = new int[boardHeight][boardWidth];
			for (int i = 0; i < boardHeight; i++) {
				Arrays.fill(boardColors[i], -1);
				Arrays.fill(boardPieces[i], -1);
			}

			// Maximum number of pieces to be discarded
			int numCells = boardHeight * boardWidth;
			maxDiscard = random(numCells / 40, numCells / 4);

			// generate test representation
			StringBuffer sb = new StringBuffer();
			sb.append("BlockSize = " + blockSize + '\n');
			sb.append("ImageHeight = " + imageHeight + '\n');
			sb.append("ImageWidth = " + imageWidth + '\n');
			sb.append("MaxDiscard = " + maxDiscard + '\n');
			return sb.toString();
		} catch (Exception e) {
			addFatalError("An exception occurred while generating test case.");
			e.printStackTrace();
			return "";
		}
	}

	private static int getComponent(int color, int index) {
		return (color >>> (index << 3)) & 0xFF;
	}

	private static int getDiff(int c1, int c2) {
		int d = 0;
		for (int i = 0; i < 3; i++) {
			d += Math.abs(getComponent(c1, i) - getComponent(c2, i));
		}
		return d;
	}

	private static int getRGBDiff(int c1, int c2) {
		int d = Math.abs(getComponent(c1, 0) - getComponent(c2, 0)) << 16;
		d |= Math.abs(getComponent(c1, 1) - getComponent(c2, 1)) << 8;
		d |= Math.abs(getComponent(c1, 2) - getComponent(c2, 2));
		return d;
	}

	public double runTest(String seed) {
		try {
			String test = generate(seed);
			if (debug) System.out.println(test);
			if (vis) {
				v.init();
				if (maximized) jf.setExtendedState(JFrame.MAXIMIZED_BOTH);
				jf.pack();
				jf.setVisible(true);
			}
			if (proc != null) {
				// Call user's solution
				long timeLeft = timeLimit * 1_000_000_000L;
				try {
					long startTime = System.nanoTime();
					init(imageHeight, blockSize, maxDiscard, pixels);
					timeLeft -= System.nanoTime() - startTime;
				} catch (Exception e) {
					e.printStackTrace();
					addFatalError("Failed to get result from initialize.");
					return 0;
				}
				if (timeLeft < 0) {
					addFatalError("Init: Time limit exceeded.");
					return 0;
				}
				nextPiece();
				if (vis) v.fullRepaint();
				if (vis) delay(delay);
				while (currPiece != null) {
					String ret = null;
					try {
						int n = 0;
						int[] pPiece = new int[currPiece.length * currPiece[0].length];
						for (int i = 0; i < currPiece.length; i++) {
							for (int j = 0; j < currPiece[0].length; j++) {
								pPiece[n++] = currPiece[i][j];
							}
						}
						long startTime = System.nanoTime();
						ret = placePiece(currPiece.length, pPiece, timeLeft / 1_000_000);
						timeLeft -= System.nanoTime() - startTime;
					} catch (Exception e) {
						addFatalError("Failed to get result from placePiece.");
						return -1;
					}
					if (timeLeft < 0) {
						addFatalError("PlacePiece: Time limit exceeded.");
						return -1;
					}
					if (ret == null) {
						addFatalError("PlacePiece: Received null value.");
						return -1;
					}
					if (ret.equalsIgnoreCase("D")) {
						if (!discardPiece()) {
							addFatalError("PlacePiece: you already used all discards available.");
							return -1;
						}
						if (debug) System.out.println("Piece discarded.");
					} else {
						String[] s = ret.split(" ");
						if (s.length != 2) {
							addFatalError("PlacePiece should return two values separated by one space, or D for discard.");
							return -1;
						}
						int rotation = 0;
						try {
							rotation = Integer.parseInt(s[0]);
						} catch (NumberFormatException nfe) {
							addFatalError("PlacePiece: rotation should be an integer number.");
							return -1;
						}
						if (rotation < 0 || rotation > 3) {
							addFatalError("PlacePiece: rotation should be between 0 and 3 inclusive.");
							return -1;
						}
						int xPiece = 0;
						try {
							xPiece = Integer.parseInt(s[1]);
						} catch (NumberFormatException nfe) {
							addFatalError("PlacePiece: xPiece should be an integer number.");
							return -1;
						}
						int yPiece = canPlacePiece(xPiece, rotation);
						if (yPiece < 0) {
							if (debug) System.out.println("Piece can't be placed at xPiece=" + xPiece + " and rotation=" + rotation);
							currPiece = null;
							break;
						}
						if (vis) v.animMove(xPiece, yPiece, rotation);
						doPlacePiece(xPiece, yPiece, rotation);
						if (debug) System.out.println("Piece placed at xPiece=" + xPiece + ", yPiece=" + yPiece + " and rotation=" + rotation);
					}
					nextPiece();
					if (vis && (delay > 0 || anim > 0)) {
						v.reset();
						v.fullRepaint();
					}
					if (vis) delay(delay);
				}
			} else {
				//Manual mode
				nextPiece();
				v.preview();
				if (vis) v.fullRepaint();
				while (currPiece != null) {
					try {
						Thread.sleep(50);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
			if (vis) v.fullRepaint();
			return score;
		} catch (Exception e) {
			addFatalError("An exception occurred while trying to process your program's results.");
			e.printStackTrace();
			return -1;
		}
	}

	private void nextPiece() {
		currPieceIdx = rnd.nextInt(pieces.length);
		int[][] basePiece = pieces[currPieceIdx];
		currPiece = new int[basePiece.length][basePiece[0].length];
		int xBase = rnd.nextInt(imageWidth);
		int yBase = rnd.nextInt(imageHeight);
		for (int i = 0; i < basePiece.length; i++) {
			for (int j = 0; j < basePiece[0].length; j++) {
				if (basePiece[i][j] == 0) {
					currPiece[i][j] = -1;
				} else {
					int xp = random(Math.max(0, xBase - blockSize), Math.min(imageWidth - 1, xBase + blockSize));
					int yp = random(Math.max(0, yBase - blockSize), Math.min(imageHeight - 1, yBase + blockSize));
					currPiece[i][j] = pixels[yp * imageWidth + xp];
				}
			}
		}
	}

	private int canPlacePiece(int xPiece, int rot) {
		int[][] piece = getRotated(currPiece, rot);
		int ret = -1000;
		if (xPiece < 0 || xPiece + piece[0].length > boardWidth) return ret;
		OUT: for (int y = 1 - piece.length; y < boardHeight; y++) {
			if (y + piece.length > boardHeight) break;
			for (int r = 0; r < piece.length; r++) {
				if (y + r < 0) continue;
				for (int c = 0; c < piece[0].length; c++) {
					int color = piece[r][c];
					if (color == -1) continue;
					if (boardColors[y + r][xPiece + c] != -1) break OUT;
				}
			}
			ret = y;
		}
		return ret;
	}

	private void doPlacePiece(int xPiece, int yPiece, int rot) {
		int[][] piece = getRotated(currPiece, rot);
		for (int r = 0; r < piece.length; r++) {
			for (int c = 0; c < piece[0].length; c++) {
				int color = piece[r][c];
				if (color != -1) {
					boardColors[yPiece + r][xPiece + c] = color;
					boardPieces[yPiece + r][xPiece + c] = currPieceIdx;
					filled++;
					double err = 0;
					for (int i = 0; i < blockSize; i++) {
						int py = (r + yPiece) * blockSize + i;
						for (int j = 0; j < blockSize; j++) {
							int px = (xPiece + c) * blockSize + j;
							int pixel = pixels[py * imageWidth + px];
							err += getDiff(color, pixel) / 765.0;
							if (vis) errorImage.setRGB(px, py, getRGBDiff(color, pixel));
						}
					}
					err /= blockSize * blockSize;
					score += Math.pow(1 - err, 2);
				}
			}
		}
	}

	private boolean discardPiece() {
		if (discarded == maxDiscard) return false;
		discarded++;
		return true;
	}

	private static int[][] getRotated(int[][] piece, int rot) {
		for (int i = 0; i < rot; i++) {
			piece = getRotated(piece);
		}
		return piece;
	}

	private static int[][] getRotated(int[][] piece) {
		int r = piece[0].length;
		int c = piece.length;
		int[][] rotated = new int[r][c];
		for (int i = 0; i < piece.length; i++) {
			for (int j = 0; j < piece[0].length; j++) {
				rotated[j][c - 1 - i] = piece[i][j];
			}
		}
		return rotated;
	}

	private int random(int min, int max) {
		return rnd.nextInt(max - min + 1) + min;
	}

	// ------------- visualization part ------------
	private JFrame jf;
	private Vis v;
	private static String exec;
	private static boolean vis, debug, maximized, drawBorder, coloredPieces;
	private static Process proc;
	private InputStream is;
	private OutputStream os;
	private BufferedReader br;
	private static int anim, delay, paused;

	String init(int pImageHeight, int pBlockSize, int pDiscard, int[] pImage) throws IOException {
		StringBuilder sb = new StringBuilder();
		sb.append(pImageHeight).append('\n');
		sb.append(pBlockSize).append('\n');
		sb.append(pDiscard).append('\n');
		sb.append(pImage.length).append('\n');
		for (int i = 0; i < pImage.length; i++) {
			sb.append(pImage[i]).append('\n');
		}
		os.write(sb.toString().getBytes());
		os.flush();
		String ret = br.readLine();
		return ret;
	}

	String placePiece(int pPieceHeight, int[] pPiece, long pTimeLeft) throws IOException {
		StringBuilder sb = new StringBuilder();
		sb.append(pPieceHeight).append('\n');
		sb.append(pPiece.length).append('\n');
		for (int i = 0; i < pPiece.length; i++) {
			sb.append(pPiece[i]).append('\n');
		}
		sb.append(pTimeLeft).append('\n');
		os.write(sb.toString().getBytes());
		os.flush();
		String ret = br.readLine();
		return ret;
	}

	public class Vis extends JPanel {
		private static final long serialVersionUID = 2919900099978500636L;
		private static final int border = 8, sh = 18;
		private final Font fontBold = new Font("SansSerif", Font.BOLD, 15);
		private final Font fontPlain = new Font("SansSerif", Font.PLAIN, 15);
		private final Color grid1 = new Color(250, 250, 250, 150);
		private final Color grid2 = new Color(140, 140, 140, 150);
		private final Color grid3 = new Color(250, 250, 0);
		private final Color grid4 = new Color(140, 140, 0);
		private final Color fillColor = new Color(210, 210, 240);
		private BufferedImage paint1, paint2;
		private int xPiece, yPiece = 0, rot, yPreview = -1;
		private final AtomicBoolean waiting = new AtomicBoolean();
		private final DecimalFormat df = new DecimalFormat("0.000", DecimalFormatSymbols.getInstance(Locale.US));
		private final int[] pieceColors = new int[] {0x00AAAA,0xAA5500,0x00AA00,0x00FFFF,0xFFFF00,0xAA00FF,0xFF0000,0x00FF00,0x0000FF,0xFFAA00};

		public void init() {
			int pw = imageWidth + imageWidth / 3 + 3 * border;
			int ph = imageHeight + 5 * blockSize + 2 * border;
			paint1 = new BufferedImage(pw, ph, BufferedImage.TYPE_INT_RGB);
			paint2 = new BufferedImage(pw, ph, BufferedImage.TYPE_INT_RGB);
			setPreferredSize(new Dimension(pw, ph));
			fullRepaint();
		}

		private void fullRepaint() {
			synchronized (paint1) {
				Graphics2D g2 = paint1.createGraphics();
				g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
				g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
				g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);

				g2.setColor(Color.lightGray);
				g2.fillRect(0, 0, paint1.getWidth(), paint1.getHeight());

				fill(g2, imageWidth + 2 * border, 2 * border + 3 * sh, imageWidth / 3, sh, filled / (double) (boardHeight * boardWidth));
				fill(g2, imageWidth + 2 * border, 3 * border + 5 * sh, imageWidth / 3, sh, discarded / (double) maxDiscard);

				g2.setColor(Color.black);
				g2.setFont(fontBold);
				ds(g2, "Score", imageWidth + 2 * border, border, imageWidth / 3, sh, 0);
				ds(g2, "Filled", imageWidth + 2 * border, 2 * border + 2 * sh, imageWidth / 3, sh, 0);
				ds(g2, "Discarded", imageWidth + 2 * border, 3 * border + 4 * sh, imageWidth / 3, sh, 0);
				g2.setFont(fontPlain);
				ds(g2, df.format(score), imageWidth + 2 * border, border + 1 * sh, imageWidth / 3, sh, 0);
				ds(g2, filled + " / " + boardHeight * boardWidth, imageWidth + 2 * border, 2 * border + 3 * sh, imageWidth / 3, sh, 0);
				ds(g2, discarded + " / " + maxDiscard, imageWidth + 2 * border, 3 * border + 5 * sh, imageWidth / 3, sh, 0);

				paintBoard(g2, border, border, imageWidth, imageHeight + 5 * blockSize);
				paintImage(image, g2, imageWidth + 2 * border, imageHeight + 5 * blockSize - 2 * imageHeight / 3, imageWidth / 3, imageHeight / 3);
				paintImage(errorImage, g2, imageWidth + 2 * border, imageHeight + 5 * blockSize + border - imageHeight / 3, imageWidth / 3, imageHeight / 3);
				g2.dispose();
			}
			repaint();
		}

		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			Graphics2D g2 = paint2.createGraphics();
			g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			synchronized (paint1) {
				g2.drawImage(paint1, 0, 0, null);
			}
			if (currPiece != null) {
				int im = yPreview < 0 ? 0 : 1;
				int[][] piece = getRotated(currPiece, rot);
				for (int r = 0; r < piece.length; r++) {
					for (int c = 0; c < piece[0].length; c++) {
						int color = piece[r][c];
						if (color == -1) continue;
						if (coloredPieces) color = pieceColors[currPieceIdx];
						int xr = border + ((c + xPiece) * blockSize);
						for (int i = 0; i <= im; i++) {
							int yr = border + ((r + (i == 0 ? yPiece : yPreview + 5)) * blockSize);
							if (i == 0) {
								g2.setColor(new Color(color));
								g2.fillRect(xr, yr, blockSize, blockSize);
							}
							g2.setColor(i == 0 ? grid1 : grid3);
							g2.drawLine(xr, yr, xr, yr + blockSize - 1);
							g2.drawLine(xr, yr, xr + blockSize - 1, yr);
							g2.setColor(i == 0 ? grid2 : grid4);
							g2.drawLine(xr + blockSize - 1, yr, xr + blockSize - 1, yr + blockSize - 1);
							g2.drawLine(xr, yr + blockSize - 1, xr + blockSize - 1, yr + blockSize - 1);
						}
					}
				}
				g2.dispose();
			}
			g2 = (Graphics2D) g;
			g2.setColor(Color.lightGray);
			g2.fillRect(0, 0, getWidth(), getHeight());
			g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
			double zoomFactor = Math.min(((double) getWidth()) / paint2.getWidth(), ((double) getHeight()) / paint2.getHeight());
			int w = (int) (paint2.getWidth() * zoomFactor);
			int h = (int) (paint2.getHeight() * zoomFactor);
			g2.drawImage(paint2, (getWidth() - w) / 2, (getHeight() - h) / 2, w, h, null);
		}

		private void paintImage(BufferedImage img, Graphics2D g, int x, int y, int w, int h) {
			g.drawImage(img, x, y, w, h, null);
			g.setColor(Color.gray);
			g.drawRect(x, y, w, h);
		}

		private void paintBoard(Graphics2D g, int x, int y, int w, int h) {
			int off = blockSize * 5;
			if (coloredPieces) {
				g.setColor(Color.black);
				g.fillRect(x, y + off, w, h - off);
			} else {
				g.drawImage(image, x, y + off, w, h - off, null);
			}
			g.setColor(Color.gray);
			g.drawRect(x - 1, y + off - 1, w + 1, h - off + 1);
			for (int r = 0; r < boardHeight; r++) {
				for (int c = 0; c < boardWidth; c++) {
					int color = boardColors[r][c];
					if (color == -1) continue;
					if (coloredPieces) color = pieceColors[boardPieces[r][c]];
					int xr = x + c * blockSize;
					int yr = y + off + r * blockSize;
					g.setColor(new Color(color));
					g.fillRect(xr, yr, blockSize, blockSize);
					if (drawBorder) {
						g.setColor(grid1);
						g.drawLine(xr, yr, xr, yr + blockSize - 1);
						g.drawLine(xr, yr, xr + blockSize - 1, yr);
						g.setColor(grid2);
						g.drawLine(xr + blockSize - 1, yr, xr + blockSize - 1, yr + blockSize - 1);
						g.drawLine(xr, yr + blockSize - 1, xr + blockSize - 1, yr + blockSize - 1);
					}
				}
			}
		}

		private void ds(Graphics2D g, String s, int x, int y, int w, int h, int align) {
			FontMetrics metrics = g.getFontMetrics();
			Rectangle2D rect = metrics.getStringBounds(s, g);
			int th = (int) (rect.getHeight());
			int tw = (int) (rect.getWidth());
			if (align == 0) x += (w - tw) / 2;
			else if (align == 1) x += w - tw;
			y = y + (h - th) / 2 + metrics.getAscent();
			g.drawString(s, x, y);
		}

		private void fill(Graphics2D g, int x, int y, int w, int h, double pct) {
			g.setColor(fillColor);
			g.fillRect(x, y, (int) Math.round(w * pct), h);
			g.setColor(Color.gray);
			g.drawRect(x, y, w, h);
		}

		private void preview() {
			yPreview = currPiece == null ? -1 : canPlacePiece(xPiece, rot);
		}

		private void checkX() {
			while (xPiece > boardWidth - (rot % 2 == 0 ? currPiece[0].length : currPiece.length)) {
				xPiece--;
			}
		}

		private void animMove(int xt, int yt, int rott) {
			if (anim <= 0) return;
			int d = anim / Math.max(boardHeight, boardWidth);
			rot = rott;
			checkX();
			repaint();
			delay(delay);
			while (xPiece != xt) {
				if (xPiece > xt) xPiece--;
				else xPiece++;
				repaint();
				delay(d);
			}
			for (int i = -4; i < yt; i++) {
				yPiece = i + 5;
				repaint();
				delay(d);
			}
		}

		private void reset() {
			yPiece = 0;
			rot = 0;
		}

		public Vis() {
			setFocusable(true);
			jf.addWindowListener(new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					if (proc != null) try {
						proc.destroy();
					} catch (Exception ex) {
						ex.printStackTrace();
					}
					System.exit(0);
				}
			});
			addKeyListener(new KeyAdapter() {
				public void keyTyped(KeyEvent e) {
					if (e.getKeyChar() == 'b') {
						drawBorder = !drawBorder;
						fullRepaint();
					}
					if (e.getKeyChar() == 'c') {
						coloredPieces = !coloredPieces;
						fullRepaint();
					}
					if (e.getKeyChar() == ' ') {
						if (paused == 0) paused = 1;
						else paused = 0;
					}
					if (e.getKeyChar() == 'n') {
						if (paused == 1) paused = 2;
					}
					if (currPiece == null || waiting.get() || exec != null) return;
					if (e.getKeyChar() == 'd') {
						if (discardPiece()) {
							rot = 0;
							nextPiece();
							checkX();
							preview();
							repaint();
						}
					}
				}

				public void keyPressed(KeyEvent e) {
					if (waiting.get()) {
						e.consume();
						return;
					}
					if (currPiece == null || exec != null) return;
					if (e.getKeyCode() == KeyEvent.VK_LEFT) {
						if (xPiece > 0) xPiece--;
						preview();
						repaint();
					}
					if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
						xPiece++;
						checkX();
						preview();
						repaint();
					}
					if (e.getKeyCode() == KeyEvent.VK_UP) {
						if (++rot == 4) rot = 0;
						checkX();
						preview();
						repaint();
					}
					if (e.getKeyCode() == KeyEvent.VK_DOWN) {
						int y = canPlacePiece(xPiece, rot);
						if (y >= 0) {
							Thread tp = new Thread() {
								public void run() {
									waiting.set(true);
									if (anim > 0) {
										int d = anim / boardHeight;
										for (int i = -4; i < y; i++) {
											yPiece = i + 5;
											repaint();
											delay(d);
										}
									}
									doPlacePiece(xPiece, y, rot);
									yPiece = 0;
									rot = 0;
									nextPiece();
									checkX();
									preview();
									fullRepaint();
									waiting.set(false);
								}
							};
							tp.start();
						}
					}
				}
			});
		}
	}

	private void delay(long t) {
		try {
			if (t > 0) Thread.sleep(t);
			while (paused == 1) {
				Thread.sleep(10);
			}
			if (paused == 2) paused = 1;
		} catch (InterruptedException e) {
		}
	}

	public ImageFromBlocksVis(String seed) {
		try {
			if (vis) {
				jf = new JFrame();
				jf.setTitle("MM 110 - ImageFromBlocks - Seed " + seed);
				v = new Vis();
				jf.setContentPane(v);
			}
			if (exec != null) {
				try {
					Runtime rt = Runtime.getRuntime();
					proc = rt.exec(exec);
					os = proc.getOutputStream();
					is = proc.getInputStream();
					br = new BufferedReader(new InputStreamReader(is));
					new ErrorReader(proc.getErrorStream()).start();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
			System.out.println("Score = " + runTest(seed));
			if (proc != null) {
				try {
					proc.destroy();
				} catch (Exception e) {
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@SuppressWarnings("unused")
	public static void main(String[] args) {
		String seed = "1";
		vis = true;
		drawBorder = true;
		anim = -1;
		for (int i = 0; i < args.length; i++) {
			if (args[i].equalsIgnoreCase("-seed")) seed = args[++i];
			if (args[i].equalsIgnoreCase("-exec")) exec = args[++i];
			if (args[i].equalsIgnoreCase("-anim")) anim = Integer.parseInt(args[++i]);
			if (args[i].equalsIgnoreCase("-delay")) delay = Integer.parseInt(args[++i]);
			if (args[i].equalsIgnoreCase("-novis")) vis = false;
			if (args[i].equalsIgnoreCase("-noborder")) drawBorder = false;
			if (args[i].equalsIgnoreCase("-colored")) coloredPieces = true;
			if (args[i].equalsIgnoreCase("-time")) timeLimit = Integer.parseInt(args[++i]);
			if (args[i].equalsIgnoreCase("-images")) imagesFolder = args[++i];
			if (args[i].equalsIgnoreCase("-debug")) debug = true;
			if (args[i].equalsIgnoreCase("-paused")) paused = 1;
			if (args[i].equalsIgnoreCase("-max")) maximized = true;
		}
		if (anim == -1 && exec == null) anim = 300;
		if (exec == null && !vis) vis = true;
		if (!vis) System.setProperty("java.awt.headless", "true");

		new ImageFromBlocksVis(seed);
	}

	void addFatalError(String message) {
		System.out.println(message);
	}
}

class ErrorReader extends Thread {
	InputStream error;

	public ErrorReader(InputStream is) {
		error = is;
	}

	public void run() {
		try {
			byte[] ch = new byte[50000];
			int read;
			while ((read = error.read(ch)) > 0) {
				String s = new String(ch, 0, read);
				System.out.print(s);
				System.out.flush();
			}
		} catch (Exception e) {
		}
	}
}