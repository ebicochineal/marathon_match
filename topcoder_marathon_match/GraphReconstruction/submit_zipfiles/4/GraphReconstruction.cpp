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

struct ABC {
public:
    int a, b, c;
    ABC (int a, int b, int c) {
        this->a = a; this->b = b; this->c = c;
    }
};
ostream& operator << (ostream& os, const ABC& p) {
    os << "(" << p.a << ", " << p.b << ", " << p.c << ")";
    return os;
};

class GraphReconstruction {
public:
    StopWatch sw;
    vector<ABC> paths;
    int N, K;
    double C;
    bool matrix[100][100];
    
    bool badmatrix[100][100];
    bool goodmatrix[100][100];
    
    int cmatrix[100][100];
    
    vector<string> findSolution (int N, double C, int K, vector<string> paths) {
        this->sw = StopWatch();
        this->N = N;
        this->K = K;
        this->C = C;
        for (int y = 0; y < 100; ++y) {
            for (int x = 0; x < 100; ++x) {
                this->matrix[y][x] = false;
                this->badmatrix[y][x] = false;
                this->goodmatrix[y][x] = false;
                
                this->cmatrix[y][x] = 0;
            }
        }
        
        for (int i = 0; i < paths.size(); i+=3) {
            ABC t(stoi(paths[i]), stoi(paths[i+1]), stoi(paths[i+2]));
            this->paths.emplace_back(t);
            // fdebug(t);
            // swap(t.a, t.b);
            // fdebug(t);
        }
        
        
        for (auto&& i : this->paths) {
            if (i.c == 1) {
                this->matrix[i.a][i.b] = true;
                this->matrix[i.b][i.a] = true;
                
                this->goodmatrix[i.a][i.b] = true;
                this->goodmatrix[i.b][i.a] = true;
            }
            if (i.c == -1) {
                this->badmatrix[i.a][i.b] = true;
                this->badmatrix[i.b][i.a] = true;
            }
            if (i.c >= 2) {
                this->badmatrix[i.a][i.b] = true;
                this->badmatrix[i.b][i.a] = true;
            }
            
            this->cmatrix[i.a][i.b] = i.c;
            this->cmatrix[i.b][i.a] = i.c;
        }
        
        
        // for (int y = 0; y < N; ++y) {
        //     for (int x = 0; x < N; ++x) {
        //         if (this->badmatrix[y][x] == false) {
        //             this->matrix[y][x] = true;
        //         }
        //     }
        // }
        
        
        
        // for (int y = 0; y < N; ++y) {
        //     int yc = 0;
        //     for (int x = 0; x < N; ++x) {
        //         // if (this->badmatrix[y][x] == false) {
        //         //     this->matrix[y][x] = true;
        //         // }
        //         if (this->badmatrix[y][x] == true) {
        //             yc += 1;
        //         }
        //     }
        //     pdebug(N-yc);
        // }
        
        // for (int i = 0; i < 8; ++i) {
        //     this->badRegister();
        // }
        // pdebug("B", this->badCnt());
        // auto e = initEdges();
        // for (int y = 0; y < this->N; ++y) {
        //     for (int x = y + 1; x < this->N; ++x) {
        //         if (this->matrix[y][x]) { continue; }
        //         if (this->matrix[y][x] < 0) { continue; }
        //         e.emplace_back(y, x, 1);
        //         e.emplace_back(x, y, 1);
        //         auto g = GraphDijkstra(this->N, e, true);
        //         bool f = true;
        //         for (auto&& i : this->paths) {
        //             if (i.c < 1) { continue; }
        //             g.calcPath(i.a, i.b);
        //             if (g.pathcost < i.c && g.pathcost >= 0) {
        //                 f = false;
        //                 break;
        //             }
        //         }
        //         if (f) {
        //             if (0) {
        //                 this->matrix[y][x] = true;
        //                 this->matrix[x][y] = true;
        //             } else {
        //                 e.pop_back();
        //                 e.pop_back();
        //             }
        //         } else {
        //             e.pop_back();
        //             e.pop_back();
        //             this->badmatrix[y][x] = true;
        //             this->badmatrix[x][y] = true;
        //         }
        //     }
        // }
        
        for (int i = 0; i < 8; ++i) {
            this->badRegister();
        }
        this->mRegister();
        this->mRegister();
        this->mRegister();
        
        
        pdebug("B", this->badCnt(), this->aCnt());
        //pdebug("A", (int)(this->aCnt()*C) - this->mCnt());
        
        pdebug(N, C, K, this->sw.get_milli_time());
        
        return this->toRet();
    }
    
