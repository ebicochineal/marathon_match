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

struct bridge {
    int a, b, v;
    bridge () {}
    bridge (int a, int b, int v) {
        this->a = a;
        this->b = b;
        this->v = v;
    }
};



class MM {
public:
    StopWatch sw;
    int N, C;
    vector<bridge> ans;
    vector<bridge> btmp;
    vector<int> grid;
    
    bitset<1024> coli;
    vector< vector<int> > urdlp;
    vector<int> vv;
    MM () { this->sw = StopWatch(); }
    void input () {
        
        cin >> this->N >> this->C;
        
        this->grid = vector<int>(this->N*this->N, 0);
        
        for (int row = 0; row < this->N; row++) {
            for (int col = 0; col < this->N; col++) {
                cin >> this->grid[row * this->N + col];
                if (this->grid[row * this->N + col] > 0) {
                    this->coli[row*this->N+col] = true;
                }
            }
        }
        
        this->urdlp = vector< vector<int> >(this->N*this->N, vector<int>(4, -1));
        for (int row = 0; row < this->N; ++row) {
            for (int col = 0; col < this->N; ++col) {
                int p = row * this->N + col;
                if (this->grid[p] == 0) { continue; }
                
                int maxv = min(this->grid[p], this->C);
                
                
                // up
                for (int v = row-1; v >= 0; --v) {
                    int np = v * this->N + col;
                    if (this->grid[np] > 0) {
                        this->urdlp[p][0] = np;
                        break;
                    }
                }
                // right
                for (int h = col+1; h < this->N; ++h) {
                    int np = row * this->N + h;
                    if (this->grid[np] > 0) {
                        this->urdlp[p][1] = np;
                        break;
                    }
                }
                // down
                for (int v = row+1; v < this->N; ++v) {
                    int np = v * this->N +col;
                    if (this->grid[np] > 0) {
                        this->urdlp[p][2] = np;
                        break;
                    }
                }
                // left
                for (int h = col-1; h >= 0; --h) {
                    int np = row * this->N + h;
                    if (this->grid[np] > 0) {
                        this->urdlp[p][3] = np;
                        break;
                    }
                }
            }
        }
        
        for (int row = 0; row < this->N; ++row) {
            for (int col = 0; col < this->N; ++col) {
                int p = row * this->N + col;
                if (this->grid[p] == 0) { continue; }
                
                int maxv = min(this->grid[p], this->C);
                
                for (int d = 0; d < 4; ++d) {
                    int np = this->urdlp[p][d];
                    if (np < 0) { continue; }
                    int maxn = next_check(p, np, this->grid, this->coli);
                    if ((this->grid[np]-maxv-maxn) > 0) { this->urdlp[p][d] = -1; }
                }
            }
        }
        
        for (int row = 0; row < this->N; row++) {
            for (int col = 0; col < this->N; col++) {
                int p = row * this->N + col;
                if (this->grid[p] == 0) { continue; }
                bool f = false;
                
                for (int d = 0; d < 4; ++d) {
                    if (this->urdlp[p][d] != -1) { f = true; }
                }
                
                if (f) { this->vv.emplace_back(p); }
            }
        }
        
        
    }
    
    void output () {
        pdebug(this->N, this->C, this->sw.get_milli_time());
        
        //this->remove_double(this->ans);
        
        cout << this->ans.size() << endl;
        for (auto&& i : this->ans) {
            cout << print(i.a/this->N, i.a%this->N, i.b/this->N, i.b%this->N, i.v) << endl;
        }
    }
    
    bool isputbridge (int d, int p, int np, bitset<1024>& tcoli) {
        if (d == 0) {
            for (int i = np+this->N; i < p; i+=this->N) {
                if (tcoli[i]) { return false; }
            }
        } else if (d == 1) {
            for (int i = p+1; i < np; i+=1) {
                if (tcoli[i]) { return false; }
            }
        } else if (d == 2) {
            for (int i = p+this->N; i < np; i+=this->N) {
                if (tcoli[i]) { return false; }
            }
        } else {
            for (int i = np+1; i < p; i+=1) {
                if (tcoli[i]) { return false; }
            }
        }
        return true;
    }
    
