#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
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
#include <bitset>
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
const int gmaxN = 1000;
const int gmaxM = 20;
const int gmaxK = 20;
const int gmaxR = 3000;
struct Members {
    int M = gmaxM;
    array< array<int, gmaxK>, gmaxM > skills;
    array<int, gmaxM> tasks;
    array<int, gmaxM> cnts;
    Members () {
        for (int y = 0; y < this->skills.size(); ++y) {
            for (int x = 0; x < this->skills[y].size(); ++x) {
                this->skills[y][x] = 0;
            }
        }
        for (int i = 0; i < this->M; ++i) {
            this->tasks[i] = -1;
            this->cnts[i] = 0;
        }
    }
    
    vector<int> free_menbers () {
        vector<int> r;
        for (int i = 0; i < this->M; ++i) {
            if (this->tasks[i] < 0) { r.emplace_back(i); }
        }
        return r;
    }
    
    void end_tasks (vector<int>& v) {
        for (auto&& m : v) { this->tasks[m] = -1; }
    }
};

struct Tasks {
    array< array<int, gmaxK>, gmaxN > skills;
    array< vector<int>, gmaxN > dependency;
    array< vector<int>, gmaxN > rdependency;
    array<int, gmaxN> status;
    Tasks () {
        for (int i = 0; i < gmaxN; ++i) { this->status[i] = 0; }
    }
    
    int sum_skill (int x) {
        int r = 0;
        for (auto&& i : this->skills[x]) { r += i; }
        return r;
    }
    
    int sum_rdependency (int x) {
        int r = 0;
        for (auto&& i : this->rdependency[x]) { if (this->status[i] == 0) { r += i; } }
        return r > 0;
    }
    
    vector<int> possibletasks () {
        vector<int> r;
        for (int i = 0; i < gmaxN; ++i) {
            if (this->possible(i)) { r.emplace_back(i); }
        }
        return r;
    }
    
    bool possible (int x) {
        if (this->status[x] > 0) { return false; }
        for (auto&& i : this->dependency[x]) {
            if (this->status[i] < 2) { return false; }
        }
        return true;
    }
};

class MM {
public:
    StopWatch sw;
    int N, M, K, R;
    Tasks tasks;
    Members members;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->M >> this->K >> this->R;
        
        array< array<int, gmaxK>, gmaxN > skills;
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < this->K; ++j) {
                cin >> this->tasks.skills[i][j];
            }
        }
        
        for (int i = 0; i < this->R; ++i) {
            int u, v;
            cin >> u >> v;
            this->tasks.dependency[v - 1].emplace_back(u - 1);
            this->tasks.rdependency[u - 1].emplace_back(v - 1);
        }
    }
    
    
    string v_to_str (vector< pair<int, int> >& v) {
        string r = to_string(v.size());
        for (int i = 0; i < v.size(); ++i) {
            r += " " + to_string(v[i].first) + " " + to_string(v[i].second);
        }
        return r;
    }
    
    
    void output () {
        
        for (int turn = 0; turn < 2000; ++turn) {
            
            vector< pair<int, int> > out;
            
            vector<int> fm = this->members.free_menbers();
            if (turn >= 300) {
                sort(fm.begin(), fm.end(), [&](const int& a, const int& b) { return this->members.cnts[a] > this->members.cnts[b]; });
            }
            
            for (auto&& i : fm) {
                vector<int> pt = this->tasks.possibletasks();
                if (pt.size() > 0) {
                    
                    if (turn >= 300) {
                        sort(pt.begin(), pt.end(), [&](const int& a, const int& b) { return this->tasks.sum_rdependency(a) > this->tasks.sum_rdependency(b); });
                    }
                    
                    out.emplace_back(i+1, pt[0]+1);
                    this->members.tasks[i] = pt[0];
                    this->tasks.status[pt[0]] = 1;
                }
            }
            cout << this->v_to_str(out) << endl;
            cout.flush();
            
            int r;
            cin >> r;
            if (r == -1) { return; }
            
            for (int i = 0; i < r; ++i) {
                int m;
                cin >> m;
                this->tasks.status[this->members.tasks[m-1]] = 2;
                this->members.tasks[m-1] = -1;
                if (turn < 300) {
                    this->members.cnts[m-1] += 2;
                } else {
                    this->members.cnts[m-1] += 1;
                }
                
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
