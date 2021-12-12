#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#include <stdio.h>
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <time.h>
#include <sys/timeb.h>
#include <random>
using namespace std;

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char* v) { return "\"" + string(v) + "\""; }
string in_v_to_str (const string v) { return "\"" + v + "\""; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T, size_t N> string v_to_str (const array< array<T, N>, N >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const set<T>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const map<K, V>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class T> string v_to_str (const unordered_set<T>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const unordered_map<K, V>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class F, class S> string in_v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
template<class F, class S> string v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
string print () { return ""; }
template<typename F, typename... R> string print (const F& f, const R& ...r) { stringstream ss; ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); } return ss.str(); }

template<typename F, typename... R> void pdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>" << ss.str() << "</cerr>" << endl;
}

template<typename F, typename... R> void fdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerrfile>" << ss.str() << "</cerrfile>" << endl;
}

template<typename F, typename... R> void tdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>[time]" << ss.str() << "</cerr>" << endl;
}

namespace strlib {
    string replace (string str, string old_s, string new_s, int n = 0) {
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.find(old_s, i)) > -1 && n; --n) {
            str.replace(i, old_s.size(), new_s);
            i += new_s.size();
        }
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

struct e512pos {
public:
    int x;
    int y;
    e512pos () { this->x = 0; this->y = 0; }
    e512pos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    e512pos operator + (const e512pos& t) { return e512pos(this->x + t.x, this->y + t.y); }
    e512pos operator - (const e512pos& t) { return e512pos(this->x - t.x, this->y - t.y); }
    bool operator == (const e512pos& t) const { return this->x == t.x && this->y == t.y; }
};
namespace std {
    template <> class hash<e512pos> {
    public:
        size_t operator()(const e512pos& t) const{ return t.x<<16 | t.y; }
    };
}
ostream& operator << (ostream& os, const e512pos& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
};

class StopWatch {
public:
    int starts;
    int startm;
    int tstarts = 0;
    int tstartm = 0;
    struct timeb timebuffer;
    StopWatch () {
        ftime(&this->timebuffer);
        this->starts = this->timebuffer.time;
        this->startm = this->timebuffer.millitm;
    }
    inline void stop () {
        ftime(&this->timebuffer);
        this->tstarts = this->timebuffer.time;
        this->tstartm = this->timebuffer.millitm;
    }
    inline void resume () {
        ftime(&this->timebuffer);
        this->starts += this->timebuffer.time - this->tstarts;
        this->startm += this->timebuffer.millitm - this->tstartm;
    }
    inline int get_milli_time () {
        ftime(&this->timebuffer);
        return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
    }
};

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}


class MM {
public:
    StopWatch sw;
    int N, M, K, R;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->M >> this->K >> this->R;
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < this->K; ++j) {
                int t;
                cin >> t;
            }
        }
        // for (int i = 0; i < this->R; ++i) {
        //     int u, v;
        //     cin >> u >> v;
        // }
        
        
    }
    
    
    void output () {
        vector< vector<int> > task_dependency(this->N, vector<int>());
        
        for (int i = 0; i < this->R; ++i) {
            int u, v;
            cin >> u >> v;
            
            task_dependency[v - 1].emplace_back(u - 1);
            
        }
        
        
        vector<int> task_status(this->N, -1);
        int member_status = -1;
        
        string r0;
        getline(cin, r0);
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        while (true) {
            vector<int> out = {0};
            if (member_status < 0) {
                vector<int> tasklist;
                for (int i = 0; i < this->N; ++i) { tasklist.emplace_back(i); }
                
                // mt19937 mt(xrnd());
                // shuffle(tasklist.begin(), tasklist.end(), mt);
                
                
                for (auto&& task : tasklist) {
                    if (task_status[task] != -1) { continue; }
                    bool ok = true;
                    
                    for (auto&& necessary : task_dependency[task]) {
                        if (task_status[necessary] != 1) {
                            ok = false;
                            break;
                        }
                    }
                    
                    if (ok) {
                        task_status[task] = 0;
                        member_status = task;
                        out = {1, 1, task + 1};
                        break;
                    }
                }
            }
            string str_output;
            for (int i = 0; i < out.size(); ++i) {
                str_output += to_string(out[i]);
                if (i < out.size()-1) {
                    str_output += " ";
                }
            }
            cout << str_output << endl;
            cout.flush();
            
            string r;
            getline(cin, r);
            
            vector<int> temp;
            vector<string> sp = strlib::split(r, " ");
            for (auto&& i : sp) { temp.emplace_back(stoi(i)); }
            
            if (temp.size() == 1) {
                if (temp[0] == -1) { return; }
            } else {
                int task = member_status;
                task_status[task] = 1;
                member_status = -1;
            }
        }
        
    }
    void solve () {}
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    
    return 0;
}
