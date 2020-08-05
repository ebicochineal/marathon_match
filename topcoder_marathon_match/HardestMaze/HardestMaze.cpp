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



class AllScore1 {
public:
    int N, R, T;
    vector< pair<int, int> > Starts;
    vector< vector< pair<int, int> > > Targets;
    int _getscore = 0;
    vector< vector<int> > bestInd;
    vector<int>  Dist;
    AllScore1 () {}
    
    AllScore1 (int N, int R, int T, vector< pair<int, int> > Starts, vector< vector< pair<int, int> > > Targets) {
        this->N = N;
        this->R = R;
        this->T = T;
        this->Starts = Starts;
        this->Targets = Targets;
        bestInd = vector< vector<int> >(R, vector<int>(T, 0));
    }
    
    void calcScore (vector<char>& solution) {
        int score = 0;
        int INF = 1000000;
        Dist = vector<int>(N*N*N*N, INF);// Arrays.fill(Dist, INF);
        vector< vector<bool> > Grid = vector< vector<bool> >(N, vector<bool>(N, false));
        
        for (int i=0; i<N*N; i++) { Grid[i/N][i%N]=(solution[i]=='#'); }
        
        for (int i=0; i<R; i++) {
            if (Grid[Starts[i].first][Starts[i].second]) {
                score = -1;
                return;
            }
            for (int k=0; k<T; k++) {
                if (Grid[Targets[i][k].first][Targets[i][k].second]) {
                    score = -1;
                    return;
                }
            }
        }
        int dr[] = {0,1,0,-1};     //L, U, R, D
        int dc[] = {-1,0,1,0};
        for (int r=0, id=0; r<N; r++) {
            for (int c=0; c<N; c++,id++) {
                if (Grid[r][c]) { continue; }
                Dist[id*N*N+id]=0;
                for (int m=0; m<4; m++) {
                    int r2=r+dr[m];
                    int c2=c+dc[m];
                    if (inGrid(r2,c2) && !Grid[r2][c2]) {
                        int id2=coords2id(r2,c2);
                        Dist[id*N*N+id2]=1;
                        Dist[id2*N*N+id]=1;
                    }
                }
            }
        }
        
        allPairsShortestPath(Dist);
        
        vector<int> PathLengths(R);
        score=0;
        for (int q=0; q<R; q++) {
            int startId=coords2id(Starts[q].first,Starts[q].second);
            //check that all targets are reachable
            for (int i=0; i<T; i++) {
                int targetId=coords2id(Targets[q][i].first,Targets[q][i].second);
                if (Dist[startId*N*N+targetId]>=INF) {
                    score = -2;
                    return;
                }
            }

            PathLengths[q]=INF;

            vector<int> ind(T);
            for (int i=0; i<T; i++) { ind[i]=i; }
            
            do {
                int total=0;
                int prevId=startId;
                for (int i=0; i<T; i++) {
                    int nextId=coords2id(Targets[q][ind[i]].first,Targets[q][ind[i]].second);
                    total+=Dist[prevId*N*N+nextId];
                    prevId=nextId;
                }
                //store target permutation with the shortest path
                if (total<PathLengths[q]) {
                    PathLengths[q]=total;
                    for (int i=0; i<T; i++) { bestInd[q][i]=ind[i]; }
                }
            } while (nextPermutation(ind));
            
            score+=PathLengths[q];
        }
        _getscore = score;
        
        
        
        
    }
    
