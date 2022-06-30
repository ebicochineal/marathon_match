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


const int dr[8] = {-2, -2, -1,  1,  2,  2,  1, -1};// dy
const int dc[8] = {-1,  1,  2,  2,  1, -1, -2, -2};// dx

struct rcrc {
    int r1, c1, r2, c2;
    rcrc (int r1, int c1, int r2, int c2) {
        this->r1 = r1;
        this->c1 = c1;
        this->r2 = r2;
        this->c2 = c2;
    }
};

struct mmgrid {
    int score = 0;
    int cnt = 0;
    array< array<int, 34>, 34> grid;
    vector<rcrc> out;
    mmgrid (array< array<int, 34>, 34> grid) {
        this->grid = grid;
    }
};


class MM {
public:
    StopWatch sw;
    int N, C, N2;
    array< array<int, 34>, 34> grid;
    array< array<int, 8>, 8> D;
    array< array<int, 8>, 8> D2;
    
    array<int, 8> colors;
    vector<rcrc> bestout;
    
    vector<e512pos> vsp;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->C;
        pdebug(this->N, this->C);
        for (int i = 0; i < 8; ++i) { this->colors[i] = 0; }
        
        for (int r = 0; r < 34; r++) {
            for (int c = 0; c < 34; c++) { this->grid[r][c] = -1; }
        }
        for (int r = 0; r < this->N; r++) {
            for (int c = 0; c < this->N; c++) {
                cin >> this->grid[r+2][c+2];
                this->colors[this->grid[r+2][c+2]] += 1;
            }
        }
        
