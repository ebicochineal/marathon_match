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
    int8_t ar, ac, br, bc;
    rcrc (int8_t ar, int8_t ac, int8_t br, int8_t bc) {
        this->ar = ar;
        this->ac = ac;
        this->br = br;
        this->bc = bc;
    }
};


class CumulativeSum2DColors {
public:
    
    
};

class SameColorPairs {
public:
    int H;
    int W;
    int C;
    vector<rcrc> ret;
    vector<rcrc> bestret;
    array< array<int8_t, 100>, 100> board;
    
    vector<rcrc> tmpret;
    array< array<int8_t, 100>, 100> tmpboard;
    
    vector<string> removePairs(vector<string> board) {
        vector<string> ret;
        int H = board.size(), W = board[0].size();
        this->H = H;
        this->W = W;
        
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                this->board[i][j] = board[i][j] - 48;
                this->C = max(this->C, board[i][j] - 48);
            }
        }
        
        StopWatch sw;
        
        this->remove_cellsv();
        this->bestret = this->ret;
        
        int cnt = 0;
        int swtime = sw.get_milli_time();
        
        while (swtime < 2500 && this->bestret.size() < H * W / 2) {
            if (cnt % 5 == 0) { swtime = sw.get_milli_time(); }
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
        
        vector< vector<rcrc> > bestrets;
        vector< vector<rcrc> > rets;
        while (swtime < 5000 && this->bestret.size() < H * W / 2) {
            if (cnt % 10 == 0) { swtime = sw.get_milli_time(); }
            this->remove_cellsvr();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
                bestrets.emplace_back(this->ret);
                // this->bestret_rewind(H*W/16);
                
                if (bestrets.size() < 8) {
                    bestrets.emplace_back(this->ret);
                } else {
                    bestrets[bestrets.size() - 1].clear();
                    bestrets[bestrets.size() - 1] = this->ret;
                    sort(bestrets.begin(), bestrets.end(), [](const vector<rcrc> &a, const vector<rcrc> &b) { return a.size() > b.size(); });
                }
            } else {
                if (this->ret.size() > H*W/2 - 48) {
                    if (rets.size() < 4) {
                        rets.emplace_back(this->ret);
                    } else {
                        rets[rets.size() - 1].clear();
                        rets[rets.size() - 1] = this->ret;
                        sort(rets.begin(), rets.end(), [](const vector<rcrc> &a, const vector<rcrc> &b) { return a.size() > b.size(); });
                    }
                    
                }
            }
            
            cnt += 1;
        }
        
        this->rewind_board.clear();
        this->rewind_ret.clear();
        this->bestret_rewind(H+W/16);
        for (int i = 0; i < min(8, (int)bestrets.size()); ++i) {
            this->ret_rewind(H+W/16, bestrets[bestrets.size()-i-1]);
        }
        for (int i = 0; i < min(4, (int)rets.size()); ++i) {
            
            this->ret_rewind(H+W/16, rets[i]);
        }
        bestrets.clear();
        rets.clear();
        
        while (swtime < 6000 && this->bestret.size() < H * W / 2) {
            if (cnt % 10 == 0) { swtime = sw.get_milli_time(); }
            this->remove_cellsvr();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
                bestrets.emplace_back(this->ret);
                // this->bestret_rewind(H*W/16);
                
                if (bestrets.size() < 8) {
                    bestrets.emplace_back(this->ret);
                } else {
                    bestrets[bestrets.size() - 1].clear();
                    bestrets[bestrets.size() - 1] = this->ret;
                    sort(bestrets.begin(), bestrets.end(), [](const vector<rcrc> &a, const vector<rcrc> &b) { return a.size() > b.size(); });
                }
            } else {
                if (this->ret.size() > H*W/2 - 48) {
                    if (rets.size() < 4) {
                        rets.emplace_back(this->ret);
                    } else {
                        rets[rets.size() - 1].clear();
                        rets[rets.size() - 1] = this->ret;
                        sort(rets.begin(), rets.end(), [](const vector<rcrc> &a, const vector<rcrc> &b) { return a.size() > b.size(); });
                    }
                    
                }
            }
            
            cnt += 1;
        }
        
        this->rewind_board.clear();
        this->rewind_ret.clear();
        this->bestret_rewind(32);
        for (int i = 0; i < min(8, (int)bestrets.size()); ++i) {
            this->ret_rewind(32, bestrets[bestrets.size()-i-1]);
        }
        for (int i = 0; i < min(4, (int)rets.size()); ++i) {
            
            this->ret_rewind(32, rets[i]);
        }
        bestrets.clear();
        
        
        while (swtime < 9300 && this->bestret.size() < H * W / 2) {
            if (cnt % 100 == 0 || (swtime > 9000 && cnt % 20 == 0)) { swtime = sw.get_milli_time(); }
            
            this->remove_cellsvr();
            if (this->ret.size() > this->bestret.size()) {
                this->bestret = this->ret;
                
                if (bestrets.size() < 2) {
                    bestrets.emplace_back(this->ret);
                } else {
                    bestrets[bestrets.size() - 1].clear();
                    bestrets[bestrets.size() - 1] = this->ret;
                    sort(bestrets.begin(), bestrets.end(), [](const vector<rcrc> &a, const vector<rcrc> &b) { return a.size() > b.size(); });
                }
                
                
            }
            cnt += 1;
        }
        
        this->rewind_board.clear();
        this->rewind_ret.clear();
        this->bestret_rewind(32);
        for (int i = 0; i < min(2, (int)bestrets.size()); ++i) {
            this->ret_rewind(32, bestrets[bestrets.size()-i-1]);
        }
        while (swtime < 9850 && this->bestret.size() < H * W / 2) {
            if (cnt % 20 == 0) { swtime = sw.get_milli_time(); }
            
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
        
        
        //cerr << print("H :", board.size(), ", W :", board[0].size(), ", C :", this->C, " Time :", sw.get_milli_time() * 0.001, cnt) << endl;
        
        
        return ret;
    }
    
    vector< vector<rcrc> > rewind_ret;
    vector< array< array<int8_t, 100>, 100> > rewind_board;
    void bestret_rewind (int n) {
        vector<rcrc> r;
        array< array<int8_t, 100>, 100> b = this->board;
        
        for (int i = 0; i < max(0, (int)this->bestret.size() - n); ++i) {
            r.emplace_back(this->bestret[i]);
            b[this->bestret[i].ar][this->bestret[i].ac] = -1;
            b[this->bestret[i].br][this->bestret[i].bc] = -1;
        }
        
        this->rewind_ret.emplace_back(r);
        this->rewind_board.emplace_back(b);
        
    }
    
    void ret_rewind (int n, vector<rcrc> ret) {
        vector<rcrc> r;
        array< array<int8_t, 100>, 100> b = this->board;
        
        for (int i = 0; i < max(0, (int)ret.size() - n); ++i) {
            r.emplace_back(ret[i]);
            b[ret[i].ar][ret[i].ac] = -1;
            b[ret[i].br][ret[i].bc] = -1;
        }
        
        this->rewind_ret.emplace_back(r);
        this->rewind_board.emplace_back(b);
    }
    
    
    void remove_cellsvr () {
        int rn = xrnd() % this->rewind_board.size();
        array< array<int8_t, 100>, 100> board = this->rewind_board[rn];
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
                int mlx = j;
                int muy = i;
                for (int x = j + 1; x < this->W; ++x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        mrx = x;
                    } else {
                        break;
                    }
                }
                
                for (int x = j - 1; x >= 0; --x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        mlx = x;
                    } else {
                        break;
                    }
                }
                
                for (int y = i + 1; y < this->H; ++y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        mdy = y;
                    } else {
                        break;
                    }
                }
                
                for (int y = i - 1; y >= 0; --y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        muy = y;
                    } else {
                        break;
                    }
                }
                
                if (this->rect_first_remove(j, i, mrx, mdy, mlx, muy, board)) {
                    f = 1;
                    continue;
                }
            }
        }
    }
    
    void remove_cellsv () {
        array< array<int8_t, 100>, 100> board = this->board;
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
                int mrx = j;
                int mdy = i;
                int mlx = j;
                int muy = i;
                for (int x = j + 1; x < this->W; ++x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        mrx = x;
                    } else {
                        break;
                    }
                }
                
                for (int x = j - 1; x >= 0; --x) {
                    if (board[i][x] < 0 || board[i][x] == board[i][j]) {
                        mlx = x;
                    } else {
                        break;
                    }
                }
                
                for (int y = i + 1; y < this->H; ++y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        mdy = y;
                    } else {
                        break;
                    }
                }
                
                for (int y = i - 1; y >= 0; --y) {
                    if (board[y][j] < 0 || board[y][j] == board[i][j]) {
                        muy = y;
                    } else {
                        break;
                    }
                }
                
                if (this->rect_first_remove(j, i, mrx, mdy, mlx, muy, board)) {
                    f = 1;
                    continue;
                }
                
            }
        }
    }
    
    inline bool rect_first_remove (const int ax, const int ay, const int mrx, const int mdy, const int mlx, const int muy, array< array<int8_t, 100>, 100> &board) {
        const char c = board[ay][ax];
        int tlx = mlx;
        int trx = mrx;
        
        for (int i = mlx; i < ax; ++i) {
            const char tc = board[ay][i];
            if (tc == c) {
                board[ay][ax] = -1;
                board[ay][i] = -1;
                this->add_ret(ay, ax, ay, i);
                return true;
            }
        }
        for (int i = mrx; i > ax; --i) {
            const char tc = board[ay][i];
            if (tc == c) {
                board[ay][ax] = -1;
                board[ay][i] = -1;
                this->add_ret(ay, ax, ay, i);
                return true;
            }
        }
        
        for (int i = muy; i < ay; ++i) {
            const char tc = board[i][ax];
            if (tc == c) {
                board[ay][ax] = -1;
                board[i][ax] = -1;
                this->add_ret(ay, ax, i, ax);
                return true;
            }
        }
        for (int i = mdy; i > ay; --i) {
            const char tc = board[i][ax];
            if (tc == c) {
                board[ay][ax] = -1;
                board[i][ax] = -1;
                this->add_ret(ay, ax, i, ax);
                return true;
            }
        }
        
        for (int i = ay+1; i <= mdy; ++i) {// H
            // left
            if (ax > 0) {
                int lx = ax;
                for (int j = ax - 1; j >= tlx; --j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        board[ay][ax] = -1;
                        board[i][j] = -1;
                        this->add_ret(ay, ax, i, j);
                        return true;
                    } else if (tc < 0) {
                        lx = j;
                    } else {
                        break;
                    }
                }
                tlx = lx;
            }
            
            // right
            if (ax < this->W-1) {
                int rx = ax;
                for (int j = ax + 1; j <= trx; ++j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        board[ay][ax] = -1;
                        board[i][j] = -1;
                        this->add_ret(ay, ax, i, j);
                        return true;
                    } else if (tc < 0) {
                        rx = j;
                    } else {
                        break;
                    }
                }
                trx = rx;
            }
        }
        
        tlx = mlx;
        trx = mrx;
        for (int i = ay - 1; i >= muy; --i) {// H
            // left
            if (ax > 0) {
                int lx = ax;
                for (int j = ax - 1; j >= tlx; --j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        board[ay][ax] = -1;
                        board[i][j] = -1;
                        this->add_ret(ay, ax, i, j);
                        return true;
                    } else if (tc < 0) {
                        lx = j;
                    } else {
                        break;
                    }
                }
                tlx = lx;
            }
            
            // right
            if (ax < this->W-1) {
                int rx = ax;
                for (int j = ax + 1; j <= trx; ++j) {// W
                    const char tc = board[i][j];
                    if (tc == c) {
                        board[ay][ax] = -1;
                        board[i][j] = -1;
                        this->add_ret(ay, ax, i, j);
                        return true;
                    } else if (tc < 0) {
                        rx = j;
                    } else {
                        break;
                    }
                }
                trx = rx;
            }
        }
        
        return false;
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
