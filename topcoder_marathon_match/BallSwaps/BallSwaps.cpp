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

struct YXYX {
public:
    int a, b, c, d;
    YXYX (int a, int b, int c, int d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};
ostream& operator << (ostream& os, const YXYX& t) {
    os << print(t.a, t.b, t.c, t.d);
    return os;
};

struct GHASH6 {
    // 000 000 000 000 000 000
    // 000 000 000 000 000 000
    // 000 000 000 000 000 000
    
    // 000 000 000 000 000 000
    // 000 000 000 000 000 000
    // 000 000 000 000 000 000
    uint64_t a, b;
    GHASH6 (array< array<int, 30>, 30 >& grid, int N) {
        this->a = 0;
        this->b = 0;
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (y < 3) {
                    uint64_t t = grid[y][x];
                    this->a |= t << (x*3+y*18);
                } else {
                    uint64_t t = grid[y][x];
                    this->b |= t << (x*3+(y-3)*18);
                }
            }
        }
    }
    
    bool operator == (const GHASH6& t) const { return this->a == t.a && this->b == t.b; }
};
namespace std {
    template <> class hash<GHASH6> {
    public:
        size_t operator()(const GHASH6& t) const{ return hash<uint64_t>()(t.a<<32) | hash<uint64_t>()(t.b); }
    };
}

