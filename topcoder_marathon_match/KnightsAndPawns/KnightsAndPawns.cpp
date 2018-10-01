// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <complex>
#include <random>
using namespace std;


#include <time.h>
#include <sys/timeb.h>

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



class KnightsAndPawns {
public:
    vector< vector<int> > sboard;
    StopWatch sw;
    
    vector<string> placeKnights(vector<string> board) {
        int H = board.size(), W = board[0].size();
        vector<string> ret(H, string(W, '.'));
        
        this->sboard = vector< vector<int> >(H+4, vector<int>(W+4, -2));
        int pcnt = 0;
        for (int y=0; y<H; ++y) {
            for (int x=0; x<W; ++x) {
                if (board[y][x] == 'P') {
                    sboard[y+2][x+2] = -1;
                    pcnt += 1;
                } else {
                    sboard[y+2][x+2] = 0;
                }
            }
        }
        
        int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        
        vector< vector<int> > tboard = sboard;
        vector< vector<int> > tboard2 = sboard;
        // vector< vector<int> > besttboard = sboard;
        // double bestscore = 0;
        // for (int i = 0; i < 4; ++i) {
        //     tboard = sboard;
        //     this->TPut2(tboard, H, W);
        //     this->TPut3(tboard, H, W);
        //     this->TPut4(tboard, H, W);
        //     this->Remove(tboard, H, W);
        //     double tscore = this->AllScore(tboard, H, W);
        //     if (tscore > bestscore) {
        //         bestscore = tscore;
        //         besttboard = tboard;
        //     }
        // }
        // tboard = besttboard;
        
        this->TPut(tboard, H, W);
        this->TPut3(tboard, H, W);
        this->TPut4(tboard, H, W);
        this->Remove(tboard, H, W);
        
        if (((double)pcnt) / (H*W) < 0.2) {
            this->Solve(tboard, H, W);
        } else {
            this->SolveSA(tboard, H, W, 9200);
        }
        
        
        this->Remove(tboard, H, W);
        
        bool f = true;
        while (f) {
            f = false;
            for (int y=2; y<H+2; ++y) {
                for (int x=2; x<W+2; ++x) {
                    int bcnt = 0;
                    if (tboard[y][x] != 0) { continue; }
                    for (int z=0; z<8; ++z) {
                        int py = y + dy[z];
                        int px = x + dx[z];
                        if (tboard[py][px] == -1) { bcnt += 1; }
                        if (tboard[py][px] == 2) { bcnt += 10; }
                    }
                    
                    if (bcnt == 2) {
                        tboard[y][x] = 2;
                        f = true;
                    }
                }
            }
        }
        this->Remove(tboard, H, W);
        // this->Remove(tboard, H, W);
        this->TPut2(tboard, H, W);
        this->TPut3(tboard, H, W);
        this->TPut4(tboard, H, W);
        this->Remove(tboard, H, W);
        
        
        this->Solve2(tboard2, H, W, 9200);
        this->Remove(tboard2, H, W);
        this->TPut2(tboard2, H, W);
        this->TPut3(tboard2, H, W);
        this->TPut4(tboard2, H, W);
        this->Remove(tboard2, H, W);

        
        // cerr << this->sw.get_milli_time();
        
        if (this->AllScore(tboard, H, W) > this->AllScore(tboard2, H, W)) {
            return this->BoardToRet(tboard, H, W);
        } else {
            return this->BoardToRet(tboard2, H, W);
        }
        
        
        
        
        return this->BoardToRet(tboard, H, W);
    }
    