    void mRegister () {
        auto e = initEdges();
        
        for (int i = 0; i < this->N; ++i) {
            if (this->sw.get_milli_time() > 9500) { break; }
            for (int j = 0; j < this->N; ++j) {
                int t = this->cmatrix[i][j];
                if (t < 1) { continue; }
                if (t > 2 && t < 10) { continue; }//
                
                for (int k = 0; k < this->N; ++k) {
                    if (this->cmatrix[i][k] < 1) { continue; }
                    if (this->cmatrix[i][k] + 1 == t || (this->cmatrix[i][k] - 1 > 0 && this->cmatrix[i][k] - 1 == t)) {
                        if (!this->badmatrix[k][j]) {
                            e.emplace_back(k, j, 1);
                            e.emplace_back(j, k, 1);
                            auto g = GraphDijkstra(this->N, e, true);
                            bool f = true;
                            for (auto&& i : this->paths) {
                                if (i.c < 1) {
                                    g.calcPath(i.a, i.b);
                                    if (g.pathcost > i.c) {
                                        f = false;
                                        break;
                                    }
                                } else {
                                    g.calcPath(i.a, i.b);
                                    if (g.pathcost < i.c && g.pathcost >= 0) {
                                        f = false;
                                        break;
                                    }
                                }
                            }
                            if (f) {
                                this->matrix[k][j] = true;
                                this->matrix[j][k] = true;
                                this->cmatrix[j][k] = 1;
                                this->cmatrix[k][j] = 1;
                            } else {
                                e.pop_back();
                                e.pop_back();
                                this->badmatrix[k][j] = true;
                                this->badmatrix[j][k] = true;
                            }
                        }
                    }
                }
            }
        }
    }
    
    void badRegister () {
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < this->N; ++j) {
                if (this->cmatrix[i][j] != -1) { continue; }
                for (int k = 0; k < this->N; ++k) {
                    if (this->cmatrix[j][k] > 0) {
                        this->cmatrix[i][k] = -1;
                        this->cmatrix[k][i] = -1;
                        this->badmatrix[k][i] = true;
                        this->badmatrix[i][k] = true;
                    }
                }
            }
        }
        
    }
    
    int badCnt () {
        int r = 0;
        for (int i=0; i<this->N; i++) {
            for (int j=i+1; j<this->N; j++) {
                r += this->badmatrix[i][j];
            }
        }
        return r;
    }
    int mCnt () {
        int r = 0;
        for (int i=0; i<this->N; i++) {
            for (int j=i+1; j<this->N; j++) {
                r += this->matrix[i][j];
            }
        }
        return r;
    }
    int aCnt () {
        int r = 0;
        for (int i=0; i<this->N; i++) {
            r += this->N - i -1;
        }
        return r;
    }
    
    vector<string> toRet () {
        vector<string> out;
        int c = 0;
        for (int i=0; i<this->N; i++) {
            string row;
            for (int k=0; k<this->N; k++) {
                row += this->matrix[i][k] ? "1" : "0";
                c += this->matrix[i][k];
            }
            out.push_back(row);
        }
        
        // bad only
        // if (1) {
        //     out.clear();
        //     for (int i=0; i<this->N; i++) {
        //         string row;
        //         for (int k=0; k<this->N; k++) { 
        //             row += this->badmatrix[i][k] ? "1" : "0";
        //         }
        //         out.push_back(row);
        //     }
        // }
        
        // if (c/2<2) {
        // if (1) {
        //     out.clear();
        //     for (int i=0; i<this->N; i++) {
        //         string row;
        //         for (int k=0; k<this->N; k++) { 
        //             row += this->badmatrix[i][k] ? "0" : "1";
        //         }
        //         out.push_back(row);
        //     }
        // }
        // if (1) {
        //     out.clear();
        //     for (int i=0; i<this->N; i++) {
        //         string row;
        //         for (int k=0; k<this->N; k++) { 
        //             row += "1";
        //         }
        //         out.push_back(row);
        //     }
        // }
        
        
        return out;
    }
    
    vector<Edge> initEdges () {
        vector<Edge> r;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (matrix[y][x]) {
                    r.emplace_back(y, x, 1);
                }
            }
        }
        return r;
    }
    
    
    
};

int main() {
    GraphReconstruction prog;
    int N;
    double C;
    int K;
    int NumPaths;
    vector<string> paths;
    string path;
    cin >> N;
    cin >> C;
    cin >> K;
    cin >> NumPaths;
    for (int i=0; i < NumPaths * 3; i++) {
        cin >> path;
        paths.push_back(path);
    }
    
    vector<string> ret = prog.findSolution(N,C,K,paths);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
}

