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
#include <random>
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

struct mmstate {
public:
    int N = 8;
    int maximum = 0;
    int score = 0;
    array< array<int, 48>, 48 > grid;
    vector<e512pos> out;
    mmstate (int N, array< array<int, 48>, 48 >& grid) {
        this->N = N;
        this->grid = grid;
    }
    
    bool tryput (int px, int py) {
        if (this->grid[py][px] > 0) { return false; }
        int p = 0;
        int cnt = 0;
        for (int y = py-1; y < py+2; ++y) {
            for (int x = px-1; x < px+2; ++x) {
                int t = this->grid[y][x] & 0xFFFF;
                p += t;
                cnt += t > 0;
            }
        }
        if  (p == 0) {
            this->grid[py][px] = 1;
            this->maximum = max(1, this->maximum);
            this->out.emplace_back(px, py);
            this->score += 1;
            return true;
        } else if (cnt > 1 && p <= this->maximum + 1) {
            this->grid[py][px] = p;
            this->maximum = max(p, this->maximum);
            this->out.emplace_back(px, py);
            this->score += p;
            return true;
        } else {
            return false;
        }
    }
    
    bool tryput2 (int px, int py) {
        if (this->grid[py][px] > 0) { return false; }
        int p = 0;
        int cnt = 0;
        for (int y = py-1; y < py+2; ++y) {
            for (int x = px-1; x < px+2; ++x) {
                int t = this->grid[y][x] & 0xFFFF;
                p += t;
                cnt += t > 0;
            }
        }
        if  (p == 0) {
            this->grid[py][px] = 1;
            this->maximum = max(1, this->maximum);
            // this->out.emplace_back(px, py);
            this->score += 1;
            return true;
        } else if (cnt > 1 && p <= this->maximum + 1) {
            this->grid[py][px] = p;
            this->maximum = max(p, this->maximum);
            // this->out.emplace_back(px, py);
            this->score += p;
            return true;
        } else {
            return false;
        }
    }
    
    int vputpoint (int px, int py) {
        if (this->grid[py][px] > 0) { return 0; }
        int p = 0;
        int cnt = 0;
        for (int y = py-1; y < py+2; ++y) {
            for (int x = px-1; x < px+2; ++x) {
                int t = this->grid[y][x] & 0xFFFF;
                p += t;
                cnt += t > 0;
            }
        }
        if  (p == 0) {
            return 1;
        } else if (cnt > 1 && p <= this->maximum + 1) {
            return p;
        } else {
            return 0;
        }
    }
};



class MM {
public:
    StopWatch sw;
    int N;
    int M = 2;
    array< array<int, 48>, 48 > igrid;
    
    vector<e512pos> bestout;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N;
        for (int row = 0; row < 48; row++) {
            for (int col = 0; col < 48; col++) {
                this->igrid[row][col] = 0;
            }
        }
        
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                char c;
                cin >> c;
                this->igrid[row+this->M][col+this->M] = c == '#' ? 1 << 16 : 0;
            }
        }
    }
    void output () {
        cout << this->bestout.size() << endl;
        for (auto&& i : this->bestout) { cout << print(i.y-this->M, i.x-this->M) << endl; }
    }
    
    
    
    vector<e512pos> maximize_sa (vector<e512pos> v, int s, int etime, double stemp = 256.0, double etemp = 0.0) {
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector<e512pos> bestv = v;
        double bestscore = this->calcscore(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        int cnt = 0;
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            int a1 = xrnd() % (v.size()-s) + s;
            int b1 = xrnd() % (v.size()-s) + s;
            int a2 = xrnd() % (v.size()-s) + s;
            int b2 = xrnd() % (v.size()-s) + s;
            int a3 = xrnd() % (v.size()-s) + s;
            int b3 = xrnd() % (v.size()-s) + s;
            swap(v[a1], v[b1]);
            swap(v[a2], v[b2]);
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
                swap(v[a2], v[b2]);
                swap(v[a1], v[b1]);
            }
            cnt += 1;
        }
        
        return bestv;
    }
    
    
    
    
    int calcscore (vector<e512pos>& v) {
        static mmstate ms(this->N, this->igrid);
        ms.score = 0;
        ms.maximum = 0;
        ms.grid = this->igrid;
        ms.out.clear();
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        return ms.score;
    }
    vector<e512pos> calcout (vector<e512pos>& v) {
        static mmstate ms(this->N, this->igrid);
        ms.score = 0;
        ms.maximum = 0;
        ms.grid = this->igrid;
        ms.out.clear();
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        pdebug(ms.maximum);
        return ms.out;
    }
    mmstate calcmmstate (vector<e512pos>& v) {
        mmstate ms(this->N, this->igrid);
        ms.score = 0;
        ms.maximum = 0;
        ms.grid = this->igrid;
        ms.out.clear();
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        for (auto&& i : v) { ms.tryput(i.x, i.y); }
        return ms;
    }
    
    void solve () {
        mmstate bestms(this->N, this->igrid);
        
        
        
        mmstate ams = dfs();
        
        
        vector<e512pos> v = ams.out;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->igrid[y+this->M][x+this->M] == 0) {
                    v.emplace_back(x+this->M, y+this->M);
                }
            }
        }
        v = this->maximize_sa(v, 0, max(5000-(int)this->sw.get_milli_time(), 0), 2);
        mmstate bms = this->calcmmstate(v);
        v = bms.out;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->igrid[y+this->M][x+this->M] == 0) {
                    v.emplace_back(x+this->M, y+this->M);
                }
            }
        }
        v = this->maximize_sa(v, 0, max(8800-(int)this->sw.get_milli_time(), 0), 2);
        
        bms = this->calcmmstate(v);
        v = bms.out;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (this->igrid[y+this->M][x+this->M] == 0) {
                    v.emplace_back(x+this->M, y+this->M);
                }
            }
        }
        v = this->maximize_sa(v, 0, max(9800-(int)this->sw.get_milli_time(), 0), 2);
        
        bms = this->calcmmstate(v);
        
        
        
        int c = max(ams.maximum, bms.maximum);
        this->bestout = bms.out;
        pdebug(this->sw.get_milli_time(), c);
    }
    
    
    mmstate dfs () {
        mmstate best(this->N, this->igrid);
        
        for (int y = 1; y < this->N; y+=3) {
            for (int x = 1; x < this->N; x+=3) {
                best.tryput(x+this->M, y+this->M);
            }
        }
        
        
        vector<mmstate> q;
        q.emplace_back(best);
        
        vector< pair<int, e512pos> > maxv;
        int cnt = 0;
        while (q.size() > 0 && this->sw.get_milli_time() < 2000) {
            cnt += 1;
            mmstate t = q.back();
            q.pop_back();
            maxv.clear();
            if (t.score > best.score) { best = t; }
            
            
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    int point = t.vputpoint(x+this->M, y+this->M);
                    if (point > 0) { maxv.emplace_back(point, e512pos(x+this->M, y+this->M)); }
                }
            }
            if (maxv.size() == 0) { continue; }
            sort(maxv.begin(), maxv.end(), [](const pair<int, e512pos>& a, const pair<int, e512pos>& b) { return a.first > b.first; });
            
            int bestpoint = maxv[0].first;
            for (auto&& i : maxv) {
                if (i.first < bestpoint) { break; }
                mmstate tt = t;
                tt.tryput(i.second.x, i.second.y);
                q.emplace_back(tt);
                if (cnt > 2) { break; }
            }
            
            
        }
        
        
        return best;
    }
    
    
    
    
};







int main() {
    
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    cout.flush();
    
    
    return 0;
}