    void fillbridge (int d, int p, int np, bitset<1024>& tcoli) {
        if (d == 0) {
            for (int i = np+this->N; i < p; i+=this->N) {
                tcoli[i] = true;
            }
        } else if (d == 1) {
            for (int i = p+1; i < np; i+=1) {
                tcoli[i] = true;
            }
        } else if (d == 2) {
            for (int i = p+this->N; i < np; i+=this->N) {
                tcoli[i] = true;
            }
        } else {
            for (int i = np+1; i < p; i+=1) {
                tcoli[i] = true;
            }
        }
    }
    
    int next_check (const int prevp, const int nextp, vector<int>& tgrid, bitset<1024>& tcoli) {
        int tv = 0;
        for (int d = 0; d < 4; ++d) {
            int np = this->urdlp[nextp][d];
            if (prevp == np) { continue; }
            if (np < 0) { continue; }
            if (tgrid[np] == 0) { continue; }
            if (this->isputbridge(d, nextp, np, tcoli)) {
                tv += min(tgrid[np], this->C);
            }
        }
        return tv;
    }
    
    
    vector<bridge> tmp;
    void bridgeset_search (int p, bitset<1024>& tcoli, vector<int>& tgrid) {
        static int drn[24][4] = {
                                    {0, 1, 2, 3},
                                    {0, 1, 3, 2},
                                    {0, 2, 1, 3},
                                    {0, 2, 3, 1},
                                    {0, 3, 1, 2},
                                    {0, 3, 2, 1},
                                    {1, 0, 2, 3},
                                    {1, 0, 3, 2},
                                    {1, 2, 0, 3},
                                    {1, 2, 3, 0},
                                    {1, 3, 0, 2},
                                    {1, 3, 2, 0},
                                    {2, 0, 1, 3},
                                    {2, 0, 3, 1},
                                    {2, 1, 0, 3},
                                    {2, 1, 3, 0},
                                    {2, 3, 0, 1},
                                    {2, 3, 1, 0},
                                    {3, 0, 1, 2},
                                    {3, 0, 2, 1},
                                    {3, 1, 0, 2},
                                    {3, 1, 2, 0},
                                    {3, 2, 0, 1},
                                    {3, 2, 1, 0},
                                };
        
        
        static vector<int> q;
        q.clear();
        this->tmp.clear();
        q.emplace_back(p);
        
        
        while (q.size()) {
            p = q.back();
            q.pop_back();
            int x = xrnd() % 24;
            for (int i = 0; i < 4; ++i) {
                int d = drn[x][i];
                
                int np = this->urdlp[p][d];
                if (np < 0) { continue; }
                if (tgrid[np] == 0) { continue; }
                if (tgrid[p] == 0) { continue; }
                if (this->isputbridge(d, p, np, tcoli)) {
                    int maxv = min(min(tgrid[p], tgrid[np]), this->C);
                    
                    int maxn = this->next_check(p, np, tgrid, tcoli);
                    
                    if ((tgrid[np]-maxv-maxn) > 0) { continue; }
                    
                    
                    tgrid[p] -= maxv;
                    tgrid[np] -= maxv;
                    this->fillbridge(d, p, np, tcoli);
                    this->tmp.emplace_back(p, np, maxv);
                    if (tgrid[np] > 0) { q.emplace_back(np); }
                }
            }
            
            if (tgrid[p] > 0) {
                this->tmp.clear();
                return;
            }
        }
        
        return;
    };
    
    void remove_double (vector<bridge>& t) {
        this->btmp = t;
        t.clear();
        for (auto&& i : this->btmp) {
            bool f = true;
            for (auto&& j : t) {
                if (i.a == j.a && i.b == j.b) {
                    j.v += i.v;
                    f = false;
                    break;
                }
                if (i.a == j.b && i.b == j.a) {
                    j.v += i.v;
                    f = false;
                    break;
                }
            }
            if (f) { t.emplace_back(i); }
        }
    }
    
