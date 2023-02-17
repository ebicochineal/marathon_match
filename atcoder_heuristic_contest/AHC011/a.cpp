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

template <class T>
struct ScoreState {
    vector< pair<float, T> > v;
    size_t n;
    ScoreState (size_t n) { this->n = n; }
    
    void maxadd (float score, T state) {
        const size_t s = this->v.size();
        if (s < this->n) {
            this->v.emplace_back(score, state);
            sort(this->v.begin(), this->v.end(), [](const pair<float, T>& a, const pair<float, T>& b) { return a.first > b.first; });
        } else if (score > this->v[s-1].first) {
            this->v[s-1] = pair<float, T>(score, state);
            sort(this->v.begin(), this->v.end(), [](const pair<float, T>& a, const pair<float, T>& b) { return a.first > b.first; });
        }
    }
    void minadd (float score, T state) {
        const size_t s = this->v.size();
        if (s < this->n) {
            this->v.emplace_back(score, state);
            sort(this->v.begin(), this->v.end(), [](const pair<float, T>& a, const pair<float, T>& b) { return a.first < b.first; });
        } else if (score < this->v[s-1].first) {
            this->v[s-1] = pair<float, T>(score, state);
            sort(this->v.begin(), this->v.end(), [](const pair<float, T>& a, const pair<float, T>& b) { return a.first < b.first; });
        }
    }
    void clear () { this->v.clear(); }
    size_t size () { return this->v.size(); }
};

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


struct Edge {
public:
    int a, b, cost;
    Edge () {
        this->a = 0;
        this->b = 0;
        this->cost = 1000000;
    }
    Edge (int a, int b, int cost) {
        this->a = a;
        this->b = b;
        this->cost = cost;
    }
    bool operator == (const Edge& t) const { return this->a == t.a && this->b == t.b; }
};
namespace std {
    template <> class hash<Edge> {
    public:
        size_t operator()(const Edge& t) const{ return hash<int>()(t.a<<16) | hash<int>()(t.b); }
    };
}

class GraphDijkstra {
private:
    class Node {
    public:
        int cost;
        int index;
        Node (int cost, int index) {
            this->cost = cost;
            this->index = index;
        }
        bool operator > (const Node& t) const { return this->cost > t.cost; }
        bool operator < (const Node& t) const { return this->cost < t.cost; }
    };
    int tmp = -1;
    vector<int> prevs;
    vector<int> costs;
    priority_queue<Node, vector<Node>, greater<Node> > que;
    vector< vector< pair<int, int> > > edgecost;
public:
    int n;
    int pathcost;
    
    GraphDijkstra () {}
    
    GraphDijkstra (int n) {
        this->n = n;
        this->edgecost = vector< vector< pair<int, int> > >(this->n, vector< pair<int, int> >());
    }
    
    void update (vector<Edge>& edges) {
        for (auto&& i : this->edgecost) { i.clear(); }
        for (auto&& i : edges) {
            this->edgecost[i.a].emplace_back(i.b, i.cost);
        }
    } 
    
    
    void calcPath (int start_i, int end_i, int m, vector<e512pos>& path) {
        static const int limit = numeric_limits<int>::max();
        path.clear();
        if (true) {
            this->prevs = vector<int>(this->n, -1);
            this->costs = vector<int>(this->n, limit);
            this->que = priority_queue<Node, vector<Node>, greater<Node> >();
            this->costs[start_i] = 0;
            this->que.emplace(0, start_i);
        }
        this->tmp = start_i;
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
            if (t.cost >= this->costs[end_i]) { break; }
            this->que.pop();
            for (auto&& i : this->edgecost[t.index]) {
                const int cost = t.cost + i.second;
                if (cost < this->costs[i.first]) {
                    this->costs[i.first] = cost;
                    this->prevs[i.first] = t.index;
                    this->que.emplace(cost, i.first);
                }
            }
        }
        
        if (this->costs[end_i] < limit) {
            this->pathcost = this->costs[end_i];
            int e = end_i;
            while (e > -1) {
                path.emplace_back(e%m, e/m);
                e = this->prevs[e];
            }
            reverse(path.begin(), path.end());
        } else {
            this->pathcost = -1;
        }
    }
};





// LURD
const int dy[4] = {0, -1, 0, 1};
const int dx[4] = {-1, 0, 1, 0};

struct mmstate1 {
    array<int, 16> pcnt;
    array<int, 128> grid;
    array<int, 128> dopen;
    int cnt = 0;
    mmstate1 (array<int, 16>& pcnt, array<int, 128>& grid, int d) {
        this->pcnt = pcnt;
        this->grid = grid;
        for (int i = 0; i < 128; ++i) { this->dopen[i] = 0; }
        this->dopen[0] = d;
        
        for (int i = 1; i < 16; ++i) { this->cnt += this->pcnt[i]; }
    }
};

struct mmstate2 {
    int ignore = 4;
    vector<char> command;
    array<int, 128> grid;
    int score = 0;
    e512pos bp;
    mmstate2 (e512pos bp, array<int, 128>& grid) {
        this->bp = bp;
        this->grid = grid;
    }
};


class MM {
public:
    StopWatch sw;
    int N, T, NN;
    int epy, epx;
    array<int, 128> grid;
    string bestout;
    array<int, 16> pcnt;
    
    GraphDijkstra gd;
    
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->T;
        this->NN = this->N * this->N;
        for (int y = 0; y < this->N; ++y) {
            string s;
            cin >> s;
            for (int x = 0; x < this->N; ++x) {
                if (s[x] >= '0' && s[x] <= '9') {
                    this->grid[y*this->N+x] = s[x] - '0';
                } else {
                    this->grid[y*this->N+x] = s[x] - 'a' + 10;
                }
            }
        }
        
        
        pdebug(this->N, this->T);
        for (int i = 0; i < 16; ++i) { this->pcnt[i] = 0;}
        for (int i = 0; i < this->NN; ++i) { this->pcnt[grid[i]] += 1; }
        
