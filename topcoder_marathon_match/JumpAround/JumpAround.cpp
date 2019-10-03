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
#include <random>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

int rawgrid[55][55];
int tmpgrid[55][55];
int prioritygrid[55][55];
int scores[630];
int tscores[630];
bool xgrid[2505];
vector<int> vret[630];
vector<int> tvret[630];


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
        return ((this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm));
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
    bool operator == (const Edge &t) const { return this->a == t.a && this->b == t.b; }
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
        bool operator > (const Node &t) const { return this->cost > t.cost; }
        bool operator < (const Node &t) const { return this->cost < t.cost; }
    };
    int tmp = -1;
    vector<int> prevs;
    vector<int> costs;
    vector<int> jumps;
    priority_queue<Node, vector<Node>, greater<Node> > que;
    vector< vector< pair<int, int> > > edgecost;
public:
    int n, m, p;
    vector<int> path;
    vector<int> rpath;
    int pathcost;
    
    GraphDijkstra (int m, int n, int p, vector<Edge> edges, bool undir = false) {
        this->pathcost = 0;
        this->path.clear();
        this->n = n;
        this->m = m;
        this->p = p;
        this->edgecost = vector< vector< pair<int, int> > >(this->n, vector< pair<int, int> >());
        if (undir) {// undirected
            for (auto&& i : edges) {
                this->edgecost[i.a].emplace_back(i.b, i.cost);
                this->edgecost[i.b].emplace_back(i.a, i.cost);
            }
        } else {// directed
            for (auto&& i : edges) {
                this->edgecost[i.a].emplace_back(i.b, i.cost);
            }
        }
    }
    
    void Update (vector<Edge>& edges) {
        this->tmp = -1;
        this->pathcost = 0;
        this->path.clear();
        for (auto&& i : this->edgecost) { i.clear(); }
        
        for (auto&& i : edges) {
            this->edgecost[i.a].emplace_back(i.b, i.cost);
        }
    }
    
    void Update2 (unordered_set<int>& us, vector<Edge>& uedges, int p) {
        this->p = p;
        this->tmp = -1;
        this->pathcost = 0;
        this->path.clear();
        for (auto&& i : us) { this->edgecost[i].clear(); }
        
        for (auto&& i : uedges) {
            this->edgecost[i.a].emplace_back(i.b, i.cost);
        }
    }
    
    void calcPath (int start_i, int end_i) {
        static const int limit = numeric_limits<int>::max();
        this->path.clear();
        //this->rpath.clear();
        if (this->tmp != start_i) {
            this->prevs = vector<int>(this->n, -1);
            this->costs = vector<int>(this->n, limit);
            this->jumps = vector<int>(this->n, 1);
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
                    if (i.second == 0) {
                        this->costs[i.first] = cost + (this->jumps[t.index] == 0 ? 0 : 1);
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 0;// jump
                        this->que.emplace(cost + (this->jumps[t.index] == 0 ? 0 : 1), i.first);
                    } else {
                        this->costs[i.first] = cost;
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 1;// not jump
                        this->que.emplace(cost, i.first);
                    }
                }
            }
        }
        
        if (this->costs[end_i] < limit) {
            this->pathcost = this->costs[end_i];
            int e = end_i;
            while (e > -1) {
                this->path.emplace_back(e);
                e = this->prevs[e];
            }
            // this->path = this->path;
            reverse(this->path.begin(), this->path.end());
        } else {
            this->pathcost = -1;
        }
    }
    
    vector<int> xs;
    void calcPath (int start_i) {
        static const int limit = numeric_limits<int>::max();
        this->path.clear();
        //this->rpath.clear();
        this->xs.clear();
        if (this->tmp != start_i) {
            this->prevs = vector<int>(this->n, -1);
            this->costs = vector<int>(this->n, limit);
            this->jumps = vector<int>(this->n, 1);
            this->que = priority_queue<Node, vector<Node>, greater<Node> >();
            this->costs[start_i] = 0;
            this->que.emplace(0, start_i);
        }
        this->tmp = start_i;
        int tp = -1;
        int tpcost = 1000000;
        while (!this->que.empty()) {
            const Node t = this->que.top();
            if (xgrid[t.index]) {
                this->xs.emplace_back(t.index);
                tpcost = min(t.cost, tpcost);
            }
            if (t.cost > tpcost) { break; }
            
            this->que.pop();
            for (auto&& i : this->edgecost[t.index]) {
                const int cost = this->costs[t.index] + i.second;
                if (cost < this->costs[i.first]) {
                    // const int d = prioritygrid[i.first/this->m][i.first%this->m];
                    if (i.second == 0) {
                        this->costs[i.first] = cost + (this->jumps[t.index] == 0 ? 0 : 1);
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 0;// jump
                        
                        this->que.emplace(cost + (this->jumps[t.index] == 0 ? 0 : 1), i.first);
                    } else {
                        this->costs[i.first] = cost;
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 1;// not jump
                        
                        this->que.emplace(cost, i.first);
                        
                    }
                }
            }
        }
        
        int bestcost = 1000000;
        for (auto&& i : this->xs) {
            int y = i / this->m;
            int x = i % this->m;
            if (this->costs[i] - prioritygrid[y][x] <= bestcost) {
                bestcost = this->costs[i] - prioritygrid[y][x];
                tp = i;
            }
        }
        
        
        if (tp > -1) {
            this->pathcost = this->costs[tp];
            int e = tp;
            while (e > -1) {
                this->path.emplace_back(e);
                e = this->prevs[e];
            }
            // this->path = this->path;
            reverse(this->path.begin(), this->path.end());
        } else {
            this->pathcost = -1;
        }
    }
    
    void calcPath2 (int start_i) {
        static const int limit = numeric_limits<int>::max();
        this->path.clear();
        //this->rpath.clear();
        this->xs.clear();
        if (this->tmp != start_i) {
            this->prevs = vector<int>(this->n, -1);
            this->costs = vector<int>(this->n, limit);
            this->jumps = vector<int>(this->n, 1);
            this->que = priority_queue<Node, vector<Node>, greater<Node> >();
            this->costs[start_i] = 0;
            this->que.emplace(0, start_i);
        }
        this->tmp = start_i;
        int tp = -1;
        int tpcost = 1000000;
        while (!this->que.empty()) {
            const Node t = this->que.top();
            if (xgrid[t.index]) {
                this->xs.emplace_back(t.index);
                tpcost = min(t.cost, tpcost);
            }
            if (t.cost > tpcost + 2) { break; }
            
            this->que.pop();
            for (auto&& i : this->edgecost[t.index]) {
                const int cost = this->costs[t.index] + i.second;
                if (cost < this->costs[i.first]) {
                    // const int d = prioritygrid[i.first/this->m][i.first%this->m];
                    if (i.second == 0) {
                        this->costs[i.first] = cost + (this->jumps[t.index] == 0 ? 0 : 1);
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 0;// jump
                        
                        this->que.emplace(cost + (this->jumps[t.index] == 0 ? 0 : 1), i.first);
                    } else {
                        this->costs[i.first] = cost;
                        this->prevs[i.first] = t.index;
                        this->jumps[i.first] = 1;// not jump
                        
                        this->que.emplace(cost, i.first);
                        
                    }
                }
            }
        }
        
        int bestcost = 1000000;
        for (auto&& i : this->xs) {
            int y = i / this->m;
            int x = i % this->m;
            int r = xrnd()%8 ==0 ? xrnd()%4 : 0;
            if (this->costs[i] - r <= bestcost) {
                bestcost = this->costs[i] - r;
                tp = i;
            }
        }
        
        
        if (tp > -1) {
            this->pathcost = this->costs[tp];
            int e = tp;
            while (e > -1) {
                this->path.emplace_back(e);
                e = this->prevs[e];
            }
            // this->path = this->path;
            reverse(this->path.begin(), this->path.end());
        } else {
            this->pathcost = -1;
        }
    }
};



