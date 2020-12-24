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


class test {
public:
    vector<bool> a;
    vector<int> t;
    int n, m;
    test (int n, int m) {
        this->n = n;
        this->m = m;
        if (this->m == 0) { return; }
        this->a = vector<bool>(n, false);
        for (int i = 0; i < m; ++i) {
            this->a[i] = true;
            this->t.emplace_back(i);
        }
    }
    bool next () {
        if (this->n == 0 || this->m == 0 || this->t[0] == this->n - this->m) { return true; }
        for (int i = 0; i < this->m; ++i) {
            int c = this->t[this->m-i-1];
            if (c == this->n-1-i) {
                continue;
            } else {
                swap(this->a[c], this->a[c+1]);
                this->t[this->m-i-1] += 1;
            }
            for (int j = 0; j < i; ++j) {
                int p1 = this->t[this->m-i-1] + 1 + j;
                int p2 = this->n-i+j;
                swap(this->a[p1], this->a[p2]);
                this->t[this->m-i+j] = p1;
            }
            return false;
        }
    }
};


class test2 {
public:
    vector<bool> a;
    vector<int> t;
    int n, m;
    test2 (int n) {
        this->n = n;
        this->m = 1;
        this->a = vector<bool>(n, false);
        this->t = vector<int>(n, 0);
        for (int i = 0; i < this->m; ++i) {
            this->a[i] = true;
            this->t[i] = i;
        }
        for (int i = 0; i < this->n; ++i) {
            this->t.emplace_back(i);
        }
    }
    bool next () {
        
        if (this->m < this->n) {
            if (this->t[0] == this->n - this->m) {
                this->m += 1;
                for (int i = 0; i < this->n; ++i) {
                    if (i < this->m) {
                        this->a[i] = true;
                        this->t[i] = i;
                    } else {
                        this->a[i] = false;
                    }
                }
                return false;
            }
        } else {
            if (this->n == 0 || this->t[0] == this->n - this->m) { return true; }
        }
        
        
        for (int i = 0; i < this->m; ++i) {
            int c = this->t[this->m-i-1];
            if (c == this->n-1-i) {
                continue;
            } else {
                swap(this->a[c], this->a[c+1]);
                this->t[this->m-i-1] += 1;
            }
            for (int j = 0; j < i; ++j) {
                int p1 = this->t[this->m-i-1] + 1 + j;
                int p2 = this->n-i+j;
                swap(this->a[p1], this->a[p2]);
                this->t[this->m-i+j] = p1;
            }
            return false;
        }
    }
};

class pppp {
public:
    int n, m, bom;
    vector<e512pos> v;
    vector<bool> f;
    vector<bool> sf;
    
    vector< vector<bool> > vflaggrid;
    pppp (vector<e512pos> v, int m) {
        this->n = v.size();
        this->m = m;
        this->v = v;
        this->f = vector<bool>(n, false);
        this->sf = vector<bool>(n, false);
        this->vflaggrid = vector< vector<bool> >(50, vector<bool>(50, false));
    }
    
};

class pppp2 {
public:
    int n, m, bom;
    vector<e512pos> v;
    vector<bool> f;
    vector<bool> sf;
    
    array< array<bool, 50>, 50> vflaggrid;
    array< array<bool, 50>, 50> eqgrid;
    
    pppp2 () {
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                this->vflaggrid[y][x] = false;
                this->eqgrid[y][x] = false;
            }
        }
    }
    pppp2 (vector<e512pos> v) {
        this->n = v.size();
        // this->m = m;
        this->v = v;
        this->f = vector<bool>(n, false);
        this->sf = vector<bool>(n, false);
        
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                this->vflaggrid[y][x] = false;
                this->eqgrid[y][x] = false;
            }
        }
    }
    void init () {
        this->n = this->v.size();
        // this->m = m;
        this->f = vector<bool>(this->n, false);
        this->sf = vector<bool>(this->n, false);
    }
};


class SuperMinesweeper {
public:
    // N 10 ~ 50
    // M mine 0.1*N*N ~ 0.3*N*N
    // D{1,2,4,5,8,9,10}
    // R |, C -
    int N, M, D;
    vector< vector<int> > Grid;
    int lastR;
    int lastC;
    
    vector<e512pos> drv;
    
    vector< vector<int> > feedbackgrid;
    vector< vector<bool> > safegrid;
    vector< vector<bool> > opengrid;
    vector< vector<bool> > flaggrid;
    double cellpoint;
    int ccnt = 0;
    int bcnt = 1;
    
    int64_t runtime = 0;
    
