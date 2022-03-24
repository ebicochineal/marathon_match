// C++11
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

struct Grid {
    array< array<int, 30>, 30 > g;
    array<int, 120> bp;
    
    array<e512pos, 5> bp_pos;
    array<int, 5> bp_dir;
    
    int N, B, V;
    Grid () {}
    Grid (array< array<int, 30>, 30 >& ig, int N, int B, int V) {
        this->init(ig, N, B, V);
    }
    
    void copy (Grid& t) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->g[y][x] = t.g[y][x];
            }
        }
        for (int i = 0; i < 120; ++i) {
            this->bp[i] = t.bp[i];
        }
        
        
    }
    
    void init (array< array<int, 30>, 30 >& ig, int N, int B, int V) {
        this->N = N;
        this->B = B;
        this->V = V;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->g[y][x] = ig[y][x];
            }
        }
        
        for (int i = 0; i < this->N*4; ++i) { this->bp[i] = i % this->N + (i / this->N) * 30; }
    }
    
    int ra, rb;
    void random_swap_bp () {
        this->ra = xrnd() % this->B;
        this->rb = this->B + xrnd() % (this->N*4-this->B);
        swap(this->bp[this->ra], this->bp[this->rb]);
    }
    void swap_back_bp () {
        swap(this->bp[this->ra], this->bp[this->rb]);
    }
    
    
    int sim () {
        // /\.*
        static int dtable[4][8] = {
            { 1,-1, 0, 0, 1,-1, 0, 0},
            {-1, 1, 0, 0,-1, 1, 0, 0},
            { 1,-1, 0, 0, 1,-1, 0, 0},
            {-1, 1, 0, 0,-1, 1, 0, 0}
        };
        static int ptable[8] = {1, 1, 0, this->V, 1, 1, 0, this->V};
        static int gtable[2] = {1, 0};
        
        static array< array<int, 30>, 30 > ctg;
        static array< array<int, 30>, 30 > tg;
        static vector<e512pos> v;
        
        int score = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                tg[y][x] = this->g[y][x];
                ctg[y][x] = 0;
            }
        }
        
        for (int i = 0; i < this->B; ++i) {
            int a = this->bp[i] / 30;
            int b = this->bp[i] % 30;
            this->bp_dir[i] = (a+2) & 0b11;
            if (a == 0) {
                this->bp_pos[i].y = 0;
                this->bp_pos[i].x = b;
            }
            if (a == 1) {
                this->bp_pos[i].y = b;
                this->bp_pos[i].x = this->N-1;
            }
            if (a == 2) {
                this->bp_pos[i].y = this->N-1;
                this->bp_pos[i].x = this->N-1-b;
            }
            if (a == 3) {
                this->bp_pos[i].y = this->N-1-b;
                this->bp_pos[i].x = 0;
            }
        }
        
        
        bool f = true;
        
        while (f) {
            // dire score
            for (int i = 0; i < this->B; ++i) {
                const int y = this->bp_pos[i].y;
                const int x = this->bp_pos[i].x;
                const int d = this->bp_dir[i];
                const int t = tg[y][x];
                this->bp_dir[i] = (this->bp_dir[i] + dtable[d][t] + 4) & 0b11;
                score += ptable[t];
                ctg[y][x] += 1;
            }
            
            // grid dire
            
            for (int i = 0; i < this->B; ++i) {
                const int y = this->bp_pos[i].y;
                const int x = this->bp_pos[i].x;
                
                if (ctg[y][x] == 1 && this->g[y][x] < 2) {
                    tg[y][x] = gtable[tg[y][x]];
                }
                ctg[y][x] = 0;
            }
            
            
            // move
            for (int i = 0; i < this->B; ++i) {
                const int y = this->bp_pos[i].y;
                const int x = this->bp_pos[i].x;
                const int d = this->bp_dir[i];
                
                if (d == 0) {
                    this->bp_pos[i].y -= 1;
                    if (this->bp_pos[i].y < 0) { f = false; }
                }
                if (d == 1) {
                    this->bp_pos[i].x += 1;
                    if (this->bp_pos[i].x >= this->N) { f = false; }
                }
                if (d == 2) {
                    this->bp_pos[i].y += 1;
                    if (this->bp_pos[i].y >= this->N) { f = false; }
                }
                if (d == 3) {
                    this->bp_pos[i].x -= 1;
                    if (this->bp_pos[i].x < 0) { f = false; }
                }
            }
            
        }
        for (int i = 0; i < this->B; ++i) {
            const int y = this->bp_pos[i].y;
            const int x = this->bp_pos[i].x;
            if (this->bp_pos[i].y < 0) { continue; }
            if (this->bp_pos[i].x >= this->N) { continue; }
            if (this->bp_pos[i].y >= this->N) { continue; }
            if (this->bp_pos[i].x < 0) { continue; }
            const int d = this->bp_dir[i];
            const int t = tg[y][x];
            this->bp_dir[i] = (this->bp_dir[i] + dtable[d][t] + 4) & 0b11;
            score += ptable[t];
        }
        
        return score;
    }
    
    
};
class MM {
public:
    StopWatch sw;
    int N, B, bonusValue;
    Grid bestgrid;
    array< array<int, 30>, 30 > ig;
    