    void SolveSA (vector< vector<int> > &board, int H, int W, int limit) {
        vector< vector<int> > bestboard = board;
        double lastscore = this->AllScore(board, -0.5, H, W);
        double bestscore = lastscore;
        int saTimeStart = this->sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 10000000;
        
        int loop = H*W > 8000 ? 20000 : 40000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            if (saTimeCurrent > 8000) { loop = 4000; }
            for (int i = 0; i < loop; ++i) {
                int ty = xrnd() % H + 2;
                int tx = xrnd() % W + 2;
                if (board[ty][tx] < 0) { continue; }
                int tmp = board[ty][tx];
                board[ty][tx] = board[ty][tx] == 0 ? 2 : 0;
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                // double tscore = this->AllScore(board, -0.5, H, W);
                double tscore = tmp == 0 ? this->DiffScore(board, -0.5, H, W, ty, tx) + lastscore : this->AllScore(board, -0.5, H, W) ;
                
                double startTemp   = 1.0;
                double endTemp     = 0.0;
                double temp        = startTemp + (endTemp - startTemp) * t / T;
                double probability = exp((tscore - lastscore) / temp);
                bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tscore > lastscore || (FORCE_NEXT)) {
                    lastscore = tscore;
                    
                    if (lastscore < bestscore - 64) {
                        // lastscore = bestscore;
                        board = bestboard;
                    }
                    if (tscore > bestscore) {
                        bestscore = tscore;
                        bestboard = board;
                    }
                } else {
                    board[ty][tx] = tmp;
                }
                
                cnt += 1;
            }
            
        }
        board = bestboard;
        // cerr << cnt;
    }
    
    
    
    void Solve2 (vector< vector<int> > &board, int H, int W, int limit) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        vector<mpos> v;
        for (int y=2; y<H+2; ++y) {
            for (int x=2; x<W+2; ++x) {
                v.emplace_back(x, y);
            }
        }
        
        mt19937 mt(xrnd());
        
        
        bool f = true;
        
        
        
        while (f) {
            f = false;
            // shuffle(v.begin(), v.end(), mt);
            for (auto &m : v) {
                const int x = m.x;
                const int y = m.y;
                
                int bcnt = 0;
                if (board[y][x] != 0) { continue; }
                
                vector<mpos> pos;
                vector<mpos> path;
                for (int z=0; z<8; ++z) {
                    int py = y + dy[z];
                    int px = x + dx[z];
                    if (board[py][px] == 0) { pos.emplace_back(px, py); }
                    if (board[py][px] == -1) { bcnt += 1; }
                    if (board[py][px] == 2) { bcnt += 10; }
                }
                
                if (bcnt == 2) {
                    f = true;
                    board[y][x] = 2;
                    continue;
                }
                
                if (bcnt != 1) { continue; }
                
                mpos prev(x, y);
                path.emplace_back(x, y);
                bool b = false;
                for (int i = 0; i < 16; ++i) {
                    
                    for (auto &j : pos) {
                        b = false;
                        path[path.size()-1].x = j.x;
                        path[path.size()-1].y = j.y;
                        bcnt = 1;
                        vector<mpos> pos2;
                        for (int z=0; z<8; ++z) {
                            int py = j.y + dy[z];
                            int px = j.x + dx[z];
                            if (px == prev.x && py == prev.y) { continue; }
                            if (board[py][px] == 0) { pos2.emplace_back(px, py); }
                            if (board[py][px] == -1) { bcnt += 1; }
                            if (board[py][px] == 2) { bcnt += 10; }
                        }
                        
                        if (bcnt == 2) {
                            b = true;
                            board[j.y][j.x] = 2;
                            break;
                        }
                        if (bcnt == 1) {
                            path.emplace_back(j.x, j.y);
                            prev.x = j.x;
                            prev.y = j.y;
                            pos = pos2;
                            break;
                        }
                        
                    }
                    if (b) {
                        for (auto &k : path) { board[k.y][k.x] = 2; }
                        
                        
                        board[y][x] = 2;
                        f = true;
                        
                        break;
                        
                    }
                }
            }
            
        }
    }
    
    
    
    void Solve (vector< vector<int> > &board, int H, int W) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        
        double score = this->AllScore(board, 0, H, W);
        double bestscore = score;
        int cnt = 0;
        
        int ntime = this->sw.get_milli_time();
        int loop = H*W > 8000 ? 5000 : 10000;
        while (ntime < 9200) {
            // cnt += 1;
            if (ntime > 8000) { loop = 1000; }
            for (int i = 0; i < loop; ++i) {
                double t = (1.0 - (ntime / 9200));
                int ty = xrnd() % H + 2;
                int tx = xrnd() % W + 2;
                if (board[ty][tx] < 0) { continue; }
                int tmp = board[ty][tx];
                board[ty][tx] = board[ty][tx] == 0 ? 2 : 0;
                double tscore = this->AllScore(board, -0.5 + t*0.5, H, W);
                // double tscore = tmp == 0 ? this->DiffScore(board, -0.5 + t, H, W, ty, tx) + bestscore : this->AllScore(board, -0.5 + t, H, W) ;
                if (tscore > bestscore || (tscore >= bestscore - t && xrnd() % 128 < 128 * t)) {
                    bestscore = tscore;
                } else {
                    board[ty][tx] = tmp;
                }
                cnt += 1;
            }
            ntime = this->sw.get_milli_time();
            
            
        }
        // cerr << cnt;
    }
    
    double DiffScore (vector< vector<int> > &board, double ascore, int H, int W, int ty, int tx) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        
        double score = 0;
        
        int bcnt = 0;
        int pcnt = 0;
        int ppcnt = 0;
        int pppcnt = 0;
        if (board[ty][tx] == 2) {
            for (int z=0; z<8; ++z) {
                int py = ty + dy[z];
                int px = tx + dx[z];
                if (board[py][px] == -1) { bcnt += 1; }
                if (board[py][px] == 2) { bcnt += 1; }
                
                if (board[py][px] != 2) { continue; }
                int bbcnt = 0;
                for (int zz=0; zz<8; ++zz) {
                    int ppy = py + dy[zz];
                    int ppx = px + dx[zz];
                    if (board[ppy][ppx] == -1) { bbcnt += 1; }
                    if (board[ppy][ppx] == 2) { bbcnt += 1; }
                }
                if (bbcnt == 2) {
                    score += 1;
                    pcnt += 1;
                } else if (bbcnt == 1) {
                    score += ascore;
                    ppcnt += 1;
                } else if (bbcnt > 2) {
                    score += -10;
                    pppcnt += 1;
                }
                
            }
            
            if (bcnt == 2) {
                score += 1 - pcnt;
            } else if (bcnt == 1) {
                score += ascore - ascore * ppcnt;
            } else if (bcnt > 2) {
                score += -10 + 10 * pppcnt;
            }
            
        } else {
            
            
            
            
            
            
        }
        
        
        
        return score;
    }
    
    inline double AllScore (vector< vector<int> > &board, double ascore, int H, int W) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        
        double score = 0;
        
        for (int y=2; y<H+2; ++y) {
            for (int x=2; x<W+2; ++x) {
                int bcnt = 0;
                if (board[y][x] < 1) { continue; }
                for (int z=0; z<8; ++z) {
                    const int py = y + dy[z];
                    const int px = x + dx[z];
                    if (board[py][px] == -1) {
                        bcnt += 1;
                    } else if (board[py][px] == 2) { bcnt += 1; }
                }
                
                if (bcnt == 2) {
                    score += 1;
                } else if (bcnt == 1) {
                    score += ascore;
                } else if (bcnt > 2) {
                    score += -10;
                }
            }
        }
        return score;
    }
    
    double AllScore (vector< vector<int> > &board, int H, int W) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        
        double score = 0;
        
        for (int y=2; y<H+2; ++y) {
            for (int x=2; x<W+2; ++x) {
                int bcnt = 0;
                if (board[y][x] < 1) { continue; }
                for (int z=0; z<8; ++z) {
                    int py = y + dy[z];
                    int px = x + dx[z];
                    if (board[py][px] == -1) { bcnt += 1; }
                    if (board[py][px] == 2) { bcnt += 1; }
                }
                
                if (bcnt == 2) {
                    score += 1;
                } else if (bcnt == 1) {
                    return -1;
                } else if (bcnt > 2) {
                    return -1;
                }
            }
        }
        return score;
    }
    
    
    void TPut4 (vector< vector<int> > &board, int H, int W) {
        static const int dy1[] = {-2, -1, 0, 1};
        static const int dx1[] = {-1, 0, 1, 2};
        static const int dy2[] = {-1, 1, -1, -2};
        static const int dx2[] = {-1, 0, 1, 2};
        double bestscore = this->AllScore(board, H, W);
        for (int y=2; y<H; ++y) {
            if (y % 5 == 0 && this->sw.get_milli_time() > 9600) { break; }
            for (int x=2; x<W; ++x) {
                vector<mpos> v;
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<4; ++z) {
                    int py = y + dy1[z];
                    int px = x + dx1[z];
                    if (board[py][px] == 0) {
                        board[py][px] = 2;
                        v.emplace_back(px, py);
                    }
                }
                
                double tscore = this->AllScore(board, H, W);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    for (auto &i : v) { board[i.y][i.x] = 0; }
                }
            }
        }
        for (int y=2; y<H; ++y) {
            if (y % 5 == 0 && this->sw.get_milli_time() > 9600) { break; }
            for (int x=2; x<W; ++x) {
                vector<mpos> v;
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<4; ++z) {
                    int py = y + dy2[z];
                    int px = x + dx2[z];
                    if (board[py][px] == 0) {
                        board[py][px] = 2;
                        v.emplace_back(px, py);
                    }
                }
                
                double tscore = this->AllScore(board, H, W);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    for (auto &i : v) { board[i.y][i.x] = 0; }
                }
            }
        }
    }
    
    void TPut3 (vector< vector<int> > &board, int H, int W) {
        static const int dy1[] = {0, -1, -1, 0, 1, 1};
        static const int dx1[] = {-1, 0, 1, 2, 1, 0};
        static const int dy2[] = {-1, 0, 1, 2, 1, 0};
        static const int dx2[] = {0, -1, -1, 0, 1, 1};
        double bestscore = this->AllScore(board, H, W);
        for (int y=2; y<H; ++y) {
            if (y % 5 == 0 && this->sw.get_milli_time() > 9600) { break; }
            for (int x=2; x<W; ++x) {
                vector<mpos> v;
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<6; ++z) {
                    int py = y + dy1[z];
                    int px = x + dx1[z];
                    if (board[py][px] == 0) {
                        board[py][px] = 2;
                        v.emplace_back(px, py);
                    }
                }
                
                double tscore = this->AllScore(board, H, W);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    for (auto &i : v) { board[i.y][i.x] = 0; }
                }
            }
        }
        for (int y=2; y<H; ++y) {
            if (y % 5 == 0 && this->sw.get_milli_time() > 9600) { break; }
            for (int x=2; x<W; ++x) {
                vector<mpos> v;
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<6; ++z) {
                    int py = y + dy2[z];
                    int px = x + dx2[z];
                    if (board[py][px] == 0) {
                        board[py][px] = 2;
                        v.emplace_back(px, py);
                    }
                }
                
                double tscore = this->AllScore(board, H, W);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    for (auto &i : v) { board[i.y][i.x] = 0; }
                }
            }
        }
    }
    
    
    void TPut2 (vector< vector<int> > &board, int H, int W) {
        static const int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
        static const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
        double bestscore = this->AllScore(board, H, W);
        
        for (int y=3; y<H+1; ++y) {
            if (y % 5 == 0 && this->sw.get_milli_time() > 9600) { break; }
            for (int x=3; x<W+1; ++x) {
                vector<mpos> v;
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<8; ++z) {
                    int py = y + dy[z];
                    int px = x + dx[z];
                    if (board[py][px] == 0) {
                        board[py][px] = 2;
                        v.emplace_back(px, py);
                    }
                }
                
                double tscore = this->AllScore(board, H, W);
                if (tscore > bestscore) {
                    bestscore = tscore;
                } else {
                    for (auto &i : v) { board[i.y][i.x] = 0; }
                }
            }
        }
    }
    
    void TPut (vector< vector<int> > &board, int H, int W) {
        static const int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
        static const int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
        
        for (int y=3; y<H+1; y+=5) {
            for (int x=3; x<W+1; x+=5) {
                if (board[y][x] != 0) { continue; }
                for (int z=0; z<8; ++z) {
                    int py = y + dy[z];
                    int px = x + dx[z];
                    if (board[py][px] == 0) { board[py][px] = 2; }
                }
            }
        }
        
    }
    
    void Remove (vector< vector<int> > &board, int H, int W) {
        static const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        bool f = true;
        while (f) {
            f = false;
            for (int y=2; y<H+2; ++y) {
                for (int x=2; x<W+2; ++x) {
                    int bcnt = 0;
                    if (board[y][x] < 1) { continue; }
                    for (int z=0; z<8; ++z) {
                        int py = y + dy[z];
                        int px = x + dx[z];
                        if (board[py][px] == -1) { bcnt += 1; }
                        if (board[py][px] == 2) { bcnt += 1; }
                    }
                    
                    if (bcnt != 2) {
                        board[y][x] = 0;
                        f = true;
                    }
                    
                }
            }
        }
    }
    
    
    
    vector<string> BoardToRet (vector< vector<int> > &board, int H, int W) {
        vector<string> ret;
        for (int y=2; y<H+2; ++y) {
            string s = "";
            for (int x=2; x<W+2; ++x) {
                if (board[y][x] > 0) {
                    s += 'K';
                } else {
                    s += '.';
                }
            }
            ret.emplace_back(s);
        }
        return ret;
    }
    
    
};




// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    KnightsAndPawns kap;
    int H;
    cin >> H;
    vector<string> board(H);
    getVector(board);
    
    vector<string> ret = kap.placeKnights(board);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
