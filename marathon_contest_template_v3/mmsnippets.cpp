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



// #include <time.h>
// #include <sys/timeb.h>
// class StopWatch {
// public:
//     int starts;
//     int startm;
//     int tstarts = 0;
//     int tstartm = 0;
//     struct timeb timebuffer;
//     StopWatch () {
//         ftime(&this->timebuffer);
//         this->starts = this->timebuffer.time;
//         this->startm = this->timebuffer.millitm;
//     }
//     inline void stop () {
//         ftime(&this->timebuffer);
//         this->tstarts = this->timebuffer.time;
//         this->tstartm = this->timebuffer.millitm;
//     }
//     inline void resume () {
//         ftime(&this->timebuffer);
//         this->starts += this->timebuffer.time - this->tstarts;
//         this->startm += this->timebuffer.millitm - this->tstartm;
//     }
//     inline int get_milli_time () {
//         ftime(&this->timebuffer);
//         return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
//     }
// };

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
    vector<int> path;
    vector<int> rpath;
    int pathcost;
    
    GraphDijkstra () {}
    
    GraphDijkstra (int n, vector<Edge>& edges, bool undir = false) {
        this->pathcost = 0;
        this->path.clear();
        this->n = n;
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
    
    GraphDijkstra (vector<Edge>& edges, bool undir = false) {
        this->pathcost = 0;
        this->path.clear();
        int n = 0;
        for (auto&& i : edges) { n = max(max(i.a, i.b), n); }
        this->n = n+1;
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
    
    void costUpdate (vector<Edge>& edges, bool undir = false) {
        for (auto&& i : this->edgecost) { i.clear(); }
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
    
    
    void calcPath (int start_i, int end_i) {
        static const int limit = numeric_limits<int>::max();
        this->path.clear();
        this->rpath.clear();
        if (this->tmp != start_i) {
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
                this->rpath.emplace_back(e);
                e = this->prevs[e];
            }
            this->path = this->rpath;
            reverse(this->path.begin(), this->path.end());
        } else {
            this->pathcost = -1;
        }
    }
};

struct E512Grid {
    vector<int> grid;
    int W, H;
    E512Grid () {}
    E512Grid (int W, int H) { this->init(W, H); }
    E512Grid (int N) { this->init(N, N); }
    void init (int W, int H) {
        this->W = W;
        this->H = H;
        this->grid = vector<int>(this->W*this->H, 0);
    }
    int getIndex (int x, int y) { return y*this->W+x; }
    int getValue (int x, int y) { return this->grid[y*this->W+x]; }
    void setValue (int x, int y, int value) { this->grid[y*this->W+x] = value; }
    bool inSide (int x, int y) { return (x >= 0 && x < this->W && y >= 0 && y < this->H); }
    void input () {
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                cin >> this->grid[y*this->W+x];
            }
        }
    }
    void inputNoSplit () {
        for (int y = 0; y < this->H; ++y) {
            string t;
            cin >> t;
            for (int x = 0; x < this->W; ++x) {
                this->grid[y*this->W+x] = (int)(t[x]-'0');
            }
        }
    }
    void randomFill (int minvalue, int maxvalue) {
        int d = abs(maxvalue-minvalue)+1;
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                this->grid[y*this->W+x] = xrnd()%d+minvalue;
            }
        }
    }
    string toStringNoSplit () {
        string r;
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                r += to_string(this->grid[y*this->W+x]);
            }
            if (y != this->H-1) { r += '\n'; }
        }
        return r;
    }
    string toStringPathGridNoSplit (vector<int>& path) {
        string r;
        vector<int> m = vector<int>(this->grid.size(), 0);
        for (auto&& i : path) { m[i] = 1; }
        
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                r += m[y*this->W+x] == 1 ? '+' : '.';
            }
            if (y != this->H-1) { r += '\n'; }
        }
        return r;
    }
    string toStringPathGridNoSplit (vector<int>& path, int wall) {
        string r;
        vector<int> m = vector<int>(this->grid.size(), 0);
        for (auto&& i : path) { m[i] = 1; }
        
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                r += (this->grid[y*this->W+x] == wall ? '#' : (m[y*this->W+x] == 1 ? '+' : '.'));
            }
            if (y != this->H-1) { r += '\n'; }
        }
        return r;
    }
    
    string toStringWallGrid (E512Grid& horizontal, E512Grid& vertical) {
        vector< vector<char> > g = vector< vector<char> >(this->H, vector<char>(this->W*2-1, ' '));
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W-1; ++x) {
                if (horizontal.getValue(x, y) == 1) { g[y][x*2+1] = '|'; }
            }
        }
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                if (vertical.getValue(x, y) == 1) { g[y][x*2] = '_'; }
            }
        }
        string r;
        for (int x = 0; x < this->W*2+1; ++x) { r += '#'; }
        r += '\n';
        for (int y = 0; y < this->H; ++y) {
            r += '#';
            for (int x = 0; x < this->W*2-1; ++x) {
                r += g[y][x];
            }
            r += "#\n";
        }
        for (int x = 0; x < this->W*2+1; ++x) { r += '#'; }
        return r;
    }
    
};
ostream& operator << (ostream& os, const E512Grid& p) {
    for (int y = 0; y < p.H; ++y) {
        for (int x = 0; x < p.W; ++x) {
            os << to_string(p.grid[y*p.W+x]);
            if (x != p.W-1) { os << ' '; }
        }
        if (y != p.H-1) { os << '\n'; }
    }
    return os;
};

