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


class NXN1 {
public:
    int x, y, n;
    vector< vector< vector<int> > > subgrid1;
    vector< vector< vector<int> > > subgrid2;
    int m1 = 0;
    int m2 = 0;
    
    NXN1 (int n){
        this->n = n;
        this->y = n / 2;
        this->x = y + 1;
        
        if (this->x % 2) {
            this->m2 = 1;
            this->xodd1();
            this->xodd2();
        } else {
            this->xeven1();
            this->xeven2();
        }
    }
    
    void xodd1 () {
        for (int j = 0; j < this->x/2; ++j) {
            for (int i = 0; i < this->y/2; ++i) {
                vector< vector<int> > b(this->y, vector<int>(this->x, -1));
                int sx = j * 2;
                int p = sx *this->y;
                this->vertical(b, 0, 0, sx, this->y, 0, 1);
                
                this->horizontal(b, sx, 0, this->x - sx, i*2, p, 1);
                this->vertical(b, sx, i*2, this->x - sx, this->y-i*2, (this->x - sx) * i*2 + p, 1);
                this->subgrid1.emplace_back(b);
            }
        }
        for (int i = 1; i < this->y/2; ++i) {
            vector< vector<int> > b(this->y, vector<int>(this->x, -1));
            
            this->vertical(b, 0, 0, this->x, i*2, 0, 1);
            this->horizontal(b, 0, i*2, this->x, this->y-i*2, this->x * i*2, 0);
            this->subgrid1.emplace_back(b);
        }
    }
    
    void xodd2 () {
        for (int j = 0; j < this->x/2-1; ++j) {
            for (int i = 0; i < this->y/2; ++i) {
                vector< vector<int> > a(this->y, vector<int>(this->x, -1));
                this->vertical(a, 0, 0, j*2, this->y, 0, 1);
                this->horizontal(a, j*2, 0, 2, this->y-1, j*2 * this->y, 1);
                int p = (this->y - 1) * 2 + j*2 * this->y;
                a[0][j*2+1] = p;
                
                int sx = j * 2;
                this->horizontalr(a, sx + 2, 0, this->x-2 - sx, 2*i, p + 1, 1);
                this->vertical(a, sx + 2, 0, this->x-2 - sx, this->y-i*2, (this->x-2-sx)*2*i + p + 1, 0);
                this->subgrid2.emplace_back(a);
            }
        }
    }
    
    void xeven1 () {
        for (int i = 0; i < this->x/2; ++i) {
            vector< vector<int> > b(this->y, vector<int>(this->x, -1));
            this->vertical(b, 0, 0, i*2, this->y, 0, 1);
            this->horizontal(b, i*2, 0, this->x-i*2, this->y, i*2 * this->y, 1);
            this->subgrid1.emplace_back(b);
        }
        
        
        for (int j = 0; j < this->y/2; ++j) {
            for (int i = 0; i < this->x-3; ++i) {
                vector< vector<int> > b(this->y, vector<int>(this->x, -1));
                int p;
                this->horizontal(b, 0, 0, 2, this->y - 2*j, 0, 1);
                p = 2 * (this->y - 2*j);
                this->horizontalr(b, 2, 2*j, i+1, this->y-2*j, p, 1);
                p = p + (i+1) * (this->y-2*j);
                this->horizontal(b, 2+i+1, 0, this->x-(2+i+1), this->y - 2*j, p, 1);
                p = this->y * this->x - 2*j * this->x;
                this->horizontal(b, 0, this->y - 2*j, this->x, 2*j, p, 0);
                
                this->subgrid1.emplace_back(b);
            }
        }
        for (int i = 1; i < this->x/2; ++i) {
            vector< vector<int> > b(this->y, vector<int>(this->x, -1));
            this->horizontal(b, 0, 0, i*2, this->y, 0, 1);
            this->vertical(b, i*2, 0, this->x-i*2, this->y, i*2*this->y, 0);
            
            this->subgrid1.emplace_back(b);
        }
        
        
    }
    void xeven2 () {
        for (int j = 0; j < this->x/2-1; ++j) {
            for (int i = 0; i < this->y/2+1; ++i) {
                vector< vector<int> > b(this->y, vector<int>(this->x, -1));
                this->vertical(b, 0, 0, j*2+1, this->y, 0, 1);
                
                int p = (j*2+1) * this->y;
                
                int sx = j*2+1;
                this->horizontalr(b, sx, 0, this->x - sx, 2*i, p, 1);
                this->vertical(b, sx, 0, this->x - sx, this->y-2*i, (this->x - sx)*2*i + p, 0);
                this->subgrid2.emplace_back(b);
            }
        }
        
    }
    
