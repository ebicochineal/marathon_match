// C++11
// #include <algorithm>
// #include <cstdlib>
// #include <iostream>
// #include <map>
// #include <sstream>
// #include <vector>
// #include <set>
// #include <string>

// using namespace std;
#include <algorithm>
#include <random>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <utility>

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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

inline double distance (const int ax, const int ay, const int bx, const int by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
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

class clitem {
public:
    int y;
    int x;
    int8_t c;
    clitem (int y, int x, char c) {
        this->y = y;
        this->x = x;
        this->c = c;
    }
    
    clitem (string s) {
        int n = 0;
        string tmp = "";
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') {
                if (n == 0) {
                    this->y = stoi(tmp);
                } else {
                    this->x = stoi(tmp);
                }
                tmp = "";
                n += 1;
            } else {
                tmp += s[i];
            }
        }
        this->c = s[s.size()-1];
    }
};

class ray {
public:
    int sy, sx, ey, ex;
    int8_t c;
    ray (int sy, int sx, int ey, int ex, int8_t c) {
        this->sy = sy;
        this->sx = sx;
        this->ey = ey;
        this->ex = ex;
        this->c = c;
    }
};

class ray4 {
public:
    vector<ray> l;
    vector<ray> r;
    vector<ray> u;
    vector<ray> d;
    
    void addray (ray r) {
        if (r.sx < r.ex) { this->l.emplace_back(r); }
        if (r.sx > r.ex) { this->r.emplace_back(r); }
        if (r.sy < r.ey) { this->u.emplace_back(r); }
        if (r.sy > r.ey) { this->d.emplace_back(r); }
    }
    
};

template<class T, int I>
class size_priority_container_min {
public:
    priority_queue< pair<int, T> > v;
    int max = I;
    
    void emplace (int i, T t) {
        if (this->v.size() < this->max) {
            this->v.emplace(i, t);
        } else {
            this->v.emplace(i, t);
            this->v.pop();
        }
    }
    
    vector<T> to_vector () {
        priority_queue< pair<int, T> > v = this->v;
        vector<T> r(v.size());
        for (int i = 0; i < r.size(); ++i) {
            r[r.size() - 1 - i] = v.top().second;
            v.pop();
        }
        return r;
    }
};
template<class T, int I>
class size_priority_container_max {
public:
    priority_queue< pair<int, T>, vector< pair<int, T> >, greater< pair<int, T> > > v;
    int max = I;
    
    void emplace (int i, T t) {
        if (this->v.size() < this->max) {
            this->v.emplace(i, t);
        } else {
            this->v.emplace(i, t);
            this->v.pop();
        }
    }
    
    vector<T> to_vector () {
        priority_queue< pair<int, T>, vector< pair<int, T> >, greater< pair<int, T> > > v = this->v;
        vector<T> r(v.size());
        for (int i = 0; i < r.size(); ++i) {
            r[r.size() - 1 - i] = v.top().second;
            v.pop();
        }
        return r;
    }
};

class CrystalLighting {
public:
    int H, W;
    vector<clitem> crystals;
    vector< vector<int8_t> > targetBoard;
    vector< vector<int8_t> > blankBoard;
    int costLantern;
    int costMirror;
    int costObstacle;
    int maxMirrors;
    int maxObstacles;
    vector< vector<int8_t> > colormap = vector< vector<int8_t> >(6, vector<int8_t>(6, 0));
    
    vector< vector< vector<clitem> > > lem;
    vector< vector< vector<mpos> > > lcem;
    
    
    StopWatch sw;
    
