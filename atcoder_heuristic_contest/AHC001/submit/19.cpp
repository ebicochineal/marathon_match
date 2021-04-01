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
inline double distance (const int& ax, const int& ay, const int& bx, const int& by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline float distance (const e512pos& a, const e512pos& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

class RectXYR {
public:
    int x, y, z;
    int l = -1;
    int r = -1;
    int u = -1;
    int d = -1;
    RectXYR () {}
    RectXYR (int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    RectXYR (int x, int y, int z, int l, int r, int u, int d) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->l = l;
        this->r = r;
        this->u = u;
        this->d = d;
    }
    
    int area () {
        return (this->r-this->l) * (this->d -this->u);
    }
    
};

class MM {
public:
    StopWatch sw;
    int N;
    int SD;
    vector<RectXYR> rects;
    MM () {
        this->sw = StopWatch();
        this->input();
        // vector<RectXYR> initrects = this->initial_solution(this->rects);
        // int64_t bestscore = this->all_score(initrects);
        // this->rects = initrects;
        this->rects = this->SA0(500, this->rects, 0.5);
        this->rects = this->SA0(500, this->rects, 0.75);
        this->rects = this->SA0(500, this->rects, 0.95);
        this->rects = this->SA0(3400, this->rects, 0.98);
        this->rects = this->SA(50, this->rects);
        
        pdebug(this->sw.get_milli_time());
        
        
        this->output();
    }
    vector<RectXYR> SA0 (int limit, vector<RectXYR> ret, float v) {
        StopWatch sw;
        
        vector<RectXYR> bestret = ret;
        double bestscore = this->all_score(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        vector<RectXYR> tret;
        int cnt = 0;
        int lcnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            // {
            //     tret = ret;
            //     for (int i = 0; i < 8; ++i) {
            //         int p = xrnd() % this->N;
            //         ret[p].l = ret[p].x;
            //         ret[p].r = ret[p].x+1;
            //         ret[p].u = ret[p].y;
            //         ret[p].d = ret[p].y+1;
            //     }
            //     this->initial_solution_v(ret, v);
                
            //     double tmpscore = this->all_score(ret);
                
            //     const double T = saTimeEnd-saTimeStart;
            //     const double t = saTimeCurrent-saTimeStart;
            //     const double startTemp   = 512600.0;
            //     const double endTemp     = 0.0;
            //     const double temp        = startTemp + (endTemp - startTemp) * t / T;
            //     const double probability = exp((tmpscore - lastscore) / temp);
            //     const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
            //     if (tmpscore > lastscore || FORCE_NEXT) {
            //         lastscore = tmpscore;
            //         if (tmpscore > bestscore) {
            //             bestscore = tmpscore;
            //             bestret = ret;
            //             cnt = 0;
            //         }
            //     } else {
            //         ret = tret;
            //     }
                
            //     cnt += 1;
            //     if (cnt > 100) {
            //         ret = bestret;
            //         cnt = 0;
            //     }
            //     lcnt += 1;
            // }
            {
                tret = ret;
                double minscore = 2.0;
                int minindex = xrnd() % this->N;
                // for (int i = 0; i < this->N; ++i) {
                //     double tscore = this->score(ret[i]);
                //     if (tscore < minscore) {
                //         minscore = tscore;
                //         minindex = i;
                //     }
                // }
                
                auto vv = testindex(ret, minindex);
                
                ret[minindex].l = ret[minindex].x;
                ret[minindex].r = ret[minindex].x+1;
                ret[minindex].u = ret[minindex].y;
                ret[minindex].d = ret[minindex].y+1;
                
                for (auto&& i : vv) {
                    ret[i].l = ret[i].x;
                    ret[i].r = ret[i].x+1;
                    ret[i].u = ret[i].y;
                    ret[i].d = ret[i].y+1;
                }
                for (int i = 0; i < 4; ++i) {
                    int p = xrnd() % this->N;
                    ret[p].l = ret[p].x;
                    ret[p].r = ret[p].x+1;
                    ret[p].u = ret[p].y;
                    ret[p].d = ret[p].y+1;
                }
                
                this->initial_solution_v(ret, v);
                
                double tmpscore = this->all_score(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 512600.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        cnt = 0;
                    }
                } else {
                    ret = tret;
                }
                
                // cnt += 1;
                // if (cnt > 100) {
                //     ret = bestret;
                //     cnt = 0;
                // }
                // lcnt += 1;
            }
            
            
        }
        pdebug(lcnt);
        return bestret;
    }
    vector<RectXYR> SA (int limit, vector<RectXYR> ret) {
        StopWatch sw;
        
        vector<RectXYR> bestret = ret;
        double bestscore = this->all_score(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        vector<RectXYR> tret;
        int cnt = 0;
        int lcnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            tret = ret;
            for (int i = 0; i < 8; ++i) {
                int p = xrnd() % this->N;
                ret[p].l = ret[p].x;
                ret[p].r = ret[p].x+1;
                ret[p].u = ret[p].y;
                ret[p].d = ret[p].y+1;
            }
            this->initial_solution(ret);
            
            double tmpscore = this->all_score(ret);
            
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            const double startTemp   = 512600.0;
            const double endTemp     = 0.0;
            const double temp        = startTemp + (endTemp - startTemp) * t / T;
            const double probability = exp((tmpscore - lastscore) / temp);
            const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore > lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore > bestscore) {
                    bestscore = tmpscore;
                    bestret = ret;
                    cnt = 0;
                }
            } else {
                ret = tret;
            }
            
            cnt += 1;
            if (cnt > 100) {
                ret = bestret;
                cnt = 0;
            }
            lcnt += 1;
        }
        pdebug(lcnt);
        return bestret;
    }
    
    
    void initial_solution_v (vector<RectXYR>& rects, float v) {
        this->expand_v(rects, 100, 120, v);
        this->expand_v(rects, 10, 60, v);
        this->expand_v(rects, 1, 60, v);
    }
    void initial_solution (vector<RectXYR>& rects) {
        this->expand(rects, 100, 120);
        this->expand(rects, 10, 60);
        this->expand(rects, 1, 60);
    }
    
    void expand_v (vector<RectXYR>& rects, int w, int loop, float v) {
        const int s = 0 + w;
        const int e = 10000 - w;
        for (int j = 0; j < loop; ++j) {
            for (int i = 0; i < this->N; ++i) {
                RectXYR& r = rects[i];
                int x = xrnd() % 4;
                const int t = r.z*v;
                if (r.area() >= t) { continue; }
                if (x == 0 && r.l >= s) {
                    r.l -= w;
                    if (r.area() > t || this->test(rects, i)) { r.l += w; }
                } else if (x == 1 && r.r <= e) {
                    r.r += w;
                    if (r.area() > t || this->test(rects, i)) { r.r -= w; }
                } else if (x == 2 && r.u >= s) {
                    r.u -= w;
                    if (r.area() > t || this->test(rects, i)) { r.u += w; }
                } else if (x == 3 && r.d <= e) {
                    r.d += w;
                    if (r.area() > t || this->test(rects, i)) { r.d -= w; }
                }
            }
        }
    }
    void expand (vector<RectXYR>& rects, int w, int loop) {
        const int s = 0 + w;
        const int e = 10000 - w;
        for (int j = 0; j < loop; ++j) {
            for (int i = 0; i < this->N; ++i) {
                RectXYR& r = rects[i];
                int x = xrnd() % 4;
                if (r.area() >= r.z) { continue; }
                if (x == 0 && r.l >= s) {
                    r.l -= w;
                    if (r.area() > r.z || this->test(rects, i)) { r.l += w; }
                } else if (x == 1 && r.r <= e) {
                    r.r += w;
                    if (r.area() > r.z || this->test(rects, i)) { r.r -= w; }
                } else if (x == 2 && r.u >= s) {
                    r.u -= w;
                    if (r.area() > r.z || this->test(rects, i)) { r.u += w; }
                } else if (x == 3 && r.d <= e) {
                    r.d += w;
                    if (r.area() > r.z || this->test(rects, i)) { r.d -= w; }
                }
            }
        }
    }
    
    
    bool test (vector<RectXYR>& rects, int t) {
        for (int i = 0; i < this->N; ++i) {
            if (i != t && this->aabb1(rects[t], rects[i])) { return true; }
        }
        return false;
    }
    
    vector<int> testindex (vector<RectXYR>& rects, int t) {
        RectXYR trect = rects[t];
        trect.l = max(trect.l-1, 0);
        trect.r = min(trect.r+1, 10000);
        trect.u = max(trect.u-1, 0);
        trect.d = min(trect.d+1, 10000);
        
        vector<int> r;
        for (int i = 0; i < this->N; ++i) {
            if (i != t && this->aabb1(trect, rects[i])) { r.emplace_back(i); }
        }
        return r;
    }
    
    
    void input () {
        cin >> this->N;
        pdebug(this->N);
        this->SD = 1000000000/this->N;
        for (int i = 0; i < this->N; ++i) {
            RectXYR r;
            cin >> r.x >> r.y >> r.z;
            r.l = r.x;
            r.r = r.x+1;
            r.u = r.y;
            r.d = r.y+1;
            this->rects.emplace_back(r);
        }
    }
    
    void output () {
        for (auto&& i : this->rects) {
            cout << print(i.l, i.u, i.r, i.d) << endl;
        }
    }
    
    int64_t all_score (vector<RectXYR>& rects) {
        double r = 0;
        for (auto&& i : rects) { r += this->score(i); }
        return (int64_t)(r * this->SD);
    }
    double score (RectXYR& r) {
        if (r.x < r.l || r.x > r.r || r.y < r.u || r.y > r.d) { return 0; }
        int s = r.area();
        double t = (1.0 - (double)min(r.z, s)/(double)max(r.z, s));
        return 1.0 - (t*t);
    }
    double score (int x, int y, int sx, int sy, int ex, int ey, int r) {
        if (x < sx || x > ex || y < sy || y > ey) { return 0; }
        int s = abs(sx-ex) * abs(sy-ey);
        double t = (1.0 - (double)min(r, s)/(double)max(r, s));
        return 1.0 - (t*t);
    }
    
    bool aabb1 (RectXYR& r1, RectXYR& r2) {
        return min(r1.r, r2.r) > max(r1.l, r2.l) && min(r1.d, r2.d) > max(r1.u, r2.u);
    }
    bool aabb2 (RectXYR& r1, RectXYR& r2) {
        if (r1.l >= r2.r) { return false; }
        if (r2.l >= r1.r) { return false; }
        if (r1.u >= r2.d) { return false; }
        if (r2.u >= r1.d) { return false; }
        return true;
    }
    
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM();
    
    return 0;
}


