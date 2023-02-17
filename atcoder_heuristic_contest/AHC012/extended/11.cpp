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

inline double distance (const int& ax, const int& ay, const int& bx, const int& by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}



inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}

struct mmout {
    int cx, cy, dx, dy;
    mmout () {
        this->cx = 0;
        this->cy = 0;
        this->dx = 10000;
        this->dy = 0;
    }
    
    
    void position (int x, int y) {
        this->cx = x;
        this->cy = y;
    }
    
    void rotate (double r) {
        int tx = cos(r)*this->dx - sin(r)*this->dy;
        int ty = sin(r)*this->dx + cos(r)*this->dy; 
        this->dx = tx;
        this->dy = ty;
    }
    
    string out () {
        return print(this->cx, this->cy , this->cx+this->dx, this->cy +this->dy);
    }
    
};



class MM {
public:
    StopWatch sw;
    int N, K;
    array<int, 10> a;
    vector<e512pos> v;
    
    vector<mmout> bestout;
    double pi = 3.141592653589793;
    vector< vector<int> > initpieces;
    
    MM () { this->sw = StopWatch(); }
    
    
    
    void input () {
        cin >> this->N >> this->K;
        for (int i = 0; i < 10; ++i) { cin >> this->a[i]; }
        for (int i = 0; i < this->N; ++i) {
            e512pos t;
            cin >> t.x >> t.y;
            v.emplace_back(t);
        }
        
        
        
        
        this->initpieces.emplace_back(vector<int>());
        for (int i = 0; i < this->N; ++i) { this->initpieces[0].emplace_back(i); }
        
        
    }
    
    
    
    vector<mmout> maximize_sa (vector<mmout> v, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector<mmout> bestv = v;
        double bestscore = this->calcscore(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        while (true) {
            {
                ntime = sw.get_milli_time();
                if (ntime >= etime) { break; }
                int a = xrnd() % (v.size()-8) + 8;
                int cx = v[a].cx;
                int cy = v[a].cy;
                v[a].position(cx, xrnd()%20001-10000);
                
                
                
                double tmpscore = this->calcscore(v);
                const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestv = v;
                    }
                } else {
                    v[a].cx = cx;
                    v[a].cy = cy;
                }
                cnt += 1;
            }
        }
        pdebug(cnt);
        return bestv;
    }
    
    int calcscore (vector<mmout>& out) {
        static vector< vector<int> > pieces;
        
        static vector< vector<int> > new_pieces;
        static vector<int> left;
        static vector<int> right;
        pieces = this->initpieces;
        for (auto&& i : out) {
            const int px = i.cx;
            const int py = i.cy;
            const int qx = i.cx + i.dx;
            const int qy = i.cy + i.dy;
            new_pieces.clear();
            
            for (auto&& piece : pieces) {
                left.clear();
                right.clear();
                for (auto&& j : piece) {
                    const int x = this->v[j].x;
                    const int y = this->v[j].y;
                    const int side = (qx - px) * (y - py) - (qy - py) * (x - px);
                    if (side > 0) {
                        left.emplace_back(j);
                    } else if (side < 0) {
                        right.emplace_back(j);
                    }
                }
                if (left.size() > 0) {
                    new_pieces.emplace_back(left);
                }
                if (right.size() > 0) {
                    new_pieces.emplace_back(right);
                }
            }
            pieces = new_pieces;
            
        }
        
        int score = 0;
        array<int, 10> b = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto&& piece : pieces) {
            if (piece.size() <= 10) {
                b[piece.size() - 1] += 1;
            }
        }
        int num = 0;
        int den = 0;
        for (int d = 0; d < 10; ++d) {
            num += min(this->a[d], b[d]);
            den += this->a[d];
        }
        score = round(1e6 * num / (double)den);
        
        return score;
    }
    
    
    // k
    // x1 y1 x2 y2
    void output () {
        cout << this->bestout.size() << endl;
        for (auto&& i : this->bestout) {
            cout << i.out() << endl;
        }
        
    }
    void solve () {
        
        int k = 100;
        
        for (int i = 0; i < k; ++i) {
            this->bestout.emplace_back(mmout());
        }
        
        for (int i = 0; i < 8; ++i) {
            this->bestout[i].rotate(this->pi/2);
            this->bestout[i].position((20000/(9))*(i+1)-10000, 0);
        }
        for (int i = 0; i < k-8; ++i) {
            this->bestout[i+8].position(0, (20000/(k/2))*i-10000);
        }
        this->bestout = this->maximize_sa(this->bestout, 2800, 2, 0);
        int bestscore = this->calcscore(bestout);
        while (this->bestout.size() < this->K && this->sw.get_milli_time() < 2940) {
            int y = xrnd() % 20001 - 10000;
            mmout m;
            m.position(0, y);
            bestout.emplace_back(m);
            int score = this->calcscore(bestout);
            if (score > bestscore) {
                bestscore = score;
            } else {
                bestout.pop_back();
            }
        }
        
        pdebug(this->calcscore(bestout), this->sw.get_milli_time());
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