    vector<string> placeItems(vector<string> targetBoard, int costLantern, int costMirror, int costObstacle, int maxMirrors, int maxObstacles) {
        //this->targetBoard = targetBoard;
        this->costLantern = costLantern;
        this->costMirror = costMirror;
        this->costObstacle = costObstacle;
        this->maxObstacles = maxObstacles;
        this->H = targetBoard.size();
        this->W = targetBoard[0].size();
        for (int i = 0; i < this->H; ++i) {
            vector<int8_t> vi(this->W);
            for (int j = 0; j < this->W; ++j) {
                vi[j] = targetBoard[i][j];
                if (vi[j] >= '1' && vi[j] <= '6') { this->crystals.emplace_back(i, j, vi[j]); }
            }
            this->targetBoard.emplace_back(vi);
            this->blankBoard.emplace_back(vector<int8_t>(this->W, '.'));
        }
        this->init_color_map();
        
        this->lem = this->lantern_effectrange_map();
        this->lcem = lantern_collision_effectrange_map();
        
        this->init_bp();
        vector<clitem> bestret = this->test2();
        int bestscore = this->all_score(bestret);
        
        vector<clitem> tmpret = bestret;
        int tmpscore = bestscore;
        
        int cnt = 0;
        
        while (this->sw.get_milli_time() < 1500) {
            for (int v = 0; v < 10; ++v) {
                vector<clitem> ret = this->test2();
                int score = this->all_score(ret);
                if (score > bestscore) {
                    bestret = ret;
                    bestscore = score;
                }
                cnt += 1;
            }
        }
        
        while (this->sw.get_milli_time() < 2000) {
            for (int v = 0; v < 10; ++v) {
                vector<clitem> ret;
                int a = xrnd() % bestret.size();
                for (int j = 0; j < bestret.size(); ++j) {
                    if (j == a) { continue; }
                    ret.emplace_back(bestret[j]);
                }
                int score = this->all_score(ret);
                if (score > bestscore) {
                    bestret = ret;
                    bestscore = score;
                }
            }
        }
        
        vector< vector<int8_t> > b = this->targetBoard;
        
        for (auto &i : bestret) { b[i.y][i.x] = i.c; }
        int mo = maxObstacles;
        int mm = maxMirrors;
        int lcnt = 0;
        for (int k = 0; k < 256; ++k) {
            if (this->sw.get_milli_time() > 9500) { break; }
            // for (int z = 0; z < 32; ++z) {
            //     vector<clitem> tret;
            //     int tscore = bestscore;
            //     mpos p;
            //     for (int i = 0; i < this->H; ++i) {
            //         if (i % 10 == 0 && this->sw.get_milli_time() > 8000) { break; }
            //         for (int j = 0; j < this->W; ++j) {
            //             vector<clitem> ret = bestret;
            //             if (b[i][j] != '.' || mo < 1) { continue; }
            //             ret.emplace_back(i, j, 'X');
            //             int score = this->all_score(ret);
            //             if (score > tscore) {
            //                 tret = ret;
            //                 tscore = score;
            //                 p.y = i;
            //                 p.x = j;
            //             }
            //         }
            //     }
            //     if (tscore > bestscore) {
            //         bestscore = tscore;
            //         bestret = tret;
            //         b[p.y][p.x] = 'X';
            //         mo -= 1;
            //     }
            // }
            
            for (int i = 0; i < this->H; ++i) {
                if (i % 20 == 0 && this->sw.get_milli_time() > 9500) { break; }
                for (int j = 0; j < this->W; ++j) {
                    lcnt += 1;
                    vector<clitem> ret = bestret;
                    if (b[i][j] != '.' || mo < 1) { continue; }
                    ret.emplace_back(i, j, 'X');
                    int score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = 'X';
                        mo -= 1;
                    }
                }
            }
            
            for (int i = 0; i < this->H; ++i) {
                if (i % 20 == 0 && this->sw.get_milli_time() > 9500) { break; }
                for (int j = 0; j < this->W; ++j) {
                    lcnt += 1;
                    vector<clitem> ret = bestret;
                    if (b[i][j] != '.' || mm < 1) { continue; }
                    ret.emplace_back(i, j, '/');
                    int score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = '/';
                        mm -= 1;
                        continue;
                    }
                    ret = bestret;
                    if (b[i][j] != '.' || mm < 1) { continue; }
                    ret.emplace_back(i, j, '\\');
                    score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = '\\';
                        mm -= 1;
                    }
                }
            }
            
            for (int i = 0; i < this->H; ++i) {
                if (i % 20 == 0 && this->sw.get_milli_time() > 9500) { break; }
                for (int j = 0; j < this->W; ++j) {
                    lcnt += 1;
                    vector<clitem> ret = bestret;
                    if (b[i][j] != '.') { continue; }
                    ret.emplace_back(i, j, '1');
                    int score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = '1';
                        continue;
                    }
                    ret = bestret;
                    if (b[i][j] != '.') { continue; }
                    ret.emplace_back(i, j, '2');
                    score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = '2';
                    }
                    
                    ret = bestret;
                    if (b[i][j] != '.') { continue; }
                    ret.emplace_back(i, j, '4');
                    score = this->all_score(ret);
                    if (score > bestscore) {
                        bestret = ret;
                        bestscore = score;
                        b[i][j] = '4';
                        continue;
                    }
                }
            }
            
            // move
            bool f = true;
            for (int z = 0; z < 10 && f == true; ++z) {
                f = false;
                int mcnt = 0;
                for (auto &i : bestret) {
                    lcnt += 1;
                    if (mcnt % 50 == 0 && this->sw.get_milli_time() > 9500) { break; }
                    vector<clitem> tret;
                    for (auto &c : bestret) { if (i.x != c.x || i.y != c.y) { tret.emplace_back(c); } }
                    
                    int tscore = bestscore;
                    int ty;
                    int tx;
                    int tc;
                    for (auto &c : {'1', '2', '4', 'X'}) {
                        if ('X' == c && mo < 1) { continue; }
                        if ('/' == c && mm < 1) { continue; }
                        if ('\\' == c && mm < 1) { continue; }
                        for (int y = max(i.y - 1, 0); y < min(i.y + 2, this->H); ++y) {
                            for (int x = max(i.x - 1, 0); x < min(i.x + 2, this->W); ++x) {
                                if (i.y == y && i.x == x) { continue; }
                                if (b[y][x] != '.') { continue; }
                                vector<clitem> ret = tret;
                                ret.emplace_back(y, x, c);
                                int score = this->all_score(ret);
                                if (score > tscore) {
                                    tscore = score;
                                    ty = y;
                                    tx = x;
                                    tc = c;
                                }
                            }
                        }
                    }
                    
                    if (tscore > bestscore) {
                        b[i.y][i.x] = '.';
                        b[ty][tx] = tc;
                        bestret = tret;
                        bestret.emplace_back(ty, tx, tc);
                        if ('X' == tc) { mo -= 1; }
                        if ('/' == tc) { mm -= 1; }
                        if ('\\' == tc) { mm -= 1; }
                        f = true;
                        break;
                    }
                    
                    mcnt += 1;
                }
            }
            
        
        }
        while (this->sw.get_milli_time() < 9800) {
            for (int z = 0; z < 10; ++z) {
                vector<clitem> ret;
                int a = xrnd() % bestret.size();
                for (int j = 0; j < bestret.size(); ++j) {
                    if (j == a) { continue; }
                    ret.emplace_back(bestret[j]);
                }
                int score = this->all_score(ret);
                if (score > bestscore) {
                    bestret = ret;
                    bestscore = score;
                }
            }
            
        }
        
        cerr << print("Score", this->all_score(bestret), "Time", this->sw.get_milli_time(), "cnt", cnt, "retcnt", bestret.size(), lcnt) << endl;
        return this->to_strings(bestret);
    }
    // .:46 /:47 \\:92 X:88  1:49 2:50 3:51 4:52 5:53 6:54
    
    vector<string> to_strings (vector<clitem> items) {
        vector<string> ret;
        for (auto &i : items) {
            string s = {i.c};
            ret.emplace_back(to_string(i.y) + " " + to_string(i.x) + " " + s);
        }
        return ret;
    }
    
    vector<mpos> blank_pos () {
        vector<mpos> ret;
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < this->W; ++j) {
                if (this->targetBoard[i][j] == '.') {
                    ret.emplace_back(j, i);
                }
            }
        }
        return ret;
    }
    
    vector<clitem> lantern_effectrange (int y, int x) {
        // l u r d
        static const int dy[4] = {0, -1, 0, 1};
        static const int dx[4] = {-1, 0, 1, 0};
        
        vector<clitem> ret;
        int8_t c;
        for (int i = 0; i < 4; ++i) {
            int py = y;
            int px = x;
            if (this->targetBoard[py][px] != '.') { continue; }
            while (true) {
                py += dy[i];
                px += dx[i];
                if (py < 0 || py >= this->H || px < 0 || px >= this->W) { break; }
                c = this->targetBoard[py][px];
                if (c == 'X') { break; }
                if (c != '.') {
                    ret.emplace_back(py, px, c);
                    break;
                }
            }
        }
        return ret;
    }
    
    vector< vector< vector<clitem> > > lantern_effectrange_map () {
        vector< vector< vector<clitem> > > ret = vector< vector< vector<clitem> > >(this->H, vector< vector<clitem> >(this->W, vector<clitem>()));
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < this->W; ++j) {
                if (this->targetBoard[i][j] == '.') {
                    ret[i][j] = this->lantern_effectrange(i, j);
                }
            }
        }
        return ret;
    }
    
    vector<mpos> lantern_collision_effectrange (int y, int x) {
        // l u r d
        static const int dy[4] = {0, -1, 0, 1};
        static const int dx[4] = {-1, 0, 1, 0};
        vector<mpos> ret;
        ret.emplace_back(x, y);
        int8_t c;
        for (int i = 0; i < 4; ++i) {
            int py = y;
            int px = x;
            while (true) {
                py += dy[i];
                px += dx[i];
                if (py < 0 || py >= this->H || px < 0 || px >= this->W) { break; }
                c = this->targetBoard[py][px];
                if (c != '.') {
                    break;
                } else {
                    ret.emplace_back(px, py);
                }
            }
        }
        return ret;
    }
    
    vector< vector< vector<mpos> > > lantern_collision_effectrange_map () {
        vector< vector< vector<mpos> > > ret = vector< vector< vector<mpos> > >(this->H, vector< vector<mpos> >(this->W, vector<mpos>()));
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < this->W; ++j) {
                if (this->targetBoard[i][j] == '.') {
                    ret[i][j] = this->lantern_collision_effectrange(i, j);
                }
            }
        }
        return ret;
    }
    
    void fill_lantern_collision_effectrange_map (vector< vector< bool > > &flcem, int y, int x) {
        // l u r d
        static const int dy[4] = {0, -1, 0, 1};
        static const int dx[4] = {-1, 0, 1, 0};
        
        for (auto &i : this->lcem[y][x]) {
            flcem[i.y][i.x] = true;
        }
    }
    
    
    /////
    inline int put_test_color_score (int color, clitem &crystal, int &ray_color) {
        static const int bcols6[6] = {1, 1<<1, 1+(1<<1), 1<<2, 1+(1<<2), (1<<1)+(1<<2)};
        static const int bcols[3] = {1, 2, 4};
        static const int points[6] = {20, 20, 30, 20, 30, 30};
        
        int crystal_color = bcols6[crystal.c - '1'];
        int point = points[crystal.c - '1'];
        int prev_achievement = (crystal_color ==  ray_color);
        int next_achievement = (crystal_color == (ray_color | bcols[color]));
        
        if (prev_achievement == true && next_achievement == false) { return -point; }
        if (prev_achievement == false && next_achievement == true) { return point; }
        
        int ret = crystal_color > (ray_color | bcols[color]);
        return ret * 4;
    }
    
    
    vector<clitem> test () {
        static const int8_t col[3] = {'1', '2', '4'};
        
        static const int bcols[6] = {1, 2, 4};
        vector<clitem> ret;
        vector<mpos> bp = this->blank_pos();
        vector< vector< vector<clitem> > > lem = this->lem;
        
        vector< vector<int> > ccm = vector< vector<int> >(this->H, vector<int>(this->W, 0));
        
        vector< vector< bool > > flcem = vector< vector< bool > >(this->H, vector< bool >(this->W, false));
        
        mt19937 mt(xrnd());
        shuffle(bp.begin(), bp.end(), mt);
        int score = 0;
        bool re = true;
        while (re) {
            re = false;
            
            int tscore = 0;
            int tindex = 0;
            mpos t;
            
            for (auto &i : bp) {
                if (flcem[i.y][i.x] == false) {
                    int index = 0;
                    int score0 = 0;
                    int score1 = 0;
                    int score2 = 0;
                    int putscore = 0;
                    for (auto &j : lem[i.y][i.x]) {
                        score0 += this->put_test_color_score(0, j, ccm[j.y][j.x]);
                        score1 += this->put_test_color_score(1, j, ccm[j.y][j.x]);
                        score2 += this->put_test_color_score(2, j, ccm[j.y][j.x]);
                    }
                    
                    if (score0 >= score1 && score0 >= score2) {
                        putscore = score0;
                        index = 0;
                    }
                    if (score1 >= score0 && score1 >= score2) {
                        putscore = score1;
                        index = 1;
                    }
                    if (score2 >= score1 && score2 >= score0) {
                        putscore = score2;
                        index = 2;
                    }
                    
                    if (putscore > tscore) {
                        tscore = putscore;
                        tindex = index;
                        t = i;
                    }
                }
            }
            if (tscore > 0) {
                ret.emplace_back(t.y, t.x, col[tindex]);
                this->fill_lantern_collision_effectrange_map (flcem, t.y, t.x);
                for (auto &j : lem[t.y][t.x]) {
                    ccm[j.y][j.x] |= bcols[tindex];
                }
                score += tscore;
                re = true;
            }
        }
        
        
        return ret;
    }
    
    vector< vector< vector<mpos> > > bp;
    void init_bp () {
        for (int n = 2; n < 16; n+=2) {
            vector< vector<mpos> > v = vector< vector<mpos> >(n*n, vector<mpos>());
            for (auto &i : this->blank_pos()) {
                int y = i.y / (this->H / n + n);
                int x = i.x / (this->W / n + n);
                int p = y * n + x;
                v[p].emplace_back(i);
            }
            
            // for (auto &i : this->blank_pos()) {
            //     int y = i.y / (this->H / n + n) + 1;
            //     int x = i.x / (this->W / n + n);
            //     int p = y * n + x;
            //     v[p].emplace_back(i);
            // }
            
            // for (auto &i : this->blank_pos()) {
            //     int y = i.y / (this->H / n + n);
            //     int x = i.x / (this->W / n + n) + 1;
            //     int p = y * n + x;
            //     v[p].emplace_back(i);
            // }
            
            
            // for (auto &i : this->blank_pos()) {
            //     int y = i.y / (this->H / n + n) + 1;
            //     int x = i.x / (this->W / n + n) + 1;
            //     int p = y * n + x;
            //     v[p].emplace_back(i);
            // }
            
            this->bp.emplace_back(v);
        }
    }
    
    void shuffle_bp (int n) {
        mt19937 mt(xrnd());
        for (auto &i : this->bp[n]) {
            shuffle(i.begin(), i.end(), mt);
        }
    }
    
    vector<clitem> test2 () {
        static const int8_t col[3] = {'1', '2', '4'};
        // static const int bcols[6] = {1, 1<<1, 1+(1<<1), 1<<2, 1+(1<<2), (1<<1)+(1<<2)};
        static const int bcols6[6] = {1, 2, 4};
        vector<clitem> ret;
        //vector<mpos> bp = this->blank_pos();
        
        
        
        
        
        vector< vector< vector<clitem> > > lem = this->lem;
        
        // old color_score
        // vector< vector< vector<int8_t> > > ccm = vector< vector< vector<int8_t> > >(this->H, vector< vector<int8_t> >(this->W, vector<int8_t>()));
        
        // put_test_color_score
        vector< vector<int> > ccm = vector< vector<int> >(this->H, vector<int>(this->W, 0));
        
        vector< vector< bool > > flcem = vector< vector< bool > >(this->H, vector< bool >(this->W, false));
        
        // int n = 8 + xrnd() % 8;
        // vector< vector<mpos> > bp = vector< vector<mpos> >((n+1)*(n+1), vector<mpos>());
        
        // for (auto &i : this->blank_pos()) {
        //     int y = i.y / (this->H / n + n);
        //     int x = i.x / (this->W / n + n);
        //     int p = y * n + x;
        //     bp[p].emplace_back(i);
        // }
        
        // for (auto &i : this->blank_pos()) {
        //     int y = i.y / (this->H / n + n) + 1;
        //     int x = i.x / (this->W / n + n);
        //     int p = y * n + x;
        //     bp[p].emplace_back(i);
        // }
        
        
        // for (auto &i : this->blank_pos()) {
        //     int y = i.y / (this->H / n + n);
        //     int x = i.x / (this->W / n + n) + 1;
        //     int p = y * n + x;
        //     bp[p].emplace_back(i);
        // }
        
        
        // for (auto &i : this->blank_pos()) {
        //     int y = i.y / (this->H / n + n) + 1;
        //     int x = i.x / (this->W / n + n) + 1;
        //     int p = y * n + x;
        //     bp[p].emplace_back(i);
        // }
        
        // mt19937 mt(xrnd());
        // for (auto &i : bp) {
        //     shuffle(i.begin(), i.end(), mt);
        // }
        
        
        int n = xrnd() % this->bp.size();
        
        this->shuffle_bp(n);
        int score = 0;
        bool re = true;
        while (re) {
            re = false;
            
            for (auto &z : this->bp[n]) {
                int tscore = 0;
                int tindex = 0;
                mpos t;
                
                for (auto &i : z) {
                    if (flcem[i.y][i.x] == false) {
                        int index = 0;
                        int score0 = 0;
                        int score1 = 0;
                        int score2 = 0;
                        int putscore = 0;
                        for (auto &j : lem[i.y][i.x]) {
                            score0 += this->put_test_color_score(0, j, ccm[j.y][j.x]);
                            score1 += this->put_test_color_score(1, j, ccm[j.y][j.x]);
                            score2 += this->put_test_color_score(2, j, ccm[j.y][j.x]);
                        }
                        
                        if (score0 >= score1 && score0 >= score2) {
                            putscore = score0;
                            index = 0;
                        }
                        if (score1 >= score0 && score1 >= score2) {
                            putscore = score1;
                            index = 1;
                        }
                        if (score2 >= score1 && score2 >= score0) {
                            putscore = score2;
                            index = 2;
                        }
                        
                        if (putscore > tscore) {
                            tscore = putscore;
                            tindex = index;
                            t = i;
                        }
                    }
                }
                if (tscore > 0) {
                    ret.emplace_back(t.y, t.x, col[tindex]);
                    this->fill_lantern_collision_effectrange_map (flcem, t.y, t.x);
                    for (auto &j : lem[t.y][t.x]) {
                        ccm[j.y][j.x] |= bcols6[tindex];
                    }
                    score += tscore;
                    re = true;
                }
            }
            
        }
        
        return ret;
    }
    
    
    
    void init_color_map () {
        vector< unordered_set<int8_t> > color(6);
        
        color[0].emplace(0+1);
        color[1].emplace(1+1);
        color[2].emplace(0+1);
        color[2].emplace(1+1);
        color[3].emplace(3+1);
        color[4].emplace(0+1);
        color[4].emplace(3+1);
        color[5].emplace(1+1);
        color[5].emplace(3+1);
        
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                unordered_set<int8_t> t;
                for (auto &k : color[i]) { t.emplace(k); }
                for (auto &k : color[j]) { t.emplace(k); }
                int8_t ti = 0;
                for (auto &k : t) { ti += k; }
                this->colormap[i][j] = ti + '0';
                if (t.size() > 2) { this->colormap[i][j] = '0'; }
            }
        }
    }
    
    
    void put_items (vector< vector<int8_t> > &itemboard, vector<clitem> &lanterns, vector<clitem> &items, int &cost) {
        for (auto &i : items) {
            itemboard[i.y][i.x] = i.c;
            if (i.c >= '1' && i.c <= '6') {
                cost += this->costLantern;
                lanterns.emplace_back(i);
            } else if (i.c == '/' || i.c == '\\') {
                cost += this->costMirror;
            } else if (i.c == 'X') {
                cost += this->costObstacle;
            }
        }
    }
    
    inline int8_t mix_color(int8_t a, int8_t b) {
        if (a == '0' || b == '0') { return '0'; }
        int x = a - '1';
        int y = b - '1';
        return this->colormap[x][y];
    }
    
    void put_rays (vector< vector<int8_t> > &itemboard, vector<clitem> &lanterns, vector<clitem> &items, int &error) {
        // l u r d
        static const int dy[4] = {0, -1, 0, 1};
        static const int dx[4] = {-1, 0, 1, 0};
        int tmp;
        int8_t tc;
        for (auto &i : lanterns) {
            for (int j = 0; j < 4; ++j) {
                int ty = dy[j];
                int tx = dx[j];
                int py = i.y;
                int px = i.x;
                itemboard[py][px] = i.c;
                while (true) {
                    py += ty;
                    px += tx;
                    if (py < 0 || py >= this->H || px < 0 || px >= this->W) { break; }
                    tc = this->targetBoard[py][px];
                    if (tc == 'X') { break; }
                    
                    if (itemboard[py][px] == '/') {
                        tmp = ty;
                        ty = -tx;
                        tx = -tmp;
                        continue;
                    }
                    if (itemboard[py][px] == '\\') {
                        tmp = ty;
                        ty = tx;
                        tx = tmp;
                        continue;
                    }
                    
                    // lantern x lantern
                    if (!(tc >= '1' && tc <= '6') && itemboard[py][px] >= '1' && itemboard[py][px] <= '6') {
                        error += 1;
                        return;
                    }
                    
                    // crystal
                    if (tc >= '1' && tc <= '6') {
                        if (itemboard[py][px] == '.') {
                            itemboard[py][px] = i.c;
                        } else {
                            itemboard[py][px] = this->mix_color(itemboard[py][px], i.c);
                        }
                        break;
                    }
                    
                    if (itemboard[py][px] == 'X') { break; }
                }
            }
        }
    }
    
    int all_score (vector<string> &items) {
        vector<clitem> t;
        for (auto &i : items) { t.emplace_back(clitem(i)); }
        return this->all_score(t);
    }
    
    int all_score (vector<clitem> &items) {
        vector< vector<int8_t> > itemboard = this->blankBoard;
        vector<clitem> lanterns;
        int score = 0;
        int cost = 0;
        int error = 0;
        this->put_items(itemboard, lanterns, items, cost);
        this->put_rays(itemboard, lanterns, items, error);
        if (error > 0) { return -1000000; }
        score -= cost;
        
        for (auto &i : this->crystals) {
            if (itemboard[i.y][i.x] == '.') { continue; }
            if (itemboard[i.y][i.x] == i.c) {
                if (i.c == '3' || i.c == '5' || i.c == '6') {
                    score += 30;
                } else {
                    score += 20;
                }
                
            } else {
                score -= 10;
            }
        }
        
        return score;
    }
    
    
};

// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    CrystalLighting cl;
    int H;
    cin >> H;
    vector<string> targetBoard(H);
    getVector(targetBoard);
    int costLantern, costMirror, costObstacle, maxMirrors, maxObstacles;
    cin >> costLantern >> costMirror >> costObstacle >> maxMirrors >> maxObstacles;

    vector<string> ret = cl.placeItems(targetBoard, costLantern, costMirror, costObstacle, maxMirrors, maxObstacles);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
