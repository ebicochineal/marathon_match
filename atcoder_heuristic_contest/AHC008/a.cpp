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
template<class T, size_t N> string v_to_str (const array<T, N>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < (int)v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T, size_t N> string v_to_str (const array< array<T, N>, N >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < (int)v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < (int)v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < (int)v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
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
                this->path.emplace_back(e);
                e = this->prevs[e];
            }
            reverse(this->path.begin(), this->path.end());
        } else {
            this->pathcost = -1;
        }
    }
};



vector<int> tgrid = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 1, 1, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

vector<int> ngrid = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 3, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 3, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 3, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 3, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
array<int, 30> yy = {-1,-1,-1,1,1,0,0,-1,0, 0,1,0,-1,-1,0,1,1,0,-1,0,0,1,0,0,-1,-1,1,1,1,0};

array<int, 30> xx = {-2, -1, 0, 1, 0, -1, -1, -1, 0,
                      0,
                      0, -1, -1, 0, 1, 1, 0, -1, -1, 0,
                      0,
                      0, -1, -1,-1, 0, 1, 0, -1, -2
                    };

class PT {
public:
    int x, y, pt;
    bool alive = true;
    PT (int y, int x, int pt) {
        this->y = y;
        this->x = x;
        this->pt = pt;
    }
    void apply_action (string& mv) {
        for (auto&& i : mv) {
            if (i == 'U') { this->y -= 1; }
            if (i == 'R') { this->x += 1; }
            if (i == 'D') { this->y += 1; }
            if (i == 'L') { this->x -= 1; }
        }
    }
    bool putcollision (int x, int y) {
        if (abs(this->x - x) + abs(this->y - y) < 2) { return true; }
        return false;
    }
};

class HM {
public:
    int x, y;
    
    vector<int> path;
    
    
    string task = "wait";
    int taskv1 = -1;
    int taskv2 = -1;
    
    char c = '.';
    HM (int y, int x) {
        this->y = y;
        this->x = x;
    }
    
    int turn_end_pos () {
        int px = this->x;
        int py = this->y;
        if (this->c == 'U') { py -= 1; }
        if (this->c == 'R') { px += 1; }
        if (this->c == 'D') { py += 1; }
        if (this->c == 'L') { px -= 1; }
        return py * 30 + px;
    }
    
    bool putcollision (int x, int y) {
        int px = this->x;
        int py = this->y;
        if (x == px && y == py) { return true; }
        if (this->c == 'U') { py -= 1; }
        if (this->c == 'R') { px += 1; }
        if (this->c == 'D') { py += 1; }
        if (this->c == 'L') { px -= 1; }
        // if (this->c == 'u') { py -= 1; }
        // if (this->c == 'r') { px += 1; }
        // if (this->c == 'd') { py += 1; }
        // if (this->c == 'l') { px -= 1; }
        if (x == px && y == py) { return true; }
        return false;
    }
    bool movecollision (int x, int y) {
        int px = this->x;
        int py = this->y;
        if (this->c == 'u' && x == px && y == py-1) { return true; }
        if (this->c == 'r' && x == px+1 && y == py) { return true; }
        if (this->c == 'd' && x == px && y == py+1) { return true; }
        if (this->c == 'l' && x == px-1 && y == py) { return true; }
        return false;
    }
    void apply_action () {
        if (this->c == 'U') { this->y -= 1; }
        if (this->c == 'R') { this->x += 1; }
        if (this->c == 'D') { this->y += 1; }
        if (this->c == 'L') { this->x -= 1; }
        this->c = '.';
    }
    
    
};



//urdl
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};


class MM {
public:
    StopWatch sw;
    
    int N=0, M=0;
    
    int turn = 0;
    vector<PT> pts;
    vector<HM> hms;
    bitset<900> impossible;
    array<int, 900> petgrid;
    bitset<900> hmgrid;
    
    bitset<900> targetflags;
    bitset<900> truetargetflags;
    
    int dcnt = 0;
    int state = 0;
    
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N;
        for (int i = 0; i < this->N; ++i) {
            int y, x, pt;
            cin >> y >> x >> pt;
            this->pts.emplace_back(y-1, x-1, pt);
        }
        cin >> this->M;
        for (int i = 0; i < this->M; ++i) {
            int y, x;
            cin >> y >> x;
            this->hms.emplace_back(y-1, x-1);
        }
        
        for (auto&& i : this->pts) {
            if (i.pt == 4) { this->dcnt += 1; }
        }
        