    void vertical (vector< vector<int> >& g, int sx, int sy, int w, int h, int n, int s) {
        for (int x = 0; x < w; ++x) {
            for (int y = 0; y < h; ++y) {
                if (x % 2 == s) {
                    g[this->y - sy - (h-1) + y - 1][sx + x] = n;
                } else {
                    g[this->y - sy - y - 1][sx + x] = n;
                }
                n += 1;
            }
        }
    }
    
    void horizontal (vector< vector<int> >& g, int sx, int sy, int w, int h, int n, int s) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (y % 2 == s) {
                    g[this->y - sy - y - 1][sx + (w-1) - x] = n;
                } else {
                    g[this->y - sy - y - 1][sx + x] = n;
                }
                n += 1;
            }
        }
        
    }
    void horizontalr (vector< vector<int> >& g, int sx, int sy, int w, int h, int n, int s) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (y % 2 == s) {
                    g[sy + y][sx + (w-1) - x] = n;
                } else {
                    g[sy + y][sx + x] = n;
                }
                n += 1;
            }
        }
    }
};
ostream& operator << (ostream& os, const NXN1& p) {
    os << p.n << " " << p.x << " " << p.y << " " << (p.x % 2 ? "ODD" : "EVEN") << "\n";
    os << p.subgrid1.size() << " " << p.subgrid2.size() << "\n";
    for (auto&& i : p.subgrid1) {
        for (auto&& j : i) { os << print(j) << "\n"; }
        os << "---" << endl;
    }
    // os << "-E-" << endl;
    // for (auto&& i : p.subgrid2) {
    //     for (auto&& j : i) { os << print(j) << "\n"; }
    //     os << "---" << endl;
    // }
    return os;
};


class SnakeCharmer {
public:
    int N, V, NN, HN;
    StopWatch sw;
    vector<int> snakev;
    
    
    
