// C++11
#include <random>
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
    vector<int> inda;
    vector<int> indb;
    graph_dijkstra (int n, vector<edge> edges) {
        this->pathcost = 0;
        this->path.clear();
        this->n = n;
        // this->edges = edges;
        
        this->next_cost = vector< vector< pair<int, int> > >(n, vector< pair<int, int> >());
        for (auto &i : edges) {
            this->next_cost[i.a].emplace_back(i.b, i.cost);
            this->next_cost[i.b].emplace_back(i.a, i.cost);
            this->inda.emplace_back(i.a);
            this->indb.emplace_back(this->next_cost[i.a].size()-1);
            this->inda.emplace_back(i.b);
            this->indb.emplace_back(this->next_cost[i.b].size()-1);
        }
    }
    
    void edge_update (const vector<edge> edges) {
        for (int i = 0; i < edges.size(); ++i) {
            this->next_cost[this->inda[i*2]][this->indb[i*2]].second = edges[i].cost;
            this->next_cost[this->inda[i*2+1]][this->indb[i*2+1]].second = edges[i].cost;
        }
    }
    
    void route (int start_i, int end_i) {
        this->pathcost = 0;
        this->path.clear();
        // priority_queue<node> que;
        vector<int> prevs(1000, -1);
        vector<int> costs(1000, 1000000);
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
    vector<edge> redges;
    vector<edge> edges;
    vector<edge> edges2;
    vector<edge> edges3;
    unordered_map<edge, int> edges_points;
    unordered_map<mpos, int> edge_indexs;
    unordered_map<mpos, int> edge_costs;
    vector<int> edgeindex_costs;
    vector<int> edgeindex_points;
    vector<route> routes;
    int NM, N, E, R;
    
    StopWatch sw;
    vector<int> findSolution (int NM, int N, int E, vector<string> edges, int R, vector<string> routes) {
        this->sw = StopWatch();
        vector<int> ret;
        this->NM = NM;
        this->N = N;
        this->E = E;
        this->R = R;
        this->edgeindex_costs = vector<int>(E, 0);
        this->edgeindex_points = vector<int>(E, 0);
        
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
        
        
        //build connections until we run out of materials        
        for (int i = 0; i < E; i++) {
            vector<string> temp = this->split(edges[i], " ");
            int cost = atoi(temp[2].c_str());
            
            int a = atoi(temp[0].c_str());
            int b = atoi(temp[1].c_str());
            int point = atoi(temp[3].c_str());
            mpos p;
            edge e;
            edge e2;
            edge e3;
            edge re;
            if (a < b) {
                p = mpos(a, b);
                re = edge(a, b, cost);
                e = edge(a, b, cost*100/(point+(xxx.find(a)!=xxx.end())*2+(xxx.find(b)!=xxx.end())*2));
                e2 = edge(a, b, max(cost*20/(point+(xxx.find(a)!=xxx.end())*2+(xxx.find(b)!=xxx.end())*2), 1));
                e3 = edge(a, b, max(cost*100/(point+(xxx.find(a)!=xxx.end())+(xxx.find(b)!=xxx.end())), 1));
            } else {
                p = mpos(b, a);
                re = edge(b, a, cost);
                e = edge(b, a, cost*100/(point+(xxx.find(a)!=xxx.end())*2+(xxx.find(b)!=xxx.end())*2));
                e2 = edge(b, a, max(cost*20/(point+(xxx.find(a)!=xxx.end())*2+(xxx.find(b)!=xxx.end())*2), 1));
                e3 = edge(b, a, max(cost*100/(point+(xxx.find(a)!=xxx.end())+(xxx.find(b)!=xxx.end())), 1));
            }
            
            this->edges_points.emplace(e, point);
            this->edges.emplace_back(e);
            this->edges2.emplace_back(e2);
            this->edges3.emplace_back(e3);
            this->redges.emplace_back(re);
            this->edge_indexs.emplace(p, i);
            this->edge_costs.emplace(p, cost);
            this->edgeindex_costs[i] = cost;
            this->edgeindex_points[i] = point;
        }
        
        unordered_set<int> xxx2;
        for (auto &i : this->edges) {
            if (xxx.find(i.a)!=xxx.end()) {
                xxx2.emplace(i.b);
            }
            if (xxx.find(i.b)!=xxx.end()) {
                xxx2.emplace(i.a);
            }
        }
        unordered_set<int> xxx3;
        for (auto &i : this->edges) {
            if (xxx2.find(i.a)!=xxx2.end()) {
                xxx3.emplace(i.b);
            }
            if (xxx2.find(i.b)!=xxx2.end()) {
                xxx3.emplace(i.a);
            }
        }
        unordered_set<int> xxx4;
        for (auto &i : this->edges) {
            if (xxx3.find(i.a)!=xxx3.end()) {
                xxx4.emplace(i.b);
            }
            if (xxx3.find(i.b)!=xxx3.end()) {
                xxx4.emplace(i.a);
            }
        }
        for (int i = 0; i < this->edges.size(); ++i) {
            int a = this->edges[i].a;
            int b = this->edges[i].b;
            int cost = this->edgeindex_costs[i] * 100;
            int point = this->edgeindex_points[i];
            cost = cost / (point+(xxx.find(a)!=xxx.end())*3+(xxx.find(b)!=xxx.end())*3) - ((xxx2.find(a)!=xxx2.end())*3+(xxx2.find(b)!=xxx2.end())*3) - ((xxx3.find(a)!=xxx3.end())+(xxx3.find(b)!=xxx3.end())) - ((xxx4.find(a)!=xxx4.end())+(xxx4.find(b)!=xxx4.end()));
            this->edges[i].cost = max(cost, 1);
        }
        for (int i = 0; i < this->edges.size(); ++i) {
            int a = this->edges[i].a;
            int b = this->edges[i].b;
            int cost = this->edgeindex_costs[i] * 100;
            int point = this->edgeindex_points[i];
            cost = cost / (point+(xxx.find(a)!=xxx.end())+(xxx.find(b)!=xxx.end())) - ((xxx2.find(a)!=xxx2.end())*2+(xxx2.find(b)!=xxx2.end())*2) - ((xxx3.find(a)!=xxx3.end())*1+(xxx3.find(b)!=xxx3.end())*1) - ((xxx4.find(a)!=xxx4.end())+(xxx4.find(b)!=xxx4.end()));
            this->edges3[i].cost = max(cost, 1);
        }
        
        
        
        pdebug("NM", NM, "N", N, "E", E, "R", R);
        // fdebug("N", N);
        // fdebug("E", E);
        // fdebug("edges", edges);
        // fdebug("R", R);
        // fdebug("routes", routes);
        // fdebug("ret", ret);
        // pdebug(ascore, bscore, ascore * bscore);
        
        vector< pair<int, int> > pi;
        for (int i = 0; i < E; ++i) {
            pi.emplace_back(this->edgeindex_costs[i] * 100 / this->edgeindex_points[i], i);
        }
        // sort(pi.begin(), pi.end(), [](const pair<int, int> &a, pair<int, int> &b) { return a.second < b.second; });
        sort(pi.begin(), pi.end());
        
        auto g = graph_dijkstra(N, this->edges);
        
        mt19937 mt(xrnd());
        
        int bestscore = 0;
        unordered_set<int> bestusret;
        int cnt = 0;
        int timer = 0;
        int m = 2;
        unordered_set<int> usret;
        vector<route> troutes = this->routes;
        
        vector< vector<int> > tmp_paths;
        vector< vector<int> > best_paths;
        
        bool lf = false;
        int lrn = 0;
        
        unordered_map<mpos, int> rp;
        auto rg = graph_dijkstra(N, this->redges);
        for (auto &i : this->routes) {
            g.route(i.a, i.b);
            vector<int> t = this->path_to_edgeindexs(g.path);
            int allpoint = 0;
            int allcost = 0;
            for (auto &j : t) {
                allpoint += this->edgeindex_points[j];
                allcost += this->edgeindex_costs[j];
            }
            rp.emplace(mpos(i.a, i.b), (allcost * 100) / allpoint);
            
            
        }
        
        
        
        sort(this->routes.begin(), this->routes.end(), [&rp](const route &a, const route &b) { return rp[mpos(a.a, a.b)] < rp[mpos(b.a, b.b)]; });
        // sort(this->routes.begin(), this->routes.end(), [&rp](const route &a, const route &b) { return a.point > b.point; });
        
        
        
        while (timer < 2000) {
            if (cnt % m == 0) { timer = this->sw.get_milli_time(); }
            if (timer < 800 && cnt > 200) { m = 4; }
            if (timer < 800 && cnt > 500) { m = 8; }
            if (timer < 800 && cnt > 1000) { m = 16; }
            if (timer < 800 && cnt > 5000) { m = 32; }
            if (timer > 9000) { m = 2; }
            if (timer > 9000 && cnt > 2000) { m = 4; }
            if (timer > 9000 && cnt > 50000) { m = 16; }
            int b = 0;
            usret.clear();
            // shuffle(this->routes.begin(), this->routes.end(), mt);
            // int tcost = 0;
            bool f = xrnd() % NM == 0;
            int rn = xrnd() % 6;
            
            tmp_paths.clear();
            
            for (auto &i : this->routes) {
                if (f) {
                    g.edge_update(this->update_edges(this->redges, usret));
                } else if (rn == 0) {
                    g.edge_update(this->update_edges(this->edges2, usret));
                } else if (rn == 1) {
                    g.edge_update(this->update_edges(this->edges3, usret));
                } else if (rn == 2) {
                    if (xrnd() % 4 == 0) {
                        g.edge_update(this->update_edges(this->redges, usret));
                    } else {
                        g.edge_update(this->update_edges(this->edges, usret));
                    }
                } else {
                    g.edge_update(this->update_edges(this->edges, usret));
                }
                
                g.route(i.a, i.b);
                const vector<int> path_i = this->path_to_edgeindexs(g.path);
                tmp_paths.emplace_back(path_i);
                int cost = this->all_cost_add(usret, path_i);
                if (cost <= NM) {
                    for (auto &j : path_i) { usret.emplace(j); }
                    b += i.point;
                    // tcost = cost;
                }
            }
            int cost = this->all_cost(usret);
            for (auto &w : pi) {
                int i = w.second;
                if (cost + this->edgeindex_costs[i] <= NM && usret.find(i) == usret.end()) {
                    usret.emplace(i);
                    cost += this->edgeindex_costs[i];
                }
                if (cost == NM) { break; }
            }
            int score = b * this->score_a(usret);
            
            bestscore = score;
            bestusret = usret;
            troutes = this->routes;
            lf = f;
            lrn = rn;
            best_paths = tmp_paths;
            
            cnt += 1;
            break;
        }
        this->routes = troutes;
        
        StopWatch sw;
        
        double dbestscore = 0;
        double lastscore = dbestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = 9600;
        int saTimeCurrent = saTimeStart;
        int64_t X = 1000000000;
        double xn = 1;
        
        unordered_set<route> useroutes;
        
        while (saTimeCurrent < saTimeEnd && cnt < 30000) {
            // xn = 1 + bestscore / 50000;
            if (bestscore > 50000) { xn = 2; }
            if (bestscore > 100000) { xn = 5; }
            if (bestscore > 500000) { xn = 10; }
            saTimeCurrent = timer;
            if (cnt % m == 0) { timer = this->sw.get_milli_time(); }
            if (timer < 800 && cnt > 200) { m = 4; }
            if (timer < 800 && cnt > 500) { m = 8; }
            if (timer < 800 && cnt > 1000) { m = 16; }
            if (timer < 800 && cnt > 5000) { m = 32; }
            if (timer > 9000) { m = 2; }
            if (timer > 9000 && cnt > 2000) { m = 4; }
            if (timer > 9000 && cnt > 50000) { m = 16; }
            if (timer > 9500 && cnt < 500) { m = 1; }
            int b = 0;
            usret.clear();
            // shuffle(this->routes.begin()+this->routes.size()/2, this->routes.end(), mt);
            
            int ia = xrnd() % this->routes.size();
            int ib = xrnd() % this->routes.size();
            int ic = xrnd() % this->routes.size();
            
            bool ff = xrnd() % 2 == 0;
            
            int mi = this->routes.size();
            if (ff) {
                if (ia != ib && ia != ic && ic != ib) {
                    swap(this->routes[ia], this->routes[ib]);
                    swap(this->routes[ib], this->routes[ic]);
                }
                mi = min(mi, ia);
                mi = min(mi, ib);
                mi = min(mi, ic);
            } else {
                if (ia != ib) {
                    swap(this->routes[ia], this->routes[ib]);
                }
                mi = min(mi, ia);
                mi = min(mi, ib);
            }
            
            // if (ia != ib) {
            //     swap(this->routes[ia], this->routes[ib]);
            // }
            
            // int tcost = 0;
            bool f = xrnd() % NM == 0;
            int rn = xrnd() % 6;
            
            tmp_paths.clear();
            
            // for (auto &i : this->routes) {
            vector<route> rr;
            for (int h = 0; h < this->routes.size(); ++h) {
                const route i = this->routes[h];
                
                if (timer > 4000 && useroutes.find(i) == useroutes.end()) {
                    tmp_paths.emplace_back(best_paths[h]);
                    continue;
                }
                
                if (timer < 3000) {
                    if (f) {
                        g.edge_update(this->update_edges(this->redges, usret));
                    } else if (rn == 0) {
                        g.edge_update(this->update_edges(this->edges2, usret));
                    } else if (rn == 1) {
                        g.edge_update(this->update_edges(this->edges3, usret));
                    } else if (rn == 2) {
                        if (xrnd() % 4 == 0) {
                            g.edge_update(this->update_edges(this->redges, usret));
                        } else {
                            g.edge_update(this->update_edges(this->edges, usret));
                        }
                    } else {
                        g.edge_update(this->update_edges(this->edges, usret));
                    }
                } else {
                    if (h >= mi) {
                        if (lf) {
                            g.edge_update(this->update_edges(this->redges, usret));
                        } else if (lrn == 0) {
                            g.edge_update(this->update_edges(this->edges2, usret));
                        } else if (lrn == 1) {
                            g.edge_update(this->update_edges(this->edges3, usret));
                        } else if (lrn == 2) {
                            if (xrnd() % 4 == 0) {
                                g.edge_update(this->update_edges(this->redges, usret));
                            } else {
                                g.edge_update(this->update_edges(this->edges, usret));
                            }
                        } else {
                            g.edge_update(this->update_edges(this->edges, usret));
                        }
                    }
                }
                
                vector<int> path_i;
                if (h >= mi) {
                    g.route(i.a, i.b);
                    path_i = this->path_to_edgeindexs(g.path);
                } else {
                    path_i = best_paths[h];
                }
                
                tmp_paths.emplace_back(path_i);
                int cost = this->all_cost_add(usret, path_i);
                if (cost <= NM) {
                    for (auto &j : path_i) { usret.emplace(j); }
                    b += i.point;
                    // tcost = cost;
                    rr.emplace_back(i);
                }
            }
            
            int cost = this->all_cost(usret);
            for (auto &w : pi) {
                int i = w.second;
                if (cost + this->edgeindex_costs[i] <= NM && usret.find(i) == usret.end()) {
                    usret.emplace(i);
                    cost += this->edgeindex_costs[i];
                    
                }
                if (cost == NM) { break; }
            }
            int score = b * this->score_a(usret);
            
            double tmpscore = score;
            
            const double T = saTimeEnd-saTimeStart;
            const double t = saTimeCurrent-saTimeStart;
            double startTemp   = 512.0 * xn;
            double endTemp     = 0.0;
            double temp        = startTemp + (endTemp - startTemp) * t / T;
            double probability = exp((tmpscore - lastscore) / temp);
            bool FORCE_NEXT    = probability > (double)(xrnd() % X) / X;
            
            if (tmpscore > lastscore || (FORCE_NEXT)) {
                lastscore = tmpscore;
                if (tmpscore > dbestscore) {
                    dbestscore = tmpscore;
                    bestusret = usret;
                    if (timer < 3000) {
                        lf = f;
                        lrn = rn;
                    }
                }
                best_paths = tmp_paths;
                
                if (timer > 800 && timer < 4000) { 
                    for (auto &i : rr) {
                        useroutes.emplace(i);
                    }
                }
            } else {
                
                if (ff) {
                    if (ia != ib && ia != ic && ic != ib) {
                        swap(this->routes[ib], this->routes[ic]);
                        swap(this->routes[ia], this->routes[ib]);
                    }
                } else {
                    if (ia != ib) {
                        swap(this->routes[ia], this->routes[ib]);
                    }
                }
                // if (ia != ib) {
                //     swap(this->routes[ia], this->routes[ib]);
                // }
            }
            
            cnt += 1;
        }
        
        bestscore = dbestscore;
        unordered_set<int> bestignore;
        int igcnt = 0;
        while (timer < 9600) {
            if (igcnt % m == 0) { timer = this->sw.get_milli_time(); }
            if (timer < 800 && cnt > 200) { m = 4; }
            if (timer < 800 && cnt > 500) { m = 8; }
            if (timer < 800 && cnt > 1000) { m = 16; }
            if (timer < 800 && cnt > 5000) { m = 32; }
            if (timer > 9000) { m = 2; }
            if (timer > 9000 && cnt > 2000) { m = 4; }
            if (timer > 9000 && cnt > 50000) { m = 16; }
            int b = 0;
            usret.clear();
            
            int a = xrnd() % E;
            
            unordered_set<int> tignore = bestignore;
            if (bestignore.find(a) != bestignore.end()) {
                tignore.erase(a);
            } else {
                tignore.emplace(a);
            }
            
            
            
            for (auto &i : this->routes) {
                
                if (lf) {
                    g.edge_update(this->update_edges(this->update_edges(this->redges, tignore), usret));
                } else if (lrn == 0) {
                    g.edge_update(this->update_edges(this->update_edges(this->edges2, tignore), usret));
                } else if (lrn == 1) {
                    g.edge_update(this->update_edges(this->update_edges(this->edges3, tignore), usret));
                } else if (lrn == 2) {
                    if (xrnd() % 4 == 0) {
                        g.edge_update(this->update_edges(this->update_edges(this->redges, tignore), usret));
                    } else {
                        g.edge_update(this->update_edges(this->update_edges(this->edges, tignore), usret));
                    }
                } else {
                    g.edge_update(this->update_edges(this->update_edges(this->edges, tignore), usret));
                }
                
                g.route(i.a, i.b);
                const vector<int> path_i = this->path_to_edgeindexs(g.path);
                
                int cost = this->all_cost_add(usret, path_i);
                if (cost <= NM) {
                    for (auto &j : path_i) { usret.emplace(j); }
                    b += i.point;
                }
            }
            int cost = this->all_cost(usret);
            for (auto &w : pi) {
                int i = w.second;
                if (cost + this->edgeindex_costs[i] <= NM && usret.find(i) == usret.end()) {
                    usret.emplace(i);
                    cost += this->edgeindex_costs[i];
                }
                if (cost == NM) { break; }
            }
            int score = b * this->score_a(usret);
            if (score >= bestscore) {
                bestscore = score;
                bestusret = usret;
                bestignore = tignore;
                
            }
            igcnt += 1;
        }
        
        
        pdebug("time", this->sw.get_milli_time());
        pdebug("cnt", cnt, igcnt);
        // pdebug("score", bestscore);
        return this->tov(bestusret);
    }
    
    int score_a (unordered_set<int> us) {
        int a = 0;
        for (auto &i : us) {
            a += this->edgeindex_points[i];
        }
        return a;
    }
    
    
    inline vector<edge> update_edges2 (vector<edge> edges, const unordered_set<int> &usret) {
        for (auto &i : usret) {
            edges[i].cost = 10000;
        }
        return edges;
    }
    
    inline vector<edge> update_edges (vector<edge> edges, const unordered_set<int> &usret) {
        for (auto &i : usret) {
            edges[i].cost = 0;
        }
        return edges;
    }
    
    inline int all_cost (const unordered_set<int> &us) {
        int cost = 0;
        for (auto &i : us) { cost += this->edgeindex_costs[i]; }
        return cost;
    }
    
    inline int all_cost_add (unordered_set<int> us, const vector<int> v) {
        int cost = 0;
        for (auto &i : v) { us.emplace(i); }
        for (auto &i : us) { cost += this->edgeindex_costs[i]; }
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
            r.emplace_back(this->edge_indexs[p]);
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