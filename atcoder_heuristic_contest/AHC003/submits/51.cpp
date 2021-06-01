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

class Cost2 {
public:
    
    array<int, 30> borderh;
    array<int, 30> borderv;
    
    array<int, 30> hcl;
    array<int, 30> hcr;
    array<int, 30> vcu;
    array<int, 30> vcd;
    
    Cost2 () {
        for (int i = 0; i < 30; ++i) {
            this->borderh[i] = 0;
            this->borderv[i] = 0;
            this->hcl[i] = 0;
            this->hcr[i] = 0;
            this->vcu[i] = 0;
            this->vcd[i] = 0;
        }
    }
    
    int get (int hv, int x, int y) {
        if (hv == 0) {
            if (x < this->borderh[y]) {
                return this->hcl[y];
            } else {
                return this->hcr[y];
            }
        } else {
            if (y < this->borderv[x]) {
                return this->vcu[x];
            } else {
                return this->vcd[x];
            }
        }
    }

};


class MM {
public:
    StopWatch sw;
    int sx, sy, ex, ey;
    int turn = 0;
    array<int, 1740> hvcost;
    array<int, 1740> hvcostcnt;
    
    MM () {
        this->sw = StopWatch();
        int v = 3000;
        
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 29; ++x) {
                this->hvcost[this->hvpos(0, x, y)] = v;
            }
        }
        for (int y = 0; y < 29; ++y) {
            for (int x = 0; x < 30; ++x) {
                this->hvcost[this->hvpos(1, x, y)] = v;
            }
        }
        
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 29; ++x) {
                this->hvcostcnt[this->hvpos(0, x, y)] = 0;
            }
        }
        for (int y = 0; y < 29; ++y) {
            for (int x = 0; x < 30; ++x) {
                this->hvcostcnt[this->hvpos(1, x, y)] = 0;
            }
        }
    }
    
    
    void input () {
        cin >> this->sy >> this->sx >> this->ey >> this->ex;
    }
    void input2 () {
        int p;
        cin >> p;
        this->truecosts.emplace_back(p);
        this->turn += 1;
    }
    
    
    string out;
    
    
    vector< vector<int> > paths;
    vector<int> truecosts;
    
    
    
    Cost2 co2;
    void update_cost2 () {
        int w = 4;
        
        // h
        for (int i = 0; i < 30; ++i) {
            int f = false;
            int bestborder = 0;
            int bestscore = 0;
            int besta = 5000;
            int bestb = 5000;
            for (int j = 1; j < 28; ++j) {
                int asum = 0;
                int bsum = 0;
                int acnt = 0;
                int bcnt = 0;
                // l
                for (int k = 0; k < j; ++k) {
                    if (this->hvcostcnt[this->hvpos(0, k, i)] > 0) {
                        asum += this->hvcost[this->hvpos(0, k, i)];
                        acnt += 1;
                    }
                }
                // r
                for (int k = j; k < 29; ++k) {
                    if (this->hvcostcnt[this->hvpos(0, k, i)] > 0) {
                        bsum += this->hvcost[this->hvpos(0, k, i)];
                        bcnt += 1;
                    }
                }
                if (acnt <= w || bcnt <= w) { continue; }
                asum /= acnt;
                bsum /= bcnt;
                int score = abs(asum - bsum);
                
                if (score >= bestscore) {
                    bestscore = score;
                    bestborder = j;
                    besta = asum;
                    bestb = bsum;
                    f = true;
                }
            }
            if (f) {
                this->co2.borderh[i] = bestborder;
                this->co2.hcl[i] = besta;
                this->co2.hcr[i] = bestb;
            } else {
                int t = 0;
                for (int j = 0; j < 29; ++j) {
                    if (this->hvcostcnt[this->hvpos(0, j, i)] > 0) {
                        t += this->hvcost[this->hvpos(0, j, i)];
                    } else {
                        t += 5000;
                    }
                }
                t /= 29;
                this->co2.borderh[i] = 15;
                this->co2.hcl[i] = t;
                this->co2.hcr[i] = t;
            }
            
            // if (this->turn == 999) {
            //     string s = "";
            //     for (int j = 0; j < 29; ++j) {
            //         s += to_string(this->hvcost[this->hvpos(0, j, i)]) + " ";
            //     }
            //     fdebug(i, s);
            //     fdebug(i, this->co2.borderh[i], this->co2.hcl[i], this->co2.hcr[i]);
                
                
                
                
            // }
            
            
        }
        
        // v
        for (int i = 0; i < 30; ++i) {
            int f = false;
            int bestborder = 0;
            int bestscore = 0;
            int besta = 5000;
            int bestb = 5000;
            for (int j = 1; j < 28; ++j) {
                int asum = 0;
                int bsum = 0;
                int acnt = 0;
                int bcnt = 0;
                // u
                for (int k = 0; k < j; ++k) {
                    if (this->hvcostcnt[this->hvpos(1, i, k)] > 0) {
                        asum += this->hvcost[this->hvpos(1, i, k)];
                        acnt += 1;
                    }
                }
                // d
                for (int k = j; k < 29; ++k) {
                    if (this->hvcostcnt[this->hvpos(1, i, k)] > 0) {
                        bsum += this->hvcost[this->hvpos(1, i, k)];
                        bcnt += 1;
                    }
                }
                if (acnt <= w || bcnt <= w) { continue; }
                asum /= acnt;
                bsum /= bcnt;
                int score = abs(asum - bsum);
                
                if (score >= bestscore) {
                    bestscore = score;
                    bestborder = j;
                    besta = asum;
                    bestb = bsum;
                    f = true;
                }
            }
            if (f) {
                this->co2.borderv[i] = bestborder;
                this->co2.vcu[i] = besta;
                this->co2.vcd[i] = bestb;
            } else {
                int t = 0;
                for (int j = 0; j < 29; ++j) {
                    if (this->hvcostcnt[this->hvpos(1, i, j)] > 0) {
                        t += this->hvcost[this->hvpos(1, i, j)];
                    } else {
                        t += 5000;
                    }
                }
                t /= 29;
                this->co2.borderv[i] = 15;
                this->co2.vcu[i] = t;
                this->co2.vcd[i] = t;
            }
            
            
        }
    }
    
    
    void HC () {
        if (this->paths.size() == 0) { return; }
        int v = 1000 - this->turn/2;
        
        int a1 = 2;
        int b1 = 3;
        int b2 = 2;
        if (this->turn % 8 == 0) { a1 = 3; b2 = 3; }
        if (this->sw.get_milli_time() > 1900) { return; }
        if (this->sw.get_milli_time() > 1600) { b1 = 2; }
        if (this->sw.get_milli_time() > 1750) { b1 = 1; }
        if (this->sw.get_milli_time() > 1850) { a1 = 1; b1 = 1; b2 = 2; }
        
        
        double bestscore = this->all_cost_score(this->hvcost);
        auto best = this->hvcost;
        int a = this->paths.size()-1;
        for (int j = 0; j < a1; ++j) {
            for (auto&& x : this->paths[a]) {
                int tmp = this->hvcost[x];
                this->hvcost[x] += xrnd()%2 ? v : -v;
                this->hvcost[x] = max(this->hvcost[x], 1000);
                this->hvcost[x] = min(this->hvcost[x], 9000);
                double score = this->all_cost_score(this->hvcost);
                if (score < bestscore) {
                    bestscore = score;
                    best[x] = this->hvcost[x];
                } else {
                    this->hvcost[x] = tmp;
                }
            }
        }
        if (this->paths.size() > 1) {
            for (int j = 0; j < a1; ++j) {
                for (auto&& x : this->paths[a-1]) {
                    int tmp = this->hvcost[x];
                    this->hvcost[x] += xrnd()%2 ? v : -v;
                    this->hvcost[x] = max(this->hvcost[x], 1000);
                    this->hvcost[x] = min(this->hvcost[x], 9000);
                    double score = this->all_cost_score(this->hvcost);
                    if (score < bestscore) {
                        bestscore = score;
                        best[x] = this->hvcost[x];
                    } else {
                        this->hvcost[x] = tmp;
                    }
                }
            }
        }
        for (int i = 0; i < b1-1; ++i) {
            int a = xrnd() % this->paths.size();
            for (int j = 0; j < b2; ++j) {
                for (auto&& x : this->paths[a]) {
                    int tmp = this->hvcost[x];
                    this->hvcost[x] += xrnd()%2 ? v : -v;
                    this->hvcost[x] = max(this->hvcost[x], 1000);
                    this->hvcost[x] = min(this->hvcost[x], 9000);
                    double score = this->all_cost_score(this->hvcost);
                    if (score < bestscore) {
                        bestscore = score;
                        best[x] = this->hvcost[x];
                    } else {
                        this->hvcost[x] = tmp;
                    }
                }
            }
        }
        
        
    }
    
    
    
    void output () {
        string s;
        int x = this->sx;
        int y = this->sy;
        
        if (this->paths.size()>0) {
            int p = this->truecosts.back();
            int av = p/this->paths.back().size();
            int n = 2;
            int t = 0;
            for (auto&& j : this->paths.back()) { t += this->hvcost[j]; }
            // if (t < p * 0.95 || t > p * 1.05) {
                for (auto&& j : this->paths.back()) {
                    this->hvcostcnt[j] += 1;
                    this->hvcost[j] += (av-this->hvcost[j]) / n;
                    this->hvcost[j] = max(this->hvcost[j], 1000);
                    this->hvcost[j] = min(this->hvcost[j], 9000);
                }
            // }
        }
        
        this->HC();
        this->update_cost2();
        
        
        
        vector<int> path;
        
        double zacnt = 0;
        double zbcnt = 0;
        {
            int px = x;
            int py = y;
            while (px != this->ex) {
                if (px < this->ex) {
                    zacnt += this->hvcostcnt[this->hvpos(0, px, py)] == 0 ? 1 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(0, px, py)] == 1 ? 0.5 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(0, px, py)] == 2 ? 0.25 : 0;
                    px += 1;
                }
                if (px > this->ex) {
                    zacnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 0 ? 1 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 1 ? 0.5 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 2 ? 0.25 : 0;
                    px -= 1;
                }
            }
            while (py != this->ey) {
                if (py < this->ey) {
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py)] == 0 ? 1 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py)] == 1 ? 0.5 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py)] == 2 ? 0.25 : 0;
                    py += 1;
                }
                if (py > this->ey) {
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 0 ? 1 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 1 ? 0.5 : 0;
                    zacnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 2 ? 0.25 : 0;
                    py -= 1;
                }
            }
        }
        {
            int px = x;
            int py = y;
            while (py != this->ey) {
                if (py < this->ey) {
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py)] == 0 ? 1 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py)] == 1 ? 0.5 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py)] == 2 ? 0.25 : 0;
                    py += 1;
                }
                if (py > this->ey) {
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 0 ? 1 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 1 ? 0.5 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(1, px, py-1)] == 2 ? 0.25 : 0;
                    py -= 1;
                }
            }
            while (px != this->ex) {
                if (px < this->ex) {
                    zbcnt += this->hvcostcnt[this->hvpos(0, px, py)] == 0 ? 1 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(0, px, py)] == 1 ? 0.5 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(0, px, py)] == 2 ? 0.25 : 0;
                    px += 1;
                }
                if (px > this->ex) {
                    zbcnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 0 ? 1 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 1 ? 0.5 : 0;
                    zbcnt += this->hvcostcnt[this->hvpos(0, px-1, py)] == 2 ? 0.25 : 0;
                    px -= 1;
                }
            }
        }
            
        
        
        
        int len = abs(this->sx-this->ex)+abs(this->sy-this->ey);
        int ab = abs(abs(this->sx-this->ex)-abs(this->sy-this->ey));
        bool bb = ab >= len * 0.6;
        if (this->turn < 70 || (bb && this->turn < 120 && (zacnt > len * 0.60 || zbcnt > len * 0.60)) || (bb && this->turn < 160 && (zacnt > len * 0.80 || zbcnt > len * 0.80))) {
            int acnt = 0;
            int bcnt = 0;
            {
                int px = x;
                int py = y;
                while (px != this->ex) {
                    if (px < this->ex) {
                        acnt += this->hvcostcnt[this->hvpos(0, px, py)]*this->hvcostcnt[this->hvpos(0, px, py)];
                        px += 1;
                    }
                    if (px > this->ex) {
                        acnt += this->hvcostcnt[this->hvpos(0, px-1, py)]*this->hvcostcnt[this->hvpos(0, px-1, py)];
                        px -= 1;
                    }
                }
                while (py != this->ey) {
                    if (py < this->ey) {
                        acnt += this->hvcostcnt[this->hvpos(1, px, py)]*this->hvcostcnt[this->hvpos(1, px, py)];
                        py += 1;
                    }
                    if (py > this->ey) {
                        acnt += this->hvcostcnt[this->hvpos(1, px, py-1)]*this->hvcostcnt[this->hvpos(1, px, py-1)];
                        py -= 1;
                    }
                }
            }
            {
                int px = x;
                int py = y;
                while (py != this->ey) {
                    if (py < this->ey) {
                        bcnt += this->hvcostcnt[this->hvpos(1, px, py)]*this->hvcostcnt[this->hvpos(1, px, py)];
                        py += 1;
                    }
                    if (py > this->ey) {
                        bcnt += this->hvcostcnt[this->hvpos(1, px, py-1)]*this->hvcostcnt[this->hvpos(1, px, py-1)];
                        py -= 1;
                    }
                }
                while (px != this->ex) {
                    if (px < this->ex) {
                        bcnt += this->hvcostcnt[this->hvpos(0, px, py)]*this->hvcostcnt[this->hvpos(0, px, py)];
                        px += 1;
                    }
                    if (px > this->ex) {
                        bcnt += this->hvcostcnt[this->hvpos(0, px-1, py)]*this->hvcostcnt[this->hvpos(0, px-1, py)];
                        px -= 1;
                    }
                }
            }
            
            if (acnt < bcnt) {
                while (x != this->ex) {
                    if (x < this->ex) {
                        path.emplace_back(this->hvpos(0, x, y));
                        s += "R";
                        x += 1;
                    }
                    if (x > this->ex) {
                        path.emplace_back(this->hvpos(0, x-1, y));
                        s += "L";
                        x -= 1;
                    }
                }
                while (y != this->ey) {
                    if (y < this->ey) {
                        path.emplace_back(this->hvpos(1, x, y));
                        s += "D";
                        y += 1;
                    }
                    if (y > this->ey) {
                        path.emplace_back(this->hvpos(1, x, y-1));
                        s += "U";
                        y -= 1;
                    }
                }
            } else {
                while (y != this->ey) {
                    if (y < this->ey) {
                        path.emplace_back(this->hvpos(1, x, y));
                        s += "D";
                        y += 1;
                    }
                    if (y > this->ey) {
                        path.emplace_back(this->hvpos(1, x, y-1));
                        s += "U";
                        y -= 1;
                    }
                }
                while (x != this->ex) {
                    if (x < this->ex) {
                        path.emplace_back(this->hvpos(0, x, y));
                        s += "R";
                        x += 1;
                    }
                    if (x > this->ex) {
                        path.emplace_back(this->hvpos(0, x-1, y));
                        s += "L";
                        x -= 1;
                    }
                }
            }
        } else {
            vector<Edge> v = this->vedge(this->hvcost);
            GraphDijkstra g(v, false);
            g.calcPath(this->sx+this->sy*30, this->ex+this->ey*30);
            // fdebug(g.path);
            
            for (int i = 0; i < g.path.size()-1; ++i) {
                int a = g.path[i];
                int b = g.path[i+1];
                int ax = a % 30;
                int ay = a / 30;
                int bx = b % 30;
                int by = b / 30;
                if (ax < bx) {
                    path.emplace_back(this->hvpos(0, ax, ay));
                    s += "R";
                }
                if (ax > bx) {
                    path.emplace_back(this->hvpos(0, ax-1, ay));
                    s += "L";
                }
                if (ay < by) {
                    path.emplace_back(this->hvpos(1, ax, ay));
                    s += "D";
                }
                if (ay > by) {
                    path.emplace_back(this->hvpos(1, ax, ay-1));
                    s += "U";
                }
            }
        }
        
        this->paths.emplace_back(path);
        
        
        cout << s << endl;
        
        cout.flush();
        this->out = s;
    }
    
    // h = 0, v = 1
    int hvpos (int hv, int x, int y) {
        return 870*hv + x + y * (29+hv);
    }
    
    
    vector<Edge> vedge (array<int, 1740>& hvcost) {
        vector<Edge> r;
        int a = 29;
        int b = 30;
        int n = 30;
        
        int m = 10;
        
        int xx = 1;
        // LR
        for (int y = 0; y < b; ++y) {
            for (int x = 0; x < a; ++x) {
                int cost = hvcost[this->hvpos(0, x, y)];
                double d = 1;
                
                cost += hvcost[this->hvpos(0, x, y)] * (this->hvcostcnt[this->hvpos(0, x, y)]/8);
                d += (this->hvcostcnt[this->hvpos(0, x, y)]/8);
                
                
                cost += this->co2.get(0, x, y) * xx;
                d += xx;
                
                for (int i = 0; i < m; ++i) {
                    int g = i + 1;
                    if (x > i) {
                        int p = this->hvpos(0, x-g, y);
                        int u = this->hvcostcnt[p];
                        if (u > 0) {
                            cost += hvcost[p] / (i*0.5+1) * this->costv(u);
                            d += (1.0 / (i*0.5+1) * this->costv(u));
                        }
                    } else {
                        break;
                    }
                    
                }
                for (int i = 0; i < m; ++i) {
                    int g = i + 1;
                    if (x < a-g) {
                        int p = this->hvpos(0, x+g, y);
                        int u = this->hvcostcnt[p];
                        if (u > 0) {
                            cost += hvcost[p] / (i*0.5+1) * this->costv(u);
                            d += (1.0 / (i*0.5+1) * this->costv(u));
                        }
                    } else {
                        break;
                    }
                }
                r.emplace_back(Edge(x+y*n, x+1+y*n, cost/d));
                r.emplace_back(Edge(x+1+y*n, x+y*n, cost/d));
            }
        }
        // UD
        for (int y = 0; y < a; ++y) {
            for (int x = 0; x < b; ++x) {
                int cost = hvcost[this->hvpos(1, x, y)];
                double d = 1;
                
                cost += hvcost[this->hvpos(1, x, y)] * (this->hvcostcnt[this->hvpos(1, x, y)]/8);
                d += (this->hvcostcnt[this->hvpos(1, x, y)]/8);
                
                cost += this->co2.get(1, x, y) * xx;
                d += xx;
                
                for (int i = 0; i < m; ++i) {
                    int g = i + 1;
                    if (y > i) {
                        int p = this->hvpos(1, x, y-g);
                        int u = this->hvcostcnt[p];
                        if (u > 0) {
                            cost += hvcost[p] / (i*0.5+1) * this->costv(u);
                            d += (1.0 / (i*0.5+1) * this->costv(u));
                        }
                    } else {
                        break;
                    }
                }
                for (int i = 0; i < m; ++i) {
                    int g = i + 1;
                    if (y < a-g) {
                        int p = this->hvpos(1, x, y+g);
                        int u = this->hvcostcnt[p];
                        if (u > 0) {
                            cost += hvcost[p] / (i*0.5+1) * this->costv(u);
                            d += (1.0 / (i*0.5+1) * this->costv(u));
                        }
                    } else {
                        break;
                    }
                }
                r.emplace_back(Edge(x+y*n, x+(y+1)*n, cost/d));
                r.emplace_back(Edge(x+(y+1)*n, x+y*n, cost/d));
            }
        }
        return r;
    }
    
    double costv (int v) {
        return min(v * 0.1 + 0.3, 1.5);
    }
    
    double turnd () {
        return this->turn / 1000.0;
    }
    
    double all_cost_score (array<int, 1740>& hvcost) {
        double e = this->turnd();
        double score = 0;
        for (int i = 0; i < this->paths.size(); ++i) {
            int t = 0;
            for (int j = 0; j < this->paths[i].size(); ++j) {
                t += hvcost[this->paths[i][j]];
            }
            double d = abs(t - this->truecosts[i]);
            double v = this->truecosts[i] * 0.01;
            double f = d / v;
            if (f > 5 - e) {
                score += ((f - 2.5 - e) * (f - 2.5 - e));
            }
        }
        return score;
    }
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    for (int i = 0; i < 1000; ++i) {
        mm.sw.stop();
        mm.input();
        mm.sw.resume();
        mm.output();
        mm.sw.stop();
        mm.input2();
        mm.sw.resume();
    }
    pdebug(mm.sw.get_milli_time());
    return 0;
}
