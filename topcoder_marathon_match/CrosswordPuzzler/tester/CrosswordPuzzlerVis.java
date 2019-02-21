// To run:
//     javac CrosswordPuzzlerVis.java
//     java CrosswordPuzzler ....

import java.io.*;
import java.security.*;
import java.util.*;

public class CrosswordPuzzlerVis { 
  public static void main(String[] args) {
    LongTest longTest = new LongTest(args);
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

class LongTest {
  public static LongTest instance;
  public static CrosswordPuzzler sol;
  
  static String exec;
  Process proc;
  boolean vis;
  InputStream is;
  OutputStream os;
  BufferedReader br;

  String seed = "";
  
  String[] result_createPuzzle;
  
  public LongTest(String[] args) {
    instance = this;
    sol = new CrosswordPuzzler();
    seed = "1";
    for (int i = 0; i<args.length; i++) {  
      if (args[i].equals("-seed"))
        seed = args[++i];
      if (args[i].equals("-exec"))
        exec = args[++i];
      }
    try {
      if (exec != null) {
        try {
          Runtime rt = Runtime.getRuntime();
          proc = rt.exec(exec);
          os = proc.getOutputStream();
          is = proc.getInputStream();
          br = new BufferedReader(new InputStreamReader(is));
          new ErrorReader(proc.getErrorStream()).start();
          System.out.println("Score = " + sol.runTest(this));
        } catch (Exception e) { e.printStackTrace(); }
      }
      if (proc != null)
        try { proc.destroy(); }
        catch (Exception e) { e.printStackTrace(); }
    }
    catch (Exception e) { e.printStackTrace(); }
  }
  
  public String getTest() {
    return seed;
  }
  
  public void addFatalError(String s) {
    System.out.println(s);
  }
  
  public boolean getStatus() {
    return true;
  }
  
  public void setTimeLimit(int timeLimit) {
  }
  
  public int getTime() {
    return 0;
  }
  
  public String[] getResult_createPuzzle() {
    return result_createPuzzle;
  }
  
  public void createPuzzle(int width, int height, String[] dict) {
    try {
      StringBuffer sb = new StringBuffer();
      sb.append(width).append("\n");
      sb.append(height).append("\n");
      sb.append(dict.length).append("\n");
      for (int i = 0; i < dict.length; i++)
        sb.append(dict[i]).append("\n");
      os.write(sb.toString().getBytes());
      os.flush();
      String s;
      result_createPuzzle = new String[Integer.parseInt(br.readLine())];
      for (int i = 0; i < result_createPuzzle.length; i++)
        result_createPuzzle[i] = br.readLine();
      System.out.println("\n\n");
    } catch (IOException e) {}
  }
}

class CrosswordPuzzler {
  private int TIME_LIMIT = 10000;
  private int width, height;
  private HashSet<String> wordList = new HashSet<String>();
  private String[] words;
  private int[] scores = new int[] { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
  public String checkData(String s) { return ""; }
  public String displayTestCase(String s) {
	generateTestCase(s);
    String ret = "width = " + width + ", height = " + height + "\n";
    ret += "Dictionary Length = " + words.length + "\n";
    if (words.length < 20)
      for (int i = 0; i < words.length; i++) ret += words[i] + "\n";
    return ret;
  }
  private void generateTestCase(String s) {
    Long seed = Long.parseLong(s);
    if (seed == 1 || seed == 2) {
      if (seed == 1) {
        height = 3;
        width = 8;
      } else {
        height = 4;
        width = 7;
      }
      words = new String[] { "CLOCK", "BIO", "SWITCH", "CIS", "LOW", "CAT", "DOG", "TURTLE", "LION", "MULE", "ANT", "ELEPHANT", "POSSUM", "TURKEY" };
      wordList.addAll(Arrays.asList(words));
      return;
    }
    Random r = new Random(seed);
    try {
      r = SecureRandom.getInstance("SHA1PRNG");
      r.setSeed(seed);
    } catch (Exception e) {
    }
	width = r.nextInt(41) + 10;
	height = r.nextInt(41) + 10;
	int numWords = height * width / 4 + r.nextInt(1 + height * width - height * width / 4);
	String[] dist = new String[27];
	for (int i = 0; i < 27; i++) {
	  char c = 'A';
	  dist[i] = "";
	  while (c <= 'Z') {
	    if (r.nextDouble() < 0.6) {
		  dist[i] += c;
		} else {
		  c++;
		}
	  }
	}
    char lastChar;
    int[] lenDist = new int[]{ 1, 1, 2, 2, 3, 4 };
	while (wordList.size() < numWords) {
      int wordLen = lenDist[r.nextInt(6)] + lenDist[r.nextInt(6)] + lenDist[r.nextInt(6)];
      String thisWord = "" + (lastChar = dist[26].charAt(r.nextInt(dist[26].length())));
      while (thisWord.length() < wordLen)
        thisWord += lastChar = dist[lastChar - 'A'].charAt(r.nextInt(dist[lastChar - 'A'].length()));
      wordList.add(thisWord);
    }
    words = wordList.toArray(new String[0]);
  }
  public double runTest(LongTest lt) {
	generateTestCase(lt.getTest());
	lt.setTimeLimit(TIME_LIMIT);
	lt.createPuzzle(width, height, words);
	if (!lt.getStatus()) {
	  lt.addFatalError("Error calling createPuzzle.");
	  return -1;
	}
	TIME_LIMIT -= lt.getTime();
	if (TIME_LIMIT < 10) {
	  lt.addFatalError("Time limit exceeded.");
	  return -1;
	}
	String[] ret = lt.getResult_createPuzzle();
	if (!lt.getStatus()) {
	  lt.addFatalError("Error getting result from createPuzzle.");
	  return -1;
	}
    if (ret.length != height) {
      lt.addFatalError("Return value was expected to have " + height + " elements.");
	  return -1;
	}
	int score = 0;
	for (int i = 0; i < ret.length; i++) {
	  if (ret[i].length() != width) {
	    lt.addFatalError("Element " + i + " of return was expected to have " + width + " characters.");
		return -1;
	  }
      for (int j = 0; j < ret[i].length(); j++) {
        char c = ret[i].charAt(j);
        if (c == '-') {
          score--;
          continue;
        }
        if (c < 'A' || c > 'Z') {
  	      lt.addFatalError("Character " + j + " of element " + i + " of return is not a valid character.");
	  	  return -1;
        }
      }
    }
	for (int i = 0; i < ret.length; i++) {
      String[] s = ret[i].split("-");
      for (int j = 0; j < s.length; j++) {
        if (s[j].length() > 1) {
          if (wordList.contains(s[j])) {
            wordList.remove(s[j]);
            score += scores[s[j].length()];
          } else {
            lt.addFatalError("Horizontal word " + s[j] + " is not in the dictionary or is duplicated.");
            return - 1;
          }
        }
      }
    }
    for (int i = 0; i < ret[0].length(); i++) {
      String t = "";
      for (int k = 0; k < ret.length; k++) t += ret[k].charAt(i);
      String[] s = t.split("-");
      for (int j = 0; j < s.length; j++) {
        if (s[j].length() > 1) {
          if (wordList.contains(s[j])) {
            wordList.remove(s[j]);
            score += scores[s[j].length()];
          } else {
            lt.addFatalError("Vertical word " + s[j] + " is not in the dictionary or is duplicated.");
            return - 1;
          }
        }
      }
    }
        
	return Math.max(0, score);
  }
	
public double[] score(double[][] raw) {
  int coderCnt = raw.length;
  if (coderCnt == 0) return new double[0];
  int testCnt = raw[0].length;
  double[] res = new double[raw.length];
  for (int test = 0; test < testCnt; test++) {
    double best = -1e100;
    for (int i = 0; i < coderCnt; i++)
      if (raw[i][test] >= -0.5) {
        best = Math.max(best, raw[i][test]);
      }
    if (best <= 0.001) continue;
    for (int i=0; i < coderCnt; i++)
      if (raw[i][test] >= -0.5) {
        res[i] += raw[i][test] / best;
      }
  }
  for (int i=0; i < res.length; i++) {
    res[i] /= testCnt;
    res[i] *= 1000000.0;
  }
  return res;
}
}

