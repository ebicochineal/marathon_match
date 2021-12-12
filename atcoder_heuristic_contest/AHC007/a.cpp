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
#include <bitset>
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

// d*1 <= true_dist <= d*3
inline int distance1 (const int ax, const int ay, const int bx, const int by) {
    return (int)sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

const int gN = 400;
const int gM = 1995;

class MM {
public:
    StopWatch sw;
    const int N = gN;
    const int M = gM;
    array<int, gN> ax, ay;
    array<int, gM> au, av;
    
    array< array<int, gN>, gN > vmat;
    array<int, gM> vdists;
    array< array<int, gN>, gN > mat_to_i;
    
    bitset<gM> used;
    bitset<gM> use;
    
    MM () { this->sw = StopWatch(); }
    void input () {
        for (int u = 0; u < this->N; ++u) {
            for (int v = 0; v < this->N; ++v) {
                this->vmat[u][v] = 1000000;
                this->mat_to_i[u][v] = -1;
            }
        }
        
        for (int i = 0; i < this->N; ++i) {
            cin >> this->ax[i] >> this->ay[i];
        }
        
        for (int i = 0; i < this->M; ++i) {
            int u, v;
            cin >> u >> v;
            this->mat_to_i[u][v] = i;
            this->mat_to_i[v][u] = i;
            this->au[i] = u;
            this->av[i] = v;
            int d = distance1(this->ax[u], this->ay[u], this->ax[v], this->ay[v]);
            this->vmat[u][v] = d;
            this->vmat[v][u] = d;
            vdists[i] = d;
        }
    }
    void solve () {
        int prevscore = this->mst0();
        bool f = false;
        for (int i = 0; i < this->M; ++i) {
            int true_dist;
            cin >> true_dist;
            int u = this->au[i];
            int v = this->av[i];
            
            int score = prevscore;
            
            
            int vdist = this->vmat[u][v];
            this->vmat[u][v] = true_dist;
            this->vmat[v][u] = true_dist;
            this->vdists[i] = true_dist;
            
            if (this->use[i]) {
                cout << 1 << endl;
                this->used[i] = true;
            } else {
                cout << 0 << endl;
            }
            
            cout.flush();
        }
        
        pdebug(this->sw.get_milli_time());
    }
    
    int mst0 () {
        bitset<gN> vuse;
        for (int i = 0; i < this->M; ++i) {
            this->use[i] = false;
        }
        
        vuse[0] = true;
        while (vuse.count() < this->N) {
            int bestdist = 1000000;
            int bestedge = -1;
            
            for (int i = 0; i < this->M; ++i) {
                if (this->use[i]) { continue; }
                int u = this->au[i];
                int v = this->av[i];
                if (vuse[u] == vuse[v]) { continue; }
                
                int dist = this->vmat[u][v];
                    
                if (dist < bestdist) {
                    bestdist = dist;
                    bestedge = i;
                }
            }
            
            this->use[bestedge] = true;
            vuse[this->au[bestedge]] = true;
            vuse[this->av[bestedge]] = true;
            
        }
        int score = 0;
        for (int i = 0; i < this->M; ++i) {
            if (this->use[i]) { score += this->vmat[this->au[i]][this->av[i]]; }
        }
        
        return score;
    }
    
    
    int mst1 () {
        bitset<gN> vuse;
        
        array<int, gN> aunion;
        for (int i = 0; i < this->N; ++i) { aunion[i] = -1; }
        
        int ucnt = 0;
        int ucnt_d = 0;
        for (int i = 0; i < this->M; ++i) {
            this->use[i] = this->used[i];
        }
        
        for (int i = 0; i < this->M; ++i) {
            if (this->used[i]) {
                int u = this->au[i];
                int v = this->av[i];
                int maxuv = max(aunion[u], aunion[v]);
                int minuv = min(aunion[u], aunion[v]);
                if (aunion[u] == -1 && aunion[v] == -1) {
                    aunion[u] = ucnt;
                    aunion[v] = ucnt;
                    ucnt += 1;
                } else if (aunion[u] == -1 || aunion[v] == -1) {
                    aunion[u] = maxuv;
                    aunion[v] = maxuv;
                } else if (aunion[u] > -1 && aunion[v] > -1 && aunion[u] != aunion[v]) {
                    for (int z = 0; z < this->N; ++z) {
                        if (aunion[z] == minuv) { aunion[z] = maxuv; }
                    }
                    ucnt_d += 1;
                }
            }
        }
        
        int g = 0;
        for (int i = 0; i < this->N; ++i) {
            if (aunion[i] > -1) {
                g = aunion[i];
            } else {
                ucnt += 1;
            }
        }
        for (int i = 0; i < this->N; ++i) {
            if (aunion[i] == g) { vuse[i] = true; }
        }
        
        int loop = ucnt - ucnt_d - 1;
        
        bool f = false;
        for (int i = 0; i < this->N; ++i) {
            if (aunion[i] != g) {
                f = true;
                break;
            }
        }
        
        while (f) {
            int bestdist = 1000000;
            int bestedge = -1;
            
            for (int i = 0; i < this->M; ++i) {
                if (this->use[i]) { continue; }
                int u = this->au[i];
                int v = this->av[i];
                if (vuse[u] == vuse[v]) { continue; }
                
                int dist = this->vdists[i];
                
                if (dist < bestdist) {
                    bestdist = dist;
                    bestedge = i;
                }
            }
            int u = this->au[bestedge];
            int v = this->av[bestedge];
            this->use[bestedge] = true;
            int target = -1;
            if (aunion[u] != g) { target = aunion[u]; }
            if (aunion[v] != g) { target = aunion[v]; }
            if (target > -1) {
                for (int z = 0; z < this->N; ++z) {
                    if (aunion[z] == target) {
                        aunion[z] = g;
                        vuse[z] = true;
                    }
                }
            }
            
            aunion[u] = g;
            aunion[v] = g;
            vuse[u] = true;
            vuse[v] = true;
            
            loop -= 1;
            
            
            f = false;
            for (int i = 0; i < this->N; ++i) {
                if (aunion[i] != g) {
                    f = true;
                    break;
                }
            }
        }
        
        for (int i = 0; i < this->N; ++i) {
            if (aunion[i] != g) { pdebug(aunion[i]);}
        }
        int score = 0;
        for (int i = 0; i < this->M; ++i) {
            if (this->use[i]) { score += this->vmat[this->au[i]][this->av[i]]; }
        }
        
        return score;
    }
    
    
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    cout.flush();
    return 0;
}