    SuperMinesweeper (int N, int M, int D, int row, int col) {
        this->cellpoint = 1.0 / ((N*N) - M);
        this->N = N;
        this->M = M;
        this->D = D;
        this->Grid.resize(this->N, vector<int>(this->N));
        for (int r=0; r<this->N; r++) {
            for (int c=0; c<this->N; c++) {
                this->Grid[r][c]=-1;
            }
        }
        this->Grid[row][col]=0;
        this->lastR=0;
        this->lastC=-1;
        
        pdebug(N, M, D);
        
        this->feedbackgrid = vector< vector<int> >(this->N, vector<int>(this->N, -100));
        this->safegrid = vector< vector<bool> >(this->N, vector<bool>(this->N, false));
        this->opengrid = vector< vector<bool> >(this->N, vector<bool>(this->N, false));
        this->flaggrid = vector< vector<bool> >(this->N, vector<bool>(this->N, false));
        this->opengrid[row][col] = true;
        this->update_safegrid(row, col);
        this->feedbackgrid[row][col] = 0;
        this->ccnt += 1;
        
        this->drv = this->d_range();
        
        // vector<e512pos> a;
        
        // for (auto&& i : a) {
        //     this->flaggrid[i.y][i.x] = true;
        //     this->opengrid[i.y][i.x] = true;
        //     cout << print("F", i.y, i.x) << endl;
        //     string feedback;
        //     getline(cin, feedback);
        // }
        
        
        // int y = row + 2;
        // int x = col - 1;
        // this->flaggrid[y][x] = true;
        // this->opengrid[y][x] = true;
        // cout << print("F", y, x) << endl;
        // string feedback;
        // getline(cin, feedback);
    }
    
    string nextm0 () {
        // if (this->Grid[this->lastR][this->lastC] == -1) {
        //     this->pdebug_score();
        //     return "STOP";
        // }
        int r = this->lastR;
        int c = this->lastC;
        while (true) {
            c++;
            if (c >= this->N) {
                c = 0;
                r++;
            }
            if (this->Grid[r][c]==-1) { break; }
        }
        this->lastR = r;
        this->lastC = c;
        this->opengrid[r][c] = true;
        return print("G", r, c);
    }
    
