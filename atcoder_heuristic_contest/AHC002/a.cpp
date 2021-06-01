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
        size_t operator()(const e512pos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
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


inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}

class Ret {
public:
    vector<int> d;
    vector<bool> a = vector<bool>(2500, 0);
    e512pos p, lastp;
    int score = 0;
    // int nextscore = 0;
    Ret () {}
    Ret (e512pos p, int a, int score) {
        this->p = p;
        this->lastp = p;
        this->a[a] = true;
        this->score = score;
    }
};

class MM {
public:
    StopWatch sw;
    int sx, sy;
    vector< vector<int> > agrid = vector< vector<int> >(50, vector<int>(50, -1));
    vector< vector<int> > bgrid = vector< vector<int> >(50, vector<int>(50, -1));
    Ret bestret;
    MM () { this->sw = StopWatch(); }
    
    void input() {
        cin >> this->sy >> this->sx;
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                cin >> this->agrid[y][x];
            }
        }
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                cin >> this->bgrid[y][x];
                
            }
        }
        // gdebug(bgrid, 50, 50, 2);
        
    }
    
    void output() {
        static string ds[] = {"U", "R", "D", "L"};
        string out = "";
        for (auto&& i : this->bestret.d) {
            out += ds[i];
        }
        
        cout << out << endl;
    }
    
    void calc () {
        Ret ret(e512pos(this->sx, this->sy), this->agrid[this->sy][this->sx], this->bgrid[this->sy][this->sx]);
        
        for (int i = 0; i < 256; ++i) {
            if (this->sw.get_milli_time() > 1950) { break; }
            this->test(32 * i * 2);
        }
        
        
        cerr << print("Score =", this->bestret.score) << endl;
        cerr << print("Score =", this->calcscore(this->bestret)) << endl;
    }
    Ret test0 () {
        static int dx[4] = { 0, 1, 0, -1 };
        static int dy[4] = { -1, 0, 1, 0 };
        Ret ret(e512pos(this->sx, this->sy), this->agrid[this->sy][this->sx], this->bgrid[this->sy][this->sx]);
        
        while (true) {
            int bestd = -1;
            e512pos bestp(-1, -1);
            int score = 0;
            for (int d = 0; d < 4; ++d) {
                e512pos tp = ret.lastp;
                tp.x +=dx[d];
                tp.y +=dy[d];
                if (!insidexywh(tp.x, tp.y, 50, 50)) { continue; }
                if (ret.a[this->agrid[tp.y][tp.x]]) { continue; }
                
                if (this->bgrid[tp.y][tp.x] > score) {
                    bestp = tp;
                    bestd = d;
                    score = this->bgrid[tp.y][tp.x];
                }
            }
            
            
            if (bestd < 0) { break; }
            ret.a[this->agrid[bestp.y][bestp.x]] = true;
            ret.d.emplace_back(bestd);
            ret.score += this->bgrid[bestp.y][bestp.x];
            ret.lastp.x +=dx[bestd];
            ret.lastp.y +=dy[bestd];
        }
        
        return ret;
    }
    Ret test (int tbw) {
        static int dx[4] = { 0, 1, 0, -1 };
        static int dy[4] = { -1, 0, 1, 0 };
        Ret sret(e512pos(this->sx, this->sy), this->agrid[this->sy][this->sx], this->bgrid[this->sy][this->sx]);
        
        vector<Ret> rets;
        rets.emplace_back(sret);
        
        if (sret.score > this->bestret.score) { this->bestret = sret; }
        
        vector<Ret> trets;
        
        unordered_set<int> us;
        // while (rets.size()) {
        while (rets.size() && this->sw.get_milli_time() < 1950) {
            trets.clear();
            for (auto&& ret : rets) {
                for (int d = 0; d < 4; ++d) {
                    e512pos tp = ret.lastp;
                    tp.x +=dx[d];
                    tp.y +=dy[d];
                    if (!insidexywh(tp.x, tp.y, 50, 50)) { continue; }
                    if (ret.a[this->agrid[tp.y][tp.x]]) { continue; }
                    
                    Ret tret = ret;
                    tret.a[this->agrid[tp.y][tp.x]] = true;
                    tret.d.emplace_back(d);
                    tret.score += this->bgrid[tp.y][tp.x];
                    tret.lastp.x +=dx[d];
                    tret.lastp.y +=dy[d];
                    // tret.nextscore = 0;
                    // for (int nd = 0; nd < 4; ++nd) {
                    //     e512pos ttp = tret.lastp;
                    //     ttp.x +=dx[nd];
                    //     ttp.y +=dy[nd];
                    //     if (!insidexywh(ttp.x, ttp.y, 50, 50)) { continue; }
                    //     if (tret.a[this->agrid[ttp.y][ttp.x]]) { continue; }
                    //     tret.nextscore += 10;
                    // }
                    
                    
                    trets.emplace_back(tret);
                    
                    if (tret.score > this->bestret.score) {
                        this->bestret = tret;
                    }
                }
            }
            rets.clear();
            // sort(trets.begin(), trets.end(), [](const Ret& a, const Ret& b) { return a.score + a.nextscore > b.score + b.nextscore; });
            
            if (this->sw.get_milli_time() > 1600) { tbw /= 2; }
            if (this->sw.get_milli_time() > 1700) { tbw /= 2; }
            if (this->sw.get_milli_time() > 1800) { tbw /= 2; }
            if (this->sw.get_milli_time() > 1900) { tbw /= 2; }
            if (this->sw.get_milli_time() > 1920) { tbw /= 2; }
            if (this->sw.get_milli_time() > 1940) { tbw /= 2; }
            us.clear();
            
            sort(trets.begin(), trets.end(), [](const Ret& a, const Ret& b) { return a.score > b.score; });
            int bw = min((int)trets.size(), tbw);
            for (int i = 0; i < bw; ++i) {
                rets.emplace_back(trets[i]);
                us.emplace(i);
            }
            
            
            if (trets.size() > bw) {
                for (int i = 0; i < 32; ++i) {
                    int j = xrnd() % trets.size();
                    if (us.find(j) == us.end()) {
                        rets.emplace_back(trets[j]);
                        us.emplace(j);
                    }
                    
                }
            }
            
        }
        
        
        return this->bestret;
    }
    
    double calcscore (Ret ret) {
        static int dx[4] = { 0, 1, 0, -1 };
        static int dy[4] = { -1, 0, 1, 0 };
        double score = this->bgrid[ret.p.y][ret.p.x];
        e512pos p = ret.p;
        for (auto&& i : ret.d) {
            p.x += dx[i];
            p.y += dy[i];
            score += this->bgrid[p.y][p.x];
        }
        return score;
    }
    
};



int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    MM mm;
    mm.input();
    mm.calc();
    mm.output();
    
    return 0;
}