struct E512GridUtils {
    static vector<int> findValueIndexes (E512Grid& g, int target) {
        vector<int> r;
        for (int i = 0; i < g.grid.size(); ++i) {
            if (g.grid[i] == target) { r.emplace_back(i); }
        }
        return r;
    }
    
    // Direction
    static vector<Edge> getEdges (E512Grid& g) {
        vector<Edge> e;
        for (int y = 0; y < g.H; ++y) {
            for (int x = 0; x < g.W; ++x) {
                int a = y*g.W+x;
                if (y-1 >=  0) { e.emplace_back(a, (y-1)*g.W+x, 1); }
                if (x+1 < g.W) { e.emplace_back(a, y*g.W+(x+1), 1); }
                if (y+1 < g.H) { e.emplace_back(a, (y+1)*g.W+x, 1); }
                if (x-1 >=  0) { e.emplace_back(a, y*g.W+(x-1), 1); }
            }
        }
        return e;
    }
    static vector<Edge> getEdges (E512Grid& g, int wall) {
        vector<Edge> e;
        for (int y = 0; y < g.H; ++y) {
            for (int x = 0; x < g.W; ++x) {
                int a = y*g.W+x;
                int b;
                if (y-1 >=  0) { b = (y-1)*g.W+x; if (g.grid[a] != wall && g.grid[b] != wall) { e.emplace_back(a, b, 1); } }
                if (x+1 < g.W) { b = y*g.W+(x+1); if (g.grid[a] != wall && g.grid[b] != wall) { e.emplace_back(a, b, 1); } }
                if (y+1 < g.H) { b = (y+1)*g.W+x; if (g.grid[a] != wall && g.grid[b] != wall) { e.emplace_back(a, b, 1); } }
                if (x-1 >=  0) { b = y*g.W+(x-1); if (g.grid[a] != wall && g.grid[b] != wall) { e.emplace_back(a, b, 1); } }
            }
        }
        return e;
    }
    static vector<Edge> getEdges (E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        vector<Edge> e;
        for (int y = 0; y < g.H; ++y) {
            for (int x = 0; x < g.W; ++x) {
                int a = y*g.W+x;
                if (y-1 >=  0 &&   vertical.getValue(x, y-1) == 0) { e.emplace_back(a, (y-1)*g.W+x, 1); }
                if (x+1 < g.W &&   horizontal.getValue(x, y) == 0) { e.emplace_back(a, y*g.W+(x+1), 1); }
                if (y+1 < g.H &&     vertical.getValue(x, y) == 0) { e.emplace_back(a, (y+1)*g.W+x, 1); }
                if (x-1 >=  0 && horizontal.getValue(x-1, y) == 0) { e.emplace_back(a, y*g.W+(x-1), 1); }
            }
        }
        return e;
    }
    
    static void setEdgeCost (E512Grid& g, vector<Edge>& e) {
        for (auto&& i : e) { i.cost = g.grid[i.b]; }
    }
    
    static vector<Edge> getCostEdges (E512Grid& g) {
        vector<Edge> e = E512GridUtils::getEdges(g);
        E512GridUtils::setEdgeCost(g, e);
        return e;
    }
    static vector<Edge> getCostEdges (E512Grid& g, int wall) {
        vector<Edge> e = E512GridUtils::getEdges(g, wall);
        E512GridUtils::setEdgeCost(g, e);
        return e;
    }
    static vector<Edge> getCostEdges (E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        vector<Edge> e = E512GridUtils::getEdges(g, horizontal, vertical);
        E512GridUtils::setEdgeCost(g, e);
        return e;
    }
    
