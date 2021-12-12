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
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        static bitset<256> bs;
        
        for (int i = 0; i < 256; ++i) { bs[i] = 0; }
        
        
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (!hg[i] || bs[i]) { continue; }
            vector<int> v;
            vector<int> o;
            
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
    
    int vharvest (vector<Vege>& veges, bitset<256>& hg) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        static bitset<256> bs;
        
        for (int i = 0; i < 256; ++i) { bs[i] = 0; }
        
        
        int r = 0;
        for (int i = 0; i < 256; ++i) {
            if (!hg[i] || bs[i]) { continue; }
            vector<int> v;
            vector<int> o;
            
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
        vector<Com> ret1;
        int score1 = this->solve1(ret1);
        vector<Com> ret2;
        int score2 = this->solve2(ret2);
        
        this->bestret = score1 > score2 ? ret1 : ret2;
        
        pdebug(this->sw.get_milli_time());
    }
    
    int harvester (int n) {
        n += 1;
        return n*n*n;
    }
    
    int solve1 (vector<Com>& ret) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        int g = 1;
        int h = 0;
        bitset<256> hg;
        VegeGrid vg;
        
        bitset<256> test = this->test16_1();
        
        for (int t = 0; t < this->T; ++t) {
            vg.update_f(this->veges, t);
            int hc = this->harvester(h);
            int mv = this->moveharvester_index(hg, test);
            int bestmvscore = 0;
            int besta = 0;
            int bestb = 0;
            
            if (mv > -1) {
                // bitset<256> lg;
                // for (auto&& b : this->link_moves(hg, mv)) { lg[b] = true; }
                
                for (int b = 0; b < 256; ++b) {
                    if (hg[b]) { continue; }
                    hg[mv] = false;
                    hg[b] = true;
                    int score = vg.vharvest(this->veges, hg);
                    hg[mv] = true;
                    hg[b] = false;
                    if (score > bestmvscore) {
                        bestmvscore = score;
                        besta = mv;
                        bestb = b;
                    }
                }
                
            }
            
            if ((t < 900 && hc <= g)) {
                int bestscore = -1;
                int bestp = 0;
                if (h > 0) {
                    for (int i = 0; i < 256; ++i) {
                        if (hg[i] || !test[i]) { continue; }
                        int x = i % this->S;
                        int y = i / this->S;
                        int cnt = 0;
                        for (int d = 0; d < 4; ++d) {
                            int px = x + dx[d];
                            int py = y + dy[d];
                            int p = py*this->S+px;
                            if (!insidexywh(px, py, this->S, this->S)) { continue; }
                            cnt += hg[p];
                        }
                        if (cnt >= bestscore) {
                            bestscore = cnt;
                            bestp = i;
                        }
                    }
                    if (bestscore > -1) {
                        hg[bestp] = true;
                        ret.emplace_back(bestp/this->S, bestp%this->S);
                        g -= hc;
                        h += 1;
                    }
                } else {
                    for (int y = 0; y < this->S; ++y) {
                        for (int x = 0; x < this->S; ++x) {
                            int p = y * this->S + x;
                            hg[p] = true;
                            int score = vg.vharvest(this->veges, hg);
                            hg[p] = false;
                            if (score > bestscore) {
                                bestscore = score;
                                bestp = p;
                            }
                        }
                    }
                    hg[bestp] = true;
                    ret.emplace_back(bestp/this->S, bestp%this->S);
                    g -= hc;
                    h += 1;
                }
                
            } else if (bestmvscore > 0) {
                hg[besta] = false;
                hg[bestb] = true;
                ret.emplace_back(besta/this->S, besta%this->S, bestb/this->S, bestb%this->S);
            }
            
            if (ret.size() == t) { ret.emplace_back(); }
            
            
            g += vg.harvest(this->veges, hg);
            
            vg.update_e(this->veges, t);
        }
        
        return g;
        // pdebug(h, g);
    }
    int solve2 (vector<Com>& ret) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        int g = 1;
        int h = 0;
        bitset<256> hg;
        VegeGrid vg;
        
        bitset<256> test = this->test16_2();
        
        for (int t = 0; t < this->T; ++t) {
            vg.update_f(this->veges, t);
            int hc = this->harvester(h);
            int mv = this->moveharvester_index(hg, test);
            int bestmvscore = 0;
            int besta = 0;
            int bestb = 0;
            
            if (mv > -1) {
                // bitset<256> lg;
                // for (auto&& b : this->link_moves(hg, mv)) { lg[b] = true; }
                
                for (int b = 0; b < 256; ++b) {
                    if (hg[b]) { continue; }
                    hg[mv] = false;
                    hg[b] = true;
                    int score = vg.vharvest(this->veges, hg);
                    hg[mv] = true;
                    hg[b] = false;
                    if (score > bestmvscore) {
                        bestmvscore = score;
                        besta = mv;
                        bestb = b;
                    }
                }
                
            }
            
            if ((t < 900 && hc <= g)) {
                int bestscore = -1;
                int bestp = 0;
                if (h > 0) {
                    for (int i = 0; i < 256; ++i) {
                        if (hg[i] || !test[i]) { continue; }
                        int x = i % this->S;
                        int y = i / this->S;
                        int cnt = 0;
                        for (int d = 0; d < 4; ++d) {
                            int px = x + dx[d];
                            int py = y + dy[d];
                            int p = py*this->S+px;
                            if (!insidexywh(px, py, this->S, this->S)) { continue; }
                            cnt += hg[p];
                        }
                        if (cnt >= bestscore) {
                            bestscore = cnt;
                            bestp = i;
                        }
                    }
                    if (bestscore > -1) {
                        hg[bestp] = true;
                        ret.emplace_back(bestp/this->S, bestp%this->S);
                        g -= hc;
                        h += 1;
                    }
                } else {
                    for (int y = 0; y < this->S; ++y) {
                        for (int x = 0; x < this->S; ++x) {
                            int p = y * this->S + x;
                            hg[p] = true;
                            int score = vg.vharvest(this->veges, hg);
                            hg[p] = false;
                            if (score > bestscore) {
                                bestscore = score;
                                bestp = p;
                            }
                        }
                    }
                    hg[bestp] = true;
                    ret.emplace_back(bestp/this->S, bestp%this->S);
                    g -= hc;
                    h += 1;
                }
                
            } else if (bestmvscore > 0) {
                hg[besta] = false;
                hg[bestb] = true;
                ret.emplace_back(besta/this->S, besta%this->S, bestb/this->S, bestb%this->S);
            }
            
            if (ret.size() == t) { ret.emplace_back(); }
            
            
            g += vg.harvest(this->veges, hg);
            
            vg.update_e(this->veges, t);
        }
        
        return g;
        // pdebug(h, g);
    }
    
    int moveharvester_index (bitset<256>& g, bitset<256>& tg) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        int r = -1;
        for (int i = 0; i < 256; ++i) {
            if (g[i] && !tg[i]) { return i; }
        }
        
        for (int y = 0; y < this->S; ++y) {
            for (int x = 0; x < this->S; ++x) {
                int i = y*this->S+x;
                if (!g[i]) { continue; }
                int cnt = 0;
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py*this->S+px;
                    if (!insidexywh(px, py, this->S, this->S)) { continue; }
                    cnt += g[p];
                }
                if (cnt <= 1) { return i; }
            }
        }
        return -1;
    }
    
    bitset<256> test16_1 () {
        bitset<256> r("0000000000000000000000000000000000111111111111000010000000000100001000000000010000100000000001000010000000000100001111111111110000100000000001000010000000000100001000000000010000100000000001000010000000000100001111111111110000000000000000000000000000000000");
        
        return r;
    }
    
    bitset<256> test16_2 () {
        bitset<256> r("0000000000000000011111111111111001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001000000000000100100000000000010010000000000001001111111111111100000000000000000");
        return r;
    }
    
    vector<int> link_moves (bitset<256>& g, int t) {
        static const int dx[] = {1, -1, 0, 0};
        static const int dy[] = {0, 0, 1, -1};
        static bitset<256> bg;
        vector<int> r;
        for (int i = 0; i < 256; ++i) { bg[i] = false; }
        for (int y = 0; y < this->S; ++y) {
            for (int x = 0; x < this->S; ++x) {
                if (!g[y*this->S+x] || y*this->S+x == t) {continue; }
                for (int d = 0; d < 4; ++d) {
                    int px = x + dx[d];
                    int py = y + dy[d];
                    int p = py*this->S+px;
                    if (!insidexywh(px, py, this->S, this->S)) { continue; }
                    if (bg[p] || g[p]) { continue; }
                    bg[p] = true;
                    r.emplace_back(p);
                }
            }
        }
        return r;
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

