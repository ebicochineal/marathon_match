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
#include <random>
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
    
    GraphDijkstra (int n, vector<Edge> edges, bool undir = false) {
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
    
    GraphDijkstra (vector<Edge> edges, bool undir = false) {
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

vector<Edge> gridToGraph (array< array<int, 70>, 70>& grid, int N) {
    static const int dx[4] = {0, 0, -1, 1};
    static const int dy[4] = {-1, 1, 0, 0};
    
    vector<Edge> r;
    int h = N;
    int w = N;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int ax = x;
            int ay = y;
            if (grid[ay][ax] < 0) { continue; }
            for (int i = 0; i < 4; ++i) {
                int bx = ax + dx[i];
                int by = ay + dy[i];
                if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                if (grid[by][bx] < 0) { continue; }
                r.emplace_back(Edge(ay*w+ax, by*w+bx, grid[by][bx]));
            }
        }
    }
    return r;
}

inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}


class MM {
public:
    StopWatch sw;
    int N, SX, SY;
    array< array<int, 70>, 70> grid;
    MM () { this->sw = StopWatch(); }
    vector<int> bestret;
    void input () {
        cin >> this->N >> this->SY >> this->SX;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                char c;
                cin >> c;
                if (c == '#') {
                    this->grid[y][x] = -1;
                } else {
                    this->grid[y][x] = c - '0';
                }
            }
        }
        
    }
    
    void output () {
        static const string d = "URDL";
        string s = "";
        for (auto&& i : this->bestret) {
            s += d[i];
        }
        pdebug(this->sw.get_milli_time());
        cout << s << endl;
    }
    
    vector< vector<int> > abc;
    vector<int> pos;
    
    void delPos () {
        vector<int> tmp;
        array< array<int, 70>, 70> bgrid;
        
        for (int y = 0; y < 70; ++y) {
            for (int x = 0; x < 70; ++x) {
                bgrid[y][x] = 0;
            }
        }
        
        
        for (auto&& i : this->pos) {
            int cnt = 0;
            int x = i % this->N;
            int y = i / this->N;
            
            for (int d = 0; d < this->N; ++d) {
                int dx = x + d;
                if (!insidexywh(dx, y, this->N, this->N)) { break; }
                if (this->grid[y][dx] < 0) { break; }
                if (bgrid[y][dx] == 0) { cnt += 1; }
                bgrid[y][dx] = 1;
            }
            for (int d = 0; d < this->N; ++d) {
                int dx = x - d;
                if (!insidexywh(dx, y, this->N, this->N)) { break; }
                if (this->grid[y][dx] < 0) { break; }
                if (bgrid[y][dx] == 0) { cnt += 1; }
                bgrid[y][dx] = 1;
            }
            for (int d = 0; d < this->N; ++d) {
                int dy = y + d;
                if (!insidexywh(x, dy, this->N, this->N)) { break; }
                if (this->grid[dy][x] < 0) { break; }
                if (bgrid[dy][x] == 0) { cnt += 1; }
                bgrid[dy][x] = 1;
            }
            for (int d = 0; d < this->N; ++d) {
                int dy = y - d;
                if (!insidexywh(x, dy, this->N, this->N)) { break; }
                if (this->grid[dy][x] < 0) { break; }
                if (bgrid[dy][x] == 0) { cnt += 1; }
                bgrid[dy][x] = 1;
            }
            if (cnt > 0) {
                tmp.emplace_back(i);
            }
        }
        
        
        this->pos = tmp;
    }
    
    
    void solve () {
        static const int dx[4] = {0, 0, -1, 1};
        static const int dy[4] = {-1, 1, 0, 0};
        vector<Edge> ed = gridToGraph(this->grid, this->N);
        GraphDijkstra gd(ed, true);
        
        this->pos.emplace_back(this->SY * this->N + this->SX);
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->grid[y][x] < 0) { continue; }
                bool v = false;
                bool h = false;
                for (int i = 0; i < 2; ++i) {
                    int px = x + dx[i];
                    int py = y + dy[i];
                    if (insidexywh(px, py, this->N, this->N) && this->grid[py][px] > -1) { v = true; }
                }
                for (int i = 2; i < 4; ++i) {
                    int px = x + dx[i];
                    int py = y + dy[i];
                    if (insidexywh(px, py, this->N, this->N) && this->grid[py][px] > -1) { h = true; }
                }
                if (v && h && !(x == this->SX && y == this->SY)) {
                    this->pos.emplace_back(y * this->N + x);
                }
            }
        }
        vector<int> tmp = this->pos;
        this->delPos();
        vector<int> best = this->pos;
        int bestscore = this->pos.size();
        mt19937 mt(xrnd());
        while(this->sw.get_milli_time() < 500) {
            this->pos = tmp;
            shuffle(this->pos.begin()+1, this->pos.end(), mt);
            this->delPos();
            int score = this->pos.size();
            if (score < bestscore) {
                bestscore = score;
                best = this->pos;
            }
        }
        this->pos = best;
        
        
        int sp = this->SY * this->N + this->SX;
        for (int y = 0; y < this->pos.size(); ++y) {
            this->abc.emplace_back(vector<int>(this->pos.size(), 0));
        }
        
        for (int i = 0; i < this->pos.size(); ++i) {
            for (int j = 0; j < this->pos.size(); ++j) {
                if (i==j) { continue; }
                gd.calcPath(this->pos[i], this->pos[j]);
                this->abc[i][j] = gd.pathcost;
            }
        }
        
        vector<int> v;
        
        {
            vector<int> f(this->pos.size(), 0);
            f[0] = 1;
            int p = 0;
            
            bool lp = true;
            while (lp) {
                lp = false;
                int bestscore = 1000000;
                int best = -1;
                for (int i = 0; i < this->pos.size(); ++i) {
                    if (f[i] > 0) { continue; }
                    int score = this->abc[p][i];
                    if (score < bestscore) {
                        bestscore = score;
                        best = i;
                    }
                    
                }
                if (best > -1) {
                    f[best] = 1;
                    v.emplace_back(best);
                    p = best;
                    lp = true;
                }
            }
        }
        
        tmp.clear();
        tmp.emplace_back(this->pos[0]);
        for (int i = 0; i < v.size(); ++i) {
            tmp.emplace_back(this->pos[v[i]]);
        }
        this->pos = tmp;
        
        this->delPos();
        tmp = this->pos;
        best = this->pos;
        
        while(this->sw.get_milli_time() < 1000) {
            this->pos = tmp;
            shuffle(this->pos.begin()+1, this->pos.end(), mt);
            this->delPos();
            int score = this->pos.size();
            if (score < bestscore) {
                bestscore = score;
                best = this->pos;
            }
        }
        this->pos = best;
        for (int i = 0; i < this->pos.size(); ++i) {
            for (int j = 0; j < this->pos.size(); ++j) {
                if (i==j) { continue; }
                gd.calcPath(this->pos[i], this->pos[j]);
                this->abc[i][j] = gd.pathcost;
            }
        }
        v.clear();
        
        {
            vector<int> f(this->pos.size(), 0);
            f[0] = 1;
            int p = 0;
            
            bool lp = true;
            while (lp) {
                lp = false;
                int bestscore = 1000000;
                int best = -1;
                for (int i = 0; i < this->pos.size(); ++i) {
                    if (f[i] > 0) { continue; }
                    int score = this->abc[p][i];
                    if (score < bestscore) {
                        bestscore = score;
                        best = i;
                    }
                    
                }
                if (best > -1) {
                    f[best] = 1;
                    v.emplace_back(best);
                    p = best;
                    lp = true;
                }
            }
        }
        
        v = this->minimize_sa(v, 2500-this->sw.get_milli_time(), 8, 0);
        
        
        
        
        
        
        
        vector<int> path;
        int p = sp;
        
        array< array<int, 70>, 70> bgrid;
        for (int y = 0; y < 70; ++y) {
            for (int x = 0; x < 70; ++x) {
                bgrid[y][x] = 0;
            }
        }
        this->fill(p, bgrid);
        
        for (int i = 0; i < v.size(); ++i) {
            if (this->fillcnt(this->pos[v[i]], bgrid) == 0) { continue; }
            gd.calcPath(p, this->pos[v[i]]);
            this->addPath(gd.path, path);
            for (auto&& j : path) { this->fill(this->pos[v[i]], bgrid); }
            p = this->pos[v[i]];
        }
        gd.calcPath(p, sp);
        this->addPath(gd.path, path);
        
        
        this->bestret = path;
        
        // for (auto&& i : this->pos) {
        //     int x = i % N;
        //     int y = i / N;
        //     this->grid[y][x] = 10000;
        // }
        // for (int y = 0; y < N; ++y) {
        //     string s = "";
        //     for (int x = 0; x < N; ++x) {
        //         if (SX==x&&SY==y) {
        //             s += "*";
        //         } else {
        //             if (this->grid[y][x] == 10000) {
        //                 s += "@";
        //             } else {
        //                 s += this->grid[y][x] < 0 ? "#" : " ";
        //             }
        //         }
        //     }
        //     fdebug(s);
        // }
        
        
    }
    
    void fill (int i, array< array<int, 70>, 70>& bgrid) {
        int x = i % this->N;
        int y = i / this->N;
        bgrid[y][x] = 1;
        for (int d = 0; d < this->N; ++d) {
            int dx = x + d;
            if (!insidexywh(dx, y, this->N, this->N)) { break; }
            if (this->grid[y][dx] < 0) { break; }
            bgrid[y][dx] = 1;
        }
        for (int d = 0; d < this->N; ++d) {
            int dx = x - d;
            if (!insidexywh(dx, y, this->N, this->N)) { break; }
            if (this->grid[y][dx] < 0) { break; }
            bgrid[y][dx] = 1;
        }
        for (int d = 0; d < this->N; ++d) {
            int dy = y + d;
            if (!insidexywh(x, dy, this->N, this->N)) { break; }
            if (this->grid[dy][x] < 0) { break; }
            bgrid[dy][x] = 1;
        }
        for (int d = 0; d < this->N; ++d) {
            int dy = y - d;
            if (!insidexywh(x, dy, this->N, this->N)) { break; }
            if (this->grid[dy][x] < 0) { break; }
            bgrid[dy][x] = 1;
        }
    }
    int fillcnt (int i, array< array<int, 70>, 70>& bgrid) {
        int cnt = 0;
        int x = i % this->N;
        int y = i / this->N;
        if (bgrid[y][x] == 0) { cnt += 1; }
        for (int d = 1; d < this->N; ++d) {
            int dx = x + d;
            if (!insidexywh(dx, y, this->N, this->N)) { break; }
            if (this->grid[y][dx] < 0) { break; }
            if (bgrid[y][dx] == 0) { cnt += 1; }
        }
        for (int d = 1; d < this->N; ++d) {
            int dx = x - d;
            if (!insidexywh(dx, y, this->N, this->N)) { break; }
            if (this->grid[y][dx] < 0) { break; }
            if (bgrid[y][dx] == 0) { cnt += 1; }
        }
        for (int d = 1; d < this->N; ++d) {
            int dy = y + d;
            if (!insidexywh(x, dy, this->N, this->N)) { break; }
            if (this->grid[dy][x] < 0) { break; }
            if (bgrid[dy][x] == 0) { cnt += 1; }
        }
        for (int d = 1; d < this->N; ++d) {
            int dy = y - d;
            if (!insidexywh(x, dy, this->N, this->N)) { break; }
            if (this->grid[dy][x] < 0) { break; }
            if (bgrid[dy][x] == 0) { cnt += 1; }
        }
        return cnt;
    }
    
    double calcScore (vector<int>& v) {
        double score = 0;
        int p = 0;
        for (int i = 0; i < v.size(); ++i) {
            score += this->abc[p][v[i]];
            p = v[i];
        }
        score += this->abc[p][0];
        return score;
    }
    
    void addPath (vector<int>& path, vector<int>& ret) {
        //static const string d = "URDL";
        int px = path[0] % this->N;
        int py = path[0] / this->N;
        for (int j = 1; j < path.size(); ++j) {
            int i = path[j];
            int bx = i % this->N;
            int by = i / this->N;
            if (by < py) {
                ret.emplace_back(0);
            } else if (bx > px) {
                ret.emplace_back(1); }
            else if (by > py) {
                ret.emplace_back(2);
            } else if (bx < px) {
                ret.emplace_back(3);
            }
            px = bx;
            py = by;
        }
        
        
        
    }
    
    
    vector<int> minimize_sa (vector<int> v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector<int> bestv = v;
        double bestscore = this->calcScore(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        while (true) {
            {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                int l = 0;
                int r = 0;
                int t = max(((int)v.size() - l - r), 1);
                int a = xrnd() % t + l;
                int b = xrnd() % t + l;
                if (a > b) { swap(a, b); }
                reverse(v.begin()+a, v.begin()+b+1);
                
                double tmpscore = this->calcScore(v);
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
                    reverse(v.begin()+a, v.begin()+b+1);
                }
                cnt += 1;
            }
            
        }
        return bestv;
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