    static vector< vector<int> > getCostMatrix (E512Grid& g) {
        int n = g.W * g.H;
        vector< vector<int> > mat = vector< vector<int> >(n, vector<int>(n));
        vector<Edge> e = E512GridUtils::getEdges(g);
        GraphDijkstra d(e);
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                d.calcPath(a, b);
                mat[a][b] = d.pathcost;
                mat[b][a] = d.pathcost;
            }
        }
        return mat;
    }
    static vector< vector<int> > getCostMatrix (E512Grid& g, int wall) {
        int n = g.W * g.H;
        vector< vector<int> > mat = vector< vector<int> >(n, vector<int>(n));
        vector<Edge> e = E512GridUtils::getEdges(g, wall);
        GraphDijkstra d(e);
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                d.calcPath(a, b);
                mat[a][b] = d.pathcost;
                mat[b][a] = d.pathcost;
            }
        }
        return mat;
    }
    static vector< vector<int> > getCostMatrix (E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        int n = g.W * g.H;
        vector< vector<int> > mat = vector< vector<int> >(n, vector<int>(n));
        vector<Edge> e = E512GridUtils::getEdges(g, horizontal, vertical);
        GraphDijkstra d(e);
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                d.calcPath(a, b);
                mat[a][b] = d.pathcost;
                mat[b][a] = d.pathcost;
            }
        }
        return mat;
    }
    
    static vector< vector<int> > getVertEdges (E512Grid& g) {
        vector<Edge> e = E512GridUtils::getEdges(g);
        vector< vector<int> > r = vector< vector<int> >(g.W*g.H, vector<int>());
        for (auto&& i : e) { r[i.a].emplace_back(i.b); }
        return r;
    }
    static vector< vector<int> > getVertEdges (E512Grid& g, int wall) {
        vector<Edge> e = E512GridUtils::getEdges(g, wall);
        vector< vector<int> > r = vector< vector<int> >(g.W*g.H, vector<int>());
        for (auto&& i : e) { r[i.a].emplace_back(i.b); }
        return r;
    }
    static vector< vector<int> > getVertEdges (E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        vector<Edge> e = E512GridUtils::getEdges(g, horizontal, vertical);
        vector< vector<int> > r = vector< vector<int> >(g.W*g.H, vector<int>());
        for (auto&& i : e) { r[i.a].emplace_back(i.b); }
        return r;
    }
    
    static vector<Edge> toUnDirection (E512Grid& g, vector<Edge>& e) {
        vector<Edge> r;
        unordered_set<e512pos> us;
        for (auto&& i : e) {
            int a = i.a;
            int b = i.b;
            if (a > b) { swap(a, b); }
            if (us.find(e512pos(a, b)) == us.end()) {
                r.emplace_back(a, b, 1);
                us.emplace(e512pos(a, b));
            }
        }
        return r;
    }
    
    static void rotateRight (E512Grid& g) {
        if (g.W != g.H) { return; }
        int n = g.W;
        vector<int> v = g.grid;
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                int rx = n-1-y;
                int ry = x;
                g.grid[ry*n+rx] = v[y*n+x];
            }
        }
    }
    static void rotateLeft (E512Grid& g) {
        if (g.W != g.H) { return; }
        int n = g.W;
        vector<int> v = g.grid;
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                int rx = y;
                int ry = n-1-x;
                g.grid[ry*n+rx] = v[y*n+x];
            }
        }
    }
    
    static void dropDown (E512Grid& g, int ignore = 0) {
        for (int x = 0; x < g.W; ++x) {
            int d = g.H-1;
            for (int y = 0; y < g.H; ++y) {
                if (g.grid[(g.H-y-1)*g.W+x] == ignore) {
                } else {
                    swap(g.grid[(g.H-y-1)*g.W+x], g.grid[d*g.W+x]);
                    d -= 1;
                }
            }
        }
    }
    
    static bool canMove (int ax, int ay, int bx, int by, E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        if (!g.inSide(bx, by)) { return false; }
        if (by < ay) { return (  vertical.getValue(bx, by) == 0); }
        if (bx > ax) { return (horizontal.getValue(ax, by) == 0); }
        if (by > ay) { return (  vertical.getValue(bx, ay) == 0); }
        if (bx < ax) { return (horizontal.getValue(bx, by) == 0); }
        return true;
    }
    
    static vector<int> group (E512Grid& g, int x, int y) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        static vector<e512pos> v;
        
        vector<int> e = vector<int>(g.grid.size(), 0);
        vector< vector<int> > r;
        
        int a = g.getIndex(x, y);
        e[a] = 1;
        vector<int> u;
        u.emplace_back(a);
        v.clear();
        v.emplace_back(x, y);
        while (v.size() > 0) {
            e512pos p = v.back();
            v.pop_back();
            for (int d = 0; d < 4; ++d) {
                int nx = p.x + dx[d];
                int ny = p.y + dy[d];
                int b = g.getIndex(nx, ny);
                if (!g.inSide(nx, ny)) { continue; }
                if (g.grid[b] != g.grid[a]) { continue; }
                if (e[b] == 1) { continue; }
                e[b] = 1;
                u.emplace_back(b);
                v.emplace_back(nx, ny);
            }
        }
        return u;
    }
    static vector< vector<int> > groupLists (E512Grid& g) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        static vector<e512pos> v;
        
        vector<int> e = vector<int>(g.grid.size(), 0);
        vector< vector<int> > r;
        for (int y = 0; y < g.H; ++y) {
            for (int x = 0; x < g.W; ++x) {
                int a = g.getIndex(x, y);
                if (e[a] == 1) { continue; }
                e[a] = 1;
                vector<int> u;
                u.emplace_back(a);
                v.clear();
                v.emplace_back(x, y);
                while (v.size() > 0) {
                    e512pos p = v.back();
                    v.pop_back();
                    for (int d = 0; d < 4; ++d) {
                        int nx = p.x + dx[d];
                        int ny = p.y + dy[d];
                        int b = g.getIndex(nx, ny);
                        if (!g.inSide(nx, ny)) { continue; }
                        if (g.grid[b] != g.grid[a]) { continue; }
                        if (e[b] == 1) { continue; }
                        e[b] = 1;
                        u.emplace_back(b);
                        v.emplace_back(nx, ny);
                    }
                }
                r.emplace_back(u);
            }
        }
        return r;
    }
    
    static vector<int> group (E512Grid& g, int x, int y, E512Grid& horizontal, E512Grid& vertical) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        static vector<e512pos> v;
        
        vector<int> e = vector<int>(g.grid.size(), 0);
        vector< vector<int> > r;
        
        int a = g.getIndex(x, y);
        e[a] = 1;
        vector<int> u;
        u.emplace_back(a);
        v.clear();
        v.emplace_back(x, y);
        while (v.size() > 0) {
            e512pos p = v.back();
            v.pop_back();
            for (int d = 0; d < 4; ++d) {
                int nx = p.x + dx[d];
                int ny = p.y + dy[d];
                int b = g.getIndex(nx, ny);
                if (!E512GridUtils::canMove(p.x, p.y, nx, ny, g, horizontal, vertical)) { continue; }
                if (g.grid[b] != g.grid[a]) { continue; }
                if (e[b] == 1) { continue; }
                e[b] = 1;
                u.emplace_back(b);
                v.emplace_back(nx, ny);
            }
        }
        return u;
    }
    static vector< vector<int> > groupLists (E512Grid& g, E512Grid& horizontal, E512Grid& vertical) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {-1, 0, 1, 0};
        static vector<e512pos> v;
        
        vector<int> e = vector<int>(g.grid.size(), 0);
        vector< vector<int> > r;
        for (int y = 0; y < g.H; ++y) {
            for (int x = 0; x < g.W; ++x) {
                int a = g.getIndex(x, y);
                if (e[a] == 1) { continue; }
                e[a] = 1;
                vector<int> u;
                u.emplace_back(a);
                v.clear();
                v.emplace_back(x, y);
                while (v.size() > 0) {
                    e512pos p = v.back();
                    v.pop_back();
                    for (int d = 0; d < 4; ++d) {
                        int nx = p.x + dx[d];
                        int ny = p.y + dy[d];
                        int b = g.getIndex(nx, ny);
                        if (!E512GridUtils::canMove(p.x, p.y, nx, ny, g, horizontal, vertical)) { continue; }
                        if (g.grid[b] != g.grid[a]) { continue; }
                        if (e[b] == 1) { continue; }
                        e[b] = 1;
                        u.emplace_back(b);
                        v.emplace_back(nx, ny);
                    }
                }
                r.emplace_back(u);
            }
        }
        return r;
    }
    
    static vector<int> withinRangeVertices (int startindex, int range, vector< vector< int > >& vertedges, int verticescnt = 10000) {
        static array<int, 10000> visited;
        static int bfscnt = 0;
        if (bfscnt == 0 || bfscnt > 1000000) { for (int i = 0; i < verticescnt; ++i) { visited[i] = 0; } }
        bfscnt += 1;
        static vector<int> q;
        q.clear();
        q.emplace_back(startindex);
        visited[startindex] = bfscnt;
        int qcnt = 0;
        int tqcnt = 0;
        for (int z = 0; z < range; ++z) {
            tqcnt = q.size();
            for (int i = qcnt; i < tqcnt; ++i) {
                for (auto&& j : vertedges[q[i]]) {
                    if (visited[j] < bfscnt) {
                        q.emplace_back(j);
                        visited[j] = bfscnt;
                    }
                }
            }
            qcnt = tqcnt;
        }
        return q;
    }
    static vector< vector<int> > withinRangeVerticesDist (int startindex, int range, vector< vector< int > >& vertedges, int verticescnt = 10000) {
        static array<int, 10000> visited;
        static int bfscnt = 0;
        if (bfscnt == 0 || bfscnt > 1000000) { for (int i = 0; i < verticescnt; ++i) { visited[i] = 0; } }
        bfscnt += 1;
        static vector<int> q, t;
        static vector< vector<int> > r;
        q.clear();
        r.clear();
        q.emplace_back(startindex);
        t.clear();
        t.emplace_back(startindex);
        r.emplace_back(t);
        visited[startindex] = bfscnt;
        int qcnt = 0;
        int tqcnt = 0;
        for (int z = 0; z < range; ++z) {
            tqcnt = q.size();
            for (int i = qcnt; i < tqcnt; ++i) {
                for (auto&& j : vertedges[q[i]]) {
                    if (visited[j] < bfscnt) {
                        q.emplace_back(j);
                        visited[j] = bfscnt;
                    }
                }
            }
            t.clear();
            for (int i = qcnt; i < q.size(); ++i) { t.emplace_back(q[i]); }
            r.emplace_back(t);
            qcnt = tqcnt;
        }
        return r;
    }
};

