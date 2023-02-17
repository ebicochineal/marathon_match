#pragma GCC option("arch=native")

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


struct UVW {
    int u, v, w;
    UVW (int u, int v, int w){
        this->u = u;
        this->v = v;
        this->w = w;
    }
    
};

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
    vector<int> us;
    vector<int> vs;
    GraphDijkstra (int n, vector<UVW>& uvw) {
        this->pathcost = 0;
        this->n = n;
        this->edgecost = vector< vector< pair<int, int> > >(this->n, vector< pair<int, int> >());
        
        for (int i = 0; i < uvw.size(); ++i) {
            this->us.emplace_back(this->edgecost[uvw[i].u].size());
            this->vs.emplace_back(this->edgecost[uvw[i].v].size());
            this->edgecost[uvw[i].u].emplace_back(uvw[i].v, uvw[i].w);
            this->edgecost[uvw[i].v].emplace_back(uvw[i].u, uvw[i].w);
        }
    }
    
    
    void update (int n, vector<UVW>& uvw, bitset<3005>& bs) {
        this->pathcost = 0;
        this->n = n;
        this->tmp = -1;
        
        for (int i = 0; i < uvw.size(); ++i) {
            if (bs[i] == false) {
                this->edgecost[uvw[i].u][this->us[i]].second = uvw[i].w;
                this->edgecost[uvw[i].v][this->vs[i]].second = uvw[i].w;
            } else {
                this->edgecost[uvw[i].u][this->us[i]].second = 20000000;
                this->edgecost[uvw[i].v][this->vs[i]].second = 20000000;
            }
        }
    }
    
    
    void update_remove (int n, vector<UVW>& uvw, int i) {
        this->edgecost[uvw[i].u][this->us[i]].second = uvw[i].w;
        this->edgecost[uvw[i].v][this->vs[i]].second = uvw[i].w;
    }
    
    
    void update_add (int n, vector<UVW>& uvw, int i) {
        this->edgecost[uvw[i].u][this->us[i]].second = 20000000;
        this->edgecost[uvw[i].v][this->vs[i]].second = 20000000;
    }
    
    
    void update_remove_add (int n, vector<UVW>& uvw, int i, int j) {
        this->edgecost[uvw[i].u][this->us[i]].second = uvw[i].w;
        this->edgecost[uvw[i].v][this->vs[i]].second = uvw[i].w;
        this->edgecost[uvw[j].u][this->us[j]].second = 20000000;
        this->edgecost[uvw[j].v][this->vs[j]].second = 20000000;
    }
    
    
    
    
    void calcPath (int start_i, int end_i) {
        static const int limit = numeric_limits<int>::max();
        if (this->tmp != start_i) {
            // this->prevs = vector<int>(this->n, -1);
            this->costs = vector<int>(this->n, 20000000);
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
                    // this->prevs[i.first] = t.index;
                    this->que.emplace(cost, i.first);
                }
            }
        }
        
        if (this->costs[end_i] < limit) {
            this->pathcost = this->costs[end_i];
        } else {
            this->pathcost = 20000000;
        }
    }
    
    
    int64_t calctest (int start_i) {
        
        static vector<int> prevs;
        static vector<int> costs;
        
        
        costs = vector<int>(this->n, 20000000);
        prevs = vector<int>(this->n, -1);
        costs[start_i] = 0;
        this->que.emplace(0, start_i);
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
            this->que.pop();
            for (auto&& i : this->edgecost[t.index]) {
                const int cost = t.cost + i.second;
                if (cost < costs[i.first]) {
                    costs[i.first] = cost;
                    prevs[i.first] = t.index;
                    que.emplace(cost, i.first);
                }
            }
        }
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += costs[i]; }
        return r;
    }
    
    
    
    
    
    vector<int> tprevs;
    vector<int> tcosts;
    int64_t calc (int start_i) {
        static const int limit = numeric_limits<int>::max();
        this->costs = vector<int>(this->n, 20000000);
        this->prevs = vector<int>(this->n, -1);
        this->que = priority_queue<Node, vector<Node>, greater<Node> >();
        this->costs[start_i] = 0;
        this->que.emplace(0, start_i);
        this->tmp = start_i;
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
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
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += this->costs[i]; }
        return r;
    }
    
    void cancel () {
        this->costs = this->tcosts;
        this->prevs = this->tprevs;
    }
    
    int64_t calc_remove (int start_i, vector<UVW>& uvw, int edgeindex) {
        this->tcosts = this->costs;
        this->tprevs = this->prevs;
        
        
        for (auto&& i : this->edgecost[uvw[edgeindex].u]) {
            for (auto&& j : this->edgecost[i.first]) {
                const int cost = this->costs[i.first] + j.second;
                if (cost < this->costs[j.first]) {
                    this->costs[j.first] = cost;
                    this->prevs[j.first] = i.first;
                    this->que.emplace(cost, j.first);
                }
            }
        }
        for (auto&& i : this->edgecost[uvw[edgeindex].v]) {
            for (auto&& j : this->edgecost[i.first]) {
                const int cost = this->costs[i.first] + j.second;
                if (cost < this->costs[j.first]) {
                    this->costs[j.first] = cost;
                    this->prevs[j.first] = i.first;
                    this->que.emplace(cost, j.first);
                }
            }
        }
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
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
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += this->costs[i]; }
        
        // if (r != this->calctest(start_i)) { fdebug(0); }
        
        return r;
    }
    
    int64_t calc_add (int start_i, vector<UVW>& uvw, int edgeindex) {
        this->tcosts = this->costs;
        this->tprevs = this->prevs;
        
        static vector<int> l;
        static bitset<1005> bs;
        static vector<int> q;
        
        int u = uvw[edgeindex].u;
        int v = uvw[edgeindex].v;
        
        bs.reset();
        l.clear();
        q.clear();
        if (this->prevs[u] == v) {
            q.emplace_back(u);
            l.emplace_back(u);
            bs[u] = true;
            this->costs[u] = 20000000;
            this->prevs[u] = -1;
        }
        if (this->prevs[v] == u) {
            q.emplace_back(v);
            l.emplace_back(v);
            bs[v] = true;
            this->costs[v] = 20000000;
            this->prevs[v] = -1;
            
        }
        
        while (!q.empty()) {
            int t = q.back();
            q.pop_back();
            for (auto&& i : this->edgecost[t]) {
                if (this->prevs[i.first] == t && !bs[i.first]) {
                    q.emplace_back(i.first);
                    l.emplace_back(i.first);
                    bs[i.first] = true;
                    this->costs[i.first] = 20000000;
                    this->prevs[i.first] = -1;
                }
            }
        }
        
        for (auto&& i : l) {
            for (auto&& j : this->edgecost[i]) {
                if (this->costs[j.first] >= 20000000) { continue; }
                this->que.emplace(this->costs[j.first], j.first);
            }
        }
        
        // this->costs[start_i] = 0;
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
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
        
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += this->costs[i]; }
        
        // if (r != this->calctest(start_i)) { fdebug(0); }
        
        return r;
    }
    
    
    int64_t calc_remove_add (int start_i, vector<UVW>& uvw, int removeedgeindex, int edgeindex) {
        this->tcosts = this->costs;
        this->tprevs = this->prevs;
        
        static vector<int> l;
        static bitset<1005> bs;
        static vector<int> q;
        
        int u = uvw[edgeindex].u;
        int v = uvw[edgeindex].v;
        
        bs.reset();
        l.clear();
        q.clear();
        if (this->prevs[u] == v) {
            q.emplace_back(u);
            l.emplace_back(u);
            bs[u] = true;
            this->costs[u] = 20000000;
            this->prevs[u] = -1;
        }
        if (this->prevs[v] == u) {
            q.emplace_back(v);
            l.emplace_back(v);
            bs[v] = true;
            this->costs[v] = 20000000;
            this->prevs[v] = -1;
            
        }
        
        while (!q.empty()) {
            int t = q.back();
            q.pop_back();
            for (auto&& i : this->edgecost[t]) {
                if (this->prevs[i.first] == t && !bs[i.first]) {
                    q.emplace_back(i.first);
                    l.emplace_back(i.first);
                    bs[i.first] = true;
                    this->costs[i.first] = 20000000;
                    this->prevs[i.first] = -1;
                }
            }
        }
        
        for (auto&& i : l) {
            for (auto&& j : this->edgecost[i]) {
                if (this->costs[j.first] >= 20000000) { continue; }
                this->que.emplace(this->costs[j.first], j.first);
            }
        }
        
        for (auto&& i : this->edgecost[uvw[removeedgeindex].u]) {
            for (auto&& j : this->edgecost[i.first]) {
                const int cost = this->costs[i.first] + j.second;
                if (cost < this->costs[j.first]) {
                    this->costs[j.first] = cost;
                    this->prevs[j.first] = i.first;
                    this->que.emplace(cost, j.first);
                }
            }
        }
        for (auto&& i : this->edgecost[uvw[removeedgeindex].v]) {
            for (auto&& j : this->edgecost[i.first]) {
                const int cost = this->costs[i.first] + j.second;
                if (cost < this->costs[j.first]) {
                    this->costs[j.first] = cost;
                    this->prevs[j.first] = i.first;
                    this->que.emplace(cost, j.first);
                }
            }
        }
        
        this->costs[start_i] = 0;
        
        while (!this->que.empty()) {
            const Node t = this->que.top();
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
        
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += this->costs[i]; }
        
        // if (r != this->calctest(start_i)) { fdebug(0); }
        
        return r;
    }
    
    
    
    int64_t calc_spfa (int s) {
        static bitset<1024> bs;
        static queue<int> q;
        this->costs = vector<int>(this->n, 20000000);
        bs.reset();
        bs[s]=true;
        q.push(s);
        this->costs[s]=0;
        
        while(!q.empty()){
            int t = q.front();
            q.pop();
            bs[t] = false;
            
            for (auto&& e : this->edgecost[t]) {
                if(this->costs[e.first] > this->costs[t]+e.second){
                    this->costs[e.first] = this->costs[t]+e.second;
                    if(!bs[e.first]){
                        bs[e.first] = true;
                        q.push(e.first);
                    }
                }
            }
        }
        int64_t r = 0;
        for (int i = 0; i < this->n; ++i) { r += this->costs[i]; }
        return r;
    }
};