        pdebug(N, M, this->dcnt);
    }
    
    bool isput (int x, int y) {
        for (auto&& i : this->pts) {
            if (i.putcollision(x, y)) { return false; }
        }
        for (auto&& i : this->hms) {
            if (i.putcollision(x, y)) { return false; }
        }
        if (this->impossible[y*30+x]) { return false; }
        
        return true;
    }
    bool ismove (int x, int y) {
        for (auto&& i : this->hms) {
            if (i.movecollision(x, y)) { return false; }
        }
        return !this->impossible[y*30+x];
    }
    
    bool isinside (const int x, const int y) {
        return (0 <= x && x < 30 && 0 <= y && y < 30);
    }
    
    bool isoutside (const int x, const int y) {
        return !(0 <= x && x < 30 && 0 <= y && y < 30);
    }
    void debug_grid () {
        static bitset<900> timpossible;
        int h = 30;
        int w = 30;
        
        fdebug(this->turn);
        for (int y = 0; y < h; ++y) {
            string s;
            for (int x = 0; x < w; ++x) {
                s += this->ismove(x, y) ? " " : "#";
            }
            fdebug(s);
        }
        
    }
    
    vector<Edge> gridToGraph () {
        static bitset<900> timpossible;
        static array<int, 900> costgrid;
        vector<Edge> r;
        int h = 30;
        int w = 30;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                timpossible[y*w+x] = this->ismove(x, y);
                costgrid[y*w+x] = 1;
                if (tgrid[y*w+x]==1) { costgrid[y*w+x] += 2; }
            }
        }
        
        if (this->state >= 3) {
            for (auto&& i : this->hms) {
                for (auto&& j : i.path) {
                    int x = j % 30;
                    int y = j / 30;
                    costgrid[j] += 1;
                    for (int i = 0; i < 4; ++i) {
                        int bx = x + dx[i];
                        int by = y + dy[i];
                        if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                        costgrid[by*w+bx] += 1;
                    }
                }
            }
        }
        
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                for (int i = 0; i < 4; ++i) {
                    int bx = x + dx[i];
                    int by = y + dy[i];
                    if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                    if (!timpossible[by*w+bx]) { continue; }
                    r.emplace_back(Edge(y*w+x, by*w+bx, costgrid[by*w+bx]));
                }
            }
        }
        return r;
    }
    
    int petcnt (int sx, int sy) {
        static bitset<900> g;
        static vector<int> q;
        g.reset();
        q.clear();
        q.emplace_back(sy*30+sx);
        
        int cnt = 0;
        while (q.size() > 0) {
            int u = q.back();
            g[u] = true;
            if (this->petgrid[u] > 0) { cnt += 1; }
            q.pop_back();
            int x = u % 30;
            int y = u / 30;
            for (int d = 0; d < 4; ++d) {
                int px = x + dx[d];
                int py = y + dy[d];
                int v = py*30+px;
                if (this->isoutside(px, py)) { continue; }
                if (this->impossible[v]) { continue; }
                if (g[v]) { continue; }
                g[v] = true;
                q.emplace_back(v);
            }
            
        }
        return cnt;
    }
    
    int petcnt (int sx, int sy, int t) {
        static bitset<900> g;
        static vector<int> q;
        g.reset();
        q.clear();
        q.emplace_back(sy*30+sx);
        
        int cnt = 0;
        while (q.size() > 0) {
            int u = q.back();
            g[u] = true;
            if (this->petgrid[u] == t) { cnt += 1; }
            q.pop_back();
            int x = u % 30;
            int y = u / 30;
            for (int d = 0; d < 4; ++d) {
                int px = x + dx[d];
                int py = y + dy[d];
                int v = py*30+px;
                if (this->isoutside(px, py)) { continue; }
                if (this->impossible[v]) { continue; }
                if (g[v]) { continue; }
                g[v] = true;
                q.emplace_back(v);
            }
        }
        return cnt;
    }
    
    int hmcnt (int sx, int sy) {
        static bitset<900> g;
        static vector<int> q;
        g.reset();
        q.clear();
        q.emplace_back(sy*30+sx);
        
        int cnt = 0;
        while (q.size() > 0) {
            int u = q.back();
            g[u] = true;
            if (this->hmgrid[u]) { return 1; }
            q.pop_back();
            int x = u % 30;
            int y = u / 30;
            for (int d = 0; d < 4; ++d) {
                int px = x + dx[d];
                int py = y + dy[d];
                int v = py*30+px;
                if (this->isoutside(px, py)) { continue; }
                if (this->impossible[v]) { continue; }
                if (g[v]) { continue; }
                g[v] = true;
                q.emplace_back(v);
            }
        }
        return cnt;
    }
    
    int areacnt (int sx, int sy) {
        static bitset<900> g;
        static vector<int> q;
        g.reset();
        q.clear();
        q.emplace_back(sy*30+sx);
        
        int cnt = 0;
        while (q.size() > 0) {
            int u = q.back();
            g[u] = true;
            cnt += 1;
            q.pop_back();
            int x = u % 30;
            int y = u / 30;
            for (int d = 0; d < 4; ++d) {
                int px = x + dx[d];
                int py = y + dy[d];
                int v = py*30+px;
                if (this->isoutside(px, py)) { continue; }
                if (this->impossible[v]) { continue; }
                if (g[v]) { continue; }
                g[v] = true;
                q.emplace_back(v);
            }
            
        }
        return cnt;
    }
    
    int calcscore () {
        double r = 0;
        for (auto&& i : this->hms) {
            int ri = this->areacnt(i.x, i.y);
            int ni = this->petcnt(i.x, i.y);
            r += (ri/900.0) * pow(2.0, -ni) * 100000000 * (1.0/this->M);
        }
        return (int)r;
    }
    
    int zero_hm_cnt () {
        int cnt = 0;
        for (auto&& i : this->pts) {
            if (this->hmcnt(i.x, i.y) == 0) { cnt += 1; }
        }
        return cnt;
    }
    
    void wall_put (HM& hm) {
        if (hm.c != '.') { return; }
        if (hm.x > 0   && this->isput(hm.x-1, hm.y) && tgrid[hm.y*30+(hm.x-1)] == 1) { hm.c = 'l'; }
        if (hm.x < 29  && this->isput(hm.x+1, hm.y) && tgrid[hm.y*30+(hm.x+1)] == 1) { hm.c = 'r'; }
        if (hm.y > 0   && this->isput(hm.x, hm.y-1) && tgrid[(hm.y-1)*30+hm.x] == 1) { hm.c = 'u'; }
        if (hm.y < 29  && this->isput(hm.x, hm.y+1) && tgrid[(hm.y+1)*30+hm.x] == 1) { hm.c = 'd'; }
    }
    
    void hm_set_path (vector<int>& path, HM& hm) {
        if (path.size() < 2) { return; }
        hm.path.clear();
        for (int i = 1; i < (int)path.size(); ++i) { hm.path.emplace_back(path[path.size()-i]); }
    }
    
    void set_wall_path (HM& hm) {
        if (hm.c != '.') { return; }
        if (hm.path.size() > 0) { return; }
        vector<Edge> e = this->gridToGraph();
        GraphDijkstra g(905, e, false);
        
        int bestdist = 10000;
        
        vector<int> path;
        for (int p = 0; p < 900; ++p) {
            if (tgrid[p] != 1) { continue; }
            if (this->impossible[p]) { continue; }
            if (this->targetflags[p] == true) { continue; }
            g.calcPath(hm.y*30+hm.x, p);
            int dist = g.pathcost;
            if (g.path.size() < 3) { continue; }
            
            int cnt = 0;
            for (int d = 0; d < 4; ++d) {
                int bx = (p%30)+dx[d];
                int by = (p/30)+dy[d];
                if (this->isoutside(bx, by)) { cnt += 1; }
            }
            if (this->state == 3) {
                dist = max(dist-cnt*2, 1);
            }
            
            if (dist < bestdist) {
                bestdist = dist;
                path = g.path;
            }
        }
        this->hm_set_path(path, hm);
    }
    
    
    void path_check (HM& hm) {
        bool f = false;
        for (auto&& i : hm.path) {
            if (!this->ismove(i%30, i/30)) {
                f = true;
                break;
            }
        }
        if (f) { hm.path.clear(); }
    }
    
    
    void path_move0 (HM& hm) {
        if (hm.c != '.') { return; }
        if (hm.path.size() == 0) { return; }
        
        
        int p = hm.path.back();
        int x = p % 30;
        int y = p / 30;
        hm.path.pop_back();
        if (!this->ismove(x, y) || this->impossible[p] || abs(x-hm.x)+abs(y-hm.y) > 1) {
            hm.path.clear();
            return;
        }
        
        if (x < hm.x) { hm.c = 'L'; }
        if (x > hm.x) { hm.c = 'R'; }
        if (y < hm.y) { hm.c = 'U'; }
        if (y > hm.y) { hm.c = 'D'; }
    }
    
    
    
    void path_move (HM& hm) {
        if (hm.c != '.') { return; }
        if (hm.path.size() == 0) { return; }
        
        this->pet_block_put2(hm);
        if (hm.c != '.') { return; }
        
        
        int p = hm.path.back();
        int x = p % 30;
        int y = p / 30;
        hm.path.pop_back();
        if (!this->ismove(x, y) || this->impossible[p] || abs(x-hm.x)+abs(y-hm.y) > 1) {
            hm.path.clear();
            return;
        }
        
        if (x < hm.x) { hm.c = 'L'; }
        if (x > hm.x) { hm.c = 'R'; }
        if (y < hm.y) { hm.c = 'U'; }
        if (y > hm.y) { hm.c = 'D'; }
    }
    
    void tgridet_target_path () {
        if (this->state != 1) { return; }
        
        vector<int> sp;
        for (int i = 0; i < 900; ++i) {
            if (tgrid[i] == 2) {
                sp.emplace_back(i);
            }
        }
        vector<Edge> e = this->gridToGraph();
        GraphDijkstra g(905, e, false);
        
        bitset<10> bs; 
        for (int i = 0; i < this->M; ++i) {
            int p = sp[i%2];
            int best = -1;
            int bestdist = 1000;
            vector<int> path;
            for (int j = 0; j < this->M; ++j) {
                if (bs[j]) { continue; }
                HM& hm = this->hms[j];
                g.calcPath(hm.y*30+hm.x, p);
                int dist = g.pathcost;
                if (dist > -1 && dist < bestdist){
                    bestdist = dist;
                    best = j;
                    path = g.path;
                }
            }
            if (best > -1) {
                bs[best] = true;
                this->hms[best].path.clear();
                this->hm_set_path(path, this->hms[best]);
            }
        }
        this->state = 2;
    }
    
    void tgridet_target_path0 (HM& hm) {
        if (hm.c != '.') { return; }
        if (this->state != 0) { return; }
        
        vector<int> sp;
        int t = 2+xrnd()%2;
        for (int i = 0; i < 900; ++i) {
            if (tgrid[i] == t) {
                sp.emplace_back(i);
            }
        }
        
        int best = -1;
        int bestdist = 1000;
        for (auto&& i : sp) {
            int x = i % 30;
            int y = i / 30;
            int dist = abs(hm.x-x) + abs(hm.y-y);
            if (dist < bestdist){
                bestdist = dist;
                best = i;
            }
        }
        if (best > -1) {
            vector<Edge> e = this->gridToGraph();
            GraphDijkstra g(905, e, false);
            g.calcPath(hm.y*30+hm.x, best);
            this->hm_set_path(g.path, hm);
        }
        
    }
    
    
    void tgridblock_put () {
        if (this->state != 2) { return; }
        
        for (auto&& i : this->hms) {
            int p = i.y * 30 + i.x;
            if (tgrid[p] != 2) { return; }
        }
        
        for (int i = 0; i < 900; ++i) {
            int x = i % 30;
            int y = i / 30;
            if (tgrid[i] == 4 && this->isput(x, y)) {
                this->impossible[i] = true;
            }
        }
        int dogcnt = this->dcnt;
        for (auto&& i : this->pts) {
            if (i.pt != 4) { continue; }
            if (this->hmcnt(i.x, i.y) == 0) { dogcnt -= 1; }
        }
        for (int i = 0; i < 900; ++i) {
            if (tgrid[i] == 4) { this->impossible[i] = false; }
        }
        
        if (dogcnt > 0) { return; }
        
        for (auto&& i : this->hms) {
            int p = i.y * 30 + i.x;
            if (tgrid[p] != 2) { return; }
        }
        
        for (auto&& i : this->hms) {
            for (int d = 0; d < 4; ++d) {
                int px = i.x + dx[d];
                int py = i.y + dy[d];
                int v = py*30+px;
                if (this->isoutside(px, py)) { continue; }
                if (this->impossible[v]) { continue; }
                if (tgrid[v] == 4) {
                    this->impossible[v] = true;
                    if (d == 0) { i.c = 'u'; }
                    if (d == 1) { i.c = 'r'; }
                    if (d == 2) { i.c = 'd'; }
                    if (d == 3) { i.c = 'l'; }
                    break;
                }
            }
        }
        
        this->state = 3;
        pdebug("de", this->turn);
    }
    
    
    int set_start_tgridpath () {
        int rdist = 0;
        vector<Edge> e = this->gridToGraph_w();
        GraphDijkstra g(905, e, false);
        vector<int> sp;
        for (int i = 0; i < 900; ++i) {
            if (tgrid[i] == 2) {
                sp.emplace_back(i);
            }
        }
        for (auto&& hm : this->hms) { hm.path.clear(); }
        {
            int bestindex = 0;
            int bestdist = 1000;
            for (int i = 0; i < this->M; ++i) {
                HM& hm = this->hms[i];
                int p = hm.y*30+hm.x;
                g.calcPath(p, sp[0]);
                int dist = g.pathcost;
                if (dist < bestdist) {
                    bestdist = dist;
                    bestindex = i;
                }
            }
            HM& hm = this->hms[bestindex];
            int p = hm.y*30+hm.x;
            g.calcPath(p, sp[0]);
            vector<int> path = g.path;
            g.calcPath(sp[0], sp[1]);
            for (int i = 1; i < (int)g.path.size(); ++i) {
                path.emplace_back(g.path[i]);
            }
            this->hm_set_path(path, hm);
        }
        
        {
            int bestindex = 0;
            int bestdist = 1000;
            for (int i = 0; i < this->M; ++i) {
                HM& hm = this->hms[i];
                int p = hm.y*30+hm.x;
                g.calcPath(p, sp[1]);
                int dist = g.pathcost;
                if (dist < bestdist) {
                    bestdist = dist;
                    bestindex = i;
                }
            }
            HM& hm = this->hms[bestindex];
            int p = hm.y*30+hm.x;
            g.calcPath(p, sp[1]);
            vector<int> path = g.path;
            g.calcPath(sp[1], sp[0]);
            for (int i = 1; i < (int)g.path.size(); ++i) {
                path.emplace_back(g.path[i]);
            }
            this->hm_set_path(path, hm);
        }
        
        int c = 0;
        for (auto&& hm : this->hms) {
            if (hm.path.size() > 0) { continue; }
            int p = hm.y*30+hm.x;
            
            if (c % 2 == 0) {
                g.calcPath(p, sp[0]);
                vector<int> path = g.path;
                // g.calcPath(sp[0], sp[1]);
                // for (int i = 1; i < g.path.size(); ++i) {
                //     path.emplace_back(g.path[i]);
                // }
                this->hm_set_path(path, hm);
            } else {
                g.calcPath(p, sp[1]);
                vector<int> path = g.path;
                // g.calcPath(sp[1], sp[0]);
                // for (int i = 1; i < g.path.size(); ++i) {
                //     path.emplace_back(g.path[i]);
                // }
                this->hm_set_path(path, hm);
            }
            
            c += 1;
        }
        
        for (auto&& i : this->hms) { rdist += i.path.size(); }
        return rdist;
    }
    
    vector<int> rotategrid (vector<int> v) {
        vector<int> r = v;
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                r[x*30+(29-y)] = v[y*30+x];
            }
        }
        return r;
    }
    
    vector<Edge> gridToGraph_w () {
        static bitset<900> timpossible;
        static array<int, 900> costgrid;
        vector<Edge> r;
        int h = 30;
        int w = 30;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                timpossible[y*w+x] = this->ismove(x, y);
                costgrid[y*w+x] = 1;
                if (tgrid[y*w+x]==1) { costgrid[y*w+x] += 100; }
            }
        }
        
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                for (int i = 0; i < 4; ++i) {
                    int bx = x + dx[i];
                    int by = y + dy[i];
                    if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                    if (!timpossible[by*w+bx]) { continue; }
                    r.emplace_back(Edge(y*w+x, by*w+bx, costgrid[by*w+bx]));
                }
            }
        }
        return r;
    }
    
    
    
    void hmgrid_update () {
        for (int j = 0; j < 900; ++j) { this->hmgrid[j] = false; }
        for (auto&& j : this->hms) { this->hmgrid[j.turn_end_pos()] = true; }
    }
    
    void pet_alive_update () {
        for (auto&& i : this->pts) {
            if (this->hmcnt(i.x, i.y) == 0) {
                i.alive = false;
            } else {
                i.alive = true;
            }
        }
    }
    
    vector<int> pet_alive_cnt () {
        vector<int> v(5, 0);
        for (auto&& i : this->pts) {
            if (i.alive) { v[i.pt - 1] += 1; }
        }
        return v;
    }
    
    
    vector<int> liney;
    vector<int> linewells;
    vector<int> ilinewells;
    vector<int> lp;
    vector<int> rp;
    
    int lefthome = 0;
    int righthome = 0;
    int lefthomecnt = 0;
    int righthomecnt = 0;
    int L = 5;
    
    string gamestate = "wall";
    
    
    void initline () {
        
        for (int y = 0; y < 30; ++y) {
            int l = 0;
            int r = 29;
            if (ngrid[y*30+l] == 3) { this->lp.emplace_back(y*30+l); }
            if (ngrid[y*30+r] == 3) { this->rp.emplace_back(y*30+r); }
            if (ngrid[y*30+l] == 3) { this->liney.emplace_back(y); }
        }
        this->L = this->liney.size();
        
        vector<int> vlines;
        for (int x = 0; x < 30; ++x) {
            int cnt = 0;
            for (int y = 0; y < 30; ++y) {
                if (ngrid[y*30+x] == 0) { cnt += 1; }
                
            }
            if (cnt >= 26) { vlines.emplace_back(x); }
        }
        this->lefthome  = vlines[0];
        this->righthome = vlines[1];
        
    }
    
    
    vector< vector<int> > hlv = vector< vector<int> >(7);
    void inithline () {
        
        for (int z = 0; z < this->L; ++z) {
            int y = this->lp[z] / 30;
            for (int i = 0; i < 30; ++i) {
                int u = (y-1) * 30 + i;
                int uu = (y-2) * 30 + i;
                int d = (y+1) * 30 + i;
                int dd = (y+2) * 30 + i;
                if (y-1 >= 0 && ngrid[u] == 1) { this->hlv[z].emplace_back(u); }
                if (y-2 >= 0 && ngrid[uu] == 1) { this->hlv[z].emplace_back(uu); }
                if (y+1 < 30 && ngrid[d] == 1) { this->hlv[z].emplace_back(d); }
                if (y+2 < 30 && ngrid[dd] == 1) { this->hlv[z].emplace_back(dd); }
                
                y += yy[i];
            }
        }
        
    }
    int hlinecnt (int line) {
        int cnt = 0;
        
        for (auto&& i : this->hlv[line]) {
            if (this->impossible[i]) { cnt += 1; }
        }
        
        return this->hlv[line].size()-cnt;
    }
    
    
    int near_mdist_free_hm (int p) {
        int x = p % 30;
        int y = p / 30;
        int bestdist = 10000;
        int best = -1;
        for (int i = 0; i < this->M; ++i) {
            HM& hm = this->hms[i];
            if (hm.task != "wait") { continue; }
            int dist = abs(hm.x-x) + abs(hm.y-y);
            if (dist < bestdist) {
                bestdist = dist;
                best = i;
            }
        }
        return best;
    }
    
    
    void lr_put_move (HM& hm) {
        if (hm.task != "rightmove" && hm.task != "leftmove") { return; }
        
        if (hm.c != '.') { return; }
        
        this->pet_block_put2(hm);
        if (hm.c != '.') { return; }
        
        
        
        int u = (hm.y-1)*30+hm.x;
        int d = (hm.y+1)*30+hm.x;
        int l = (hm.y)*30+hm.x-1;
        int r = (hm.y)*30+hm.x+1;
        bool bu = ngrid[u] == 1 && !this->impossible[u];
        bool bd = ngrid[d] == 1 && !this->impossible[d];
        if (bu && this->isput(hm.x, hm.y-1)) {
            hm.c = 'u';
            return;
        }
        if (bd && this->isput(hm.x, hm.y+1)) {
            hm.c = 'd';
            return;
        }
        if (bu && !this->isput(hm.x, hm.y-1)) { return; }
        if (bd && !this->isput(hm.x, hm.y+1)) { return; }
        
        
        
        int p;
        bool b;
        // up
        p = (hm.y-2)*30+hm.x;
        b = this->isinside(hm.x, (hm.y-2)) && ngrid[p] == 1 && !this->impossible[p];
        if (b &&this->ismove(p%30, p/30)) { hm.c = 'U'; return; }
        
        // down
        p = (hm.y+2)*30+hm.x;
        b = this->isinside(hm.x, (hm.y+2)) && ngrid[p] == 1 && !this->impossible[p];
        if (b &&this->ismove(p%30, p/30)) { hm.c = 'D'; return; }
        
        
        
        
        if (bu == false && bd == false && hm.task == "rightmove" && hm.x < 29) {
            if (this->ismove(hm.x+1, hm.y) && (ngrid[r] == 0 || ngrid[r] == 3)) {
                hm.c = 'R';
                return;
            }
        }
        if (bu == false && bd == false && hm.task == "leftmove" && hm.x > 0) {
            if (this->ismove(hm.x-1, hm.y) && (ngrid[l] == 0 || ngrid[l] == 3)) {
                hm.c = 'L';
                return;
            }
        }
        
        
        if (this->impossible[u]) {
            if (this->ismove(hm.x, hm.y+1) && (ngrid[d] == 0 || ngrid[d] == 3)) {
                hm.c = 'D';
                return;
            }
        }
        if (this->impossible[d]) {
            if (this->ismove(hm.x, hm.y-1) && (ngrid[u] == 0 || ngrid[u] == 3)) {
                hm.c = 'U';
                return;
            }
        }
        
        
    }
    
    vector<Edge> grid_to_graph_line () {
        static bitset<900> timpossible;
        static array<int, 900> costgrid;
        vector<Edge> r;
        int h = 30;
        int w = 30;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                timpossible[y*w+x] = this->ismove(x, y);
                costgrid[y*w+x] = 1;
            }
        }
        
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                for (int i = 0; i < 4; ++i) {
                    int bx = x + dx[i];
                    int by = y + dy[i];
                    if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                    if (!timpossible[by*w+bx]) { continue; }
                    r.emplace_back(Edge(y*w+x, by*w+bx, costgrid[by*w+bx]));
                }
            }
        }
        return r;
    }
    
    int y_to_lineindex (int y) {
        for (int i = 0; i < this->L; ++i) {
            if (this->liney[i] == y) { return i; }
        }
        return -1;
    }
    
    void linepos_setpath (HM& hm) {
        if (hm.task != "rightmove setpath" && hm.task != "leftmove setpath") { return; }
        vector<Edge> e = this->grid_to_graph_line();
        GraphDijkstra g(905, e, false);
        g.calcPath(hm.y*30+hm.x, hm.taskv1);
        this->hm_set_path(g.path, hm);
        if (hm.task == "rightmove setpath") { hm.task = "rightmove pathmove"; }
        if (hm.task == "leftmove setpath") { hm.task = "leftmove pathmove"; }
    }
    
    void linepos_re_setpath (HM& hm) {
        if (hm.task != "rightmove pathmove" && hm.task != "leftmove pathmove") { return; }
        if (hm.path.size() > 0) { return; }
        if (hm.taskv1 < 0) { return; }
        vector<Edge> e = this->grid_to_graph_line();
        GraphDijkstra g(905, e, false);
        g.calcPath(hm.y*30+hm.x, hm.taskv1);
        this->hm_set_path(g.path, hm);
    }
    
    void task_check (HM& hm) {
        if (hm.task == "rightmove pathmove") {
            int p = hm.y * 30 + hm.x;
            if (hm.taskv1 == p) {
                hm.taskv1 = -1;
                hm.task = "rightmove";
            }
        }
        if (hm.task == "leftmove pathmove") {
            int p = hm.y * 30 + hm.x;
            if (hm.taskv1 == p) {
                hm.taskv1 = -1;
                hm.task = "leftmove";
            }
        }
        if ((hm.task == "leftmove" || hm.task == "rightmove") && this->hlinecnt(hm.taskv2) == 0) {
            this->set_home(hm);
        }
        
        
        
        if (hm.task == "homemove") {
            this->path_check(hm);
            if (hm.y*30+hm.x != hm.taskv1 && hm.path.size() == 0) {
                this->set_home_re(hm);
            }
            
            if (hm.y*30+hm.x == hm.taskv1) { this->set_homedire(hm); }
            return;
        }
        
        
    }
    
    void set_home (HM& hm) {
        hm.task = "homemove";
        // if (this->lefthomecnt == this->righthomecnt) {
        //     ///////////
        // } else 
        
        if (this->righthomecnt+this->lefthomecnt < 2 || (this->righthomecnt+this->lefthomecnt == this->M-1 && this->M%2 == 1) || this->righthomecnt == this->lefthomecnt) {
            int rdist = abs(this->righthome-hm.x);
            int ldist = abs(this->lefthome-hm.x);
            
            if (rdist < ldist) {
                hm.taskv1 = min(max(hm.y, 1), 28)*30+this->righthome;
                
                vector<Edge> e = this->grid_to_graph_line();
                GraphDijkstra g(905, e, false);
                g.calcPath(hm.y*30+hm.x, hm.taskv1);
                this->hm_set_path(g.path, hm);
                
                hm.taskv2 = this->righthomecnt+this->lefthomecnt;
                
                this->righthomecnt += 1;
            } else {
                hm.taskv1 = min(max(hm.y, 1), 28)*30+this->lefthome;
                
                vector<Edge> e = this->grid_to_graph_line();
                GraphDijkstra g(905, e, false);
                g.calcPath(hm.y*30+hm.x, hm.taskv1);
                this->hm_set_path(g.path, hm);
                
                hm.taskv2 = this->righthomecnt+this->lefthomecnt;
                this->lefthomecnt += 1;
            }
            
            return;
        }
        
        
        
        
        if (this->lefthomecnt > this->righthomecnt) {
            hm.taskv1 = min(max(hm.y, 1), 28)*30+this->righthome;
            
            vector<Edge> e = this->grid_to_graph_line();
            GraphDijkstra g(905, e, false);
            g.calcPath(hm.y*30+hm.x, hm.taskv1);
            this->hm_set_path(g.path, hm);
            
            hm.taskv2 = this->righthomecnt+this->lefthomecnt;
            
            this->righthomecnt += 1;
        } else {
            hm.taskv1 = min(max(hm.y, 1), 28)*30+this->lefthome;
            
            vector<Edge> e = this->grid_to_graph_line();
            GraphDijkstra g(905, e, false);
            g.calcPath(hm.y*30+hm.x, hm.taskv1);
            this->hm_set_path(g.path, hm);
            
            hm.taskv2 = this->righthomecnt+this->lefthomecnt;
            this->lefthomecnt += 1;
        }
    }
    
    void set_home_re (HM& hm) {
        vector<Edge> e = this->grid_to_graph_line();
        GraphDijkstra g(905, e, false);
        g.calcPath(hm.y*30+hm.x, hm.taskv1);
        this->hm_set_path(g.path, hm);
    }
    
    
    int all_line_cnt () {
        int r = 0;
        for (int i = 0; i < this->L; ++i) {
            r += this->hlinecnt(i);
        }
        return r;
    }
    bool ismove_c (HM& hm, char c) {
        int x = hm.x;
        int y = hm.y;
        if (c == 'U') { y -= 1; }
        if (c == 'D') { y += 1; }
        if (c == 'L') { x -= 1; }
        if (c == 'R') { x += 1; }
        
        if (this->isoutside(x, y)) { return false; }
        
        for (auto&& i : this->hms) {
            if (i.movecollision(x, y)) { return false; }
        }
        return !this->impossible[y*30+x];
    }
    
    void set_homedire (HM& hm) {
        hm.taskv1 = -1;
        if (hm.y > 15) {
            hm.task = "homedown";
        } else {
            hm.task = "homeup";
        }
    }
    
    void pet_block_put2 (HM& hm) {
        if (hm.c != '.') { return; }
        const int x = hm.x;
        const int y = hm.y;
        int bestcnt = this->zero_hm_cnt();
        int best = -1;
        int ac = this->areacnt(x, y) * 0.5;
        for (int d = 1; d < 4; d += 2) {
            int px = x + dx[d];
            int py = y + dy[d];
            int p = py*30+px;
            if (px == this->lefthome || px == this->righthome) { continue; }
            if (this->isoutside(px, py)) { continue; }
            if (ngrid[p] != 0) { continue; }
            if (!this->isput(px, py)) { continue; }
            if (this->impossible[p] == 1) { continue; }
            
            this->impossible[p] = true;
            int cnt = this->zero_hm_cnt();
            int nac = this->areacnt(x, y);
            if (nac > ac && cnt > bestcnt) {
                bestcnt = cnt;
                best = d;
            }
            this->impossible[p] = false;
        }
        
        if (best == 0) { hm.c = 'u'; }
        if (best == 1) { hm.c = 'r'; }
        if (best == 2) { hm.c = 'd'; }
        if (best == 3) { hm.c = 'l'; }
    }
    
    void home_move (HM& hm) {
        if (hm.task != "homedown" && hm.task != "homeup" && hm.task != "homelink") { return; }
        
        this->pet_block_put2(hm);
        if (hm.c != '.') { return; }
        
        for (int d = 0; d < 4; ++d) {
            int x = hm.x + dx[d];
            int y = hm.y + dy[d];
            int p = y * 30 + x;
            if (this->isoutside(x, y)) { continue; }
            if (!this->impossible[p] && ngrid[p] == 4 && this->isput(x, y)) {
                if (d == 0) { hm.c = 'u'; }
                if (d == 1) { hm.c = 'r'; }
                if (d == 2) { hm.c = 'd'; }
                if (d == 3) { hm.c = 'l'; }
                return;
            }
        }
        
        
        
        if (hm.task == "homedown") {
            if (this->ismove_c(hm, 'D')) {
                hm.c = 'D';
            } else {
                hm.task = "homeup";
                hm.c = 'U';
            }
            return;
        }
        if (hm.task == "homeup") {
            if (this->ismove_c(hm, 'U')) {
                hm.c = 'U';
            } else {
                hm.task = "homedown";
                hm.c = 'D';
            }
            return;
        }
    }
    
    bool is2blockput (int y, int a, int b) {
        int tcnt = this->zero_hm_cnt();
        int tac = this->areacnt(a-1, y) * 0.75;
        
        this->impossible[y*30+a] = true;
        this->impossible[y*30+b] = true;
        
        int ncnt = this->zero_hm_cnt();
        int nac = this->areacnt(a-1, y);
        
        
        this->impossible[y*30+a] = false;
        this->impossible[y*30+b] = false;
        
        if (nac > tac && ncnt > tcnt) { return true; }
        return false;
    }
    
    
    vector<int> center_pet_line;
    void update_center_pet_line () {
        this->center_pet_line.clear();
        for (int y = 0; y < 30; ++y) {
            int a = this->lefthome+1;
            int b = this->righthome-1;
            if (this->isput(a, y) && this->isput(b, y)) {
                if (this->is2blockput(y, a, b)) { this->center_pet_line.emplace_back(y); }
            }
        }
    }
    
    void put_apply (HM& hm) {
        if (hm.c == 'l') { this->impossible[(hm.y)*30+hm.x-1] = true; }
        if (hm.c == 'r') { this->impossible[(hm.y)*30+hm.x+1] = true; }
        if (hm.c == 'u') { this->impossible[(hm.y-1)*30+hm.x] = true; }
        if (hm.c == 'd') { this->impossible[(hm.y+1)*30+hm.x] = true; }
    }
    
    void link_pet_block_put () {
        for (auto&& y : this->center_pet_line) {
            int ahm = -1;
            int bhm = -1;
            
            for (int i = 0; i < this->M; ++i) {
                if (this->hms[i].x == this->lefthome && this->hms[i].y == y && this->hms[i].c == '.') { ahm = i; }
                if (this->hms[i].x == this->righthome && this->hms[i].y == y && this->hms[i].c == '.') { bhm = i; }
            }
            if (ahm == -1 || bhm == -1) { continue; }
            this->hms[ahm].c = 'r';
            this->hms[bhm].c = 'l';
            
            this->put_apply(this->hms[ahm]);
            this->put_apply(this->hms[bhm]);
            
            this->hmgrid_update();
            this->pet_alive_update();
            if (this->hms[ahm].task == "homelink") { this->set_homedire(this->hms[ahm]); }
            if (this->hms[bhm].task == "homelink") { this->set_homedire(this->hms[bhm]); }
        }
    }
    
    
    
    int dogline () {
        int best = 0;
        int bestdist = 10000;
        
        for (int y = 1; y < 29; ++y) {
            if (this->impossible[y*30+this->lefthome+1]) { continue; }
            if (this->impossible[y*30+this->lefthome+2]) { continue; }
            if (this->impossible[y*30+this->righthome-1]) { continue; }
            if (this->impossible[y*30+this->righthome-2]) { continue; }
            if (abs(15-y) < bestdist) {
                best = y;
                bestdist = abs(15-y);
            }
        }
        return best;
    }
    
    
    int calcvscore () {
        double r = 0;
        int cnt = 0;
        for (auto&& i : this->pts) {
            if (i.alive) { cnt += 1; }
        }
        
        
        for (auto&& i : this->hms) {
            int ri = this->areacnt(i.x, i.y) - 16 * 0.75 * cnt;
            int ni = 0;
            r += (ri/900.0) * pow(2.0, -ni) * 100000000 * (1.0/this->M);
        }
        return (int)r;
    }
    void lastturn_cerrout2 () {
        if (this->turn == 299) {
            pdebug("Time", this->sw.get_milli_time());
            this->hmgrid_update();
            this->pet_alive_update();
            pdebug("pet", this->pet_alive_cnt());
            pdebug(this->calcvscore());
        }
    }
    
    
    array<int, 14> minimize_sa_fixedstep (array<int, 14> v, int ecnt, double stemp = 256.0, double etemp = 0.0) {
        const double sacnt = ecnt;
        array<int, 14> bestv = v;
        double bestscore = this->start_pos_score(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
            int a = xrnd() % (this->L*2);
            int b = xrnd() % (this->L*2);
            swap(v[a], v[b]);////
            double tmpscore = this->start_pos_score(v);
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
        return bestv;
    }
    
    
    int start_pos_score (array<int, 14>& a) {
        int score = 0;
        int m = 0;
        bitset<7> f;
        int l = 0;
        int r = 0;
        
        bool lc = false;
        bool rc = false;
        
        for (int i = 0; i < this->M; ++i) {
            HM& hm = this->hms[i];
            int line = a[i] % max(this->L, 5);
            f[line] = true;
            
            if (line == 3) {
                if (a[i] / max(this->L, 5) == 0) {
                    lc = true;
                } else {
                    rc = true;
                }
                
                
            }
            
            if (a[i] / max(this->L, 5) == 0) {
                int x = this->lp[line] % 30;
                int y = this->lp[line] / 30;
                m = max(abs(x-hm.x)+abs(y-hm.y), m);
                score += abs(x-hm.x)+abs(y-hm.y);
                l += 1;
            } else {
                int x = this->rp[line] % 30;
                int y = this->rp[line] / 30;
                m = max(abs(x-hm.x)+abs(y-hm.y), m);
                score += abs(x-hm.x)+abs(y-hm.y);
                r += 1;
            }
        }
        score += m*this->M;
        // r = m;
        for (int i = 0; i < this->L; ++i) { if (!f[i]) { score += 1000; } }
        
        if (this->M >= 7) {
            if (lc == false || rc == false) { score += 1000; }
        }
        
        
        // if (abs(l - r) >= 2) { score += 2; }
        // if (abs(l - r) >= 4) { score += 2; }
        return score;
    }
    
    void initial_setlinepos () {
        array<int, 14> a;
        
        for (int i = 0; i < 14; ++i) { a[i] = i; }
        
        a = this->minimize_sa_fixedstep(a, 51260, 8, 0);
        
        for (int i = 0; i < this->M; ++i) {
            HM& hm = this->hms[i];
            int line = a[i] % max(this->L, 5);
            
            if (a[i] / max(this->L, 5) == 0) {
                hm.task = "rightmove setpath";
                hm.taskv1 = this->lp[line];
                hm.taskv2 = line;
            } else {
                hm.task = "leftmove setpath";
                hm.taskv1 = this->rp[line];
                hm.taskv2 = line;
            }
        }
    }
    
    vector<int> pet_hline;
    void update_pet_hline () {
        this->pet_hline.clear();
        for (int i = 0; i < 30; ++i) {
            int l = this->lefthome;
            int r = this->righthome;
            bool f = false;
            if (i == 0 || i == 29) { continue; }
            if (!this->impossible[i*30+l-1] && !this->impossible[i*30+l-2]) { f = true; }
            if (!this->impossible[i*30+l+1] && !this->impossible[i*30+l+2]) { f = true; }
            if (!this->impossible[i*30+r-1] && !this->impossible[i*30+r-2]) { f = true; }
            if (!this->impossible[i*30+r+1] && !this->impossible[i*30+r+2]) { f = true; }
            
            if (f) { this->pet_hline.emplace_back(i); }
        }
    }
    
    
    void link_move () {
        this->update_pet_hline();
        this->hmgrid_update();
        this->pet_alive_update();
        
        unordered_set<int> us;
        vector<int> pet_line_pos;
        
        
        
        for (auto&& i : this->pts) {
            if (!i.alive) { continue; }
            int bestdist = 1000;
            int best = -1;
            for (int z = 0; z < this->pet_hline.size(); ++z) {
                int y = this->pet_hline[z];
                //int dist = abs(y-max(min((i.y + xx[i.x]), 29), 0));
                int dist = abs(y-max(min((i.y + xx[i.x]), 29), 0)) + abs(y-i.y);
                if (dist < bestdist) {
                    bestdist = dist;
                    best = y;
                }
                
            }
            if (bestdist > -1) { us.emplace(best); }
        }
        
        for (auto&& i : us) { pet_line_pos.emplace_back(i); }
        
        if (pet_line_pos.size() == 0) { return; }
        
        vector<int> lhm;
        vector<int> rhm;
        for (int i = 0; i < this->M; ++i) {
            if (this->hms[i].c != '.') { continue; }
            if (this->hms[i].task != "homeup" && this->hms[i].task != "homedown" && this->hms[i].task != "homelink") { continue; }
            if (this->hms[i].x < 15) { lhm.emplace_back(i); }
            if (this->hms[i].x > 15) { rhm.emplace_back(i); }
        }
        
        int hcnt = min(lhm.size(), rhm.size());
        
        us.clear();
        
        for (int i = 0; i < hcnt; ++i) {
            HM& l = this->hms[lhm[i]];
            HM& r = this->hms[rhm[i]];
            int bestdist = 10000;
            int bestypos = -1;
            for (auto&& y : pet_line_pos) {
                int dist = max(l.y-y, r.y-y);
                if (dist < bestdist && us.find(y) == us.end()) {
                    bestdist = dist;
                    bestypos = y;
                }
            }
            if (bestypos > -1) {
                us.emplace(bestypos);
                if (l.y != bestypos) { l.c = l.y < bestypos ? 'D' : 'U'; }
                if (r.y != bestypos) { r.c = r.y < bestypos ? 'D' : 'U'; }
                l.task = "homelink";
                r.task = "homelink";
            }
        }
        
    }
    void link_pet_block() {
        for (int y = 0; y < 30; ++y) {
            int l = -1;
            int r = -1;
            for (int i = 0; i < this->M; ++i) {
                if (this->hms[i].c != '.') { continue; }
                if (this->hms[i].task != "homelink") { continue; }
                if (this->hms[i].y == y && this->hms[i].x < 15 && l < 0) { l = i; }
                if (this->hms[i].y == y && this->hms[i].x > 15 && r < 0) { r = i; }
            }
            
            if (l > -1 && r > -1) {
                HM& lhm = this->hms[l];
                HM& rhm = this->hms[r];
                int a = this->lefthome+1;
                int b = this->righthome-1;
                
                
                if (this->isput(a, y) && this->isput(b, y) && this->is2blockput(y, a, b)) {
                    
                    lhm.c = 'r';
                    rhm.c = 'l';
                    this->put_apply(lhm);
                    this->put_apply(rhm);
                    break;
                    
                }
            }
            
            
        }
    }
    
    void solve () {
        if (this->M >= 7 && this->dcnt >= 2) {
            this->gamestate = "sdog";
            this->set_start_tgridpath();
        } else {
            this->initline();
            this->inithline();
            this->initial_setlinepos();
            for (auto&& i : this->hms) { this->linepos_setpath(i); }
        }
        
        
        for (this->turn = 0; this->turn < 300; ++this->turn) {
            
            
            this->hmgrid_update();
            this->pet_alive_update();
            int dogcnt = this->pet_alive_cnt()[3];
            int petcnt = 0;
            for (auto&& i : this->pet_alive_cnt()) {
                petcnt += i;
            }
            
            bool isallhome = true;
            for (auto&& i : this->hms) {
                if (i.task != "homeup" && i.task != "homedown" && i.task != "homelink") { isallhome = false; }
            }
            // if (isallhome && dogcnt > 3) { this->gamestate = "dog"; }
            if (isallhome && dogcnt > 0 && petcnt == dogcnt) { this->gamestate = "dog"; }
            
            
            if (this->gamestate == "wall") {
                this->link_move();
                this->link_pet_block();
                
                this->hmgrid_update();
                this->pet_alive_update();
                for (auto&& i : this->hms) {
                    this->pet_block_put2(i);
                    this->put_apply(i);
                }
                
                
                for (auto&& i : this->hms) {
                    this->hmgrid_update();
                    this->pet_alive_update();
                    
                    this->task_check(i);
                    this->path_check(i);
                    this->linepos_re_setpath(i);
                    this->path_move(i);
                    this->lr_put_move(i);
                    this->home_move(i);
                    
                    this->put_apply(i);
                }
            }
            
            
            // if (this->gamestate == "dog") { this->gamestate = "final"; }
            
            if (this->gamestate == "dog") {
                
                int dl = this->dogline();
                int lc = 0;
                int rc = 0;
                for (auto&& i : this->hms) {
                    if (i.y < dl) { i.c = 'D'; }
                    if (i.y > dl) { i.c = 'U'; }
                    if (i.c == '.' && i.x == this->lefthome) { lc += 1; }
                    if (i.c == '.' && i.x == this->righthome) { rc += 1; }
                }
                bool f = false;
                if (this->isput(this->lefthome+1, dl) && this->isput(this->righthome-1, dl)) {
                    this->impossible[dl*30+this->lefthome+1] = true;
                    this->impossible[dl*30+this->righthome-1] = true;
                    this->pet_alive_update();
                    if (this->pet_alive_cnt()[3] == 0) { f = true; }
                    this->impossible[dl*30+this->lefthome+1] = false;
                    this->impossible[dl*30+this->righthome-1] = false;
                }
                
                if (f && lc > 0 && rc > 0) {
                    for (auto&& i : this->hms) {
                        if (i.c == '.' && i.x == this->lefthome) {
                            i.c = 'r';
                            break;
                        }
                    }
                    for (auto&& i : this->hms) {
                        if (i.c == '.' && i.x == this->righthome) {
                            i.c = 'l';
                            break;
                        }
                    }
                    for (auto&& i : this->hms) { this->put_apply(i); }
                    pdebug("de", this->turn);
                    this->gamestate = "final";
                }
            }
            
            if (this->gamestate == "final") {
                this->link_move();
                this->link_pet_block();
                
                this->hmgrid_update();
                this->pet_alive_update();
                for (auto&& i : this->hms) {
                    this->pet_block_put2(i);
                    this->put_apply(i);
                }
                
                for (auto&& i : this->hms) {
                    this->hmgrid_update();
                    this->pet_alive_update();
                    
                    this->task_check(i);
                    this->path_check(i);
                    this->linepos_re_setpath(i);
                    this->path_move(i);
                    this->lr_put_move(i);
                    this->home_move(i);
                    
                    this->put_apply(i);
                }
            }
            
            
            if (this->gamestate == "sdog") {
                this->tgridblock_put();
                this->tgridet_target_path();
                for (auto&& i : this->hms) {
                    if (this->state >= 3) { continue; }
                        this->targetflags.reset();
                        this->truetargetflags.reset();
                        this->path_check(i);
                        for (auto&& j : this->hms) {
                            if (j.path.size() > 0) {
                                this->truetargetflags[j.path[0]] = true;
                            }
                            
                            for (auto&& k : j.path) {
                                this->targetflags[k] = true;
                            }
                        }
                        
                        this->hmgrid_update();
                        this->pet_alive_update();
                        
                        if (this->state <= 3) { this->wall_put(i); }
                        this->path_move0(i);
                        
                        if (this->sw.get_milli_time() < 2800) {
                            this->set_wall_path(i);
                            this->tgridet_target_path0(i);
                            this->path_move0(i);
                        }
                        this->put_apply(i);
                }
                
                bool b = true;
                for (int i = 0; i < 900; ++i) {
                    if (!this->impossible[i] && tgrid[i] == 1) { b = false; }
                }
                if (b) {
                    if (this->state == 0) {
                        pdebug("dw", this->turn);
                        this->state = 1;
                    }
                }
                if (this->state == 3) {
                    this->gamestate = "wall";
                    this->initline();
                    this->inithline();
                    this->initial_setlinepos();
                    for (auto&& i : this->hms) { this->linepos_setpath(i); }
                }
            }
            
            
            this->lastturn_cerrout2();
            
            // output update
            string out;
            for (auto&& i : this->hms) {
                out += i.c;
                i.apply_action();
            }
            
            // input update
            cout << out << endl;
            cout.flush();
            
            for (int i = 0; i < 900; ++i) { this->petgrid[i] = 0; }
            for (auto&& i : this->pts) {
                string pta;
                cin >> pta;
                i.apply_action(pta);
                this->petgrid[i.y*30+i.x] = i.pt;
            }
        }
        
    }
    
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    MM mm;
    mm.input();
    mm.solve();
    return 0;
}