vector<Edge> minimumSpanningTree (vector<Edge> e, bool undir=true) {
    static bitset<4096> v;
    vector<Edge> r;
    if (e.size() == 0) { return r; }
    sort(e.begin(), e.end(), [](const Edge& a, const Edge& b) { return a.cost < b.cost; });
    v.reset();
    for (auto&& i : e) { v[i.a]=true; v[i.b]=true; }
    int t = e[0].a;
    v[t] = false;
    bool f = true;
    if (undir) {
        while (v.count() > 0 && f) {
            f = false;
            for (auto&& i : e) {
                if (v[i.a] == false && v[i.b] == true) {
                    v[i.b] = false;
                    r.emplace_back(i);
                    f = true;
                    break;
                }
                if (v[i.b] == false && v[i.a] == true) {
                    v[i.a] = false;
                    r.emplace_back(i);
                    f = true;
                    break;
                }
            }
        }
    } else {
        while (v.count() > 0 && f) {
            f = false;
            for (auto&& i : e) {
                if (v[i.a] == false && v[i.b] == true) {
                    v[i.b] = false;
                    r.emplace_back(i);
                    f = true;
                    break;
                }
            }
        }
    }
    return r;
}



vector<int> kMeansCenter (vector<int>& r, int k, vector< vector<int> >& mat) {
    vector<int> b(k, -1);
    vector<int> s(k, 1000000);
    for (int i = 0; i < mat.size(); ++i) {
        if (r[i] < 0) { continue; } 
        int t = 0;
        for (int j = 0; j < mat.size(); ++j) {
            if (r[i] == r[j] && mat[i][j] >= 0) { t += mat[i][j]; }
        }
        if (t < s[r[i]]) {
            b[r[i]] = i;
            s[r[i]] = t;
        }
    }
    return b;
}

