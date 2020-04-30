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

struct pd {
public:
    int x;
    int y;
    int d;
    int cost = 100000;
    pd () { this->x = -1; this->y = -1; this->d = -1; }
    pd (int x, int y, int d, int cost) {
        this->x = x;
        this->y = y;
        this->d = d;
        this->cost = cost;
    }
    bool operator == (const pd& t) const { return this->x == t.x && this->y == t.y && this->d == t.d; }
};
namespace std {
    template <> class hash<pd> {
    public:
        size_t operator()(const pd& t) const{ return hash<int>()(t.d<<8) | hash<int>()(t.x<<8) | hash<int>()(t.y); }
    };
}


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

class RCSD {
public:
    int x = 0;
    int y = 0;
    int s = 0;
    int d = 0;// R0, L1
    RCSD () {}
    RCSD (int x, int y, int s, int d) {
        this->x = x;
        this->y = y;
        this->s = s;
        this->d = d;
    }
    
    
    
};

int g_flpow[45] = {0, 0, 1, 2, 5, 8, 11, 14, 18, 22, 27, 31, 36, 41, 46, 52, 58, 64, 70, 76, 82, 89, 96, 103, 110, 117, 125, 132, 140, 148, 156, 164, 172, 181, 189, 198, 207, 216, 225, 234, 243, 252, 262, 272, 281};
int g_rgrid[40][40];
bool g_notmove[40][40];
int g_div[1600];
int g_mod[1600];
int g_dy[4] = {-1, 0, 1, 0};
int g_dx[4] = {0, 1, 0, -1};
class RotatingNumbers {
public:
    int N, P;
    vector<int> rawgrid;
    StopWatch sw;
    int mtime = 0;
    vector<string> findSolution(int N, int P, vector<int> grid) {
        this->sw = StopWatch();
        this->N = N;
        this->P = P;
        this->rawgrid = grid;
        
        for (int i = 0; i < 1600; ++i) {
            g_div[i] = i / this->N;
            g_mod[i] = i % this->N;
        }
        
        
        int cnt = 0;
        
        vector<RCSD> t;
        int bestscore = this->test0(t);
        vector<RCSD> bestret = t;
        while (this->sw.get_milli_time() < 9000) {
            this->mtime = this->sw.get_milli_time();
            t.clear();
            int tscore = this->test1(t);
            if (tscore < bestscore) {
                bestscore = tscore;
                bestret = t;
            }
            cnt += 1;
        }
        this->bestScoreRet(bestret);
        while (this->sw.get_milli_time() < 9250 && bestret.size() > 0) {
            auto t = bestret[bestret.size()-1];
            bestret.pop_back();
            int tscore = this->allScore(bestret);
            if (tscore < bestscore) {
                bestscore = tscore;
            } else {
                bestret.emplace_back(t);
            }
        }
        while (this->sw.get_milli_time() < 9500) {
            int x = xrnd() % (this->N - 1);
            int y = xrnd() % (this->N - 1);
            int s = max(2, (int)(xrnd() % (this->N - max(x, y) + 1)));
            int d = xrnd() % 2;
            bestret.emplace_back(x, y, s, d);
            int tscore = this->allScore(bestret);
            if (tscore < bestscore) {
                bestscore = tscore;
            } else {
                bestret.pop_back();
            }
        }
        
        
        
        
        pdebug("N =", N, "P =", P);
        pdebug(cnt, this->sw.get_milli_time());
        return this->out(bestret);
        
        // vector<RCSD> t;
        // vector<int> g = this->rawgrid;
        // pdebug(g[(this->N-1)+this->N*(this->N-1)]);
        // pdebug(this->freeGreedyMove(g, t, 0, 0, 0, 0, this->N-1, this->N-1));
        // return out(t);
        
    }
    
    int test0 (vector<RCSD>& r) {
        this->gmove02X(this->rawgrid, r);
        
        
        
        
        return this->allScore(r);
    }
    
    int test1 (vector<RCSD>& r) {
        vector<int> g = this->rawgrid;
        int c = xrnd() % 8;
        
        for (int i = 0; i < c; ++i) {
            int s = max(2, (int)(xrnd() % max(this->N/8, 1)));
            int px = xrnd() % (this->N-s+1);
            int py = xrnd() % (this->N-s+1);
            
            if (xrnd()%2 == 0) {
                this->rotR(px, py, s, g);
                r.emplace_back(px, py, s, 0);
            } else {
                this->rotL(px, py, s, g);
                r.emplace_back(px, py, s, 1);
            }
        }
        int bestscore = this->allScore(r);
        auto bestret = r;
        
        // {
        //     auto tret = r;
        //     int score = this->gmove01(g, tret);
        //     if (score < bestscore) {
        //         bestscore = score;
        //         bestret = tret;
        //     }
        // }
        // {
        //     auto tret = r;
        //     int score = this->gmove02(g, tret);
        //     if (score < bestscore) {
        //         bestscore = score;
        //         bestret = tret;
        //     }
        // }
        {
            auto tret = r;
            int score = this->gmove01X(g, tret);
            if (score < bestscore) {
                bestscore = score;
                bestret = tret;
            }
        }
        {
            auto tret = r;
            int score = this->gmove02X(g, tret);
            if (score < bestscore) {
                bestscore = score;
                bestret = tret;
            }
        }
        r = bestret;
        return bestscore;
    }
    // ---
        void pxpySet (int x, int y, int& px, int& py, vector<int>& grid) {
            const int NN = this->N * this->N;
            const int t = y * this->N + x + 1;
            for (int i = 0; i < NN; ++i) {
                if (grid[i] == t) {
                    px = g_mod[i];
                    py = g_div[i];
                    return;
                }
            }
        }
        
        
        
        
        inline int subGridScore (const vector<int>& grid, const int& px, const int& py, const int& sgs) {
            const int ex = px + sgs;
            const int ey = py + sgs;
            int r = g_flpow[sgs];
            
            for (int y = py; y < ey; ++y) {
                for (int x = px; x < ex; ++x) {
                    r += this->dist(grid, x, y);
                }
            }
            return r;
        }
        
        void lastX (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
            int vx = abs(x - px);
            int vy = abs(y - py);
            if (vy == 1) {
                if (px < this->N-1) {
                    this->rotL(px, py, 2, grid);
                    v.emplace_back(px, py, 2, 1);
                } else {
                    this->rotR(px-1, py, 2, grid);
                    v.emplace_back(px-1, py, 2, 0);
                }
                
                py += 1;
                vy = 2;
            }
            
            this->freeGreedyMove(grid, v, x, y+2, px, py);
            py = y+2;
            px = x;
            
            
            this->rotR(px-1, py-2, 2, grid);
            v.emplace_back(px-1, py-2, 2, 0);
            this->rotL(px-1, py-1, 2, grid);
            v.emplace_back(px-1, py-1, 2, 1);
            this->rotL(px-1, py-2, 2, grid);
            v.emplace_back(px-1, py-2, 2, 1);
        }
        