    void fillgrid(vector<char>& ret) {
        //////
        int dr[] = {0,1,0,-1};     //L, U, R, D
        int dc[] = {-1,0,1,0};
        vector< vector<int> > g = vector< vector<int> >(N, vector<int>(N, 0));
        
        for (int i=0; i<R; i++) {
            int r=Starts[i].first;
            int c=Starts[i].second;
            g[r][c] += 1;
            for (int k=0; k<T; k++) {
              int targetR=Targets[i][bestInd[i][k]].first;
              int targetC=Targets[i][bestInd[i][k]].second;
              int targetId=coords2id(targetR,targetC);
              
              while(true) {
                if (r==targetR && c==targetC) break;    //reached our target, so exit
                bool found=false;
                for (int m=0; m<4; m++) {
                  int r2=r+dr[m];
                  int c2=c+dc[m];
                  if (inGrid(r2,c2) && Dist[targetId*N*N+coords2id(r2,c2)]<Dist[targetId*N*N+coords2id(r,c)]) {
                    r=r2;
                    c=c2;
                    found=true;
                    break;
                  }
                }
                if (!found) { break; }
                g[r][c] += 1;
              }
            }
        }
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                if (g[y][x] == 0) {
                    ret[y*N + x] = '#';
                }
            }
        }
        
        
    }
    
    int getScore () { return _getscore; }
    
    bool nextPermutation (vector<int>& a) {
        int n=a.size();
        int i=n-2;
        for (; i>=0; i--) { if (a[i]<a[i+1]) { break; } }
        if (i<0) return false;
        
        for (int j=n-1; j>=i; j--) {
            if (a[j]>a[i]) {
                int temp=a[i];
                a[i]=a[j];
                a[j]=temp;
                break;
            }
        }
        for (int j=i+1; j<(n+i+1)/2; j++) {
            int temp=a[j];
            a[j]=a[n+i-j];
            a[n+i-j]=temp;
        }
        return true;
    }
    
    int coords2id (int r, int c) { return r*N+c; }
    bool inGrid (int x, int y) { return x >= 0 && x < N && y >= 0 && y < N; }
    void allPairsShortestPath (vector<int>& a) {
        int q[N * N];
        int dx[] = {-1,1,0,0};
        int dy[] = {0,0,-1,1};
        for (int k = 0; k < N * N; k++) {
            int knn = k * N * N;
            if (a[knn + k] != 0) continue;
            int tot = 0;
            int curr = 0;
            for (int i = 0; i < N * N; i++) {
                if (a[knn + i] == 1) { q[tot++] = i; }
            }
            while (curr < tot) {
                int i = q[curr++];
                for (int j = 0; j < 4; j++) {
                    int x = i % N + dx[j];
                    int y = i / N + dy[j];
                    int p = y * N + x;
                    if (x >= 0 && x < N && y >= 0 && y < N && a[knn + p] > a[knn + i] + 1 && a[p * N * N + p] == 0) {
                        a[knn + p] = a[knn + i] + 1;
                        q[tot++] = p; 
                    }
                }
            }
        }
    }
};



