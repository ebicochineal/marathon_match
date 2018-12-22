#include <iostream>
using namespace std; namespace Sender { int getChecksum(int start,int length) { cout << "?getChecksum" << endl; cout << start << endl; cout << length << endl; cout.flush(); int ret; cin >> ret; return ret; } string getMessage(int start,int length) { cout << "?getMessage" << endl; cout << start << endl; cout << length << endl; cout.flush(); string ret; cin >> ret;return ret; } }

///////////////////////////////////////////////

#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

class StopWatch {
public:
    int starts;
    int startm;
    struct timeb timebuffer;
    StopWatch () {
        ftime(&this->timebuffer);
        this->starts = this->timebuffer.time;
        this->startm = this->timebuffer.millitm;
    }
    
    inline int get_milli_time () {
        ftime(&this->timebuffer);
        return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
    }
};

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char *v) { return '"' + v + '"'; }
string in_v_to_str (const string v) { return '"' + v + '"'; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str();
}
template<class T, size_t N> string v_to_str (const array< array<T, N>, N > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class T> string v_to_str (const unordered_set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const unordered_map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class F, class S> string in_v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
template<class F, class S> string v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
string print () { return ""; }
template<typename F, typename... R> string print (const F &f, const R &...r) { stringstream ss; ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); } return ss.str(); }

template<class T>
void pdebug (T s) {
    stringstream ss;
    ss << "<cerr>" << print(s) << "</cerr>";
    cerr << ss.str();
}

namespace strlib {
    string replace (string str, string old_s, string new_s, int n = 0) {
        n = n < 1 ? str.size() : n;
        for (int i; (i = str.find(old_s)) > -1 && n; --n) { str.replace(i, old_s.size(), new_s); }
        return str;
    }
    int count (string str, string t) {
        int cnt = 0;
        for (int i = 0; (i = str.find(t, i)) > -1; i += t.size()) { ++cnt; }
        return cnt;
    }
    vector<string> split (string str, string sep = " ", int n = 0) {
        int prev = 0;
        vector<string> v;
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.find(sep, prev)) > -1 && n; --n) {
            v.push_back(str.substr(prev, i - prev));
            prev = i + sep.size();
        }
        v.push_back(str.substr(prev, str.size()));
        return v;
    }
    vector<string> split (string str, char sep = ' ', int n = 0) {
        string s = {sep};
        return split(str, s, n);
    }
    vector<string> rsplit (string str, string sep = " ", int n = 0) {
        int prev = str.size() - 1;
        vector<string> v;
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.rfind(sep, prev)) > -1 && n; --n) {
            v.insert(v.begin(), str.substr(i + sep.size(), prev - i + sep.size() - 1));
            prev = i - 1;
        }
        v.insert(v.begin(), str.substr(0, prev + 1));
        return v;
    }
    vector<string> rsplit (string str, char sep = ' ', int n = 0) {
        string s = {sep};
        return rsplit(str, s, n);
    }
    string slice (string str, int a, int b) {
        int s = a < 0 ? str.size() + a : a;
        int e = b < 0 ? str.size() + b : b;
        e = b == 0 ? str.size() : e;
        return str.substr(s, (s > e ? s : e) - s);
    }
}



class MessageChecksum {
public:
    string receiveMessage(int n, string s) {
        // int checksum = Sender::getChecksum(0, n);
        // string a = Sender::getMessage(0, n);
        
        
        string r;
        bool f = true;
        for (int i = 0; i < n; ++i) {
            
                string a = Sender::getMessage(i, 1);
                string b = Sender::getMessage(i, 1);
                string c = Sender::getMessage(i, 1);
                if (a == b && a == c) {
                    r += a;
                } else {
                    char c = Sender::getChecksum(i, 1) + 'A';
                    r += c;
                    f = false;
                }
            
        }
        
        return r;
    }
};

// -------8<------- end of solution submitted to the website -------8<-------

int main() {
    MessageChecksum mc;
    int length;
    string message;
    cin >> length;
    cin >> message;
    string ret = mc.receiveMessage(length,message);
    cout << ret << endl;
    cout.flush();
}