        this->gd = GraphDijkstra(this->NN);
        
    }
    void output () {
        vector<char> vc;
        char prev = '@';
        for (int i = 0; i < min((int)this->bestout.size(), this->T); ++i) {
            if (this->bestout[i] == 'R' && prev == 'L') { vc.pop_back(); prev = '@'; continue; }
            if (this->bestout[i] == 'L' && prev == 'R') { vc.pop_back(); prev = '@'; continue; }
            if (this->bestout[i] == 'U' && prev == 'D') { vc.pop_back(); prev = '@'; continue; }
            if (this->bestout[i] == 'D' && prev == 'U') { vc.pop_back(); prev = '@'; continue; }
            prev = this->bestout[i];
            vc.emplace_back(this->bestout[i]);
        }
        string s;
        for (auto&& i : vc) { s += i; }
        pdebug(s.size());
        cout << s << endl;
    }
    
    string doutput (string out) {
        static vector<char> vc;
        vc.clear();
        char prev = '@';
        for (int i = 0; i < min((int)out.size(), this->T); ++i) {
            if (out[i] == 'R' && prev == 'L') { vc.pop_back(); prev = '@'; continue; }
            if (out[i] == 'L' && prev == 'R') { vc.pop_back(); prev = '@'; continue; }
            if (out[i] == 'U' && prev == 'D') { vc.pop_back(); prev = '@'; continue; }
            if (out[i] == 'D' && prev == 'U') { vc.pop_back(); prev = '@'; continue; }
            prev = out[i];
            vc.emplace_back(out[i]);
        }
        string s;
        for (auto&& i : vc) { s += i; }
        return s;
    }
    
    
    void vinput (array<int, 128>& grid) {
        fdebug(this->N, this->T);
        for (int y = 0; y < this->N; ++y) {
            string s;
            for (int x = 0; x < this->N; ++x) {
                if (grid[y*this->N+x] < 0) {
                    s += "0";
                } else {
                    s += "0123456789abcdef"[grid[y*this->N+x]];
                }
                
            }
            fdebug(s);
        }
    }
    
    void solve () {
        vector< pair<array<int, 128>, int> > v;
        vector< pair<array<int, 128>, int> > v0;
        array<int, 128> g = this->grid;
        int bestscore = 0;
        int ccnt = 0;
        for (int i = 0; i < 64; ++i) {
            array<int, 128> tg = this->grid;
            tg = this->maximize_sa(tg, min(450, max(2400-(int)this->sw.get_milli_time(), 0)), 0, 0);
            int score = this->calc_score(tg);
            if (score > bestscore) {
                bestscore = score;
                g = tg;
                
            }
            if (score >= 500000) {
                ccnt += 1;
                v.emplace_back(tg, score);
            } else {
                v0.emplace_back(tg, score);
            }
            if (this->sw.get_milli_time() > 2500) { break; }
        }
        pdebug("5", ccnt);
        
        this->bestout = this->moves(this->grid, g);
        bestscore = this->simscore(this->bestout);
        int cnt = 0;
        
        sort(v0.begin(), v0.end(), [](const pair<array<int, 128>, int>& a, const pair<array<int, 128>, int>& b) { return a.second > b.second; });
        sort(v.begin(), v.end(), [](const pair<array<int, 128>, int>& a, const pair<array<int, 128>, int>& b) { return a.second > b.second; });
        if (v.size() < 1) { v = v0; }
        
        
        while (this->sw.get_milli_time() < 2900) {
            g = v[xrnd() % min((int)v.size(), 2)].first;
            
            int a = xrnd() % 4;
            for (int i = 0; i < a; ++i) {
                this->rotate(this->grid);
                this->rotate(g);
                this->swapud(this->grid);
                this->swapud(g);
            }
            
            
            string out = cnt % 2 ? this->moves(this->grid, g) : this->moves2(this->grid, g);
            
            for (int i = 0; i < 4-a; ++i) {
                this->rotate(this->grid);
                this->rotate(g);
                this->rotate(out);
                this->swapud(this->grid);
                this->swapud(g);
                this->swapud(out);
            }
            int ts = out.size();
            for (int i = 0; i < 32; ++i) {
                out = this->doutput(out);
                if (ts == out.size()) { break; }
                ts = out.size();
            }
            
            
            int score = this->simscore(out);
            if (score > bestscore) {
                bestscore = score;
                this->bestout = out;
            }
            cnt += 1;
        }
        pdebug("c", cnt);
        
        
        pdebug(this->simscore(this->bestout));
        
        // this->vinput(g);
        
        pdebug(this->calc_score(g), this->sw.get_milli_time());
        pdebug(this->gcnt);
    }
    
    
    bool isopen (int& v, int d) {
        return ((v >> d) & 1) > 0;
    }
    void setclose (int& v, int d) {
        v &= ~(1<<d);
    }
    
    void beamsaerch () {
        char cd[4] = {'L', 'U', 'R', 'D'};
        int bw = 512;
        vector<mmstate2> q;
        vector<mmstate2> qt;
        e512pos sbp;
        for (int i = 0; i < this->NN; ++i) {
            if (this->grid[i] == 0) {
                sbp.x = i % this->N;
                sbp.y = i / this->N;
            }
        }
        mmstate2 t(sbp, this->grid);
        q.emplace_back(t);
        int bestscore = 0;
        int turn = 0;
        
        mt19937 mt(xrnd());
        
        
        while (turn < this->T && turn < 400) {
            turn += 1;
            qt.clear();
            for (auto&& p : q) {
                for (int d = 0; d < 4; ++d) {
                    if (d == p.ignore) { continue; }
                    e512pos np = p.bp;
                    np.x += dx[d];
                    np.y += dy[d];
                    if (np.x < 0 || np.x >= this->N || np.y < 0 || np.y >= this->N) { continue; }
                    mmstate2 n = p;
                    n.bp = np;
                    swap(n.grid[p.bp.y*this->N+p.bp.x], n.grid[np.y*this->N+np.x]);
                    n.score = this->calc_score(n.grid);
                    
                    if (n.score > bestscore) { bestscore = n.score; }
                    
                    n.ignore = (p.ignore+2)%4;
                    n.command.emplace_back(cd[d]);
                    if (n.score >= 500000) { pdebug("hit"); }
                    qt.emplace_back(n);
                }
            }
            q.clear();
            sort(qt.begin(), qt.end(), [](const mmstate2& a, const mmstate2& b) { return a.score > b.score; });
            // shuffle(qt.begin(), qt.end(), mt);
            for (int i = 0; i < min(bw, (int)qt.size()); ++i) {
                q.emplace_back(qt[i]);
            }
        }
        
        pdebug(bestscore);
    }
    
    void saerch () {
        static vector<mmstate1> q;
        q.clear();
        array<int, 128> grid;
        for (int i = 0; i < this->NN; ++i) { grid[i] = -1; }
        
        int p[3] =  {4, 8, 12};
        for (int i = 0; i < 3; ++i) {
            int o = p[i];
            if (this->pcnt[o] > 0) {
                grid[0] = o;
                this->pcnt[o] -= 1;
                q.emplace_back(this->pcnt, grid, o);
                grid[0] = 0;
                this->pcnt[o] += 1;
            }
        }
        
        int sdl[4][8] = {
            {4, 5, 6, 7,12,13,14,15},
            {8, 9,10,11,12,13,14,15},
            {1, 3, 5, 7, 9,11,13,15},
            {2, 3, 6, 7,10,11,14,15},
        };
        int cnt = 0;
        
        // mt19937 mt(xrnd());
        while (q.size() > 0) {
            // if (cnt % 64 == 0) { shuffle(q.begin(), q.end(), mt); }
            
            cnt += 1;
            
            mmstate1 m = q.back();
            q.pop_back();
            
            if (m.cnt < 1) {
                pdebug("hit", this->sw.get_milli_time(), cnt);
                return;
            }
            if (cnt >= 1024) {
                return;
            }
            for (int p = 0; p < this->NN; ++p) {
                if (m.grid[p] < 0) { continue; }
                if (m.dopen[p] < 1) { continue; }
                int x = p % this->N;
                int y = p / this->N;
                for (int d = 0; d < 4; ++d) {
                    if (this->isopen(m.dopen[p], d) == false) { continue; }
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    int np = ny * this->N + nx;
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { break; }
                    if (m.grid[np] > -1) { break; }
                    int r = 0;
                    // r = xrnd()%32;
                    for (int d2 = 0; d2 < 8; ++d2) {
                        int ncell = sdl[d][(d2+r)%8];
                        if (m.pcnt[ncell] == 0) { continue; }
                        int open = ncell;
                        
                        this->setclose(open, (d+2)%4);
                        
                        bool f = false;
                        for (int nd = 0; nd < 4; ++nd) {
                            if (this->isopen(open, nd) == false) { continue; }
                            int nnx = nx + dx[nd];
                            int nny = ny + dy[nd];
                            int nnp = nny * this->N + nnx;
                            if (nnx < 0 || nnx >= this->N || nny < 0 || nny >= this->N) { f = true; }
                            if (m.grid[nnp] > -1) { f = true; }
                            
                            for (int nnd = 0; nnd < 4; ++nnd) {
                                // if (this->isopen(open, nnd) == false) { continue; }
                                int nnnx = nnx + dx[nnd];
                                int nnny = nny + dy[nnd];
                                int nnnp = nnny * this->N + nnnx;
                                if (nnnx < 0 || nnnx >= this->N || nnny < 0 || nnny >= this->N) { continue; }
                                if (m.grid[nnnp] > -1 && this->isopen(m.dopen[nnnp], (nnd+2)%4)) {
                                    f = true;
                                    break;
                                }
                            }
                            
                        }
                        if (f) { continue; }
                        
                        mmstate1 t = m;
                        
                        t.cnt -= 1;
                        t.grid[np] = ncell;
                        t.dopen[np] = open;
                        t.pcnt[ncell] -= 1;
                        this->setclose(t.dopen[p], d);
                        q.emplace_back(t);
                    }
                }
            }
        }
    }
    
    void movepath_dijk (e512pos s, e512pos e, array<int, 128>& grid, vector<e512pos>& path) {
        
        static vector<Edge> edges;
        edges.clear();
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                int ax = x;
                int ay = y;
                if (this->fixed[ay*this->N+ax]) { continue; }
                for (int i = 0; i < 4; ++i) {
                    int bx = ax + dx[i];
                    int by = ay + dy[i];
                    if (bx < 0 || bx >= this->N || by < 0 || by >= this->N) { continue; }
                    if (this->fixed[by*this->N+bx]) { continue; }
                    edges.emplace_back(Edge(ay*this->N+ax, by*this->N+bx, 50+xrnd()%50));
                }
            }
        }
        
        this->gd.update(edges);
        this->gd.calcPath(s.y*this->N+s.x, e.y*this->N+e.x, this->N, path);
    }
    
    array<int, 128> gtarget;
    void movepath_dijk2 (e512pos s, e512pos e, array<int, 128>& grid, vector<e512pos>& path) {
        static array<e512pos, 128> near;
        static bitset<128> use;
        static vector<Edge> edges;
        edges.clear();
        
        
        use.reset();
        
        for (int i = 0; i < this->NN; ++i) {
            if (grid[i] == 0) { continue; }
            if (this->fixed[i]) { continue; }
            int bestdist = 1000;
            int best = -1;
            int ax = i % this->N;
            int ay = i / this->N;
            
            for (int j = 0; j < this->NN; ++j) {
                int bx = j % this->N;
                int by = j / this->N;
                int dist = abs(ax-bx) + abs(ay-by);
                if (this->fixed[j] == false && use[j] == false && grid[i] == this->gtarget[j] && dist < bestdist) {
                    bestdist = dist;
                    best = j;
                }
            }
            if (bestdist < 1000) {
                use[best] = true;
                near[i] = e512pos(best%this->N, best/this->N);
            } else {
                near[i] = e512pos(i%this->N, i/this->N);
            }
        }
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                int ax = x;
                int ay = y;
                int ap = ay*this->N+ax;
                if (this->fixed[ay*this->N+ax]) { continue; }
                for (int i = 0; i < 4; ++i) {
                    int bx = ax + dx[i];
                    int by = ay + dy[i];
                    int bp = by*this->N+bx;
                    if (bx < 0 || bx >= this->N || by < 0 || by >= this->N) { continue; }
                    if (this->fixed[bp]) { continue; }
                    
                    
                    int cost = 150;
                    if (near[bp].x < bx && i == 2) { cost = 0; }
                    if (near[bp].x > bx && i == 0) { cost = 0; }
                    if (near[bp].y < by && i == 3) { cost = 0; }
                    if (near[bp].y > by && i == 1) { cost = 0; }
                    
                    edges.emplace_back(Edge(ap, bp, 50+xrnd()%50 + cost));
                }
            }
        }
        
        this->gd.update(edges);
        this->gd.calcPath(s.y*this->N+s.x, e.y*this->N+e.x, this->N, path);
    }
    bool vcheck (e512pos p) {
        bool b = this->fixed[p.y*this->N+p.x];
        if (b) {
            for (int y = 0; y < this->N; ++y) {
                string st;
                for (int x = 0; x < this->N; ++x) {
                    if (p.x == x && p.y == y) {
                        st += this->fixed[y*this->N+x] ? "@" : "o";
                    } else {
                        st += this->fixed[y*this->N+x] ? "f" : ".";
                    }
                }
                fdebug(st);
            }
        }
        
        
        
        return b;
    }
    
    void blankcellmove (e512pos& bp, e512pos ep, array<int, 128>& grid, array<int, 128>& targetgrid, string& out) {
        if (ep == bp) { return; }
        
        static vector<e512pos> blankpath;
        this->movepath_dijk2(bp, ep, grid, blankpath);
        
        for (int j = 1; j < blankpath.size(); ++j) {
            e512pos bnp = blankpath[j];
            if (bnp.y < bp.y) { this->applycommand('U', bp, out, grid); }
            if (bnp.y > bp.y) { this->applycommand('D', bp, out, grid); }
            if (bnp.x < bp.x) { this->applycommand('L', bp, out, grid); }
            if (bnp.x > bp.x) { this->applycommand('R', bp, out, grid); }
        }
    }
    
    e512pos to_e512pos (int i) { return e512pos(i % this->N, i / this->N);}
    
    
    void cellmove (int si, int ei, e512pos& bp, array<int, 128>& grid, array<int, 128>& targetgrid, string& out) {
        static vector<e512pos> targetpath;
        e512pos ep(ei%this->N, ei/this->N);
        e512pos sp(si%this->N, si/this->N);
        
        this->movepath_dijk(sp, ep, grid, targetpath);
        for (int i = 1; i < targetpath.size(); ++i) {
            e512pos p = targetpath[i-1];
            e512pos np = targetpath[i];
            int fpi = p.y*this->N+p.x;
            
            this->fixed[fpi] = true;
            this->blankcellmove(bp, np, grid, targetgrid, out);
            this->fixed[fpi] = false;
            
            if (p.y < np.y) { this->applycommand('U', bp, out, grid); }
            if (p.y > np.y) { this->applycommand('D', bp, out, grid); }
            if (p.x < np.x) { this->applycommand('L', bp, out, grid); }
            if (p.x > np.x) { this->applycommand('R', bp, out, grid); }
        }
    }
    
    void applycommand (char c, e512pos& bp, string& out, array<int, 128>& grid) {
        e512pos p = bp;
        if (c == 'U') { bp.y -= 1; }
        if (c == 'D') { bp.y += 1; }
        if (c == 'L') { bp.x -= 1; }
        if (c == 'R') { bp.x += 1; }
        swap(grid[p.y*this->N+p.x], grid[bp.y*this->N+bp.x]);
        out += c;
        
    }
    
    void swapud (array<int, 128>& g) {
        for (int i = 0; i < this->N/2; ++i) {
            for (int x = 0; x < this->N; ++x) {
                swap(g[i*this->N+x], g[(this->N-1-i)*this->N+x]);
            }
        }
    }
    
    
    void swapud (string& s) {
        string t;
        for (auto&& i : s) {
            if (i == 'U') {
                t += 'D';
            } else if (i == 'D') {
                t += 'U';
            } else {
                t += i;
            }
        }
        s = t;
    }
    void rotate (array<int, 128>& g) {
        for (int y = 0; y < this->N; ++y) {
            for (int x = y+1; x < this->N; ++x) {
                swap(g[y*this->N+x], g[x*this->N+y]);
            }
        }
    }
    void rotate (string& s) {
        string t;
        for (auto&& i : s) {
            if (i == 'R') {
                t += 'D';
            } else if (i == 'L') {
                t += 'U';
            } else if (i == 'U') {
                t += 'L';
            } else if (i == 'D') {
                t += 'R';
            } else {
                t += i;
            }
        }
        s = t;
    }
    
    int simscore (string out) {
        array<int, 128> tgrid = this->grid;
        e512pos bp;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (tgrid[y*this->N+x] == 0) {
                    bp.x = x;
                    bp.y = y;
                }
            }
        }
        
        int t = min((int)out.size(), this->T);
        for (int i = 0; i < t; ++i) {
            char c = out[i];
            if (c == 'U') {
                int a = bp.y * this->N+ bp.x;
                bp.y -= 1;
                int b = bp.y * this->N+ bp.x;
                swap(tgrid[a], tgrid[b]);
            } else if (c == 'D') {
                int a = bp.y * this->N+ bp.x;
                bp.y += 1;
                int b = bp.y * this->N+ bp.x;
                swap(tgrid[a], tgrid[b]);
            } else if (c == 'L') {
                int a = bp.y * this->N+ bp.x;
                bp.x -= 1;
                int b = bp.y * this->N+ bp.x;
                swap(tgrid[a], tgrid[b]);
            } else {
                int a = bp.y * this->N+ bp.x;
                bp.x += 1;
                int b = bp.y * this->N+ bp.x;
                swap(tgrid[a], tgrid[b]);
            }
        }
        return this->calc_score2(tgrid, t);
    }
    
    bitset<128> fixed;
    
    string moves (array<int, 128> grid, array<int, 128>& targetgrid) {
        this->gtarget = targetgrid;
        this->fixed.reset();
        string out;
        
        e512pos bp, lp;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (grid[y*this->N+x] == 0) {
                    bp.x = x;
                    bp.y = y;
                }
                if (targetgrid[y*this->N+x] == 0) {
                    lp.x = x;
                    lp.y = y;
                }
            }
        }
        
        
        int mu = lp.y-1;
        int md = lp.y;
        int ml = lp.x-1;
        int mr = lp.x;
        
        if (lp.y == 0) {
            mu += 1;
            md += 1;
        }
        if (lp.x == 0) {
            mr += 1;
            ml += 1;
        }
        
        
        // U
        for (int y = 0; y < mu; ++y) {
            if (y >= mu-1){
                for (int x = 0; x < this->N-2; ++x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                }
                
                {
                    int ax = this->N-2;
                    int bx = this->N-1;
                    int cy = y+1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('D', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('L', bp, out, grid);
                        this->applycommand('D', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "ULDDRULURDDLURULD";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            } else {
                int ax = 0;
                int bx = 1;
                int cy = y+1;
                int dy = y+2;
                
                int ai = y*this->N+ax;
                int bi = y*this->N+bx;
                int ci = cy*this->N+ax;
                int di = dy*this->N+ax;
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (grid[ci] != targetgrid[ai]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                }
                this->fixed[ci] = true;
                
                for (int x = 1; x < this->N-1; ++x) {
                    int ti = y * this->N + x;
                    int tti = y * this->N + x + 1;
                    if (grid[ti] != targetgrid[tti]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[tti] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        this->cellmove(si, ti, bp, grid, targetgrid, out);
                    }
                    this->fixed[ti] = true;
                }
                
                this->blankcellmove(bp, e512pos((this->N-1), y), grid, targetgrid, out);
                for (int x = 1; x < this->N; ++x) { this->applycommand('L', bp, out, grid); }
                this->applycommand('D', bp, out, grid);
                for (int x = 0; x < this->N; ++x) { this->fixed[y*this->N+x] = true; }
                this->fixed[ci] = false;
                
            }
            
        }
        
        // D
        for (int y = this->N-1; y > md; --y) {
            if (y >= md + 1){
                for (int x = 0; x < this->N-2; ++x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                    
                    
                }
                
                {
                    int ax = this->N-2;
                    int bx = this->N-1;
                    int cy = y-1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('U', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('L', bp, out, grid);
                        this->applycommand('U', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "DLUURDLDRUULDRDLU";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            } else {
                int ax = 0;
                int bx = 1;
                int cy = y-1;
                int dy = y-2;
                
                int ai = y*this->N+ax;
                int bi = y*this->N+bx;
                int ci = cy*this->N+ax;
                int di = dy*this->N+ax;
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (grid[ci] != targetgrid[ai]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                }
                this->fixed[ci] = true;
                
                for (int x = 1; x < this->N-1; ++x) {
                    int ti = y * this->N + x;
                    int tti = y * this->N + x + 1;
                    if (grid[ti] != targetgrid[tti]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[tti] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        this->cellmove(si, ti, bp, grid, targetgrid, out);
                    }
                    this->fixed[ti] = true;
                }
                
                this->blankcellmove(bp, e512pos((this->N-1), y), grid, targetgrid, out);
                for (int x = 1; x < this->N; ++x) { this->applycommand('L', bp, out, grid); }
                this->applycommand('U', bp, out, grid);
                for (int x = 0; x < this->N; ++x) { this->fixed[y*this->N+x] = true; }
                this->fixed[ci] = false;
                
            }
        }
        
        // L
        for (int x = 0; x < ml; ++x) {
            for (int y = mu; y <= md-2; ++y) {
                int ei = y*this->N+x;
                if (grid[ei] != targetgrid[ei]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-x)+abs(sy-y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                }
                this->fixed[ei] = true;
            }
            
            {
                int ay = mu;
                int by = mu+1;
                int cx = x+1;
                
                int ai = ay*this->N+x;
                int bi = by*this->N+x;
                int ci = ay*this->N+cx;
                int di = by*this->N+cx;
                
                
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (bp.y*this->N+bp.x == bi) { this->applycommand('R', bp, out, grid); }
                if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                    
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                    
                }
                
                if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                    this->fixed[ci] = true;
                    this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                    this->fixed[ci] = false;
                    
                    this->applycommand('U', bp, out, grid);
                    this->applycommand('R', bp, out, grid);
                }
                this->fixed[bi] = true;
                
                
                if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                    this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                    string com = "LURRDLULDRRULDLUR";
                    for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                    
                }
            }
        }
        
        // R
        for (int x = this->N-1; x > mr; --x) {
            for (int y = mu; y <= md-2; ++y) {
                int ei = y*this->N+x;
                if (grid[ei] != targetgrid[ei]) {
                    int mindist = 1000;
                    int si = 0;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-x)+abs(sy-y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                }
                this->fixed[ei] = true;
                
                
            }
            {
                int ay = mu;
                int by = mu+1;
                int cx = x-1;
                
                int ai = ay*this->N+x;
                int bi = by*this->N+x;
                int ci = ay*this->N+cx;
                int di = by*this->N+cx;
                
                
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (bp.y*this->N+bp.x == bi) { this->applycommand('L', bp, out, grid); }
                if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                    
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                    
                }
                
                if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                    this->fixed[ci] = true;
                    this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                    this->fixed[ci] = false;
                    
                    this->applycommand('U', bp, out, grid);
                    this->applycommand('L', bp, out, grid);
                }
                this->fixed[bi] = true;
                
                
                if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                    this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                    string com = "RULLDRURDLLURDRUL";
                    for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                    
                }
            }
        }
        
        // for (int y = 0; y < this->N; ++y) {
        //     string st;
        //     for (int x = 0; x < this->N; ++x) {
        //         st += this->fixed[y*this->N+x] ? "1" : "0";
        //     }
        //     fdebug(st);
        // }
        
        // if (this->fixed[(bp.y)*this->N+(bp.x)]) {
        //     for (int y = 0; y < this->N; ++y) {
        //         string st;
        //         for (int x = 0; x < this->N; ++x) {
        //             st += this->fixed[y*this->N+x] ? "1" : "0";
        //         }
        //         fdebug(st);
        //     }
        // }
        
        if (xrnd()) {
            for (int i = 0; i < 4; ++i) {
                bool f = true;
                for (int j = 0; j < this->NN; ++j) {
                    if (grid[j] != targetgrid[j]) { f = false; }
                }
                if (f) { break; }
                
                
                if (bp.y > 0) {
                    if (this->fixed[(bp.y-1)*this->N+(bp.x)] == false && (bp.x == this->N-1 || this->fixed[(bp.y)*this->N+(bp.x+1)])) {
                        this->applycommand('U', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.x > 0) {
                    if (this->fixed[(bp.y)*this->N+(bp.x-1)] == false && (bp.y == 0 || this->fixed[(bp.y-1)*this->N+(bp.x)])) {
                        this->applycommand('L', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                
                if (bp.y < this->N-1) {
                    if (this->fixed[(bp.y+1)*this->N+(bp.x)] == false && (bp.x == 0 || this->fixed[(bp.y)*this->N+(bp.x-1)])) {
                        this->applycommand('D', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                
                }
                if (bp.x < this->N-1) {
                    if (this->fixed[(bp.y)*this->N+(bp.x+1)] == false && (bp.y == this->N-1 || this->fixed[(bp.y+1)*this->N+(bp.x)])) {
                        this->applycommand('R', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                bool f = true;
                for (int j = 0; j < this->NN; ++j) {
                    if (grid[j] != targetgrid[j]) { f = false; }
                }
                if (f) { break; }
                
                
                if (bp.y > 0) {
                    if (this->fixed[(bp.y-1)*this->N+(bp.x)] == false && (bp.x == 0 || this->fixed[(bp.y)*this->N+(bp.x-1)])) {
                        this->applycommand('U', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.x < this->N-1) {
                    if (this->fixed[(bp.y)*this->N+(bp.x+1)] == false && (bp.y == 0 || this->fixed[(bp.y-1)*this->N+(bp.x)])) {
                        this->applycommand('R', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.y < this->N-1) {
                    if (this->fixed[(bp.y+1)*this->N+(bp.x)] == false && (bp.x == this->N-1 || this->fixed[(bp.y)*this->N+(bp.x+1)])) {
                        this->applycommand('D', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                
                }
                if (bp.x > 0) {
                    if (this->fixed[(bp.y)*this->N+(bp.x-1)] == false && (bp.y == this->N-1 || this->fixed[(bp.y+1)*this->N+(bp.x)])) {
                        this->applycommand('L', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                
                
                
            }
        }
        
        return out;
    }
    
    
    string moves2 (array<int, 128> grid, array<int, 128>& targetgrid) {
        this->gtarget = targetgrid;
        this->fixed.reset();
        string out;
        
        e512pos bp, lp;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (grid[y*this->N+x] == 0) {
                    bp.x = x;
                    bp.y = y;
                }
                if (targetgrid[y*this->N+x] == 0) {
                    lp.x = x;
                    lp.y = y;
                }
            }
        }
        
        
        int mu = lp.y-1;
        int md = lp.y;
        int ml = lp.x-1;
        int mr = lp.x;
        
        if (lp.y == 0) {
            mu += 1;
            md += 1;
        }
        if (lp.x == 0) {
            mr += 1;
            ml += 1;
        }
        
        
        // U
        for (int y = 0; y < mu; ++y) {
            if (y % 2){
                for (int x = 0; x < this->N-2; ++x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                }
                
                {
                    int ax = this->N-2;
                    int bx = this->N-1;
                    int cy = y+1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('D', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('L', bp, out, grid);
                        this->applycommand('D', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "ULDDRULURDDLURULD";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            } else {
                for (int x = this->N-1; x > 1; --x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                }
                
                {
                    int ax = 1;
                    int bx = 0;
                    int cy = y+1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('D', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('R', bp, out, grid);
                        this->applycommand('D', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "URDDLURULDDRULURD";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            }
        }
        
        // D
        for (int y = this->N-1; y > md; --y) {
            if (y % 2){
                for (int x = 0; x < this->N-2; ++x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                    
                    
                }
                
                {
                    int ax = this->N-2;
                    int bx = this->N-1;
                    int cy = y-1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('U', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('L', bp, out, grid);
                        this->applycommand('U', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "DLUURDLDRUULDRDLU";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            } else {
                for (int x = this->N-1; x > 1; --x) {
                    int ei = y*this->N+x;
                    if (grid[ei] != targetgrid[ei]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-x)+abs(sy-y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ei] = true;
                    
                    
                }
                {
                    int ax = 1;
                    int bx = 0;
                    int cy = y-1;
                    
                    int ai = y*this->N+ax;
                    int bi = y*this->N+bx;
                    int ci = cy*this->N+ax;
                    int di = cy*this->N+bx;
                    e512pos ap(ai%this->N, ai%this->N);
                    e512pos cp(ci%this->N, ci%this->N);
                    
                    
                    if (grid[ai] != targetgrid[bi]) {
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-ap.x)+abs(sy-ap.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                    }
                    this->fixed[ai] = true;
                    
                    if (bp.y*this->N+bp.x == bi) { this->applycommand('U', bp, out, grid); }
                    if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                        
                        int mindist = 1000;
                        int si = -1;
                        for (int i = 0; i < this->NN; ++i) {
                            int sy = i / this->N;
                            int sx = i % this->N;
                            int dist = abs(sx-cp.x)+abs(sy-cp.y);
                            if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                                mindist = dist;
                                si = i;
                            }
                        }
                        
                        if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                        
                    }
                    
                    if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                        this->fixed[ci] = true;
                        this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                        this->fixed[ci] = false;
                        
                        this->applycommand('R', bp, out, grid);
                        this->applycommand('U', bp, out, grid);
                    }
                    this->fixed[bi] = true;
                    
                    
                    if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                        this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                        string com = "DRUULDRDLUURDLDRU";
                        for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                        
                    }
                }
                
            }
        }
        
        // L
        for (int x = 0; x < ml; ++x) {
            for (int y = mu; y <= md-2; ++y) {
                int ei = y*this->N+x;
                if (grid[ei] != targetgrid[ei]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-x)+abs(sy-y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                }
                this->fixed[ei] = true;
            }
            
            {
                int ay = mu;
                int by = mu+1;
                int cx = x+1;
                
                int ai = ay*this->N+x;
                int bi = by*this->N+x;
                int ci = ay*this->N+cx;
                int di = by*this->N+cx;
                
                
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (bp.y*this->N+bp.x == bi) { this->applycommand('R', bp, out, grid); }
                if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                    
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                    
                }
                
                if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                    this->fixed[ci] = true;
                    this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                    this->fixed[ci] = false;
                    
                    this->applycommand('U', bp, out, grid);
                    this->applycommand('R', bp, out, grid);
                }
                this->fixed[bi] = true;
                
                
                if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                    this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                    string com = "LURRDLULDRRULDLUR";
                    for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                    
                }
            }
        }
        
        // R
        for (int x = this->N-1; x > mr; --x) {
            for (int y = mu; y <= md-2; ++y) {
                int ei = y*this->N+x;
                if (grid[ei] != targetgrid[ei]) {
                    int mindist = 1000;
                    int si = 0;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-x)+abs(sy-y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ei] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ei, bp, grid, targetgrid, out); }
                }
                this->fixed[ei] = true;
                
                
            }
            {
                int ay = mu;
                int by = mu+1;
                int cx = x-1;
                
                int ai = ay*this->N+x;
                int bi = by*this->N+x;
                int ci = ay*this->N+cx;
                int di = by*this->N+cx;
                
                
                e512pos ap(ai%this->N, ai%this->N);
                e512pos cp(ci%this->N, ci%this->N);
                
                
                if (grid[ai] != targetgrid[bi]) {
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-ap.x)+abs(sy-ap.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[bi] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    if (si > -1) { this->cellmove(si, ai, bp, grid, targetgrid, out); }
                }
                this->fixed[ai] = true;
                
                if (bp.y*this->N+bp.x == bi) { this->applycommand('L', bp, out, grid); }
                if (grid[ci] != targetgrid[ai] && grid[bi] != targetgrid[ai]) {
                    
                    int mindist = 1000;
                    int si = -1;
                    for (int i = 0; i < this->NN; ++i) {
                        int sy = i / this->N;
                        int sx = i % this->N;
                        int dist = abs(sx-cp.x)+abs(sy-cp.y);
                        if (this->fixed[i] == false && grid[i] == targetgrid[ai] && dist < mindist) {
                            mindist = dist;
                            si = i;
                        }
                    }
                    
                    if (si > -1) { this->cellmove(si, ci, bp, grid, targetgrid, out); }
                    
                }
                
                if (grid[ci] == targetgrid[ai] && grid[ai] == targetgrid[bi]) {
                    this->fixed[ci] = true;
                    this->blankcellmove(bp, e512pos(bi%this->N, bi/this->N), grid, targetgrid, out);
                    this->fixed[ci] = false;
                    
                    this->applycommand('U', bp, out, grid);
                    this->applycommand('L', bp, out, grid);
                }
                this->fixed[bi] = true;
                
                
                if (grid[ai] != targetgrid[ai] || grid[bi] != targetgrid[bi]) {
                    this->blankcellmove(bp, e512pos(di%this->N, di/this->N), grid, targetgrid, out);
                    string com = "RULLDRURDLLURDRUL";
                    for (auto&& i : com) { this->applycommand(i, bp, out, grid); }
                    
                }
            }
        }
        
        // for (int y = 0; y < this->N; ++y) {
        //     string st;
        //     for (int x = 0; x < this->N; ++x) {
        //         st += this->fixed[y*this->N+x] ? "1" : "0";
        //     }
        //     fdebug(st);
        // }
        
        // if (this->fixed[(bp.y)*this->N+(bp.x)]) {
        //     for (int y = 0; y < this->N; ++y) {
        //         string st;
        //         for (int x = 0; x < this->N; ++x) {
        //             st += this->fixed[y*this->N+x] ? "1" : "0";
        //         }
        //         fdebug(st);
        //     }
        // }
        if (xrnd()) {
            for (int i = 0; i < 4; ++i) {
                bool f = true;
                for (int j = 0; j < this->NN; ++j) {
                    if (grid[j] != targetgrid[j]) { f = false; }
                }
                if (f) { break; }
                
                
                if (bp.y > 0) {
                    if (this->fixed[(bp.y-1)*this->N+(bp.x)] == false && (bp.x == this->N-1 || this->fixed[(bp.y)*this->N+(bp.x+1)])) {
                        this->applycommand('U', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.x > 0) {
                    if (this->fixed[(bp.y)*this->N+(bp.x-1)] == false && (bp.y == 0 || this->fixed[(bp.y-1)*this->N+(bp.x)])) {
                        this->applycommand('L', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                
                if (bp.y < this->N-1) {
                    if (this->fixed[(bp.y+1)*this->N+(bp.x)] == false && (bp.x == 0 || this->fixed[(bp.y)*this->N+(bp.x-1)])) {
                        this->applycommand('D', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                
                }
                if (bp.x < this->N-1) {
                    if (this->fixed[(bp.y)*this->N+(bp.x+1)] == false && (bp.y == this->N-1 || this->fixed[(bp.y+1)*this->N+(bp.x)])) {
                        this->applycommand('R', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                bool f = true;
                for (int j = 0; j < this->NN; ++j) {
                    if (grid[j] != targetgrid[j]) { f = false; }
                }
                if (f) { break; }
                
                
                if (bp.y > 0) {
                    if (this->fixed[(bp.y-1)*this->N+(bp.x)] == false && (bp.x == 0 || this->fixed[(bp.y)*this->N+(bp.x-1)])) {
                        this->applycommand('U', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.x < this->N-1) {
                    if (this->fixed[(bp.y)*this->N+(bp.x+1)] == false && (bp.y == 0 || this->fixed[(bp.y-1)*this->N+(bp.x)])) {
                        this->applycommand('R', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                if (bp.y < this->N-1) {
                    if (this->fixed[(bp.y+1)*this->N+(bp.x)] == false && (bp.x == this->N-1 || this->fixed[(bp.y)*this->N+(bp.x+1)])) {
                        this->applycommand('D', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                
                }
                if (bp.x > 0) {
                    if (this->fixed[(bp.y)*this->N+(bp.x-1)] == false && (bp.y == this->N-1 || this->fixed[(bp.y+1)*this->N+(bp.x)])) {
                        this->applycommand('L', bp, out, grid);
                    }
                    bool f = true;
                    for (int j = 0; j < this->NN; ++j) {
                        if (grid[j] != targetgrid[j]) { f = false; }
                    }
                    if (f) { break; }
                }
                
                
                
            }
        }
        return out;
    }
    
    int gcnt = 0;
    array<int, 128> maximize_sa (array<int, 128> v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        array<int, 128> bestv = v;
        double bestscore = this->calc_score(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        
        while (true) {
            {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                int a = xrnd() % (this->NN);
                int b = xrnd() % (this->NN);
                swap(v[a], v[b]);
                int tmpscore = v[a] == v[b] ? lastscore : this->calc_score(v, bestscore);
                // const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                // const double probability = exp((tmpscore - lastscore) / temp);
                // const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                if (tmpscore >= lastscore) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestv = v;
                        if (bestscore >= 500000) { return bestv; }
                    }
                } else {
                    swap(v[a], v[b]);
                }
                cnt += 1;
                this->gcnt += 1;
            }
            {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                int a = xrnd() % (this->NN);
                int b = xrnd() % (this->NN);
                int c = xrnd() % (this->NN);
                int d = xrnd() % (this->NN);
                swap(v[a], v[b]);
                swap(v[c], v[d]);
                int tmpscore = this->calc_score(v, bestscore);
                // const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                // const double probability = exp((tmpscore - lastscore) / temp);
                // const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                if (tmpscore >= lastscore) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestv = v;
                        if (bestscore >= 500000) { return bestv; }
                    }
                } else {
                    swap(v[c], v[d]);
                    swap(v[a], v[b]);
                }
                cnt += 1;
                this->gcnt += 1;
            }
        }
        return bestv;
    }
    
    int calc_score (array<int, 128>& grid) {
        static bitset<128> open;
        static vector< pair<e512pos, int> > q;
        int maxcnt = 0;
        open.reset();
        
        for (int i = 0; i < this->NN; ++i) {
            if (open[i]) { continue; }
            int px = i % this->N;
            int py = i / this->N;
            // open[i] = true;
            int cnt = 1;
            q.emplace_back(e512pos(px, py), -1);
            bool f = false;
            while (q.size() > 0) {
                e512pos pos = q.back().first;
                int p = pos.y * this->N + pos.x;
                open[p] = true;
                int prev = q.back().second;
                q.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int nx = pos.x + dx[d];
                    int ny = pos.y + dy[d];
                    int np = ny * this->N + nx;
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        cnt = 0;
                        q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
            }
            if (f) { cnt = 0; }
            maxcnt = max(cnt, maxcnt);
        }
        int nn = this->NN-1;
        if (maxcnt == nn) { maxcnt = 500000 + this->md_score(grid); }
        // if (maxcnt == nn && this->even_odd(grid)) { maxcnt = 500000; }
        
        return maxcnt;
        
        // return round(500000 * (maxcnt / nn));
    }
    
    // int calc_score (array<int, 128>& grid, int bs) {
    //     static bitset<128> open;
    //     static vector< pair<e512pos, int> > q;
    //     int maxcnt = 0;
    //     open.reset();
        
    //     for (int i = 0; i < this->NN; ++i) {
    //         if (open[i]) { continue; }
    //         int px = i % this->N;
    //         int py = i / this->N;
    //         // open[i] = true;
    //         int cnt = 1;
    //         q.emplace_back(e512pos(px, py), -1);
    //         bool f = false;
    //         while (q.size() > 0) {
    //             e512pos pos = q.back().first;
    //             int p = pos.y * this->N + pos.x;
    //             open[p] = true;
    //             int prev = q.back().second;
    //             q.pop_back();
    //             for (int d = 0; d < 4; ++d) {
    //                 int nx = pos.x + dx[d];
    //                 int ny = pos.y + dy[d];
    //                 int np = ny * this->N + nx;
    //                 if (((grid[p] >> d) & 1) == 0) { continue; }
    //                 if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
    //                 if (np == prev) { continue; }
    //                 if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
    //                 if (open[np]) {
    //                     q.clear();
    //                     f = true;
    //                 } else {
    //                     // open[np] = true;
    //                     cnt += 1;
    //                     q.emplace_back(e512pos(nx, ny), p);
    //                 }
    //             }
    //         }
    //         if (cnt < bs && this->NN-1-cnt < bs) { return 0; }
            
    //         if (f) { cnt = 0; }
    //         maxcnt = max(cnt, maxcnt);
    //     }
    //     int nn = this->NN-1;
    //     if (maxcnt == nn) { maxcnt = 500000 + this->md_score(grid); }
    //     // if (maxcnt == nn && this->even_odd(grid)) { maxcnt = 500000; }
        
    //     return maxcnt;
        
    //     // return round(500000 * (maxcnt / nn));
    // }
    
    int calc_score (array<int, 128>& grid, int bs) {
        static bitset<128> open;
        static vector< pair<e512pos, int> > q;
        int maxcnt = 0;
        open.reset();
        
        for (int i = 0; i < this->NN; ++i) {
            if (open[i]) { continue; }
            int px = i % this->N;
            int py = i / this->N;
            // open[i] = true;
            int cnt = 1;
            q.emplace_back(e512pos(px, py), -1);
            bool f = false;
            while (q.size() > 0) {
                e512pos pos = q.back().first;
                int p = pos.y * this->N + pos.x;
                open[p] = true;
                int prev = q.back().second;
                q.pop_back();
                for (int d = 0; d == 0 && pos.x > 0; ++d) {
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    int nx = pos.x + dx[d];
                    int ny = pos.y;
                    int np = ny * this->N + nx;
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
                for (int d = 1; d == 1 && pos.y > 0; ++d) {
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    int nx = pos.x;
                    int ny = pos.y + dy[d];
                    int np = ny * this->N + nx;
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
                for (int d = 2; d == 2 && pos.x < this->N-1; ++d) {
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    int nx = pos.x + dx[d];
                    int ny = pos.y;
                    int np = ny * this->N + nx;
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
                for (int d = 3; d == 3 && pos.y < this->N-1; ++d) {
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    int nx = pos.x;
                    int ny = pos.y + dy[d];
                    int np = ny * this->N + nx;
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        // q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
            }
            
            if (f) { cnt = 0; }
            maxcnt = max(cnt, maxcnt);
            if (maxcnt <= bs && this->NN - open.count() <= bs) { return maxcnt; }
        }
        int nn = this->NN-1;
        if (maxcnt == nn) { maxcnt = 500000 + this->md_score(grid); }
        // if (maxcnt == nn && this->even_odd(grid)) { maxcnt = 500000; }
        
        return maxcnt;
        
        // return round(500000 * (maxcnt / nn));
    }
    
    int calc_score2 (array<int, 128>& grid, int len) {
        static bitset<128> open;
        static vector< pair<e512pos, int> > q;
        int maxcnt = 0;
        open.reset();
        
        for (int i = 0; i < this->NN; ++i) {
            if (open[i]) { continue; }
            int px = i % this->N;
            int py = i / this->N;
            // open[i] = true;
            int cnt = 1;
            q.emplace_back(e512pos(px, py), -1);
            bool f = false;
            while (q.size() > 0) {
                e512pos pos = q.back().first;
                int p = pos.y * this->N + pos.x;
                open[p] = true;
                int prev = q.back().second;
                q.pop_back();
                for (int d = 0; d < 4; ++d) {
                    int nx = pos.x + dx[d];
                    int ny = pos.y + dy[d];
                    int np = ny * this->N + nx;
                    if (((grid[p] >> d) & 1) == 0) { continue; }
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    if (np == prev) { continue; }
                    if (((grid[np] >> ((d+2) % 4)) & 1) == 0) { continue; }
                    if (open[np]) {
                        cnt = 0;
                        q.clear();
                        f = true;
                    } else {
                        // open[np] = true;
                        cnt += 1;
                        q.emplace_back(e512pos(nx, ny), p);
                    }
                }
            }
            if (f) { cnt = 0; }
            maxcnt = max(cnt, maxcnt);
        }
        int nn = this->NN-1;
        if (maxcnt == nn) {
            return round(500000 * (2-(float)(len)/(this->T)));
        } else {
            return round(500000 * ((float)maxcnt / nn));
        }
    }
    
    int md_score (array<int, 128>& g) {
        static bitset<128> use;
        use.reset();
        int score = 0;
        
        for (int i = 0; i < this->NN; ++i) {
            if (g[i] == 0) { continue; }
            int bestdist = 1000;
            int best = -1;
            int ax = i % this->N;
            int ay = i / this->N;
            
            for (int j = 0; j < this->NN; ++j) {
                int bx = j % this->N;
                int by = j / this->N;
                int dist = abs(ax-bx) + abs(ay-by);
                if (use[j]==false && g[i] == this->grid[j] && dist < bestdist) {
                    bestdist = dist;
                    best = j;
                }
            }
            use[best] = true;
            score += bestdist;
        }
        use.reset();
        for (int i = this->NN-1; i >= 0; --i) {
            if (g[i] == 0) { continue; }
            int bestdist = 1000;
            int best = -1;
            int ax = i % this->N;
            int ay = i / this->N;
            
            for (int j = 0; j < this->NN; ++j) {
                int bx = j % this->N;
                int by = j / this->N;
                int dist = abs(ax-bx) + abs(ay-by);
                if (use[j]==false && g[i] == this->grid[j] && dist < bestdist) {
                    bestdist = dist;
                    best = j;
                }
            }
            use[best] = true;
            score += bestdist;
        }
        
        return this->T*2 - score;
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