        void lastY (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
            
            int vx = abs(x - px);
            int vy = abs(y - py);
            
            if (vx == 1) {// right
                if (py < this->N-1) {
                    this->rotR(px, py, 2, grid);
                    v.emplace_back(px, py, 2, 0);
                } else {
                    this->rotL(px, py-1, 2, grid);
                    v.emplace_back(px, py-1, 2, 1);
                }
                px += 1;
                vx = 2;
            }
            
            this->freeGreedyMove(grid, v, x+2, y, px, py);
            py = y;
            px = x+2;
            
            this->rotL(px-2, py-1, 2, grid);
            v.emplace_back(px-2, py-1, 2, 1);
            this->rotR(px-1, py-1, 2, grid);
            v.emplace_back(px-1, py-1, 2, 0);
            this->rotR(px-2, py-1, 2, grid);
            v.emplace_back(px-2, py-1, 2, 0);
        }
        
        void lastXR (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
            int vx = abs(x - px);
            int vy = abs(y - py);
            if (vy == 1) {
                if (px < this->N-1) {
                    this->rotL(px, py, 2, grid);
                    v.emplace_back(px, py, 2, 1);
                } else {
                    this->rotR(px-1, py, 2, grid);
                    v.emplace_back(px-1, py, 2, 0);
                }
                
                py += 1;
                vy = 2;
            }
            
            this->freeGreedyMove(grid, v, x, y+2, px, py);
            py = y+2;
            px = x;
            
            
            this->rotL(px, py-2, 2, grid);
            v.emplace_back(px, py-2, 2, 1);
            this->rotR(px, py-1, 2, grid);
            v.emplace_back(px, py-1, 2, 0);
            this->rotR(px, py-2, 2, grid);
            v.emplace_back(px, py-2, 2, 0);
        }
        
        void lastYR (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
            
            int vx = abs(x - px);
            int vy = abs(y - py);
            
            if (vx == 1) {// right
                if (py < this->N-1) {
                    this->rotR(px, py, 2, grid);
                    v.emplace_back(px, py, 2, 0);
                } else {
                    this->rotL(px, py-1, 2, grid);
                    v.emplace_back(px, py-1, 2, 1);
                }
                px += 1;
                vx = 2;
            }
            
            this->freeGreedyMove(grid, v, x+2, y, px, py);
            py = y;
            px = x+2;
            
            this->rotR(px-2, py, 2, grid);
            v.emplace_back(px-2, py, 2, 0);
            this->rotL(px-1, py, 2, grid);
            v.emplace_back(px-1, py, 2, 1);
            this->rotL(px-2, py, 2, grid);
            v.emplace_back(px-2, py, 2, 1);
        }
        
        bool isOutSide (int x, int y, int n) {
            return (x < this->minx || y < this->miny || x+n > this->maxx || y+n > this->maxy);
        }
        bool isOutSideCol (int x, int y, int n) {
            if (x < this->minx || y < this->miny || x+n > this->maxx || y+n > this->maxy) { return true; }
            
            for (int py = 0; py < n; ++py) {
                for (int px = 0; px < n; ++px) {
                    if (g_notmove[py+y][px+x] == true) { return true; }
                }
            }
            return false;
        }
        bool isCollision (int x, int y) {
            if (x < this->minx || y < this->miny || x >= this->maxx || y >= this->maxy) { return true; }
            if (g_notmove[y][x] == true) { return true; }
            
            return false;
        }
        
        int minx = 0;
        int miny = 0;
        int maxx = 40;
        int maxy = 40;
        
        bool isABNum (int x, int y, vector<int> g, int d) {
            const int nx = x + g_dx[d];
            const int ny = y + g_dy[d];
            const int a = this->N * y + x + 1;
            const int b = this->N * ny + nx + 1;
            return (g[this->N*y+x] == b && g[this->N*ny+nx] == a);
        }
        
