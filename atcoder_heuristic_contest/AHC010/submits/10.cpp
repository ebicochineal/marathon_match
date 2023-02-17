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



// #include <time.h>
// #include <sys/timeb.h>
// class StopWatch {
// public:
//     int starts;
//     int startm;
//     int tstarts = 0;
//     int tstartm = 0;
//     struct timeb timebuffer;
//     StopWatch () {
//         ftime(&this->timebuffer);
//         this->starts = this->timebuffer.time;
//         this->startm = this->timebuffer.millitm;
//     }
//     inline void stop () {
//         ftime(&this->timebuffer);
//         this->tstarts = this->timebuffer.time;
//         this->tstartm = this->timebuffer.millitm;
//     }
//     inline void resume () {
//         ftime(&this->timebuffer);
//         this->starts += this->timebuffer.time - this->tstarts;
//         this->startm += this->timebuffer.millitm - this->tstartm;
//     }
//     inline int get_milli_time () {
//         ftime(&this->timebuffer);
//         return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
//     }
// };

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


inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}

int to[8][4] = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};



class MM {
public:
    
    StopWatch sw;
    bitset<900> use;
    array< array<int, 30>, 30> grid;
    array< array<int, 30>, 30> rgrid;
    array< array<int, 30>, 30> rot;
    MM () { this->sw = StopWatch(); }
    void input () {
        
        for (int y = 0; y < 30; ++y) {
            string s;
            cin >> s;
            for (int x = 0; x < 30; ++x) {
                this->grid[y][x] = (int)s[x]-(int)'0';
            }
        }
        this->rgrid = this->grid;
        
        this->sw = StopWatch();
        
        int bestscore = 0;
        array< array<int, 30>, 30> rot;
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                this->rot[y][x] = 0;
                rot[y][x] = 0;
            }
        }
        int cnt = 0;
        
        this->rot = this->maximize_sa(rot, 1950, 16, 0);
        
        
        this->updatergrid(this->rot, this->grid);
        pdebug(this->truescore());
        
    }
    
    array< array<int, 30>, 30> maximize_sa (array< array<int, 30>, 30> v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        array< array<int, 30>, 30> bestv = v;
        
        this->updatergrid(v, this->grid);
        double bestscore = this->vscore();
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        array<int, 900> tmp;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            
            int n = 2 + xrnd() % 6;
            int ry = xrnd()%(31-n);
            int rx = xrnd()%(31-n);
            for (int y = 0; y < n; y+=1) {
                for (int x = 0; x < n; x+=1) {
                    tmp[y*n+x] = v[ry+y][rx+x];
                    v[ry+y][rx+x] = xrnd() % 3;
                }
            }
            this->updatergrid(v, this->grid);
            
            double tmpscore = this->vscore();
            const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
            const double probability = exp((tmpscore - lastscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore > lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore > bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                for (int y = 0; y < n; y+=1) {
                    for (int x = 0; x < n; x+=1) {
                        v[ry+y][rx+x] = tmp[y*n+x];
                    }
                }
            }
            cnt += 1;
        }
        pdebug(cnt);
        return bestv;
    }

    
    
    void updatergrid (array< array<int, 30>, 30>& r, array< array<int, 30>, 30>& g) {
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                if (g[y][x] < 4) {
                    this->rgrid[y][x] = (g[y][x]+r[y][x]) % 4;
                } else if (g[y][x] < 6) {
                    this->rgrid[y][x] = 4+(g[y][x]-4+r[y][x]) % 2;
                } else {
                    this->rgrid[y][x] = 6+(g[y][x]-6+r[y][x]) % 2;
                }
            }
        }
    }
    
    void output () {
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                cout << this->rot[y][x];;
            }
        }
        cout << endl;
    }
    void solve () {}
    
    
    int truescore () {
        this->use.reset();
        int a = 0;
        int b = 0;
        int c = 0;
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                if (this->use[y*30+x]) { continue; }
                int t = this->truepscore(y, x);
                if (t >= a) {
                    b = a;
                    a = t;
                } else if (t > b) {
                    b = t;
                }
            }
        }
        
        return a*b;
    }
    int truepscore (int si, int sj) {
        static int di[4] = {0, -1, 0, 1};
        static int dj[4] = {-1, 0, 1, 0};
        // lurd
        
        int sumlength = 0;
        this->use[si*30+sj] = true;
        
        for (int sd = 0; sd < 4; ++sd) {
            int length = 0;
            int i = si;
            int j = sj;
            int d = sd;
            while (1) {
                int d2 = to[this->rgrid[i][j]][d];
                if (d2 == -1) { break; }
                i += di[d2];
                j += dj[d2];
                if (i < 0 || i >= 30 || j < 0 || j >= 30) { break; }
                this->use[i*30+j] = true;
                d = (d2 + 2) % 4;
                length += 1;
                if (i == si && j == sj && d == sd) { return length; }
            }
            sumlength += length;
        }
        return 0;
    }
    
    
    
    int vscore () {
        this->use.reset();
        int a = 0;
        int b = 0;
        int c = 0;
        
        for (int y = 0; y < 30; ++y) {
            for (int x = 0; x < 30; ++x) {
                if (this->use[y*30+x]) { continue; }
                int t = this->vpscore(y, x);
                c += this->sumlength * this->sumlength;
                if (t >= a) {
                    b = a;
                    a = t;
                } else if (t > b) {
                    b = t;
                }
            }
        }
        return a*b+c/30;
    }
    
    int sumlength = 0;
    int vpscore (int si, int sj) {
        static int di[4] = {0, -1, 0, 1};
        static int dj[4] = {-1, 0, 1, 0};
        // lurd
        this->sumlength = 0;
        this->use[si*30+sj] = true;
        
        for (int sd = 0; sd < 4; ++sd) {
            int length = 0;
            int i = si;
            int j = sj;
            int d = sd;
            while (1) {
                int d2 = to[this->rgrid[i][j]][d];
                if (d2 == -1) { break; }
                i += di[d2];
                j += dj[d2];
                if (i < 0 || i >= 30 || j < 0 || j >= 30) { break; }
                this->use[i*30+j] = true;
                d = (d2 + 2) % 4;
                length += 1;
                if (i == si && j == sj && d == sd) { return length * 30; }
            }
            this->sumlength += length;
        }
        return 0;
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