inline double distance (const e512pos a, const e512pos b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}



class MM {
public:
    StopWatch sw;
    
    int N, M, D, K;
    vector<UVW> uvw;
    
    vector<int> pt;
    vector<e512pos> pos;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->M >> this->D >> this->K;
        for (int i = 0; i < this->M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            this->uvw.emplace_back(u-1, v-1, w);
        }
        for (int i = 0; i < this->N; ++i) {
            int x, y;
            cin >> x >> y;
            this->pos.emplace_back(x, y);
        }
        
        for (int i = 0; i < 32; ++i) { this->pt.emplace_back(xrnd()%this->N); }
        
        int d = 250;
        for (int i = 0; i < this->N; ++i) {
            e512pos t(500, 500);
            if (distance(this->pos[i], t) < distance(this->pos[pt[0]], t)) { pt[0] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(0+d, 0+d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[1]], t)) { pt[1] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(0+d, 1000-d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[2]], t)) { pt[2] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(1000-d, 0+d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[3]], t)) { pt[3] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(1000-d, 1000-d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[4]], t)) { pt[4] = i; }
        }
        
        
    }
    
    vector<int> bestv;
    void output () {
        pdebug(this->M, this->D, this->K, this->sw.get_milli_time());
        for (auto&& i : this->bestv) { cout << i+1 << " "; }
        cout << endl;
        
    }
    
    
    
    void solve () {
        vector<int> a;
        
        for (int i = 0; i < this->M; ++i) {
            a.emplace_back(i % this->D);
        }
        
        
        vector< vector<int> > v;
        for (int d = 0; d < this->D; ++d) {
            vector<int> t;
            for (int m = 0; m < this->M; ++m) {
                if (a[m] == d) { t.emplace_back(m); }
            }
            v.emplace_back(t);
        }
        
        int64_t s = 0;
        for (auto&& i : this->uvw) { s+= i.w; }
        s /= this->M;
        
        v = this->minimize_sa(5, v, 5940-this->sw.get_milli_time(), s*2, 0);
        
        vector< pair<int,  int> > md;
        for (int d = 0; d < this->D; ++d) {
            for (auto&& m : v[d]) {
                md.emplace_back(m, d);
            }
        }
        sort(md.begin(), md.end(), [](const pair<int,  int>& a, const pair<int,  int>& b) { return a.first < b.first; });
        
        for (int m = 0; m < this->M; ++m) {
            a[m] = md[m].second;
        }
        this->bestv = a;
    }
    
    vector< vector<int> > minimize_sa (int n, vector< vector<int> > v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        vector<int64_t> bestscores;
        for (int i = 0; i < this->D; ++i) {
            bestscores.emplace_back(this->calc_score_d(n, v[i], i, true));
        }
        unordered_set<e512pos> us1, us2;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector< vector<int> > bestv = v;
        double bestscore = this->sumscore(bestscores);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        vector< pair<int, int> > q;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            {
                // for (int z = 0; z < 8; ++z) {
                //     int a = xrnd()%this->D;
                //     int b = xrnd()%this->D;
                //     if (a == b) { continue; }
                //     if (v[a].size() < 1 || v[b].size() < 1) { continue; }
                //     int ai = xrnd()%v[a].size();
                //     int bi = xrnd()%v[b].size();
                //     int arm = v[a][ai];
                //     int aadd = v[b][bi];
                //     int brm = v[b][bi];
                //     int badd = v[a][ai];
                    
                //     swap(v[a][ai], v[b][bi]);
                    
                //     int64_t ascore = this->calc_score_d_remove_add(n, a, arm, aadd);
                //     int64_t bscore = this->calc_score_d_remove_add(n, b, brm, badd);
                    
                    
                //     double tmpscore = lastscore - bestscores[a] - bestscores[b] + ascore + bscore;
                //     const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                //     const double probability = exp((lastscore - tmpscore) / temp);
                //     const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                //     if (tmpscore < lastscore || FORCE_NEXT) {
                //         lastscore = tmpscore;
                        
                //         bestscores[a] = ascore;
                //         bestscores[b] = bscore;
                        
                //         if (tmpscore < bestscore) {
                //             bestscore = tmpscore;
                //             bestv = v;
                //         }
                //     } else {
                //         swap(v[a][ai], v[b][bi]);
                        
                //         this->calc_score_d_remove_add_cancel(n, a, arm, aadd);
                //         this->calc_score_d_remove_add_cancel(n, b, brm, badd);
                //     }
                //     cnt += 1;
                // }
                
                
                for (int z = 0; z < 16; ++z) {
                    int a = xrnd()%this->D;
                    int b = xrnd()%this->D;
                    if (a == b) { continue; }
                    if (v[a].size() < 1 || v[b].size() >= this->K) { continue; }
                    int ai = xrnd()%v[a].size();
                    int tmp = v[a][ai];
                    swap(v[a][ai], v[a][v[a].size()-1]);
                    v[b].emplace_back(v[a][v[a].size()-1]);
                    v[a].pop_back();
                    
                    
                    int64_t ascore = this->calc_score_d_remove(n, a, tmp);
                    int64_t bscore = this->calc_score_d_add(n, b, tmp);
                    
                    
                    double tmpscore = lastscore - bestscores[a] - bestscores[b] + ascore + bscore;
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    if (tmpscore < lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        bestscores[a] = ascore;
                        bestscores[b] = bscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            bestv = v;
                        }
                    } else {
                        v[a].emplace_back(v[b][v[b].size()-1]);
                        swap(v[a][ai], v[a][v[a].size()-1]);
                        v[b].pop_back();
                        
                        this->calc_score_d_remove_cancel(n, a, tmp);
                        this->calc_score_d_add_cancel(n, b, tmp);
                    }
                    cnt += 1;
                }
                
                
            }
        }
        pdebug(cnt);
        return bestv;
    }
    
    
    void solve26 () {
        vector<int> a;
        if (this->D > 10) {
            int cnt = 0;
            int dd = 0;
            for (int i = 0; i < this->M; ++i) {
                a.emplace_back(dd);
                cnt += 1;
                if (cnt >= this->K) {
                    cnt = 0;
                    dd += 1;
                }
            }
        } else {
            for (int i = 0; i < this->M; ++i) {
                a.emplace_back(i % this->D);
            }
        }
        
        vector< vector<int> > v;
        for (int d = 0; d < this->D; ++d) {
            vector<int> t;
            for (int m = 0; m < this->M; ++m) {
                if (a[m] == d) { t.emplace_back(m); }
            }
            v.emplace_back(t);
        }
        
        int64_t s = 0;
        for (auto&& i : this->uvw) { s+= i.w; }
        s /= this->M;
        
        v = this->minimize_sa26(2, v, 600, s, 0);
        int d = 250;
        for (int i = 0; i < this->N; ++i) {
            e512pos t(0+d, 0+d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[0]], t)) { pt[0] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(0+d, 1000-d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[1]], t)) { pt[1] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(1000-d, 0+d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[2]], t)) { pt[2] = i; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            e512pos t(1000-d, 1000-d);
            if (distance(this->pos[i], t) < distance(this->pos[pt[3]], t)) { pt[3] = i; }
        }
        
        v = this->minimize_sa26(4, v, 5850-this->sw.get_milli_time(), s, 0);
        
        vector< pair<int,  int> > md;
        for (int d = 0; d < this->D; ++d) {
            for (auto&& m : v[d]) {
                md.emplace_back(m, d);
            }
        }
        sort(md.begin(), md.end(), [](const pair<int,  int>& a, const pair<int,  int>& b) { return a.first < b.first; });
        
        for (int m = 0; m < this->M; ++m) {
            a[m] = md[m].second;
        }
        this->bestv = a;
    }
    
    
    vector< vector<int> > minimize_sa26 (int n, vector< vector<int> > v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        vector<int64_t> bestscores;
        for (int i = 0; i < this->D; ++i) {
            bestscores.emplace_back(this->calc_score_d(n, v[i]));
        }
        unordered_set<e512pos> us1, us2;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector< vector<int> > bestv = v;
        double bestscore = this->sumscore(bestscores);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        vector< pair<int, int> > q;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            if (ntime >= etime * 0.5) {
                for (int z = 0; z < 16; ++z) {
                    int a = xrnd()%this->D;
                    int b = xrnd()%this->D;
                    if (a == b) { continue; }
                    if (v[a].size() < 1 || v[b].size() < 1) { continue; }
                    int ai = xrnd()%v[a].size();
                    int bi = xrnd()%v[b].size();
                    
                    if (us1.find(e512pos(v[a][ai], b)) != us1.end()) { continue; }
                    if (us1.find(e512pos(v[b][bi], a)) != us1.end()) { continue; }
                    
                    e512pos pa, pb;
                    pa = this->pos[this->uvw[v[a][ai]].v];
                    pb = this->pos[this->uvw[v[b][bi]].v];
                    if ((distance(pa, e512pos(500, 500)) > 400 || distance(pb, e512pos(500, 500)) > 400) && z % 2) { continue; }
                    
                    
                    
                    swap(v[a][ai], v[b][bi]);
                    int64_t ascore = this->calc_score_d(n, v[a]);
                    
                    if (ascore > bestscores[a] + 51260*6) {
                        swap(v[a][ai], v[b][bi]);
                        us1.emplace(v[b][bi], a);
                        cnt += 1;
                        continue;
                    }
                    
                    int64_t bscore = this->calc_score_d(n, v[b]);
                    
                    double tmpscore = lastscore - bestscores[a] - bestscores[b] + ascore + bscore;
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    if (tmpscore < lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        bestscores[a] = ascore;
                        bestscores[b] = bscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            bestv = v;
                        }
                    } else {
                        swap(v[a][ai], v[b][bi]);
                        if (bscore > bestscores[b] + 51260) {
                            us1.emplace(v[a][ai], b);
                        }
                        if (ascore > bestscores[a] + 51260) {
                            us1.emplace(v[b][bi], a);
                        }
                    }
                    cnt += 1;
                }
            } else if (ntime >= etime * 0.1) {
                for (int z = 0; z < 16; ++z) {
                    int a = xrnd()%this->D;
                    int b = xrnd()%this->D;
                    if (a == b) { continue; }
                    if (v[a].size() < 1 || v[b].size() < 1) { continue; }
                    int ai = xrnd()%v[a].size();
                    int bi = xrnd()%v[b].size();
                    
                    e512pos pa, pb;
                    pa = this->pos[this->uvw[v[a][ai]].v];
                    pb = this->pos[this->uvw[v[b][bi]].v];
                    if ((distance(pa, e512pos(500, 500)) > 400 || distance(pb, e512pos(500, 500)) > 400) && z % 2) { continue; }
                    
                    swap(v[a][ai], v[b][bi]);
                    
                    int64_t ascore = this->calc_score_d(n, v[a]);
                    
                    int64_t bscore = this->calc_score_d(n, v[b]);
                    
                    
                    double tmpscore = lastscore - bestscores[a] - bestscores[b] + ascore + bscore;
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    if (tmpscore < lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        bestscores[a] = ascore;
                        bestscores[b] = bscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            bestv = v;
                        }
                    } else {
                        swap(v[a][ai], v[b][bi]);
                    }
                    cnt += 1;
                }
            } else {
                for (int z = 0; z < 16; ++z) {
                    int a = xrnd()%this->D;
                    int b = xrnd()%this->D;
                    if (a == b) { continue; }
                    if (v[a].size() < 1 || v[b].size() < 1) { continue; }
                    int ai1 = xrnd()%v[a].size();
                    int bi1 = xrnd()%v[b].size();
                    int ai2 = xrnd()%v[a].size();
                    int bi2 = xrnd()%v[b].size();
                    int ai3 = xrnd()%v[a].size();
                    int bi3 = xrnd()%v[b].size();
                    int ai4 = xrnd()%v[a].size();
                    int bi4 = xrnd()%v[b].size();
                    
                    swap(v[a][ai1], v[b][bi1]);
                    swap(v[a][ai2], v[b][bi2]);
                    swap(v[a][ai3], v[b][bi3]);
                    swap(v[a][ai4], v[b][bi4]);
                    
                    
                    int64_t ascore = this->calc_score_d(n, v[a]);
                    int64_t bscore = this->calc_score_d(n, v[b]);
                    
                    
                    double tmpscore = lastscore - bestscores[a] - bestscores[b] + ascore + bscore;
                    const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                    if (tmpscore < lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        bestscores[a] = ascore;
                        bestscores[b] = bscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            bestv = v;
                        }
                    } else {
                        swap(v[a][ai4], v[b][bi4]);
                        swap(v[a][ai3], v[b][bi3]);
                        swap(v[a][ai2], v[b][bi2]);
                        swap(v[a][ai1], v[b][bi1]);
                    }
                    cnt += 1;
                }
            }
        }
        pdebug(cnt);
        return bestv;
    }
    
    
    
    int64_t calc_score_d (int n, vector<int>& v) {
        static GraphDijkstra g(N, this->uvw);
        static bitset<3005> bs;
        // int a = this->N/n+n;
        
        int64_t r = 0;
        bs.reset();
        for (auto&& i : v) { bs[i] = true; }
        
        g.update(N, this->uvw, bs);
        
        for (int i = 0; i < n; ++i) {
            r += g.calc(this->pt[i]);
        }
        
        return r;
    }
    
    
    array<array<GraphDijkstra, 5>, 30> gs;
    int64_t calc_score_d (int n, vector<int>& v, int d, bool f = false) {
        static bitset<3005> bs;
        bs.reset();
        for (auto&& i : v) { bs[i] = true; }
        
        int64_t r = 0;
        
        for (int i = 0; i < n; ++i) {
            if (f) { this->gs[d][i] = GraphDijkstra(N, this->uvw); }
            this->gs[d][i].update(N, this->uvw, bs);
            r += this->gs[d][i].calc(this->pt[i]);
        }
        
        return r;
    }
    
    int64_t calc_score_d_remove_add (int n, int d, int removeindex, int addindex) {
        int64_t r = 0;
        
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_remove_add(N, this->uvw, removeindex, addindex);
            r += this->gs[d][i].calc_remove_add(this->pt[i], this->uvw, removeindex, addindex);
        }
        
        return r;
    }
    
    void calc_score_d_remove_add_cancel (int n, int d, int removeindex, int addindex) {
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_remove_add(N, this->uvw, addindex, removeindex);
            this->gs[d][i].cancel();
        }
    }
    
    int64_t calc_score_d_add (int n, int d, int index) {
        int64_t r = 0;
        
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_add(N, this->uvw, index);
            r += this->gs[d][i].calc_add(this->pt[i], this->uvw, index);
        }
        
        return r;
    }
    void calc_score_d_add_cancel (int n, int d, int index) {
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_remove(N, this->uvw, index);
            this->gs[d][i].cancel();
        }
    }
    int64_t calc_score_d_remove (int n, int d, int index) {
        int64_t r = 0;
        
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_remove(N, this->uvw, index);
            r += this->gs[d][i].calc_remove(this->pt[i], this->uvw, index);
        }
        return r;
    }
    void calc_score_d_remove_cancel (int n, int d, int index) {
        for (int i = 0; i < n; ++i) {
            this->gs[d][i].update_add(N, this->uvw, index);
            this->gs[d][i].cancel();
        }
    }
    
    int64_t sumscore (vector<int64_t>& scores) {
        int64_t r = 0;
        for (auto&& i : scores) { r += i; }
        return r;
    }
    
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    // mm.solve26();
    mm.output();
    cout.flush();
    return 0;
}