        inline int dist (const vector<int>& grid, const int& px, const int& py) {
            const int k = grid[py*this->N+px]-1;
            const int kx = g_mod[k];
            const int ky = g_div[k];
            return (abs(kx-px) + abs(ky - py));
        }
    // ---
    
    
    int gmove01X (vector<int> grid, vector<RCSD>& v) {
        
        
        int d = min((int)(2+xrnd()%16), this->N);
        this->minx = 0;
        this->miny = 0;
        this->maxx = this->N;
        this->maxy = this->N;
        
        for (int y = 0; y < this->N-d; ++y) {
            auto av = v;
            auto agrid = grid;
            for (int x = 0; x < this->N; ++x) {
                int px, py;
                
                for (int z = 2; z < 4; ++z) {
                    if (x >= this->N - z) { break; }
                    
                    
                }
                
                
                this->pxpySet(x, y, px, py, agrid);
                this->minx = 0;
                this->miny = y+1;
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == this->N - 1 && y < this->N-2) {
                    this->lastX(agrid, av, x, y, px, py);
                    continue;
                }
                if (x == this->N - 2 && !this->isABNum(x, y, agrid, 1)) {
                    
                    this->pxpySet(x+1, y, px, py, agrid);
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 1)) {
                                this->rotR(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove1(agrid, av, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x, y+1, px, py);
                        this->rotR(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x, y+1, px, py);
                    this->rotR(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 0);
                    break;
                }
                
                
                
                if (x <= this->N - 5) {
                    bool fa = abs(y - py) > 2;//
                    this->pxpySet(x+1, y, px, py, agrid);//
                    bool fb = abs(y - py) > 1;//
                    bool fbb = px <= x;//
                    this->pxpySet(x+2, y, px, py, agrid);//
                    bool fc = px <= x;//
                    this->pxpySet(x, y, px, py, agrid);//
                    if (fa && fb && fc && fbb) {
                        this->miny = y;//
                        this->notMoveClear();//
                        for (int i = 0; i < x; ++i) { g_notmove[y][i] = true; }
                        
                        this->pxpySet(x+2, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y, px, py);
                        g_notmove[y][x] = true;
                        
                        this->pxpySet(x+1, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y+1, px, py);
                        g_notmove[y+1][x] = true;
                        
                        this->pxpySet(x, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y+2, px, py);
                        g_notmove[y+2][x] = true;
                        
                        this->rotR(x, y, 3, agrid);
                        av.emplace_back(x, y, 3, 0);
                        x+=2;
                        continue;
                    }
                }
                if (x <= this->N - 4) {
                    bool fa = x < px;
                    this->pxpySet(x+1, y, px, py, agrid);
                    bool fb = abs(py - y) > 0;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->miny = y;
                        this->notMoveClear();
                        for (int i = 0; i < x; ++i) {
                            g_notmove[y][i] = true;
                        }
                        this->freeGreedyMoveCol(agrid, av, x+1, y, px, py);
                        this->pxpySet(x+1, y, px, py, agrid);
                        g_notmove[y][x+1] = true;
                        if (this->freeGreedyMoveCol(agrid, av, x+1, y+1, px, py)) {
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            x += 1;
                            continue;
                        } else {
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            continue;
                        }
                    }
                }
                
                if (x <= this->N - 4) {
                    bool fa = abs(y - py) > 0;
                    this->pxpySet(x+1, y, px, py, agrid);
                    bool fb = px <= x;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->pxpySet(x+1, y, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x, y+1, px, py);
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, agrid);
                        if (abs(y+1 - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x, y+1, px, py);
                        }
                        
                        this->rotR(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 0);
                        x+=1;
                        continue;
                    }
                }
                
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove1(agrid, av, px, py, 2);
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int x = this->N-1; x >= 0; --x) {
                int px, py;
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = 0;
                this->miny = y+1;
                
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == 0 && y < this->N-2) {
                    this->lastXR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (x == 1 && !this->isABNum(x, y, bgrid, 3)) {
                    this->pxpySet(x-1, y, px, py, bgrid);
                    
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 3)) {
                                this->rotL(x-1, y, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove2(bgrid, bv, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                        this->rotL(x-1, y, 2, bgrid);
                        bv.emplace_back(x-1, y, 2, 1);
                    }
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                    this->rotL(x-1, y, 2, bgrid);
                    bv.emplace_back(x-1, y, 2, 1);
                    break;
                }
                
                if (x >= 4) {
                    bool fa = abs(y - py) > 2;//
                    this->pxpySet(x-1, y, px, py, bgrid);//
                    bool fb = abs(y - py) > 1;//
                    bool fbb = px >= x;//
                    this->pxpySet(x-2, y, px, py, bgrid);//
                    bool fc = px >= x;//
                    this->pxpySet(x, y, px, py, bgrid);//
                    if (fa && fb && fc && fbb) {
                        this->miny = y;//
                        this->notMoveClear();//
                        for (int i = this->N-1; i > x; --i) { g_notmove[y][i] = true; }//
                        
                        this->pxpySet(x-2, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y, px, py);//
                        g_notmove[y][x] = true;//
                        
                        this->pxpySet(x-1, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y+1, px, py);//
                        g_notmove[y+1][x] = true;//
                        
                        this->pxpySet(x, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y+2, px, py);//
                        g_notmove[y+2][x] = true;//
                        
                        this->rotL(x-2, y, 3, bgrid);//
                        bv.emplace_back(x-2, y, 3, 1);//
                        x-=2;//
                        continue;
                    }
                }
                
                if (x >= 3) {
                    bool fa = x > px;//
                    this->pxpySet(x-1, y, px, py, bgrid);//
                    bool fb = abs(py - y) > 0;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->miny = y;
                        this->notMoveClear();
                        for (int i = this->N-1; i >= x ; --i) {//
                            g_notmove[y][i] = true;
                        }
                        this->freeGreedyMoveCol(bgrid, bv, x-1, y, px, py);//
                        this->pxpySet(x-1, y, px, py, bgrid);//
                        g_notmove[y][x-1] = true;//
                        if (this->freeGreedyMoveCol(bgrid, bv, x-1, y+1, px, py)) {//
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            x -= 1;//
                            continue;
                        } else {
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            continue;
                        }
                    }
                }
                if (x >= 3) {
                    bool fa = abs(y - py) > 0;
                    this->pxpySet(x-1, y, px, py, bgrid);
                    bool fb = px >= x;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->pxpySet(x-1, y, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                            this->rotL(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 1);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, bgrid);
                        if (abs(y+1 - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                        }
                        
                        this->rotL(x-1, y, 2, bgrid);
                        bv.emplace_back(x-1, y, 2, 1);
                        x-=1;
                        continue;
                    }
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove2(bgrid, bv, px, py, 2);
            }
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
        }
        
        for (int x = 0; x < this->N-2; ++x) {
            auto av = v;
            auto agrid = grid;
            
            for (int y = this->N-d; y < this->N; ++y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, agrid);
                this->minx = x+1;
                this->miny = this->N-d;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == this->N - 1 && x < this->N-2) {
                    this->lastY(agrid, av, x, y, px, py);
                    continue;
                }
                
                if (y == this->N - 2 && x < this->N-2 && !this->isABNum(x, y, agrid, 2)) {
                    
                    this->pxpySet(x, y+1, px, py, agrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 2)) {
                                this->rotL(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove1(agrid, av, px, py, 2);
                                } else {
                                    this->freeGreedyMove(agrid, av, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x+1, y, px, py);
                        this->rotL(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 1);
                        
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                    this->rotL(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 1);
                    break;
                }
                
                if (y <= this->N - 5) {
                    bool fa = abs(x - px) > 2;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = abs(x - px) > 1;
                    bool fbb = py <= y;
                    this->pxpySet(x, y+2, px, py, agrid);
                    bool fc = py <= y;
                    this->pxpySet(x, y, px, py, agrid);//
                    if (fa && fb && fc && fbb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = 0; i < y; ++i) { g_notmove[i][x] = true; }
                        
                        this->pxpySet(x, y+2, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y, px, py);
                        g_notmove[y][x] = true;
                        
                        this->pxpySet(x, y+1, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x+1, y, px, py);
                        g_notmove[y][x+1] = true;
                        
                        this->pxpySet(x, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x+2, y, px, py);
                        g_notmove[y][x+2] = true;
                        
                        this->rotL(x, y, 3, agrid);
                        av.emplace_back(x, y, 3, 1);
                        y+=2;
                        continue;
                    }
                }
                
                if (y <= this->N - 4) {
                    bool fa = y < py;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = abs(px - x) > 0;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = 0; i < y; ++i) {
                            g_notmove[i][x] = true;
                        }
                        this->freeGreedyMoveCol(agrid, av, x, y+1, px, py);
                        this->pxpySet(x, y+1, px, py, agrid);
                        g_notmove[y+1][x] = true;
                        if (this->freeGreedyMoveCol(agrid, av, x+1, y+1, px, py)) {
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            y += 1;
                            continue;
                        } else {
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            continue;
                        }
                    }
                }
                
                if (y <= this->N - 4) {
                    bool fa = abs(x - px) > 0;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = py <= y;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->pxpySet(x, y+1, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x+1, y, px, py);
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                        }
                        
                        this->pxpySet(x, y, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x+1 - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x+1, y, px, py);
                        }
                        
                        this->rotL(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 1);
                        y+=1;
                        continue;
                    }
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(agrid, av, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove1(agrid, av, px, py, 2);
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int y = this->N-1; y >= this->N-d; --y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = x+1;
                this->miny = this->N-d;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == this->N-d && x < this->N-2) {
                    this->lastYR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (y == this->N-d+1 && x < this->N-2  && !this->isABNum(x, y, bgrid, 0)) {
                    this->pxpySet(x, y-1, px, py, bgrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 0)) {
                                this->rotR(x, y-1, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove2(bgrid, bv, px, py, 2);
                                } else {
                                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                        this->rotR(x, y-1, 2, bgrid);
                        bv.emplace_back(x, y-1, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                    this->rotR(x, y-1, 2, bgrid);
                    bv.emplace_back(x, y-1, 2, 0);
                    break;
                }
                
                if (y >= 4) {
                    bool fa = abs(x - px) > 2;
                    this->pxpySet(x, y-1, px, py, bgrid);
                    bool fb = abs(x - px) > 1;
                    bool fbb = py >= y;
                    this->pxpySet(x, y-2, px, py, bgrid);
                    bool fc = py >= y;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb && fc && fbb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = this->N-1; i > y; --i) { g_notmove[i][x] = true; }//
                        
                        this->pxpySet(x, y-2, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y, px, py);//
                        g_notmove[y][x] = true;//
                        
                        this->pxpySet(x, y-1, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x+1, y, px, py);//
                        g_notmove[y][x+1] = true;//
                        
                        this->pxpySet(x, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x+2, y, px, py);//
                        g_notmove[y][x+2] = true;//
                        
                        this->rotR(x, y-2, 3, bgrid);//
                        bv.emplace_back(x, y-2, 3, 0);//
                        y-=2;//
                        continue;
                    }
                }
                
                if (y >= 3) {
                    bool fa = y > py;//
                    this->pxpySet(x, y-1, px, py, bgrid);//
                    bool fb = abs(px - x) > 0;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = this->N-1; i >= y ; --i) {//
                            g_notmove[i][x] = true;
                        }
                        this->freeGreedyMoveCol(bgrid, bv, x, y-1, px, py);//
                        this->pxpySet(x, y-1, px, py, bgrid);//
                        g_notmove[y-1][x] = true;//
                        if (this->freeGreedyMoveCol(bgrid, bv, x+1, y-1, px, py)) {//
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            y -= 1;//
                            continue;
                        } else {
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            continue;
                        }
                    }
                }
                if (y >= 3) {
                    bool fa = abs(x - px) > 0;
                    this->pxpySet(x, y-1, px, py, bgrid);
                    bool fb = py >= y;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->pxpySet(x, y-1, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                            this->rotR(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 0);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x+1 - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                        }
                        
                        this->rotR(x, y-1, 2, bgrid);
                        bv.emplace_back(x, y-1, 2, 0);
                        y-=1;
                        continue;
                    }
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove2(bgrid, bv, px, py, 2);
                
            }
            
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
            
        }
        
        for (int y = this->N-d; y < this->N-2; ++y) {
            auto av = v;
            auto agrid = grid;
            for (int x = this->N-2; x < this->N; ++x) {
                int px, py;
                this->pxpySet(x, y, px, py, agrid);
                this->minx = this->N-2;
                this->miny = y+1;
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == this->N - 1 && y < this->N-2) {
                    this->lastX(agrid, av, x, y, px, py);
                    continue;
                }
                
                if (x == this->N - 2 && !this->isABNum(x, y, agrid, 1)) {
                    
                    this->pxpySet(x+1, y, px, py, agrid);
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 1)) {
                                this->rotR(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove1(agrid, av, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x, y+1, px, py);
                        this->rotR(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x, y+1, px, py);
                    this->rotR(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 0);
                    break;
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove1(agrid, av, px, py, 2);
                
                
                
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int x = this->N-1; x >= this->N-2; --x) {
                int px, py;
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = this->N-2;
                this->miny = y+1;
                
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == this->N-2 && y < this->N-2) {
                    this->lastXR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (x == this->N-1 && !this->isABNum(x, y, bgrid, 3)) {
                    this->pxpySet(x-1, y, px, py, bgrid);
                    
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 3)) {
                                this->rotL(x-1, y, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove2(bgrid, bv, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                        this->rotL(x-1, y, 2, bgrid);
                        bv.emplace_back(x-1, y, 2, 1);
                    }
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                    this->rotL(x-1, y, 2, bgrid);
                    bv.emplace_back(x-1, y, 2, 1);
                    break;
                }
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove2(bgrid, bv, px, py, 2);
            }
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
        }
        
        return this->allGridScore(v, grid);
        
    }
    
    
    int gmove02X (vector<int> grid, vector<RCSD>& v) {
        int d = min((int)(2+xrnd()%16), this->N);
        this->minx = 0;
        this->miny = 0;
        this->maxx = this->N;
        this->maxy = this->N;
        for (int x = 0; x < this->N-d; ++x) {
            auto av = v;
            auto agrid = grid;
            
            for (int y = 0; y < this->N; ++y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, agrid);
                this->minx = x+1;
                this->miny = 0;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == this->N - 1 && x < this->N-2) {
                    this->lastY(agrid, av, x, y, px, py);
                    continue;
                }
                
                if (y == this->N - 2 && x < this->N-2 && !this->isABNum(x, y, agrid, 2)) {
                    
                    this->pxpySet(x, y+1, px, py, agrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 2)) {
                                this->rotL(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove1(agrid, av, px, py, 2);
                                } else {
                                    this->freeGreedyMove(agrid, av, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x+1, y, px, py);
                        this->rotL(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 1);
                        
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                    this->rotL(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 1);
                    break;
                }
                
                if (y <= this->N - 5) {
                    bool fa = abs(x - px) > 2;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = abs(x - px) > 1;
                    bool fbb = py <= y;
                    this->pxpySet(x, y+2, px, py, agrid);
                    bool fc = py <= y;
                    this->pxpySet(x, y, px, py, agrid);//
                    if (fa && fb && fc && fbb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = 0; i < y; ++i) { g_notmove[i][x] = true; }
                        
                        this->pxpySet(x, y+2, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y, px, py);
                        g_notmove[y][x] = true;
                        
                        this->pxpySet(x, y+1, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x+1, y, px, py);
                        g_notmove[y][x+1] = true;
                        
                        this->pxpySet(x, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x+2, y, px, py);
                        g_notmove[y][x+2] = true;
                        
                        this->rotL(x, y, 3, agrid);
                        av.emplace_back(x, y, 3, 1);
                        y+=2;
                        continue;
                    }
                }
                
                if (y <= this->N - 4) {
                    bool fa = y < py;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = abs(px - x) > 0;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = 0; i < y; ++i) {
                            g_notmove[i][x] = true;
                        }
                        this->freeGreedyMoveCol(agrid, av, x, y+1, px, py);
                        this->pxpySet(x, y+1, px, py, agrid);
                        g_notmove[y+1][x] = true;
                        if (this->freeGreedyMoveCol(agrid, av, x+1, y+1, px, py)) {
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            y += 1;
                            continue;
                        } else {
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            continue;
                        }
                    }
                }
                
                
                if (y <= this->N - 4) {
                    bool fa = abs(x - px) > 0;
                    this->pxpySet(x, y+1, px, py, agrid);
                    bool fb = py <= y;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->pxpySet(x, y+1, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x+1, y, px, py);
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                        }
                        
                        this->pxpySet(x, y, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x+1 - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x+1, y, px, py);
                        }
                        
                        this->rotL(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 1);
                        y+=1;
                        continue;
                    }
                }
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(agrid, av, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove1(agrid, av, px, py, 2);
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int y = this->N-1; y >= 0; --y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = x+1;
                this->miny = 0;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == 0 && x < this->N-2) {
                    this->lastYR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (y == 1 && x < this->N-2  && !this->isABNum(x, y, bgrid, 0)) {
                    this->pxpySet(x, y-1, px, py, bgrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 0)) {
                                this->rotR(x, y-1, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove2(bgrid, bv, px, py, 2);
                                } else {
                                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                        this->rotR(x, y-1, 2, bgrid);
                        bv.emplace_back(x, y-1, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                    this->rotR(x, y-1, 2, bgrid);
                    bv.emplace_back(x, y-1, 2, 0);
                    break;
                }
                
                
                if (y >= 4) {
                    bool fa = abs(x - px) > 2;
                    this->pxpySet(x, y-1, px, py, bgrid);
                    bool fb = abs(x - px) > 1;
                    bool fbb = py >= y;
                    this->pxpySet(x, y-2, px, py, bgrid);
                    bool fc = py >= y;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb && fc && fbb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = this->N-1; i > y; --i) { g_notmove[i][x] = true; }//
                        
                        this->pxpySet(x, y-2, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y, px, py);//
                        g_notmove[y][x] = true;//
                        
                        this->pxpySet(x, y-1, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x+1, y, px, py);//
                        g_notmove[y][x+1] = true;//
                        
                        this->pxpySet(x, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x+2, y, px, py);//
                        g_notmove[y][x+2] = true;//
                        
                        this->rotR(x, y-2, 3, bgrid);//
                        bv.emplace_back(x, y-2, 3, 0);//
                        y-=2;//
                        continue;
                    }
                }
                
                
                if (y >= 3) {
                    bool fa = y > py;//
                    this->pxpySet(x, y-1, px, py, bgrid);//
                    bool fb = abs(px - x) > 0;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->minx = x;
                        this->notMoveClear();
                        for (int i = this->N-1; i >= y ; --i) {//
                            g_notmove[i][x] = true;
                        }
                        this->freeGreedyMoveCol(bgrid, bv, x, y-1, px, py);//
                        this->pxpySet(x, y-1, px, py, bgrid);//
                        g_notmove[y-1][x] = true;//
                        if (this->freeGreedyMoveCol(bgrid, bv, x+1, y-1, px, py)) {//
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            y -= 1;//
                            continue;
                        } else {
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            continue;
                        }
                    }
                }
                
                if (y >= 3) {
                    bool fa = abs(x - px) > 0;
                    this->pxpySet(x, y-1, px, py, bgrid);
                    bool fb = py >= y;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->pxpySet(x, y-1, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                            this->rotR(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 0);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x+1 - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                        }
                        
                        this->rotR(x, y-1, 2, bgrid);
                        bv.emplace_back(x, y-1, 2, 0);
                        y-=1;
                        continue;
                    }
                }
                
                
                
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove2(bgrid, bv, px, py, 2);
                
            }
            
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
            
        }
        
        for (int y = 0; y < this->N-2; ++y) {
            auto av = v;
            auto agrid = grid;
            for (int x = this->N-d; x < this->N; ++x) {
                int px, py;
                this->pxpySet(x, y, px, py, agrid);
                this->minx = this->N-d;
                this->miny = y+1;
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == this->N - 1 && y < this->N-2) {
                    this->lastX(agrid, av, x, y, px, py);
                    continue;
                }
                
                if (x == this->N - 2 && !this->isABNum(x, y, agrid, 1)) {
                    
                    this->pxpySet(x+1, y, px, py, agrid);
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 1)) {
                                this->rotR(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove1(agrid, av, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x, y+1, px, py);
                        this->rotR(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x, y+1, px, py);
                    this->rotR(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 0);
                    break;
                }
                
                
                if (x <= this->N - 5) {
                    bool fa = abs(y - py) > 2;//
                    this->pxpySet(x+1, y, px, py, agrid);//
                    bool fb = abs(y - py) > 1;//
                    bool fbb = px <= x;//
                    this->pxpySet(x+2, y, px, py, agrid);//
                    bool fc = px <= x;//
                    this->pxpySet(x, y, px, py, agrid);//
                    if (fa && fb && fc && fbb) {
                        this->miny = y;//
                        this->notMoveClear();//
                        for (int i = 0; i < x; ++i) { g_notmove[y][i] = true; }
                        
                        this->pxpySet(x+2, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y, px, py);
                        g_notmove[y][x] = true;
                        
                        this->pxpySet(x+1, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y+1, px, py);
                        g_notmove[y+1][x] = true;
                        
                        this->pxpySet(x, y, px, py, agrid);
                        this->freeGreedyMoveCol(agrid, av, x, y+2, px, py);
                        g_notmove[y+2][x] = true;
                        
                        this->rotR(x, y, 3, agrid);
                        av.emplace_back(x, y, 3, 0);
                        x+=2;
                        continue;
                    }
                }
                
                if (x <= this->N - 4) {
                    bool fa = x < px;
                    this->pxpySet(x+1, y, px, py, agrid);
                    bool fb = abs(py - y) > 0;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->miny = y;
                        this->notMoveClear();
                        for (int i = 0; i < x; ++i) {
                            g_notmove[y][i] = true;
                        }
                        this->freeGreedyMoveCol(agrid, av, x+1, y, px, py);
                        this->pxpySet(x+1, y, px, py, agrid);
                        g_notmove[y][x+1] = true;
                        if (this->freeGreedyMoveCol(agrid, av, x+1, y+1, px, py)) {
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            x += 1;
                            continue;
                        } else {
                            this->rotL(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 1);
                            continue;
                        }
                    }
                }
                
                if (x <= this->N - 4) {
                    bool fa = abs(y - py) > 0;
                    this->pxpySet(x+1, y, px, py, agrid);
                    bool fb = px <= x;
                    this->pxpySet(x, y, px, py, agrid);
                    if (fa && fb) {
                        this->pxpySet(x+1, y, px, py, agrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x, y+1, px, py);
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, agrid);
                        if (abs(y+1 - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(agrid, av, x, y+1, px, py);
                        }
                        
                        this->rotR(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 0);
                        x+=1;
                        continue;
                    }
                }
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(agrid, av, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove1(agrid, av, px, py, 2);
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int x = this->N-1; x >= this->N-d; --x) {
                int px, py;
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = this->N-d;
                this->miny = y+1;
                
                if (x == px && y == py) { continue; }
                if (y > py) { continue; }
                if (x == this->N-d && y < this->N-2) {
                    this->lastXR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (x == this->N-d+1 && !this->isABNum(x, y, bgrid, 3)) {
                    this->pxpySet(x-1, y, px, py, bgrid);
                    
                    if (abs(y - py) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 3)) {
                                this->rotL(x-1, y, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                                px = x;
                                py = y+1;
                                this->upMove2(bgrid, bv, px, py, 2);
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                        this->rotL(x-1, y, 2, bgrid);
                        bv.emplace_back(x-1, y, 2, 1);
                    }
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                    this->rotL(x-1, y, 2, bgrid);
                    bv.emplace_back(x-1, y, 2, 1);
                    break;
                }
                
                
                if (x >= 4) {
                    bool fa = abs(y - py) > 2;//
                    this->pxpySet(x-1, y, px, py, bgrid);//
                    bool fb = abs(y - py) > 1;//
                    bool fbb = px >= x;//
                    this->pxpySet(x-2, y, px, py, bgrid);//
                    bool fc = px >= x;//
                    this->pxpySet(x, y, px, py, bgrid);//
                    if (fa && fb && fc && fbb) {
                        this->miny = y;//
                        this->notMoveClear();//
                        for (int i = this->N-1; i > x; --i) { g_notmove[y][i] = true; }//
                        
                        this->pxpySet(x-2, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y, px, py);//
                        g_notmove[y][x] = true;//
                        
                        this->pxpySet(x-1, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y+1, px, py);//
                        g_notmove[y+1][x] = true;//
                        
                        this->pxpySet(x, y, px, py, bgrid);//
                        this->freeGreedyMoveCol(bgrid, bv, x, y+2, px, py);//
                        g_notmove[y+2][x] = true;//
                        
                        this->rotL(x-2, y, 3, bgrid);//
                        bv.emplace_back(x-2, y, 3, 1);//
                        x-=2;//
                        continue;
                    }
                }
                
                
                if (x >= 3) {
                    bool fa = x > px;//
                    this->pxpySet(x-1, y, px, py, bgrid);//
                    bool fb = abs(py - y) > 0;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->miny = y;
                        this->notMoveClear();
                        for (int i = this->N-1; i >= x ; --i) {//
                            g_notmove[y][i] = true;
                        }
                        this->freeGreedyMoveCol(bgrid, bv, x-1, y, px, py);//
                        this->pxpySet(x-1, y, px, py, bgrid);//
                        g_notmove[y][x-1] = true;//
                        if (this->freeGreedyMoveCol(bgrid, bv, x-1, y+1, px, py)) {//
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            x -= 1;//
                            continue;
                        } else {
                            this->rotR(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 0);
                            continue;
                        }
                    }
                }
                if (x >= 3) {
                    bool fa = abs(y - py) > 0;
                    this->pxpySet(x-1, y, px, py, bgrid);
                    bool fb = px >= x;
                    this->pxpySet(x, y, px, py, bgrid);
                    if (fa && fb) {
                        this->pxpySet(x-1, y, px, py, bgrid);
                        if (abs(y - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                            this->rotL(x-1, y, 2, bgrid);
                            bv.emplace_back(x-1, y, 2, 1);
                        }
                        
                        
                        this->pxpySet(x, y, px, py, bgrid);
                        if (abs(y+1 - py) == 0 && abs(x - px) == 0) {
                        } else {
                            this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                        }
                        
                        this->rotL(x-1, y, 2, bgrid);
                        bv.emplace_back(x-1, y, 2, 1);
                        x-=1;
                        continue;
                    }
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vy == 0) {
                    this->miny = y;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                
                this->freeGreedyMove(bgrid, bv, x, y+1, px, py);
                px = x;
                py = y+1;
                this->upMove2(bgrid, bv, px, py, 2);
            }
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
        }
        
        for (int x = this->N-d; x < this->N-2; ++x) {
            auto av = v;
            auto agrid = grid;
            
            for (int y = this->N-d; y < this->N; ++y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, agrid);
                this->minx = x+1;
                this->miny = this->N-2;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == this->N - 1 && x < this->N-2) {
                    this->lastY(agrid, av, x, y, px, py);
                    continue;
                }
                
                if (y == this->N - 2 && x < this->N-2 && !this->isABNum(x, y, agrid, 2)) {
                    
                    this->pxpySet(x, y+1, px, py, agrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotR(x, y, 2, agrid);
                            av.emplace_back(x, y, 2, 0);
                            
                            ///
                            if (this->isABNum(x, y, agrid, 2)) {
                                this->rotL(x, y, 2, agrid);
                                av.pop_back();
                                this->pxpySet(x, y, px, py, agrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove1(agrid, av, px, py, 2);
                                } else {
                                    this->freeGreedyMove(agrid, av, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                        }
                    } else {
                        this->freeGreedyMove(agrid, av, x+1, y, px, py);
                        this->rotL(x, y, 2, agrid);
                        av.emplace_back(x, y, 2, 1);
                        
                    }
                    
                    this->pxpySet(x, y, px, py, agrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(agrid, av, x+1, y, px, py);
                    this->rotL(x, y, 2, agrid);
                    av.emplace_back(x, y, 2, 1);
                    break;
                }
                
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(agrid, av, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(agrid, av, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove1(agrid, av, px, py, 2);
            }
            
            auto bv = v;
            auto bgrid = grid;
            for (int y = this->N-1; y >= this->N-d; --y) {
                int px, py;
                
                this->pxpySet(x, y, px, py, bgrid);
                this->minx = x+1;
                this->miny = this->N-2;
                if (x == px && y == py) { continue; }
                if (x > px) { continue; }
                if (y == this->N-2 && x < this->N-2) {
                    this->lastYR(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                if (y == this->N-1 && x < this->N-2  && !this->isABNum(x, y, bgrid, 0)) {
                    this->pxpySet(x, y-1, px, py, bgrid);
                    if (abs(x - px) == 0) {
                        if (x == px && y == py) {
                            
                        } else{
                            this->rotL(x, y-1, 2, bgrid);
                            bv.emplace_back(x, y-1, 2, 1);
                            
                            ///
                            if (this->isABNum(x, y, bgrid, 0)) {
                                this->rotR(x, y-1, 2, bgrid);
                                bv.pop_back();
                                this->pxpySet(x, y, px, py, bgrid);
                                
                                if (x < this->N-2) {
                                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                                    px = x+1;
                                    py = y;
                                    this->leftMove2(bgrid, bv, px, py, 2);
                                } else {
                                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                                }
                                continue;
                            }
                            ///
                            
                        }
                    } else {
                        this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                        this->rotR(x, y-1, 2, bgrid);
                        bv.emplace_back(x, y-1, 2, 0);
                    }
                    
                    this->pxpySet(x, y, px, py, bgrid);
                    if (x == px && y == py) { break; }
                    this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                    this->rotR(x, y-1, 2, bgrid);
                    bv.emplace_back(x, y-1, 2, 0);
                    break;
                }
                
                
                int vx = abs(x - px);
                int vy = abs(y - py);
                
                
                if (vx == 0) {
                    this->minx = x;
                    this->freeGreedyMove(bgrid, bv, x, y, px, py);
                    continue;
                }
                
                this->freeGreedyMove(bgrid, bv, x+1, y, px, py);
                px = x+1;
                py = y;
                this->leftMove2(bgrid, bv, px, py, 2);
                
            }
            
            
            if (this->allGridScore(av, agrid) < this->allGridScore(bv, bgrid)){
                v = av;
                grid = agrid;
            } else {
                v = bv;
                grid = bgrid;
            }
            
        }
        
        return this->allGridScore(v, grid);
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void gridFDebug (vector<int>& grid) {
        for (int y = 0; y < this->N; ++y) {
            vector<int> t ;
            for (int x = 0; x < this->N; ++x) {
                t.emplace_back(grid[x+this->N*y]);
            }
            fdebug(t);
        }
        fdebug(" ");
        
        
        
    }
    
    bool freeGreedyMove (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
        
        if (x == px && y == py) { return true; }
        
        int vx = abs(x - px);
        int vy = abs(y - py);
        int t = 6;
        t += xrnd() % 8;
        t = min(this->N, t);
        if (this->mtime > 7500) { t = 4; }
        while (vy + vx > 0) {
            int bestscore = 100000;
            int best = -1;
            int bestsize = 2;
            for (int s = 2; s < t; ++s) {
                if (vx >= s-1) {
                    if (x < px) {// left
                        int a = this->leftMoveCost1(grid, px, py, s);
                        int b = this->leftMoveCost2(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 0;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 1;
                                bestsize = s;
                            }
                        }
                    } else {
                        int a = this->rightMoveCost1(grid, px, py, s);
                        int b = this->rightMoveCost2(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 2;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 3;
                                bestsize = s;
                            }
                        }
                    }
                }
                if (vy >= s-1) {
                    if (y < py) {// up
                        int a = this->upMoveCost1(grid, px, py, s);
                        int b = this->upMoveCost2(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 4;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 5;
                                bestsize = s;
                            }
                        }
                    } else {
                        int a = this->downMoveCost1(grid, px, py, s);
                        int b = this->downMoveCost2(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 6;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 7;
                                bestsize = s;
                            }
                        }
                    }
                }
            }
            
            
            if (best == 0) { this->leftMove1(grid, v, px, py, bestsize);  vx -= bestsize - 1; }
            if (best == 1) { this->leftMove2(grid, v, px, py, bestsize);  vx -= bestsize - 1; }
            if (best == 2) { this->rightMove1(grid, v, px, py, bestsize); vx -= bestsize - 1; }
            if (best == 3) { this->rightMove2(grid, v, px, py, bestsize); vx -= bestsize - 1; }
            if (best == 4) { this->upMove1(grid, v, px, py, bestsize);    vy -= bestsize - 1; }
            if (best == 5) { this->upMove2(grid, v, px, py, bestsize);    vy -= bestsize - 1; }
            if (best == 6) { this->downMove1(grid, v, px, py, bestsize);  vy -= bestsize - 1; }
            if (best == 7) { this->downMove2(grid, v, px, py, bestsize);  vy -= bestsize - 1; }
            if (best == -1) { return false; }
        }
        
        return true;
    }
    
    bool freeGreedyMoveCol (vector<int>& grid, vector<RCSD>& v, int x, int y, int px, int py) {
        
        if (x == px && y == py) { return true; }
        
        int vx = abs(x - px);
        int vy = abs(y - py);
        int t = 6;
        t += xrnd() % 8;
        t = min(this->N, t);
        if (this->mtime > 7500) { t = 4; }
        while (vy + vx > 0) {
            int bestscore = 100000;
            int best = -1;
            int bestsize = 2;
            for (int s = 2; s < t; ++s) {
                if (vx >= s-1) {
                    if (x < px) {// left
                        int a = this->leftMoveCost1Col(grid, px, py, s);
                        int b = this->leftMoveCost2Col(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 0;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 1;
                                bestsize = s;
                            }
                        }
                    } else {
                        int a = this->rightMoveCost1Col(grid, px, py, s);
                        int b = this->rightMoveCost2Col(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 2;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 3;
                                bestsize = s;
                            }
                        }
                    }
                }
                if (vy >= s-1) {
                    if (y < py) {// up
                        int a = this->upMoveCost1Col(grid, px, py, s);
                        int b = this->upMoveCost2Col(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 4;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 5;
                                bestsize = s;
                            }
                        }
                    } else {
                        int a = this->downMoveCost1Col(grid, px, py, s);
                        int b = this->downMoveCost2Col(grid, px, py, s);
                        if (a < b) {
                            if (a < bestscore) {
                                bestscore = a;
                                best = 6;
                                bestsize = s;
                            }
                        } else {
                            if (b < bestscore) {
                                bestscore = b;
                                best = 7;
                                bestsize = s;
                            }
                        }
                    }
                }
            }
            
            
            if (best == 0) { this->leftMove1(grid, v, px, py, bestsize);  vx -= bestsize - 1; }
            if (best == 1) { this->leftMove2(grid, v, px, py, bestsize);  vx -= bestsize - 1; }
            if (best == 2) { this->rightMove1(grid, v, px, py, bestsize); vx -= bestsize - 1; }
            if (best == 3) { this->rightMove2(grid, v, px, py, bestsize); vx -= bestsize - 1; }
            if (best == 4) { this->upMove1(grid, v, px, py, bestsize);    vy -= bestsize - 1; }
            if (best == 5) { this->upMove2(grid, v, px, py, bestsize);    vy -= bestsize - 1; }
            if (best == 6) { this->downMove1(grid, v, px, py, bestsize);  vy -= bestsize - 1; }
            if (best == 7) { this->downMove2(grid, v, px, py, bestsize);  vy -= bestsize - 1; }
            if (best == -1) { return false; }
        }
        
        return true;
    }
    
    // move 2
        int leftMoveCost1 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int leftMoveCost2 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int rightMoveCost1 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int rightMoveCost2 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        void leftMove1 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            this->rotL(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 1);
            px -= d;
        }
        void leftMove2 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            this->rotR(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 0);
            px -= d;
        }
        void rightMove1 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            this->rotR(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 0);
            px += d;
        }
        void rightMove2 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            this->rotL(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 1);
            px += d;
        }
        
        int upMoveCost1 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            
            return r;
        }
        
        int upMoveCost2 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        void upMove1 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            this->rotR(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 0);
            py -= d;
        }
        void upMove2 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            this->rotL(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 1);
            py -= d;
        }
        
        int downMoveCost1 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int downMoveCost2 (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            if (this->isOutSide(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            return r;
        }
        
        void downMove1 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            this->rotL(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 1);
            py += d;
        }
        void downMove2 (vector<int>& grid, vector<RCSD>& v, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            this->rotR(rx, ry, s, grid);
            v.emplace_back(rx, ry, s, 0);
            py += d;
        }
        
        inline int cost (const int& s) {
            if (s >= 4) {
                return g_flpow[s] * 2;
            } else {
                return 0;
            }
        }
        
    //
    
    // move Col
        int leftMoveCost1Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int leftMoveCost2Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int rightMoveCost1Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int rightMoveCost2Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        int upMoveCost1Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py-d;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            
            
            return r;
        }
        
        int upMoveCost2Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py-d;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int downMoveCost1Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px;
            int ry = py;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            
            r += this->cost(s);
            
            return r;
        }
        
        int downMoveCost2Col (vector<int>& grid, int& px, int& py, int s) {
            const int d = s - 1;
            int rx = px-d;
            int ry = py;
            if (this->isOutSideCol(rx, ry, s)) { return 100000; }
            int r = 0;
            r -= this->subGridScore(grid, rx, ry, s);
            this->rotR(rx, ry, s, grid);
            r += this->subGridScore(grid, rx, ry, s);
            this->rotL(rx, ry, s, grid);
            
            r += this->cost(s);
            return r;
        }
        
    //
    
    void rotR (int px, int py, int s, vector<int>& grid) {
        for (int y = 0; y < s; ++y) {
            for (int x = 0; x < s; ++x) {
                g_rgrid[y][x] = grid[(py+y) * this->N + px+x];
            }
        }
        for (int y = 0; y < s; ++y) {
            for (int x = 0; x < s; ++x) {
                grid[(py+y) * this->N + px+x] = g_rgrid[s-x-1][y];
            }
        }
    }
    
    void rotL (int px, int py, int s, vector<int>& grid) {
        for (int y = 0; y < s; ++y) {
            for (int x = 0; x < s; ++x) {
                g_rgrid[y][x] = grid[(py+y) * this->N + px+x];
            }
        }
        for (int y = 0; y < s; ++y) {
            for (int x = 0; x < s; ++x) {
                grid[(py+y) * this->N + px+x] = g_rgrid[x][s-y-1];
            }
        }
    }
    
    int gridScore (vector<int>& grid) {
        int r = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                const int k = grid[y*this->N+x]-1;
                const int kx = g_mod[k];
                const int ky = g_div[k];
                r += (abs(kx-x) + abs(ky - y)) * this->P;
            }
        }
        return r;
    }
    
    
    void bestScoreRet (vector<RCSD>& v) {
        vector<int> g = this->rawgrid;
        int r = 0;
        vector<RCSD> bestv;
        vector<RCSD> tv;
        int bestscore = 100000;
        for (auto&& i : v) {
            tv.emplace_back(i);
            if (i.s > 0) {
                r += g_flpow[i.s];
                if (i.d == 0) {
                    this->rotR(i.x, i.y, i.s, g);
                } else {
                    this->rotL(i.x, i.y, i.s, g);
                }
                int score = this->gridScore(g) + r;
                if (score < bestscore) {
                    bestscore = score;
                    bestv = tv;
                }
            }
        }
        v = bestv;
    }
    
    int allScore (vector<RCSD>& v) {
        vector<int> t = this->rawgrid;
        int r = 0;
        for (auto&& i : v) {
            if (i.s > 0) {
                r += g_flpow[i.s];
                //r += floor(pow(i.s - 1, 1.5f));
                if (i.d == 0) {
                    this->rotR(i.x, i.y, i.s, t);
                } else {
                    this->rotL(i.x, i.y, i.s, t);
                }
            }
        }
        r += this->gridScore(t);
        return r;
    }
    
    int allGridScore (vector<RCSD>& v, vector<int>& g) {
        int r = 0;
        for (auto&& i : v) {
            r += g_flpow[i.s];
        }
        r += this->gridScore(g);
        return r;
    }
    
    
    void notMoveClear () {
        for (int y = 0; y < 40; ++y) {
            for (int x = 0; x < 40; ++x) {
                g_notmove[y][x] = false;
            }
        }
    }
    
    
    vector<string> out (vector<RCSD> v) {
        vector<string> r;
        for (auto&& i : v) {
            if (i.s > 0) { r.emplace_back(print(i.y, i.x, i.s, (i.d == 0 ? "R" : "L"))); }
        }
        return r;
    }
    
};

int main() {
    RotatingNumbers prog;
    int N;
    int P;
    int num;
    vector<int> grid;
    
    cin >> N;
    cin >> P;
    for (int i=0; i<N*N; i++) {
        cin >> num;
        grid.push_back(num);
    }
    
    vector<string> ret = prog.findSolution(N, P, grid);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
}