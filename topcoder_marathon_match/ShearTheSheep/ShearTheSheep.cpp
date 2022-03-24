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
        size_t operator()(const e512pos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
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

void fgdebug (array< array<char, 32>, 32 >& g, int n) {
    fdebug(n, n);
    for (int y = 0; y < n; ++y) {
        string s = "";
        for (int x = 0; x < n; ++x) { s += g[y][x]; }
        fdebug(s);
    }
}

inline bool inside (int x, int y, int n) { return x >= 0 && x < n && y >= 0 && y < n; }



struct sheep {
    int x, y;
    sheep (int x, int y, char w) {
        this->x = x;
        this->y = y;
    }
    
};
struct farmer {
    char mv = 'N';
    int x, y;
    int nx, ny;
    int tx, ty;
    farmer (int x, int y, char w) {
        this->x = x;
        this->y = y;
    }
};



static const int dy[] = {-1, 0, 1, 0};
static const int dx[] = {0, 1, 0, -1};
static const char dir[] = {'U', 'R', 'D', 'L'};

class MM {
public:
    int N, C, S, F, B;
    array< array<char, 32>, 32 > grid;
    
    array< array<char, 32>, 32 > tgrid;
    
    int turn = 0;
    int time = 0;
    
    vector<farmer> farmers;
    vector<sheep> sheeps;
    vector<e512pos> barns;
    
    vector< vector<int> > allcost = vector< vector<int> >(900, vector<int>(900, 1000000));
    
    
    
    StopWatch sw;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->C;
        this->gridupdate();
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                char c = this->grid[y][x];
                if (c >= 'a' && c <= 'z') { this->farmers.emplace_back(x, y, c); }
                if (c >= 'A' && c <= 'D') { this->sheeps.emplace_back(x, y, c); }
                if (c == 'X') {this->barns.emplace_back(x, y); }
            }
        }
        this->S = this->sheeps.size();
        this->F = this->farmers.size();
        this->B = this->barns.size();
        
        
        // pdebug(this->F / (double)(this->N*this->N));
        pdebug(this->S / (double)(this->N*this->N));
        pdebug(this->F / (double)this->S);
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->bfs_all(x, y);
            }
        }
        
    }
    
    void gridupdate () {
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cin >> this->grid[y][x];
                this->tgrid[y][x] = this->grid[y][x];
            }
        }
    }
    void stateupdate() {
        this->sheeps.clear();
        // this->farmers.clear();
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                char c = this->grid[y][x];
                if (c >= 'A' && c <= 'D') { this->sheeps.emplace_back(x, y, c); }
                // if (c >= 'a' && c <= 'z') { this->farmers.emplace_back(x, y, c); }
            }
        }
    }
    
    
    vector< pair<int, e512pos> > bfs_sheep_v_a (int x, int y) {
        static array< array<int, 32>, 32 > cost;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        vector< pair<int, e512pos> > v;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            
            cost[ny][nx] = cost[y][x]+1;
            if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
            if (this->grid[ny][nx] >= 'A' && this->grid[ny][nx] <= 'D') { v.emplace_back(cost[ny][nx], e512pos(nx, ny));}
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
                    if (this->grid[ny][nx] >= 'A' && this->grid[ny][nx] <= 'D') { v.emplace_back(cost[ny][nx], e512pos(nx, ny)); }
                }
            }
        }
        return v;
    }
    
    
    vector< pair<int, e512pos> > bfs_sheep_v (int x, int y) {
        static array< array<int, 32>, 32 > cost;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        vector< pair<int, e512pos> > v;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            
            cost[ny][nx] = cost[y][x]+1;
            if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
            if (this->grid[ny][nx] > 'A' && this->grid[ny][nx] <= 'D') { v.emplace_back(cost[ny][nx], e512pos(nx, ny));}
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
                    if (this->grid[ny][nx] > 'A' && this->grid[ny][nx] <= 'D') { v.emplace_back(cost[ny][nx], e512pos(nx, ny)); }
                }
            }
        }
        return v;
    }
    
    
    void bfs_all (int x, int y) {
        static array< array<int, 32>, 32 > cost;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        vector< pair<int, e512pos> > v;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            
            cost[ny][nx] = cost[y][x]+1;
            if (!(this->grid[ny][nx] == '#' || this->grid[ny][nx] == 'X')) { que.emplace_back(nx, ny); }
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    if (!(this->grid[ny][nx] == '#' || this->grid[ny][nx] == 'X')) { que.emplace_back(nx, ny); }
                }
            }
        }
        
        int ap = y * this->N + x;
        for (int by = 0; by < this->N; ++by) {
            for (int bx = 0; bx < this->N; ++bx) {
                int bp = by * this->N + bx;
                this->allcost[ap][bp] = cost[by][bx];
            }
        }
        
    }
    
    
    
    char bfs_sheep_mv (int x, int y, int tx, int ty) {
        static array< array<int, 32>, 32 > cost;
        static array< array<char, 32>, 32 > sdir;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
                sdir[y][x] = 'N';
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            
            cost[ny][nx] = cost[y][x]+1;
            sdir[ny][nx] = dir[d];
            if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
            if (nx == tx && ny == ty) { return sdir[ny][nx]; }
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    sdir[ny][nx] = sdir[p.y][p.x];
                    if (nx == tx && ny == ty) { return sdir[ny][nx]; }
                    if (this->grid[ny][nx] == '.') {
                        que.emplace_back(nx, ny);
                    }
                }
            }
        }
        return 'N';
    }
    
    int bfs_dist (int x, int y, int tx, int ty) {
        static array< array<int, 32>, 32 > cost;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            cost[ny][nx] = cost[y][x]+1;
            if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
            if (nx == tx && ny == ty) { return cost[ny][nx]; }
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    if (nx == tx && ny == ty) { return cost[ny][nx]; }
                    if (this->grid[ny][nx] == '.') {
                        que.emplace_back(nx, ny);
                    }
                }
            }
        }
        return 1000000;
    }
    
    
    
    char bfs_barn (int x, int y) {
        static array< array<int, 32>, 32 > cost;
        static array< array<char, 32>, 32 > sdir;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
                sdir[y][x] = 'N';
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        que.emplace_back(x, y);
        
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            if (!(this->grid[ny][nx] == '.' || this->grid[ny][nx] == 'X')) { continue; }
            cost[ny][nx] = 1;
            sdir[ny][nx] = dir[d];
            que.emplace_back(nx, ny);
            
        }
        
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) {
                if (this->grid[p.y][p.x] == 'X') { return sdir[p.y][p.x]; }
                tque.emplace_back(p);
            }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (!(this->grid[ny][nx] == '.' || this->grid[ny][nx] == 'X')) { continue; }
                    if (cost[p.y][p.x]+1 < cost[ny][nx]) {
                        cost[ny][nx] = cost[p.y][p.x]+1;
                        if (sdir[p.y][p.x] != 'N') { sdir[ny][nx] = sdir[p.y][p.x]; }
                        que.emplace_back(nx, ny);
                    }
                }
            }
        }
        return 'N';
    }
    
    
    vector< pair<int, e512pos> > bfs_barn_v (int x, int y) {
        static array< array<int, 32>, 32 > cost;
        static vector<e512pos> que;
        static vector<e512pos> tque;
        vector< pair<int, e512pos> > v;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                cost[y][x] = 1000000;
            }
        }
        que.clear();
        tque.clear();
        cost[y][x] = 0;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny, this->N)) { continue; }
            
            cost[ny][nx] = cost[y][x]+1;
            if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
            if (this->grid[ny][nx] == 'X') { v.emplace_back(cost[ny][nx], e512pos(nx, ny));}
        }
        
        while (que.size() > 0) {
            tque.clear();
            for (auto&& p : que) { tque.emplace_back(p); }
            que.clear();
            for (auto&& p : tque) {
                for (int d = 0; d < 4; ++d) {
                    int nx = p.x + dx[d];
                    int ny = p.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (cost[p.y][p.x]+1 >= cost[ny][nx]) { continue; }
                    cost[ny][nx] = cost[p.y][p.x]+1;
                    if (this->grid[ny][nx] == '.') { que.emplace_back(nx, ny); }
                    if (this->grid[ny][nx] == 'X') { v.emplace_back(cost[ny][nx], e512pos(nx, ny)); }
                }
            }
        }
        return v;
    }
    
    
    
    
    
    void output () {
        string s = "";
        for (int i = 0; i < this->F; ++i) {
            s += print(this->farmers[i].y, this->farmers[i].x, this->farmers[i].mv) + " ";
            this->farmers[i].y = this->farmers[i].ny;
            this->farmers[i].x = this->farmers[i].nx;
        }
        cout << s << endl;
        cout.flush();
    }
    void mmloop () {
        pdebug("N"+to_string(this->N), "C"+to_string(this->C), "S"+to_string(this->S), "F"+to_string(this->F), "B"+to_string(this->B));
    
        this->solve();
        this->output();
        for (int i = 1; i < 1001; ++i) {
            this->turn = i;
            cin >> this->time;
            if (i == 999) {
                pdebug(this->time);
                cerr.flush();
            }
            this->gridupdate();
            this->stateupdate();
            this->solve();
            this->output();
        }
    }
    
    void solve () {
        array< array<int, 32>, 32 > cost;
        array< array<e512pos, 32>, 32 > pos;
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 32; ++x) {
                cost[y][x] = 1000000;
                pos[y][x] = e512pos(-1, -1);
                
            }
        }
        
        for (auto&& i : this->farmers) {
            if (this->grid[i.y][i.x]-'a' >= this->C) { continue; }
            auto v = this->bfs_sheep_v(i.x, i.y);
            for (auto&& j : v) {
                e512pos p = j.second;
                if (j.first < cost[p.y][p.x]) {
                    cost[p.y][p.x] = j.first;
                    pos[p.y][p.x] = e512pos(i.x, i.y);
                }
            }
        }
        
        for (auto&& i : this->farmers) {
            i.tx = -1;
            i.ty = -1;
            i.mv = 'N';
            i.nx = i.x;
            i.ny = i.y;
            int bestdist = 1000000;
            int bestpos;
            for (auto&& j : this->barns) {
                // bestdist = min(abs(j.x-i.x) + abs(j.y-i.y), bestdist);
                if (this->allcost[i.y*this->N+i.x][j.y*this->N+j.x] < bestdist) {
                    bestdist = this->allcost[i.y*this->N+i.x][j.y*this->N+j.x];
                    bestpos = j.y*this->N+j.x;
                }
                
            }
            
            if (this->grid[i.y][i.x]-'a' >= max(this->C*0.4, 3.0) && this->turn < 1000 - (bestdist + 6) - 10) {
                for (int d = 0; d < 4; ++d) {
                    int nx = i.x + dx[d];
                    int ny = i.y + dy[d];
                    if (!inside(nx, ny, this->N)) { continue; }
                    if (this->grid[ny][nx] != 'X') { continue; }
                    i.mv = dir[d];
                    break;
                }
            }
            
            if (i.mv == 'N' && this->bfs_barn_v(i.x, i.y).size() > 0) {
                if (this->C > 15) {
                    if (i.mv == 'N') {
                        if (this->grid[i.y][i.x]-'a' >= this->C-3 && bestdist <= 2 && this->turn < 1000 - (bestdist + 6) - 30) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                    if (i.mv == 'N') {
                        if (this->grid[i.y][i.x]-'a' >= this->C-6 && bestdist <= 1 && this->turn < 1000 - (bestdist + 6) - 30) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                } else if (this->C > 10) {
                    if (i.mv == 'N') {
                        if (this->grid[i.y][i.x]-'a' >= this->C-2 && bestdist <= 2 && this->turn < 1000 - (bestdist + 6) - 20) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                    if (i.mv == 'N') {
                        if (this->grid[i.y][i.x]-'a' >= this->C-4 && bestdist <= 1 && this->turn < 1000 - (bestdist + 6) - 20) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                } else if (this->C > 3) {
                    if (i.mv == 'N') {
                        if (this->grid[i.y][i.x]-'a' >= this->C-1 && bestdist <= 2 && this->turn < 1000 - (bestdist + 6) - 10) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                    if (i.mv == 'N' && this->C > 4) {
                        if (this->grid[i.y][i.x]-'a' >= this->C-2 && bestdist <= 1 && this->turn < 1000 - (bestdist + 6) - 10) {
                            i.mv = this->bfs_barn(i.x, i.y);
                        }
                    }
                }
            }
            if (i.mv == 'N') {
                if ((this->grid[i.y][i.x]-'a' < this->C && this->turn < 1000 - (bestdist + 6)) || (this->grid[i.y][i.x]-'a' < min(this->C, 4) && this->turn < 1000 - (bestdist))) {
                    
                    if (i.mv == 'N') {
                        vector< pair<int, e512pos> > v = this->bfs_sheep_v(i.x, i.y);
                        if (v.size() == 0 && this->S <= 2) { v = this->bfs_sheep_v_a(i.x, i.y); }
                        vector< pair<int, e512pos> > tv = v;
                        
                        if (v.size() > 0) {
                            for (auto&& j : v) {
                                int x = j.second.x;
                                int y = j.second.y;
                                int jdist = j.first;
                                j.first *= 100;
                                
                                if (jdist == 2) { j.first += 100; }
                                if (jdist == 4) { j.first += 25; }
                                
                                if (e512pos(i.x, i.y) == pos[y][x]) { j.first -= 3200; }
                                j.first -= ((int)this->grid[y][x]-(int)'A')*100;
                                if (this->grid[y][x] == 'D' && this->F <= 2 && this->F / (double)this->S > 0.12) { j.first -= 50; }
                                
                                if ((this->grid[i.y][i.x]-'a')+(this->grid[y][x]-'A') == this->C) { j.first -= 75; }
                                
                                
                                if ((this->grid[i.y][i.x]-'a') + 2 < this->C) {
                                    for (auto&& k : v) {
                                        if (j == k) { continue; }
                                        int bx = k.second.x;
                                        int by = k.second.y;
                                        char c = this->grid[k.second.y][k.second.x];
                                        
                                        e512pos kp = k.second;
                                        if (!(e512pos(i.x, i.y) == pos[kp.y][kp.x])) { continue; }
                                        int dist = this->allcost[y*this->N+x][by*this->N+bx];
                                        if (dist <= 6) { j.first -= 2 * (c-'A'); }
                                        if (dist <= 5) { j.first -= 2 * (c-'A'); }
                                        if (dist <= 4) { j.first -= 4 * (c-'A'); }
                                        if (dist <= 3) { j.first -= 4 * (c-'A'); }
                                        if (dist <= 2) { j.first -= 6 * (c-'A'); }
                                        if (dist <= 1) { j.first -= 6 * (c-'A'); }
                                        if (c == 'D') {
                                            if (dist == 6) { j.first -= 12; }
                                            if (dist == 5) { j.first -= 12; }
                                            if (dist == 4) { j.first -= 25; }
                                            if (dist == 3) { j.first -= 25; }
                                            if (dist == 2) { j.first -= 50; }
                                            if (dist == 1) { j.first -= 50; }
                                        }
                                        
                                    }
                                } else {
                                    int bbestdist = 1000000;
                                    for (auto&& k : this->barns) {
                                        bbestdist = min(this->allcost[y*this->N+x][k.y*this->N+k.x], bbestdist);
                                    }
                                    j.first += bbestdist * 25;
                                }
                            }
                            
                            sort(v.begin(), v.end(), [&](const pair<int, e512pos>& a, const pair<int, e512pos>& b) { return a.first < b.first; });
                            i.mv = this->bfs_sheep_mv(i.x, i.y, v[0].second.x, v[0].second.y);
                            this->grid[v[0].second.y][v[0].second.x] = max(this->grid[v[0].second.y][v[0].second.x]-1, (int)'A');
                            
                            i.tx = v[0].second.x;
                            i.ty = v[0].second.y;
                            
                            if (tv.size() > 1 && tv[0].first > 1) {
                                int ax = v[0].second.x;
                                int ay = v[0].second.y;
                                int bx = v[1].second.x;
                                int by = v[1].second.y;
                                int adist = 0;
                                int bdist = 0;
                                
                                for (auto&& j : tv) {
                                    if (j.second.x == ax && j.second.y == ay) { adist = j.first; }
                                    if (j.second.x == bx && j.second.y == by) { bdist = j.first; }
                                }
                                
                                for (int d = 0; d < 4; ++d) {
                                    int nx = i.x + dx[d];
                                    int ny = i.y + dy[d];
                                    if (!inside(nx, ny, this->N)) { continue; }
                                    if (this->grid[ny][nx] != '.') { continue; }
                                    
                                    swap(this->grid[i.y][i.x], this->grid[ny][nx]);
                                    int tadist = this->bfs_dist(nx, ny, ax, ay);
                                    int tbdist = this->bfs_dist(nx, ny, bx, by);
                                    if (tadist < adist && tbdist < bdist) {
                                        i.mv = dir[d];
                                    }
                                    swap(this->grid[i.y][i.x], this->grid[ny][nx]);
                                }
                            }
                        }
                    }
                } else {
                    i.mv = this->bfs_barn(i.x, i.y);
                }
                
                if (i.mv == 'N' && this->grid[i.y][i.x] != 'a') {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i.x + dx[d];
                        int ny = i.y + dy[d];
                        if (!inside(nx, ny, this->N)) { continue; }
                        if (this->grid[ny][nx] != 'X') { continue; }
                        i.mv = dir[d];
                        break;
                    }
                }
                if (i.mv == 'N' && this->grid[i.y][i.x] != 'a') {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i.x + dx[d];
                        int ny = i.y + dy[d];
                        if (!inside(nx, ny, this->N)) { continue; }
                        if (this->grid[ny][nx] != '.') { continue; }
                        if (this->allcost[ny*this->N+nx][bestpos] < bestdist) {
                            i.mv = dir[d];
                            break;
                        }
                    }
                }
                if (i.mv == 'N' && this->grid[i.y][i.x] != 'a') {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i.x + dx[d];
                        int ny = i.y + dy[d];
                        if (!inside(nx, ny, this->N)) { continue; }
                        if (!(this->grid[ny][nx] >= 'a' && this->grid[ny][nx] <= 'z')) { continue; }
                        if (this->grid[ny][nx] - 'a' == this->C) { continue; }
                        if (this->allcost[ny*this->N+nx][bestpos] < bestdist) {
                            i.mv = dir[d];
                            break;
                        }
                    }
                }
                
                if (i.mv == 'N') {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i.x + dx[d];
                        int ny = i.y + dy[d];
                        if (!inside(nx, ny, this->N)) { continue; }
                        if (this->grid[ny][nx] != '.') { continue; }
                        i.mv = dir[d];
                        break;
                    }
                }
            }
            
            if (i.mv != 'N') {
                int ny = i.y;
                int nx = i.x;
                if (i.mv == 'U') { ny -= 1; }
                if (i.mv == 'D') { ny += 1; }
                if (i.mv == 'L') { nx -= 1; }
                if (i.mv == 'R') { nx += 1; }
                
                if (this->grid[ny][nx] == '.') {
                    swap(this->grid[i.y][i.x], this->grid[ny][nx]);
                    i.nx = nx;
                    i.ny = ny;
                    continue;
                }
                if (this->grid[ny][nx] >= 'a' && this->grid[ny][nx] <= 'z') {
                    int cnt = this->C - (this->grid[ny][nx]-'a');
                    if (cnt > 0) {
                        int bcnt = this->grid[i.y][i.x]-'a';
                        if (bcnt > cnt) {
                            this->grid[ny][nx] = 'a'+this->C;
                            this->grid[i.y][i.x] = 'a'+bcnt-cnt;
                        } else {
                            int m = (this->C-(this->grid[i.y][i.x]-'a'));
                            this->grid[ny][nx] += bcnt;
                            this->grid[i.y][i.x] = 'a';
                        }
                    }
                    continue;
                }
                if (this->grid[ny][nx] == 'X') {
                    this->grid[i.y][i.x] = 'a';
                    continue;
                }
                if (this->grid[ny][nx] >= 'B' && this->grid[ny][nx] <= 'D') {
                    this->grid[ny][nx] -= 1;
                    this->grid[i.y][i.x] += 1;
                    continue;
                }
                
            }
        }
    }
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.mmloop();
    cout.flush();
    return 0;
}