    array<int, 5> output_b;
    array< array<int, 30>, 30 > output_g;
    
    int mg = 0;
    
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N;
        cin >> this->B;
        cin >> this->bonusValue;
        
        int xcnt = 0;
        for (int r = 0; r < this->N; r++) {
            for (int c = 0; c < this->N; c++) {
                char t;
                cin >> t;
                if (t == '/' ) { this->ig[r][c] = 0+4; }
                if (t == '\\') { this->ig[r][c] = 1+4; }
                if (t == '.' ) { this->ig[r][c] = 2; }
                if (t == '*' ) { this->ig[r][c] = 3+4; }
                if (t != '.') { xcnt += 1;}
                getchar();
            }
        }
        
        pdebug(N, B, bonusValue);
        
    }
    void output () {
        for (int i = 0; i < this->B; ++i) {
            int a = this->bestgrid.bp[i] / 30;
            int b = this->bestgrid.bp[i] % 30;
            if (a == 0) { cout << print(-1, b) << endl; }
            if (a == 1) { cout << print(b, this->N) << endl; }
            if (a == 2) { cout << print(this->N, this->N-1-b) << endl; }
            if (a == 3) { cout << print(this->N-1-b, -1) << endl; }
            
        }
        
        
        char cells[] = {'/', '\\', '.', '*'};
        for (int r = 0; r < this->N; r++) {
            for (int c = 0; c < this->N; c++) {
                cout << cells[this->bestgrid.g[r][c] % 4] << endl;
            }
        }
    }
    
    
    void solve () {
        Grid grid(this->ig, this->N, this->B, this->bonusValue);
        int cnt = 0;
        double bestscore = 0;
        
        this->bestgrid = grid;
        if (this->N < 8) {
            for (int i = 0; i < 32; ++i) {
                Grid t = grid;
                for (int j = 0; j < 32; ++j) { t.random_swap_bp(); }
                for (int y = 0; y < this->N; ++y) {
                    for (int x = 0; x < this->N; ++x) {
                        if (t.g[y][x] == 2) { t.g[y][x] = xrnd()%2; }
                    }
                }
                double score = 0;
                t = this->maximize_sa(t, score, cnt, 7000/32, 32.0, 8.0);
                if (score > bestscore) {
                    bestscore = score;
                    bestgrid = t;
                }
            }
        } else if (this->N < 10) {
            for (int i = 0; i < 24; ++i) {
                Grid t = grid;
                for (int j = 0; j < 32; ++j) { t.random_swap_bp(); }
                for (int y = 0; y < this->N; ++y) {
                    for (int x = 0; x < this->N; ++x) {
                        if (t.g[y][x] == 2) { t.g[y][x] = xrnd()%2; }
                    }
                }
                double score = 0;
                t = this->maximize_sa(t, score, cnt, 7000/24, 32.0, 8.0);
                if (score > bestscore) {
                    bestscore = score;
                    bestgrid = t;
                }
            }
        } else if (this->N < 12) {
            for (int i = 0; i < 16; ++i) {
                Grid t = grid;
                for (int j = 0; j < 32; ++j) { t.random_swap_bp(); }
                for (int y = 0; y < this->N; ++y) {
                    for (int x = 0; x < this->N; ++x) {
                        if (t.g[y][x] == 2) { t.g[y][x] = xrnd()%2; }
                    }
                }
                double score = 0;
                t = this->maximize_sa(t, score, cnt, 7000/16, 32.0, 8.0);
                if (score > bestscore) {
                    bestscore = score;
                    bestgrid = t;
                }
            }
        } else {
            if (this->N >= 12) { this->mg = 1; }
            if (this->N >= 16) { this->mg = 2; }
            if (this->N >= 20) { this->mg = 3; }
            if (this->N >= 24) { this->mg = 4; }
            if (this->N >= 28) { this->mg = 5; }
            if (this->N >= 30) { this->mg = 6; }
            
            // if (this->N >= 12) { this->mg = 1; }
            // if (this->N >= 18) { this->mg = 2; }
            // if (this->N >= 24) { this->mg = 3; }
            // if (this->N >= 28) { this->mg = 4; }
            
            int d = 1;
            if (this->N >= 12) { d = 8; }
            if (this->N >= 16) { d = 4; }
            if (this->N >= 20) { d = 2; }
            if (this->N >= 24) { d = 1; }
            
            for (int i = 0; i < d; ++i) {
                Grid t = grid;
                for (int j = 0; j < 32; ++j) { t.random_swap_bp(); }
                for (int y = this->mg; y < this->N-this->mg; ++y) {
                    for (int x = this->mg; x < this->N-this->mg; ++x) {
                        if (t.g[y][x] == 2) { t.g[y][x] = xrnd()%2; }
                    }
                }
                double score = 0;
                t = this->maximize_sa_mg_1(t, score, cnt, 2000/d, 32.0, 8.0);
                if (score > bestscore) {
                    bestscore = score;
                    bestgrid = t;
                }
            }
        }
        if (this->N < 12) {
            bestgrid = this->maximize_sa2(bestgrid, bestscore, cnt, 2000, 32.0, 8.0);
            bestgrid = this->maximize_sa2(bestgrid, bestscore, cnt, 800, 24.0, 8.0);
        } else {
            bestgrid = this->maximize_sa_mg_2(bestgrid, bestscore, cnt, 7800, 32.0, 8.0);
            // bestgrid = this->maximize_sa2(bestgrid, bestscore, cnt, 800, 24.0, 0.0);
        }
        
        pdebug(bestgrid.sim());
        
        
        // this->bestgrid = this->maximize_sa(this->bestgrid, bestscore, 2000, 24.0, 0.0);
        pdebug(cnt, this->sw.get_milli_time());
    }
    
    
    Grid maximize_sa_mg_1 (Grid v, double& refscore, int& cnt, int etime, double stemp = 256.0, double etemp = 0.0, double k = 2.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        Grid bestv = v;
        double bestscore = v.sim();
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        
        int dcnt = 0;
        int m = this->N <= 12 ? 50000 : 1000000;
        
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            if (ntime < etime*0.01) {
                for (int i = 0; i < 64; ++i) {
                    v.random_swap_bp();
                
                    double tmpscore = v.sim();
                    const double temp = stemp;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                        dcnt= 0;
                    } else {
                        v.swap_back_bp();
                    }
                    cnt += 1;
                }
                
            }
            for (int y = this->mg; y < this->N-this->mg; ++y) {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                for (int x = this->mg; x < this->N-this->mg; ++x) {
                    
                    int t = v.g[y][x];
                    
                    
                    if(v.g[y][x] <= 2) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    } else {
                        continue;
                    }
                    if(v.g[y][x] == 2 && xrnd()%8 > 0) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    }
                    
                    
                    double tmpscore = v.sim();
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                    } else {
                        v.g[y][x] = t;
                    }
                    cnt += 1;
                }
            }
            if (dcnt > m) {
                v.copy(bestv);
                lastscore = bestscore;
                dcnt = 0;
            }
        }
        refscore = bestscore;
        return bestv;
    }
    Grid maximize_sa_mg_2 (Grid v, double& refscore, int& cnt, int etime, double stemp = 256.0, double etemp = 0.0, double k = 2.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        Grid bestv = v;
        double bestscore = v.sim();
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        
        int dcnt = 0;
        int m = this->N <= 12 ? 50000 : 1000000;
        int lcnt = 0;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            if (lcnt >= 16) {
                this->mg -= 1;
                lcnt = 0;
            }
            for (int y = max(this->mg-1, 0); y < this->N-max(this->mg-1, 0); ++y) {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                for (int x = max(this->mg-1, 0); x < this->N-max(this->mg-1, 0); ++x) {
                    
                    int t = v.g[y][x];
                    
                    
                    if(v.g[y][x] <= 2) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    } else {
                        continue;
                    }
                    if(v.g[y][x] == 2 && xrnd()%8 > 0) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    }
                    
                    
                    double tmpscore = v.sim();
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                    } else {
                        v.g[y][x] = t;
                    }
                    cnt += 1;
                }
            }
            
            
            if (dcnt > m) {
                v.copy(bestv);
                lastscore = bestscore;
                dcnt = 0;
            }
            lcnt += 1;
        }
        refscore = bestscore;
        return bestv;
    }
    
    
    Grid maximize_sa (Grid v, double& refscore, int& cnt, int etime, double stemp = 256.0, double etemp = 0.0, double k = 2.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        Grid bestv = v;
        double bestscore = v.sim();
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        
        int dcnt = 0;
        int m = this->N <= 12 ? 50000 : 1000000;
        
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            if (ntime < etime*0.01) {
                for (int i = 0; i < 64; ++i) {
                    v.random_swap_bp();
                
                    double tmpscore = v.sim();
                    const double temp = stemp;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                        dcnt= 0;
                    } else {
                        v.swap_back_bp();
                    }
                    cnt += 1;
                }
                
            }
            for (int y = 0; y < this->N; ++y) {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                for (int x = 0; x < this->N; ++x) {
                    
                    int t = v.g[y][x];
                    
                    
                    if(v.g[y][x] <= 2) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    } else {
                        continue;
                    }
                    if(v.g[y][x] == 2 && xrnd()%8 > 0) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    }
                    
                    
                    double tmpscore = v.sim();
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                    } else {
                        v.g[y][x] = t;
                    }
                    cnt += 1;
                }
            }
            if (dcnt > m) {
                v.copy(bestv);
                lastscore = bestscore;
                dcnt = 0;
            }
        }
        refscore = bestscore;
        return bestv;
    }
    
    Grid maximize_sa2 (Grid v, double& refscore, int& cnt, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        Grid bestv = v;
        double bestscore = v.sim();
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        
        int dcnt = 0;
        int m = this->N <= 12 ? 50000 : 1000000;
        
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            for (int y = 0; y < this->N; ++y) {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                for (int x = 0; x < this->N; ++x) {
                    
                    int t = v.g[y][x];
                    
                    
                    if(v.g[y][x] <= 2) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    } else {
                        continue;
                    }
                    if(v.g[y][x] == 2 && xrnd()%8 > 0) {
                        v.g[y][x] = (v.g[y][x] + 1 + xrnd()%2)%3;
                    }
                    
                    
                    double tmpscore = v.sim();
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    dcnt += 1;
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestv.copy(v);
                            dcnt = 0;
                        }
                    } else {
                        v.g[y][x] = t;
                    }
                    cnt += 1;
                }
            }
            if (dcnt > m) {
                v.copy(bestv);
                lastscore = bestscore;
                dcnt = 0;
            }
        }
        refscore = bestscore;
        return bestv;
    }
};

int main () {
    // cin.tie(0);
    // ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    cout.flush();
    return 0;
}