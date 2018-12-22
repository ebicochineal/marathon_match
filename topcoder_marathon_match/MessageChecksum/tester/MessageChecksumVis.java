import java.io.*;
import java.security.*;
import java.util.*;

public class MessageChecksumVis {

public String checkData(String s) { return ""; }

public String displayTestCase(String s) {
  long x = Long.parseLong(s);
  generateTestCase(x);  
  return "Message Length = " + message.length() + "\nError Rate = " + errorRate + "\n" +
    (x <= 3 ? "Actual message = " + message + "\nInitial received = " + getMessage(0, message.length()) : "");
}

LongTest lt;
String message;
String[] state = new String[27];
double errorRate;
int[] checkSum;
Random r = new Random();
long cost = 0;
boolean fail = false;
int timeLimit = 10000;

private void generateTestCase(long x) {
  try {
    r = SecureRandom.getInstance("SHA1PRNG");
  } catch (Exception e) { }
  r.setSeed(x);  
  int length = r.nextInt(9901) + 100;
  if (x == 1) length = 20;
  if (x == 2) length = 40;
  if (x == 3) length = 80;
  checkSum = new int[length + 1];
  message = "";
  for (int i = 0; i < length; i++) {
    int pick = r.nextInt(26);
    message += (char)('A' + pick);
    checkSum[i + 1] = (checkSum[i] + pick) % 26;
  }
  errorRate = 0.01 + r.nextDouble() * 0.49;
  if (x == 1) errorRate = 0.10;
  if (x == 2) errorRate = 0.12;
  if (x == 3) errorRate = 0.15;
  state[26] = "";
  for (int i = 0; i < 26; i++) state[i] = "" + (char)('A' + i);
  for (int i = 26; i > 0; i--) {
    int pick = r.nextInt(i + 1);
    if (pick == i) continue;
    String temp = state[pick];
    state[pick] = state[i];
    state[i] = temp;
  }  
}

public int getChecksum(int start, int length) {
  if ((start < 0) || (length < 1) || (length > message.length()) || (start + length > message.length())) {
    lt.addFatalError("Invalid parameters to getChecksum: " + start + ", " + length + "\n");
    fail = true;
    return -1;
  }
  cost += 5;
  return (26 + checkSum[start + length] - checkSum[start]) % 26;
}

public String getMessage(int start, int length) {
  if ((start < 0) || (length < 1) || (length > message.length()) || (start + length > message.length())) {
    lt.addFatalError("Invalid parameters to getMessage: " + start + ", " + length + "\n");
    fail = true;
    return "";
  }
  cost += length;
  String ret = "";
  for (int i = start; i < start + length; i++) {
    if (r.nextDouble() < errorRate)
      ret += state[(int)Math.sqrt(Math.floor(r.nextDouble() * 729))];
    else
      ret += message.charAt(i);
  }
  return ret;
}

public int editDistance(String s1, String s2) {
  int[][] dp = new int[s1.length() + 1][s2.length() + 1];
  for (int i = 0; i <= s1.length(); i++) {
    for (int j = 0; j <= s2.length(); j++) {
      if (i == 0) {
        dp[i][j] = j;
      } else if (j == 0) {
        dp[i][j] = i;
      } else if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + Math.min(Math.min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);        
      }
    }
  }  
  return dp[s1.length()][s2.length()];
}

public double runTest(LongTest longTest) {
  lt = longTest;
  generateTestCase(Long.parseLong(lt.getTest()));
  cost -= message.length();
  lt.setTimeLimit(timeLimit);
  lt.receiveMessage(message.length(), getMessage(0, message.length()));
  if (!lt.getStatus()) {
    lt.addFatalError("Error calling receiveMessage()\n");
    return -1;
  }
  timeLimit -= lt.getTime();
  if (timeLimit < 10) {
    lt.addFatalError("Time limit exceeded.\n");
    return -1;
  }
  String ret = lt.getResult_receiveMessage();
  if (!lt.getStatus()) {
    lt.addFatalError("Error getting result from receiveMessage()\n");
    return -1;
  }
  if (fail) return -1;
  int correct = editDistance(message, ret);
  lt.addFatalError("Total cost = " + cost + "\nEdit Distance = " + correct + "\n");
  return 1.0 * (cost + 100) * (correct + 1);
}

public double[] score(double[][] raw) {
  int coderCnt = raw.length;
  if (coderCnt == 0) return new double[0];
  int testCnt = raw[0].length;
  double[] res = new double[raw.length];
  for (int test = 0; test < testCnt; test++) {
    double min = Double.MAX_VALUE;
    for (int i = 0; i < coderCnt; i++) {
      if (raw[i][test] > 0) {
        min = Math.min(min, raw[i][test]);
      }
    }
    for (int i = 0; i < coderCnt; i++) {
      if (raw[i][test] > 0) {
        res[i] += min / raw[i][test];
      }
    }
  }
  for (int i = 0; i < res.length; i++) {
    res[i] /= testCnt;
    res[i] *= 1000000.0;
  }
  return res;
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
  public static MessageChecksumVis sol;
  
  static String exec;
  Process proc;
  boolean vis;
  InputStream is;
  OutputStream os;
  BufferedReader br;

  String seed = "";
  
  String result_receiveMessage = "";
  
  public LongTest(String[] args) {
    instance = this;
    sol = new MessageChecksumVis();
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
  
  public String getResult_receiveMessage() {
    return result_receiveMessage;
  }
  
  public void receiveMessage(int length, String message) {
    try {
      StringBuffer sb = new StringBuffer();
      sb.append(length).append("\n");
      sb.append(message).append("\n");
      os.write(sb.toString().getBytes());
      os.flush();
      String s;
      while ((s = br.readLine()).startsWith("?")) {
        String call = s;
        int st, len;
        try {
          st = Integer.parseInt(br.readLine());
          len = Integer.parseInt(br.readLine());
        } catch (NumberFormatException e) {
          return;
        }
        System.out.println(call + "(" + st + "," + len + ")");
        if (call.equals("?getChecksum")) {
          int checksum = sol.getChecksum(st, len);
          System.out.println(checksum);
          os.write((checksum + "\n").getBytes());
          os.flush();
        } else if (call.equals("?getMessage")) {
          String msg = sol.getMessage(st, len);
          System.out.println(msg);
          os.write((msg + "\n").getBytes());
          os.flush();
        } else {
          System.out.println("Call not found");
        }
      }
      result_receiveMessage = s;
      System.out.println("\n\n");
    } catch (IOException e) {}
  }
  
  public static void main(String[] args) {
    LongTest longTest = new LongTest(args);
  }
}

