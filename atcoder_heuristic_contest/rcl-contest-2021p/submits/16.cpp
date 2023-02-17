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
        size_t operator()(const e512pos& t) const{ return t.x<<16 | t.y; }
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

struct Vege {
    int r, c, s, e, v;
    Vege () {}
    Vege (int r, int c, int s, int e, int v) {
        this->r = r;
        this->c = c;
        this->s = s;
        this->e = e;
        this->v = v;
    }
};
ostream& operator << (ostream& os, const Vege& p) {
    os << print(p.r, p.c, p.s, p.e, p.v);
    return os;
};

struct Com {
    int a, b, c, d;
    Com () {
        this->a = -1;
        this->b = -1;
        this->c = -1;
        this->d = -1;
    }
    Com (int a, int b) {
        this->a = a;
        this->b = b;
        this->c = -1;
        this->d = -1;
    }
    Com (int a, int b, int c, int d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};
ostream& operator << (ostream& os, const Com& p) {
    if (p.a < 0) {
        os << -1;
    } else if (p.c < 0) {
        os << print(p.a, p.b);
    } else {
        os << print(p.a, p.b, p.c, p.d);
    }
    return os;
};
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct VegeGrid {
    // int size;
    array<int, 256> ends;
    array<int, 256> vals;
    VegeGrid () {
        for (int i = 0; i < 256; ++i) {
            this->ends[i] = 0;
            this->vals[i] = 0;
        }
    }
    
    void update_f (vector<Vege>& veges, int turn) {
        for (auto&& i : veges) {
            if (i.s == turn) {
                int p = i.r * 16 + i.c;
                this->ends[p] = i.e;
                this->vals[p] = i.v;
            }
        }
    }
    
    int harvest (vector<Vege>& veges, bitset<256>& hg) {
        static bitset<256> bs;
        static vector<int> v;
        static vector<int> o;
        for (int i = 0; i < 256; ++i) { bs[i] = 0; }
        
        
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (!hg[i] || bs[i]) { continue; }
            v.clear();
            o.clear();
            
            o.emplace_back(i);
            bs[i] = true;
            while (o.size() > 0) {
                int t = o.back();
                v.emplace_back(t);
                int x = t % 16;
                int y = t / 16;
                o.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py * 16 + px;
                    if (!insidexywh(px, py, 16, 16) || bs[p] || !hg[p]) { continue; }
                    o.emplace_back(p);
                    bs[p] = true;
                }
            }
            
            int cnt = v.size();
            for (auto&& i : v) {
                r += this->vals[i] * cnt;
                this->ends[i] = 0;
                this->vals[i] = 0;
            }
        }
        
        return r;
    }
    
    int vharvest (vector<Vege>& veges, bitset<256>& hg, int t) {
        static bitset<256> bs;
        static vector<int> v;
        static vector<int> o;
        for (int i = 0; i < 256; ++i) { bs[i] = 0; }
        
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (!hg[i] || bs[i]) { continue; }
            v.clear();
            o.clear();
            
            o.emplace_back(i);
            bs[i] = true;
            while (o.size() > 0) {
                int t = o.back();
                v.emplace_back(t);
                int x = t % 16;
                int y = t / 16;
                o.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py * 16 + px;
                    if (!insidexywh(px, py, 16, 16) || bs[p] || !hg[p]) { continue; }
                    o.emplace_back(p);
                    bs[p] = true;
                }
            }
            
            int cnt = v.size();
            for (auto&& i : v) {
                if (abs(this->ends[i] - t) < 5) {
                    r += this->vals[i] * cnt * 4;
                } else {
                    r += this->vals[i] * cnt;
                }
                
                // r += this->vals[i] * cnt;
            }
        }
        
        return r;
    }
    void update_e (vector<Vege>& veges, int turn) {
        for (int i = 0; i < 256; ++i) {
            if (this->ends[i] == turn) {
                this->ends[i] = 0;
                this->vals[i] = 0;
            }
        }
    }
    
};