        for (int r = 0; r < this->C; r++) {
            for (int c = 0; c < this->C; c++) { cin >> this->D[r][c]; }
        }
        this->N2 = this->N + 2;
        
        
        vector< pair<int, int> > v;
        for (int i = 0; i < this->C; ++i) {
            v.emplace_back(i, this->colors[i]);
        }
        sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });
        this->D2 = this->D;
        
        for (int j = 0; j < 8; ++j) {
            this->D2[j][j] = 1;
        }
        
        this->vsp = this->spiral(this->N+4, this->N+4, 1, 2, 2, 2, 2);
    }
    void output () {
        pdebug(this->sw.get_milli_time());
        
        cout << this->bestout.size() << endl;
        for (int i = 0; i < this->bestout.size(); i++) {
            rcrc o = this->bestout[i];
            cout << print(o.r1-2, o.c1-2, o.r2-2, o.c2-2) << endl;
        }
    }
    
    vector<e512pos> spiral (int h, int w, int m = 1, int l = 0, int r = 0, int u = 0, int d = 0) {
        vector<e512pos> ret;
        int x = l-1;
        int y = u-1;
        while (true) {
            for (x+=1, y+=1; x < w-r; ++x) { ret.emplace_back(x, y); }
            u += m;
            if (x-1 < l) { break; }
            for (y+=1, x-=1; y < h-d; ++y) { ret.emplace_back(x, y); }
            r += m;
            if (y-1 < u) { break; }
            for (x-=1, y-=1; x >= l; --x) { ret.emplace_back(x, y); }
            d += m;
            if (x+1 >= w-r) { break; }
            for (y-=1, x+=1; y >= u; --y) { ret.emplace_back(x, y); }
            l += m;
            if (y+1 >= h-d) { break; }
        }
        return ret;
    }
    
    void solve () {
        int bestscore = 0;
        mmgrid bestg2(this->grid);
        int n = 5126/2;
        // if (C == 3) { n = 51260/2; }
        // if (C == 4) { n = 51260/4; }
        // if (C == 5) { n = 51260/8; }
        int cnt = 0;
        for (int z = 0; z < 128; ++z) {
            if (this->sw.get_milli_time() > 9600) { break; }
            if (this->sw.get_milli_time() > 8000) { n = 5126/4; }
            mmgrid bestg(this->grid);
            if (N > 12) {
                for (int i = 0; i < n; ++i) {
                    if (i % 32 == 0 && this->sw.get_milli_time() > 9600) { break; }
                    mmgrid g(this->grid);
                    this->extend(g);
                    if (g.score > bestg.score) { bestg = g; }
                    cnt += 1;
                }
                
                for (int i = 0; i < 10; ++i) {
                    mmgrid tg = bestg;
                    for (int z = 0; z < 10-i; ++z) {
                        for (int i = 0; i < n / 10; ++i) {
                            if (i % 32 == 0 && this->sw.get_milli_time() > 9600) { break; }
                            mmgrid g = tg;
                            this->extend(g);
                            if (g.score > bestg.score) { bestg = g; }
                            cnt += 1;
                        }
                    }
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    if (i % 32 == 0 && this->sw.get_milli_time() > 9600) { break; }
                    mmgrid g(this->grid);
                    if (z % 2) {
                        this->extend0(g);
                    } else {
                        this->extend(g);
                    }
                    
                    
                    if (g.score > bestg.score) { bestg = g; }
                    cnt += 1;
                }
                
                for (int i = 0; i < 10; ++i) {
                    mmgrid tg = bestg;
                    for (int z = 0; z < 10-i; ++z) {
                        for (int i = 0; i < n / 10; ++i) {
                            if (i % 32 == 0 && this->sw.get_milli_time() > 9600) { break; }
                            mmgrid g = tg;
                            if (z % 2) {
                                this->extend0(g);
                            } else {
                                this->extend(g);
                            }
                            if (g.score > bestg.score) { bestg = g; }
                            cnt += 1;
                        }
                    }
                }
            }
            
            
            {
                mmgrid tg = bestg;
                {
                    mmgrid g = tg;
                    g = this->fill0(g);
                    if (g.score > bestg.score) { bestg = g; }
                }
                for (int z = 0; z < 16; ++z) {
                    mmgrid g = tg;
                    g = this->fill(g);
                    if (g.score > bestg.score) { bestg = g; }
                }
            }
            
            int score = this->calc_score(bestg.out);
            if (score > bestscore) {
                bestscore = score;
                bestg2 = bestg;
            }
        }
        
        pdebug(cnt);
        this->bestout = bestg2.out;
        
        pdebug(this->calc_score(this->bestout));
        
    }
    
    void extend (mmgrid& g, int m = -1000) {
        static vector<e512pos> cp;
        cp.clear();
        for (int y = 2; y < this->N2; ++y) {
            for (int x = 2; x < this->N2; ++x) {
                if (g.grid[y][x] >= 0) { cp.emplace_back(x, y); }
            }
        }
        if (cp.size() == 0) { return; }
        
        e512pos fp = cp[xrnd()%cp.size()];
        e512pos ep = fp;
        int pr = fp.y;
        int pc = fp.x;
        int color = g.grid[fp.y][fp.x];
        g.grid[fp.y][fp.x] = -1;
        bool f = true;
        int cnt = 0;
        
        
        static vector<e512pos> sv;
        static vector<e512pos> ev;
        sv.clear();
        ev.clear();
        
        
        static array<int, 8> v;
        for (int i = 0; i < 8; ++i) { v[i] = i; }
        
        mt19937 mt(xrnd());
        
        shuffle(v.begin(), v.end(), mt);
        f = true;
        while (f) {
            f = false;
            // shuffle(v.begin(), v.end(), mt);
            
            for (int d = 0; d < 8; ++d) {
                int br = fp.y + dr[v[d]];
                int bc = fp.x + dc[v[d]];
                if (g.grid[br][bc] == color) {
                    g.grid[fp.y][fp.x] = -1;
                    g.grid[br][bc] = -1;
                    fp.y = br;
                    fp.x = bc;
                    f = true;
                    break;
                }
            }
            
            if (f) {
                sv.emplace_back(fp.x, fp.y);
                continue;
            }
            
            
            {
                
                int bestbr, bestbc;
                int bestscore = m;
                int bestr, bestc;
                for (int d = 0; d < 8; ++d) {
                    int br = fp.y + dr[v[d]];
                    int bc = fp.x + dc[v[d]];
                    
                    if (g.grid[br][bc] < 0) { continue; }
                    
                    int bscore = 0;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        if (cr == br && cc == bc) { continue; }
                        bscore += 1;
                    }
                    
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        int score = this->D[color][g.grid[br][bc]] + bscore * 4;
                        if (score > bestscore) {
                            bestscore = score;
                            bestr = cr;
                            bestc = cc;
                            bestbc = bc;
                            bestbr = br;
                        }
                    }
                }
                
                if (bestscore > m) {
                    g.grid[fp.y][fp.x] = -1;
                    fp.y = bestbr;
                    fp.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 1;
                    sv.emplace_back(fp.x, fp.y);
                    continue;
                }
            }
            
            {
                int bestscore = m;
                int bestr, bestc, bestr2, bestc2;
                int bestbr, bestbc;
                for (int d = 0; d < 8; ++d) {
                    int br = fp.y + dr[v[d]];
                    int bc = fp.x + dc[v[d]];
                    if (g.grid[br][bc] < 0) { continue; }
                    
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] < 0 || (br == cr && bc == cc)) { continue; }
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            if (g.grid[cr2][cc2] != color) { continue; }
                            int score = this->D[color][g.grid[br][bc]] + this->D[color][g.grid[cr][cc]];
                            if (score > bestscore) {
                                bestscore = score;
                                bestr = cr;
                                bestc = cc;
                                bestr2 = cr2;
                                bestc2 = cc2;
                                bestbr = br;
                                bestbc = bc;
                            }
                        }
                    }
                }
                if (bestscore > m) {
                    g.grid[fp.y][fp.x] = -1;
                    fp.y = bestbr;
                    fp.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.grid[bestr2][bestc2] = -1;
                    g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 2;
                    sv.emplace_back(fp.x, fp.y);
                    continue;
                }
            }
            
            {
                
                int bestbr, bestbc;
                int bestscore = m;
                int bestr, bestc, bestr2, bestc2, bestr3, bestc3;
                
                for (int d = 0; d < 8; ++d) {
                    int br = fp.y + dr[v[d]];
                    int bc = fp.x + dc[v[d]];
                    if (g.grid[br][bc] < 0) { continue; }
                    
                    e512pos p1, p2, p3, p4;
                    p1.y = br;
                    p1.x = bc;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        p2.y = cr;
                        p2.x = cc;
                        if (p2 == p1) { continue; }
                        if (g.grid[cr][cc] < 0) { continue; }
                        
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            
                            p3.y = cr2;
                            p3.x = cc2;
                            if (p3 == p2 || p3 == p1) { continue; }
                            if (g.grid[cr2][cc2] < 0) { continue; }
                            for (int sd3 = 0; sd3 < 8; ++sd3) {
                                int cr3 = cr2 + dr[v[sd3]];
                                int cc3 = cc2 + dc[v[sd3]];
                                p4.y = cr3;
                                p4.x = cc3;
                                if (p4 == p3 || p4 == p2 || p4 == p1) { continue; }
                                if (g.grid[cr3][cc3] != color) { continue; }
                                int score = this->D[color][g.grid[br][bc]] + this->D[color][g.grid[cr][cc]] + this->D[color][g.grid[cr2][cc2]];
                                
                                if (score > bestscore) {
                                    bestscore = score;
                                    bestr = cr;
                                    bestc = cc;
                                    bestr2 = cr2;
                                    bestc2 = cc2;
                                    bestr3 = cr3;
                                    bestc3 = cc3;
                                    bestbr = br;
                                    bestbc = bc;
                                }
                            }
                        }
                    }
                    
                }
                if (bestscore > m) {
                    g.grid[fp.y][fp.x] = -1;
                    fp.y = bestbr;
                    fp.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.grid[bestr2][bestc2] = -1;
                    g.grid[bestr3][bestc3] = -1;
                    g.out.emplace_back(bestr3, bestc3, bestr2, bestc2);
                    g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 3;
                    sv.emplace_back(fp.x, fp.y);
                    continue;
                }
            }
            
            
        }
        shuffle(v.begin(), v.end(), mt);
        f = true;
        
        while (f) {
            f = false;
            // shuffle(v.begin(), v.end(), mt);
            
            for (int d = 0; d < 8; ++d) {
                int br = ep.y + dr[v[d]];
                int bc = ep.x + dc[v[d]];
                if (g.grid[br][bc] == color) {
                    
                    g.grid[ep.y][ep.x] = -1;
                    g.grid[br][bc] = -1;
                    ep.y = br;
                    ep.x = bc;
                    f = true;
                    break;
                }
            }
            
            if (f) {
                ev.emplace_back(ep.x, ep.y);
                continue;
            }
            
            {
                
                int bestbr, bestbc;
                int bestscore = m;
                int bestr, bestc;
                for (int d = 0; d < 8; ++d) {
                    int br = ep.y + dr[v[d]];
                    int bc = ep.x + dc[v[d]];
                    
                    if (g.grid[br][bc] < 0) { continue; }
                    int bscore = 0;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        if (cr == br && cc == bc) { continue; }
                        bscore += 1;
                    }
                    
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        
                        int score = this->D[color][g.grid[br][bc]] + bscore * 4;
                        if (score > bestscore) {
                            bestscore = score;
                            bestr = cr;
                            bestc = cc;
                            bestbc = bc;
                            bestbr = br;
                        }
                    }
                }
                
                if (bestscore > m) {
                    g.grid[ep.y][ep.x] = -1;
                    ep.y = bestbr;
                    ep.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 1;
                    ev.emplace_back(ep.x, ep.y);
                    continue;
                }
            }
            {
                int bestscore = m;
                int bestr, bestc, bestr2, bestc2;
                int bestbr, bestbc;
                for (int d = 0; d < 8; ++d) {
                    int br = ep.y + dr[v[d]];
                    int bc = ep.x + dc[v[d]];
                    if (g.grid[br][bc] < 0) { continue; }
                    
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] < 0 || (br == cr && bc == cc)) { continue; }
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            if (g.grid[cr2][cc2] != color) { continue; }
                            int score = this->D[color][g.grid[br][bc]] + this->D[color][g.grid[cr][cc]];
                            if (score > bestscore) {
                                bestscore = score;
                                bestr = cr;
                                bestc = cc;
                                bestr2 = cr2;
                                bestc2 = cc2;
                                bestbr = br;
                                bestbc = bc;
                            }
                        }
                    }
                }
                if (bestscore > m) {
                    g.grid[ep.y][ep.x] = -1;
                    ep.y = bestbr;
                    ep.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.grid[bestr2][bestc2] = -1;
                    g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 2;
                    ev.emplace_back(ep.x, ep.y);
                    continue;
                }
            }
            
            {
                
                int bestbr, bestbc;
                int bestscore = m;
                int bestr, bestc, bestr2, bestc2, bestr3, bestc3;
                
                for (int d = 0; d < 8; ++d) {
                    int br = ep.y + dr[v[d]];
                    int bc = ep.x + dc[v[d]];
                    if (g.grid[br][bc] < 0) { continue; }
                    
                    
                    e512pos p1, p2, p3, p4;
                    p1.y = br;
                    p1.x = bc;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        p2.y = cr;
                        p2.x = cc;
                        if (p2 == p1) { continue; }
                        if (g.grid[cr][cc] < 0) { continue; }
                        
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            
                            p3.y = cr2;
                            p3.x = cc2;
                            if (p3 == p2 || p3 == p1) { continue; }
                            if (g.grid[cr2][cc2] < 0) { continue; }
                            for (int sd3 = 0; sd3 < 8; ++sd3) {
                                int cr3 = cr2 + dr[v[sd3]];
                                int cc3 = cc2 + dc[v[sd3]];
                                p4.y = cr3;
                                p4.x = cc3;
                                if (p4 == p3 || p4 == p2 || p4 == p1) { continue; }
                                if (g.grid[cr3][cc3] != color) { continue; }
                                int score = this->D[color][g.grid[br][bc]] + this->D[color][g.grid[cr][cc]] + this->D[color][g.grid[cr2][cc2]];
                                
                                if (score > bestscore) {
                                    bestscore = score;
                                    bestr = cr;
                                    bestc = cc;
                                    bestr2 = cr2;
                                    bestc2 = cc2;
                                    bestr3 = cr3;
                                    bestc3 = cc3;
                                    bestbr = br;
                                    bestbc = bc;
                                }
                            }
                        }
                    }
                    
                }
                if (bestscore > m) {
                    g.grid[ep.y][ep.x] = -1;
                    ep.y = bestbr;
                    ep.x = bestbc;
                    g.grid[bestbr][bestbc] = -1;
                    g.grid[bestr][bestc] = -1;
                    g.grid[bestr2][bestc2] = -1;
                    g.grid[bestr3][bestc3] = -1;
                    g.out.emplace_back(bestr3, bestc3, bestr2, bestc2);
                    g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                    g.out.emplace_back(bestr, bestc, bestbr, bestbc);
                    f = true;
                    cnt += 3;
                    ev.emplace_back(ep.x, ep.y);
                    continue;
                }
            }
            
            
        }
        
        if (ev.size() + sv.size() + 1 < 6) { return; }
        
        if (ev.size() > 0) {
            int ar = ev[ev.size()-1].y;
            int ac = ev[ev.size()-1].x;
            g.grid[ar][ac] = -1;
            for (int i = ev.size()-2; i >= 0; --i) {
                int br = ev[i].y;
                int bc = ev[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = -1;
            g.out.emplace_back(ar, ac, pr, pc);
            ar = pr;
            ac = pc;
            for (int i = 0; i < sv.size(); ++i) {
                int br = sv[i].y;
                int bc = sv[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = color;
        } else {
            int ar = pr;
            int ac = pc;
            for (int i = 0; i < sv.size(); ++i) {
                int br = sv[i].y;
                int bc = sv[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = color;
        }
        
        g.cnt += cnt;
        g.score = this->calc_score(g.out) - g.cnt * 5;
    }
    
    
    void extend0 (mmgrid& g, int m = -1000) {
        static vector<e512pos> cp;
        cp.clear();
        for (int y = 2; y < this->N2; ++y) {
            for (int x = 2; x < this->N2; ++x) {
                if (g.grid[y][x] >= 0) { cp.emplace_back(x, y); }
            }
        }
        if (cp.size() == 0) { return; }
        
        e512pos fp = cp[xrnd()%cp.size()];
        e512pos ep = fp;
        int pr = fp.y;
        int pc = fp.x;
        int color = g.grid[fp.y][fp.x];
        g.grid[fp.y][fp.x] = -1;
        bool f = true;
        int cnt = 0;
        
        
        static vector<e512pos> sv;
        static vector<e512pos> ev;
        sv.clear();
        ev.clear();
        
        
        static array<int, 8> v;
        for (int i = 0; i < 8; ++i) { v[i] = i; }
        
        mt19937 mt(xrnd());
        
        
        shuffle(v.begin(), v.end(), mt);
        f = true;
        while (f) {
            f = false;
            // shuffle(v.begin(), v.end(), mt);
            
            for (int d = 0; d < 8; ++d) {
                int br = fp.y + dr[v[d]];
                int bc = fp.x + dc[v[d]];
                if (g.grid[br][bc] == color) {
                    g.grid[fp.y][fp.x] = -1;
                    g.grid[br][bc] = -1;
                    fp.y = br;
                    fp.x = bc;
                    f = true;
                    break;
                }
            }
            
            if (f) {
                sv.emplace_back(fp.x, fp.y);
                continue;
            }
            
            
            for (int d = 0; d < 8; ++d) {
                int br = fp.y + dr[v[d]];
                int bc = fp.x + dc[v[d]];
                if (g.grid[br][bc] < 0) { continue; }
                {
                    int bestscore = m;
                    int bestr, bestc;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        if (this->D[g.grid[cr][cc]][g.grid[br][bc]] > bestscore) {
                            bestscore = this->D[g.grid[cr][cc]][g.grid[br][bc]];
                            bestr = cr;
                            bestc = cc;
                        }
                    }
                    
                    if (bestscore > m) {
                        g.grid[fp.y][fp.x] = -1;
                        fp.y = br;
                        fp.x = bc;
                        g.grid[br][bc] = -1;
                        g.grid[bestr][bestc] = -1;
                        g.out.emplace_back(bestr, bestc, br, bc);
                        f = true;
                        cnt += 1;
                        break;
                    }
                }
            }
            
            if (f) {
                sv.emplace_back(fp.x, fp.y);
                continue;
            }
            
            
            
            for (int d = 0; d < 8; ++d) {
                int br = fp.y + dr[v[d]];
                int bc = fp.x + dc[v[d]];
                if (g.grid[br][bc] < 0) { continue; }
                {
                    int bestscore = m;
                    int bestr, bestc, bestr2, bestc2;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] < 0 || (br == cr && bc == cc)) { continue; }
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            if (g.grid[cr2][cc2] != color) { continue; }
                            int score = this->D[g.grid[cr][cc]][g.grid[br][bc]] + this->D[g.grid[cr2][cc2]][g.grid[cr][cc]];
                            if (score > bestscore) {
                                bestscore = score;
                                bestr = cr;
                                bestc = cc;
                                bestr2 = cr2;
                                bestc2 = cc2;
                            }
                        }
                    }
                    
                    if (bestscore > m) {
                        g.grid[fp.y][fp.x] = -1;
                        fp.y = br;
                        fp.x = bc;
                        g.grid[br][bc] = -1;
                        g.grid[bestr][bestc] = -1;
                        g.grid[bestr2][bestc2] = -1;
                        g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                        g.out.emplace_back(bestr, bestc, br, bc);
                        f = true;
                        cnt += 2;
                        break;
                    }
                }
            }
            
            
            if (f) {
                sv.emplace_back(fp.x, fp.y);
                continue;
            }
            
        }
        shuffle(v.begin(), v.end(), mt);
        f = true;
        while (f) {
            f = false;
            // shuffle(v.begin(), v.end(), mt);
            
            for (int d = 0; d < 8; ++d) {
                int br = ep.y + dr[v[d]];
                int bc = ep.x + dc[v[d]];
                if (g.grid[br][bc] == color) {
                    
                    g.grid[ep.y][ep.x] = -1;
                    g.grid[br][bc] = -1;
                    ep.y = br;
                    ep.x = bc;
                    f = true;
                    break;
                }
            }
            
            if (f) {
                ev.emplace_back(ep.x, ep.y);
                continue;
            }
            
            for (int d = 0; d < 8; ++d) {
                int br = ep.y + dr[v[d]];
                int bc = ep.x + dc[v[d]];
                if (g.grid[br][bc] < 0) { continue; }
                {
                    int bestscore = m;
                    int bestr, bestc;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] != color) { continue; }
                        if (this->D[g.grid[cr][cc]][g.grid[br][bc]] > bestscore) {
                            bestscore = this->D[g.grid[cr][cc]][g.grid[br][bc]];
                            bestr = cr;
                            bestc = cc;
                        }
                    }
                    
                    if (bestscore > m) {
                        g.grid[ep.y][ep.x] = -1;
                        ep.y = br;
                        ep.x = bc;
                        g.grid[br][bc] = -1;
                        g.grid[bestr][bestc] = -1;
                        g.out.emplace_back(bestr, bestc, br, bc);
                        f = true;
                        cnt += 1;
                        break;
                    }
                }
            }
            
            if (f) {
                ev.emplace_back(ep.x, ep.y);
                continue;
            }
            
            for (int d = 0; d < 8; ++d) {
                int br = ep.y + dr[v[d]];
                int bc = ep.x + dc[v[d]];
                if (g.grid[br][bc] < 0) { continue; }
                {
                    int bestscore = m;
                    int bestr, bestc, bestr2, bestc2;
                    for (int sd = 0; sd < 8; ++sd) {
                        int cr = br + dr[v[sd]];
                        int cc = bc + dc[v[sd]];
                        if (g.grid[cr][cc] < 0 || (br == cr && bc == cc)) { continue; }
                        for (int sd2 = 0; sd2 < 8; ++sd2) {
                            int cr2 = cr + dr[v[sd2]];
                            int cc2 = cc + dc[v[sd2]];
                            if (g.grid[cr2][cc2] != color) { continue; }
                            int score = this->D[g.grid[cr][cc]][g.grid[br][bc]] + this->D[g.grid[cr2][cc2]][g.grid[cr][cc]];
                            if (score > bestscore) {
                                bestscore = score;
                                bestr = cr;
                                bestc = cc;
                                bestr2 = cr2;
                                bestc2 = cc2;
                            }
                        }
                    }
                    
                    if (bestscore > m) {
                        g.grid[ep.y][ep.x] = -1;
                        ep.y = br;
                        ep.x = bc;
                        g.grid[br][bc] = -1;
                        g.grid[bestr][bestc] = -1;
                        g.grid[bestr2][bestc2] = -1;
                        g.out.emplace_back(bestr2, bestc2, bestr, bestc);
                        g.out.emplace_back(bestr, bestc, br, bc);
                        f = true;
                        cnt += 2;
                        break;
                    }
                }
            }
            
            
            if (f) {
                ev.emplace_back(ep.x, ep.y);
                continue;
            }
            
        }
        
        if (ev.size() + sv.size() + 1 < 6) { return; }
        
        if (ev.size() > 0) {
            int ar = ev[ev.size()-1].y;
            int ac = ev[ev.size()-1].x;
            g.grid[ar][ac] = -1;
            for (int i = ev.size()-2; i >= 0; --i) {
                int br = ev[i].y;
                int bc = ev[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = -1;
            g.out.emplace_back(ar, ac, pr, pc);
            ar = pr;
            ac = pc;
            for (int i = 0; i < sv.size(); ++i) {
                int br = sv[i].y;
                int bc = sv[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = color;
        } else {
            int ar = pr;
            int ac = pc;
            for (int i = 0; i < sv.size(); ++i) {
                int br = sv[i].y;
                int bc = sv[i].x;
                g.grid[ar][ac] = -1;
                g.out.emplace_back(ar, ac, br, bc);
                ar = br;
                ac = bc;
            }
            g.grid[ar][ac] = color;
        }
        
        
        g.cnt += cnt;
        g.score = this->calc_score(g.out) - g.cnt * 5;
    }
    
    int calc_score (vector<rcrc>& v) {
        int score = 0;
        array< array<int, 34>, 34> tgrid = this->grid;
        int chain = 0;
        int prevr = -1;
        int prevc = -1;
        int prevcolor = -1;
        for (auto&& i : v) {
            int a = tgrid[i.r1][i.c1];
            int b = tgrid[i.r2][i.c2];
            
            if (prevr != i.r1 || prevc != i.c1 || prevcolor != a || prevcolor != b) { chain = 0; }
            
            if (a == b) {
                chain += 1;
                score += chain;
            } else {
                score += this->D[a][b];
            }
            
            tgrid[i.r1][i.c1] = -1;
            tgrid[i.r2][i.c2] = a;
            
            prevr = i.r2;
            prevc = i.c2;
            prevcolor = tgrid[i.r2][i.c2];
        }
        return score;
    }
    
    
    mmgrid fill (mmgrid mg) {
        array< array<int, 34>, 34> tgrid = mg.grid;
        // vector< pair<int,  int> > rc;
        
        vector< pair<int, int> > cc;
        for (int y = 0; y < this->C; ++y) {
            for (int x = 0; x < this->C; ++x) {
                cc.emplace_back(y, x);
            }
        }
        
        mt19937 mt(xrnd());
        shuffle(cc.begin(), cc.end(), mt);
        
        for (auto&& i : cc) {
            for (int j = 0; j < 2; ++j) {
                int color1 = i.first;
                int color2 = i.second;
                for (auto&& z : this->vsp) {
                    int r = z.y;
                    int c = z.x;
                    if (tgrid[r][c] != color1) { continue; }
                    for (int d = 0; d < 8; ++d) {
                        int r2 = r + dr[d];
                        int c2 = c + dc[d];
                        if (tgrid[r2][c2] != color2) { continue; }
                        if (this->D2[tgrid[r][c]][tgrid[r2][c2]] >= 0) {
                            mg.out.emplace_back(r, c, r2, c2);
                            tgrid[r2][c2] = tgrid[r][c];
                            tgrid[r][c] = -1;
                            break;
                        }
                    }
                }
            }
        }
        
        for (auto&& i : cc) {
            for (int j = 0; j < 2; ++j) {
                int color1 = i.first;
                int color2 = i.second;
                for (auto&& z : this->vsp) {
                    int r = z.y;
                    int c = z.x;
                    if (tgrid[r][c] != color1) { continue; }
                    for (int d = 0; d < 8; ++d) {
                        int r2 = r + dr[d];
                        int c2 = c + dc[d];
                        if (tgrid[r2][c2] != color2) { continue; }
                        if (this->D2[tgrid[r][c]][tgrid[r2][c2]] >= 0) {
                            mg.out.emplace_back(r, c, r2, c2);
                            tgrid[r2][c2] = tgrid[r][c];
                            tgrid[r][c] = -1;
                            break;
                        }
                    }
                }
            }
        }
        
        
        
        
        mg.score = this->calc_score(mg.out);
        return mg;
    }
    
    mmgrid fill0 (mmgrid mg) {
        array< array<int, 34>, 34> tgrid = mg.grid;
        vector< pair<int,  int> > rc;
        
        // for (int n = 32; n >= 6; --n) {
        //     for (auto&& z : this->vsp) {
        //         int r = z.y;
        //         int c = z.x;
        //         if (tgrid[r][c] < 0) { continue; }
        //         int color = tgrid[r][c];
        //         int pr = r;
        //         int pc = c;
        //         rc.clear();
        //         bool loop = true;
        //         while (loop) {
        //             loop = false;
        //             for (int d = 0; d < 8; ++d) {
        //                 int r2 = pr + dr[d];
        //                 int c2 = pc + dc[d];
        //                 if (tgrid[pr][pc] == tgrid[r2][c2]) {
        //                     rc.emplace_back(r2, c2);
        //                     tgrid[r2][c2] = tgrid[pr][pc];
        //                     tgrid[pr][pc] = -1;
        //                     loop = true;
        //                     pr = r2;
        //                     pc = c2;
        //                     break;
        //                 }
        //             }
        //         }
                
        //         if (rc.size() < n) {
        //             pr = r;
        //             pc = c;
        //             tgrid[r][c] = color;
        //             for (auto&& i : rc) {
        //                 int r2 = i.first;
        //                 int c2 = i.second;
        //                 tgrid[r2][c2] = color;
        //             }
        //         } else {
        //             pr = r;
        //             pc = c;
        //             for (auto&& i : rc) {
        //                 int r2 = i.first;
        //                 int c2 = i.second;
        //                 mg.out.emplace_back(pr, pc, r2, c2);
        //                 loop = true;
        //                 pr = r2;
        //                 pc = c2;
        //             }
        //         }
                
        //     }
        // }
        
        vector< pair<int, int> > cc;
        for (int y = 0; y < this->C; ++y) {
            for (int x = 0; x < this->C; ++x) {
                cc.emplace_back(y, x);
            }
        }
        sort(cc.begin(), cc.end(), [=](const pair<int, int>& a, const pair<int, int>& b) { return this->D[a.first][a.second] > this->D[b.first][b.second]; });
        
        
        for (auto&& i : cc) {
            for (int j = 0; j < 3; ++j) {
                int color1 = i.first;
                int color2 = i.second;
                for (auto&& z : this->vsp) {
                    int r = z.y;
                    int c = z.x;
                    if (tgrid[r][c] != color1) { continue; }
                    for (int d = 0; d < 8; ++d) {
                        int r2 = r + dr[d];
                        int c2 = c + dc[d];
                        if (tgrid[r2][c2] != color2) { continue; }
                        if (this->D2[tgrid[r][c]][tgrid[r2][c2]] >= 0) {
                            mg.out.emplace_back(r, c, r2, c2);
                            tgrid[r2][c2] = tgrid[r][c];
                            tgrid[r][c] = -1;
                            break;
                        }
                    }
                }
            }
        }
        
        for (auto&& i : cc) {
            for (int j = 0; j < 3; ++j) {
                int color1 = i.first;
                int color2 = i.second;
                for (auto&& z : this->vsp) {
                    int r = z.y;
                    int c = z.x;
                    if (tgrid[r][c] != color1) { continue; }
                    for (int d = 0; d < 8; ++d) {
                        int r2 = r + dr[d];
                        int c2 = c + dc[d];
                        if (tgrid[r2][c2] != color2) { continue; }
                        if (this->D2[tgrid[r][c]][tgrid[r2][c2]] >= 0) {
                            mg.out.emplace_back(r, c, r2, c2);
                            tgrid[r2][c2] = tgrid[r][c];
                            tgrid[r][c] = -1;
                            break;
                        }
                    }
                }
            }
        }
        
        mg.score = this->calc_score(mg.out);
        return mg;
    }
    
};



int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    cout.flush();
}