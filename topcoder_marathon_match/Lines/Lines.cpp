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

class CNT5 {
public:
    array<int, 10> cnts;
    int N, C;
    CNT5 (int N, int C) {
        this->N = N;
        this->C = C;
        for (int i = 0; i < 10; ++i) { this->cnts[i] = 0; }
    }
    // CNT5 (int a, int b, int c) {
    //     this->target = a;
    //     this->different = b;
    //     this->blank = c;
    // }
    int score () {
        
        int m = 0;
        for (int i = 1; i < 10; ++i) {
            m = max(m, this->cnts[i]);
        }
        int r = 0;
        if (this->C == 3 && this->N == 11) {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 45*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 45*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 45*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 45 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->C == 3 && this->N == 10) {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 38*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 38*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 38*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 38 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->C == 3 && this->N == 9) {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 30*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 30*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 30*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 30 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->C == 3 && this->N == 8) {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 25*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 25*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 25*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 25 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 7 && this->C == 3)  {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 15*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 15*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 15*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 15 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 7 && this->C == 4)  {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 15*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 15*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 15*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 15 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 7 && this->C == 5)  {
            if (this->cnts[0] == 5) { return 5 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 10*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 10*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 10*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 10 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 7 && this->C == 6)  {
            if (this->cnts[0] == 5) { return 5 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 5*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 5*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 5*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 5 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 7)  {
            if (this->cnts[0] == 5) { return 5 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 5*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 5*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 5*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 5 : 0;
            
            // r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            // r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            // r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            // r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            return r;
        } else if (this->N == 8 && this->C == 9)  {
            if (this->cnts[0] == 5) { return 5 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 10*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 10*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 10*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 10 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            r += m == 3 && this->cnts[0] == 0 ? 1*2*2 : 0;
            r += m == 2 && this->cnts[0] == 1 ? 1*2 : 0;
            r += m == 1 && this->cnts[0] == 2 ? 1 : 0;
            
            return r;
        } else if (this->N == 8 && this->C == 8)  {
            if (this->cnts[0] == 5) { return 5 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 15*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 15*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 15*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 15 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            r += m == 3 && this->cnts[0] == 0 ? 1*2*2 : 0;
            r += m == 2 && this->cnts[0] == 1 ? 1*2 : 0;
            r += m == 1 && this->cnts[0] == 2 ? 1 : 0;
            
            return r;
        } else if (this->C < 6 || this->N > 9)  {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 15*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 15*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 15*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 15 : 0;
            
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            r += m == 3 && this->cnts[0] == 0 ? 1*2*2 : 0;
            r += m == 2 && this->cnts[0] == 1 ? 1*2 : 0;
            r += m == 1 && this->cnts[0] == 2 ? 1 : 0;
            return r;
        } else {
            if (this->cnts[0] == 5) { return 15 * this->C; }
            r += m == 4 && this->cnts[0] == 1 ? 10*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 2 ? 10*8*8 : 0;
            r += m == 2 && this->cnts[0] == 3 ? 10*8 : 0;
            r += m == 1 && this->cnts[0] == 4 ? 10 : 0;
            r += m == 4 && this->cnts[0] == 0 ? 1*8*8*8 : 0;
            r += m == 3 && this->cnts[0] == 1 ? 1*8*8 : 0;
            r += m == 2 && this->cnts[0] == 2 ? 1*8 : 0;
            r += m == 1 && this->cnts[0] == 3 ? 1 : 0;
            
            r += m == 3 && this->cnts[0] == 0 ? 1*2*2 : 0;
            r += m == 2 && this->cnts[0] == 1 ? 1*2 : 0;
            r += m == 1 && this->cnts[0] == 2 ? 1 : 0;
            return r;
        }
        
        return 0;
    }
};

class Lines {
public:
    int N, NN;
    int C;
    int time = 0;
    int turn = -1;
    vector<int> currentgrid;
    array<int, 3> nextb;
    Lines (int N, int C) {
        this->N = N;
        this->NN = N*N;
        this->C = C;
        pdebug(N, C);
        this->currentgrid = vector<int>(N*N);
        
        // fdebug(N);
    }
    bool f = true;
    void update (vector<int>& grid, array<int, 3>& nextb, int time) {
        this->turn += 1;
        for (int i = 0; i < grid.size(); ++i) { this->currentgrid[i] = grid[i]; }
        for (int i = 0; i < 3; ++i) { this->nextb[i] = nextb[i]; }
        this->time = time;
        
        // fdebug(grid);
        int bestscore = -100000;
        int besta = -1;
        int bestb = -1;
        if (this->time < 9800) {
            this->sets_update(grid);
            this->movecomb_update(grid);
            
            int lcnt = 0;
            
            for (auto&& o : this->movecomb) {
                lcnt += 1;
                if (this->time > 9000 && lcnt % 2 > 0 && this->C < 8) { continue; }
                if (this->time > 9400 && lcnt % 8 > 0 && this->C < 6) { continue; }
                if (this->time > 9800) { break; }
                // if (this->time > 9500) {
                //     if (this->f) {
                //         this->f = false;
                //         pdebug(this->turn);
                //     }
                //     break;
                // }
                int a = o.first;
                int b = o.second;
                swap(grid[a], grid[b]);
                
                int score = 0;
                
                int bx = b % this->N;
                int by = b / this->N;
                int tc = grid[b];
                int allcnt = 1;
                int cnt = 0;
                for (int i = bx+1; i < this->N; ++i, ++cnt) {
                    if (grid[by*this->N+i] != tc) { break; }
                }
                for (int i = bx-1; i >= 0; --i, ++cnt) {
                    if (grid[by*this->N+i] != tc) { break; }
                }
                
                if (cnt >= 4) {
                    allcnt += cnt;
                    for (int i = bx+1; i < this->N; ++i) {
                        if (grid[by*this->N+i] != tc) { break; }
                        grid[by*this->N+i] = 0;
                    }
                    for (int i = bx-1; i >= 0; --i) {
                        if (grid[by*this->N+i] != tc) { break; }
                        grid[by*this->N+i] = 0;
                    }
                    grid[b] = 0;
                }
                cnt = 0;
                
                for (int i = by+1; i < this->N; ++i, ++cnt) {
                    if (grid[i*this->N+bx] != tc) { break; }
                }
                for (int i = by-1; i >= 0; --i, ++cnt) {
                    if (grid[i*this->N+bx] != tc) { break; }
                }
                
                if (cnt >= 4) {
                    allcnt += cnt;
                    for (int i = by+1; i < this->N; ++i) {
                        if (grid[i*this->N+bx] != tc) { break; }
                        grid[i*this->N+bx] = 0;
                    }
                    for (int i = by-1; i >= 0; --i) {
                        if (grid[i*this->N+bx] != tc) { break; }
                        grid[i*this->N+bx] = 0;
                    }
                    grid[b] = 0;
                }
                cnt = 0;
                
                for (int i = bx+1, j = by+1; i < this->N && j < this->N; ++i, ++j, ++cnt) {
                    if (grid[j*this->N+i] != tc) { break; }
                }
                for (int i = bx-1, j = by-1; i >= 0 && j >= 0; --i, --j, ++cnt) {
                    if (grid[j*this->N+i] != tc) { break; }
                }
                
                if (cnt >= 4) {
                    allcnt += cnt;
                    for (int i = bx+1, j = by+1; i < this->N && j < this->N; ++i, ++j) {
                        if (grid[j*this->N+i] != tc) { break; }
                        grid[j*this->N+i] = 0;
                    }
                    for (int i = bx-1, j = by-1; i >= 0 && j >= 0; --i, --j) {
                        if (grid[j*this->N+i] != tc) { break; }
                        grid[j*this->N+i] = 0;
                    }
                    grid[b] = 0;
                }
                cnt = 0;
                
                
                for (int i = bx-1, j = by+1; i >= 0 && j < this->N; --i, ++j, ++cnt) {
                    if (grid[j*this->N+i] != tc) { break; }
                }
                for (int i = bx+1, j = by-1; i < this->N && j >= 0; ++i, --j, ++cnt) {
                    if (grid[j*this->N+i] != tc) { break; }
                }
                
                if (cnt >= 4) {
                    allcnt += cnt;
                    for (int i = bx-1, j = by+1; i >= 0 && j < this->N; --i, ++j) {
                        if (grid[j*this->N+i] != tc) { break; }
                        grid[j*this->N+i] = 0;
                    }
                    for (int i = bx+1, j = by-1; i < this->N && j >= 0; ++i, --j) {
                        if (grid[j*this->N+i] != tc) { break; }
                        grid[j*this->N+i] = 0;
                    }
                    grid[b] = 0;
                }
                cnt = 0;
                
                
                score += allcnt > 1 ? (allcnt*allcnt-allcnt*7+20)*6000 : 0;
                if (score > 0 && this->C == 3) {
                    if (this->nextb[0] == tc) { score *= 0.5; }
                    if (this->nextb[1] == tc) { score *= 0.5; }
                    if (this->nextb[2] == tc) { score *= 0.5; }
                }
                
                if (this->N < 9 && this->C < 7) {
                    for (int i = 0; i < this->N; ++i) {
                        CNT5 c5(this->N, this->C);
                        for (int k = 0; k < 5; ++k) {
                            const int x = k;
                            const int y = i;
                            const int p = y * this->N + x;
                            if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                        }
                        score += c5.score();
                        for (int j = 1; j < this->N-4; ++j) {
                            {
                                const int x = j-1;
                                const int y = i;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] -= 1; }
                            }
                            {
                                const int x = j+4;
                                const int y = i;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                            }
                            score += c5.score();
                        }
                    }
                    
                    for (int i = 0; i < this->N; ++i) {
                        CNT5 c5(this->N, this->C);
                        for (int k = 0; k < 5; ++k) {
                            const int x = i;
                            const int y = k;
                            const int p = y * this->N + x;
                            if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                        }
                        score += c5.score();
                        for (int j = 1; j < this->N-4; ++j) {
                            {
                                const int x = i;
                                const int y = j-1;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] -= 1; }
                            }
                            {
                                const int x = i;
                                const int y = j+4;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                            }
                            score += c5.score();
                        }
                    }
                    
                    for (int i = 0; i < this->N-4; ++i) {
                        for (int j = 0; j < this->N-4; ++j) {
                            CNT5 c5(this->N, this->C);
                            for (int k = 0; k < 5; ++k) {
                                const int x = j+k;
                                const int y = i+k;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                            }
                            score += c5.score();
                            
                        }
                    }
                    for (int i = 0; i < this->N-4; ++i) {
                        for (int j = 0; j < this->N-4; ++j) {
                            CNT5 c5(this->N, this->C);
                            for (int k = 0; k < 5; ++k) {
                                const int x = i+4-k;
                                const int y = j+k;
                                const int p = y * this->N + x;
                                if (this->blank(grid, p)) { c5.cnts[grid[p]] += 1; }
                            }
                            score += c5.score();
                        }
                    }
                } else {
                    for (int i = 0; i < this->N; ++i) {
                        CNT5 c5(this->N, this->C);
                        for (int k = 0; k < 5; ++k) {
                            const int x = k;
                            const int y = i;
                            const int p = y * this->N + x;
                            c5.cnts[grid[p]] += 1;
                        }
                        score += c5.score();
                        for (int j = 1; j < this->N-4; ++j) {
                            {
                                const int x = j-1;
                                const int y = i;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] -= 1;
                            }
                            {
                                const int x = j+4;
                                const int y = i;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] += 1;
                            }
                            score += c5.score();
                        }
                    }
                    
                    for (int i = 0; i < this->N; ++i) {
                        CNT5 c5(this->N, this->C);
                        for (int k = 0; k < 5; ++k) {
                            const int x = i;
                            const int y = k;
                            const int p = y * this->N + x;
                            c5.cnts[grid[p]] += 1;
                        }
                        score += c5.score();
                        for (int j = 1; j < this->N-4; ++j) {
                            {
                                const int x = i;
                                const int y = j-1;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] -= 1;
                            }
                            {
                                const int x = i;
                                const int y = j+4;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] += 1;
                            }
                            score += c5.score();
                        }
                    }
                    
                    for (int i = 0; i < this->N-4; ++i) {
                        for (int j = 0; j < this->N-4; ++j) {
                            CNT5 c5(this->N, this->C);
                            for (int k = 0; k < 5; ++k) {
                                const int x = j+k;
                                const int y = i+k;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] += 1;
                            }
                            score += c5.score();
                            
                        }
                    }
                    for (int i = 0; i < this->N-4; ++i) {
                        for (int j = 0; j < this->N-4; ++j) {
                            CNT5 c5(this->N, this->C);
                            for (int k = 0; k < 5; ++k) {
                                const int x = i+4-k;
                                const int y = j+k;
                                const int p = y * this->N + x;
                                c5.cnts[grid[p]] += 1;
                            }
                            score += c5.score();
                        }
                    }
                }
                
                // if (score > bestscore || (score >= bestscore && xrnd()%2==0)) {
                if (score > bestscore) {
                    bestscore = score;
                    besta = a;
                    bestb = b;
                }
                
                // for (int i = 0; i < this->NN; ++i) { grid[i] = this->currentgrid[i]; }
                grid = this->currentgrid;
            }
        }
        if (bestscore > -100000) {
            cout << print(besta/this->N, besta%this->N, bestb/this->N, bestb%this->N) << endl;
        } else {
            this->calc0();
        }
        
        
    }
    
    bool blank (vector<int>& grid, int p) {
        static const int dy[] = { 0, 1, 0,-1};
        static const int dx[] = {-1, 0, 1, 0};
        if (grid[p] > 0) { return true; }
        int x = p % this->N;
        int y = p / this->N;
        int cnt = 0;
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= this->N) { continue; }
            if (ty < 0 || ty >= this->N) { continue; }
            int tp = ty * this->N + tx;
            if (grid[tp] == 0) { cnt += 1; }
        }
        return (cnt < 1 ? false : true);
    }
    
    
    vector< pair<int, int> > movecomb;
    void movecomb_update (vector<int>& grid) {
        this->movecomb.clear();
        
        for (int k = 0; k < this->sets.size(); ++k) {
            for (int p = 0; p < this->NN; ++p) {
                if (grid[p] > 0 || this->setsgrid[p] != k) { continue; }
                for (auto&& a : this->sets[k]) { this->movecomb.emplace_back(a, p); }
            }
        }
    }
    
    vector< vector<int> > sets;
    vector<int> setsgrid;
    void sets_update (vector<int>& grid) {
        static const int dy[] = { 0, 1, 0,-1};
        static const int dx[] = {-1, 0, 1, 0};
        this->setsgrid = vector<int>(this->N*this->N, -1);
        
        vector<int> q;
        this->sets.clear();
        unordered_set<int> tset;
        for (int p = 0; p < this->NN; ++p) {
            if (grid[p] == 0 && this->setsgrid[p] == -1) {
                this->setsgrid[p] = this->sets.size();
                tset.clear();
                q.clear();
                q.emplace_back(p);
                while (q.size() > 0) {
                    int t = q.back();
                    int px = t % this->N;
                    int py = t / this->N;
                    q.pop_back();
                    for (int i = 0; i < 4; ++i) {
                        int tx = px + dx[i];
                        int ty = py + dy[i];
                        if (tx < 0 || tx >= this->N) { continue; }
                        if (ty < 0 || ty >= this->N) { continue; }
                        int tp = ty * this->N + tx;
                        if (grid[tp] > 0) {
                            tset.emplace(tp);
                            continue;
                        }
                        if (grid[tp] == 0 && this->setsgrid[tp] == -1) {
                            q.emplace_back(tp);
                            this->setsgrid[tp] = this->sets.size();
                        }
                    }
                }
                vector<int> v;
                for (auto&& i : tset) { v.emplace_back(i); }
                this->sets.emplace_back(v);
            }
        }
        
    }
    
    
    
    void calc0 () {
        static const int EMPTY = 0;
        static const int dr[] = { 0, 1, 0,-1};
        static const int dc[] = {-1, 0, 1, 0};
        for (int r=0; r<N; ++r) {
            for (int c=0; c<N; ++c) {
                if (this->currentgrid[r*N+c]==EMPTY) { continue; }
                for (int m=0; m<4; m++) {
                    int r2=r+dr[m];
                    int c2=c+dc[m];

                    if (r2>=0 && r2<N && c2>=0 && c2<N && this->currentgrid[r2*N+c2]==EMPTY) {
                        cout << print(r, c, r2, c2) << endl;
                        return;
                    }
                }
            }   
        }
    }
    
};



int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    int C;
    int elapsedTime;
    array<int, 3> nextBalls;

    cin >> N;
    cin >> C;
    
    Lines lines(N, C);
    vector<int> grid(N*N);
    
    for (int i=0; i<1000; ++i) {
        //read grid
        for (int k=0; k<N*N; ++k) { cin >> grid[k]; }
        //read next balls
        for (int k=0; k<3; ++k) { cin >> nextBalls[k]; }
        //read elapsed time
        cin >> elapsedTime;
        
        lines.update(grid, nextBalls, elapsedTime);
        
        //make move
        // lines.calc0();
    }
}