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

class ScoreGridAB {
public:
    double score = 0;
    array<int, 256> grid;
    int a = 0;
    int b = 1;
    ScoreGridAB () {}
};

class CpGrid {
public:
    array<int, 256> grid;
    int n;
    int cnt;
    CpGrid () {}
    CpGrid (array<int, 256> grid, int n) {
        this->grid = grid;
        this->n = n;
        this->cnt = 0;
        for (int i = 0; i < 256; ++i) {
            if (this->grid[i]>0) { this->cnt += 1; }
        }
    }
    
    int score (array<int, 256>& targetgrid) {
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (this->grid[i]>0 && this->grid[i] == targetgrid[i]) {
                r += 1;
            }
        }
        return r;
    }
    
};


class Jewels {
public:
    int N, NN, C, turn;
    array<int, 256> grid;
    int runtime = 0;
    
    array<int, 256> ptox;
    array<int, 256> ptoy;
    CpGrid cpg;
    Jewels (int N, int C) {
        pdebug(N, C);
        this->N = N;
        this->C = C;
        this->NN = N*N;
        this->grid;
        this->turn = -1;
        
        for (int i = 0; i < this->NN; ++i) {
            this->ptox[i] = i % this->N;
            this->ptoy[i] = i / this->N;
        }
        
        // vector<string> s;
        // s.emplace_back("00110000");
        // s.emplace_back("00110000");
        // s.emplace_back("00220000");
        // s.emplace_back("00330000");
        // s.emplace_back("11221100");
        // s.emplace_back("11221100");
        vector<string> s;
        // s.emplace_back("00330000");
        // s.emplace_back("00330000");
        // s.emplace_back("00110000");
        // s.emplace_back("00113400");
        // s.emplace_back("33223300");
        // s.emplace_back("33550300");
        // s.emplace_back("11221100");
        // s.emplace_back("11221144");
        
        // s.emplace_back("33000000000000");
        // s.emplace_back("33000000000000");
        // s.emplace_back("44000000000000");
        // s.emplace_back("44000000000000");
        // s.emplace_back("55103040105000");
        // s.emplace_back("11334411556660");
        // s.emplace_back("55221155224400");
        // s.emplace_back("55221155224400");
        // s.emplace_back("44332211552244");
        // s.emplace_back("44332211552244");
        if (this->N == 16) {
            s.emplace_back("0000006600000000");
            s.emplace_back("0000007700000000");
            s.emplace_back("0000008850600000");
            s.emplace_back("0000005566770000");
            s.emplace_back("0000118811000000");
            s.emplace_back("0033118811330000");
            s.emplace_back("1144557755441100");
            s.emplace_back("1155667766551100");
            s.emplace_back("2244220022442200");
            s.emplace_back("3344330033443300");
            s.emplace_back("2211221122112211");
            s.emplace_back("2211221122112211");
        } else if (this->N >= 14) {
            s.emplace_back("00006600000000");
            s.emplace_back("00007700000000");
            s.emplace_back("00008850600000");
            s.emplace_back("00005566770000");
            s.emplace_back("00118811000000");
            s.emplace_back("33118811330000");
            s.emplace_back("44557755441100");
            s.emplace_back("55667766551100");
            s.emplace_back("44220022442200");
            s.emplace_back("44330033443300");
            s.emplace_back("11221122112211");
            s.emplace_back("11221122112211");
        } else {
            s.emplace_back("006600000000");
            s.emplace_back("007700000000");
            s.emplace_back("008850600000");
            s.emplace_back("005566770000");
            s.emplace_back("118811000000");
            s.emplace_back("118811330000");
            s.emplace_back("557755441100");
            s.emplace_back("667766551100");
            s.emplace_back("220022442200");
            s.emplace_back("330033443300");
            s.emplace_back("221122112211");
            s.emplace_back("221122112211");
        }
        
        this->cpg = this->toCpGrid(s);
    }
    