vector<int> kMeansInit (int k, vector< vector<int> >& mat, bool obstacles) {
    vector<int> r(mat.size(), -1);
    for (auto&& i : r) { i = xrnd()%k; }
    if (obstacles) {
        for (int i = 0; i < mat.size(); ++i) {
            int c = 1;
            for (int j = 0; j < mat.size(); ++j) { c += mat[i][j] < 0; }
            if (c >= mat.size()) { r[i] = -1; }
        }
    }
    return r;
}

void kMeans (vector<int>& r, int k, vector< vector<int> >& mat) {
    vector<int> center = kMeansCenter(r, k, mat);
    for (int i = 0; i < mat.size(); ++i) {
        int best = 1000000;
        int bestindex = -1;
        if (r[i] < 0) { continue; }
        for (int j = 0; j < k; ++j) {
            if (center[j] < 0) { continue; }
            int d = mat[center[j]][i];
            if (d < best && d >= 0) {
                best = d;
                bestindex = j;
            }
        }
        r[i] = bestindex;
    }
}

// connected graph cost matrix, excluding obstacles
vector<int> kMeans (int k, vector< vector<int> >& mat, uint32_t iter=6, bool obstacles=true) {
    vector<int> r = kMeansInit(k, mat, obstacles);
    for (int z = 0; z < iter; ++z) {
        vector<int> center = kMeansCenter(r, k, mat);
        kMeans(r, k, mat);
    }
    return r;
}