    vector<char> findSolution(int N, int V, string snake) {
        this->sw = StopWatch();
        this->N = N;
        this->HN = N / 2;
        this->NN = N * N;
        this->V = V;
        for (auto&& i : snake) { this->snakev.emplace_back(i-48); }
        
        vector<int> best(this->HN, 0);
        best = this->SA(6000, best);
        vector<char> bestret = this->solve11(best);
        int bestscore = this->solve00(best);
        
        if (N == 7) {
            for (int i = 0; i < this->NN-1; ++i) {
                vector< vector<int> > tmp = this->solve7x7(i);
                int tscore = this->indexgridscore(tmp);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestret = this->indexGridToCommand(tmp);
                }
            }
            for (int i = 0; i < this->NN-1; ++i) {
                vector< vector<int> > tmp = this->solve7x7_2(i);
                int tscore = this->indexgridscore(tmp);
                
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestret = this->indexGridToCommand(tmp);
                }
            }
        }
        
        if (N == 9) {
            for (int i = 0; i < this->NN-1; ++i) {
                vector< vector<int> > tmp = this->solve9x9(i);
                int tscore = this->indexgridscore(tmp);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestret = this->indexGridToCommand(tmp);
                }
            }
            for (int i = 0; i < this->NN-1; ++i) {
                vector< vector<int> > tmp = this->solve9x9_2(i);
                int tscore = this->indexgridscore(tmp);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestret = this->indexGridToCommand(tmp);
                }
            }
        }
        if (this->N > 7){
            NXN1 nxn1(this->N);
            NXN1 nxn2(this->N-2);
            for (int i = 0; i < this->NN-1; ++i) {
            
                {
                    vector< vector<int> > tmp = this->solveNxN(i, nxn1);
                    int tscore = this->indexgridscore(tmp);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestret = this->indexGridToCommand(tmp);
                    }
                }
                {
                    vector< vector<int> > tmp = this->solveNxN2(i, nxn2);
                    int tscore = this->indexgridscore(tmp);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestret = this->indexGridToCommand(tmp);
                    }
                }
                if (this->sw.get_milli_time() > 9800) { break; }
            }
            pdebug(bestscore);
        } else {
            NXN1 nxn1(this->N);
            for (int i = 0; i < this->NN-1; ++i) {
                {
                    vector< vector<int> > tmp = this->solveNxN(i, nxn1);
                    int tscore = this->indexgridscore(tmp);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestret = this->indexGridToCommand(tmp);
                    }
                }
                if (this->sw.get_milli_time() > 9800) { break; }
            }
            pdebug(bestscore);
        }
        
        pdebug(this->N, this->V, this->sw.get_milli_time());
        return bestret;
        
    }
    
    vector<int> SA (int limit, vector<int> ret) {
        StopWatch sw;
        
        vector<int> bestret = ret;
        double bestscore = 0;
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int a = xrnd() % this->HN;
                int b = xrnd() % this->HN;
                int tmpa = ret[a];
                int tmpb = ret[b];
                ret[a] = xrnd() % this->nlen(a+1);
                ret[b] = xrnd() % this->nlen(b+1);
                double tmpscore = this->solve00(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 64.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    ret[a] = tmpa;
                    ret[b] = tmpb;
                }
            }
            
        }
        
        return bestret;
    }
    
    
    char nextPL (int& x, int& y, int n) {
        int s = this->HN - n;
        int e = s + n * 2;
        char r = 'U';
        if (y == s && x < e) { r = 'R'; }
        if (x == e && y < e) { r = 'D'; }
        if (y == e && x > s) { r = 'L'; }
        if (x == s && y > s) { r = 'U'; }
        return r;
    }
    
    char nextPR (int& x, int& y, int n) {
        int s = this->HN - n;
        int e = s + n * 2;
        char r = 'U';
        if (x == s && y < e) { r = 'D'; }
        if (y == e && x < e) { r = 'R'; }
        if (x == e && y > s) { r = 'U'; }
        if (y == s && x > s) { r = 'L'; }
        return r;
    }
    
    vector<char> nextP (int& x, int& y, int n) {
        vector<char> r;
        int s = this->HN - n;
        int e = s + n * 2;
        if (n == 0) {
            r.emplace_back('U');
        } else {
            if (x == s) { r.emplace_back('L'); }
            if (x == e) { r.emplace_back('R'); }
            if (y == s) { r.emplace_back('U'); }
            if (y == e) { r.emplace_back('D'); }
        }
        return r;
    }
    
    void charpos (int& x, int& y, char c) {
        if (c == 'U') { y -=1; }
        if (c == 'D') { y +=1; }
        if (c == 'L') { x -=1; }
        if (c == 'R') { x +=1; }
        
    }
    
    int solve00 (vector<int> g) {
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, 0));
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, 0));
        int bestscore = 0;
        int px = this->HN;
        int py = this->HN;
        
        int cnt = 0;
        for (auto&& i : g) { cnt += i; }
        
        int sp = this->snakev.size()-1-cnt;
        grid[py][px] = this->snakev[sp];
        sp -= 1;
        for (int j = 0; j < this->HN; ++j) {
            int spx = px;
            int spy = py;
            for (auto&& i : this->nextP(px, py, j)) {
                {
                    int tsp = sp;
                    int tpx = spx;
                    int tpy = spy;
                    int ltpx = spx;
                    int ltpy = spy;
                    this->charpos(tpx, tpy, i);
                    for (int k = 0; k < this->nlen(j+1); ++k) {
                        if (k >= this->nlen(j+1) - g[j]) {
                            if (k > 0) { this->charpos(tpx, tpy, this->nextPL(tpx, tpy, j+1)); }
                            grid[tpy][tpx] = 0;
                        } else {
                            if (k > 0) { this->charpos(tpx, tpy, this->nextPL(tpx, tpy, j+1)); }
                            grid[tpy][tpx] = this->snakev[tsp-k];
                            ltpx = tpx;
                            ltpy = tpy;
                        }
                    }
                    
                    int tscore = this->score(grid);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestgrid = grid;
                        px = ltpx;
                        py = ltpy;
                    }
                }
                {
                    int tsp = sp;
                    int tpx = spx;
                    int tpy = spy;
                    int ltpx = spx;
                    int ltpy = spy;
                    this->charpos(tpx, tpy, i);
                    for (int k = 0; k < this->nlen(j+1); ++k) {
                        if (k >= this->nlen(j+1) - g[j]) {
                            if (k > 0) { this->charpos(tpx, tpy, this->nextPR(tpx, tpy, j+1)); }
                            grid[tpy][tpx] = 0;
                        } else {
                            if (k > 0) { this->charpos(tpx, tpy, this->nextPR(tpx, tpy, j+1)); }
                            grid[tpy][tpx] = this->snakev[tsp-k];
                            ltpx = tpx;
                            ltpy = tpy;
                        }
                    }
                    
                    int tscore = this->score(grid);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestgrid = grid;
                        px = ltpx;
                        py = ltpy;
                    }
                }
            }
            sp = sp - this->nlen(j+1) + g[j];
            grid = bestgrid;
            
        }
        
        //for (auto&& i : bestgrid) { fdebug(i); }
        
        
        return this->score(bestgrid);
        
    }
    
    vector<char> solve11 (vector<int> g) {
        vector<char> ret;
        
        
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, 0));
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, 0));
        int bestscore = 0;
        
        int px = this->HN;
        int py = this->HN;
        int cnt = 0;
        for (auto&& i : g) { cnt += i; }
        
        int sp = this->snakev.size()-1-cnt;
        grid[py][px] = this->snakev[sp];
        sp -= 1;
        for (int j = 0; j < this->HN; ++j) {
            int spx = px;
            int spy = py;
            vector<char> retadd;
            for (auto&& i : this->nextP(px, py, j)) {
                {
                    vector<char> tretadd;
                    int tsp = sp;
                    int tpx = spx;
                    int tpy = spy;
                    int ltpx = spx;
                    int ltpy = spy;
                        
                    this->charpos(tpx, tpy, i);
                    tretadd.emplace_back(i);
                    for (int k = 0; k < this->nlen(j+1); ++k) {
                        if (k >= this->nlen(j+1) - g[j]) {
                            if (k > 0) {
                                char t = this->nextPL(tpx, tpy, j+1);
                                this->charpos(tpx, tpy, t);
                            }
                            grid[tpy][tpx] = 0;
                        } else {
                            if (k > 0) {
                                char t = this->nextPL(tpx, tpy, j+1);
                                this->charpos(tpx, tpy, t);
                                tretadd.emplace_back(t);
                            }
                            grid[tpy][tpx] = this->snakev[tsp-k];
                            ltpx = tpx;
                            ltpy = tpy;
                        }
                        
                    }
                    int tscore = this->score(grid);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestgrid = grid;
                        px = ltpx;
                        py = ltpy;
                        retadd = tretadd;
                    }
                }
                {
                    vector<char> tretadd;
                    int tsp = sp;
                    int tpx = spx;
                    int tpy = spy;
                    int ltpx = spx;
                    int ltpy = spy;
                        
                    this->charpos(tpx, tpy, i);
                    tretadd.emplace_back(i);
                    for (int k = 0; k < this->nlen(j+1); ++k) {
                        if (k >= this->nlen(j+1) - g[j]) {
                            if (k > 0) {
                                char t = this->nextPR(tpx, tpy, j+1);
                                this->charpos(tpx, tpy, t);
                            }
                            grid[tpy][tpx] = 0;
                        } else {
                            if (k > 0) {
                                char t = this->nextPR(tpx, tpy, j+1);
                                this->charpos(tpx, tpy, t);
                                tretadd.emplace_back(t);
                            }
                            grid[tpy][tpx] = this->snakev[tsp-k];
                            ltpx = tpx;
                            ltpy = tpy;
                        }
                        
                    }
                    int tscore = this->score(grid);
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestgrid = grid;
                        px = ltpx;
                        py = ltpy;
                        retadd = tretadd;
                    }
                }
            }
            sp = sp - this->nlen(j+1) + g[j];
            grid = bestgrid;
            for (auto&& i : retadd) {
                ret.emplace_back(i);
            }
            
            
        }
        
        return ret;
    }
    
    int score (vector< vector<int> >& grid) {
        static int vt[10][5] = 
        {{ 0,  0,   0,    0,     0},
         { 0,  0,   0,    0,     0},
         { 2,  4,   8,   16,    32},
         { 3,  9,  27,   81,   243},
         { 4, 16,  64,  256,  1024},
         { 5, 25, 125,  625,  3125},
         { 6, 36, 216, 1296,  7776},
         { 7, 49, 343, 2401, 16807},
         { 8, 64, 512, 4096, 32768},
         { 9, 81, 729, 6561, 59049}};
        
        
        int r = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (grid[y][x] < 1) { continue; }
                int cnt = 0;
                cnt += (y - 1 >= 0 && grid[y-1][x] == grid[y][x]);
                cnt += (y + 1 < this->N && grid[y+1][x] == grid[y][x]);
                cnt += (x - 1 >= 0 && grid[y][x-1] == grid[y][x]);
                cnt += (x + 1 < this->N && grid[y][x+1] == grid[y][x]);
                r += vt[grid[y][x]][cnt];
                // int v = grid[y][x];
                // for (int i = 0; i < cnt; ++i) {
                //     v *= grid[y][x];
                // }
                // r += v;
            }
        }
        
        return r;
    }
    
    int indexgridscore (vector< vector<int> >& grid) {
        static int vt[10][5] = 
        {{ 0,  0,   0,    0,     0},
         { 0,  0,   0,    0,     0},
         { 2,  4,   8,   16,    32},
         { 3,  9,  27,   81,   243},
         { 4, 16,  64,  256,  1024},
         { 5, 25, 125,  625,  3125},
         { 6, 36, 216, 1296,  7776},
         { 7, 49, 343, 2401, 16807},
         { 8, 64, 512, 4096, 32768},
         { 9, 81, 729, 6561, 59049}};
        
        int r = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (grid[y][x] < 0) { continue; }
                int cnt = 0;
                cnt += (y - 1 >= 0      && grid[y-1][x] > -1 && this->snakev[grid[y-1][x]] == this->snakev[grid[y][x]]);
                cnt += (y + 1 < this->N && grid[y+1][x] > -1 && this->snakev[grid[y+1][x]] == this->snakev[grid[y][x]]);
                cnt += (x - 1 >= 0      && grid[y][x-1] > -1 && this->snakev[grid[y][x-1]] == this->snakev[grid[y][x]]);
                cnt += (x + 1 < this->N && grid[y][x+1] > -1 && this->snakev[grid[y][x+1]] == this->snakev[grid[y][x]]);
                r += vt[this->snakev[grid[y][x]]][cnt];
            }
        }
        return r;
    }
    
    int nlen (int n) {
        static int r[] = {1, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232};
        return r[n];
    }
    
    void zero (vector< vector<int> >& grid, int n) {
        // int t = n * 2;//  1 + n * 2 - 1;
        // int s = this->N / 2 - n;
        // if (n == 0) { grid[s][s] = 0; }
        // for (int i = 0; i < t; ++i) { grid[s][s+i] = 0; }
        // for (int i = 0; i < t; ++i) { grid[s+i][s+t] = 0; }
        // for (int i = 0; i < t; ++i) { grid[s+t][s+t-i] = 0; }
        // for (int i = 0; i < t; ++i) { grid[s+t-i][s] = 0; }
        int x = this->HN - n;
        int y = this->HN - n;
        for (int i = 0; i < this->nlen(n); ++i) {
            grid[y][x] = 0;
            this->charpos(x, y, this->nextPR(x, y, n));
        }
        
    }
    
    vector< vector<int> > solve7x7 (int n) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        vector< vector<int> > a34 = {{9, 10, 11, 12, 8, 7, 6, 5, 1, 2, 3, 4}
                                    ,{3, 4, 11, 12, 2, 5, 10, 9, 1, 6, 7, 8}
                                    ,{3, 4, 5, 12, 2, 7, 6, 11, 1, 8, 9, 10}
                                    ,{5, 6, 7, 12, 4, 3, 8, 11, 1, 2, 9, 10}
                                    ,{5, 6, 7, 12, 4, 3, 8, 11, 1, 2, 9, 10}};
        vector< vector<int> > al34 = {{3, 4, 9, 10, 2, 5, 8, 11, 1, 6, 7, 12}
                                        ,{7, 8, 9, 10, 6, 5, 4, 11, 1, 2, 3, 12}
                                        ,{3, 4, 5, 6, 2, 9, 8, 7, 1, 10, 11, 12}
                                        ,{5, 6, 7, 8, 4, 3, 10, 9, 1, 2, 11, 12}};
                                        
                                        
        vector< vector<int> > all34 = {{7, 8, 9, 10, 6, 3, 2, 11, 5, 4, 1, 12}
                                      ,{5, 6, 9, 10, 4, 7, 8, 11, 3, 2, 1, 12}};
        
        bestgrid[3][3] = this->NN - 1 - n;
        for (int k = 0; k < 32; ++k) {
            grid = bestgrid;
            for (auto&& i : a34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] > n) {
                            grid[y][x] = i[p] - n - 1;
                        } else {
                            grid[y][x] = -1;
                        }
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 12 > n) {
                            grid[x][6-y] = i[p] - n + 12 - 1;
                        } else {
                            grid[x][6-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 24 > n) {
                            grid[6-y][6-x] = i[p] - n + 24 - 1;
                        } else {
                            grid[6-y][6-x] = -1;
                        }
                        
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : al34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 36 > n) {
                            grid[6-x][y] = i[p] - n + 36 - 1;
                        } else {
                            grid[6-x][y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
        }
        
        return bestgrid;
        
    }
    vector< vector<int> > solve7x7_2 (int n) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        vector< vector<int> > a34 = {{9, 10, 11, 12, 8, 7, 6, 5, 1, 2, 3, 4}
                                    ,{3, 4, 11, 12, 2, 5, 10, 9, 1, 6, 7, 8}
                                    ,{3, 4, 5, 12, 2, 7, 6, 11, 1, 8, 9, 10}
                                    ,{5, 6, 7, 12, 4, 3, 8, 11, 1, 2, 9, 10}
                                    ,{5, 6, 7, 12, 4, 3, 8, 11, 1, 2, 9, 10}};
        vector< vector<int> > al34 = {{3, 4, 9, 10, 2, 5, 8, 11, 1, 6, 7, 12}
                                        ,{7, 8, 9, 10, 6, 5, 4, 11, 1, 2, 3, 12}
                                        ,{3, 4, 5, 6, 2, 9, 8, 7, 1, 10, 11, 12}
                                        ,{5, 6, 7, 8, 4, 3, 10, 9, 1, 2, 11, 12}};
                                        
                                        
        vector< vector<int> > all34 = {{7, 8, 9, 10, 6, 3, 2, 11, 5, 4, 1, 12}
                                      ,{5, 6, 9, 10, 4, 7, 8, 11, 3, 2, 1, 12}};
        
        bestgrid[3][3] = this->NN - 1 - n;
        for (int k = 0; k < 32; ++k) {
            grid = bestgrid;
            for (auto&& i : all34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] > n) {
                            grid[y][x] = i[p] - n - 1;
                        } else {
                            grid[y][x] = -1;
                        }
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : all34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 12 > n) {
                            grid[x][6-y] = i[p] - n + 12 - 1;
                        } else {
                            grid[x][6-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : all34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 24 > n) {
                            grid[6-y][6-x] = i[p] - n + 24 - 1;
                        } else {
                            grid[6-y][6-x] = -1;
                        }
                        
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : all34) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 4; ++x) {
                        int p = y*4+x;
                        if (i[p] + 36 > n) {
                            grid[6-x][y] = i[p] - n + 36 - 1;
                        } else {
                            grid[6-x][y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
        }
        
        return bestgrid;
        
    }
    
    
    vector< vector<int> > solve9x9 (int n) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        vector< vector<int> > a36 = {{13,14,15,16,17,18,12,11,10, 9, 8, 7, 1, 2, 3, 4, 5, 6,},
                                     { 3, 4, 9,10,17,18, 2, 5, 8,11,16,15, 1, 6, 7,12,13,14,},
                                     { 3, 4,15,16,17,18, 2, 5,14,13,12,11, 1, 6, 7, 8, 9,10,},
                                     { 3, 4, 5,16,17,18, 2, 7, 6,15,14,13, 1, 8, 9,10,11,12,},
                                     { 3, 4, 5, 6,17,18, 2, 9, 8, 7,16,15, 1,10,11,12,13,14,},
                                     { 3, 4, 5, 6, 7,18, 2,11,10, 9, 8,17, 1,12,13,14,15,16,},
                                     { 3, 4, 9,10,11,18, 2, 5, 8,13,12,17, 1, 6, 7,14,15,16,},
                                     { 5, 6, 7,12,13,18, 4, 3, 8,11,14,17, 1, 2, 9,10,15,16,},
                                     { 3, 4, 5,12,13,18, 2, 7, 6,11,14,17, 1, 8, 9,10,15,16,}};


        vector< vector<int> > al36 = {{ 7, 8, 9,10,11,12, 6, 5, 4,15,14,13, 1, 2, 3,16,17,18,},
                                      { 3, 4, 9,10,15,16, 2, 5, 8,11,14,17, 1, 6, 7,12,13,18,},
                                      { 3, 4, 9,10,11,12, 2, 5, 8,15,14,13, 1, 6, 7,16,17,18,},
                                      { 7, 8, 9,10,15,16, 6, 5, 4,11,14,17, 1, 2, 3,12,13,18,},
                                      { 3, 4, 5, 6,15,16, 2, 9, 8, 7,14,17, 1,10,11,12,13,18,}};
        
        vector< vector<int> > al33 {{1,2,3,8,9,4,7,6,5},{1,8,7,2,9,6,3,4,5}};

        bestgrid[4][4] = this->NN - 1 - n;
        for (int k = 0; k < 32; ++k) {
            grid = bestgrid;
            for (auto&& i : al33) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 3; ++x) {
                        int p = y*3+x;
                        grid[y+3][x+3] = i[p] - n + 18*4 - 1;
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
            
            grid = bestgrid;
            for (auto&& i : al36) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 6; ++x) {
                        int p = y*6+x;
                        if (i[p] + 18*3 > n) {
                            grid[8-x][y] = i[p] - n + 18*3 - 1;
                        } else {
                            grid[8-x][y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a36) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 6; ++x) {
                        int p = y*6+x;
                        if (i[p] > n) {
                            grid[y][x] = i[p] - n - 1;
                        } else {
                            grid[y][x] = -1;
                        }
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a36) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 6; ++x) {
                        int p = y*6+x;
                        if (i[p] + 18 > n) {
                            grid[x][8-y] = i[p] - n + 18 - 1;
                        } else {
                            grid[x][8-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a36) {
                for (int y = 0; y < 3; ++y) {
                    for (int x = 0; x < 6; ++x) {
                        int p = y*6+x;
                        if (i[p] + 18*2 > n) {
                            grid[8-y][8-x] = i[p] - n + 18*2 - 1;
                        } else {
                            grid[8-y][8-x] = -1;
                        }
                        
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
        }
        // fdebug(bestgrid);
        return bestgrid;
        
    }
    
    
    vector< vector<int> > solve9x9_2 (int n) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        vector< vector<int> > a45 = {{12,13,16,17,20,11,14,15,18,19,10, 9, 8, 7, 6, 1, 2, 3, 4, 5},
                                     {16,17,18,19,20,15,12,11, 8, 7,14,13,10, 9, 6, 1, 2, 3, 4, 5},
                                     {16,17,18,19,20,15,14,13,12,11, 2, 3, 6, 7,10, 1, 4, 5, 8, 9},
                                     { 4, 5,16,17,20, 3, 6,15,18,19, 2, 7,14,13,12, 1, 8, 9,10,11},
                                     { 4, 5,18,19,20, 3, 6,17,14,13, 2, 7,16,15,12, 1, 8, 9,10,11},
                                     { 4, 5,12,13,20, 3, 6,11,14,19, 2, 7,10,15,18, 1, 8, 9,16,17},
                                     {16,17,18,19,20,15,12,11,10, 9,14,13, 4, 5, 8, 1, 2, 3, 6, 7}};


        vector< vector<int> > al45 = {{ 4, 5, 6, 7, 8, 3,12,11,10, 9, 2,13,16,17,-1, 1,14,15,18,19},
                                      { 4, 5, 6, 7, 8, 3,12,11,10, 9, 2,13,16,17,18, 1,14,15,-1,19},
                                      { 4, 5, 6, 7, 8, 3,12,11,10, 9, 2,13,-1,17,18, 1,14,15,16,19},
                                      { 4, 5,12,13,14, 3, 6,11,16,15, 2, 7,10,17,18, 1, 8, 9,-1,19},
                                      { 4, 5,12,13,14, 3, 6,11,16,15, 2, 7,10,17,-1, 1, 8, 9,18,19},
                                      { 4, 5,12,13,14, 3, 6,11,-1,15, 2, 7,10,17,16, 1, 8, 9,18,19},
                                      { 4, 5,12,13,-1, 3, 6,11,14,15, 2, 7,10,17,16, 1, 8, 9,18,19}};

        bestgrid[4][4] = this->NN - 2 - n;
        for (int k = 0; k < 32; ++k) {
            grid = bestgrid;
            for (auto&& i : al45) {
                for (int y = 0; y < 4; ++y) {
                    for (int x = 0; x < 5; ++x) {
                        int p = y*5+x;
                        if (i[p] > -1 && i[p] + 60 > n) {
                            grid[8-x][y] = i[p] - n + 60 - 1;
                        } else {
                            grid[8-x][y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a45) {
                for (int y = 0; y < 4; ++y) {
                    for (int x = 0; x < 5; ++x) {
                        int p = y*5+x;
                        if (i[p] > n) {
                            grid[y][x] = i[p] - n - 1;
                        } else {
                            grid[y][x] = -1;
                        }
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a45) {
                for (int y = 0; y < 4; ++y) {
                    for (int x = 0; x < 5; ++x) {
                        int p = y*5+x;
                        if (i[p] + 20 > n) {
                            grid[x][8-y] = i[p] - n + 20 - 1;
                        } else {
                            grid[x][8-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : a45) {
                for (int y = 0; y < 4; ++y) {
                    for (int x = 0; x < 5; ++x) {
                        int p = y*5+x;
                        if (i[p] + 40 > n) {
                            grid[8-y][8-x] = i[p] - n + 40 - 1;
                        } else {
                            grid[8-y][8-x] = -1;
                        }
                        
                        
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
        }
        // fdebug(bestgrid);
        return bestgrid;
        
    }
    
    
    vector< vector<int> > solveNxN (int n, NXN1& nxn1) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        bestgrid[this->HN][this->HN] = this->NN - 1 - n - nxn1.m2;
        
        for (int k = 0; k < 2; ++k) {
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid2) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x * 3 >= n) {
                            grid[this->N-1-x][y] = i[y][x] - n + nxn1.y * nxn1.x * 3;
                        } else {
                            grid[this->N-1-x][y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
            
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] >= n) {
                            grid[y][x] = i[y][x] - n;
                        } else {
                            grid[y][x] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x >= n) {
                            grid[x][this->N-1-y] = i[y][x] - n + nxn1.y * nxn1.x;
                        } else {
                            grid[x][this->N-1-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x * 2 >= n) {
                            grid[this->N-1-y][this->N-1-x] = i[y][x] - n + nxn1.y * nxn1.x * 2;
                        } else {
                            grid[this->N-1-y][this->N-1-x] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
        }
        // for (auto&& i : bestgrid) {
        //     fdebug(i);
        // }
        
        
        return bestgrid;
        
    }
    
    vector< vector<int> > solveNxN2 (int n, NXN1& nxn1) {
        vector< vector<int> > grid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        vector< vector<int> > bestgrid = vector< vector<int> >(this->N, vector<int>(this->N, -1));
        int bestscore = 0;
        
        bestgrid[this->HN][this->HN] = this->NN - 1 - n - nxn1.m2;
        
        int p = -n;
        for (int i = this->HN; i < this->N; ++i) {
            bestgrid[i][0] = (p >= 0 ? p : -1);
            p += 1;
        }
        for (int i = 1; i < this->N; ++i) {
            bestgrid[this->N-1][i] = (p >= 0 ? p : -1);
            p += 1;
        }
        for (int i = 1; i < this->N; ++i) {
            bestgrid[this->N-1-i][this->N-1] = (p >= 0 ? p : -1);
            p += 1;
        }
        for (int i = 1; i < this->N; ++i) {
            bestgrid[0][this->N-1-i] = (p >= 0 ? p : -1);
            p += 1;
        }
        for (int i = 1; i < this->HN; ++i) {
            bestgrid[i][0] = (p >= 0 ? p : -1);
            p += 1;
        }
        
        for (int k = 0; k < 2; ++k) {
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid2) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x * 3 + p >= 0) {
                            grid[this->N-2-x][y+1] = i[y][x] + nxn1.y * nxn1.x * 3 + p;
                        } else {
                            grid[this->N-2-x][y+1] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
            
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + p >= 0) {
                            grid[y+1][x+1] = i[y][x] + p;
                        } else {
                            grid[y+1][x+1] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x + p >= 0) {
                            grid[x+1][this->N-2-y] = i[y][x] + nxn1.y * nxn1.x + p;
                        } else {
                            grid[x+1][this->N-2-y] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            grid = bestgrid;
            for (auto&& i : nxn1.subgrid1) {
                for (int y = 0; y < nxn1.y; ++y) {
                    for (int x = 0; x < nxn1.x; ++x) {
                        if (i[y][x] > -1 && i[y][x] + nxn1.y * nxn1.x * 2 + p >= 0) {
                            grid[this->N-2-y][this->N-2-x] = i[y][x] + nxn1.y * nxn1.x * 2 + p;
                        } else {
                            grid[this->N-2-y][this->N-2-x] = -1;
                        }
                    }
                }
                int tscore = this->indexgridscore(grid);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestgrid = grid;
                }
            }
            
        }
        // for (auto&& i : bestgrid) {
        //     fdebug(i);
        // }
        
        
        return bestgrid;
        
    }
    
    vector<char> indexGridToCommand (vector< vector<int> > grid) {
        vector<char> r;
        int x = this->HN;
        int y = this->HN;
        int n = this->NN-1;
        for (int i = 0; i < this->NN-1; ++i) {
            n -= 1;
            if (this->isInside(x, y-1) && grid[y-1][x] == n) {
                r.emplace_back('U');
                y -= 1;
                continue;
            }
            if (this->isInside(x+1, y) && grid[y][x+1] == n) {
                r.emplace_back('R');
                x += 1;
                continue;
            }
            if (this->isInside(x, y+1) && grid[y+1][x] == n) {
                r.emplace_back('D');
                y += 1;
                continue;
            }
            if (this->isInside(x-1, y) && grid[y][x-1] == n) {
                r.emplace_back('L');
                x -= 1;
                continue;
            }
        }
        //fdebug(r);
        return r;
    }
    inline bool isInside (int x, int y) {
        return (x >= 0 && y >= 0 && x < this->N && y < this->N);
    }
    
    
};

int main() {
    SnakeCharmer prog;
    int N;
    int V;
    string snake;
    cin >> N;
    cin >> V;
    cin >> snake;
    
    vector<char> ret = prog.findSolution(N, V, snake);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) { cout << ret[i] << endl; }
    cout.flush();
}