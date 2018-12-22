import java.io.*;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;


public class MessageChecksum {
    public static int n;
    public static String message;
    public static String[] getm = new String[10005];
    public static String[] maxchars = new String[10005];
    public static HashSet<Integer> completedchar = new HashSet<>();
    public static HashMap<Integer, Integer> completedsum = new HashMap<>();
    
    public static void Test (String target) {
        String r = "";
        for (int i = 0; i < MessageChecksum.n; ++i) {
            char c = (char)(Sender.getChecksum(i, 1) + (int)'A');
            r += String.valueOf(c);
        }
        if (!r.equals(target)) {
            System.err.println("<cerr>" + "err" + "</cerr>");
        }
    }
    public static void Test2 () {
        
        int[] a = new int[26];
        String r = "";
        for (int i = 0; i < 26; ++i) {
            a[i] = 0;
        }
        
        for (int i = 0; i < MessageChecksum.n; ++i) {
            char c = (char)(Sender.getChecksum(i, 1) + (int)'A');
            if (!maxchars[i].equals(String.valueOf(c))) {
                a[(int)c - (int)'A'] += 1;
            }
            maxchars[i] = String.valueOf(c);
        }
        for (int i = 0; i < 26; ++i) {
            System.err.println("<cerr>" + String.valueOf(a[i]) + "</cerr>");
        }
    }
    
    public static int checkSum (String[] s, int p, int n) {
        int r = 0;
        for (int i = 0; i < n; ++i) { r += (int)s[p+i].charAt(0)-(int)'A'; }
        return r%26;
    }
    public static int checkSum (String s, int p, int n) {
        int r = 0;
        for (int i = 0; i < n; ++i) { r += (int)s.charAt(p+i)-(int)'A'; }
        return r%26;
    }
    
    public static void Init () {
        for (int i = 0; i < n; ++i) {
            String a = (n - message.length() < 0 ? String.valueOf(message.charAt(i)) : "");
            a += (n - message.length() == 1 && i < n/2? String.valueOf(message.charAt(i)) : "");
            String t = "";
            while (t.equals("")) {
                a += Sender.getMessage(i, 1);
                String gt = "";
                for (int j = a.length() > 3 ? a.length() - 3 : 0; j < a.length(); ++j) {
                    gt += String.valueOf(a.charAt(j));
                }
                a = gt;
                t = maxChar(a, 2);
            }
            getm[i] = a;
            maxchars[i] = t;
            
        }
    }
    
    public static void CharsUpdate (int index, int count) {
        String t = "";
        while (t.equals("")) {
            getm[index] += Sender.getMessage(index, 1);
            t = maxChar(getm[index], count);
        }
        maxchars[index] = t;
    }
    
    // public static void InitB () {
    //     for (int i = 0; i < n; ++i) {
    //         if (i%4==0) {
    //             CompletedChar(i);
    //         }
    //     }
    // }
    
    // public static void FitString () {
    //     int len = MessageChecksum.message.length();
    //     String[] tmp = new String[MessageChecksum.n];
    //     String[] mes = new String[len];
    //     for (int i = 0; i < MessageChecksum.n; ++i) { tmp[i] = ""; }
    //     for (int i = 0; i < message.length(); ++i) {
    //         mes[i] = String.valueOf(message.charAt(i));
    //     }
    // }
    
    
    public static String maxChar (String s, int m) {
        if (s.length() < m) { return ""; }
        int maxc = 0;
        char[] cs = s.toCharArray();
        char tc = 'A';
        for (char i : cs) {
            int t = 0;
            for (char j : cs) {
                if (i == j) { t += 1; }
            }
            if (t > maxc) {
                maxc = t;
                tc = i;
            }
        }
        return maxc >= m ? String.valueOf(tc) : "";
    }
    
    public static void CompletedChar (int index) {
        if (isCompleted(index)) { return; }
        char c = (char)(Sender.getChecksum(index, 1) + (int)'A');
        maxchars[index] = String.valueOf(c);
        MessageChecksum.completedchar.add(index);
    }
    public static boolean isCompleted (int index) {
        return MessageChecksum.completedchar.contains(index);
    }
    
    public static String retString () {
        String ret = "";
        for (int i = 0; i < MessageChecksum.n; ++i) { ret += MessageChecksum.maxchars[i]; }
        return ret;
    }
    
    
    public String receiveMessage(int n, String message) {
        MessageChecksum.n = n;
        MessageChecksum.message = message;
        
        
        // MaxCharsAddMessage();
        
        int m = 5;
        if ((double)message.length()/n < 0.978*0) {
            for (int i = 0; i < n; ++i) { CompletedChar(i); }
        } else {
            Init();
            for (int i = 0; i < n-n%m; i+=m) {
                int csm = Sender.getChecksum(i, m);
                completedsum.put(i, csm);
                if (checkSum(maxchars, i, m) != csm) {
                    for (int j = 0; j < m; ++j) {
                        if (checkSum(maxchars, i, m) == csm) { break; }
                        if (j % 3 == 0) { CompletedChar(i+j); }
                    }
                    for (int j = 0; j < m; ++j) {
                        if (checkSum(maxchars, i, m) == csm) { break; }
                        if (j % 2 == 0) { CompletedChar(i+j); }
                    }
                    for (int j = 0; j < m; ++j) {
                        if (checkSum(maxchars, i, m) == csm) { break; }
                        CompletedChar(i+j);
                    }
                    
                }
            }
            
            int k = n%m;
            int p = n-k;
            if (k > 0) { completedsum.put(p, Sender.getChecksum(p, k)); }
            
            for (int i = 0; i < k; ++i) {
                if (checkSum(maxchars, p, k) == completedsum.get(p)) { break; }
                if (i % 3 == 0) { CompletedChar(p+i); }
            }
            for (int i = 0; i < k; ++i) {
                if (checkSum(maxchars, p, k) == completedsum.get(p)) { break; }
                if (i % 2 == 0) { CompletedChar(p+i); }
            }
            for (int i = 0; i < k; ++i) {
                if (checkSum(maxchars, p, k) == completedsum.get(p)) { break; }
                CompletedChar(p+i);
            }
            
        }
        
        // System.err.println("<cerr>" + String.valueOf(n) + "</cerr>");
        // System.err.println("<cerr>" + String.valueOf(n - message.length()) + "</cerr>");
        
        // System.err.println("<cerr>" + String.valueOf((double)message.length()/ n) + "</cerr>");
        
        // Test(retString());
        
        return retString();
    }
    
    
    
    
    
    
    public static void main(String[] args) {
        try {
            MessageChecksum sol = new MessageChecksum();      
            int length = Integer.parseInt(BR.readLine());
            String message = BR.readLine();
            System.out.println(sol.receiveMessage(length, message));
        } catch (Exception e) {}
    }
}





class BR {
    public static BufferedReader br;
    static {
        br = new BufferedReader(new InputStreamReader(System.in));
    }
    public static String readLine() {
        try { return br.readLine(); } catch (IOException e) { return ""; }
    }
}

class Sender {
    public static int getChecksum(int start, int length) {
        System.out.println("?getChecksum");
        System.out.println(start);
        System.out.println(length);
        System.out.flush();
        int ret = 0;
        try {
            ret = Integer.parseInt(BR.readLine());
        } catch (NumberFormatException e) {}
        return ret;
    }
    
    public static String getMessage(int start, int length) {
        System.out.println("?getMessage");
        System.out.println(start);
        System.out.println(length);
        System.out.flush();
        return BR.readLine();
    }
}