inline double distance (const double& ax, const double& ay, const double& bx, const double& by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline double distance (const int& ax, const int& ay, const int& bx, const int& by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline float distance (const e512pos& a, const e512pos& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}

// SA
template<class T>
double calcscore (T v) { return 0; }

template<class T>
class Random2optSwap {
public:
    int a, b;
    Random2optSwap (T& v, int l, int r) {// left margin size   right margin size
        int t = max(((int)v.size() - l - r), 1);
        this->a = xrnd() % t + l;
        this->b = xrnd() % t + l;
        if (this->a > this->b) { swap(this->a, this->b); }
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
    void cancel (T& v) {
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
};

template<class T>
T maximize_sa (T v, double& refscore, int etime, double stemp = 256.0, double etemp = 0.0) {
    StopWatch sw;
    int stime = 0;
    const double satime = etime - stime;
    int ntime = stime;
    T bestv = v;
    double bestscore = calcscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    int cnt = 0;
    while (true) {
        ntime = sw.get_milli_time();
        if (ntime >= etime) { break; }
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
        const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
        const double probability = exp((tmpscore - lastscore) / temp);
        const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
        if (tmpscore > lastscore || FORCE_NEXT) {
            lastscore = tmpscore;
            if (tmpscore > bestscore) {
                bestscore = tmpscore;
                bestv = v;
            }
        } else {
            swap(v[a], v[b]);
        }
        cnt += 1;
    }
    refscore = bestscore;
    return bestv;
}

template<class T>
T maximize_sa_fixedstep (T v, double& refscore, int ecnt, double stemp = 256.0, double etemp = 0.0) {
    const double sacnt = ecnt;
    T bestv = v;
    double bestscore = calcscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
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
            swap(v[a], v[b]);
        }
    }
    refscore = bestscore;
    return bestv;
}

template<class T>
T minimize_sa (T v, double& refscore, int etime, double stemp = 256.0, double etemp = 0.0) {
    StopWatch sw;
    int stime = 0;
    const double satime = etime - stime;
    int ntime = stime;
    T bestv = v;
    double bestscore = calcscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    int cnt = 0;
    while (true) {
        ntime = sw.get_milli_time();
        if (ntime >= etime) { break; }
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
        const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
        const double probability = exp((lastscore - tmpscore) / temp);
        const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
        if (tmpscore < lastscore || FORCE_NEXT) {
            lastscore = tmpscore;
            if (tmpscore < bestscore) {
                bestscore = tmpscore;
                bestv = v;
            }
        } else {
            swap(v[a], v[b]);
        }
        cnt += 1;
    }
    refscore = bestscore;
    return bestv;
}

template<class T>
T minimize_sa_fixedstep (T v, double& refscore, int ecnt, double stemp = 256.0, double etemp = 0.0) {
    const double sacnt = ecnt;
    T bestv = v;
    double bestscore = calcscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
        const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
        const double probability = exp((lastscore - tmpscore) / temp);
        const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
        if (tmpscore < lastscore || FORCE_NEXT) {
            lastscore = tmpscore;
            if (tmpscore < bestscore) {
                bestscore = tmpscore;
                bestv = v;
            }
        } else {
            swap(v[a], v[b]);
        }
    }
    refscore = bestscore;
    return bestv;
}

class MM {
public:
    StopWatch sw;
    MM () { this->sw = StopWatch(); }
    void input () {}
    void output () {}
    void solve () {}
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

