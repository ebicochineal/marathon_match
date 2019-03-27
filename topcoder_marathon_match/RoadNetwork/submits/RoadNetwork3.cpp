// C++11
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <iterator>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char *v) { return '"' + v + '"'; }
string in_v_to_str (const string v) { return '"' + v + '"'; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str();
}
template<class T, size_t N> string v_to_str (const array< array<T, N>, N > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T> &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> > &v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class T> string v_to_str (const unordered_set<T> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const unordered_map<K, V> &v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class F, class S> string in_v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
template<class F, class S> string v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
string print () { return ""; }
template<typename F, typename... R> string print (const F &f, const R &...r) { stringstream ss; ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); } return ss.str(); }
template<typename F, typename... R> void pdebug (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>" << ss.str() << "</cerr>" << endl;
}

template<typename F, typename... R> void fdebug (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerrfile>" << ss.str() << "</cerrfile>" << endl;
}

class StopWatch {
public:
    int starts;
    int startm;
    struct timeb timebuffer;
    StopWatch () {
        ftime(&this->timebuffer);
        this->starts = this->timebuffer.time;
        this->startm = this->timebuffer.millitm;
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

struct mpos {
public:
    int x;
    int y;
    mpos () { this->x = 0; this->y = 0; }
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <> class hash<mpos> {
    public:
        size_t operator()(const mpos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
    
}

struct route {
public:
    int a, b, point;
    route (int a, int b, int point) {
        this->a = a;
        this->b = b;
        this->point = point;
    }
    bool operator == (const route &t) const { return this->a == t.a && this->b == t.b; }
};
namespace std {
    template <> class hash<route> {
    public:
        size_t operator()(const route& t) const{ return hash<int>()(t.a<<16) | hash<int>()(t.b); }
    };
}

struct edge {
public:
    int a, b, cost;
    edge () {
        this->a = 0;
        this->b = 0;
        this->cost = 1000000;
    }
    edge (int a, int b, int cost) {
        this->a = a;
        this->b = b;
        this->cost = cost;
    }
    bool operator == (const edge &t) const { return this->a == t.a && this->b == t.b; }
};
namespace std {
    template <> class hash<edge> {
    public:
        size_t operator()(const edge& t) const{ return hash<int>()(t.a<<16) | hash<int>()(t.b); }
    };
}

class node {
public:
    int cost;
    int prev;
    int index;
    node (int cost, int prev, int index) {
        this->cost = cost;
        this->prev = prev;
        this->index = index;
    }
    
    bool operator > (const node &t) const { return this->cost > t.cost; }
    bool operator < (const node &t) const { return this->cost < t.cost; }
};

class graph_dijkstra {
public:
    int n;
    vector< vector< pair<int, int> > > next_cost;
    vector<int> path;
    int pathcost;
    // vector<edge> edges;
    graph_dijkstra (int n, vector<edge> edges) {
        this->pathcost = 0;
        this->path.clear();
        this->n = n;
        // this->edges = edges;
        this->next_cost = vector< vector< pair<int, int> > >(n, vector< pair<int, int> >());
        for (auto &i : edges) {
            this->next_cost[i.a].emplace_back(i.b, i.cost);
            this->next_cost[i.b].emplace_back(i.a, i.cost);
        }
    }
    
    void route (int start_i, int end_i) {
        this->pathcost = 0;
        this->path.clear();
        // priority_queue<node> que;
        vector<int> prevs(this->n, -1);
        vector<int> costs(this->n, 1000000);
        costs[start_i] = 0;
        priority_queue<node, vector<node>, greater<node> > que;
        
        for (auto &i : this->next_cost[start_i]) {
            costs[i.first] = i.second;
            prevs[i.first] = start_i;
            que.emplace(i.second, start_i, i.first);
        }
        while (!que.empty()) {
            node t = que.top();
            que.pop();
            if (t.index == end_i) {
                prevs[t.index] = t.prev;
                this->pathcost = t.cost;
                break;
            }
            for (auto &i : this->next_cost[t.index]) {
                int cost = t.cost + i.second;
                if (cost < costs[i.first]) {
                    costs[i.first] = cost;
                    prevs[i.first] = t.index;
                    que.emplace(cost, t.index, i.first);
                    
                }
            }
            
        }
        int e = end_i;
        while (e > -1) {
            this->path.emplace_back(e);
            e = prevs[e];
        }
        
    }
    
    
    
};


class RoadNetwork {
public:
    vector<edge> edges;
    unordered_map<edge, int> edges_points;
    unordered_map<mpos, int> edge_indexs;
    unordered_map<mpos, int> edge_costs;
    vector<int> edgeindex_costs;
    vector<route> routes;
    int NM;
    
    StopWatch sw;
    vector<int> findSolution (int NM, int N, int E, vector<string> edges, int R, vector<string> routes) {
        this->sw = StopWatch();
        vector<int> ret;
        this->NM = NM;
        this->edgeindex_costs = vector<int>(E, 0);
        
        unordered_set<int> xxx;
        for (auto &i : routes) {
            vector<string> temp = this->split(i, " ");
            int a = atoi(temp[0].c_str());
            int b = atoi(temp[1].c_str());
            int point = atoi(temp[2].c_str());
            if (a < b) {
                this->routes.emplace_back(a, b, point);
            } else {
                this->routes.emplace_back(b, a, point);
            }
            xxx.emplace(a);
            xxx.emplace(b);
        }
        
        int ascore = 0;
        int bscore = 0;
        
        //build connections until we run out of materials        
        for (int i = 0; i < E; i++) {
            vector<string> temp = this->split(edges[i], " ");
            int cost = atoi(temp[2].c_str());
            
            int a = atoi(temp[0].c_str());
            int b = atoi(temp[1].c_str());
            int point = atoi(temp[3].c_str());
            mpos p;
            edge e;
            if (a < b) {
                p = mpos(a, b);
                // e = edge(a, b, cost);
                e = edge(a, b, cost*10/(point+(xxx.find(a)!=xxx.end())*5+(xxx.find(b)!=xxx.end())*5));
                
            } else {
                p = mpos(b, a);
                // e = edge(b, a, cost);
                e = edge(b, a, cost*10/(point+(xxx.find(a)!=xxx.end())*5+(xxx.find(b)!=xxx.end())*5));
            }
            
            this->edges_points.emplace(e, point);
            this->edges.emplace_back(e);
            this->edge_indexs.emplace(p, i);
            this->edge_costs.emplace(p, cost);
            this->edgeindex_costs[i] = cost;
        }
        
        
        
        pdebug("NM", NM);
        // fdebug("N", N);
        // fdebug("E", E);
        // fdebug("edges", edges);
        // fdebug("R", R);
        // fdebug("routes", routes);
        // fdebug("ret", ret);
        // pdebug(ascore, bscore, ascore * bscore);
        
        auto g = graph_dijkstra(N, this->edges);
        unordered_set<int> usret;
        
        for (auto &i : this->routes) {
            g.route(i.a, i.b);
            
            int cost = this->all_cost_add(usret, this->path_to_edgeindexs(g.path));
            if (cost <= NM) {
                for (auto &j : this->path_to_edgeindexs(g.path)) {
                    usret.emplace(j);
                }
            }
        }
        
        for (int i = 0; i < E; ++i) {
            int cost = this->all_cost_add(usret, vector<int>(1, i));
            if (cost <= NM) {
                usret.emplace(i);
            }
        }
        
        pdebug("T", this->sw.get_milli_time());
        
        return this->tov(usret);
    }
    
    int all_cost (unordered_set<int> us) {
        int cost = 0;
        for (auto &i : us) { cost += this->edgeindex_costs[i]; }
        return cost;
    }
    
    int all_cost_add (unordered_set<int> us, vector<int> v) {
        int cost = 0;
        unordered_set<int> t;
        for (auto &i : v) { t.emplace(i); }
        for (auto &i : us) { t.emplace(i); }
        for (auto &i : t) { cost += this->edgeindex_costs[i]; }
        return cost;
    }
    
    
    vector<int> tov (unordered_set<int> &us) {
        vector<int> r;
        for (auto &i : us) { r.emplace_back(i); }
        return r;
    }
    
    
    vector<string> split (string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr (pos_start));
        return res;
    }
    
    vector<int> path_to_edgeindexs (vector<int> path) {
        vector<int> r;
        for (int i = 0; i < path.size()-1; ++i) {
            int a = path[i];
            int b = path[i+1];
            mpos p;
            if (a < b) {
                p = mpos(a, b);
            } else {
                p = mpos(b, a);
            }
            r.push_back(this->edge_indexs[p]);
        }
        return r;
    }
    
    
};


// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v, int num) {
    T a;
    std::getline(std::cin, a);      //skip the first one
    for (int i = 0; i < num; ++i) {
        std::getline(std::cin, a);
        v.push_back(a);
    }
}

int main() {
    RoadNetwork rn;
    int NM;
    int N;
    int E;
    int R;
    cin >> NM;
    cin >> N;
    cin >> E;
    vector<string> edges;
    getVector(edges,E);  
    cin >> R;
    vector<string> routes;
    getVector(routes,R);

    vector<int> ret = rn.findSolution(NM,N,E,edges,R,routes);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); i++) {
        cout << ret[i] << endl;
    }
    cout.flush();
}