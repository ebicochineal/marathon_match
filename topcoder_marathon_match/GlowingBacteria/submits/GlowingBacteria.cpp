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

const vector< vector< vector<int> > > granges = {{} ,{{-1, 0} ,{0, -1} ,{0, 1} ,{1, 0}} ,{{-1, -1} ,{-1, 0} ,{-1, 1} ,{0, -1} ,{0, 1} ,{1, -1} ,{1, 0} ,{1, 1}} ,{{-1, -1} ,{-1, 0} ,{-1, 1} ,{0, -1} ,{0, 1} ,{1, -1} ,{1, 0} ,{1, 1}} ,{{-2, 0} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{1, -1} ,{1, 0} ,{1, 1} ,{2, 0}} ,{{-2, -1} ,{-2, 0} ,{-2, 1} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{2, -1} ,{2, 0} ,{2, 1}} ,{{-2, -1} ,{-2, 0} ,{-2, 1} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{2, -1} ,{2, 0} ,{2, 1}} ,{{-2, -1} ,{-2, 0} ,{-2, 1} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{2, -1} ,{2, 0} ,{2, 1}} ,{{-2, -2} ,{-2, -1} ,{-2, 0} ,{-2, 1} ,{-2, 2} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{2, -2} ,{2, -1} ,{2, 0} ,{2, 1} ,{2, 2}} ,{{-3, 0} ,{-2, -2} ,{-2, -1} ,{-2, 0} ,{-2, 1} ,{-2, 2} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{0, -3} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{0, 3} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{2, -2} ,{2, -1} ,{2, 0} ,{2, 1} ,{2, 2} ,{3, 0}} ,{{-3, -1} ,{-3, 0} ,{-3, 1} ,{-2, -2} ,{-2, -1} ,{-2, 0} ,{-2, 1} ,{-2, 2} ,{-1, -3} ,{-1, -2} ,{-1, -1} ,{-1, 0} ,{-1, 1} ,{-1, 2} ,{-1, 3} ,{0, -3} ,{0, -2} ,{0, -1} ,{0, 1} ,{0, 2} ,{0, 3} ,{1, -3} ,{1, -2} ,{1, -1} ,{1, 0} ,{1, 1} ,{1, 2} ,{1, 3} ,{2, -2} ,{2, -1} ,{2, 0} ,{2, 1} ,{2, 2} ,{3, -1} ,{3, 0} ,{3, 1}}};


class GlowingBacteria {
public:
    StopWatch sw;
    int N, C, D, K;
    int grid[6][55][55];
    int rawgrid[55][55];
    int tgrid[55][55];
    int bestgrid[55][55];
    
    double ggrid[8][55][55];
    