    string nextm1 () {
        if (this->runtime > 9800) { 
            return print("STOP");
        }
        
        this->search_list2();
        
        
        
        StopWatch sw;
        int r;
        int c;
        if (this->flagcnt() == this->M) {
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    if (!this->flaggrid[y][x]) { this->safegrid[y][x] = true; }
                }
            }
        }
        
        
        
        
        if (this->safecnt(r, c) > 0) {
            this->lastR = r;
            this->lastC = c;
            this->opengrid[r][c] = true;
            return print("G", r, c);
        } else {
            this->update_flaggrid();
            this->update_safegrid2();
            if (this->safecnt(r, c) > 0) {
                this->lastR = r;
                this->lastC = c;
                this->opengrid[r][c] = true;
                return print("G", r, c);
            }
            
            
            for (int z = 0; z < 2; ++z) {
                if (this->runtime + sw.get_milli_time() > 8000) { break; }
                bool loop = false;
                auto aaa = this->search_list();
                sort(aaa.begin(), aaa.end(), [](const pppp& a, const pppp& b) { return a.n < b.n; });
                
                int fcnt = 0;
                for (auto&& i : aaa) {
                    if (i.n > 22) { continue; }
                    if (this->runtime + sw.get_milli_time() > 8000) { break; }
                    // if (i.n > 20) { break; }
                    bool e = false;
                    test o(i.n, i.m);
                    while (this->runtime + sw.get_milli_time() < 8000) {
                        for (int k = 0; k < o.n; ++k) {
                            int px = i.v[k].x;
                            int py = i.v[k].y;
                            i.vflaggrid[py][px] = o.a[k];
                        }
                        
                        if (this->check(i.vflaggrid)) {
                            
                        } else {
                            for (int k = 0; k < o.n; ++k) {
                                if (o.a[k]) { i.f[k] = true; }
                                if (!o.a[k]) { i.sf[k] = true; }
                            }
                            fcnt += 1;
                        }
                        
                        for (int k = 0; k < o.n; ++k) {
                            int px = i.v[k].x;
                            int py = i.v[k].y;
                            i.vflaggrid[py][px] = false;
                        }
                        if (o.next()) {
                            for (int k = 0; k < o.n; ++k) {
                                if (i.f[k] == false) {
                                    int px = i.v[k].x;
                                    int py = i.v[k].y;
                                    this->safegrid[py][px] = true;
                                }
                                
                                if (i.sf[k] == false) {
                                    int px = i.v[k].x;
                                    int py = i.v[k].y;
                                    if (this->opengrid[py][px] == false) {
                                        this->flaggrid[py][px] = true;
                                        this->opengrid[py][px] = true;
                                        cout << print("F", py, px) << endl;
                                        string feedback;
                                        getline(cin, feedback);
                                        
                                        loop = true;
                                    }
                                }
                            }
                            
                            break;
                        }
                    }
                    
                }
                
                if (this->safecnt(r, c) > 0) {
                    this->lastR = r;
                    this->lastC = c;
                    this->opengrid[r][c] = true;
                    return print("G", r, c);
                }
                if (!loop) { break; }
            }
            
            // 2
            for (int z = 0; z < 2; ++z) {
                if (this->runtime + sw.get_milli_time() > 8000) { break; }
                bool loop = false;
                auto aaa = this->search_list2();
                
                int fcnt = 0;
                for (auto&& i : aaa) {
                    if (i.n > 22) { continue; }
                    if (this->runtime + sw.get_milli_time() > 8000) { break; }
                    // if (i.n > 20) { break; }
                    bool e = false;
                    test2 o(i.n);
                    while (this->runtime + sw.get_milli_time() < 8000) {
                        for (int k = 0; k < o.n; ++k) {
                            int px = i.v[k].x;
                            int py = i.v[k].y;
                            i.vflaggrid[py][px] = o.a[k];
                        }
                        
                        if (this->check2(i.vflaggrid, i.eqgrid)) {
                            
                        } else {
                            for (int k = 0; k < o.n; ++k) {
                                if (o.a[k]) { i.f[k] = true; }
                                if (!o.a[k]) { i.sf[k] = true; }
                            }
                            fcnt += 1;
                        }
                        
                        for (int k = 0; k < o.n; ++k) {
                            int px = i.v[k].x;
                            int py = i.v[k].y;
                            i.vflaggrid[py][px] = false;
                        }
                        if (o.next()) {
                            for (int k = 0; k < o.n; ++k) {
                                if (i.f[k] == false) {
                                    int px = i.v[k].x;
                                    int py = i.v[k].y;
                                    this->safegrid[py][px] = true;
                                }
                                
                                if (i.sf[k] == false) {
                                    int px = i.v[k].x;
                                    int py = i.v[k].y;
                                    if (this->opengrid[py][px] == false) {
                                        this->flaggrid[py][px] = true;
                                        this->opengrid[py][px] = true;
                                        cout << print("F", py, px) << endl;
                                        string feedback;
                                        getline(cin, feedback);
                                        
                                        loop = true;
                                    }
                                }
                            }
                            
                            break;
                        }
                    }
                    
                }
                
                if (this->safecnt(r, c) > 0) {
                    this->lastR = r;
                    this->lastC = c;
                    this->opengrid[r][c] = true;
                    return print("G", r, c);
                }
                if (!loop) { break; }
            }
            
            for (int z = 0; z < 2; ++z) {
                if (this->runtime + sw.get_milli_time() > 8000) { break; }
                bool loop = false;
                pppp2 aaa(this->search_range());
                if (aaa.v.size() <= 22 && aaa.v.size() > 0){
                    for (auto&& k : aaa.v) {
                        for (auto&& i : this->drv) {
                            int px = k.x + i.x;
                            int py = k.y + i.y;
                            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                            if (this->feedbackgrid[py][px] > -1) {
                                aaa.eqgrid[py][px] = true;
                            }
                        }
                    }
                    
                    bool e = false;
                    test2 o(aaa.v.size());
                    while (this->runtime + sw.get_milli_time() < 8000) {
                        for (int k = 0; k < o.n; ++k) {
                            int px = aaa.v[k].x;
                            int py = aaa.v[k].y;
                            aaa.vflaggrid[py][px] = o.a[k];
                        }
                        
                        if (this->check2(aaa.vflaggrid, aaa.eqgrid)) {
                            
                        } else {
                            for (int k = 0; k < o.n; ++k) {
                                if (o.a[k]) { aaa.f[k] = true; }
                                if (!o.a[k]) { aaa.sf[k] = true; }
                            }
                        }
                        
                        for (int k = 0; k < o.n; ++k) {
                            int px = aaa.v[k].x;
                            int py = aaa.v[k].y;
                            aaa.vflaggrid[py][px] = false;
                        }
                        if (o.next()) {
                            for (int k = 0; k < o.n; ++k) {
                                if (aaa.f[k] == false) {
                                    int px = aaa.v[k].x;
                                    int py = aaa.v[k].y;
                                    this->safegrid[py][px] = true;
                                }
                            }
                            for (int k = 0; k < o.n; ++k) {
                                if (aaa.sf[k] == false) {
                                    int px = aaa.v[k].x;
                                    int py = aaa.v[k].y;
                                    if (this->opengrid[py][px] == false) {
                                        this->flaggrid[py][px] = true;
                                        this->opengrid[py][px] = true;
                                        cout << print("F", py, px) << endl;
                                        string feedback;
                                        getline(cin, feedback);
                                        loop = true;
                                    }
                                }
                            }
                            break;
                        }
                    }
                    
                    
                    if (this->safecnt(r, c) > 0) {
                        this->lastR = r;
                        this->lastC = c;
                        this->opengrid[r][c] = true;
                        return print("G", r, c);
                    }
                }
                if (!loop) { break; }
            }
            
            
            // SA
            if (this->runtime + sw.get_milli_time() < 7000 && this->cellpoint * this->ccnt / this->bcnt < 0.2) {
                vector< vector<bool> > vflaggrid = vector< vector<bool> >(this->N, vector<bool>(this->N, false));
                vflaggrid = this->SA(2000, vflaggrid);
                if (this->check_score(vflaggrid) > 0) {
                    int bestscore = 1000000;
                    int y;
                    int x;
                    for (auto&& i : this->search_range()) {
                        // if (vflaggrid[i.y][i.x] || this->flaggrid[i.y][i.x]) { continue; }
                        if (this->flaggrid[i.y][i.x]) { continue; }
                        // if (this->cntgrid[i.y][i.x] > 0) { continue; }
                        if (this->cntgrid[i.y][i.x] < bestscore) {
                            y = i.y;
                            x = i.x;
                            bestscore = this->cntgrid[i.y][i.x];
                        }
                        
                    }
                    
                    if (bestscore < 1000000) {
                        this->lastR = y;
                        this->lastC = x;
                        this->opengrid[y][x] = true;
                        return print("G", y, x);
                    }
                }
            }
            
            if (this->flagcnt() == this->M) {
                for (int y = 0; y < this->N; ++y) {
                    for (int x = 0; x < this->N; ++x) {
                        if (!this->flaggrid[y][x]) { this->safegrid[y][x] = true; }
                    }
                }
            }
            if (this->safecnt(r, c) > 0) {
                this->lastR = r;
                this->lastC = c;
                this->opengrid[r][c] = true;
                return print("G", r, c);
            }
            
            
            // if (this->cellpoint * this->ccnt / this->bcnt < 0.015) {
            //     for (int y = 3; y < this->N-3; y+=1) {
            //         for (int x = 3+y%2; x < this->N-3; x+=2) {
            //             if (this->opengrid[y][x]) { continue; }
            //             if (this->flaggrid[y][x]) { continue; }
            //             this->lastR = y;
            //             this->lastC = x;
            //             this->opengrid[y][x] = true;
            //             return print("G", y, x);
            //         }
            //     }
            // }
            
            
            
            
            
            pdebug("[", this->search_range().size(), "]");
            
            this->pdebug_score();
            return print("STOP");
        }
    }
    
    vector< vector<int> > cntgrid;
    vector< vector<bool> > SA (int limit, vector< vector<bool> > ret) {
        StopWatch sw;
        vector< vector<bool> > tret = ret;
        vector< vector<bool> > bestret = ret;
        double bestscore = this->check_score(ret);
        double tscore = this->check_score(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        vector<e512pos> ranges = this->search_range();
        if (ranges.size() == 0) { return ret; }
        
        int cnt = 0;
        this->cntgrid = vector< vector<int> >(this->N, vector<int>(this->N, 0));
        
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            {
                int a = xrnd() % ranges.size();
                
                ret[ranges[a].y][ranges[a].x] = ret[ranges[a].y][ranges[a].x] ? false : true;
                
                
                double tmpscore = this->check_score(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 1.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore >= bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        
                        if (bestscore == 1000000) {
                            // this->fdebug_grid2(ret);
                            for (auto&& i : ranges) {
                                if (ret[i.y][i.x]) {
                                    this->cntgrid[i.y][i.x] += 1;
                                }
                            }
                            ret = tret;
                            lastscore = tscore;
                        }
                    }
                } else {
                    ret[ranges[a].y][ranges[a].x] = ret[ranges[a].y][ranges[a].x] ? false : true;
                }
                cnt += 1;
            }
            {
                int a = xrnd() % ranges.size();
                int b = xrnd() % ranges.size();
                ret[ranges[a].y][ranges[a].x] = ret[ranges[a].y][ranges[a].x] ? false : true;
                ret[ranges[b].y][ranges[b].x] = ret[ranges[b].y][ranges[b].x] ? false : true;
                
                
                double tmpscore = this->check_score(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 1.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore >= bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        
                        if (bestscore == 1000000) {
                            // this->fdebug_grid2(ret);
                            for (auto&& i : ranges) {
                                if (ret[i.y][i.x]) {
                                    this->cntgrid[i.y][i.x] += 1;
                                }
                            }
                            ret = tret;
                            lastscore = tscore;
                        }
                    }
                } else {
                    ret[ranges[b].y][ranges[b].x] = ret[ranges[b].y][ranges[b].x] ? false : true;
                    ret[ranges[a].y][ranges[a].x] = ret[ranges[a].y][ranges[a].x] ? false : true;
                }
                cnt += 1;
            }
            {
                int a = xrnd() % ranges.size();
                int b = xrnd() % ranges.size();
                swap(ret[ranges[a].y][ranges[a].x], ret[ranges[b].y][ranges[b].x]);
                double tmpscore = this->check_score(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 1.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore >= bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        if (bestscore == 1000000) {
                            
                            // this->fdebug_grid2(ret);
                            for (auto&& i : ranges) {
                                if (ret[i.y][i.x]) {
                                    this->cntgrid[i.y][i.x] += 1;
                                }
                            }
                            ret = tret;
                            lastscore = tscore;
                        }
                    }
                } else {
                    swap(ret[ranges[a].y][ranges[a].x], ret[ranges[b].y][ranges[b].x]);
                }
                cnt += 1;
            }
        }
        // pdebug(bestscore);
        return bestret;
    }
    
    
    int safecnt (int& r, int& c) {
        int ret = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->safegrid[y][x] && this->opengrid[y][x] == false && this->flaggrid[y][x] == false) {
                    ret += 1;
                    r = y;
                    c = x;
                }
            }
        }
        return ret;
    }
    
    int flagcnt () {
        int ret = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->flaggrid[y][x]) {
                    ret += 1;
                }
            }
        }
        return ret;
    }
    
    void pdebug_score () {
        pdebug(this->cellpoint * this->ccnt / this->bcnt, this->bcnt - 1, runtime);
    }
    
    void update (string feedback) {
        if (feedback.length() == 0) { return; }
        
        int value;
        string boom;
        stringstream ss(feedback);
        if (feedback.find("BOOM!") != string::npos) {
            value = -1;
            ss >> boom >> this->runtime;
            this->bcnt += 1;
            this->flaggrid[this->lastR][this->lastC] = true;//////
            
            // fdebug("a.emplace_back(",this->lastC, ",", this->lastR, ");");
            
        } else {
            ss >> value >> this->runtime;
            this->ccnt += 1;
        }
        this->Grid[this->lastR][this->lastC] = value;
        this->feedbackgrid[this->lastR][this->lastC] = value;
        if (value == 0) {
            this->update_safegrid(this->lastR, this->lastC);
        }
        
        if (this->ccnt+this->bcnt == this->N*this->N) { this->pdebug_score(); }
        
        
    }
    
    void update_safegrid (int r, int c) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if ((y-r)*(y-r) + (x-c)*(x-c) <= this->D) {
                    this->safegrid[y][x] = true;
                }
            }
        }
    }
    
    void update_safegrid2 () {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 1) { continue; }
                this->update_safegrid3(y, x);
            }
        }
    }
    void update_safegrid3 (int ty, int tx) {
        int opencnt = 0;
        int flagcnt = 0;
        int ncnt = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if ((y-ty)*(y-ty) + (x-tx)*(x-tx) <= this->D) {
                    ncnt += 1;
                    if (this->opengrid[y][x]) { opencnt += 1; }
                    if (this->flaggrid[y][x]) { flagcnt += 1; }
                }
            }
        }
        int tbn = this->feedbackgrid[ty][tx];
        if (flagcnt != tbn) { return; }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if ((y-ty)*(y-ty) + (x-tx)*(x-tx) <= this->D && this->opengrid[y][x] == false && this->flaggrid[y][x] == false) {
                    this->safegrid[y][x] = true;
                }
            }
        }
    }
    
    
    void update_flaggrid () {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 1) { continue; }
                this->update_flaggrid2(y, x);
            }
        }
    }
    void update_flaggrid2 (int ty, int tx) {
        int opencnt = 0;
        int flagcnt = 0;
        int ncnt = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if ((y-ty)*(y-ty) + (x-tx)*(x-tx) <= this->D) {
                    ncnt += 1;
                    if (this->opengrid[y][x] && !this->flaggrid[y][x]) { opencnt += 1; }
                    if (this->flaggrid[y][x]) { flagcnt += 1; }
                }
            }
        }
        
        int tbn = this->feedbackgrid[ty][tx];
        if (ncnt - opencnt != tbn) { return; }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if ((y-ty)*(y-ty) + (x-tx)*(x-tx) <= this->D && this->opengrid[y][x] == false && this->flaggrid[y][x] == false) {
                    this->flaggrid[y][x] = true;
                    cout << print("F", y, x) << endl;
                    string feedback;
                    getline(cin, feedback);
                }
            }
        }
    }
    
    void fdebug_grid () {
        unordered_set<e512pos> us;
        for (auto&& i : this->search_range()) {
            us.emplace(i);
        }
        
        
        
        for (int y = 0; y < this->N; ++y) {
            string s;
            for (int x = 0; x < this->N; ++x) {
                // if (this->flaggrid[y][x]) {
                //     s += " P";
                //     continue;
                // }
                
                
                int v = this->feedbackgrid[y][x];
                if (us.find(e512pos(x, y)) != us.end()) {
                    s += "[]";
                } else {
                    if (v < 0) {
                        s += "  ";
                    } else {
                        s += v < 10 ? " " + to_string(v) : to_string(v);
                    }
                }
                
            }
            fdebug(s);
        }
        fdebug("");
        
    }
    
    void fdebug_grid2 (vector< vector<bool> >& vflaggrid) {
        unordered_set<e512pos> us;
        for (auto&& i : this->search_range()) {
            us.emplace(i);
        }
        
        
        
        for (int y = 0; y < this->N; ++y) {
            string s;
            for (int x = 0; x < this->N; ++x) {
                if (this->flaggrid[y][x] || vflaggrid[y][x]) {
                    s += " P";
                    continue;
                }
                
                
                int v = this->feedbackgrid[y][x];
                if (us.find(e512pos(x, y)) != us.end()) {
                    s += "[]";
                } else {
                    if (v < 0) {
                        s += "  ";
                    } else {
                        s += v < 10 ? " " + to_string(v) : to_string(v);
                    }
                }
                
            }
            fdebug(s);
        }
        fdebug("");
        
    }
    
    vector<e512pos> d_range () {
        vector<e512pos> ret;
        if(this->D == 1) {
            ret.emplace_back(0, -1);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(0, 1);
        }
        if(this->D == 2) {
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
        }
        if(this->D == 4) {
            ret.emplace_back(0, -2);
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(-2, 0);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(2, 0);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
            ret.emplace_back(0, 2);
        }
        if(this->D == 5) {
            ret.emplace_back(-1, -2);
            ret.emplace_back(0, -2);
            ret.emplace_back(1, -2);
            ret.emplace_back(-2, -1);
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(2, -1);
            ret.emplace_back(-2, 0);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(2, 0);
            ret.emplace_back(-2, 1);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
            ret.emplace_back(2, 1);
            ret.emplace_back(-1, 2);
            ret.emplace_back(0, 2);
            ret.emplace_back(1, 2);
        }
        if(this->D == 8) {
            ret.emplace_back(-2, -2);
            ret.emplace_back(-1, -2);
            ret.emplace_back(0, -2);
            ret.emplace_back(1, -2);
            ret.emplace_back(2, -2);
            ret.emplace_back(-2, -1);
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(2, -1);
            ret.emplace_back(-2, 0);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(2, 0);
            ret.emplace_back(-2, 1);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
            ret.emplace_back(2, 1);
            ret.emplace_back(-2, 2);
            ret.emplace_back(-1, 2);
            ret.emplace_back(0, 2);
            ret.emplace_back(1, 2);
            ret.emplace_back(2, 2);
        }
        if(this->D == 9) {
            ret.emplace_back(0, -3);
            ret.emplace_back(-2, -2);
            ret.emplace_back(-1, -2);
            ret.emplace_back(0, -2);
            ret.emplace_back(1, -2);
            ret.emplace_back(2, -2);
            ret.emplace_back(-2, -1);
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(2, -1);
            ret.emplace_back(-3, 0);
            ret.emplace_back(-2, 0);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(2, 0);
            ret.emplace_back(3, 0);
            ret.emplace_back(-2, 1);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
            ret.emplace_back(2, 1);
            ret.emplace_back(-2, 2);
            ret.emplace_back(-1, 2);
            ret.emplace_back(0, 2);
            ret.emplace_back(1, 2);
            ret.emplace_back(2, 2);
            ret.emplace_back(0, 3);
        }
        if(this->D == 10) {
            ret.emplace_back(-1, -3);
            ret.emplace_back(0, -3);
            ret.emplace_back(1, -3);
            ret.emplace_back(-2, -2);
            ret.emplace_back(-1, -2);
            ret.emplace_back(0, -2);
            ret.emplace_back(1, -2);
            ret.emplace_back(2, -2);
            ret.emplace_back(-3, -1);
            ret.emplace_back(-2, -1);
            ret.emplace_back(-1, -1);
            ret.emplace_back(0, -1);
            ret.emplace_back(1, -1);
            ret.emplace_back(2, -1);
            ret.emplace_back(3, -1);
            ret.emplace_back(-3, 0);
            ret.emplace_back(-2, 0);
            ret.emplace_back(-1, 0);
            ret.emplace_back(0, 0);
            ret.emplace_back(1, 0);
            ret.emplace_back(2, 0);
            ret.emplace_back(3, 0);
            ret.emplace_back(-3, 1);
            ret.emplace_back(-2, 1);
            ret.emplace_back(-1, 1);
            ret.emplace_back(0, 1);
            ret.emplace_back(1, 1);
            ret.emplace_back(2, 1);
            ret.emplace_back(3, 1);
            ret.emplace_back(-2, 2);
            ret.emplace_back(-1, 2);
            ret.emplace_back(0, 2);
            ret.emplace_back(1, 2);
            ret.emplace_back(2, 2);
            ret.emplace_back(-1, 3);
            ret.emplace_back(0, 3);
            ret.emplace_back(1, 3);
        }
        return ret;
    }
    
    
    vector<e512pos> _search_range () {
        static bool t[50][50];
        vector<e512pos> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                t[y][x] = false;
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                for (auto&& i : this->drv) {
                    int px = i.x + x;
                    int py = i.y + y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    t[py][px] = true;
                }
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (t[y][x]) { ret.emplace_back(x, y); }
            }
        }
        return ret;
    }
    
    vector<e512pos> search_range () {
        static bool t[50][50];
        vector<e512pos> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                t[y][x] = false;
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                for (auto&& i : this->drv) {
                    int px = i.x + x;
                    int py = i.y + y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    t[py][px] = true;
                }
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (t[y][x] && this->feedbackgrid[y][x] < 0 && !this->opengrid[y][x] && !this->flaggrid[y][x]) { ret.emplace_back(x, y); }
            }
        }
        return ret;
    }
    
    int vflag_score (int ty, int tx) {
        int score = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                int bcnt = 0;
                for (auto&& i : this->drv) {
                    int px = i.x + x;
                    int py = i.y + y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    if (this->flaggrid[py][px]) { bcnt += 1; }
                }
                if (bcnt == this->feedbackgrid[y][x]) {
                    score -= 10;
                }
                if (bcnt < this->feedbackgrid[y][x]) {
                    score -= 10;
                }
            }
        }
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                int bcnt = 0;
                for (auto&& i : this->drv) {
                    int px = i.x + x;
                    int py = i.y + y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    if (this->flaggrid[py][px] || (px == tx && py == ty)) { bcnt += 1; }
                }
                if (bcnt == this->feedbackgrid[y][x]) {
                    score += 10;
                }
                if (bcnt < this->feedbackgrid[y][x]) {
                    score += 10;
                }
                if (bcnt > this->feedbackgrid[y][x]) {
                    score -= 10000;
                }
            }
        }
        return score;
    }
    
    double check_score (vector< vector<bool> >& vflaggrid) {
        int score = 0;
        int score2 = 0;
        int cnt = 0;
        int fcnt = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                cnt += 1;
                if (this->fb_cnt(vflaggrid, y, x) == this->feedbackgrid[y][x]) {
                    score += 1;
                }
                // if (this->fb_cnt(vflaggrid, y, x) < this->feedbackgrid[y][x]) {
                //     score2 += 1;
                // }
                // if (this->fb_cnt(vflaggrid, y, x) > this->feedbackgrid[y][x]) {
                //     score2 -= 100;
                // }
                // if (vflaggrid[y][x]) { fcnt += 1; }
            }
            
            
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (vflaggrid[y][x]) { fcnt += 1; }
            }
            
            
        }
        
        
        if (cnt == score) { return 1000000; }
        return score + score2 + fcnt *0.1;
    }
    
    int fb_cnt (vector< vector<bool> >& vflaggrid, int y, int x) {
        int cnt = 0;
        for (auto&& i : this->drv) {
            int px = x + i.x;
            int py = y + i.y;
            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
            if (vflaggrid[py][px] || this->flaggrid[py][px]) {
                cnt += 1;
            }
        }
        return cnt;
    }
    int fb_cnt (array< array<bool, 50>, 50>& vflaggrid, int y, int x) {
        int cnt = 0;
        for (auto&& i : this->drv) {
            int px = x + i.x;
            int py = y + i.y;
            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
            if (vflaggrid[py][px] || this->flaggrid[py][px]) {
                cnt += 1;
            }
        }
        return cnt;
    }
    
    bool check (vector< vector<bool> >& vflaggrid) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                if (this->fb_cnt(vflaggrid, y, x) > this->feedbackgrid[y][x]) {
                    return true;
                }
            }
        }
        return false;
    }
    
    vector<pppp> search_list () {
        vector<pppp> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 1) { continue; }
                vector<e512pos> v;
                int bcnt = this->feedbackgrid[y][x];
                int fcnt = 0;
                for (auto&& i : this->drv) {
                    int px = x + i.x;
                    int py = y + i.y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    if (this->flaggrid[py][px]) {
                        bcnt -= 1;
                        continue;
                    }
                    if (this->feedbackgrid[py][px] < 0) {
                        v.emplace_back(px, py);
                    }
                }
                if (bcnt > 0) {
                    ret.emplace_back(v, bcnt);
                }
            }
        }
        return ret;
    }
    
    
    
    bool check2 (array< array<bool, 50>, 50>& vflaggrid, array< array<bool, 50>, 50>& eqgrid) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                int fbc = this->fb_cnt(vflaggrid, y, x);
                if (eqgrid[y][x] && fbc != this->feedbackgrid[y][x]) { return true; }
                if (fbc > this->feedbackgrid[y][x]) { return true; }
            }
        }
        return false;
    }
    
    vector<pppp2> search_list2 () {
        vector<pppp2> ret;
        
        vector<e512pos> ac = this->activecells();
        
        unordered_map<e512pos, vector<e512pos> > uac;
        for (auto&& i : ac) { uac.emplace(i, this->activecells_range(i.y, i.x)); }
        vector<e512pos> tpos;
        unordered_set<e512pos> upos;
        
        while (uac.size() > 0) {
            tpos.clear();
            upos.clear();
            pppp2 a;
            
            for (auto&& i : uac) {
                for (auto&& j : i.second) {
                    upos.emplace(j);
                }
                tpos.emplace_back(i.first);
                break;
            }
            
            uac.erase(tpos[tpos.size()-1]);
            while (upos.size() < 8 && uac.size() > 0) {
                e512pos best;
                int bestcnt = 0;
                for (auto&& i : uac) {
                    int cnt = 0;
                    for (auto&& j : i.second) {
                        if (upos.find(j) != upos.end()) { cnt += 1; }
                    }
                    if (cnt > bestcnt) {
                        best = i.first;
                        bestcnt = cnt;
                    }
                }
                if (bestcnt > 0) {
                    for (auto&& j : uac[best]) {
                        upos.emplace(j);
                    }
                    uac.erase(best);
                    tpos.emplace_back(best);
                } else {
                    break;
                }
                
                
                
                
                
            }
            
            for (auto&& i : upos) { a.v.emplace_back(i); }
            a.init();
            for (auto&& i : tpos) { a.eqgrid[i.y][i.x] = true; }
            ret.emplace_back(a);
        }
        
        
        return ret;
    }
    
    vector<e512pos> activecells () {
        vector<e512pos> ret;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->feedbackgrid[y][x] < 0) { continue; }
                int cnt = 0;
                for (auto&& i : this->drv) {
                    int px = x + i.x;
                    int py = y + i.y;
                    if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                    if (this->feedbackgrid[py][px] < 0 && !this->flaggrid[py][px] && !this->opengrid[py][px]) {
                        cnt += 1;
                    }
                }
                if (cnt > 0) {
                    ret.emplace_back(x, y);
                }
            }
        }
        return ret;
    }
    
    vector<e512pos> activecells_range (int y, int x) {
        vector<e512pos> ret;
        for (auto&& i : this->drv) {
            int px = x + i.x;
            int py = y + i.y;
            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
            if (this->feedbackgrid[py][px] < 0 && !this->flaggrid[py][px] && !this->opengrid[py][px]) {
                ret.emplace_back(px, py);
            }
        }
        return ret;
    }
    
    
    
};

int main() {
    string feedback;
    int N, M, D, row, col;
    cin >> N >> M >> D >> row >> col;
    getline(cin, feedback); // read endline
  
    SuperMinesweeper prog(N, M, D, row, col);
    
    while (true) {
        string nextm = prog.nextm1();
        
        // prog.fdebug_grid();
        // cerr.flush();
        
        cout << nextm << endl;
        cout.flush();
        
        
        if (nextm.find("STOP") != string::npos) {
            cout << "STOP" << endl;
            cout.flush();
            break;
        } else {
            getline(cin, feedback);
            prog.update(feedback);
        }
    }

    return 0;
}