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

struct mpos {
public:
    int x;
    int y;
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <>
    class hash<mpos> {
    public:
        size_t operator()(const mpos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
}

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

inline double distance (const double &ax, const double &ay, const double &bx, const double &by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline double distance (const int &ax, const int &ay, const int &bx, const int &by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline float distance (const mpos &a, const mpos &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

class SubSquare {
public:
    int r, c, size;
    SubSquare(int r, int c, int size) {
        this->r = r;
        this->c = c;
        this->size = size;
    }
};


class MM {
public:
    StopWatch sw;
    int N, M;
    int CN;
    vector< vector<int> > rboard;
    MM () {
        this->sw = StopWatch();
        cin >> this->N;
        cin >> this->M;
        this->CN = this->N / 2;
        
        for (int i = 0; i < this->N; ++i) {
            vector<int> t(this->N, 0);
            for (int j = 0; j < this->N; ++j) { cin >> t[j]; }
            this->rboard.emplace_back(t);
        }
        
        vector<SubSquare> ret;
        vector< vector<int> > board = rboard;
        int cnt  = 0;
        
        for (int i = 0; i < this->N*2; ++i) {
            if (ret.size() >= this->M && cnt >= this->M) { break; }
            for (int j = 0; j < i+1; ++j) {
                if (ret.size() >= this->M && cnt >= this->M) { break; }
                int px = i - j;
                int py = 0 + j;
                
                if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                
                int minrcnt = 4;
                int minsize = -1;
                int posc = 0;
                if (px >= 10 && py < 10) { posc = 1; }
                if (px < 10 && py >= 10) { posc = 2; }
                if (px >= 10 && py >= 10) { posc = 3; }
                if (board[py][px] == posc) { continue; }
                
                for (int k = 1; k < this->N; ++k) {
                    if (px+k >= this->N || py+k >= this->N) { break; }
                    
                    int rcnt = 0;
                    // if (posc == board[py+k][px]) {
                    //     if (minrcnt > 1) {
                    //         minrcnt = 3;
                    //         minsize = k;
                            
                    //     }
                    // }
                    
                    // if (posc == board[py+k][px+k]) {
                    //     if (minrcnt > 2) {
                    //         minrcnt = 2;
                    //         minsize = k;
                    //     }
                    // }
                    if (posc == board[py+k][px]) {
                        if (minrcnt > 1) {
                            minrcnt = 1;
                            minsize = k+1;
                        }
                        break;
                    }
                    
                    
                }
                
                if (minsize > 0 && ret.size() + minrcnt <= this->M-50) {
                    for (int q = 0; q < minrcnt; ++q) {
                        this->rotateClockwise(SubSquare(py, px, minsize), board);
                        ret.emplace_back(py, px, minsize);
                    }
                    
                    
                    
                }
                
            }
            
        }
        
        
        
        for (auto &i : ret) {
            cout << print(i.r, i.c, i.size) << endl;
        }
        
        
    }
    
    
    void rotateClockwise(SubSquare square, vector< vector<int> > &C) {
        for (int i = 0; i < square.size / 2; i++) {
            for (int j = 0; j < (square.size + 1) / 2; j++) {
                int first = C[square.r + i][square.c + j];
                C[square.r + i][square.c + j] = C[square.r + square.size - 1 - j][square.c + i];
                C[square.r + square.size - 1 - j][square.c + i] = C[square.r + square.size - 1 - i][square.c + square.size - 1 - j];
                C[square.r + square.size - 1 - i][square.c + square.size - 1 - j] = C[square.r + j][square.c + square.size - 1 - i];
                C[square.r + j][square.c + square.size - 1 - i] = first;
            }
        }
    }

    void rotateCounterClockwise(SubSquare square, vector< vector<int> > &C) {
        for (int i = 0; i < square.size / 2; i++) {
            for (int j = 0; j < (square.size + 1) / 2; j++) {
                int first = C[square.r + i][square.c + j];
                C[square.r + i][square.c + j] = C[square.r + j][square.c + square.size - 1 - i];
                C[square.r + j][square.c + square.size - 1 - i] = C[square.r + square.size - 1 - i][square.c + square.size - 1 - j];
                C[square.r + square.size - 1 - i][square.c + square.size - 1 - j] = C[square.r + square.size - 1 - j][square.c + i];
                C[square.r + square.size - 1 - j][square.c + i] = first;
            }
        }
    }

    
    
    
    int all_score (int cnt, vector< vector<int> > &board) {
        int score = 0;
        for (int y = 0; y < CN; ++y) {
            for (int x = 0; x < CN; ++x) {
                score += board[y][x] == 0;
            }
        }
        for (int y = 0; y < CN; ++y) {
            for (int x = CN; x < N; ++x) {
                score += board[y][x] == 1;
            }
        }
        for (int y = CN; y < N; ++y) {
            for (int x = 0; x < CN; ++x) {
                score += board[y][x] == 2;
            }
        }
        for (int y = CN; y < N; ++y) {
            for (int x = CN; x < N; ++x) {
                score += board[y][x] == 3;
            }
        }
        if (score == this->N * this->N) {
            score += this->M - cnt;
        }
        return score;
    }
    
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM();
    
    return 0;
}