    void bridgeset_expansion_search (bitset<1024>& tcoli, vector<int>& tgrid) {
        static int drn[24][4] = {
                                    {0, 1, 2, 3},
                                    {0, 1, 3, 2},
                                    {0, 2, 1, 3},
                                    {0, 2, 3, 1},
                                    {0, 3, 1, 2},
                                    {0, 3, 2, 1},
                                    {1, 0, 2, 3},
                                    {1, 0, 3, 2},
                                    {1, 2, 0, 3},
                                    {1, 2, 3, 0},
                                    {1, 3, 0, 2},
                                    {1, 3, 2, 0},
                                    {2, 0, 1, 3},
                                    {2, 0, 3, 1},
                                    {2, 1, 0, 3},
                                    {2, 1, 3, 0},
                                    {2, 3, 0, 1},
                                    {2, 3, 1, 0},
                                    {3, 0, 1, 2},
                                    {3, 0, 2, 1},
                                    {3, 1, 0, 2},
                                    {3, 1, 2, 0},
                                    {3, 2, 0, 1},
                                    {3, 2, 1, 0},
                                };
        
        
        static vector<int> q;
        q.clear();
        
        int p = 0;
        // q.emplace_back(p);
        
        static vector<int> ind;
        
        
        
        int c = 1 + xrnd()%(this->C-1);
        ind.clear();
        
        
        for (int i = 0; i < this->tmp.size(); ++i) {
            if (this->tmp[i].v > c) {
                int tc;
                p = this->tmp[i].a;
                tc = c;
                for (int d = 0; d < 4; ++d) {
                    int np = this->urdlp[p][d];
                    if (np < 0) { continue; }
                    if (tgrid[np] == 0) { continue; }
                    if (this->isputbridge(d, p, np, tcoli)) {
                        const int v = min(tgrid[np], this->C);
                        if (tc > v) {
                            tc -= v;
                        } else {
                            tc = 0;
                        }
                    }
                }
                if (tc > 0) { continue; }
                
                p = this->tmp[i].b;
                tc = c;
                for (int d = 0; d < 4; ++d) {
                    int np = this->urdlp[p][d];
                    if (np < 0) { continue; }
                    if (tgrid[np] == 0) { continue; }
                    if (this->isputbridge(d, p, np, tcoli)) {
                        const int v = min(tgrid[np], this->C);
                        if (tc > v) {
                            tc -= v;
                        } else {
                            tc = 0;
                        }
                    }
                }
                if (tc > 0) { continue; }
                ind.emplace_back(i);
            }
        }
        
        if (ind.size() == 0) { return; }
        
        int y = xrnd() % ind.size();
        this->tmp[ind[y]].v -= c;
        tgrid[this->tmp[ind[y]].a] += c;
        tgrid[this->tmp[ind[y]].b] += c;
        q.emplace_back(this->tmp[ind[y]].a);
        q.emplace_back(this->tmp[ind[y]].b);
        
        int a = this->tmp[ind[y]].a;
        int b = this->tmp[ind[y]].b;
        
        while (q.size()) {
            p = q.back();
            q.pop_back();
            int x = xrnd() % 24;
            
            int dc = -1;
            for (int i = 0; i < 4; ++i) {
                int d = drn[x][i];
                
                int np = this->urdlp[p][d];
                
                // if ((p == a && np == b) || (p == b && np == a)) { continue; }
                if (np < 0) { continue; }
                if (tgrid[np] == 0) { continue; }
                if (tgrid[p] == 0) { continue; }
                
                if (this->isputbridge(d, p, np, tcoli)) {
                    int maxv = min(min(tgrid[p], tgrid[np]), this->C);
                    
                    
                    int maxn = this->next_check(p, np, tgrid, tcoli);
                    
                    if ((tgrid[np]-maxv-maxn) > 0) { continue; }
                    
                    
                    tgrid[p] -= maxv;
                    tgrid[np] -= maxv;
                    this->fillbridge(d, p, np, tcoli);
                    this->tmp.emplace_back(p, np, maxv);
                    if (tgrid[np] > 0) { q.emplace_back(np); }
                }
            }
            if (tgrid[p] > 0) {
                this->tmp.clear();
                return;
            }
        }
        
        this->remove_double(this->tmp);
        
        return;
    };
    
    
    void solve1 (vector<bridge>& ret, int& retscore) {
        static vector<int> tgrid = this->grid;
        static bitset<1024> tcoli = this->coli;
        
        static vector<int> reftgrid = this->grid;
        static bitset<1024> reftcoli = this->coli;
        
        static vector<int> bestgrid = this->grid;
        static bitset<1024> bestcoli = this->coli;
        static vector<bridge> bestbridges;
        
        static vector<int> vgrid = this->grid;
        static bitset<1024> vcoli = this->coli;
        static vector<bridge> vbridges;
        
        static vector<int> v2grid = this->grid;
        static bitset<1024> v2coli = this->coli;
        static vector<bridge> v2bridges;
        
        tgrid = this->grid;
        tcoli = this->coli;
        
        int cnt = 0;
        int score = 0;
        
        static bitset<1024> pf;
        
        
        
        mt19937 mt(xrnd());
        shuffle(this->vv.begin(), this->vv.end(), mt);
        
        int bestrc = -1;
        for (int z = 0; z < 16; ++z) {
            int bestscore = 0;
            bestbridges.clear();
            
            if (z <= 0) {
                bestrc = -1;
                for (int i = 0; i < 24; ++i) {
                    for (auto&& rc : this->vv) {
                        int v = tgrid[rc];
                        if (v == 0) { continue; }
                        reftgrid = tgrid;
                        reftcoli = tcoli;
                        this->bridgeset_search(rc, reftcoli, reftgrid);
                        
                        score = 0;
                        pf.reset();
                        cnt = 0;
                        for (auto&& i : this->tmp) {
                            cnt += !(pf[i.a]);
                            score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                            pf[i.a] = true;
                            cnt += !(pf[i.b]);
                            score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                            pf[i.b] = true;
                        }
                        score += cnt * cnt;
                        
                        
                        if (score < bestscore * 0.15) { continue; }
                        
                        int vscore = score;
                        int f = true;
                        
                        vgrid = reftgrid;
                        vcoli = reftcoli;
                        vbridges = this->tmp;
                        for (int w = 0; w < 16; ++w) {
                            if (f == false) { break; }
                            if (this->sw.get_milli_time() >= 9800) { break; }
                            if (z > 0) { break; }
                            f = false;
                            v2grid = vgrid;
                            v2coli = vcoli;
                            v2bridges = vbridges;
                            for (int e = 0; e < v2bridges.size()*2; ++e) {
                                this->tmp = v2bridges;
                                reftcoli = v2coli;
                                reftgrid = v2grid;
                                
                                this->bridgeset_expansion_search(reftcoli, reftgrid);
                                score = 0;
                                pf.reset();
                                cnt = 0;
                                for (auto&& i : this->tmp) {
                                    cnt += !(pf[i.a]);
                                    score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                                    pf[i.a] = true;
                                    cnt += !(pf[i.b]);
                                    score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                                    pf[i.b] = true;
                                }
                                score += cnt * cnt;
                                
                                if (score > vscore) {
                                    vscore = score;
                                    vgrid = reftgrid;
                                    vcoli = reftcoli;
                                    vbridges = this->tmp;
                                    f = true;
                                }
                            }
                        }
                        
                        
                        if (vscore > bestscore) {
                            bestscore = vscore;
                            bestgrid = vgrid;
                            bestcoli = vcoli;
                            bestbridges = vbridges;
                            bestrc = rc;
                        }
                        
                    }
                }
                if (bestrc != -1) {
                    for (int i = 0; i < 64; ++i) {
                        int v = tgrid[bestrc];
                        if (v == 0) { continue; }
                        reftgrid = tgrid;
                        reftcoli = tcoli;
                        this->bridgeset_search(bestrc, reftcoli, reftgrid);
                        
                        score = 0;
                        pf.reset();
                        cnt = 0;
                        for (auto&& i : this->tmp) {
                            cnt += !(pf[i.a]);
                            score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                            pf[i.a] = true;
                            cnt += !(pf[i.b]);
                            score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                            pf[i.b] = true;
                        }
                        score += cnt * cnt;
                        
                        if (score < bestscore * 0.5) { continue; }
                        
                        int vscore = score;
                        int f = true;
                        
                        vgrid = reftgrid;
                        vcoli = reftcoli;
                        vbridges = this->tmp;
                        for (int w = 0; w < 16; ++w) {
                            if (f == false) { break; }
                            if (this->sw.get_milli_time() >= 9800) { break; }
                            if (z > 0) { break; }
                            f = false;
                            v2grid = vgrid;
                            v2coli = vcoli;
                            v2bridges = vbridges;
                            for (int e = 0; e < v2bridges.size()*2; ++e) {
                                this->tmp = v2bridges;
                                reftcoli = v2coli;
                                reftgrid = v2grid;
                                
                                this->bridgeset_expansion_search(reftcoli, reftgrid);
                                score = 0;
                                pf.reset();
                                cnt = 0;
                                for (auto&& i : this->tmp) {
                                    cnt += !(pf[i.a]);
                                    score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                                    pf[i.a] = true;
                                    cnt += !(pf[i.b]);
                                    score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                                    pf[i.b] = true;
                                }
                                score += cnt * cnt;
                                
                                if (score > vscore) {
                                    vscore = score;
                                    vgrid = reftgrid;
                                    vcoli = reftcoli;
                                    vbridges = this->tmp;
                                    f = true;
                                }
                            }
                        }
                        
                        if (vscore > bestscore) {
                            bestscore = vscore;
                            bestgrid = vgrid;
                            bestcoli = vcoli;
                            bestbridges = vbridges;
                        }
                    }
                }
            } else {
                for (int i = 0; i < 32; ++i) {
                    for (auto&& rc : this->vv) {
                        int v = tgrid[rc];
                        if (v == 0) { continue; }
                        reftgrid = tgrid;
                        reftcoli = tcoli;
                        this->bridgeset_search(rc, reftcoli, reftgrid);
                        
                        score = 0;
                        pf.reset();
                        cnt = 0;
                        for (auto&& i : this->tmp) {
                            cnt += !(pf[i.a]);
                            score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                            pf[i.a] = true;
                            cnt += !(pf[i.b]);
                            score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                            pf[i.b] = true;
                        }
                        score += cnt * cnt;
                        
                        
                        
                        
                        if (score < bestscore * 0.25) { continue; }
                        
                        int vscore = score;
                        int f = true;
                        
                        vgrid = reftgrid;
                        vcoli = reftcoli;
                        vbridges = this->tmp;
                        for (int w = 0; w < 16; ++w) {
                            if (f == false) { break; }
                            if (this->sw.get_milli_time() >= 9800) { break; }
                            if (z > 0) { break; }
                            f = false;
                            v2grid = vgrid;
                            v2coli = vcoli;
                            v2bridges = vbridges;
                            for (int e = 0; e < v2bridges.size()*2; ++e) {
                                this->tmp = v2bridges;
                                reftcoli = v2coli;
                                reftgrid = v2grid;
                                
                                this->bridgeset_expansion_search(reftcoli, reftgrid);
                                score = 0;
                                pf.reset();
                                cnt = 0;
                                for (auto&& i : this->tmp) {
                                    cnt += !(pf[i.a]);
                                    score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                                    pf[i.a] = true;
                                    cnt += !(pf[i.b]);
                                    score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                                    pf[i.b] = true;
                                }
                                score += cnt * cnt;
                                
                                if (score > vscore) {
                                    vscore = score;
                                    vgrid = reftgrid;
                                    vcoli = reftcoli;
                                    vbridges = this->tmp;
                                    f = true;
                                }
                            }
                        }
                        
                        
                        if (vscore > bestscore) {
                            bestscore = vscore;
                            bestgrid = vgrid;
                            bestcoli = vcoli;
                            bestbridges = vbridges;
                        }
                        
                    }
                }
            
            }
            if (bestscore == 0 || this->sw.get_milli_time() > 9800) { break; }
            bool f = true;
            for (int w = 0; w < 64; ++w) {
                if (f == false) { break; }
                if (this->sw.get_milli_time() >= 9800) { break; }
                if (z > 2) { break; }
                f = false;
                for (int e = 0; e < bestbridges.size()*4; ++e) {
                    this->tmp = bestbridges;
                    reftcoli = bestcoli;
                    reftgrid = bestgrid;
                    
                    this->bridgeset_expansion_search(reftcoli, reftgrid);
                    score = 0;
                    pf.reset();
                    cnt = 0;
                    for (auto&& i : this->tmp) {
                        cnt += !(pf[i.a]);
                        score += this->grid[i.a] * this->grid[i.a] * !(pf[i.a]);
                        pf[i.a] = true;
                        cnt += !(pf[i.b]);
                        score += this->grid[i.b] * this->grid[i.b] * !(pf[i.b]);
                        pf[i.b] = true;
                    }
                    score += cnt * cnt;
                    
                    if (score > bestscore) {
                        bestscore = score;
                        bestgrid = reftgrid;
                        bestcoli = reftcoli;
                        bestbridges = this->tmp;
                        f = true;
                    }
                }
            }
            
            tgrid = bestgrid;
            tcoli = bestcoli;
            
            for (auto&& i : bestbridges) { ret.emplace_back(i); }
            
            retscore += bestscore;
            
        }
        
    }
    
    void solve () {
        int bestscore = 0;
        int cnt = 0;
        while (this->sw.get_milli_time() < 9800) {
            int score = 0;
            vector<bridge> t;
            this->solve1(t, score);
            if (score > bestscore) {
                bestscore = score;
                this->ans = t;
            }
            cnt += 1;
        }
        
        pdebug(cnt, bestscore);
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