class MM {
public:
    StopWatch sw;
    int N;
    int C;
    array< array<int, 30>, 30 > grid;
    array<int, 8> ccnts;
    vector<YXYX> best;
    
    
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N;
        cin >> this->C;
        for (int i = 0; i < this->C; ++i) { this->ccnts[i] = 0; }
        for (int y=0; y<this->N; y++) {
            for (int x=0; x<this->N; x++) {
                cin >> this->grid[y][x];
                this->ccnts[this->grid[y][x]] += 1;
            }
        }
        vector<int> cs;
        for (int i = 0; i < this->C; ++i) { cs.emplace_back(this->ccnts[i]); }
        pdebug(this->N, this->C, cs);
    }
    
    void playSwapMove (vector<YXYX>& v, array< array<int, 30>, 30 >& grid) {
        for (auto&& t : v) { swap(grid[t.a][t.b], grid[t.c][t.d]); }
    }
    
    void solution () {
        int bestscore = 1000000;
        vector<YXYX> tmpout;
        vector<int> vi;
        for (int i = 0; i < this->C; ++i) { vi.emplace_back(i); }
        
        int cnt = 0;
        int etime = 9600;
        
        
        if (this->N < 7){
            tmpout = this->solutionBeamSearch();
            array< array<int, 30>, 30 > tg = this->grid;
            this->playSwapMove(tmpout, tg);
            if (this->componentCnt(tg) == this->C) {
                bestscore = tmpout.size();
                this->best = tmpout;
            }
        }
        
        while (this->sw.get_milli_time() < etime && cnt < 100000) {
            int a = xrnd() % this->C;
            int b = xrnd() % this->C;
            swap(vi[a], vi[b]);
            
            array< array<int, 30>, 30 > tg = this->spiralzigzag(vi);
            this->rot(xrnd(), tg);
            if (xrnd()%2) { this->rev(tg); }
            tmpout = this->solution04(tg);
            if (tmpout.size() < bestscore) {
                bestscore = tmpout.size();
                this->best = tmpout;
            }
            cnt += 1;
        }
        
        while (this->sw.get_milli_time() < etime) {
            int a = xrnd() % this->C;
            int b = xrnd() % this->C;
            swap(vi[a], vi[b]);
            
            array< array<int, 30>, 30 > tg = this->spiralzigzag(vi);
            this->rot(xrnd(), tg);
            if (xrnd()%2) { this->rev(tg); }
            tmpout = this->solution05(tg);
            if (tmpout.size() < bestscore) {
                bestscore = tmpout.size();
                this->best = tmpout;
            }
            cnt += 1;
        }
        pdebug("c", cnt);
        
        // pdebug(this->componentCnt(this->grid));
    }
    
    void aafdebug (array< array<int, 30>, 30 >& aa) {
        for (int y = 0; y < this->N; ++y) {
            string s = "";
            for (int x = 0; x < this->N; ++x) {
                s += to_string(aa[y][x]);
            }
            fdebug(s);
        }
    }
    
    void rot (int n, array< array<int, 30>, 30 >& tg) {
        static array< array<int, 30>, 30 > g;
        for (int i = 0; i < n%4; ++i) {
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    g[x][this->N-y-1] = tg[y][x];
                }
            }
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    tg[y][x] = g[y][x];
                }
            }
        }
    }
    
    void rev (array< array<int, 30>, 30 >& tg) {
        static array< array<int, 30>, 30 > g;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                g[y][x] = tg[y][this->N-x-1];
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                tg[y][x] = g[y][x];
            }
        }
    }
    
    array< array<int, 30>, 30 > zigzag (vector<int>& v) {
        array< array<int, 30>, 30 > tg;
        vector<int> cs;
        for (int i = 0; i < this->C; ++i) {
            for (int j = 0; j < this->ccnts[v[i]]; ++j) {
                cs.emplace_back(v[i]);
            }
        }
        int p = 0;
        for (int y = 0; y < this->N; ++y) {
            if (y % 2 == 0) {
                for (int x = 0; x < this->N; ++x) {
                    tg[y][x] = cs[p];
                    p += 1;
                }
            } else {
                for (int x = this->N-1; x >= 0; --x) {
                    tg[y][x] = cs[p];
                    p += 1;
                }
            }
            
        }
        
        return tg;
    }
    
    
    array< array<int, 30>, 30 > spiral (vector<int>& v) {
        array< array<int, 30>, 30 > tg;
        vector<int> cs;
        for (int i = 0; i < this->C; ++i) {
            for (int j = 0; j < this->ccnts[v[i]]; ++j) {
                cs.emplace_back(v[i]);
            }
        }
        int p = 0;
        int l = 0;
        int r = 0;
        int u = 0;
        int d = 0;
        
        while (p < this->N*this->N) {
            for (int i = l; i < this->N-r; ++i) {
                tg[u][i] = cs[p];
                p += 1;
            }
            u += 1;
            
            for (int i = u; i < this->N-d; ++i) {
                tg[i][this->N-r-1] = cs[p];
                p += 1;
            }
            r += 1;
            
            for (int i = this->N-r-1; i >= l; --i) {
                tg[this->N-d-1][i] = cs[p];
                p += 1;
            }
            d += 1;
            
            
            for (int i = this->N-d-1; i >= u; --i) {
                tg[i][l] = cs[p];
                p += 1;
            }
            l += 1;
        }
        
        
        return tg;
    }
    
    
    array< array<int, 30>, 30 > spiralzigzag (vector<int>& v) {
        array< array<int, 30>, 30 > tg;
        vector<int> cs;
        for (int i = 0; i < this->C; ++i) {
            for (int j = 0; j < this->ccnts[v[i]]; ++j) {
                cs.emplace_back(v[i]);
            }
        }
        int p = 0;
        int l = 0;
        int r = 0;
        int u = 0;
        int d = 0;
        
        int g = xrnd() % (this->N);
        
        while (p < this->N*this->N) {
            if (l < g) {
                for (int i = l; i < this->N-r; ++i) {
                    tg[u][i] = cs[p];
                    p += 1;
                }
                u += 1;
                
                for (int i = u; i < this->N-d; ++i) {
                    tg[i][this->N-r-1] = cs[p];
                    p += 1;
                }
                r += 1;
                
                for (int i = this->N-r-1; i >= l; --i) {
                    tg[this->N-d-1][i] = cs[p];
                    p += 1;
                }
                d += 1;
                
                
                for (int i = this->N-d-1; i >= u; --i) {
                    tg[i][l] = cs[p];
                    p += 1;
                }
                l += 1;
            } else {
                int i = 0;
                for (int y = u; y < this->N-d; ++y) {
                    if (i % 2 == 0) {
                        for (int x = l; x < this->N-r; ++x) {
                            tg[y][x] = cs[p];
                            p += 1;
                        }
                    } else {
                        for (int x = this->N-1-r; x >= l; --x) {
                            tg[y][x] = cs[p];
                            p += 1;
                        }
                    }
                    i += 1;
                }
            }
        }
        
        
        return tg;
    }
    
    vector<YXYX> solution04 (array< array<int, 30>, 30 >& tg) {
        static array< array<int, 30>, 30 > grid;
        vector<YXYX> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y][x] = this->grid[y][x];
            }
        }
        
        int u = 0;
        int d = 0;
        int l = 0;
        int r = 0;
        for (int i = 0; i < this->N*0.4; ++i) {
            if (xrnd() % 2) {
                int y = u;
                if (xrnd() % 2) {
                    for (int x = this->N-1; x >= 0; --x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchDL(x, y, rx, ry, d, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int x = 0; x < this->N; ++x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchDR(x, y, rx, ry, d, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                u += 1;
            } else {
                int y = this->N-1-d;
                if (xrnd() % 2) {
                    for (int x = this->N-1; x >= 0; --x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchUL(x, y, rx, ry, u, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int x = 0; x < this->N; ++x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchUR(x, y, rx, ry, u, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                d += 1;
            }
        }
        
        for (int i = 0; i < this->N; ++i) {
            if (xrnd() % 2) {
                int x = l;
                // if (xrnd() % 2) {
                    for (int y = u; y < this->N-d; ++y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchRD(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                // } else {
                //     for (int y = this->N-1-d; y >= u; --y) {
                //         if (grid[y][x] == tg[y][x]) { continue; }
                //         int ry, rx;
                //         this->searchRU(x, y, rx, ry, u, d, l, r, tg, grid);
                //         this->moveWHR(x, y, rx, ry, ret, tg, grid);
                //     }
                // }
                l += 1;
            } else {
                
                int x = this->N-1-r;
                // if (xrnd() % 2) {
                    for (int y = u; y < this->N-d; ++y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchLD(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                // } else {
                //     for (int y = this->N-1-d; y >= u; --y) {
                //         if (grid[y][x] == tg[y][x]) { continue; }
                //         int ry, rx;
                //         this->searchLU(x, y, rx, ry, u, d, l, r, tg, grid);
                //         this->moveWHR(x, y, rx, ry, ret, tg, grid);
                //     }
                // }
                r += 1;
            }
        }
        
        
        
        return ret;
    }
    
    vector<YXYX> solution05 (array< array<int, 30>, 30 >& tg) {
        static array< array<int, 30>, 30 > grid;
        vector<YXYX> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y][x] = this->grid[y][x];
            }
        }
        
        
        int u = 0;
        int d = 0;
        int l = 0;
        int r = 0;
        for (int i = 0; i < this->N*0.4; ++i) {
            if (xrnd() % 2) {
                int y = u;
                if (xrnd() % 2) {
                    for (int x = this->N-1; x >= 0; --x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchDL(x, y, rx, ry, d, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int x = 0; x < this->N; ++x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchDR(x, y, rx, ry, d, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                u += 1;
            } else {
                int y = this->N-1-d;
                if (xrnd() % 2) {
                    for (int x = this->N-1; x >= 0; --x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchUL(x, y, rx, ry, u, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int x = 0; x < this->N; ++x) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchUR(x, y, rx, ry, u, tg, grid);
                        this->moveHWR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                d += 1;
            }
        }
        
        for (int i = 0; i < this->N; ++i) {
            if (xrnd() % 2) {
                int x = l;
                if (xrnd() % 2) {
                    for (int y = u; y < this->N-d; ++y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchRD(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int y = this->N-1-d; y >= u; --y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchRU(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                l += 1;
            } else {
                
                int x = this->N-1-r;
                if (xrnd() % 2) {
                    for (int y = u; y < this->N-d; ++y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchLD(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                } else {
                    for (int y = this->N-1-d; y >= u; --y) {
                        if (grid[y][x] == tg[y][x]) { continue; }
                        int ry, rx;
                        this->searchLU(x, y, rx, ry, u, d, l, r, tg, grid);
                        this->moveWHR(x, y, rx, ry, ret, tg, grid);
                    }
                }
                r += 1;
            }
        }
        
        
        while (ret.size()) {
            YXYX t = ret.back();
            swap(grid[t.a][t.b], grid[t.c][t.d]);
            if (this->componentCnt(grid) > this->C) { break; }
            ret.pop_back();
        }
        
        return ret;
    }
    
    void gridSet (vector<YXYX>& v, array< array<int, 30>, 30 >& grid) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y][x] = this->grid[y][x];
            }
        }
        this->playSwapMove(v, grid);
    }
    
    vector<YXYX> solutionBeamSearch () {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        array< array<int, 30>, 30 > grid;
        int bmw = 5126;
        vector< pair< pair<int, bool>, vector<YXYX> > > bm;
        vector< pair< pair<int, bool>, vector<YXYX> > > tbm;
        bm.emplace_back(pair<int, bool>(this->componentCnt(this->grid), true), vector<YXYX>());
        
        unordered_set<GHASH6> gh;
        gh.emplace(GHASH6(grid, this->N));
        
        int depth = 0;
        while (this->sw.get_milli_time() < 3000 && bm.size() > 0 && depth < 48) {
            tbm.clear();
            for (auto&& i : bm) {
                this->gridSet(i.second, grid);
                int ay = -1;
                int ax = -1;
                int by = -1;
                int bx = -1;
                if (depth>0) {
                    ay = i.second.back().a;
                    ax = i.second.back().b;
                    by = i.second.back().c;
                    bx = i.second.back().d;
                }
                
                if (i.first.second) {
                    for (int y = 0; y < this->N; ++y) {
                        for (int x = 0; x < this->N-1; ++x) {
                            if (grid[y][x] == grid[y][x+1]) { continue; }
                            if (y==ay && x==ax && y==by && x+1==bx) { continue; }
                            if (y==by && x==bx && y==ay && x+1==ax) { continue; }
                            swap(grid[y][x], grid[y][x+1]);
                            int score = this->componentCnt(grid);
                            i.second.emplace_back(y, x, y, x+1);
                            
                            if (score == this->C) {
                                pdebug("bm");
                                return i.second;
                            }
                            
                            GHASH6 h(grid, this->N);
                            if (gh.find(h) == gh.end()) {
                                gh.emplace(h);
                                
                                tbm.emplace_back(pair<int, bool>(score, score < i.first.first), i.second);
                            }
                            
                            
                            i.second.pop_back();
                            swap(grid[y][x], grid[y][x+1]);
                        }
                    }
                    for (int y = 0; y < this->N-1; ++y) {
                        for (int x = 0; x < this->N; ++x) {
                            if (grid[y][x] == grid[y+1][x]) { continue; }
                            if (y==ay && x==ax && y+1==by && x==bx) { continue; }
                            if (y==by && x==bx && y+1==ay && x==ax) { continue; }
                            
                            swap(grid[y][x], grid[y+1][x]);
                            int score = this->componentCnt(grid);
                            i.second.emplace_back(y, x, y+1, x);
                            
                            if (score == this->C) {
                                pdebug("bm");
                                return i.second;
                            }
                            GHASH6 h(grid, this->N);
                            if (gh.find(h) == gh.end()) {
                                gh.emplace(h);
                                
                                tbm.emplace_back(pair<int, bool>(score, score < i.first.first), i.second);
                            }
                            i.second.pop_back();
                            swap(grid[y][x], grid[y+1][x]);
                        }
                    }
                } else {
                    {
                        int y = i.second.back().a;
                        int x = i.second.back().b;
                        for (int d = 0; d < 4; ++d) {
                            int py = y + dy[d];
                            int px = x + dx[d];
                            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                            if (grid[y][x] == grid[py][px]) { continue; }
                            if (y==ay && x==ax && py==by && px==bx) { continue; }
                            if (y==by && x==bx && py==ay && px==ax) { continue; }
                            swap(grid[y][x], grid[py][px]);
                            int score = this->componentCnt(grid);
                            i.second.emplace_back(y, x, py, px);
                            
                            if (score == this->C) {
                                pdebug("bm");
                                return i.second;
                            }
                            GHASH6 h(grid, this->N);
                            if (gh.find(h) == gh.end()) {
                                gh.emplace(h);
                                
                                tbm.emplace_back(pair<int, bool>(score, score < i.first.first), i.second);
                            }
                            i.second.pop_back();
                            swap(grid[y][x], grid[py][px]);
                        }
                    }
                    {
                        int y = i.second.back().c;
                        int x = i.second.back().d;
                        for (int d = 0; d < 4; ++d) {
                            int py = y + dy[d];
                            int px = x + dx[d];
                            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                            if (grid[y][x] == grid[py][px]) { continue; }
                            if (y==ay && x==ax && py==by && px==bx) { continue; }
                            if (y==by && x==bx && py==ay && px==ax) { continue; }
                            swap(grid[y][x], grid[py][px]);
                            int score = this->componentCnt(grid);
                            i.second.emplace_back(y, x, py, px);
                            
                            if (score == this->C) {
                                pdebug("bm");
                                return i.second;
                            }
                            GHASH6 h(grid, this->N);
                            if (gh.find(h) == gh.end()) {
                                gh.emplace(h);
                                
                                tbm.emplace_back(pair<int, bool>(score, score < i.first.first), i.second);
                            }
                            i.second.pop_back();
                            swap(grid[y][x], grid[py][px]);
                        }
                    }
                }
            }
            sort(tbm.begin(), tbm.end(), [](const pair< pair<int, bool>, vector<YXYX> >& a, const pair< pair<int, bool>, vector<YXYX> >& b) { return a.first.first-a.first.second*0.5 < b.first.first-b.first.second*0.5; });
            const int maxsz = min((int)tbm.size(), bmw);
            bm.clear();
            for (int i = 0; i < maxsz; ++i) {
                bm.emplace_back(tbm[i]);
            }
            
            depth += 1;
        }
        
        return vector<YXYX>();
    }
    
    void searchDR (int x, int y, int& rx, int& ry, int d, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        
        for (int ty = y+1; ty < this->N-d; ++ty) {
            for (int tx = 0; tx < this->N; ++tx) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx)*2 + abs(y-ty);
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int tx = x+1; tx < this->N; ++tx) {
            if (grid[y][tx] == tg[y][x]) {
                rx = tx;
                ry = y;
                return;
            }
        }
    }
    void searchDL (int x, int y, int& rx, int& ry, int d, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        
        for (int ty = y+1; ty < this->N-d; ++ty) {
            for (int tx = this->N-1; tx >= 0; --tx) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx)*2 + abs(y-ty);
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int tx = x-1; tx >= 0; --tx) {
            if (grid[y][tx] == tg[y][x]) {
                rx = tx;
                ry = y;
                return;
            }
        }
    }
    
    void searchUR (int x, int y, int& rx, int& ry, int u, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        
        for (int ty = y-1; ty >= u; --ty) {
            for (int tx = 0; tx < this->N; ++tx) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx)*2 + abs(y-ty);
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int tx = x+1; tx < this->N; ++tx) {
            if (grid[y][tx] == tg[y][x]) {
                rx = tx;
                ry = y;
                return;
            }
        }
    }
    void searchUL (int x, int y, int& rx, int& ry, int u, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        
        for (int ty = y-1; ty >= u; --ty) {
            for (int tx = this->N-1; tx >= 0; --tx) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx)*2 + abs(y-ty);
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int tx = x-1; tx >= 0; --tx) {
            if (grid[y][tx] == tg[y][x]) {
                rx = tx;
                ry = y;
                return;
            }
        }
    }
    
    void searchRD (int x, int y, int& rx, int& ry, int u, int d, int l, int r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        for (int tx = l+1; tx < this->N-r; ++tx) {
            for (int ty = u; ty < this->N-d; ++ty) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx) + abs(y-ty)*2;
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int ty = y+1; ty < this->N-d; ++ty) {
            if (grid[ty][x] == tg[y][x]) {
                rx = x;
                ry = ty;
                return;
            }
        }
    }
    
    void searchRU (int x, int y, int& rx, int& ry, int u, int d, int l, int r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        for (int tx = l+1; tx < this->N-r; ++tx) {
            for (int ty = this->N-1-d; ty >= u; --ty) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx) + abs(y-ty)*2;
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int ty = y-1; ty >= u; --ty) {
            if (grid[ty][x] == tg[y][x]) {
                rx = x;
                ry = ty;
                return;
            }
        }
    }
    
    void searchLD (int x, int y, int& rx, int& ry, int u, int d, int l, int r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        for (int tx = this->N-1-r; tx >= l; --tx) {
            for (int ty = u; ty < this->N-d; ++ty) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx) + abs(y-ty)*2;
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int ty = y+1; ty < this->N-d; ++ty) {
            if (grid[ty][x] == tg[y][x]) {
                rx = x;
                ry = ty;
                return;
            }
        }
    }
    
    void searchLU (int x, int y, int& rx, int& ry, int u, int d, int l, int r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        int dist = 1000000;
        for (int tx = this->N-1-r; tx >= l; --tx) {
            for (int ty = this->N-1-d; ty >= u; --ty) {
                if (grid[ty][tx] == tg[y][x] && grid[ty][tx] != tg[ty][tx]) {
                    int td = abs(x-tx) + abs(y-ty)*2;
                    if (td < dist) {
                        dist = td;
                        rx = tx;
                        ry = ty;
                    }
                }
            }
        }
        if (dist < 1000000) { return; }
        for (int ty = y-1; ty >= u; --ty) {
            if (grid[ty][x] == tg[y][x]) {
                rx = x;
                ry = ty;
                return;
            }
        }
    }
    
    
    void moveHW (int ax, int ay, int bx, int by, vector<YXYX>& r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        // b move
        // a goal
        while (bx != ax) {
            int nx = bx < ax ? bx + 1 : bx - 1;
            if (grid[by][bx] != grid[by][nx]) {
                r.emplace_back(by, bx, by, nx);
                swap(grid[by][bx], grid[by][nx]);
            }
            bx = nx;
        }
        while (by != ay) {
            int ny = by < ay ? by + 1 : by - 1;
            if (grid[by][bx] != grid[ny][bx]) {
                r.emplace_back(by, bx, ny, bx);
                swap(grid[by][bx], grid[ny][bx]);
            }
            by = ny;
        }
    }
    
    void moveHWR (int ax, int ay, int bx, int by, vector<YXYX>& r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        // b move
        // a goal
        
        while (abs(bx-ax) > 0 || abs(by-ay) > 1) {
            if (xrnd() % 2) {
                if (bx != ax) {
                    int nx = bx < ax ? bx + 1 : bx - 1;
                    if (grid[by][bx] != grid[by][nx]) {
                        r.emplace_back(by, bx, by, nx);
                        swap(grid[by][bx], grid[by][nx]);
                    }
                    bx = nx;
                }
            } else {
                if (abs(by-ay) > 1) {
                    int ny = by < ay ? by + 1 : by - 1;
                    if (grid[by][bx] != grid[ny][bx]) {
                        r.emplace_back(by, bx, ny, bx);
                        swap(grid[by][bx], grid[ny][bx]);
                    }
                    by = ny;
                }
            }
        }
        
        
        while (by != ay) {
            int ny = by < ay ? by + 1 : by - 1;
            if (grid[by][bx] != grid[ny][bx]) {
                r.emplace_back(by, bx, ny, bx);
                swap(grid[by][bx], grid[ny][bx]);
            }
            by = ny;
        }
    }
    
    void moveWHR (int ax, int ay, int bx, int by, vector<YXYX>& r, array< array<int, 30>, 30 >& tg, array< array<int, 30>, 30 >& grid) {
        // b move
        // a goal
        
        while (abs(bx-ax) > 1 || abs(by-ay) > 0) {
            if (xrnd() % 2) {
                if (abs(bx-ax) > 1) {
                    int nx = bx < ax ? bx + 1 : bx - 1;
                    if (grid[by][bx] != grid[by][nx]) {
                        r.emplace_back(by, bx, by, nx);
                        swap(grid[by][bx], grid[by][nx]);
                    }
                    bx = nx;
                }
            } else {
                if (by != ay) {
                    int ny = by < ay ? by + 1 : by - 1;
                    if (grid[by][bx] != grid[ny][bx]) {
                        r.emplace_back(by, bx, ny, bx);
                        swap(grid[by][bx], grid[ny][bx]);
                    }
                    by = ny;
                }
            }
        }
        
        while (bx != ax) {
            int nx = bx < ax ? bx + 1 : bx - 1;
            if (grid[by][bx] != grid[by][nx]) {
                r.emplace_back(by, bx, by, nx);
                swap(grid[by][bx], grid[by][nx]);
            }
            bx = nx;
        }
    }
    
    void output () {
        
        array< array<int, 30>, 30 > grid = this->grid;
        vector<YXYX> out;
        while (this->componentCnt(grid) > this->C) {
            YXYX t = this->best[out.size()];
            out.emplace_back(t);
            swap(grid[t.a][t.b], grid[t.c][t.d]);
            
            if (this->sw.get_milli_time() > 9800) {
                out = this->best;
                break;
            }
        }
        
        
        // pdebug("[", this->best.size()-out.size(), "]");
        
        
        pdebug(this->sw.get_milli_time());
        
        cout << out.size() << endl;
        for (auto&& i : out) { cout << i << endl; }
        
        cout.flush();
    }
    
    int componentCnt (array< array<int, 30>, 30 >& g) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        static array< array<int, 30>, 30 > fg;
        static vector<e512pos> q;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                fg[y][x] = 0;
            }
        }
        int cnt = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (fg[y][x] == 1) { continue; }
                cnt += 1;
                const int n = g[y][x];
                q.clear();
                q.emplace_back(x, y);
                fg[y][x] = 1;
                while (q.size() > 0) {
                    e512pos p = q.back();
                    q.pop_back();
                    for (int i = 0; i < 4; ++i) {
                        const int px = dx[i] + p.x;
                        const int py = dy[i] + p.y;
                        if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                        if (fg[py][px] == 1 || g[py][px] != n) { continue; }
                        q.emplace_back(px, py);
                        fg[py][px] = 1;
                    }
                }
            }
        }
        return cnt;
    }
    
    
};

int main()  {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solution();
    mm.output();
    
    // cout.flush();
}