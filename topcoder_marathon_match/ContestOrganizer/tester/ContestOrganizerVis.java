// package com.topcoder.ReviewTest;

import java.io.*;
import java.security.*;
import java.util.*;

public class ContestOrganizerVis {

  // test parameters and constants
  int[] skill;
  int contests;
  int[][] winCount;
  
  // inputs
  int M;
  int N;
  String[] wins;

  // score computation

  // -----------------------------------------
  void generate(String seedStr) {
    try {
      // generate test case
      SecureRandom r1 = SecureRandom.getInstance("SHA1PRNG");
      long seed = Long.parseLong(seedStr);
      r1.setSeed(seed);

      N = r1.nextInt(151) + 50;
      M = r1.nextInt(16) + 5;
      
      if (seed == 1) {
        N = 10;
        M = 2;
      }

      if (seed == 2) {
        N = 20;
        M = 4;
      }
      
      skill = new int[N];
      for (int i = 0; i < N; i++) {
        skill[i] = r1.nextInt(901) + 100;
        addFatalError("<cerrfile>" + String.valueOf(skill[i]) + "</cerrfile>");
      }
      contests = r1.nextInt(48) + 3;
      winCount = new int[N][N];
      wins = new String[N];
      for (int i = 0; i < contests; i++) {
        double[] perf = new double[N];
        for (int j = 0; j < N; j++)
          perf[j] = r1.nextDouble() * skill[j];
        for (int j = 0; j < N; j++)
          for (int k = 0; k < N; k++)
            if (perf[j] > perf[k])
              winCount[j][k]++;              
      }
      for (int i = 0; i < N; i++) {
        wins[i] = "";
        for (int j = 0; j < N; j++) {
          if (j > 0)
            wins[i] += " ";
          wins[i] += "" + winCount[i][j];
        }
      }
      
      if (vis)
        printTest(seedStr);

    } catch (Exception e) {
      addFatalError("An exception occurred while generating test case.");
      e.printStackTrace();
    }
  }

  void printTest(String seed) {
    System.out.println("M = " + M);
    System.out.println("N = " + N);
    for (int i = 0; i < N; i++)
      System.out.println(wins[i]);
      // System.out.println(skill[i] + ": " + wins[i]);
  }

  // -----------------------------------------
  public double runTest(String seed) {
    try {
      generate(seed);
      String[] ret = new String[0];

      if (proc != null) {
        // call the solution
        try {
          ret = callSolution();
        } catch (Exception e) {
          addFatalError("Failed to get result from your solution.");
          return this.score = -1.0;
        }
      }

      // compute score
      if (ret.length != M) {
        addFatalError("Invalid number of teams returned (" + ret.length + "), expected " + M);
        return this.score = -1.0;        
      }
      
      boolean[] used = new boolean[N];
      double minStrength = 999999;
      double maxStrength = 0;
      for (int i = 0; i < M; i++) {
        String[] s = ret[i].split(" ");
        ArrayList<Integer> team = new ArrayList<Integer>();
        int cur;
        for (int j = 0; j < s.length; j++) {
          try {
            cur = Integer.parseInt(s[j]);
          } catch (Exception e) {
            addFatalError("Invalid return value found: " + s[j]);
            return this.score = -1.0;
          }
          if (cur < 0 || cur >= N) {
            addFatalError("Invalid value for competitor number: " + cur);
            return this.score = -1.0;
          }
          if (used[cur]) {
            addFatalError("Attempted to assign competitor " + cur + " more than once.");
            return this.score = -1.0;
          }
          used[cur] = true;
          team.add(skill[cur]);          
        }
        if (team.size() == 0) {
          addFatalError("Team " + i + " has no members.");
          return this.score = -1.0;
        }
        Collections.sort(team);
        double total = 0;
        for (int j = 0; j < team.size(); j++)
          total += (j + 1) * team.get(j);
        total *= 2;
        total /= team.size();
        total /= team.size() + 1;
        minStrength = Math.min(minStrength, total);
        maxStrength = Math.max(maxStrength, total);
      }
      
      for (int i = 0; i < N; i++)
        if (!used[i]) {
          addFatalError("Competitor " + i + " was never assigned to a team.");
          return this.score = -1.0;
        }
      
      double score = 1000 / (1 + maxStrength - minStrength);
      
      if (vis) {
        System.out.println("Weakest team = " + minStrength);
        System.out.println("Strongest team = " + maxStrength);
      }
      
      return this.score = score;
    } catch (Exception e) {
      addFatalError("An exception occurred while trying to get your program's results.");
      e.printStackTrace();
      return this.score = -1.0;
    }
  }


  // ------------- visualization part ------------
  static String exec;
  static boolean vis;
  static Process proc;
  InputStream is;
  OutputStream os;
  BufferedReader br;
  static int SZ;

  // -----------------------------------------
  private String[] callSolution() throws IOException, NumberFormatException {
    if (exec == null)
      return null;

    String s = M + "\n";
    os.write(s.getBytes());
    s = wins.length + "\n";
    os.write(s.getBytes());
    for (int i = 0; i < wins.length; i++) {
      s = wins[i] + "\n";
      os.write(s.getBytes());
    }
    os.flush();

    long startTime = System.currentTimeMillis();

    // and get the return value    
    String[] ret = new String[Integer.parseInt(br.readLine())];
    for (int i = 0; i < ret.length; i++)
      ret[i] = br.readLine();

    runTime += System.currentTimeMillis() - startTime;

    return ret;
  }


  // -----------------------------------------
  public ContestOrganizerVis(String seed) {
    try {
      if (exec != null) {
        try {
          Runtime rt = Runtime.getRuntime();
          proc = rt.exec(exec);
          os = proc.getOutputStream();
          is = proc.getInputStream();
          br = new BufferedReader(new InputStreamReader(is));
          output = new ErrorReader(proc.getErrorStream());
          output.start();
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
      System.out.println("Score = " + runTest(seed));
      if (proc != null)
        try {
          proc.destroy();
        } catch (Exception e) {
          e.printStackTrace();
        }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  public static long runTime = 0;
  public double score = -1.0;
  public static ErrorReader output;

  // -----------------------------------------
  public static void main(String[] args) {
    String seed = "1";
    vis = true;
    runTime = 0;
    for (int i = 0; i < args.length; i++) {
      if (args[i].equals("-seed"))
        seed = args[++i];
      if (args[i].equals("-exec"))
        exec = args[++i];
      if (args[i].equals("-novis"))
        vis = false;
    }

    ContestOrganizerVis f = new ContestOrganizerVis(seed);
    // return f.score;
  }

  // -----------------------------------------
  void addFatalError(String message) {
    System.out.println(message);
  }
}

class ErrorReader extends Thread {
  InputStream error;
  StringBuilder sb = new StringBuilder();

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
        sb.append(s);
        System.out.flush();
      }
    } catch (Exception e) {
    }
  }

  public String getOutput() {
    return sb.toString();
  }
}
