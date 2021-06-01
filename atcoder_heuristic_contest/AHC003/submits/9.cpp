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

vector<Edge> gridToGraph (vector< vector<int> >& grid) {
    static const int dx[4] = {0, 0, -1, 1};
    static const int dy[4] = {-1, 1, 0, 0};
    
    vector<Edge> r;
    int h = grid.size();
    int w = grid[0].size();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int ax = x;
            int ay = y;
            for (int i = 0; i < 4; ++i) {
                int bx = ax + dx[i];
                int by = ay + dy[i];
                if (bx < 0 || bx >= w || by < 0 || by >= h) { continue; }
                r.emplace_back(Edge(ay*w+ax, by*w+bx, grid[by][bx]));
            }
        }
    }
    return r;
}

inline double distance (const double& ax, const double& ay, const double& bx, const double& by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
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
    Random2optSwap (T& v, int l, int r) {
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
        const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
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
        const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
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
        const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
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
        const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
        int a = xrnd() % v.size();////
        int b = xrnd() % v.size();////
        swap(v[a], v[b]);////
        double tmpscore = calcscore(v);
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
    int sx, sy, ex, ey;
    int turn = 0;
    array<int, 1740> hvcost;
    
    MM () {
        this->sw = StopWatch();
        int v = 4200;
        
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
        
    }
    
    
    void input () {
        cin >> this->sy >> this->sx >> this->ey >> this->ex;
    }
    void input2 () {
        int p;
        cin >> p;
        this->truecosts.emplace_back(p);
        int av = p/this->out.size();
        int n = 2;
        if (this->turn > 200) { n = 4; }
        if (this->turn > 400) { n = 8; }
        if (this->turn > 600) { n = 16; }
        for (auto&& j : this->paths.back()) {
            this->hvcost[j] += (av-this->hvcost[j]) / n;
            this->hvcost[j] = max(this->hvcost[j], 1);
            this->hvcost[j] = min(this->hvcost[j], 9999);
        }
        
        this->turn += 1;
    }
    
    
    string out;
    
    
    vector< vector<int> > paths;
    vector<int> truecosts;
    
    
    void HC () {
        if (this->paths.size() == 0) { return; }
        if (this->sw.get_milli_time() < 1800) {
            int bestscore = this->all_cost_score(this->hvcost);
            auto best = this->hvcost;
            int a = this->paths.size()-1;
            for (int j = 0; j < 3; ++j) {
                for (auto&& x : this->paths[a]) {
                    int tmp = this->hvcost[x];
                    this->hvcost[x] += xrnd()%2 ? 100 : -100;
                    this->hvcost[x] = max(this->hvcost[x], 1);
                    this->hvcost[x] = min(this->hvcost[x], 9999);
                    int score = this->all_cost_score(this->hvcost);
                    if (score < bestscore) {
                        bestscore = score;
                        best[x] = this->hvcost[x];
                    } else {
                        this->hvcost[x] = tmp;
                    }
                }
            }
            for (int i = 0; i < 3; ++i) {
                int a = xrnd() % this->paths.size();
                for (int j = 0; j < 3; ++j) {
                    for (auto&& x : this->paths[a]) {
                        int tmp = this->hvcost[x];
                        this->hvcost[x] += xrnd()%2 ? 100 : -100;
                        this->hvcost[x] = max(this->hvcost[x], 1);
                        this->hvcost[x] = min(this->hvcost[x], 9999);
                        int score = this->all_cost_score(this->hvcost);
                        if (score < bestscore) {
                            bestscore = score;
                            best[x] = this->hvcost[x];
                        } else {
                            this->hvcost[x] = tmp;
                        }
                    }
                }
            }
        } else {
            int bestscore = this->all_cost_score(this->hvcost);
            auto best = this->hvcost;
            int a = this->paths.size()-1;
            for (int j = 0; j < 1; ++j) {
                for (auto&& x : this->paths[a]) {
                    int tmp = this->hvcost[x];
                    this->hvcost[x] += xrnd()%2 ? 100 : -100;
                    this->hvcost[x] = max(this->hvcost[x], 1);
                    this->hvcost[x] = min(this->hvcost[x], 9999);
                    int score = this->all_cost_score(this->hvcost);
                    if (score < bestscore) {
                        bestscore = score;
                        best[x] = this->hvcost[x];
                    } else {
                        this->hvcost[x] = tmp;
                    }
                }
            }
            for (int i = 0; i < 1; ++i) {
                int a = xrnd() % this->paths.size();
                for (int j = 0; j < 2; ++j) {
                    for (auto&& x : this->paths[a]) {
                        int tmp = this->hvcost[x];
                        this->hvcost[x] += xrnd()%2 ? 100 : -100;
                        this->hvcost[x] = max(this->hvcost[x], 1);
                        this->hvcost[x] = min(this->hvcost[x], 9999);
                        int score = this->all_cost_score(this->hvcost);
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
        
    }
    
    void output () {
        string s;
        int x = this->sx;
        int y = this->sy;
        
        
        this->HC();
        
        
        vector<int> path;
        
        
        if (this->turn >= 120) {
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
        } else {
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
        // RL
        for (int y = 0; y < b; ++y) {
            for (int x = 0; x < a; ++x) {
                int cost = hvcost[this->hvpos(0, x, y)];
                r.emplace_back(Edge(x+y*n, x+1+y*n, cost));
                r.emplace_back(Edge(x+1+y*n, x+y*n, cost));
            }
        }
        // DU
        for (int y = 0; y < a; ++y) {
            for (int x = 0; x < b; ++x) {
                int cost = hvcost[this->hvpos(1, x, y)];
                r.emplace_back(Edge(x+y*n, x+(y+1)*n, cost));
                r.emplace_back(Edge(x+(y+1)*n, x+y*n, cost));
            }
        }
        return r;
    }
    
    void calc () {}
    
    // int all_cost_score (array<int, 1740>& hvcost) {
    //     int score = 0;
    //     for (int i = 0; i < this->paths.size(); ++i) {
    //         int t = this->truecosts[i];
    //         for (int j = 0; j < this->paths[i].size(); ++j) {
    //             t -= hvcost[this->paths[i][j]];
    //         }
    //         score += abs(t);
    //     }
    //     return score;
    // }
    int all_cost_score (array<int, 1740>& hvcost) {
        int score = 0;
        for (int i = 0; i < this->paths.size(); ++i) {
            int t = 0;
            for (int j = 0; j < this->paths[i].size(); ++j) {
                t += hvcost[this->paths[i][j]];
            }
            
            if (t > this->truecosts[i] * 1.05) {
                score += abs(t-this->truecosts[i]);
            }
            if (t < this->truecosts[i] * 0.95) {
                score += abs(t-this->truecosts[i]);
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
        mm.calc();
        mm.output();
        mm.sw.stop();
        mm.input2();
        mm.sw.resume();
    }
    pdebug(mm.sw.get_milli_time());
    return 0;
}

