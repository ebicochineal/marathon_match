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

inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
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




vector<Edge> gridToGraph (array< array<int, 20>, 20 >& hgrid, array< array<int, 20>, 20 > vgrid) {
    static const int dx[4] = {0, 0, -1, 1};
    static const int dy[4] = {-1, 1, 0, 0};
    
    vector<Edge> r;
    int h = 20;
    int w = 20;
    
    // h
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w-1; ++x) {
            int ax = x;
            int ay = y;
            int bx = x+1;
            int by = y;
            if (hgrid[ay][ax] == 1) { continue; }
            r.emplace_back(Edge(ay*w+ax, by*w+bx, 1));
            r.emplace_back(Edge(by*w+bx, ay*w+ax, 1));
        }
    }
    
    // v
    for (int y = 0; y < h-1; ++y) {
        for (int x = 0; x < w; ++x) {
            int ax = x;
            int ay = y;
            int bx = x;
            int by = y+1;
            if (vgrid[ay][ax] == 1) { continue; }
            r.emplace_back(Edge(ay*w+ax, by*w+bx, 1));
            r.emplace_back(Edge(by*w+bx, ay*w+ax, 1));
        }
    }
    return r;
}

struct mmstate {
    int px, py;
    vector<char> v;
    mmstate (int x, int y, vector<char> v) {
        this->px = x;
        this->py = y;
        this->v = v;
    }
    mmstate (int x, int y) {
        this->px = x;
        this->py = y;
    }
    
};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
char dir[4] = {'U', 'R', 'D', 'L'};
class MM {
public:
    StopWatch sw;
    array< array<int, 20>, 20 > hgrid;
    array< array<int, 20>, 20 > vgrid;
    
    int sx, sy, ex, ey;
    double p;
    string best;
    
    MM () { this->sw = StopWatch(); }
    
    void input () {
        cin >> this->sy >> this->sx >> this->ey >> this->ex >> this->p;
        
        for (int y = 0; y < 20; ++y) {
            string s;
            cin >> s;
            for (int x = 0; x < 19; ++x) {
                this->hgrid[y][x] = s[x] == '1' ? 1 : 0;
            }
        }
        for (int y = 0; y < 19; ++y) {
            string s;
            cin >> s;
            for (int x = 0; x < 20; ++x) {
                this->vgrid[y][x] = s[x] == '1' ? 1 : 0;
            }
        }
    }
    void output () {
        cout << this->best << endl;
    }
    