    bool gridf[55][55];
    vector<char> findSolution(int N, int C, int D, int K, char grid[]) {
        this->sw = StopWatch();
        this->N = N;
        this->C = C;
        this->D = D;
        this->K = K;
        
        for (int y = 0; y < 55; ++y) {
            for (int x = 0; x < 55; ++x) {
                for (int z = 0; z < 6; ++z) {
                    this->grid[z][y][x] = -1;
                }
                this->rawgrid[y][x] = -1;
                this->gridf[y][x] = false;
                for (int z = 0; z < 8; ++z) {
                    this->ggrid[z][y][x] = 0;
                }
            }
        }
        
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->grid[0][y][x] = (int)grid[y * this->N + x] - 48;
                this->rawgrid[y][x] = (int)grid[y * this->N + x] - 48;
            }
        }
        
        this->calcStep();
        int bestscore = this->calcScore();
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                int ccnt = 0;
                for (int i = 0; i < this->D; ++i) {
                    ccnt += this->grid[0][y][x] == this->grid[i + 1][y][x];
                }
                
                if (ccnt == this->D) {
                    this->gridf[y][x] = true;
                }
                
            }
        }
        int cnt = 0;
        
        
        int bestc = -1;
        int tscore = bestscore;
        
        this->SA(8000);
        this->calcStep();
        bestscore = this->calcScore();
        if ((bestscore < tscore * 1.3 && this->C == 2) || (bestscore < tscore * 1.6 && this->C == 3) || (bestscore < tscore * 1.8 && this->C == 4) || (this->C > 4)) {
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    this->grid[0][y][x] = this->rawgrid[y][x];
                }
            }
        }
        
        this->calcStep();
        pdebug(this->N, this->C, this->D, this->K, cnt);
        
        return this->toRet();
    }
    
    vector<char> toRet () {
        vector<char> r;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                r.emplace_back(this->grid[0][y][x] + 48);
                //r.emplace_back(this->rawgrid[y][x] + 48);
            }
        }
        return r;
    }
    
    void SA (int limit) {////
        StopWatch sw;
        for (int y = 0; y < 55; ++y) {
            for (int x = 0; x < 55; ++x) {
                this->bestgrid[y][x] = this->grid[0][y][x];
            }
        }
        this->calcStep();
        double bestscore = this->calcScore();////
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 8; ++z) {
                // int x = (xrnd() % (this->N / 4)) * 4;
                // int y = (xrnd() % (this->N / 4)) * 4;
                // int w = 4;
                // int h = 4;
                // if (x == this->N / 4 - 1) { w += 4; }
                // if (y == this->N / 4 - 1) { h += 4; }
                
                
                int x = xrnd() % this->N;
                int y = xrnd() % this->N;
                int w = xrnd() % (this->N / 4) + 1;
                int h = xrnd() % (this->N / 4) + 1;
                
                int c = xrnd() % this->C;
                this->grid0(x, y, w, h, c);
                
                this->calcStep();
                double tmpscore = this->calcScore();
                
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 4.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        for (int y = 0; y < 55; ++y) {
                            for (int x = 0; x < 55; ++x) {
                                this->bestgrid[y][x] = this->grid[0][y][x];
                            }
                        }
                    }
                } else {
                    this->grid1(x, y, w, h);
                }
            }
        }
        
        for (int y = 0; y < 55; ++y) {
            for (int x = 0; x < 55; ++x) {
                this->grid[0][y][x] = this->bestgrid[y][x];
            }
        }
    }
    
    
    void grid0 (int sx, int sy, int w, int h, int c) {
        int ex = min(sx+w, this->N);
        int ey = min(sy+h, this->N);
        for (int y = sy; y < ey; ++y) {
            for (int x = sx; x < ex; ++x) {
                this->tgrid[y][x] = this->grid[0][y][x];
                this->grid[0][y][x] = c;
            }
        }
    }
    
    void grid1 (int sx, int sy, int w, int h) {
        int ex = min(sx+w, this->N);
        int ey = min(sy+h, this->N);
        for (int y = sy; y < ey; ++y) {
            for (int x = sx; x < ex; ++x) {
                this->grid[0][y][x] = this->tgrid[y][x];
            }
        }
    }
    
    void calcStep () {
        for (int z = 0; z < this->D; ++z) {
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    this->calcStep2(y, x, z, z+1);
                }
            }
        }
    }
    
    void calcStep2 (int y, int x, int a, int b) {
        static int colors[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 10; ++i) { colors[i] = 0; }
        for (int w = 0; w < granges[this->K].size(); ++w) {
            int py = y + granges[this->K][w][0];
            int px = x + granges[this->K][w][1];
            if (this->outside(px, py)) { continue; }
            colors[this->grid[a][py][px] + 1] += 1;
        }
        
        int minc = 0;
        int mincnt = 100;
        bool f = true;
        for (int i = 1; i < this->C+1; ++i) {
            if (colors[i] > 0 && colors[i] < mincnt) {
                minc = i;
                mincnt = colors[i];
                f = true;
            } else if (colors[i] == mincnt) {
                f = false;
            }
        }
        if (minc > 0 && f) {
            this->grid[b][y][x] = minc - 1;
        } else {
            this->grid[b][y][x] = this->grid[a][y][x];
        }
        
    }
    
    int calcScore () {
        int score = 0;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                score += this->rawgrid[y][x] == this->grid[this->D][y][x];
            }
        }
        return score;
    }
    
    bool outside (int x, int y) {
        return (x < 0 || x >= this->N || y < 0 || y >= this->N);
    }
    bool inside (int x, int y) {
        return !(x < 0 || x >= this->N || y < 0 || y >= this->N);
    }
    
};

int main() {
    GlowingBacteria gb;
    int N;
    int C;
    int D;
    int K;
    cin >> N;
    cin >> C;
    cin >> D;
    cin >> K;
    
    char grid[N*N];
    for (int i=0; i<N*N; i++) cin >> grid[i];
    
    vector<char> ret = gb.findSolution(N, C, D, K, grid);
    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i] << endl;
    cout.flush();
}

