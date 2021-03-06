// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <random>
#include <string>
#include <unordered_set>
#include <unordered_map>


#include <time.h>
#include <sys/timeb.h>

using namespace std;

string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char *v) { return '"' + v + '"'; }
string in_v_to_str (const string v) { return '"' + v + '"'; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N> &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; }
        ss << in_v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[]";
    }
    return ss.str();
}
template<class T, size_t N> string v_to_str (const array< array<T, N>, N > &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; }
        ss << v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[-]";
    }
    return ss.str();
}
template<class T> string v_to_str (const vector<T> &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; }
        ss << in_v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[]";
    }
    return ss.str();
}
template<class T> string v_to_str (const vector< vector<T> > &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; }
        ss << v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[-]";
    }
    return ss.str();
}
template<class T> string v_to_str (const set<T> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class K, class V> string v_to_str (const map<K, V> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class T> string v_to_str (const unordered_set<T> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class K, class V> string v_to_str (const unordered_map<K, V> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
string print () { return ""; }
template<typename F, typename... R> string print (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f);
    if (sizeof...(r) > 0) { ss << " " << print(r...); }
    return ss.str();
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

struct rcrc {
public:
    int ar, ac, br, bc;
    rcrc (int ar, int ac, int br, int bc) {
        this->ar = ar;
        this->ac = ac;
        this->br = br;
        this->bc = bc;
    }
};

class SameColorPairs {
public:
    int H;
    int W;
    
    vector<rcrc> ret;
    vector<rcrc> bestret;
    vector<string> board;
    
    vector<rcrc> tmpret;
    vector<string> tmpboard;
    
    vector<string> removePairs(vector<string> board) {
        vector<string> ret;
        int H = board.size(), W = board[0].size();
        this->H = H;
        this->W = W;
        
        this->board = board;
        
        
        StopWatch sw;
        
        this->remove_cells();
        this->bestret = this->ret;
        
        int cnt = 0;
        
        while (sw.get_milli_time() < 5000 && this->bestret.size() < H * W / 2) {
            // if (cnt % 2 == 0) {
            //     this->remove_cells();
            // } else  {
            //     this->remove_cellsb();
            // }
            // if (cnt % 3 == 0) {
            //     this->remove_cells();
            // } else if (cnt % 3 == 1) {
            //     this->remove_cellsb();
            // } else {
            //     this->remove_cellsv();
            // }
            this->remove_cellsv();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
                this->bestret_rewind(H*W/24);
            }
            cnt += 1;
        }
        
        if (this->rewind_ret.size() < 1) {
            this->bestret_rewind(H*W/24);
        }
        
        vector< vector<rcrc> > rets;
        
        while (sw.get_milli_time() < 8500 && this->bestret.size() < H * W / 2) {
            // if (cnt % 2 == 0) {
            //     this->remove_cellsr();
            // } else {
            //     this->remove_cellsbr();
            // }
            // if (cnt % 3 == 0) {
            //     this->remove_cellsr();
            // } else if (cnt % 3 == 1) {
            //     this->remove_cellsbr();
            // } else {
            //     this->remove_cellsvr();
            // }
            this->remove_cellsvr();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
                rets.emplace_back(this->ret);
                this->bestret_rewind(H*W/16);
            }
            cnt += 1;
        }
        
        this->rewind_board.clear();
        this->rewind_ret.clear();
        this->bestret_rewind(32);
        for (int i = 0; i < min(4, (int)rets.size()); ++i) {
            this->ret_rewind(32, rets[rets.size()-i-1]);
        }
        
        
        while (sw.get_milli_time() < 9800 && this->bestret.size() < H * W / 2) {
            // if (cnt % 2 == 0) {
            //     this->remove_cellsr();
            // } else {
            //     this->remove_cellsbr();
            // }
            this->remove_cellsvr();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
            }
            cnt += 1;
        }
        
        
        for (auto &i : this->bestret) {
            //ret.emplace_back(print(i.ar, i.ac, i.br, i.bc));
            ret.emplace_back(to_string(i.ar) + " " + to_string(i.ac) + " " + to_string(i.br) + " " + to_string(i.bc));
        }
        
        
        // cerr << print("H :", board.size(), ", W :", board[0].size(), " Time :", sw.get_milli_time() * 0.001, cnt) << endl;
        
        
        return ret;
    }
    
    vector< vector<rcrc> > rewind_ret;
    vector< vector<string> > rewind_board;
    void bestret_rewind (int n) {
        vector<rcrc> r;
        vector<string> b = this->board;
        
        for (int i = 0; i < max(0, (int)this->bestret.size() - n); ++i) {
            r.emplace_back(this->bestret[i]);
            b[this->bestret[i].ar][this->bestret[i].ac] = -1;
            b[this->bestret[i].br][this->bestret[i].bc] = -1;
        }
        for (int i = 0; i < (this->bestret.size()+1) / 2; ++i) {
            this->rewind_ret.emplace_back(r);
            this->rewind_board.emplace_back(b);
        }
    }
    
    void ret_rewind (int n, vector<rcrc> ret) {
        vector<rcrc> r;
        vector<string> b = this->board;
        
        for (int i = 0; i < max(0, (int)ret.size() - n); ++i) {
            r.emplace_back(ret[i]);
            b[ret[i].ar][ret[i].ac] = -1;
            b[ret[i].br][ret[i].bc] = -1;
        }
        
        this->rewind_ret.emplace_back(r);
        this->rewind_board.emplace_back(b);
    }
    
    void remove_cellsr () {
        int rn = xrnd() % this->rewind_board.size();
        vector<string> board = this->rewind_board[rn];
        this->ret = this->rewind_ret[rn];
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        while (f) {
            f = 0;
            for (int i = 0; i < this->H; ++i) {
                for (int j = 0; j < this->W; ++j) {
                    if (board[i][j] < 0) { continue; }
                    int rx = j;
                    int dy = i;
                    int mrx = j;
                    int mdy = i;
                    for (int x = j + 1; x < this->W; ++x) {
                        if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                            if (board[i][x] == board[i][j]) {
                                rx = x;
                            }
                            mrx = x;
                        } else {
                            break;
                        }
                    }
                    
                    for (int y = i + 1; y < this->H; ++y) {
                        if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                            if (board[y][j] == board[i][j]) {
                                dy = y;
                            }
                            mdy = y;
                        } else {
                            break;
                        }
                    }
                    
                    if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                        f = 1;
                        continue;
                    }
                    if (abs(j - rx) > abs(i - dy)) {
                        if (rx != j) {
                            this->add_ret(i, j, i, rx);
                            board[i][j] = -1;
                            board[i][rx] = -1;
                            f = 1;
                            continue;
                        }
                    } else {
                        if (dy != i) {
                            this->add_ret(i, j, dy, j);
                            board[i][j] = -1;
                            board[dy][j] = -1;
                            f = 1;
                            continue;
                        }
                    }
                }
            }
        }
    }
    
    void remove_cellsbr () {
        int rn = xrnd() % this->rewind_board.size();
        vector<string> board = this->rewind_board[rn];
        this->ret = this->rewind_ret[rn];
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        while (f) {
            f = 0;
            for (int i = 0; i < this->H; ++i) {
                for (int j = 0; j < this->W; ++j) {
                    if (board[i][j] < 0) { continue; }
                    int rx = j;
                    int dy = i;
                    int mrx = j;
                    int mdy = i;
                    for (int x = j + 1; x < this->W; ++x) {
                        if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                            if (board[i][x] == board[i][j]) {
                                rx = x;
                            }
                            mrx = x;
                        } else {
                            break;
                        }
                    }
                    
                    for (int y = i + 1; y < this->H; ++y) {
                        if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                            if (board[y][j] == board[i][j]) {
                                dy = y;
                            }
                            mdy = y;
                        } else {
                            break;
                        }
                    }
                    
                    if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                        f = 1;
                        break;
                    }
                    if (abs(j - rx) > abs(i - dy)) {
                        if (rx != j) {
                            this->add_ret(i, j, i, rx);
                            board[i][j] = -1;
                            board[i][rx] = -1;
                            f = 1;
                            break;
                        }
                    } else {
                        if (dy != i) {
                            this->add_ret(i, j, dy, j);
                            board[i][j] = -1;
                            board[dy][j] = -1;
                            f = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    void remove_cellsvr () {
        int rn = xrnd() % this->rewind_board.size();
        vector<string> board = this->rewind_board[rn];
        this->ret = this->rewind_ret[rn];
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        vector<int> v;
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < this->W; ++j) {
                if (board[i][j] > -1) { v.emplace_back(i*this->W+j); }
            }
        }
        
        mt19937 mt(xrnd());
        
        
        while (f) {
            shuffle(v.begin(), v.end(), mt);
            f = 0;
            for (auto &p : v) {
                int i = p / this->W;
                int j = p % this->W;
                
                if (board[i][j] < 0) { continue; }
                int rx = j;
                int dy = i;
                int mrx = j;
                int mdy = i;
                for (int x = j + 1; x < this->W; ++x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        if (board[i][x] == board[i][j]) {
                            rx = x;
                        }
                        mrx = x;
                    } else {
                        break;
                    }
                }
                
                for (int y = i + 1; y < this->H; ++y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        if (board[y][j] == board[i][j]) {
                            dy = y;
                        }
                        mdy = y;
                    } else {
                        break;
                    }
                }
                
                if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                    f = 1;
                    continue;
                }
                if (abs(j - rx) > abs(i - dy)) {
                    if (rx != j) {
                        this->add_ret(i, j, i, rx);
                        board[i][j] = -1;
                        board[i][rx] = -1;
                        f = 1;
                        continue;
                    }
                } else {
                    if (dy != i) {
                        this->add_ret(i, j, dy, j);
                        board[i][j] = -1;
                        board[dy][j] = -1;
                        f = 1;
                        continue;
                    }
                }
            }
        }
    }
    
    void remove_cells () {
        vector<string> board = this->board;
        this->ret.clear();
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        while (f) {
            f = 0;
            for (int i = 0; i < this->H; ++i) {
                for (int j = 0; j < this->W; ++j) {
                    if (board[i][j] < 0) { continue; }
                    int rx = j;
                    int dy = i;
                    int mrx = j;
                    int mdy = i;
                    for (int x = j + 1; x < this->W; ++x) {
                        if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                            if (board[i][x] == board[i][j]) {
                                rx = x;
                            }
                            mrx = x;
                        } else {
                            break;
                        }
                    }
                    
                    for (int y = i + 1; y < this->H; ++y) {
                        if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                            if (board[y][j] == board[i][j]) {
                                dy = y;
                            }
                            mdy = y;
                        } else {
                            break;
                        }
                    }
                    
                    if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                        f = 1;
                        continue;
                    }
                    
                    if (abs(j - rx) > abs(i - dy)) {
                        if (rx != j) {
                            this->add_ret(i, j, i, rx);
                            board[i][j] = -1;
                            board[i][rx] = -1;
                            f = 1;
                            continue;
                        }
                    } else {
                        if (dy != i) {
                            this->add_ret(i, j, dy, j);
                            board[i][j] = -1;
                            board[dy][j] = -1;
                            f = 1;
                            continue;
                        }
                    }
                }
            }
        }
    }
    
    void remove_cellsb () {
        vector<string> board = this->board;
        this->ret.clear();
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        while (f) {
            f = 0;
            for (int i = 0; i < this->H; ++i) {
                for (int j = 0; j < this->W; ++j) {
                    if (board[i][j] < 0) { continue; }
                    int rx = j;
                    int dy = i;
                    int mrx = j;
                    int mdy = i;
                    for (int x = j + 1; x < this->W; ++x) {
                        if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                            if (board[i][x] == board[i][j]) {
                                rx = x;
                            }
                            mrx = x;
                        } else {
                            break;
                        }
                    }
                    
                    for (int y = i + 1; y < this->H; ++y) {
                        if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                            if (board[y][j] == board[i][j]) {
                                dy = y;
                            }
                            mdy = y;
                        } else {
                            break;
                        }
                    }
                    
                    if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                        f = 1;
                        break;
                    }
                    
                    if (abs(j - rx) > abs(i - dy)) {
                        if (rx != j) {
                            this->add_ret(i, j, i, rx);
                            board[i][j] = -1;
                            board[i][rx] = -1;
                            f = 1;
                            break;
                        }
                    } else {
                        if (dy != i) {
                            this->add_ret(i, j, dy, j);
                            board[i][j] = -1;
                            board[dy][j] = -1;
                            f = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    void remove_cellsv () {
        vector<string> board = this->board;
        this->ret.clear();
        static const vector< vector<int> > vvi = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        bool f = 1;
        
        vector<int> v;
        for (int i = 0; i < this->H; ++i) {
            for (int j = 0; j < this->W; ++j) {
                if (board[i][j] > -1) { v.emplace_back(i*this->W+j); }
            }
        }
        
        mt19937 mt(xrnd());
        
        while (f) {
            shuffle(v.begin(), v.end(), mt);
            f = 0;
            for (auto &p : v) {
                int i = p / this->W;
                int j = p % this->W;
                
                if (board[i][j] < 0) { continue; }
                int rx = j;
                int dy = i;
                int mrx = j;
                int mdy = i;
                for (int x = j + 1; x < this->W; ++x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        if (board[i][x] == board[i][j]) {
                            rx = x;
                        }
                        mrx = x;
                    } else {
                        break;
                    }
                }
                
                for (int y = i + 1; y < this->H; ++y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        if (board[y][j] == board[i][j]) {
                            dy = y;
                        }
                        mdy = y;
                    } else {
                        break;
                    }
                }
                
                if (mdy > i && this->rect_first_remove(j, i, mrx, mdy, board)) {
                    f = 1;
                    continue;
                }
                if (abs(j - rx) > abs(i - dy)) {
                    if (rx != j) {
                        this->add_ret(i, j, i, rx);
                        board[i][j] = -1;
                        board[i][rx] = -1;
                        f = 1;
                        continue;
                    }
                } else {
                    if (dy != i) {
                        this->add_ret(i, j, dy, j);
                        board[i][j] = -1;
                        board[dy][j] = -1;
                        f = 1;
                        continue;
                    }
                }
            }
        }
    }
    
    bool rect_first_remove (const int ax, const int ay, const int mrx, const int mdy, vector<string> &board) {
        
        vector<int> vx;
        vector<int> vy;
        
        const char c = board[ay][ax];
        int tlx = 0;
        int trx = mrx;
        for (int i = ay; i <= mdy; ++i) {// H
            if (ax > 0) {
                int lx = ax;
                for (int j = ax - 1; j >= tlx; --j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        // if (xrnd() % 4 < 1) {
                        //     px = j;
                        //     py = i;
                        //     return true;
                        // }
                        
                        vx.emplace_back(j);
                        vy.emplace_back(i);
                        lx = j;
                    } else if (tc < 0) {
                        lx = j;
                    } else {
                        break;
                    }
                }
                tlx = lx;
            }
            
            if (i > ay) {
                const char tc = board[i][ax];
                if (tc == c) {
                    // if (xrnd() % 4 < 1) {
                    //     px = ax;
                    //     py = i;
                    //     return true;
                    // }
                    
                    vx.emplace_back(ax);
                    vy.emplace_back(i);
                }
            }
            
            // right
            if (ax < this->W-1) {
                int rx = ax;
                for (int j = ax + 1; j <= trx; ++j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        // if (xrnd() % 4 < 1) {
                        //     px = j;
                        //     py = i;
                        //     return true;
                        // }
                        
                        vx.emplace_back(j);
                        vy.emplace_back(i);
                        rx = j;
                    } else if (tc < 0) {
                        rx = j;
                    } else {
                        break;
                    }
                }
                trx = rx;
            }
        }
        
        if (vx.size() > 0) {
            const int n = xrnd() % vx.size();
            board[ay][ax] = -1;
            board[vy[n]][vx[n]] = -1;
            this->add_ret(ay, ax, vy[n], vx[n]);
            
            return true;
        }
        
        return false;
    }
    
    inline bool rect_is_remove (const int ax, const int ay, const int bx, const int by, const vector<string> &board) {
        int minx = min(ax, bx);
        int maxx = max(ax, bx);
        int miny = min(ay, by);
        int maxy = max(ay, by);
        const char c = board[ay][ax];
        for (int i = miny; i <= maxy; ++i) {
            for (int j = minx; j <= maxx; ++j) {
                if (board[i][j] > -1 && board[i][j] != c) {
                    return false;
                }
            }
        }
        return true;
    }
    
    
    inline void add_ret (int ar, int ac, int br, int bc) { this->ret.emplace_back(ar, ac, br, bc); }
    inline bool outside (const int &x, const int &y) { return (x < 0 || x > this->W-1 || y < 0 || y > this->H-1); }
    
};
//


// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    SameColorPairs scp;
    int H;
    cin >> H;
    vector<string> board(H);
    getVector(board);
    vector<string> ret = scp.removePairs(board);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
    
}