class HardestMaze {
public:
    StopWatch sw;
    unordered_set<e512pos> noblock;
    int N, R, T;
    AllScore1 as;
    vector<char> findSolution(int N, int R, int T, vector< pair<int, int> > Starts, vector< vector< pair<int, int> > > Targets) {
        this->N = N; this->R = R; this->T = T;
        
        for (pair<int, int> i : Starts) { noblock.emplace(i.second, i.first); }
        for (vector< pair<int, int> > j : Targets) {
            for (pair<int, int> i : j) { noblock.emplace(i.second, i.first); }
        }
        
        this->as = AllScore1(N, R, T, Starts, Targets);
        vector<char> rawret(N*N, '.');
        vector<char> bestret(N*N, '.');
        int bestscore = 0;
        
        as.calcScore(bestret);
        bestscore = as.getScore();
        
        // return rawret;
        // return bestret;
        vector< pair<int, int> > index_v_score;
        vector< vector<char> > rets;
        int index = 0;
        for (int j = 0; j < min(N/3, 2); ++j) {
            for (int i = 0; i < min(N/3, 2); ++i) {
                for (int u = 0; u < 2; ++u) {
                    for (int m = 0; m < 2; ++m) {
                        if (this->sw.get_milli_time() > 6500) { break; }
                        {
                            auto g = testgrid1(m, u, i, j);
                            rets.emplace_back(g);
                            // g = this->patternMatchHC(150, g);
                            as.calcScore(g);
                            index_v_score.emplace_back(index++, as.getScore());
                            if (as.getScore() >= bestscore) {
                                bestscore = as.getScore();
                                bestret = g;
                            }
                        }
                        {
                            auto g = testgrid2(m, u, i, j);
                            rets.emplace_back(g);
                            // g = this->patternMatchHC(150, g);
                            as.calcScore(g);
                            index_v_score.emplace_back(index++, as.getScore());
                            if (as.getScore() >= bestscore) {
                                bestscore = as.getScore();
                                bestret = g;
                            }
                        }
                    }
                }
                
            }
        }
        for (int j = 4; j < min(N/3, 6); ++j) {
            for (int i = 4; i < min(N/3, 6); ++i) {
                for (int u = 0; u < 2; ++u) {
                    for (int m = 0; m < 2; ++m) {
                        if (this->sw.get_milli_time() > 6500) { break; }
                        {
                            auto g = testgrid1(m, u, i, j);
                            rets.emplace_back(g);
                            // g = this->patternMatchHC(150, g);
                            as.calcScore(g);
                            index_v_score.emplace_back(index++, as.getScore());
                            if (as.getScore() >= bestscore) {
                                bestscore = as.getScore();
                                bestret = g;
                            }
                        }
                        {
                            auto g = testgrid2(m, u, i, j);
                            rets.emplace_back(g);
                            // g = this->patternMatchHC(150, g);
                            as.calcScore(g);
                            index_v_score.emplace_back(index++, as.getScore());
                            if (as.getScore() >= bestscore) {
                                bestscore = as.getScore();
                                bestret = g;
                            }
                        }
                    }
                }
                
                
                
            }
        }
        
        
        sort(index_v_score.begin(), index_v_score.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });
        if (N < 16) {
            for (int i = 0; i < rets.size(); i+=1) {
                if (this->sw.get_milli_time() > 6000) { break; }
                auto g = rets[index_v_score[i].first];
                g = this->patternMatchHC(100, g);
                as.calcScore(g);
                if (as.getScore() >= bestscore) {
                    bestscore = as.getScore();
                    bestret = g;
                }
                
            }
        } else {
            for (int i = 0; i < 16; i+=1) {
                if (this->sw.get_milli_time() > 6000) { break; }
                auto g = rets[index_v_score[i].first];
                g = this->patternMatchHC(400, g);
                as.calcScore(g);
                if (as.getScore() >= bestscore) {
                    bestscore = as.getScore();
                    bestret = g;
                }
            }
        }
        
        
        
        
        bestret = this->patternMatchHC(7500-this->sw.get_milli_time(), bestret);
        bestret = this->SA(8000-this->sw.get_milli_time(), bestret);
        bestret = this->patternMatchHC(9500-this->sw.get_milli_time(), bestret);
        as.calcScore(bestret);
        as.fillgrid(bestret);
        pdebug(N,R,T,  as.getScore(), this->sw.get_milli_time());
        return bestret;
    }
    
    vector<char> testgrid1 (int m, int u, int st = 0, int en = 0) {
        vector<char> grid = vector<char>(N*N, '.');
        int bbb = m;
        
        int t = 0;
        for (int x=1 + st; x<N; x+=2) {
            
            bool b = true;
            int s = (bbb % 2 == 0 ? 1 : 0);
            int e = (bbb % 2 == 0 ? N : N-1);
            for (; x < N; ++x) {
                b = true;
                for (int y=s; y<e; ++y) {
                    if (noblock.find(e512pos(x, y)) != noblock.end()) { b = false; }
                }
                if (b) { break; }
            }
            
            if (x >= N-en-1) {
                x = N;
                b = false;
            }
            
            if (b) { for (int y=s; y<e; ++y) { grid[y*N+x]='#'; } }
            int bbbb = (bbb+u) % 2;
            for (int y=s; y<e; ++y) {
                if (y > 0 && y < N-1 &&   x - t > 1 && y % 2 == 0) {
                    int c = bbbb % 2;
                    for (int d = 0; d < x - t - 1; ++d) {
                        if (noblock.find(e512pos(t+d+c, y)) == noblock.end()) {
                            grid[y*N+(t+d+c)]='#';
                        }
                    }
                    bbbb += 1;
                }
            }
            if (!b) { break; }
            
            
            bbb += 1;
            t = x + 1;
        }
        return grid;
    }
    
    vector<char> testgrid2 (int m, int u, int st = 0, int en = 0) {
        vector<char> grid = vector<char>(N*N, '.');
        int bbb = m;
        
        int t = 0;
        for (int y=1+st; y<N; y+=2) {
            
            bool b = true;
            int s = (bbb % 2 == 0 ? 1 : 0);
            int e = (bbb % 2 == 0 ? N : N-1);
            for (; y < N; ++y) {
                b = true;
                for (int x=s; x<e; ++x) {
                    if (noblock.find(e512pos(x, y)) != noblock.end()) { b = false; }
                }
                if (b) { break; }
            }
            
            if (y >= N-en-1) {
                y = N;
                b = false;
            }
            
            if (b) { for (int x=s; x<e; ++x) { grid[y*N+x]='#'; } }
            int bbbb = (bbb+u) % 2;
            for (int x=s; x<e; ++x) {
                if (x > 0 && x < N-1 && y - t > 1 && x % 2 == 0) {
                    int c = bbbb % 2;
                    for (int d = 0; d < y-t-1; ++d) {
                        if (noblock.find(e512pos(x, t+d+c)) == noblock.end()) {
                            grid[(t+d+c)*N+x]='#';
                        }
                    }
                    bbbb += 1;
                }
            }
            if (!b) { break; }
            
            bbb += 1;
            t = y + 1;
        }
        return grid;
    }
    
    
    vector<char> SA (int limit, vector<char> ret) {
        StopWatch sw;
        
        vector<char> bestret = ret;
        as.calcScore(bestret);
        
        double bestscore = as.getScore();
        
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 2; ++z) {
                int a = xrnd() % ret.size();
                if (noblock.find(e512pos(a%N, a/N)) != noblock.end()) { continue; }
                if (ret[a] == '.') {
                    ret[a] = '#';
                } else {
                    ret[a] = '.';
                }
                
                as.calcScore(ret);
                double tmpscore = as.getScore();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    if (ret[a] == '.') {
                        ret[a] = '#';
                    } else {
                        ret[a] = '.';
                    }
                }
                cnt += 1;
            }
            // for (int z = 0; z < 1; ++z) {
            //     int a = xrnd() % ret.size();
            //     int b = xrnd() % ret.size();
            //     swap(ret[a], ret[b]);
            //     as.calcScore(ret);
            //     double tmpscore = as.getScore();
                
            //     const double T = saTimeEnd-saTimeStart;
            //     const double t = saTimeCurrent-saTimeStart;
            //     const double startTemp   = 1.0;
            //     const double endTemp     = 0.0;
            //     const double temp        = startTemp + (endTemp - startTemp) * t / T;
            //     const double probability = exp((tmpscore - lastscore) / temp);
            //     const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
            //     if (tmpscore >= lastscore || FORCE_NEXT) {
            //         lastscore = tmpscore;
            //         if (tmpscore > bestscore) {
            //             bestscore = tmpscore;
            //             bestret = ret;
            //         }
            //     } else {
            //         swap(ret[a], ret[b]);
            //     }
            //     cnt += 1;
            // }
        }
        pdebug(cnt);
        
        return bestret;
    }
    
    
    
    vector<char> patternMatchHC (int limit, vector<char> ret) {
        StopWatch sw;
        as.calcScore(ret);
        as.fillgrid(ret);
        double bestscore = as.getScore();
        
        vector<char> bestret = ret;
        
        
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        
        char p1[3][3] = {{'#', '#', '#'}, {'.', '.', '.'}};
        char p2[2][3] = {{'.', '.', '.'}, {'.', '#', '.'}};
        char p3[2][3] = {{'.', '.', '.'}, {'#', '#', '#'}};
        char p4[2][3] = {{'.', '#', '.'}, {'.', '.', '.'}};
        
        
        char pp1[3][2] = {{'.', '#'}
                        ,{'.', '#'}
                        ,{'.', '#'}};
        char pp2[3][2] = {{'.', '.'}
                        ,{'#', '.'}
                        ,{'.', '.'}};
        char pp3[3][2] = {{'#', '.'}
                        ,{'#', '.'}
                        ,{'#', '.'}};
        char pp4[3][2] = {{'.', '.'}
                        ,{'.', '#'}
                        ,{'.', '.'}};
        
        
        
        const double startTemp   = 0.0;
        const double endTemp     = 0.0;
        int lcnt  = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            {
                for (int y = 0; y < N-1; ++y) {
                    for (int x = 0; x < N-2; ++x) {
                        if ((saTimeCurrent = sw.get_milli_time()) > saTimeEnd) { break; }
                        bool b = false;
                        for (int dy = 0; dy < 2; ++dy) {
                            for (int dx = 0; dx < 3; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                if (ret[index] != p1[dy][dx]) {
                                    b = true;
                                    break;
                                }
                            }
                        }
                        if (b) { continue; }
                        
                        if (y > 1 && (ret[(y-1)*N+(x+0)] == '.' || ret[(y-1)*N+(x+1)] == '.' || ret[(y-1)*N+(x+2)] == '.')) { continue; }
                        if (x > 0 && ret[(y)*N+(x-1)] == '.') { continue; }
                        if (x < N-3 && ret[(y)*N+(x+3)] == '.') { continue; }
                        
                        for (int dy = 0; dy < 2; ++dy) {
                            for (int dx = 0; dx < 3; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                ret[index] = p2[dy][dx];
                            }
                        }
                        
                        as.calcScore(ret);
                        double tmpscore = as.getScore();
                        
                        if (tmpscore > bestscore) {
                                bestscore = tmpscore;
                                bestret = ret;
                        } else {
                            for (int dy = 0; dy < 2; ++dy) {
                                for (int dx = 0; dx < 3; ++dx) {
                                    int index = (y+dy)*N + (x+dx);
                                    ret[index] = p1[dy][dx];
                                }
                            }
                        }
                        cnt += 1;
                    }
                }
                for (int y = 0; y < N-1; ++y) {
                    for (int x = 0; x < N-2; ++x) {
                        if ((saTimeCurrent = sw.get_milli_time()) > saTimeEnd) { break; }
                        bool b = false;
                        for (int dy = 0; dy < 2; ++dy) {
                            for (int dx = 0; dx < 3; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                if (ret[index] != p3[dy][dx]) {
                                    b = true;
                                    break;
                                }
                            }
                        }
                        if (b) { continue; }
                        if (y < N-2 && (ret[(y+2)*N+(x+0)] == '.' || ret[(y+2)*N+(x+1)] == '.' || ret[(y+2)*N+(x+2)] == '.')) { continue; }
                        if (x > 0 && ret[(y-1)*N+(x-1)] == '.') { continue; }
                        if (x < N-3 && ret[(y-1)*N+(x+3)] == '.') { continue; }
                        
                        for (int dy = 0; dy < 2; ++dy) {
                            for (int dx = 0; dx < 3; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                ret[index] = p4[dy][dx];
                            }
                        }
                        
                        as.calcScore(ret);
                        double tmpscore = as.getScore();
                        
                        if (tmpscore > bestscore) {
                                bestscore = tmpscore;
                                bestret = ret;
                        } else {
                            for (int dy = 0; dy < 2; ++dy) {
                                for (int dx = 0; dx < 3; ++dx) {
                                    int index = (y+dy)*N + (x+dx);
                                    ret[index] = p3[dy][dx];
                                }
                            }
                        }
                        cnt += 1;
                    }
                }
            }
            
            {
                for (int y = 0; y < N-2; ++y) {
                    for (int x = 0; x < N-1; ++x) {
                        if ((saTimeCurrent = sw.get_milli_time()) > saTimeEnd) { break; }
                        bool b = false;
                        for (int dy = 0; dy < 3; ++dy) {
                            for (int dx = 0; dx < 2; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                if (ret[index] != pp1[dy][dx]) {
                                    b = true;
                                    break;
                                }
                            }
                        }
                        if (b) { continue; }
                        if (x < N-2 && (ret[(y+0)*N+(x+2)] == '.' || ret[(y+1)*N+(x+2)] == '.' || ret[(y+2)*N+(x+2)] == '.')) { continue; }
                        if (y > 0 && ret[(y-1)*N+(x+1)] == '.') { continue; }
                        if (y < N-3 && ret[(y+3)*N+(x+1)] == '.') { continue; }
                        
                        for (int dy = 0; dy < 3; ++dy) {
                            for (int dx = 0; dx < 2; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                ret[index] = pp2[dy][dx];
                            }
                        }
                        as.calcScore(ret);
                        double tmpscore = as.getScore();
                        
                        if (tmpscore > bestscore) {
                                bestscore = tmpscore;
                                bestret = ret;
                        } else {
                            for (int dy = 0; dy < 3; ++dy) {
                                for (int dx = 0; dx < 2; ++dx) {
                                    int index = (y+dy)*N + (x+dx);
                                    ret[index] = pp1[dy][dx];
                                }
                            }
                        }
                        cnt += 1;
                    }
                }
                for (int y = 0; y < N-2; ++y) {
                    for (int x = 0; x < N-1; ++x) {
                        if ((saTimeCurrent = sw.get_milli_time()) > saTimeEnd) { break; }
                        bool b = false;
                        for (int dy = 0; dy < 3; ++dy) {
                            for (int dx = 0; dx < 2; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                if (ret[index] != pp3[dy][dx]) {
                                    b = true;
                                    break;
                                }
                            }
                        }
                        if (b) { continue; }
                        if (x > 1 && (ret[(y+0)*N+(x-1)] == '.' || ret[(y+1)*N+(x-1)] == '.' || ret[(y+2)*N+(x-1)] == '.')) { continue; }
                        if (y > 1 && ret[(y-1)*N+(x)] == '.') { continue; }
                        if (y < N-3 && ret[(y+3)*N+(x)] == '.') { continue; }
                        
                        for (int dy = 0; dy < 3; ++dy) {
                            for (int dx = 0; dx < 2; ++dx) {
                                int index = (y+dy)*N + (x+dx);
                                ret[index] = pp4[dy][dx];
                            }
                        }
                        
                        as.calcScore(ret);
                        double tmpscore = as.getScore();
                        
                        if (tmpscore > bestscore) {
                                bestscore = tmpscore;
                                bestret = ret;
                        } else {
                            for (int dy = 0; dy < 3; ++dy) {
                                for (int dx = 0; dx < 2; ++dx) {
                                    int index = (y+dy)*N + (x+dx);
                                    ret[index] = pp3[dy][dx];
                                }
                            }
                        }
                        cnt += 1;
                    }
                }
            }
            lcnt += 1;
        }
        
        
        // for (int y = 0; y < this->N; ++y) {
        //     string ppp = "";
        //     for (int x = 0; x < this->N; ++x) {
        //         ppp += ret[y*this->N+x];
        //     }
        //     fdebug(ppp);
        // }
        
        
        // pdebug("UP", cnt);
        // pdebug("L", lcnt);
        return bestret;
    }
    
    
};


int main() {
    HardestMaze prog;
    int N;
    int R;
    int T;
    int row, col;
    vector< pair<int, int> > Starts;
    vector< vector< pair<int, int> > > Targets;
  
    cin >> N;
    cin >> R;
    cin >> T;

    for (int i=0; i<R; ++i) {
        cin >> row >> col;
        Starts.push_back(make_pair(row, col));
    
        vector< pair<int, int> > targ;
        for (int k=0; k<T; ++k) {
            cin >> row >> col;
            targ.push_back(make_pair(row, col));
        }
        Targets.push_back(targ);
    }
    
    vector<char> ret = prog.findSolution(N, R, T, Starts, Targets);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) { cout << ret[i] << endl; }
        
    cout.flush();
}