class JumpAround {
public:
    // 0 Empty '.'
    // 1 targets 'X'
    // 2 pegs 'P'
    // 3 walls '#'
    // penalty N*2
    int N;// 5-50
    int P;// N*N/4
    StopWatch sw;
    
    vector<Edge> edges;
    
    unordered_set<e512pos> ps;
    unordered_set<e512pos> xs;
    
    int cnt = 0;
    
    int sscore = 0;
    vector< vector<int> > svret;
    
    vector<string> findSolution (int N, int NumPegs, char grid[]) {
        this->sw = StopWatch();
        this->N = N;
        this->P = NumPegs;
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                prioritygrid[y][x] = 0;
                if (grid[y*this->N+x] == '.') { rawgrid[y][x] = 0; }
                if (grid[y*this->N+x] == 'X') {
                    rawgrid[y][x] = 1;
                    this->xs.emplace(x, y);
                }
                if (grid[y*this->N+x] == 'P') {
                    rawgrid[y][x] = 2;
                    this->ps.emplace(x, y);
                }
                if (grid[y*this->N+x] == '#') { rawgrid[y][x] = 3; }
            }
        }
        
        
        static const int dx[4] = {0, 0, -1, 1};
        static const int dy[4] = {-1, 1, 0, 0};
        
        vector<e512pos> vps;
        vector<e512pos> bestvps;
        
        int score = 1000000;
        int bestscore = score;
        
        int ic = 0;
        vector< vector<int> > bestvret;
        for (auto&& i : ps) {
            vps.emplace_back(i);
            bestvret.emplace_back(vector<int>());
            vret[ic] = vector<int>();
            ic += 1;
        }
        bestvps = vps;
        
        for (int i = 0; i < 64; ++i) {
            mt19937 mt(xrnd());
            shuffle(vps.begin(), vps.end(), mt);
            test(score, vps, 0);
            // score = this->allScore(vret);
            if (score < bestscore) {
                bestvret.clear();
                for (int i = 0; i < this->P; ++i) { bestvret.emplace_back(vret[i]); }
                bestscore = score;
                bestvps = vps;
                for (int y = 0; y < this->N; ++y) {
                    for (int x = 0; x < this->N; ++x) {
                        if (tmpgrid[y][x] == 1) {
                            prioritygrid[y][x] = 4;
                        } else if (prioritygrid[y][x] > 0) {
                            prioritygrid[y][x] = 2;
                        }
                    }
                }
            }
            this->cnt += 1;
        }
        for (int i = 0; i < this->P; ++i) { vret[i] = bestvret[i]; }
        bestvret = this->SA(9800 - this->sw.get_milli_time(), bestvret, bestvps);
        
        pdebug(this->N, this->P, this->sw.get_milli_time(), this->cnt);
        return this->toRet(bestvret);
    }
    
    inline int toPInt (const e512pos& p) {
        return p.y * this->N + p.x;
    }
    
    
    void test (int& score, const vector<e512pos>& vps, int minc) {
        this->initTmpGrid();
        score = sscore;
        
        unordered_set<e512pos> xs = this->xs;
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (rawgrid[y][x] == 1) {
                    xgrid[y * this->N + x] = true;
                } else {
                    xgrid[y * this->N + x] = false;
                }
            }
        }
        
        this->gridToGraph();
        GraphDijkstra g(this->N, this->N*this->N, this->P, this->edges);
        int c = 0;
        int pcnt = this->P;
        
        for (; c < minc; ++c) {
            if (vret[c].size() > 1)  {
                const int& iep = vret[c].back();
                const e512pos ep(iep%this->N, iep/this->N);
                const int& isp = vret[c].front();
                const e512pos sp(isp%this->N, isp/this->N);
                xs.erase(ep);
                tmpgrid[sp.y][sp.x] = 0;
                tmpgrid[ep.y][ep.x] = 3;//
                xgrid[iep] = false;
                this->updateEdges(sp, ep);
                g.Update2(this->updates, this->uedges, pcnt);
                
                score += scores[c];
                pcnt -= 1;
            }
        }
        
        for (; c < this->P; ++c) {
            const e512pos& i = vps[c];
            g.calcPath(i.y*this->N+i.x);
            if (g.path.size() > 1) {
                vret[c] = g.path;
                const int& iep = vret[c].back();
                const e512pos ep(iep%this->N, iep/this->N);
                const int& isp = vret[c].front();
                const e512pos sp(isp%this->N, isp/this->N);
                xs.erase(ep);
                xgrid[iep] = false;
                tmpgrid[sp.y][sp.x] = 0;
                tmpgrid[ep.y][ep.x] = 3;//
                
                score += g.pathcost;
                scores[c] = g.pathcost;
                pcnt -= 1;
                
                this->updateEdges(sp, ep);
                g.Update2(this->updates, this->uedges, pcnt);
            } else {
                vret[c] = vector<int>();
                scores[c] = 0;
            }
        }
        // this->fprintTmpGrid();
        // fdebug("-");
        score += pcnt * (this->N * 2);
    }
    
    void test2 (int& score, const vector<e512pos>& vps, int minc) {
        this->initTmpGrid();
        score = sscore;
        
        unordered_set<e512pos> xs = this->xs;
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (rawgrid[y][x] == 1) {
                    xgrid[y * this->N + x] = true;
                } else {
                    xgrid[y * this->N + x] = false;
                }
            }
        }
        
        this->gridToGraph();
        GraphDijkstra g(this->N, this->N*this->N, this->P, this->edges);
        int c = 0;
        int pcnt = this->P;
        
        for (; c < minc; ++c) {
            if (vret[c].size() > 1)  {
                const int& iep = vret[c].back();
                const e512pos ep(iep%this->N, iep/this->N);
                const int& isp = vret[c].front();
                const e512pos sp(isp%this->N, isp/this->N);
                xs.erase(ep);
                tmpgrid[sp.y][sp.x] = 0;
                tmpgrid[ep.y][ep.x] = 3;//
                xgrid[iep] = false;
                this->updateEdges(sp, ep);
                g.Update2(this->updates, this->uedges, pcnt);
                
                score += scores[c];
                pcnt -= 1;
            }
        }
        
        for (; c < this->P; ++c) {
            const e512pos& i = vps[c];
            g.calcPath2(i.y*this->N+i.x);
            if (g.path.size() > 1) {
                vret[c] = g.path;
                const int& iep = vret[c].back();
                const e512pos ep(iep%this->N, iep/this->N);
                const int& isp = vret[c].front();
                const e512pos sp(isp%this->N, isp/this->N);
                xs.erase(ep);
                xgrid[iep] = false;
                tmpgrid[sp.y][sp.x] = 0;
                tmpgrid[ep.y][ep.x] = 3;//
                
                score += g.pathcost;
                scores[c] = g.pathcost;
                pcnt -= 1;
                
                this->updateEdges(sp, ep);
                g.Update2(this->updates, this->uedges, pcnt);
            } else {
                vret[c] = vector<int>();
                scores[c] = 0;
            }
        }
        // this->fprintTmpGrid();
        // fdebug("-");
        score += pcnt * (this->N * 2);
    }
    
    vector< vector<int> > SA (int limit, vector< vector<int> > ret, vector<e512pos>& vps) {
        StopWatch sw;
        vector<e512pos> bestvps = vps;
        vector< vector<int> > bestret;
        for (int i = 0; i < this->P; ++i) { bestret.emplace_back(vret[i]); }
        
        double bestscore = 1000000;
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        double startTemp = 2;
        int ot = saTimeEnd/8;
        int det = this->N * this->P < 30 * 300 ? saTimeEnd/10 : 0;
        
        for (int i = 0; i < this->P; ++i) { tvret[i] = vret[i]; }
        int score;
        test(score, vps, 0);
        
        while ((saTimeCurrent = sw.get_milli_time()) < ot) {
            int a = xrnd() % this->P;
            int b = xrnd() % this->P;
            int c = xrnd() % this->P;
            int d = xrnd() % this->P;
            if (a == b && c == d) { continue; }
            swap(vps[a], vps[b]);
            swap(vps[c], vps[d]);
            
            test(score, vps, min(min(a, b), min(c, d)));
            // test(score, vps, min(a, b));
            
            double tmpscore = score;
            
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            
            const double endTemp     = 0.0;
            const double temp        = startTemp + (endTemp - startTemp) * t / T;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestret.clear();
                    for (int i = 0; i < this->P; ++i) { bestret.emplace_back(vret[i]); }
                    bestvps = vps;
                }
                for (int i = 0; i < this->P; ++i) {
                    tvret[i] = vret[i];
                    tscores[i] = scores[i];
                }
            } else {
                swap(vps[c], vps[d]);
                swap(vps[a], vps[b]);
                for (int i = 0; i < this->P; ++i) {
                    vret[i] = tvret[i];
                    scores[i] = tscores[i];
                }
            }
            this->cnt += 1;
        }
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd - det) {
        
            int a = xrnd() % this->P;
            int b = xrnd() % this->P;
            // int c = qp + xrnd() % mqp;
            // int d = qp + xrnd() % mqp;
            if (a == b) { continue; }
            // if (a == b && c == d) { continue; }
            swap(vps[a], vps[b]);
            // swap(vps[c], vps[d]);
            
            // test(score, vps, min(min(a, b), min(c, d)));
            test(score, vps, min(a, b));
            
            double tmpscore = score;
            
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            
            const double endTemp     = 0.0;
            const double temp        = startTemp + (endTemp - startTemp) * t / T;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestret.clear();
                    for (int i = 0; i < this->P; ++i) { bestret.emplace_back(vret[i]); }
                    bestvps = vps;
                }
                for (int i = 0; i < this->P; ++i) {
                    tvret[i] = vret[i];
                    tscores[i] = scores[i];
                }
            } else {
                // swap(vps[c], vps[d]);
                swap(vps[a], vps[b]);
                for (int i = 0; i < this->P; ++i) {
                    vret[i] = tvret[i];
                    scores[i] = tscores[i];
                }
            }
            this->cnt += 1;
        }
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            int a = xrnd() % this->P;
            int b = xrnd() % this->P;
            if (a == b) { continue; }
            swap(vps[a], vps[b]);
            
            test2(score, vps, min(a, b));
            
            double tmpscore = score;
            
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            
            const double endTemp     = 0.0;
            const double temp        = startTemp + (endTemp - startTemp) * t / T;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestret.clear();
                    for (int i = 0; i < this->P; ++i) { bestret.emplace_back(vret[i]); }
                    bestvps = vps;
                }
                for (int i = 0; i < this->P; ++i) {
                    tvret[i] = vret[i];
                    tscores[i] = scores[i];
                }
            } else {
                swap(vps[a], vps[b]);
                for (int i = 0; i < this->P; ++i) {
                    vret[i] = tvret[i];
                    scores[i] = tscores[i];
                }
            }
            this->cnt += 1;
            
        }
        vps = bestvps;
        return bestret;
    }
    
    
    
    void fprintTmpGrid () {
        for (int y = 0; y < this->N; ++y) {
            vector<int> v;
            for (int x = 0; x < this->N; ++x) {
                v.emplace_back(tmpgrid[y][x]);
            }
            fdebug(v);
        }
    }
    
    vector<string> toRet (vector< vector<int> > vret) {
        vector<string> ret;
        for (auto&& i : vret) {
            if (i.size() < 2) { continue; }
            e512pos p(i.front()%this->N, i.front()/this->N);
            e512pos jp = p;
            
            string tmpj = "";
            for (int j = 1; j < i.size(); ++j) {
                const e512pos tp(i[j]%this->N, i[j]/this->N);
                bool isj = abs(tp.y-p.y) + abs(tp.x-p.x) > 1;
                string dir = "";
                if (tp.y < p.y) { dir = "U"; }
                if (tp.y > p.y) { dir = "D"; }
                if (tp.x < p.x) { dir = "L"; }
                if (tp.x > p.x) { dir = "R"; }
                
                if (isj) {
                    if (tmpj == "") { jp = p; }
                    tmpj += dir;
                }
                
                if ((j == i.size()-1 || !isj) && tmpj.size() > 0) {
                    ret.emplace_back(print(jp.y, jp.x, "J", tmpj));
                    tmpj = "";
                }
                if (!isj) {
                    ret.emplace_back(print(p.y, p.x, "S", dir));
                }
                p = tp;
            }
        }
        return ret;
    }
    
    
    int pathScore (vector<int> v) {
        int score = 0;
        if (v.size() < 2) { return -1; }
        e512pos p = e512pos(v[0]%this->N, v[0]/this->N);
        e512pos jp = p;
        
        int tmpj = 0;
        for (int j = 1; j < v.size(); ++j) {
            const e512pos tp(v[j]%this->N, v[j]/this->N);
            bool isj = abs(tp.y-p.y) + abs(tp.x-p.x) > 1;
            
            if (isj) {
                if (tmpj == 0) { jp = p; }
                tmpj += 1;
            }
            if ((j == v.size()-1 || !isj) && tmpj > 0) {
                score += 1;
                tmpj = 0;
            }
            if (!isj) { score += 1; }
            p = tp;
        }
        
        return score;
    }
    
    
    inline void initTmpGrid () {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                tmpgrid[y][x] = rawgrid[y][x];
            }
        }
    }
    
    void gridToGraph () {
        static const int dx[4] = {0, 0, -1, 1};
        static const int dy[4] = {-1, 1, 0, 0};
        this->edges.clear();
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (tmpgrid[y][x] == 3) { continue; }
                for (int i = 0; i < 4; ++i) {
                    
                    int bx = x + dx[i];
                    int by = y + dy[i];
                    if (bx < 0 || bx >= this->N || by < 0 || by >= this->N) { continue; }
                    if (tmpgrid[by][bx] < 2) {
                        this->edges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 1));
                    } else {
                        bx = bx + dx[i];
                        by = by + dy[i];
                        if (bx < 0 || bx >= this->N || by < 0 || by >= this->N || tmpgrid[by][bx] > 1) { continue; }
                        this->edges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 0));
                    }
                }
            }
        }
    }
    
    
    
    vector<Edge> uedges;
    unordered_set<int> updates;
    void updateEdges (const e512pos& s, const e512pos& e) {
        static const int dx[4] = {0, 0, -1, 1};
        static const int dy[4] = {-1, 1, 0, 0};
        static const int ux[9] = {0, 0, 0, -1, 1, 0, 0, -2, 2};
        static const int uy[9] = {0, -1, 1, 0, 0, -2, 2, 0, 0};
        this->uedges.clear();
        this->updates.clear();
        for (int i = 0; i < 9; ++i) {
            int x = s.x + ux[i];
            int y = s.y + uy[i];
            if (x < 0 || x >= this->N || y < 0 || y >= this->N) { continue; }
            this->updates.emplace(y*this->N+x);
            if (tmpgrid[y][x] == 3) { continue; }
            
            for (int i = 0; i < 4; ++i) {
                int bx = x + dx[i];
                int by = y + dy[i];
                if (bx < 0 || bx >= this->N || by < 0 || by >= this->N) { continue; }
                if (tmpgrid[by][bx] < 2) {
                    this->uedges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 1));
                } else {
                    bx = bx + dx[i];
                    by = by + dy[i];
                    if (bx < 0 || bx >= this->N || by < 0 || by >= this->N || tmpgrid[by][bx] > 1) { continue; }
                    this->uedges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 0));
                }
            }
        }
        for (int i = 0; i < 9; ++i) {
            int x = e.x + ux[i];
            int y = e.y + uy[i];
            if (x < 0 || x >= this->N || y < 0 || y >= this->N) { continue; }
            
            if (this->updates.find(y*this->N+x) != this->updates.end()) { continue; }
            this->updates.emplace(y*this->N+x);
            if (tmpgrid[y][x] == 3) { continue; }
            for (int i = 0; i < 4; ++i) {
                int bx = x + dx[i];
                int by = y + dy[i];
                if (bx < 0 || bx >= this->N || by < 0 || by >= this->N) { continue; }
                if (tmpgrid[by][bx] < 2) {
                    this->uedges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 1));
                } else {
                    bx = bx + dx[i];
                    by = by + dy[i];
                    if (bx < 0 || bx >= this->N || by < 0 || by >= this->N || tmpgrid[by][bx] > 1) { continue; }
                    this->uedges.emplace_back(Edge(y*this->N+x, by*this->N+bx, 0));
                }
            }
        }
        
    }
};

int main() {
    JumpAround ja;
    int N;
    int NumPegs;
    cin >> N;
    cin >> NumPegs;
    
    char grid[N*N];
    for (int i=0; i<N*N; i++) { cin >> grid[i]; }

    vector<string> ret = ja.findSolution(N,NumPegs,grid);
    cerr.flush();
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) { cout << ret[i] << endl; }
    cout.flush();
}