    string bms_best = "";
    void bms () {
        pdebug(this->p);
        vector<mmstate> v;
        vector<mmstate> tv;
        v.emplace_back(this->sx, this->sy);
        
        array< bitset<20>, 20 > ubs;
        array< bitset<20>, 20 > rbs;
        array< bitset<20>, 20 > dbs;
        array< bitset<20>, 20 > lbs;
        ubs[this->sy][this->sx] = true;
        rbs[this->sy][this->sx] = true;
        dbs[this->sy][this->sx] = true;
        lbs[this->sy][this->sx] = true;
        
        bool cmp = false;
        int cnt = 0;
        pdebug(sx, sy);
        while (sw.get_milli_time() < 1000 && v.size() > 0) {
            cnt += 1;
            tv.clear();
            for (auto&& st : v) {
                {
                    int px = st.px;
                    int py = st.py;
                    int nx = st.px;
                    int ny = st.py;
                    vector<char> path = st.v;
                    path.emplace_back('U');
                    for (int p = 0; p < 20; ++p) {
                        nx +=  0;
                        ny += -1;
                        if (ny < 0) { break; }
                        if (this->vgrid[ny][nx] == 1) { break; }
                        px = nx;
                        py = ny;
                        path.emplace_back('U');
                        if (nx == this->ex && ny == this->ey) { break; }
                        
                    }
                    if (!ubs[py][px]) {
                        ubs[py][px] = true;
                        tv.emplace_back(px, py, path);
                    }
                }
                {
                    int px = st.px;
                    int py = st.py;
                    int nx = st.px;
                    int ny = st.py;
                    vector<char> path = st.v;
                    path.emplace_back('L');
                    for (int p = 0; p < 20; ++p) {
                        nx += -1;
                        ny +=  0;
                        if (nx < 0) { break; }
                        if (this->hgrid[ny][nx] == 1) { break; }
                        px = nx;
                        py = ny;
                        path.emplace_back('L');
                        if (nx == this->ex && ny == this->ey) { break; }
                        
                    }
                    if (!lbs[py][px]) {
                        lbs[py][px] = true;
                        tv.emplace_back(px, py, path);
                    }
                }
                
                {
                    int px = st.px;
                    int py = st.py;
                    int nx = st.px;
                    int ny = st.py;
                    vector<char> path = st.v;
                    path.emplace_back('D');
                    for (int p = 0; p < 20; ++p) {
                        nx +=  0;
                        ny +=  1;
                        if (ny >= 20) { break; }
                        if (this->vgrid[ny-1][nx] == 1) { break; }
                        px = nx;
                        py = ny;
                        path.emplace_back('D');
                        if (nx == this->ex && ny == this->ey) { break; }
                    }
                    if (!dbs[py][px]) {
                        dbs[py][px] = true;
                        tv.emplace_back(px, py, path);
                    }
                }
                
                {
                    int px = st.px;
                    int py = st.py;
                    int nx = st.px;
                    int ny = st.py;
                    vector<char> path = st.v;
                    path.emplace_back('R');
                    for (int p = 0; p < 20; ++p) {
                        nx +=  1;
                        ny +=  0;
                        if (nx >= 20) { break; }
                        if (this->hgrid[ny][nx-1] == 1) { break; }
                        px = nx;
                        py = ny;
                        path.emplace_back('R');
                        if (nx == this->ex && ny == this->ey) { break; }
                    }
                    if (!rbs[py][px]) {
                        rbs[py][px] = true;
                        tv.emplace_back(px, py, path);
                    }
                }
            }
            v.clear();
            sort(tv.begin(), tv.end(), [](const mmstate& a, const mmstate& b) { return a.v.size() < b.v.size(); });
            
            for (int i = 0; i < min(5126*8, (int)tv.size()); ++i) {
                v.emplace_back(tv[i]);
                
                if (tv[i].px == ex && tv[i].py == ey) {
                    string s;
                    int c = 0;
                    for (auto&& z : tv[i].v) {
                        s += z;
                        if (this->p < 0.2) {
                            if (c%2 == 0) { s += z; }
                        } else {
                            s += z;
                        }
                        c += 1;
                    }
                    string ss;
                    int n = 200 - s.size();
                    if (this->p > 0.35) {
                        int c = 0;
                        for (auto&& z : s) {
                            ss += z;
                            if (c%2 && n > 0) {
                                ss += z;
                                n -= 1;
                            }
                            c += 1;
                        }
                        s = ss;
                        s = ss;
                    }
                    
                    
                    this->best = s;
                    pdebug("!!!");
                    return;
                }
            }
            
        }
    }
    
    void solve () {
        vector<Edge> e = gridToGraph(this->hgrid, this->vgrid);
        GraphDijkstra g(405, e, false);
        g.calcPath(sy*20+sx, ey*20+ex);
        
        int px = -1;
        int py = -1;
        string s;
        for (auto&& i : g.path) {
            int x = i % 20;
            int y = i / 20;
            if (px > -1) {
                if (x > px) { s += "R"; }
                if (x < px) { s += "L"; }
                if (y > py) { s += "D"; }
                if (y < py) { s += "U"; }
            }
            px = x;
            py = y;
        }
        this->best = s;
        for (int i = 0; i < 16; ++i) {
            this->best += "URDL"[xrnd()%4];
        }
        this->best += s;
        for (int i = 0; i < 16; ++i) {
            this->best += "URDL"[xrnd()%4];
        }
        this->best += s;
        for (int i = 0; i < 16; ++i) {
            this->best += "URDL"[xrnd()%4];
        }
        
        this->bms();
        
        
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

