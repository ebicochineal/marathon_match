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
#include <bitset>
#include <chrono>
#include <random>
using namespace std;

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char* v) { return "\"" + string(v) + "\""; }
string in_v_to_str (const string v) { return "\"" + v + "\""; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (size_t i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T, size_t N> string v_to_str (const array< array<T, N>, N >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (size_t i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (size_t i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (size_t i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
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
        size_t operator()(const e512pos& t) const{ return t.x<<16 | t.y; }
    };
}
ostream& operator << (ostream& os, const e512pos& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
};

const int adx[8] = { 1,-1, 1,-1, 1,-1, 1, 1};
const int ady[8] = { 0, 0, 0, 0, 1, 1, 1,-1};
const int bdx[8] = { 0, 0, 0, 0, 1,-1,-1,-1};
const int bdy[8] = { 1, 1,-1,-1,-1,-1, 1,-1};

const int dx[8] = { 0, 1, 0,-1, 1,-1, 1,-1};
const int dy[8] = {-1, 0, 1, 0,-1, 1, 1,-1};



// const int adx[8] = { 1, 0,-1, 0, 1, 1,-1,-1};
// const int ady[8] = { 0, 1, 0,-1,-1, 1, 1,-1};
// const int bdx[8] = { 0,-1, 0, 1, 1,-1,-1, 1};
// const int bdy[8] = { 1, 0,-1, 0, 1, 1,-1,-1};


class StopWatch {
public:
    std::chrono::system_clock::time_point start, tstart, end;
    StopWatch () {
        this->start = std::chrono::system_clock::now();
    }
    inline void stop () {
        this->tstart = std::chrono::system_clock::now();
    }
    inline void resume () {
        this->start += std::chrono::system_clock::now() - this->tstart;
    }
    inline uint64_t get_milli_time () {
        this->end = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    }
};


inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}


int bbl;
int bbr;
int bbd;
int bbu;

inline bool insidexywh (int x, int y, int n) {
    return (0 <= x && x < n && 0 <= y && y < n);
}

inline bool bbinsidexywh (int x, int y, int n) {
    return (bbl <= x && x <= bbr && bbd <= y && y <= bbu);
}



class MM {
public:
    StopWatch sw;
    int N, M;
    vector<e512pos> v;
    
    vector<e512pos> out;
    vector<e512pos> bestout;
    array<bitset<64>, 64> grid;
    array<bitset<64>, 64> rawgrid;
    
    int C, S, Q, K;
    
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->M;
        for (int i = 0; i < this->M; ++i) {
            e512pos p;
            cin >> p.x >> p.y;
            this->v.emplace_back(p);
            this->rawgrid[p.y][p.x] = true;
        }
        
        this->C = (this->N - 1) / 2;
        this->S = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                int w = (x-this->C)*(x-this->C) + (y-this->C)*(y-this->C) + 1;
                this->S += w;
            }
        }
        this->Q = 0;
        for (auto&& i : this->v) {
            int w = (i.x-this->C)*(i.x-this->C) + (i.y-this->C)*(i.y-this->C) + 1;
            this->Q += w;
        }
        this->K = 1000000 * (((double)this->N*this->N)/((double)this->M));
    }
    void output () {
        cout << out.size()/4 << endl;
        
        for (int i = 0; i < out.size(); i+=4) {
            cout << print(out[i].x, out[i].y, out[i+1].x, out[i+1].y, out[i+2].x, out[i+2].y, out[i+3].x, out[i+3].y) << endl;
        }
    }
    
    
    void solve () {
        vector<e512pos> bestout;
        
        // this->beamsearch(512);
        this->maximize_sa(4800, 5126, 0);
        // int tmpscore = this->calcscore(this->out);
        // vector<e512pos> tmp = this->out;
        // int s = min((int)this->out.size() / 4, 32);
        // for (int i = 0; i < s; ++i) {
        //     this->out.pop_back();
        //     this->out.pop_back();
        //     this->out.pop_back();
        //     this->out.pop_back();
        // }
        // this->beamsearch(64);
        
        // if (tmpscore > this->calcscore(this->out)) {
        //     this->out = tmp;
        // } else {
        //     pdebug(this->calcscore(this->out) - tmpscore);
        // }
        
        
        pdebug(this->sw.get_milli_time());
    }
    
    void maximize_sa (int etime, double stemp = 256.0, double etemp = 0.0) {
        array< bitset<64>, 64> ls;
        // for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 64; ++x) {
                ls[x].reset();
            }
        // }
        
        
        this->initlist(ls);
        
        
        vector<e512pos> vv;
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                vv.emplace_back(x, y);
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                vv.emplace_back(x, y);
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                vv.emplace_back(x, y);
            }
        }
        
        // mt19937 mt(xrnd());
        // shuffle(vv.begin(), vv.end(), mt);
        int tbbl = this->N;
        int tbbr = 0;
        int tbbd = this->N;
        int tbbu = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->rawgrid[y][x] == false) { continue; }
                tbbl = min(x, tbbl);
                tbbr = max(x, tbbr);
                tbbd = min(y, tbbd);
                tbbu = max(y, tbbu);
            }
        }
        
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector<e512pos> bestv = this->out;
        double bestscore = this->calcscore(this->out);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        vector<int> a;
        vector<int> b;
        int m = 64;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            if (ntime >= etime*0.5) { m=32; }
            if (ntime >= etime*0.75) { m=16; }
            for (int i = 0; i < 16; ++i) {
            
                a.clear();
                b.clear();
                for (int i = 0; i < m; ++i) {
                    a.emplace_back(xrnd() % (vv.size()));
                    b.emplace_back(xrnd() % vv.size());
                }
                for (int i = 0; i < m; ++i) {
                    swap(vv[a[i]], vv[b[i]]);
                }
                
                bbl = tbbl;
                bbr = tbbr;
                bbd = tbbd;
                bbu = tbbu;
                
                
                this->solve0(vv, 64, ls);
                double tmpscore = this->calcscore(this->out);
                const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestv = this->out;
                    }
                } else {
                    for (int i = 0; i < m; ++i) {
                        swap(vv[a[m-i-1]], vv[b[m-i-1]]);
                    }
                }
                cnt += 1;
            }
        }
        pdebug(cnt);
        this->out = bestv;
    }
    
    int calcscore (const vector<e512pos>& t) {
        int q = this->Q;
        for (int i = 0; i < t.size(); i+=4) {
            q += (t[i].x-this->C)*(t[i].x-this->C) + (t[i].y-this->C)*(t[i].y-this->C) + 1;
        }
        
        return this->K * ((double)q)/((double)S);
    }
    
    void solve0 (vector<e512pos>& vv, int m, array< bitset<64>, 64>& ls) {
        this->grid = this->rawgrid;
        this->out.clear();
        
        this->useedge.reset();
        
        
        for (int z = 0; z < 2; ++z) {
            for (auto&& u : vv) {
                int x = u.x;
                int y = u.y;
                if (this->isputls(x, y, ls) == false) { continue; }
                if (this->grid[y][x] == false) { continue; }
                bool lf = false;
                for (int d = 0; d < 8; ++d) {
                    
                    int ax = x + adx[d];
                    int ay = y + ady[d];
                    int bx = x + bdx[d];
                    int by = y + bdy[d];
                    if (!insidexywh(ax, ay, this->N) || !insidexywh(bx, by, this->N)) { continue; }
                    if (this->isdedge(x, y, ax, ay) || this->isdedge(x, y, bx, by)) { continue; }
                    while (true) {
                        if (this->grid[ay][ax] == true) { break; }
                        ax += adx[d];
                        ay += ady[d];
                        if (!bbinsidexywh(ax, ay, this->N)) { break; }
                    }
                    if (!insidexywh(ax, ay, this->N)) { continue; }
                    if (this->grid[ay][ax] != true) { continue; }
                    while (true) {
                        if (this->grid[by][bx] == true) { break; }
                        bx += bdx[d];
                        by += bdy[d];
                        if (!bbinsidexywh(bx, by, this->N)) { break; }
                    }
                    if (!insidexywh(bx, by, this->N)) { continue; }
                    if (this->grid[by][bx] != true) { continue; }
                    int cx = ax + bx - x;
                    int cy = ay + by - y;
                    if (this->isdedge(ax, ay, ax+bdx[d], ay+bdy[d])) { continue; }
                    if (this->isdedge(bx, by, bx+adx[d], by+ady[d])) { continue; }
                    if (insidexywh(cx, cy, this->N) && this->grid[cy][cx] == false) {
                        bool ff = true;
                        int tx, ty;
                        tx = ax;
                        ty = ay;
                        while (tx != cx || ty != cy) {
                            tx += bdx[d];
                            ty += bdy[d];
                            if (this->grid[ty][tx] == true) {
                                ff = false;
                                break;
                            }
                        }
                        if (ff == false) { continue; }
                        tx = bx;
                        ty = by;
                        while (tx != cx || ty != cy) {
                            tx += adx[d];
                            ty += ady[d];
                            if (this->grid[ty][tx] == true) {
                                ff = false;
                                break;
                            }
                        }
                        if (ff == false) { continue; }
                        this->out.emplace_back(cx, cy);
                        this->out.emplace_back(bx, by);
                        this->out.emplace_back(x, y);
                        this->out.emplace_back(ax, ay);
                        
                        this->setedge(x, y, ax, ay);
                        this->setedge(x, y, bx, by);
                        this->setedge(ax, ay, cx, cy);
                        this->setedge(bx, by, cx, cy);
                        
                        this->grid[cy][cx] = true;
                        this->update(cx, cy, ls);
                        
                        bbl = min(cx, bbl);
                        bbr = max(cx, bbr);
                        bbd = min(cy, bbd);
                        bbu = max(cy, bbu);
                        
                        
                        lf = true;
                        break;
                    }
                }
            
                if (lf) { break; }
            }
        }
        
        int lm;
        lm = 1;
        for (auto&& u : vv) {
            int x = u.x;
            int y = u.y;
            if (this->isputls(x, y, ls) == false) { continue; }
            if (this->grid[y][x] == false) { continue; }
            
            for (int d = 0; d < 8; ++d) {
                int ax = x + adx[d];
                int ay = y + ady[d];
                int bx = x + bdx[d];
                int by = y + bdy[d];
                if (!insidexywh(ax, ay, this->N) || !insidexywh(bx, by, this->N)) { continue; }
                if (this->isdedge(x, y, ax, ay) || this->isdedge(x, y, bx, by)) { continue; }
                
                if (this->grid[ay][ax] == false || this->grid[by][bx] == false) { continue; }
                
                int cx = ax + bx - x;
                int cy = ay + by - y;
                
                if (this->isdedge(ax, ay, ax+bdx[d], ay+bdy[d])) { continue; }
                if (this->isdedge(bx, by, bx+adx[d], by+ady[d])) { continue; }
                if (insidexywh(cx, cy, this->N) && this->grid[cy][cx] == false) {
                    
                    this->out.emplace_back(cx, cy);
                    this->out.emplace_back(bx, by);
                    this->out.emplace_back(x, y);
                    this->out.emplace_back(ax, ay);
                    
                    this->setedge(x, y, ax, ay);
                    this->setedge(x, y, bx, by);
                    this->setedge(ax, ay, cx, cy);
                    this->setedge(bx, by, cx, cy);
                    
                    this->grid[cy][cx] = true;
                    
                    bbl = min(cx, bbl);
                    bbr = max(cx, bbr);
                    bbd = min(cy, bbd);
                    bbu = max(cy, bbu);
                    
                    this->update(cx, cy, ls);
                }
            }
            
        }
        
        
        lm = m;
        for (auto&& u : vv) {
            int x = u.x;
            int y = u.y;
            if (this->isputls(x, y, ls) == false) { continue; }
            if (this->grid[y][x] == false) { continue; }
            
            for (int d = 0; d < 8; ++d) {
                int ax = x + adx[d];
                int ay = y + ady[d];
                int bx = x + bdx[d];
                int by = y + bdy[d];
                if (!insidexywh(ax, ay, this->N) || !insidexywh(bx, by, this->N)) { continue; }
                if (this->isdedge(x, y, ax, ay) || this->isdedge(x, y, bx, by)) { continue; }
                for (int i = 0; i < lm; ++i) {
                    if (this->grid[ay][ax] == true) { break; }
                    ax += adx[d];
                    ay += ady[d];
                    if (!bbinsidexywh(ax, ay, this->N)) { break; }
                }
                if (!insidexywh(ax, ay, this->N)) { continue; }
                if (this->grid[ay][ax] != true) { continue; }
                for (int i = 0; i < lm; ++i) {
                    if (this->grid[by][bx] == true) { break; }
                    bx += bdx[d];
                    by += bdy[d];
                    if (!bbinsidexywh(bx, by, this->N)) { break; }
                }
                if (!insidexywh(bx, by, this->N)) { continue; }
                if (this->grid[by][bx] != true) { continue; }
                int cx = ax + bx - x;
                int cy = ay + by - y;
                if (this->isdedge(ax, ay, ax+bdx[d], ay+bdy[d])) { continue; }
                if (this->isdedge(bx, by, bx+adx[d], by+ady[d])) { continue; }
                int e = d < 4 ? max(abs(x-ax), abs(x-bx)) * max(abs(y-ay), abs(y-by)) : max(abs(x-ax) * abs(x-bx), abs(y-ay) * abs(y-by));
                if (e <= lm && insidexywh(cx, cy, this->N) && this->grid[cy][cx] == false) {
                    bool ff = true;
                    int tx, ty;
                    tx = ax;
                    ty = ay;
                    while (tx != cx || ty != cy) {
                        tx += bdx[d];
                        ty += bdy[d];
                        if (this->grid[ty][tx] == true) {
                            ff = false;
                            break;
                        }
                    }
                    if (ff == false) { continue; }
                    tx = bx;
                    ty = by;
                    while (tx != cx || ty != cy) {
                        tx += adx[d];
                        ty += ady[d];
                        if (this->grid[ty][tx] == true) {
                            ff = false;
                            break;
                        }
                    }
                    if (ff == false) { continue; }
                    this->out.emplace_back(cx, cy);
                    this->out.emplace_back(bx, by);
                    this->out.emplace_back(x, y);
                    this->out.emplace_back(ax, ay);
                    
                    this->setedge(x, y, ax, ay);
                    this->setedge(x, y, bx, by);
                    this->setedge(ax, ay, cx, cy);
                    this->setedge(bx, by, cx, cy);
                    
                    this->grid[cy][cx] = true;
                    
                    bbl = min(cx, bbl);
                    bbr = max(cx, bbr);
                    bbd = min(cy, bbd);
                    bbu = max(cy, bbu);
                    
                    
                    this->update(cx, cy, ls);
                }
            }
            
        }
        
        
        for (auto&& u : vv) {
            int x = u.x;
            int y = u.y;
            if (this->isputls(x, y, ls) == false) { continue; }
            if (this->grid[y][x] == false) { continue; }
            
            
            for (int d = 0; d < 8; ++d) {
                int ax = x + adx[d];
                int ay = y + ady[d];
                int bx = x + bdx[d];
                int by = y + bdy[d];
                if (!insidexywh(ax, ay, this->N) || !insidexywh(bx, by, this->N)) { continue; }
                if (this->isdedge(x, y, ax, ay) || this->isdedge(x, y, bx, by)) { continue; }
                while (true) {
                    if (this->grid[ay][ax] == true) { break; }
                    ax += adx[d];
                    ay += ady[d];
                    if (!bbinsidexywh(ax, ay, this->N)) { break; }
                }
                if (!insidexywh(ax, ay, this->N)) { continue; }
                if (this->grid[ay][ax] != true) { continue; }
                while (true) {
                    if (this->grid[by][bx] == true) { break; }
                    bx += bdx[d];
                    by += bdy[d];
                    if (!bbinsidexywh(bx, by, this->N)) { break; }
                }
                if (!insidexywh(bx, by, this->N)) { continue; }
                if (this->grid[by][bx] != true) { continue; }
                int cx = ax + bx - x;
                int cy = ay + by - y;
                if (this->isdedge(ax, ay, ax+bdx[d], ay+bdy[d])) { continue; }
                if (this->isdedge(bx, by, bx+adx[d], by+ady[d])) { continue; }
                if (insidexywh(cx, cy, this->N) && this->grid[cy][cx] == false) {
                    bool ff = true;
                    int tx, ty;
                    tx = ax;
                    ty = ay;
                    while (tx != cx || ty != cy) {
                        tx += bdx[d];
                        ty += bdy[d];
                        if (this->grid[ty][tx] == true) {
                            ff = false;
                            break;
                        }
                    }
                    if (ff == false) { continue; }
                    tx = bx;
                    ty = by;
                    while (tx != cx || ty != cy) {
                        tx += adx[d];
                        ty += ady[d];
                        if (this->grid[ty][tx] == true) {
                            ff = false;
                            break;
                        }
                    }
                    if (ff == false) { continue; }
                    this->out.emplace_back(cx, cy);
                    this->out.emplace_back(bx, by);
                    this->out.emplace_back(x, y);
                    this->out.emplace_back(ax, ay);
                    
                    this->setedge(x, y, ax, ay);
                    this->setedge(x, y, bx, by);
                    this->setedge(ax, ay, cx, cy);
                    this->setedge(bx, by, cx, cy);
                    
                    this->grid[cy][cx] = true;
                    
                    bbl = min(cx, bbl);
                    bbr = max(cx, bbr);
                    bbd = min(cy, bbd);
                    bbu = max(cy, bbu);
                    
                    this->update(cx, cy, ls);
                }
            }
            
        }
        
    }
    
    inline bool isputls (int& px, int& py, array< bitset<64>, 64>& ls) {
        // return ls[py][px];
        return true;
    }
    inline void update (int& px, int& py, array< bitset<64>, 64>& ls) {
        
        
        
        
        
    }
    
    void initlist (array< bitset<64>, 64>& ls) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->rawgrid[y][x] == false) { continue; }
                for (int d = 0; d < 8; ++d) {
                    int ax = x + adx[d];
                    int ay = y + ady[d];
                    int bx = x + bdx[d];
                    int by = y + bdy[d];
                    if (!insidexywh(ax, ay, this->N) || !insidexywh(bx, by, this->N)) { continue; }
                    while (true) {
                        if (this->rawgrid[ay][ax] == true) { break; }
                        ax += adx[d];
                        ay += ady[d];
                        if (!insidexywh(ax, ay, this->N)) { break; }
                    }
                    if (!insidexywh(ax, ay, this->N)) { continue; }
                    while (true) {
                        if (this->rawgrid[by][bx] == true) { break; }
                        bx += bdx[d];
                        by += bdy[d];
                        if (!insidexywh(bx, by, this->N)) { break; }
                    }
                    if (!insidexywh(bx, by, this->N)) { continue; }
                    int cx = ax + bx - x;
                    int cy = ay + by - y;
                    if (insidexywh(cx, cy, this->N) && this->rawgrid[cy][cx] == false) {
                        bool ff = true;
                        int tx, ty;
                        tx = ax;
                        ty = ay;
                        while (tx != cx || ty != cy) {
                            tx += bdx[d];
                            ty += bdy[d];
                            if (this->rawgrid[ty][tx] == true) {
                                ff = false;
                                break;
                            }
                        }
                        if (ff == false) { continue; }
                        tx = bx;
                        ty = by;
                        while (tx != cx || ty != cy) {
                            tx += adx[d];
                            ty += ady[d];
                            if (this->rawgrid[ty][tx] == true) {
                                ff = false;
                                break;
                            }
                        }
                        if (ff == false) { continue; }
                        
                        
                        ls[cy][cx] = true;
                    }
                }
            }
        }
    }
    
    bitset<16384> useedge;
    
    inline bool isdedge (int ax, int ay, int bx, int by) {
        // 4096
        if (ax == bx) {// v
            if (ay > by) { swap(ay, by); }
            int t = ax;
            
            for (int i = ay; i < by; ++i) {
                if (this->useedge[t+i*64]) { return true; }
            }
            return false;
        }
        if (ay == by) {// h
            if (ax > bx) { swap(ax, bx); }
            int t = 4096 + 64 * ay;
            for (int i = ax; i < bx; ++i) {
                if (this->useedge[t+i]) { return true; }
            }
            return false;
        }
        
        if (ax > bx) {
            swap(ax, bx);
            swap(ay, by);
        }
        
        if (by < ay) {// /
            int t = 8192 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                if (this->useedge[t+i]) { return true; }
                t -= 64;
            }
            return false;
        } else  {//
            int t = 12288 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                if (this->useedge[t+i]) { return true; }
                t += 64;
            }
            return false;
        }
        return false;
    }
    
    
    inline void setedge (int ax, int ay, int bx, int by) {
        // 4096
        if (ax == bx) {// v
            if (ay > by) { swap(ay, by); }
            int t = ax;
            for (int i = ay; i < by; ++i) {
                this->useedge[t+i*64] = true;
            }
            return;
        }
        if (ay == by) {// h
            if (ax > bx) { swap(ax, bx); }
            int t = 4096 + 64 * ay;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = true;
            }
            return;
        }
        
        if (ax > bx) {
            swap(ax, bx);
            swap(ay, by);
        }
        
        if (by < ay) {// /
            int t = 8192 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = true;
                t -= 64;
            }
            return;
        } else  {//
            int t = 12288 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = true;
                t += 64;
            }
            return;
        }
    }
    
    
    
    inline void unsetedge (int ax, int ay, int bx, int by) {
        // 4096
        if (ax == bx) {// v
            if (ay > by) { swap(ay, by); }
            int t = ax;
            for (int i = ay; i < by; ++i) {
                this->useedge[t+i*64] = false;
            }
            return;
        }
        if (ay == by) {// h
            if (ax > bx) { swap(ax, bx); }
            int t = 4096 + 64 * ay;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = false;
            }
            return;
        }
        
        if (ax > bx) {
            swap(ax, bx);
            swap(ay, by);
        }
        
        if (by < ay) {// /
            int t = 8192 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = false;
                t -= 64;
            }
            return;
        } else  {//
            int t = 12288 + ay * 64;
            for (int i = ax; i < bx; ++i) {
                this->useedge[t+i] = false;
                t += 64;
            }
            return;
        }
    }
    
    
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    cout.flush();
    return 0;
}