    CpGrid toCpGrid(vector<string> t) {
        int w = t[0].size();
        int h = t.size();
        array<int, 256> g;
        for (int i = 0; i < 256; ++i) { g[i] = 0; }
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                g[y*this->N+x] = t[h-1-y][x]-'0';
            }
        }
        return CpGrid(g, this->N);
    }
    
    
    void update_grid () {
        for (int i=0; i<this->NN; i++) { cin >> this->grid[i]; }
        this->turn += 1;
    }
    void set_runtime (int runtime) { this->runtime = runtime; }
    vector<int> scores;
    vector<ScoreGridAB> vsgab;
    
    string output () {
        //return output1();
        if (this->C >= 8 && this->N >= 12 && this->runtime < 8500) {
            return output2();
        } else {
            return output1();
        }
    }
    
    string output1 () {
        int w = 24;
        if (this->N >= 9) { w = 20; }
        if (this->N >= 10) { w = 16; }
        if (this->N >= 11) { w = 12; }
        if (this->N >= 12) { w = 10; }
        if (this->N >= 13) { w = 8; }
        if (this->N >= 14) { w = 6; }
        if (this->N >= 15) { w = 4; }
        if (this->runtime < 500 && this->turn >= 100) { w *= 2; }
        if (this->runtime < 1000 && this->turn >= 200) { w *= 2; }
        if (this->runtime < 2000 && this->turn >= 400) { w *= 2; }
        if (this->runtime < 4000 && this->turn >= 600) { w *= 2; }
        if (this->runtime < 5000 && this->turn >= 800) { w *= 2; }
        if (this->runtime > 8000) { w /= 2; }
        if (this->runtime > 9000) { w = 1; }
        
        w = max(w, 1);
        this->vsgab.clear();
        
        
        for (int a = 0; a < this->NN-1; ++a) {
            if (this->nbreaka(a)) { continue; }
            for (int b = a+1; b < this->NN; ++b) {
                if (this->grid[a] == this->grid[b]) { continue; }
                if (this->nbreakb(b)) { continue; }
                double score = this->swap_score(this->grid, a, b);
                if (this->vsgab.size() < w) {
                    this->vsgab.emplace_back(ScoreGridAB());
                    const size_t t = this->vsgab.size()-1;
                    this->vsgab[t].score = score;
                    this->vsgab[t].grid = this->tgrid;
                    this->vsgab[t].a = a;
                    this->vsgab[t].b = b;
                    sort(this->vsgab.begin(), this->vsgab.end(), [](const ScoreGridAB& sga, const ScoreGridAB& sgb) { return sga.score > sgb.score; });
                } else if (score > this->vsgab[w-1].score) {
                    this->vsgab.pop_back();
                    this->vsgab.emplace_back(ScoreGridAB());
                    const size_t t = this->vsgab.size()-1;
                    this->vsgab[t].score = score;
                    this->vsgab[t].grid = this->tgrid;
                    this->vsgab[t].a = a;
                    this->vsgab[t].b = b;
                    sort(this->vsgab.begin(), this->vsgab.end(), [](const ScoreGridAB& sga, const ScoreGridAB& sgb) { return sga.score > sgb.score; });
                }
            }
        }
        
        int bestindex = 0;
        if (this->vsgab.size() > 1 && this->turn < 999 && this->runtime < 8000) {
            double vsgabcore2 = 0;
            for (int i = 0; i < this->vsgab.size(); ++i) {
                for (int a = 0; a < this->NN-1; ++a) {
                    if (this->nbreaka(a)) { continue; }
                    for (int b = a+1; b < this->NN; ++b) {
                        if (this->vsgab[i].grid[a] == this->vsgab[i].grid[b]) { continue; }
                        if (this->vsgab[i].grid[a] < 0 || this->vsgab[i].grid[b] < 0) { continue; }
                        if (this->nbreakb(b)) { continue; }
                        double score = this->swap_score(this->vsgab[i].grid, a, b);
                        if (score + this->vsgab[i].score > vsgabcore2) {
                            vsgabcore2 = score + this->vsgab[i].score;
                            bestindex = i;
                        }
                    }
                }
            }
            
            
        }
        int r1 = this->vsgab[bestindex].a / this->N;
        int c1 = this->vsgab[bestindex].a % this->N;
        int r2 = this->vsgab[bestindex].b / this->N;
        int c2 = this->vsgab[bestindex].b % this->N;
        return print(r1, c1, r2, c2);
        
        
        
        // return print(r1, c1, r2, c2);// ay, ax, by, bx
    }
    
    string output2 () {
        int cpgscore = 0;
        int t = this->cpg.score(this->grid);
        if (t == this->cpg.cnt) { cpgscore = t*10000; }
        
        double bestscore = 0;
        int besta = 0;
        int bestb = 1;
        int a = 0;
        for (int i=0; i < 255; ++i) {
            if (this->cpg.grid[i] > 0 && this->cpg.grid[i] != this->grid[i]) {
                a = i;
            } else {
                continue;
            }
            
            
            for (int b = a+1; b < this->NN; ++b) {
                if (this->grid[a] == this->grid[b]) { continue; }
                int score = this->swap_score2(this->grid, a, b);
                if (cpgscore > 0) {
                    score += cpgscore;
                } else {
                    score += (this->cpg.score(this->tgrid)-t)*10000;
                }
                if (score > bestscore) {
                    bestscore = score;
                    besta = a;
                    bestb = b; 
                }
            }
        }
        if (bestscore < 10000) {
            for (int a = 0; a < this->NN-1; ++a) {
                for (int b = a+1; b < this->NN; ++b) {
                    if (this->grid[a] == this->grid[b]) { continue; }
                    int score = this->swap_score2(this->grid, a, b);
                    if (cpgscore > 0) {
                        score += cpgscore;
                    } else {
                        score += (this->cpg.score(this->tgrid)-t)*10000;
                    }
                    if (score > bestscore) {
                        bestscore = score;
                        besta = a;
                        bestb = b; 
                    }
                }
            }
        }
        
        
        int r1 = besta / this->N;
        int c1 = besta % this->N;
        int r2 = bestb / this->N;
        int c2 = bestb % this->N;
        return print(r1, c1, r2, c2);
    }
    
    bool nbreaka (int v) {
        if (this->turn % 32 == 0 && this->runtime < 9000) { return false; }
        if (this->N > 13) {
            if (this->ptoy[v] >= this->N-6) { return true; }
            if (this->ptox[v] < 3 || this->ptox[v] >= this->N-3) { return true; }
        }
        if (this->N > 11) {
            if (this->ptoy[v] >= this->N-5) { return true; }
            if (this->ptox[v] < 2 || this->ptox[v] >= this->N-2) { return true; }
        }
        if (this->N > 9) {
            if (this->ptoy[v] >= this->N-4) { return true; }
            if (this->ptox[v] < 1 || this->ptox[v] >= this->N-1) { return true; }
        }
        if (runtime > 8000) {
            if (this->ptoy[v] >= this->N/2) { return true; }
            if (this->ptox[v] < 2 || this->ptox[v] >= this->N-2) { return true; }
        }
        if (runtime > 8500) {
            if (this->ptoy[v] >= this->N/3) { return true; }
            if (this->ptox[v] < 2 || this->ptox[v] >= this->N-2) { return true; }
        }
        if (runtime > 9000) {
            if (this->ptoy[v] >= this->N/4) { return true; }
            if (this->ptox[v] < 3 || this->ptox[v] >= this->N-3) { return true; }
        }
        if (runtime > 9500) {
            if (this->ptoy[v] >= this->N/5) { return true; }
            if (this->ptox[v] < 3 || this->ptox[v] >= this->N-3) { return true; }
        }
        return false;
    }
    bool nbreakb (int v) {
        if (this->turn % 32 == 0 && this->runtime < 9000) { return false; }
        if (this->N > 13) {
            if (this->ptoy[v] >= this->N-4) { return true; }
            if (this->ptox[v] < 1 || this->ptox[v] >= this->N-1) { return true; }
        }
        if (this->N > 11) {
            if (this->ptoy[v] >= this->N-3) { return true; }
            if (this->ptox[v] < 1 || this->ptox[v] >= this->N-1) { return true; }
        }
        if (this->N > 9) {
            if (this->ptoy[v] >= this->N-1) { return true; }
            if (this->ptox[v] < 1 || this->ptox[v] >= this->N-1) { return true; }
        }
        if (runtime > 8000) {
            if (this->ptoy[v] >= this->N/2) { return true; }
            if (this->ptox[v] < 2 || this->ptox[v] >= this->N-2) { return true; }
        }
        if (runtime > 8500) {
            if (this->ptoy[v] >= this->N/3) { return true; }
            if (this->ptox[v] < 2 || this->ptox[v] >= this->N-2) { return true; }
        }
        if (runtime > 9000) {
            if (this->ptoy[v] >= this->N/4) { return true; }
            if (this->ptox[v] < 3 || this->ptox[v] >= this->N-3) { return true; }
        }
        if (runtime > 9500) {
            if (this->ptoy[v] >= this->N/5) { return true; }
            if (this->ptox[v] < 3 || this->ptox[v] >= this->N-3) { return true; }
        }
        return false;
    }
    
    array<int, 256> tgrid;
    array<bool, 256> hgrid;
    array<bool, 256> vgrid;
    array<bool, 256> dgrid;
    array<bool, 16> down;
    vector<int> updatelist;
    int swap_score (array<int, 256>& grid, int a, int b) {
        int linescore = 0;
        int chain = -1;
        swap(grid[a], grid[b]);
        
        if (this->check_horizontal(grid, a) == false && this->check_vertical(grid, a) == false && this->check_horizontal(grid, b) == false && this->check_vertical(grid, b) == false) {
            swap(grid[a], grid[b]);
            return 0;
        }
        
        
        for (int i = 0; i < this->NN; ++i) { this->tgrid[i] = grid[i]; }
        this->updatelist.clear();
        this->updatelist.emplace_back(a);
        this->updatelist.emplace_back(b);
        while (this->updatelist.size() > 0) {
            chain += 1;
            for (int i = 0; i < this->NN; ++i) { this->hgrid[i] = false; }
            for (int i = 0; i < this->NN; ++i) { this->vgrid[i] = false; }
            for (int i = 0; i < this->NN; ++i) { this->dgrid[i] = false; }
            for (int i = 0; i < this->N; ++i) { this->down[i] = false; }
            
            for (auto&& i : this->updatelist) {
                int h = this->horizontal_cnt2(this->tgrid, i) - 2;
                int v = this->vertical_cnt2(this->tgrid, i) - 2;
                if (h > 0) { linescore += h * h; }
                if (v > 0) { linescore += v * v; }
            }
            this->updatelist.clear();
            
            for (int x = 0; x < this->N; ++x) {
                if (this->down[x]) { this->dropdown(this->tgrid, x); }
            }
        }
        
        swap(grid[a], grid[b]);
        return linescore * chain;
    }
    
    int swap_score2 (array<int, 256>& grid, int a, int b) {
        int linescore = 0;
        int chain = -1;
        swap(grid[a], grid[b]);
        
        if (this->check_horizontal(grid, a) == false && this->check_vertical(grid, a) == false && this->check_horizontal(grid, b) == false && this->check_vertical(grid, b) == false) {
            for (int i = 0; i < this->NN; ++i) { this->tgrid[i] = grid[i]; }
            swap(grid[a], grid[b]);
            return 0;
        }
        
        
        for (int i = 0; i < this->NN; ++i) { this->tgrid[i] = grid[i]; }
        this->updatelist.clear();
        this->updatelist.emplace_back(a);
        this->updatelist.emplace_back(b);
        while (this->updatelist.size() > 0) {
            chain += 1;
            for (int i = 0; i < this->NN; ++i) { this->hgrid[i] = false; }
            for (int i = 0; i < this->NN; ++i) { this->vgrid[i] = false; }
            for (int i = 0; i < this->NN; ++i) { this->dgrid[i] = false; }
            for (int i = 0; i < this->N; ++i) { this->down[i] = false; }
            
            for (auto&& i : this->updatelist) {
                int h = this->horizontal_cnt2(this->tgrid, i) - 2;
                int v = this->vertical_cnt2(this->tgrid, i) - 2;
                if (h > 0) { linescore += h * h; }
                if (v > 0) { linescore += v * v; }
            }
            this->updatelist.clear();
            
            for (int x = 0; x < this->N; ++x) {
                if (this->down[x]) { this->dropdown(this->tgrid, x); }
            }
        }
        
        swap(grid[a], grid[b]);
        return linescore * chain;
    }
    
    int horizontal_cnt2 (array<int,256>& grid, int t) {
        if (this->hgrid[t]) { return 0; }
        if (grid[t] < 0) { return 0; }
        int cnt = 1;
        int x=this->ptox[t], p;
        int r=x, l=x;
        this->hgrid[t] = true;
        // R
        for (x=this->ptox[t]+1,p=t+1; x<this->N; ++x,++p,++cnt) {
            if (grid[p] != grid[t]) { break; }
            this->hgrid[p] = true;
            r = x;
        }
        // L
        for (x=this->ptox[t]-1,p=t-1; x>=0; --x,--p,++cnt) {
            if (grid[p] != grid[t]) { break; }
            this->hgrid[p] = true;
            l = x;
        }
        
        if (cnt > 2) {
            int y = this->ptoy[t];
            for (int i=l; i<=r; i+=1) {
                this->down[i] = true;
            }
            
            for (int i=l; i<=r; i+=1) {
                this->dgrid[y*this->N+i] = true;
            }
        }
        return cnt;
    }
    int vertical_cnt2 (array<int, 256>& grid, int t) {
        if (this->vgrid[t]) { return 0; }
        if (grid[t] < 0) { return 0; }
        int cnt = 1;
        int y=this->ptoy[t], p;
        int u=y, d=y;
        this->vgrid[t] = true;
        // U
        for (y=this->ptoy[t]+1,p=t+this->N; y<this->N; ++y,p+=this->N,++cnt) {
            if (grid[p] != grid[t]) { break; }
            this->vgrid[p] = true;
            u = y;
        }
        // D
        for (y=this->ptoy[t]-1,p=t-this->N; y>=0; --y,p-=this->N,++cnt) {
            if (grid[p] != grid[t]) { break; }
            this->vgrid[p] = true;
            d = y;
        }
        if (cnt > 2) {
            int x = this->ptox[t];
            this->down[x] = true;
            
            for (int i=d; i<=u; i+=1) {
                this->dgrid[i*this->N + x] = true;
            }
        }
        return cnt;
    }
    
    
    void dropdown (array<int, 256>& grid, int x) {
        int p = -1;
        for (int y = 0; y < this->N; ++y) {
            if (this->dgrid[y*this->N+x] == false) {
                if (p > -1) {
                    int o = p*this->N+x;
                    swap(grid[y*this->N+x], grid[o]);
                    this->updatelist.emplace_back(o);
                    p += 1;
                }
            } else {
                if (p < 0) { p = y; }
                grid[y*this->N+x] = -1;
            }
        }
    }
    
