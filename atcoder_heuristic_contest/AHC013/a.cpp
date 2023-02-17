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

struct mmyxyx {
    int ay, ax, by, bx;
    mmyxyx (int ay, int ax, int by, int bx) {
        this->ay = ay;
        this->ax = ax;
        this->by = by;
        this->bx = bx;
    }
};

class MM {
public:
    int N, K;
    array<int, 6> cnts;
    array< array<int, 48>, 48> rawgrid;
    
    vector<int> scores;
    StopWatch sw;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->K;
        
        for (int i = 0; i < 6; ++i) { this->cnts[i] = 0; }
        for (int y = 0; y < this->N; ++y) {
            string t;
            cin >> t;
            for (int x = 0; x < this->N; ++x) {
                this->rawgrid[y][x] = (char)t[x] - '0';
                this->cnts[this->rawgrid[y][x]] += 1;
            }
        }
        
        int s = 0;
        for (int i = 0; i < 128; ++i) {
            this->scores.emplace_back(s);
            s += i;
        }
        
        pdebug(this->N, this->K, ((this->cnts[0]/((float)this->N*this->N)) * 100));
        
    }
    
    
    
    int can_connect (array< array<int, 48>, 48>& grid, array<bitset<48>, 48>& use, int y, int x, int d) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        int ny = y + dy[d];
        int nx = x + dx[d];
        while (0 <= ny && ny < this->N && 0 <= nx && nx < this->N) {
            if (use[ny][nx]) { return 0; }
            if (grid[ny][nx] != 0) { return grid[ny][nx]; }
            ny += dy[d];
            nx += dx[d];
        }
        return 0;
    }
    
    mmyxyx line_fill (array< array<int, 48>, 48>& grid, array<bitset<48>, 48>& use, int y, int x, int d) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        int ny = y + dy[d];
        int nx = x + dx[d];
        while (0 <= ny && ny < this->N && 0 <= nx && nx < this->N) {
            if (grid[ny][nx] != 0) { return mmyxyx(y, x, ny, nx); }
            use[ny][nx] = true;
            ny += dy[d];
            nx += dx[d];
        }
    }
    
    
    vector<mmyxyx> connect (array< array<int, 48>, 48>& grid) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        static array<bitset<48>, 48> use;
        for (int i = 0; i < this->N; ++i) { use[i].reset(); }
        
        vector<mmyxyx> ret;
        
        int action_count_limit = this->K * 100;
        
        for (int i = 1; i <= this->K; ++i) {
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    if (grid[y][x] != i) { continue; }
                    for (int d = 0; d < 2; ++d) {
                        int c = this->can_connect(grid, use, y, x, d);
                        if (c == grid[y][x]) {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d));
                            action_count_limit--;
                            if (action_count_limit <= 0) { return ret; }
                        }
                    }
                }
            }
        }
        
        
        // pdebug("lm",action_count_limit, this->sw.get_milli_time());
        
        return ret;
    }
    
    
    e512pos can_connect2 (array< array<int, 48>, 48>& grid, array<bitset<48>, 48>& use, int y, int x, int d) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        int ny = y + dy[d];
        int nx = x + dx[d];
        while (0 <= ny && ny < this->N && 0 <= nx && nx < this->N) {
            if (use[ny][nx]) { return e512pos(-1, -1); }
            if (grid[ny][nx] != 0) { return e512pos(nx, ny); }
            ny += dy[d];
            nx += dx[d];
        }
        return e512pos(-1, -1);
    }
    
    void connect_continue (array< array<int, 48>, 48>& grid, array< array<int, 48>, 48>& uniongrid, array<bitset<48>, 48>& use, vector< vector<e512pos> >& unions, vector<int>& unionk, vector<mmyxyx>& ret, int& action_count_limit, int y, int x) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        static vector<e512pos> q;
        q.clear();
        int u = this->unicnt;
        unions[u].emplace_back(x, y);
        
        q.emplace_back(x, y);
        uniongrid[y][x] = u;
        
        int k = grid[y][x];
        
        unionk[u] = k;
        
        while (q.size() > 0) {
            e512pos p = q.back();
            q.pop_back();
            
            
            for (int d = 0; d < 4; ++d) {
                if (action_count_limit <= 0) { break; }
                int ny = p.y + dy[d];
                int nx = p.x + dx[d];
                bool b = true;
                while (0 <= ny && ny < this->N && 0 <= nx && nx < this->N) {
                    if (use[ny][nx]) { break; }
                    if (grid[ny][nx] == k && uniongrid[ny][nx] == -1) {
                        uniongrid[ny][nx] = u;
                        b = false;
                        break;
                    } else if (grid[ny][nx] != 0) {
                        break;
                    }
                    ny += dy[d];
                    nx += dx[d];
                }
                if (b) { continue; }
                ret.emplace_back(this->line_fill(grid, use, p.y, p.x, d));
                action_count_limit -= 1;
                q.emplace_back(nx, ny);
                unions[u].emplace_back(nx, ny);
            }
        }
        
        this->unicnt += 1;
    }
    
    int connectscore = 0;
    bool ff = true;
    int unicnt = 0;
    vector<mmyxyx> tout1;
    vector<mmyxyx> connect2 (array< array<int, 48>, 48>& grid, int k, vector<mmyxyx>& out1) {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        static array< array<int, 48>, 48> uniongrid;
        static array<bitset<48>, 48> use;
        for (int i = 0; i < this->N; ++i) { use[i].reset(); }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                uniongrid[y][x] = -1;
            }
        }
        static vector< vector<e512pos> > unions;
        static vector< int > unionk;
        if (this->ff) {
            this->ff = false;
            for (int i = 0; i < this->K*52; ++i) {
                unions.emplace_back(vector<e512pos>());
                unions[i].reserve(128);
                unions[i].clear();
                unionk.emplace_back(-1);
            }
            
        } else {
            for (int i = 0; i <= this->unicnt; ++i) {
                unions[i].clear();
                unionk[i] = -1;
            }
            this->unicnt = 0;
            
        }
        
        
        // if (this->ff) {
        //     this->ff = false;
        //     for (int i = 0; i < this->K*102; ++i) {
        //         unions.emplace_back(vector<e512pos>());
        //         unions[i].reserve(128);
        //         unions[i].clear();
        //         unionk.emplace_back(-1);
        //     }
        // } else {
        //     for (int i = 0; i <= this->unicnt; ++i) {
        //         unions[i].clear();
        //         unionk[i] = -1;
        //     }
        //     this->unicnt = 0;
        // }
        
        this->tout1.clear();
        vector<mmyxyx> ret;
        
        int action_count_limit = this->K * 100 - out1.size();
        
        
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (action_count_limit <= 0) { break; }
                if (grid[y][x] != k) { continue; }
                if (uniongrid[y][x] != -1) { continue; }
                bool b = false;
                for (int d = 0; d < 2; ++d) {
                    if (this->can_connect(grid, use, y, x, d) == grid[y][x]) {
                        b = true;
                        break;
                    }
                }
                
                if (b) { this->connect_continue(grid, uniongrid, use, unions, unionk, ret, action_count_limit, y, x); }
                
            }
        }
        
        for (int y = 0; y < this->N; ++y) {
            if (action_count_limit <= 1) { break; }
            for (int x = 0; x < this->N; ++x) {
                if (action_count_limit <= 1) { break; }
                
                
                for (int d = 0; d < 2; d += 1) {
                    if (grid[y][x] == 0) { break; }
                    if (grid[y][x] == k) { break; }
                    if (uniongrid[y][x] != -1) { break; }
                    if (action_count_limit <= 1) { break; }
                    e512pos pa = this->can_connect2(grid, use, y, x, d+0);
                    e512pos pb = this->can_connect2(grid, use, y, x, d+2);
                    if (pa.x < 0 || pb.x < 0) { continue; }
                    if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
                    int ua = uniongrid[pa.y][pa.x];
                    int ub = uniongrid[pb.y][pb.x];
                    if (ua == ub) { continue; }
                    
                    if (ua < 0 || ub < 0) { continue; }
                    if (unionk[ua] != k || unionk[ub] != k) { continue; }
                    if (d == 0) {
                        if (y > 0 && grid[y-1][x] == 0 && use[y-1][x] == false) {
                            this->tout1.emplace_back(y, x, y-1, x);
                            swap(grid[y][x], grid[y-1][x]);
                            action_count_limit -= 1;
                            
                        } else if (y < this->N-1 && grid[y+1][x] == 0 && use[y+1][x] == false) {
                            this->tout1.emplace_back(y, x, y+1, x);
                            swap(grid[y][x], grid[y+1][x]);
                            action_count_limit -= 1;
                            
                        } else {
                            continue;
                        }
                    } else {
                        if (x > 0 && grid[y][x-1] == 0 && use[y][x-1] == false) {
                            this->tout1.emplace_back(y, x, y, x-1);
                            swap(grid[y][x], grid[y][x-1]);
                            action_count_limit -= 1;
                            
                        } else if (x < this->N-1 && grid[y][x+1] == 0 && use[y][x+1] == false) {
                            this->tout1.emplace_back(y, x, y, x+1);
                            swap(grid[y][x], grid[y][x+1]);
                            action_count_limit -= 1;
                            
                        } else {
                            continue;
                        }
                    }
                    
                    
                    ret.emplace_back(this->line_fill(grid, use, pa.y, pa.x, d+2));
                    action_count_limit -= 1;
                    
                    for (auto&& i : unions[ub]) {
                        uniongrid[i.y][i.x] = ua;
                        unions[ua].emplace_back(i);
                    }
                    
                    unions[ub].clear();
                    
                    
                }
                
            }
        }
        
        
        for (int y = 0; y < this->N; ++y) {
            if (action_count_limit <= 1) { break; }
            for (int x = 0; x < this->N; ++x) {
                if (action_count_limit <= 1) { break; }
                if (grid[y][x] == 0) { continue; }
                if (grid[y][x] == k) { continue; }
                
                
                for (int d = 0; d < 2; d += 1) {
                    // if (uniongrid[y][x] != -1) { break; }
                    if (action_count_limit <= 1) { break; }
                    e512pos pa = this->can_connect2(grid, use, y, x, d+0);
                    e512pos pb = this->can_connect2(grid, use, y, x, d+2);
                    if (pa.x < 0 || pb.x < 0) { continue; }
                    if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
                    int ua = uniongrid[pa.y][pa.x];
                    int ub = uniongrid[pb.y][pb.x];
                    if (ua == ub) { continue; }
                    
                    // if (ua < 0) {
                    //     ua = unicnt;
                    //     unicnt += 1;
                    //     unions[ua].emplace_back(pa);
                    // }
                    // if (ub < 0) {
                    //     ub = unicnt;
                    //     unicnt += 1;
                    //     unions[ub].emplace_back(pb);
                    // }
                    
                    
                    
                    if (ua < 0 || ub < 0) { continue; }
                    if (unionk[ua] != k || unionk[ub] != k) { continue; }
                    
                    int acnt = unions[ua].size();
                    int bcnt = unions[ub].size();
                    
                    // if (acnt * bcnt < 8) { continue; }
                    
                    
                    if (uniongrid[y][x] != -1) {
                        int uc = uniongrid[y][x];
                        // if (uc == ua || uc == ub) { continue; }
                        
                        if (uc != ua) {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                            action_count_limit -= 1;
                            for (auto&& i : unions[ua]) {
                                uniongrid[i.y][i.x] = uc;
                                unions[uc].emplace_back(i);
                            }
                            unions[ua].clear();
                        }
                        if (uc != ub) {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+2));
                            action_count_limit -= 1;
                            for (auto&& i : unions[ub]) {
                                uniongrid[i.y][i.x] = uc;
                                unions[uc].emplace_back(i);
                            }
                            unions[ub].clear();
                        }
                        
                        
                        
                        
                    } else {
                        ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                        action_count_limit -= 1;
                        ret.emplace_back(this->line_fill(grid, use, y, x, d+2));
                        action_count_limit -= 1;
                        
                        unions[ua].emplace_back(x, y);
                        uniongrid[y][x] = ua;
                        for (auto&& i : unions[ub]) {
                            uniongrid[i.y][i.x] = ua;
                            unions[ua].emplace_back(i);
                        }
                        
                        unions[ub].clear();
                    }
                    
                }
                
                for (int d = 0; d < 4; d += 1) {
                    // if (uniongrid[y][x] != -1) { break; }
                    if (action_count_limit <= 1) { break; }
                    e512pos pa = this->can_connect2(grid, use, y, x, d+0);
                    e512pos pb = this->can_connect2(grid, use, y, x, (d+1)%4);
                    if (pa.x < 0 || pb.x < 0) { continue; }
                    if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
                    int ua = uniongrid[pa.y][pa.x];
                    int ub = uniongrid[pb.y][pb.x];
                    if (ua == ub) { continue; }
                    
                    // if (ua < 0) {
                    //     ua = unicnt;
                    //     unicnt += 1;
                    //     uniongrid[pa.y][pa.x] = ua;
                    //     unions[ua].emplace_back(pa);
                    // }
                    // if (ub < 0) {
                    //     ub = unicnt;
                    //     unicnt += 1;
                    //     uniongrid[pb.y][pb.x] = ub;
                    //     unions[ub].emplace_back(pb);
                    // }
                    
                    if (ua < 0 || ub < 0) { continue; }
                    if (unionk[ua] != k || unionk[ub] != k) { continue; }
                    
                    int acnt = unions[ua].size();
                    int bcnt = unions[ub].size();
                    
                    // if (acnt * bcnt < 8) { continue; }
                    
                    if (uniongrid[y][x] != -1) {
                        int uc = uniongrid[y][x];
                        // if (uc == ua || uc == ub) { continue; }
                        
                        if (uc != ua) {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                            action_count_limit -= 1;
                            for (auto&& i : unions[ua]) {
                                uniongrid[i.y][i.x] = uc;
                                unions[uc].emplace_back(i);
                            }
                            unions[ua].clear();
                        }
                        if (uc != ub) {
                            ret.emplace_back(this->line_fill(grid, use, y, x, (d+1)%4));
                            action_count_limit -= 1;
                            for (auto&& i : unions[ub]) {
                                uniongrid[i.y][i.x] = uc;
                                unions[uc].emplace_back(i);
                            }
                            unions[ub].clear();
                        }
                        
                        
                        
                    } else {
                        ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                        action_count_limit -= 1;
                        ret.emplace_back(this->line_fill(grid, use, y, x, (d+1)%4));
                        action_count_limit -= 1;
                        
                        unions[ua].emplace_back(x, y);
                        uniongrid[y][x] = ua;
                        for (auto&& i : unions[ub]) {
                            uniongrid[i.y][i.x] = ua;
                            unions[ua].emplace_back(i);
                        }
                        unions[ub].clear();
                    }
                    
                    
                }
                
            }
        }
        
        
        int kk = k-1;
        for (int kkk = 0; kkk < this->K-1; ++kkk) {
            
            k = (kkk + kk + 1) % this->K + 1;
            
            if (action_count_limit <= 0) { break; }
            for (int y = 0; y < this->N; ++y) {
                if (action_count_limit <= 0) { break; }
                for (int x = 0; x < this->N; ++x) {
                    if (action_count_limit <= 0) { break; }
                    if (grid[y][x] != k) { continue; }
                    if (uniongrid[y][x] != -1) { continue; }
                    bool b = false;
                    for (int d = 0; d < 2; ++d) {
                        if (this->can_connect(grid, use, y, x, d) == grid[y][x]) {
                            b = true;
                            break;
                        }
                    }
                    if (b) { this->connect_continue(grid, uniongrid, use, unions, unionk, ret, action_count_limit, y, x); }
                }
            }
            
            
            // for (int y = 0; y < this->N; ++y) {
            //     if (action_count_limit <= 1) { break; }
            //     for (int x = 0; x < this->N; ++x) {
            //         if (action_count_limit <= 1) { break; }
                    
                    
            //         for (int d = 0; d < 2; d += 1) {
            //             if (grid[y][x] == 0) { break; }
            //             if (grid[y][x] == k) { break; }
            //             if (uniongrid[y][x] != -1) { break; }
            //             if (action_count_limit <= 1) { break; }
            //             e512pos pa = this->can_connect2(grid, use, y, x, d+0);
            //             e512pos pb = this->can_connect2(grid, use, y, x, d+2);
            //             if (pa.x < 0 || pb.x < 0) { continue; }
            //             if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
            //             int ua = uniongrid[pa.y][pa.x];
            //             int ub = uniongrid[pb.y][pb.x];
            //             if (ua == ub) { continue; }
            //             if (ua < 0 || ub < 0) { continue; }
            //             if (unionk[ua] != k || unionk[ub] != k) { continue; }
            //             if (d == 0) {
            //                 if (y > 0 && grid[y-1][x] == 0 && use[y-1][x] == false) {
            //                     this->tout1.emplace_back(y, x, y-1, x);
            //                     swap(grid[y][x], grid[y-1][x]);
            //                     action_count_limit -= 1;
                                
            //                 } else if (y < this->N-1 && grid[y+1][x] == 0 && use[y+1][x] == false) {
            //                     this->tout1.emplace_back(y, x, y+1, x);
            //                     swap(grid[y][x], grid[y+1][x]);
            //                     action_count_limit -= 1;
                                
            //                 } else {
            //                     continue;
            //                 }
            //             } else {
            //                 if (x > 0 && grid[y][x-1] == 0 && use[y][x-1] == false) {
            //                     this->tout1.emplace_back(y, x, y, x-1);
            //                     swap(grid[y][x], grid[y][x-1]);
            //                     action_count_limit -= 1;
                                
            //                 } else if (x < this->N-1 && grid[y][x+1] == 0 && use[y][x+1] == false) {
            //                     this->tout1.emplace_back(y, x, y, x+1);
            //                     swap(grid[y][x], grid[y][x+1]);
            //                     action_count_limit -= 1;
                                
            //                 } else {
            //                     continue;
            //                 }
            //             }
                        
                        
                        
                        
                        
            //             int acnt = unions[ua].size();
            //             int bcnt = unions[ub].size();
                        
                        
            //             ret.emplace_back(this->line_fill(grid, use, pa.y, pa.x, d+2));
            //             action_count_limit -= 1;
                        
            //             for (auto&& i : unions[ub]) {
            //                 uniongrid[i.y][i.x] = ua;
            //                 unions[ua].emplace_back(i);
            //             }
                        
            //             unions[ub].clear();
                        
                        
            //         }
                    
            //     }
            // }
        
            
            
            for (int y = 0; y < this->N; ++y) {
                if (action_count_limit <= 1) { break; }
                for (int x = 0; x < this->N; ++x) {
                    if (action_count_limit <= 1) { break; }
                    if (grid[y][x] == 0) { continue; }
                    if (grid[y][x] == k) { continue; }
                    
                    
                    for (int d = 0; d < 2; d += 1) {
                        if (uniongrid[y][x] != -1 && unionk[uniongrid[y][x]] != k) { break; }
                        if (action_count_limit <= 1) { break; }
                        e512pos pa = this->can_connect2(grid, use, y, x, d+0);
                        e512pos pb = this->can_connect2(grid, use, y, x, d+2);
                        if (pa.x < 0 || pb.x < 0) { continue; }
                        if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
                        int ua = uniongrid[pa.y][pa.x];
                        int ub = uniongrid[pb.y][pb.x];
                        if (ua == ub) { continue; }
                        if (ua < 0 || ub < 0) { continue; }
                        if (unionk[ua] != k || unionk[ub] != k) { continue; }
                        
                        
                        int acnt = unions[ua].size();
                        int bcnt = unions[ub].size();
                        // if (acnt * bcnt < 8) { continue; }////
                        
                        
                        if (uniongrid[y][x] != -1) {
                            
                            int uc = uniongrid[y][x];
                            // if (uc == ua || uc == ub) { continue; }
                            
                            if (uc != ua) {
                                ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                                action_count_limit -= 1;
                                for (auto&& i : unions[ua]) {
                                    uniongrid[i.y][i.x] = uc;
                                    unions[uc].emplace_back(i);
                                }
                                unions[ua].clear();
                            }
                            if (uc != ub) {
                                ret.emplace_back(this->line_fill(grid, use, y, x, d+2));
                                action_count_limit -= 1;
                                for (auto&& i : unions[ub]) {
                                    uniongrid[i.y][i.x] = uc;
                                    unions[uc].emplace_back(i);
                                }
                                unions[ub].clear();
                            }
                            
                        } else {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                            action_count_limit -= 1;
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+2));
                            action_count_limit -= 1;
                            
                            unions[ua].emplace_back(x, y);
                            uniongrid[y][x] = ua;
                            for (auto&& i : unions[ub]) {
                                uniongrid[i.y][i.x] = ua;
                                unions[ua].emplace_back(i);
                            }
                            unions[ub].clear();
                        }
                    }
                    
                    for (int d = 0; d < 4; d += 1) {
                        if (uniongrid[y][x] != -1 && unionk[uniongrid[y][x]] != k) { break; }
                        if (action_count_limit <= 1) { break; }
                        e512pos pa = this->can_connect2(grid, use, y, x, d+0);
                        e512pos pb = this->can_connect2(grid, use, y, x, (d+1)%4);
                        if (pa.x < 0 || pb.x < 0) { continue; }
                        if (grid[pa.y][pa.x] != k || grid[pb.y][pb.x] != k) { continue; }
                        int ua = uniongrid[pa.y][pa.x];
                        int ub = uniongrid[pb.y][pb.x];
                        if (ua == ub) { continue; }
                        if (ua < 0 || ub < 0) { continue; }
                        if (unionk[ua] != k || unionk[ub] != k) { continue; }
                        
                        int acnt = unions[ua].size();
                        int bcnt = unions[ub].size();
                        
                        // if (acnt * bcnt < 8) { continue; }////
                        
                        if (uniongrid[y][x] != -1) {
                            
                            int uc = uniongrid[y][x];
                            // if (uc == ua || uc == ub) { continue; }
                            
                            if (uc != ua) {
                                ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                                action_count_limit -= 1;
                                for (auto&& i : unions[ua]) {
                                    uniongrid[i.y][i.x] = uc;
                                    unions[uc].emplace_back(i);
                                }
                                unions[ua].clear();
                            }
                            if (uc != ub) {
                                ret.emplace_back(this->line_fill(grid, use, y, x, (d+1)%4));
                                action_count_limit -= 1;
                                for (auto&& i : unions[ub]) {
                                    uniongrid[i.y][i.x] = uc;
                                    unions[uc].emplace_back(i);
                                }
                                unions[ub].clear();
                            }
                            
                            
                            
                        } else {
                            ret.emplace_back(this->line_fill(grid, use, y, x, d+0));
                            action_count_limit -= 1;
                            ret.emplace_back(this->line_fill(grid, use, y, x, (d+1)%4));
                            action_count_limit -= 1;
                            
                            unions[ua].emplace_back(x, y);
                            uniongrid[y][x] = ua;
                            for (auto&& i : unions[ub]) {
                                uniongrid[i.y][i.x] = ua;
                                unions[ua].emplace_back(i);
                            }
                            unions[ub].clear();
                        }
                    }
                }
            }
            
        }
        
        
        for (int i = 0; i < this->tout1.size(); ++i) {
            int j = this->tout1.size() - 1 - i;
            swap(grid[this->tout1[j].ay][this->tout1[j].ax], grid[this->tout1[j].by][this->tout1[j].bx]);
        }
        
        
        
        
        this->connectscore = 0;
        
        int t;
        int kcnts[6];
        for (int i = 0; i < unions.size(); ++i) {
            for (int m = 0; m <= this->K; ++m) {
                kcnts[m] = 0;
            }
            for (auto&& p : unions[i]) {
                kcnts[grid[p.y][p.x]] += 1;
            }
            
            
            
            t = 0;
            for (int m = 0; m <= this->K; ++m) {
                this->connectscore += this->scores[kcnts[m]];
                t += kcnts[m];
            }
            for (int m = this->K; m >= 0; --m) {
                t -= kcnts[m];
                this->connectscore -= t * kcnts[m];
            }
        }
        
        
        
        // for (int y = 0; y < this->N; ++y) {
        //     string s;
        //     for (int x = 0; x < this->N; ++x) {
        //         string t;
        //         if (uniongrid[y][x] >= 0) { t = to_string(uniongrid[y][x]); }
        //         for (int i = t.size(); i < 4; ++i) {
        //             s += " ";
        //         }
        //         s += t;
        //     }
        //     fdebug(s);
        // }
        
        
        // unordered_set<e512pos> us;
        // for (auto&& i : ret) {
        //     int a = i.ax + this->N * i.ay;
        //     int b = i.bx + this->N * i.by;
        //     us.emplace(min(a, b), max(a, b));
        // }
        // if (us.size() < ret.size()) { this->connectscore = 10000; }
        
        
        
        
        return ret;
    }
    
    
    
    
    
    
    vector<mmyxyx> bestout1;
    vector<mmyxyx> bestout2;
    int bestconnectscore = 0;
    void solve () {
        static const int dy[4] = {0, 1, 0, -1};
        static const int dx[4] = {1, 0, -1, 0};
        
        vector<mmyxyx> out1;
        
        
        int bestscore2 = 0;
        int bestk = 0;
        
        this->bestconnectscore = 0;
        for (int i = 0; i < this->K; ++i) {
            vector<mmyxyx> tmp = this->connect2(this->rawgrid, i+1, out1);
            if (this->connectscore > bestscore2) {
                this->bestconnectscore = this->connectscore;
                bestk = i;
            }
        }
        
        // vector<mmyxyx> tmp = this->solve2(this->rawgrid, out1, bestk);
        // {
        //     this->bestout1 = this->tout1;
        //     this->bestout2 = tmp;
            
        // }

        
        
        for (int k = 0; k < this->K; ++k) {
            int bestscore = 0;
            int stime = 0;
            int etime = (600 / this->K);
            double satime = etime - stime;
            StopWatch sw;
            array< array<int, 48>, 48> grid = this->rawgrid;
            out1.clear();
            while (sw.get_milli_time() < etime && out1.size() < this->K * 100) {
                int ntime = sw.get_milli_time();
                int g = 32;
                if (ntime > 100 / this->K) { g = 16; }
                if (ntime > 300 / this->K) { g = 2; }
                int temp = g + (0 - g) * (double)(ntime-stime) / satime;
                for (int i = 0; i < 8; ++i) {
                    int x = xrnd() % this->N;
                    int y = xrnd() % this->N;
                    int d = xrnd() % 4;
                    int nx = x+dx[d];
                    int ny = y+dy[d];
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    if (grid[y][x] == 0) { continue; }
                    if (grid[ny][nx] > 0) { continue; }
                    
                    swap(grid[y][x], grid[ny][nx]);
                    
                    out1.emplace_back(y, x, ny, nx);
                    vector<mmyxyx> tmp = this->solve2(grid, out1, k);
                    int score = this->bestconnectscore;
                    if (score > bestscore + temp) {
                        for (int j = 0; j < this->tout1.size(); ++j) {
                            swap(grid[this->tout1[j].ay][this->tout1[j].ax], grid[this->tout1[j].by][this->tout1[j].bx]);
                            out1.emplace_back(this->tout1[j]);
                        }
                        bestscore = score;
                        if (bestscore > bestscore2) {
                            this->bestout1 = out1;
                            this->bestout2 = tmp;
                            bestscore2 = bestscore;
                            bestk = k;
                        }
                        
                    } else {
                        swap(grid[y][x], grid[ny][nx]);
                        out1.pop_back();
                    }
                }
                if (temp >= 2) {
                    int x = xrnd() % this->N;
                    int y = xrnd() % this->N;
                    int d = xrnd() % 4;
                    int d2 = xrnd() % 4;
                    int nx = x+dx[d];
                    int ny = y+dy[d];
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    int nx2 = nx+dx[d2];
                    int ny2 = ny+dy[d2];
                    if (nx2 < 0 || nx2 >= this->N || ny2 < 0 || ny2 >= this->N) { continue; }
                    if (grid[y][x] == 0) { continue; }
                    if (grid[ny][nx] > 0) { continue; }
                    if (grid[ny2][nx2] > 0) { continue; }
                    
                    swap(grid[y][x], grid[ny][nx]);
                    swap(grid[ny][nx], grid[ny2][nx2]);
                    
                    out1.emplace_back(y, x, ny, nx);
                    out1.emplace_back(ny, nx, ny2, nx2);
                    vector<mmyxyx> tmp = this->solve2(grid, out1, k);
                    int score = this->bestconnectscore;
                    if (score > bestscore + temp) {
                        for (int j = 0; j < this->tout1.size(); ++j) {
                            swap(grid[this->tout1[j].ay][this->tout1[j].ax], grid[this->tout1[j].by][this->tout1[j].bx]);
                            out1.emplace_back(this->tout1[j]);
                        }
                        bestscore = score;
                        if (bestscore > bestscore2) {
                            this->bestout1 = out1;
                            this->bestout2 = tmp;
                            bestscore2 = bestscore;
                            bestk = k;
                        }
                    } else {
                        swap(grid[ny][nx], grid[ny2][nx2]);
                        swap(grid[y][x], grid[ny][nx]);
                        out1.pop_back();
                        out1.pop_back();
                    }
                }
            }
        }
        
        
        
        
        
        
        int m = 1;
        int cnt = 0;
        for (int k = 0; k < 512; ++k) {
            int bestscore = 0;
            int etime = max(0, (int)(2900-this->sw.get_milli_time()));
            StopWatch sw;
            array< array<int, 48>, 48> grid = this->rawgrid;
            out1.clear();
            int lcnt = 0;
            while (sw.get_milli_time() < etime && lcnt < 512) {
                for (int i = 0; i < 8; ++i) {
                    int x = xrnd() % this->N;
                    int y = xrnd() % this->N;
                    int d = xrnd() % 4;
                    int nx = x+dx[d];
                    int ny = y+dy[d];
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    if (grid[y][x] == 0) { continue; }
                    if (grid[ny][nx] > 0) { continue; }
                    
                    swap(grid[y][x], grid[ny][nx]);
                    
                    out1.emplace_back(y, x, ny, nx);
                    vector<mmyxyx> tmp = this->solve2(grid, out1, bestk);
                    int score = this->bestconnectscore;
                    if (score > bestscore) {
                        lcnt = 0;
                        for (int j = 0; j < this->tout1.size(); ++j) {
                            swap(grid[this->tout1[j].ay][this->tout1[j].ax], grid[this->tout1[j].by][this->tout1[j].bx]);
                            out1.emplace_back(this->tout1[j]);
                        }
                        bestscore = score;
                        if (bestscore > bestscore2) {
                            this->bestout1 = out1;
                            this->bestout2 = tmp;
                            bestscore2 = bestscore;
                        }
                        
                    } else {
                        swap(grid[y][x], grid[ny][nx]);
                        out1.pop_back();
                        lcnt += 1;
                    }
                    cnt += 1;
                }
                
                {
                    int x = xrnd() % this->N;
                    int y = xrnd() % this->N;
                    int d = xrnd() % 4;
                    int d2 = xrnd() % 4;
                    int nx = x+dx[d];
                    int ny = y+dy[d];
                    if (nx < 0 || nx >= this->N || ny < 0 || ny >= this->N) { continue; }
                    int nx2 = nx+dx[d2];
                    int ny2 = ny+dy[d2];
                    if (nx2 < 0 || nx2 >= this->N || ny2 < 0 || ny2 >= this->N) { continue; }
                    if (grid[y][x] == 0) { continue; }
                    if (grid[ny][nx] > 0) { continue; }
                    if (grid[ny2][nx2] > 0) { continue; }
                    
                    swap(grid[y][x], grid[ny][nx]);
                    swap(grid[ny][nx], grid[ny2][nx2]);
                    
                    out1.emplace_back(y, x, ny, nx);
                    out1.emplace_back(ny, nx, ny2, nx2);
                    vector<mmyxyx> tmp = this->solve2(grid, out1, bestk);
                    int score = this->bestconnectscore;
                    if (score > bestscore) {
                        lcnt = 0;
                        for (int j = 0; j < this->tout1.size(); ++j) {
                            swap(grid[this->tout1[j].ay][this->tout1[j].ax], grid[this->tout1[j].by][this->tout1[j].bx]);
                            out1.emplace_back(this->tout1[j]);
                        }
                        bestscore = score;
                        if (bestscore > bestscore2) {
                            this->bestout1 = out1;
                            this->bestout2 = tmp;
                            bestscore2 = bestscore;
                        }
                    } else {
                        swap(grid[ny][nx], grid[ny2][nx2]);
                        swap(grid[y][x], grid[ny][nx]);
                        out1.pop_back();
                        out1.pop_back();
                        lcnt += 1;
                    }
                    cnt += 1;
                }
                
            }
        }
        
        
        
        
        
        
        pdebug("s >", bestscore2, "c >", cnt);
        // this->solve2(bestgrid);
    }
    
    
    vector<mmyxyx> solve2 (array< array<int, 48>, 48>& grid, vector<mmyxyx>& out1, int k) {
        vector<mmyxyx> ret = this->connect2(grid, 1 + k, out1);
        this->bestconnectscore = this->connectscore;
        
        // for (int i = 1; i <= this->K; ++i) {
        //     vector<mmyxyx> tmp = this->connect2(grid, i, out1);
        //     if (this->connectscore > this->bestconnectscore) {
        //         ret = tmp;
        //         this->bestconnectscore = this->connectscore;
        //     }
        // }
        
        return ret;
    }
    
    void output () {
        pdebug("t", this->sw.get_milli_time());
        cout << this->bestout1.size() << endl;
        for (int i = 0; i < this->bestout1.size(); ++i) {
            mmyxyx t = this->bestout1[i];
            cout << print(t.ay, t.ax, t.by, t.bx) << endl;
        }
        
        
        
        int cnt = min(this->K * 100 - (int)this->bestout1.size(), (int)this->bestout2.size());
        
        cout << cnt << endl;
        for (int i = 0; i < cnt; ++i) {
            mmyxyx t = this->bestout2[i];
            cout << print(t.ay, t.ax, t.by, t.bx) << endl;
        }
        
    }
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    cout.flush();
    return 0;
}