class MM {
public:
    StopWatch sw;
    int S, M, T;
    vector<Vege> veges;
    vector<Com> bestret;
    
    array<int, 256> sumv;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->S >> this->M >> this->T;
        for (int i = 0; i < 256; ++i) {
            this->sumv[i] = 0;
        }
        
        for (int i = 0; i < this->M; ++i) {
            Vege v;
            cin >> v.r >> v.c >> v.s >> v.e >> v.v;
            this->veges.emplace_back(v);
            
            this->sumv[v.r*this->S+v.c] += v.v;
            // if (v.e > 880) { this->sumv[v.r*this->S+v.c] += v.v; }
            
        }
        
        // for (int y = 0; y < 16; ++y) {
        //     string s;
        //     for (int x = 0; x < 16; ++x) {
        //         s += (this->sumv[y*16+x] > 0 ? to_string(this->sumv[y*16+x]) : " ") + ", ";
        //     }
        //     fdebug(s);
        // }
        
    }
    
    void output () {
        for (auto&& i : this->bestret) { cout << i << endl; }
    }
    void solve () {
        vector<Com> ret;
        int n = 0;
        int bestscore = this->solve_a(ret, 0);
        
        this->bestret = ret;
        
        for (int i = 1; i < 15; ++i) {
            if (this->sw.get_milli_time() > 1700) { break; }
            ret.clear();
            int score = this->solve_a(ret, i);
            if (score > bestscore) {
                bestscore = score;
                this->bestret = ret;
                n = i;
            }
        }
        
        pdebug(this->sw.get_milli_time(), n%5);
    }
    
    
    int sumscore (bitset<256>& g) {
        int r = 0;
        bitset<256> g1 = this->expand(g);
        bitset<256> g2 = this->expand(g1);
        for (int i = 0; i < 256; ++i) {
            r += this->sumv[i] * (g2[i] || g1[i] || g[i]);
        }
        return r;
    }
    int harvester_cost (int n) {
        n += 1;
        return n * n * n ;
    }
    void solve2 (int& turn, VegeGrid& vg, bitset<256>& hg, int& money, bitset<256>& goal, vector<Com>& ret) {
        int h = hg.count();
        int hc = this->harvester_cost(h);
        if (turn > 997) { return; }
        if (turn < 860 && money >= hc) { return; }
        vector<int> mvs = this->moveharvester_indexs(hg, goal, 2);
        if (mvs.size() < 2) { return; }
        
        VegeGrid tvg = vg;
        tvg.update_f(this->veges, turn);
        
        int bestscore1 = 0;
        int bestb1 = 0;
        int bestscore2 = 0;
        int bestb2 = 0;
        bitset<256> thg = hg;
        
        for (auto&& i : mvs) { thg[i] = false; }
        bitset<256> thg1 = this->expand(thg);
        bitset<256> thg2 = this->expand(thg1);
        
        for (int i = 0; i < 256; ++i) {
            if (thg1[i] && thg[i]) { thg1[i] = false; }
            if (thg2[i] && (thg[i] || thg1[i])) { thg2[i] = false; }
        }
        
        
        
        for (int b = 0; b < 256; ++b) {
            if (!thg1[b]) { continue; }
            if (tvg.vals[b] < 1) { continue; }
            int score = tvg.ends[b]-turn < 5 ? tvg.vals[b] * h * 2 : tvg.vals[b] * h;
            if (score > bestscore1) {
                bestscore1 = score;
                bestb1 = b;
            }
        }
        for (int b = 0; b < 256; ++b) {
            if (!thg2[b] || hg[b]) { continue; }
            if (tvg.vals[b] < 1) { continue; }
            int score = tvg.ends[b]-turn < 5 ? tvg.vals[b] * h * 2 : tvg.vals[b] * h;
            score = tvg.ends[b]-turn < 1 ? 0 : score;
            if (score > bestscore2) {
                bestscore2 = score;
                bestb2 = b;
            }
        }
        if (bestscore2 > 0 && bestscore2 > bestscore1 * 1.2) {
            int x = bestb2 % this->S;
            int y = bestb2 / this->S;
            for (int i = 0; i < 4; ++i) {
                int px = dx[i] + x;
                int py = dy[i] + y;
                int p = py * this->S + px;
                if (!insidexywh(px, py, this->S, this->S)) { continue; }
                if (p == mvs[0]) { return; }
            }
            
            for (int i = 0; i < 4; ++i) {
                int px = dx[i] + x;
                int py = dy[i] + y;
                int p = py * this->S + px;
                if (!insidexywh(px, py, this->S, this->S)) { continue; }
                if (thg1[p] && !hg[p]) {
                    vg.update_f(this->veges, turn);
                    hg[mvs[0]] = false;
                    hg[p] = true;
                    ret.emplace_back(mvs[0]/this->S, mvs[0]%this->S, p/this->S, p%this->S);
                    money += vg.harvest(this->veges, hg);
                    vg.update_e(this->veges, turn);
                    turn += 1;
                    
                    vg.update_f(this->veges, turn);
                    hg[mvs[1]] = false;
                    hg[bestb2] = true;
                    ret.emplace_back(mvs[1]/this->S, mvs[1]%this->S, bestb2/this->S, bestb2%this->S);
                    money += vg.harvest(this->veges, hg);
                    vg.update_e(this->veges, turn);
                    
                    turn += 1;
                    return;
                }
            }
        }
    }
    
    void solve1 (int& turn, VegeGrid& vg, bitset<256>& hg, int& money, bitset<256>& goal, vector<Com>& ret) {
        vg.update_f(this->veges, turn);
        int h = hg.count();
        int hc = this->harvester_cost(h);
        int mv = this->moveharvester_index(hg, goal);
        int bestmvscore = 0;
        int besta = 0;
        int bestb = 0;
        
        if (mv > -1) {
            for (int b = 0; b < 256; ++b) {
                if (hg[b]) { continue; }
                if (vg.vals[b] < 1) { continue; }
                hg[mv] = false;
                hg[b] = true;
                int score = vg.vharvest(this->veges, hg, turn);
                hg[mv] = true;
                hg[b] = false;
                if (score > bestmvscore) {
                    bestmvscore = score;
                    besta = mv;
                    bestb = b;
                }
            }
        }
        
        // if (mv > -1) {
        //     bitset<256> thg = hg;
        //     thg[mv] = false;
        //     thg = this->expand(thg);
        //     for (int b = 0; b < 256; ++b) {
        //         if (!thg[b] || hg[b]) { continue; }
        //         if (vg.vals[b] < 1) { continue; }
        //         int score = vg.ends[b]-turn < 5 ? vg.vals[b] * h * 4 : vg.vals[b] * h;
        //         if (score > bestmvscore) {
        //             bestmvscore = score;
        //             besta = mv;
        //             bestb = b;
        //         }
        //     }
            
        //     for (int b = 0; b < 256; ++b) {
        //         if (hg[b]) { continue; }
        //         if (vg.vals[b] < 1) { continue; }
        //         int score = vg.ends[b]-turn < 5 ? vg.vals[b] * 4 : vg.vals[b];
        //         if (score > bestmvscore) {
        //             bestmvscore = score;
        //             besta = mv;
        //             bestb = b;
        //         }
        //     }
        // }
        
        if ((turn < 860 && hc <= money)) {
            int bestscore = -1;
            int bestp = 0;
            if (h > 0) {
                for (int i = 0; i < 256; ++i) {
                    if (hg[i] || !goal[i]) { continue; }
                    int x = i % this->S;
                    int y = i / this->S;
                    int cnt = 0;
                    for (int d = 0; d < 4; ++d) {
                        int px = x + dx[d];
                        int py = y + dy[d];
                        int p = py*this->S+px;
                        if (!insidexywh(px, py, this->S, this->S) || p == mv) { continue; }
                        cnt += hg[p];
                    }
                    if (cnt >= bestscore) {
                        bestscore = cnt;
                        bestp = i;
                    }
                }
                if (bestscore <= 0) {
                    for (int y = 0; y < this->S; ++y) {
                        for (int x = 0; x < this->S; ++x) {
                            int p = y * this->S + x;
                            if (hg[p]) { continue; }
                            hg[p] = true;
                            int score = vg.vharvest(this->veges, hg, turn);
                            hg[p] = false;
                            if (score > bestscore) {
                                bestscore = score;
                                bestp = p;
                            }
                        }
                    }
                }
                
                if (bestscore > -1) {
                    hg[bestp] = true;
                    ret.emplace_back(bestp/this->S, bestp%this->S);
                    money -= hc;
                }
            } else {
                for (int y = 0; y < this->S; ++y) {
                    for (int x = 0; x < this->S; ++x) {
                        int p = y * this->S + x;
                        hg[p] = true;
                        int score = vg.vharvest(this->veges, hg, turn);
                        hg[p] = false;
                        if (score > bestscore) {
                            bestscore = score;
                            bestp = p;
                        }
                    }
                }
                hg[bestp] = true;
                ret.emplace_back(bestp/this->S, bestp%this->S);
                money -= hc;
            }
            
        } else if (bestmvscore > 0) {
            hg[besta] = false;
            hg[bestb] = true;
            ret.emplace_back(besta/this->S, besta%this->S, bestb/this->S, bestb%this->S);
        }
        
        if (ret.size() == turn) { ret.emplace_back(); }
        money += vg.harvest(this->veges, hg);
        vg.update_e(this->veges, turn);
        turn += 1;
    }
    
    int solve_a (vector<Com>& ret, int n) {
        int money = 1;
        bitset<256> hg;
        VegeGrid vg;
        bitset<256> goal = this->test16_1(n);
        int turn = 0;
        while (turn < 1000) {
            
            this->solve2(turn, vg, hg, money, goal, ret);
            this->solve1(turn, vg, hg, money, goal, ret);
        }
        
        pdebug(hg.count());
        
        return money;
    }
    
    
    bitset<256> expand (bitset<256>& hg) {
        bitset<256> r;
        for (int y = 0; y < this->S; ++y) {
            for (int x = 0; x < this->S; ++x) {
                if (!hg[y*this->S+x] || r[y*this->S+x]) {continue; }
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py*this->S+px;
                    if (!insidexywh(px, py, this->S, this->S)) { continue; }
                    if (hg[p] || r[p]) { continue; }
                    r[p] = true;
                }
            }
        }
        return r;
    }
    
    
    
    
    int moveharvester_index (bitset<256>& hg, bitset<256>& goal) {
        int r = -1;
        for (int i = 0; i < 256; ++i) {
            if (hg[i] && !goal[i]) { return i; }
        }
        
        for (int y = 0; y < this->S; ++y) {
            for (int x = 0; x < this->S; ++x) {
                int i = y*this->S+x;
                if (!hg[i]) { continue; }
                int cnt = 0;
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py*this->S+px;
                    if (!insidexywh(px, py, this->S, this->S)) { continue; }
                    cnt += hg[p];
                }
                if (cnt <= 1) { return i; }
            }
        }
        return -1;
    }
    
    vector<int> moveharvester_indexs (bitset<256>& hg, bitset<256>& goal, int n) {
        vector<int> r;
        bitset<256> bg;
        for (int i = 0; i < 256; ++i) {
            if (hg[i] && !goal[i]) {
                r.emplace_back(i);
                bg[i] = true;
            }
        }
        if (r.size() < n) {
            for (int y = 0; y < this->S; ++y) {
                for (int x = 0; x < this->S; ++x) {
                    int i = y*this->S+x;
                    if (!hg[i]) { continue; }
                    int cnt = 0;
                    for (int d = 0; d < 4; ++d) {
                        int px = x + dx[d];
                        int py = y + dy[d];
                        int p = py*this->S+px;
                        if (!insidexywh(px, py, this->S, this->S)) { continue; }
                        cnt += hg[p];
                    }
                    if (cnt <= 1 && !bg[i]) {
                        bg[i] = true;
                        r.emplace_back(i);
                        if (r.size() >= n) { return r; }
                    }
                }
            } 
        }
        
        return r;
    }
    
    
    bitset<256> test16_1 (int n) {
        string s[] = {"0000000000000000000000000000000000111111111111000010000000000100001000000000010000100000000001000010000000000100001111000011110000100000000001000010000000000100001000000000010000100000000001000010000000000100001111111111110000000000000000000000000000000000", "0000000000000000011111111111111001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001111110011111100000000000000000", "0000000000000000000000000000000000000000000010000001111111111000000100000000100000010000000010000001111001111000000100000000100000010000000010000001111001111000000100000000100000010000000010000001111111111000000100000000000000000000000000000000000000000000", "0000000000000000000000000000000000000000000000000011111111111100000100000000100000010000000010000001000111111000000100000000100000010000000010000001111110001000000100000000100000010000000010000011111111111100000000000000000000000000000000000000000000000000", "0000000000000000000000000000000000111111111111000010000100000100001000010000010000100001000001000010000100000100001000010000010000100001111111000010000000000000001000000000000000100000000000000010000000000000001111111111111100000000000000000000000000000000"};
        bitset<256> r(s[n%5]);
        
        if (n >= 10) {
            r = maximize_sa_fixedstep(r, 500000, 512*2);
        } else if (n >= 5) {
            r = maximize_sa_fixedstep(r, 500000, 512);
        }
        return r;
    }
    
    int scnt (bitset<256>& hg) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        static bitset<256> bs;
        static vector<int> o;
        for (int i = 0; i < 256; ++i) { bs[i] = 0; }
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (!hg[i] || bs[i]) { continue; }
            o.clear();
            o.emplace_back(i);
            bs[i] = true;
            while (o.size() > 0) {
                int t = o.back();
                int x = t % 16;
                int y = t / 16;
                o.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py * 16 + px;
                    if (!insidexywh(px, py, 16, 16) || bs[p] || !hg[p]) { continue; }
                    o.emplace_back(p);
                    bs[p] = true;
                }
            }
            
            r += 1;
            if (r > 1) { return r; }
        }
        return r;
    }
    
    
    
    bitset<256> maximize_sa_fixedstep (bitset<256> v, int ecnt, double stemp = 256.0, double etemp = 0.0) {
        const double sacnt = ecnt;
        bitset<256> bestv = v;
        double bestscore = this->sumscore(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
            int a = xrnd() % 256;////
            int b = xrnd() % 256;////
            
            if (v[a] == v[b]) { continue; }
            bool t;
            t = v[a];
            v[a] = v[b];
            v[b] = t;
            
            if (v[a]) {
                int x = a % 16;
                int y = a / 16;
                bool c = true;
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py * 16 + px;
                    if (!insidexywh(px, py, 16, 16)) { continue; }
                    if (v[p]) {
                        c = false;
                        break;
                    }
                }
                if (c) {
                    t = v[a];
                    v[a] = v[b];
                    v[b] = t;
                    continue;
                }
            }
            if (v[b]) {
                int x = b % 16;
                int y = b / 16;
                bool c = true;
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py * 16 + px;
                    if (!insidexywh(px, py, 16, 16)) { continue; }
                    if (v[p]) {
                        c = false;
                        break;
                    }
                }
                if (c) {
                    t = v[a];
                    v[a] = v[b];
                    v[b] = t;
                    continue;
                }
            }
            
            if (this->scnt(v) > 1) {
                t = v[a];
                v[a] = v[b];
                v[b] = t;
                continue;
            }
            double tmpscore = this->sumscore(v);
            const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
            const double probability = exp((tmpscore - lastscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore > lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore > bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                t = v[a];
                v[a] = v[b];
                v[b] = t;
            }
        }
        return bestv;
    }
    
    void bdebug (bitset<256>& g1) {
        for (int y = 0; y < 16; ++y) {
            string s;
            for (int x = 0; x < 16; ++x) {
                s += g1[y*16+x] ? "*" : " ";
            }
            fdebug(s);
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
    
    return 0;
}