// 
    bool check_horizontal (array<int, 256>& grid, int t) {
        int cnt = 1;
        int x, p;
        // R
        for (x=this->ptox[t]+1,p=t+1; x<this->N; ++x,++p,++cnt) {
            if (cnt > 2) { break; }
            if (grid[p] != grid[t]) { break; }
        }
        // L
        for (x=this->ptox[t]-1,p=t-1; x>=0; --x,--p,++cnt) {
            if (cnt > 2) { break; }
            if (grid[p] != grid[t]) { break; }
        }
        return cnt > 2;
    }
    
    bool check_vertical (array<int, 256>& grid, int t) {
        int cnt = 1;
        int y, p;
        // U
        for (y=this->ptoy[t]+1,p=t+this->N; y<this->N; ++y,p+=this->N,++cnt) {
            if (cnt > 2) { break; }
            if (grid[p] != grid[t]) { break; }
        }
        // D
        for (y=this->ptoy[t]-1,p=t-this->N; y>=0; --y,p-=this->N,++cnt) {
            if (cnt > 2) { break; }
            if (grid[p] != grid[t]) { break; }
        }
        return cnt > 2;
    }
    
    int horizontal_cnt (array<int, 256>& grid, int t) {
        int cnt = 1;
        int x, p;
        // R
        for (x=t%this->N+1,p=t+1; x<this->N; ++x,++p,++cnt) {
            if (grid[p] != grid[t]) { break; }
        }
        // L
        for (x=t%this->N-1,p=t-1; x>=0; --x,--p,++cnt) {
            if (grid[p] != grid[t]) { break; }
        }
        return max(cnt-2, 0);
    }
    
    int vertical_cnt (array<int, 256>& grid, int t) {
        int cnt = 1;
        int y, p;
        // U
        for (y=t/this->N+1,p=t+this->N; y<this->N; ++y,p+=this->N,++cnt) {
            if (grid[p] != grid[t]) { break; }
        }
        // D
        for (y=t/this->N-1,p=t-this->N; y>=0; --y,p-=this->N,++cnt) {
            if (grid[p] != grid[t]) { break; }
        }
        return max(cnt-2, 0);
    }
//
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    int C;
    int runtime;
    cin >> N >> C;
    
    Jewels jewels(N, C);
    jewels.update_grid();
    string o;
    for (int i=0; i<1000; i++) {
        o = jewels.output();
        cout << o << endl;
        cout.flush();
        jewels.update_grid();
        cin >> runtime;
        jewels.set_runtime(runtime);
        if (i == 998) { tdebug(runtime); }
    }
}