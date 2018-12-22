import java.io.*;
import java.util.*;


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
        for (int i = 0; i < 26; ++i) { a[i] = 0; }
        for (int i = 0; i < MessageChecksum.n; ++i) {
            char c = (char)(Sender.getChecksum(i, 1) + (int)'A');
            if (!maxchars[i].equals(String.valueOf(c))) { a[(int)c - (int)'A'] += 1; }
            maxchars[i] = String.valueOf(c);
        }
        for (int i = 0; i < 26; ++i) {
            System.err.println("<cerr>" + String.valueOf(a[i]) + "</cerr>");
        }
    }
    public static void Test3 (String target) {
        int cnt = 0;
        for (int i = 0; i < target.length(); ++i) {
            char c = (char)(Sender.getChecksum(i, 1) + (int)'A');
            if (!String.valueOf(target.charAt(i)).equals(String.valueOf(c))) { cnt += 1; }
        }
        System.err.println("<cerr> er " + String.valueOf((double)cnt / n) + "</cerr>");
    }
    public static void Test4 (String target) {
        int cnt = 0;
        for (int i = 0; i < MessageChecksum.n; ++i) {
            if (String.valueOf(target.charAt(i)).equals(maxchars[i])) { cnt += 1; }
        }
        System.err.println("<cerr> eqcnt " + cnt + "</cerr>");
    }
    public static int checkSum (String[] s, int p, int n) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            r += (int)s[p+i].charAt(0)-(int)'A';
        }
        return r;
    }
    
    public static int checkSum (String s, int p, int n) {
        int r = 0;
        for (int i = 0; i < n; ++i) {
            r += (int)s.charAt(p+i)-(int)'A';
        }
        return r;
    }
    
    public static void Init () {
        String r = "";
        for (int i = 0; i < n; ++i) {
            String a = "";
            // a += (n - message.length() == 1 && i < n/2? String.valueOf(message.charAt(i)) : "");
            String t = "";
            while (t.equals("")) {
                a += Sender.getMessage(i, 1);
                t = maxChar(a, 1);
            }
            getm[i] = a;
            maxchars[i] = t;
            r += a;
        }
    }
    
    
    public static void Init2 (String rmessage) {
        String r = "";
        for (int i = 0; i < n; ++i) {
            String a = getm[i];
            if (rs > 0.25) { a += String.valueOf(rmessage.charAt(i)); }
            String t = "";
            while (t.equals("")) {
                a += Sender.getMessage(i, 1);
                t = maxChar(a, 3);
            }
            getm[i] = a;
            maxchars[i] = t;
            r += a;
        }
    }
    
    
    
    public static void InitB () {
        String r = "";
        for (int i = 0; i < n; ++i) {
            if (i % 8 == 0 && false) {//
                CompletedChar(i);
            } else {
                String a = (n - message.length() < 0 ? String.valueOf(message.charAt(i)) : "");
                // a += (n - message.length() == 1 && i < n/2? String.valueOf(message.charAt(i)) : "");
                String t = "";
                while (t.equals("")) {
                    a += Sender.getMessage(i, 1);
                    String gt = "";
                    for (int j = a.length() > 5 ? a.length() - 5 : 0; j < a.length(); ++j) {
                        gt += String.valueOf(a.charAt(j));
                    }
                    a = gt;
                    t = maxChar(a, 1);
                }
                getm[i] = a;
                maxchars[i] = t;
            }
        }
    }
    
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
    
    public static String CompletedMessage () {
        String r = "";
        for (int i = 0; i < MessageChecksum.n; ++i) {
            char c = (char)(Sender.getChecksum(i, 1) + (int)'A');
            r += String.valueOf(c);
        }
        return r;
    }
    
    public static int Score (int[] spaces, String[] mes) {
        int ret = 0;
        int p = 0;
        int sp = spaces[0];
        for (int i = 0; i < mes.length; ++i) {
            if (sp == i) {
                p += 1;
                if (p < spaces.length) { sp = spaces[p]; }
            }
            if (mes[i].equals(maxchars[i+p])) { ret += 1; }
        }
        return ret;
    }
    
    public static double rs = 1;
    public static String InsertSpaceInitialMessage () {
        String ret = "";
        int len = MessageChecksum.message.length();
        int dlen = MessageChecksum.n - MessageChecksum.message.length();
        // String[] tmp = new String[MessageChecksum.n];
        // for (int i = 0; i < MessageChecksum.n; ++i) { tmp[i] = ""; }
        String[] mes = new String[len];
        for (int i = 0; i < message.length(); ++i) {
            mes[i] = String.valueOf(message.charAt(i));
        }
        
        if (dlen == 0) { return MessageChecksum.message; }
        int[] spaces = new int[dlen];
        for (int i = 0; i < dlen; ++i) { spaces[i] = -1; }
        int p = 0;
        for (int i = 0; i < len; ++i) {
            
            int acnt = 0;
            int bcnt = 0;
            int ccnt = 0;
            int dcnt = 0;
            int checklen = 32;
            int bstart = -1;
            int cstart = -1;
            int dstart = -1;
            for (int j = 0; j < checklen; ++j) {
                if (i + j >= len) { break; }
                if (mes[i + j].equals(maxchars[i + j + p])) { acnt += 1; }
            }
            for (int j = 0; j < checklen; ++j) {
                if (i + j >= len - 1) { break; }
                if (mes[i + j].equals(maxchars[i + j + p + 1])) {
                    bcnt += 1;
                    if (bstart == -1) { bstart = j; }
                }
            }
            
            for (int j = 0; j < checklen; ++j) {
                if (i + j >= len - 2) { break; }
                if (mes[i + j].equals(maxchars[i + j + p + 2])) {
                    ccnt += 1;
                    if (cstart == -1) { cstart = j; }
                }
            }
            for (int j = 0; j < checklen; ++j) {
                if (i + j >= len - 3) { break; }
                if (mes[i + j].equals(maxchars[i + j + p + 3])) {
                    dcnt += 1;
                    if (dstart == -1) { dstart = j; }
                }
            }
            if (dcnt >= acnt && dcnt >= bcnt && dcnt >= ccnt) {
                spaces[p] = i + dstart;
                p += 1;
                i += dstart;
            } else if (ccnt >= acnt && ccnt >= bcnt) {
                spaces[p] = i + cstart;
                p += 1;
                i += cstart;
            } else if (bcnt >= acnt) {
                spaces[p] = i + bstart;
                p += 1;
                i += bstart;
            }
            // if (bcnt > acnt) {
            //     spaces[p] = i + bstart;
            //     p += 1;
            //     i += bstart;
            // }
            if (p == dlen) { break; }
        }
        
        
        for (int i = 0; i < dlen - p; ++i) {
            for (int j = len - 1; j >= 0 ; --j) {
                int b = 1;
                for (int k = 0; k < dlen; ++k) {
                    if (spaces[k] == j) { b = 0; }
                }
                if (b == 1) { spaces[p] = j; p += 1; }
                if (p == dlen) { break; }
            }
        }
        Arrays.sort(spaces);
        
        // System.err.println("<cerr>" + String.valueOf(Score(spaces, mes)) + "</cerr>");
        ///////////////////////
        int bestscore = Score(spaces, mes);
        
        int[] spaces2 = new int[dlen];
        for (int i = 0; i < dlen; ++i) { spaces2[i] = i * (len / dlen); }
        int bestscore2 = Score(spaces2, mes);
        if (bestscore2 > bestscore) {
            bestscore = bestscore2;
            spaces = spaces2;
        }
        
        
        
        for (int i = 0; i < 64; ++i) {
            for (int j = 0; j < dlen; ++j) {
                int vmax = len-1;
                if (j < dlen-1) { vmax = spaces[j+1] - 1; }
                if (spaces[j] + 5 >= vmax) { continue; }
                spaces[j] += 5;
                int tscore = Score(spaces, mes);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    spaces[j] -= 5;
                }
            }
            for (int j = 0; j < dlen; ++j) {
                int vmax = len-1;
                if (j < dlen-1) { vmax = spaces[j+1] - 1; }
                if (spaces[j] + 3 >= vmax) { continue; }
                spaces[j] += 3;
                int tscore = Score(spaces, mes);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    spaces[j] -= 3;
                }
            }
            for (int j = 0; j < dlen; ++j) {
                int vmax = len-1;
                if (j < dlen-1) { vmax = spaces[j+1] - 1; }
                if (spaces[j] + 1 >= vmax) { continue; }
                spaces[j] += 1;
                int tscore = Score(spaces, mes);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    spaces[j] -= 1;
                }
            }
            for (int j = 0; j < dlen; ++j) {
                int vmin = 0;
                if (j > 0) { vmin = spaces[j-1] + 1; }
                if (spaces[j] - 1 <= vmin) { continue; }
                spaces[j] -= 1;
                int tscore = Score(spaces, mes);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    spaces[j] += 1;
                }
            }
        }
        
        System.err.println("<cerr>" + String.valueOf(bestscore) + "</cerr>");
        System.err.println("<cerr>" + String.valueOf((double)bestscore / n) + "</cerr>");
        rs = (double)bestscore / n;
        
        
        /////////////////////////
        StringBuilder sb = new StringBuilder(MessageChecksum.message);
        for (int i = dlen-1; i >= 0; --i) {
            if (spaces[i] < 0) { continue; }
            sb.insert(spaces[i], " ");
        }
        
        
        ret = sb.toString();
        // System.err.println("<cerr>" + String.valueOf(dlen) + "</cerr>");
        
        // System.err.println("<cerr>raw " + MessageChecksum.message + "</cerr>");
        // System.err.println("<cerr>ret " + ret + "</cerr>");
        // System.err.println("<cerr>com " + CompletedMessage() + "</cerr>");
        // Test3(ret);
        return ret;
    }
    
    public String receiveMessage(int n, String message) {
        MessageChecksum.n = n;
        MessageChecksum.message = message;
        
        
        // MaxCharsAddMessage();
        
        int m = 16;
        if ((double)message.length()/n < 0.978*0) {
            for (int i = 0; i < n; ++i) { CompletedChar(i); }
        } else {
            Init();
            Init2(InsertSpaceInitialMessage());
            
            // Test3();
            for (int i = 0; i < n-n%m; i+=m) {
                int csm = Sender.getChecksum(i, m);
                completedsum.put(i, csm);
                if (checkSum(maxchars, i, m)%26 != csm) {
                    for (int j = 0; j < m; ++j) {
                        if (j % 3 == 0) { CompletedChar(i+j); }
                        if (checkSum(maxchars, i, m)%26 == csm) { break; }
                    }
                    if (checkSum(maxchars, i, m)%26 != csm) {
                        for (int j = 0; j < m; ++j) {
                            if (j % 2 == 0) { CompletedChar(i+j); }
                            if (checkSum(maxchars, i, m)%26 == csm) { break; }
                        }
                    }
                    if (checkSum(maxchars, i, m)%26 != csm) {
                        for (int j = 0; j < m; ++j) {
                            CompletedChar(i+j);
                            if (checkSum(maxchars, i, m)%26 == csm) { break; }
                        }
                    }
                }
            }
            
            int k = n%m;
            int p = n-k;
            if (k > 0) { completedsum.put(p, Sender.getChecksum(p, k)); }
            if (k > 0 && checkSum(maxchars, p, k)%26 == completedsum.get(p)) {
                
            } else {
                for (int i = 0; i < k; ++i) { CompletedChar(p+i); }
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
