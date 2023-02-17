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

struct MMGraph {
    int size = 4;
    vector< bitset<10> > mat;
    
    MMGraph () {}
    
    void set_graph (string s, int n) {
        this->size = n;
        this->mat.clear();
        
        for (int i = 0; i < n; ++i) { this->mat.emplace_back(bitset<10>()); }
        
        int p = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n-i-1; ++j) {
                this->mat[i][i+j+1] = s[p] == '1';
                this->mat[i+j+1][i] = s[p] == '1';
                p += 1;
            }
        }
    }
    
    
    string encode (int n, int m = 10) {
        this->size = m;
        this->mat.clear();
        
        for (int i = 0; i < this->size; ++i) { this->mat.emplace_back(bitset<10>()); }
        
        for (int i = 0; i < m-1; ++i) {
            this->mat[i][i+1] = true;
            this->mat[i+1][i] = true;
        }
        
        for (int i = 0; i < m-3; ++i) {
            if (((n >> i) & 0b0000001) > 0) {
                this->mat[0][i+2] = true;
                this->mat[i+2][0] = true;
            }
        }
        
        
        string s;
        for (int i = 0; i < this->size; ++i) {
            for (int j = 0; j < this->size-i-1; ++j) {
                s += this->mat[i][i+j+1] ? '1' : '0';
            }
        }
        return s;
    }
    
    int decode (int lm, int cnt) {
        this->maximize_sa_fixedstep(this->mat, cnt, 2, 0);
        return this->decode_num() % lm;
    }
    
    
    void debug_graph () {
        for (int y = 0; y < this->size; ++y) {
            string s;
            for (int x = 0; x < this->size; ++x) {
                if (x == y) {
                    s += '-';
                } else {
                    s += this->mat[y][x] ? '1' : '0';
                }
            }
            if (true) {
                cerr << s << endl;
            } else {
                pdebug(s);
            }
        }
    }
    
    int decode_num () {
        int r = 0;
        int t = 1;
        for (int i = 2; i < this->size; ++i) {
            if (this->mat[0][i]) { r += t; }
            t *= 2;
        }
        return r;
    }
    
    void maximize_sa_fixedstep (vector< bitset<10> > v, int ecnt, double stemp = 256.0, double etemp = 0.0) {
        const double sacnt = ecnt;
        vector< bitset<10> > bestv = v;
        double bestscore = this->calc_score(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
            int a = xrnd() % this->size;
            int b = xrnd() % this->size;
            this->swap(v, a, b);
            // int c = xrnd() % this->size;
            // int d = xrnd() % this->size;
            // this->swap(v, c, d);
            double tmpscore = this->calc_score(v);
            const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
            const double probability = exp((tmpscore - lastscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            
            if (tmpscore >= lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore > bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                    if (this->validity(v)) { break; }
                }
            } else {
                // this->swap(v, c, d);
                this->swap(v, a, b);
            }
        }
        this->mat = bestv;
    }
    
    void swap (vector< bitset<10> >& v, int a, int b) {
        bool t;
        for (int i = 0; i < this->size; ++i) {
            t = v[a][i];
            v[a][i] = v[b][i];
            v[b][i] = t;
        }
        for (int i = 0; i < this->size; ++i) {
            t = v[i][a];
            v[i][a] = v[i][b];
            v[i][b] = t;
        }
    }
    
    int calc_score (vector< bitset<10> >& v) {
        int score = 0;
        for (int i = 0; i < this->size-1; ++i) {
            if (v[i][i+1] == false) {
                score -= 1;
            } else {
                score += 1;
            }
        }
        for (int i = 2; i < this->size-1; ++i) {
            if (v[0][i] == true) { score += 1; }
        }
        for (int y = 1; y < this->size-2; ++y) {
            for (int x = 2+y; x < this->size; ++x) {
                if (v[y][x] == true) { score -= 2; }
            }
        }
        return score;
    }
    
    bool validity (vector< bitset<10> > v) {
        for (int i = 0; i < this->size-1; ++i) {
            if (v[i][i+1] == false) {
                return false;
            }
        }
        for (int y = 1; y < this->size-2; ++y) {
            for (int x = 2+y; x < this->size; ++x) {
                if (v[y][x] == true) { return false; }
            }
        }
        
        return true;
    }
    
};

struct MMGraph2 {
    int size = 4;
    vector< bitset<100> > mat;
    
    MMGraph2 () {}
    void set_graph (string s, int n) {
        this->size = n;
        this->mat.clear();
        
        for (int i = 0; i < n; ++i) { this->mat.emplace_back(bitset<100>()); }
        
        int p = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n-i-1; ++j) {
                this->mat[i][i+j+1] = s[p] == '1';
                this->mat[i+j+1][i] = s[p] == '1';
                p += 1;
            }
        }
    }
    
    
    string encode (int n, int m) {
        this->size = m;
        this->mat.clear();
        
        for (int i = 0; i < this->size; ++i) { this->mat.emplace_back(bitset<100>()); }
        
        
        if (n < m / 2) {
            for (int i = 0; i < n; ++i) {
                for (int j = 1+i; j < this->size; ++j) {
                    this->mat[i][j] = true;
                    this->mat[j][i] = true;
                }
            }
        } else {
            for (int y = 0; y < this->size; ++y) {
                for (int x = 0; x < this->size; ++x) {
                    this->mat[y][x] = true;
                    this->mat[x][y] = true;
                }
            }
            
            for (int i = 0; i < m-n; ++i) {
                for (int j = 1+i; j < this->size; ++j) {
                    this->mat[i][j] = false;
                    this->mat[j][i] = false;
                }
            }
        }
        
        
        
        
        string s;
        for (int i = 0; i < this->size; ++i) {
            for (int j = 0; j < this->size-i-1; ++j) {
                s += this->mat[i][i+j+1] ? '1' : '0';
            }
        }
        return s;
    }
    
    
    int decode (int lm, double eps) {
        int r = 0;
        int cmax = 0;
        int cmin = 100;
        vector<int> v;
        for (int i = 0; i < this->size; ++i) {
            int c = 0;
            for (int x = 0; x < this->size; ++x) {
                if (this->mat[i][x]) { c += 1; }
            }
            cmax = max(c, cmax);
            cmin = min(c, cmin);
            v.emplace_back(c);
        }
        
        for (int i = 0; i < this->size; ++i) {
            int c = 0;
            for (int x = 0; x < this->size; ++x) {
                if (this->mat[i][x]) { c += 1; }
            }
            if (abs(c-cmax) < abs(c-cmin)) { r += 1; }
        }
        
        sort(v.begin(), v.end(), [](const auto& a, const auto& b) { return a > b; });
        int r2 = 0;
        int bestscore = 0;
        for (int i = 0; i < this->size-1; ++i) {
            int score = abs(v[i]-v[i+1]);
            if (score > bestscore) {
                bestscore = score;
                r2 = i+1;
            }
            
        }
        if (abs(r-(lm/2)) < lm/6 || r == 0) {
            return min(r, lm-1);
        } else {
            return min(r2, lm-1);
        }
        
        
        
        
        
    }
    
    
};


struct MMGraph3 {
    int size = 4;
    
    vector< vector< bitset<100> > > mats;
    
    vector< bitset<100> > mat;
    
    MMGraph3 () {}
    void set_graph (string s, int n) {
        this->size = n;
        this->mat.clear();
        
        for (int i = 0; i < n; ++i) { this->mat.emplace_back(bitset<100>()); }
        
        int p = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n-i-1; ++j) {
                this->mat[i][i+j+1] = s[p] == '1';
                this->mat[i+j+1][i] = s[p] == '1';
                p += 1;
            }
        }
    }
    
    int nd (int n) { return n * (n-1) / 2; }
    
    int N;
    double eps;
    array<double, 100> simcnts;
    
    int vsize = 4;
    void init () {
        int z = 49;
        if (this->N < 36) { z = 49 * 2; }
        if (this->N < 31) { z = 49 * 2.5; }
        if (this->N < 26) { z = 49 * 3; }
        if (this->N < 21) { z = 49 * 3.5; }
        if (this->N < 16) { z = 49 * 4; }
        
        
        
        int s = this->N;
        while (this->nd(s) / this->N < z) { s += 1; }
        this->vsize = s;
    }
    
    void encodes (int N, double eps) {
        this->N = N;
        this->eps = eps;
        
        this->init();
        int vertcnt = this->nd(this->vsize);
        
        cout << this->vsize << endl;
        cout.flush();
        
        for (int i = 0; i < this->N; ++i) {
            int oc = vertcnt / this->N * i;
            string s;
            for (int j = 0; j < vertcnt; ++j) { s += j < oc ? '1' : '0'; }
            cout << s << endl;
            cout.flush();
            
            this->simcnts[i] = (vertcnt-oc) * eps + oc - oc * eps;
            // fdebug(this->simcnts[i]);
        }
    }
    
    
    int decode (string s) {
        int best = 0;
        double bestscore = 1000000;
        double cnt = 0;
        int v = this->nd(this->vsize);
        for (int i = 0; i < v; ++i) {
            if (s[i] == '1') { cnt += 1; }
        }
        
        for (int i = 0; i < this->N; ++i) {
            double score = abs(this->simcnts[i] - cnt);
            if (score < bestscore) {
                bestscore = score;
                best = i;
            }
        }
        return best;
    }
    
    
};



class MM {
public:
    StopWatch sw;
    MM () { this->sw = StopWatch(); }
    
    int N;
    double eps;
    
    int Z;
    void solve () {
        cin >> this->N >> this->eps;
        pdebug(this->N, this->eps);
        
        if (this->eps == 0.0 && this->N <= 22) {
            if (this->N <= 22) { this->Z = 7; }
            if (this->N <= 16) { this->Z = 6; }
            if (this->N <= 11) { this->Z = 5; }
            
            cout << this->Z << endl;
            
            for (int i = 0; i < this->N; ++i) {
                string s;
                for (int j = 0; j < i; ++j) { s += '1'; }
                for (int j = s.size(); j < (this->Z*(this->Z-1)/2); ++j) { s = '0' + s; }
                cout << s << endl;
                cout.flush();
            }
            for (int i = 0; i < 100; ++i) {
                string s;
                cin >> s;
                int c = 0;
                for (int j = 0; j < (this->Z*(this->Z-1)/2); ++j) { if (s[j] == '1') { c += 1; } }
                cout << c % this->N << endl;
                cout.flush();
            }
            
            
            pdebug(this->sw.get_milli_time());
            cerr.flush();
        } else if (this->eps <= 0.01) {
            MMGraph g;
            this->Z = 10;
            if (this->N <= 64) { this->Z = 9; }
            if (this->N <= 32) { this->Z = 8; }
            if (this->N <= 16) { this->Z = 7; }
            cout << this->Z << endl;
            for (int i = 0; i < this->N; ++i) {
                cout << g.encode(i, this->Z) << endl;
                cout.flush();
            }
            for (int i = 0; i < 100; ++i) {
                string s;
                cin >> s;
                g.set_graph(s, this->Z);
                
                if (this->sw.get_milli_time() < 4000) {
                    cout << g.decode(this->N, 51260*3) << endl;
                } else if (this->sw.get_milli_time() < 4600) {
                    cout << g.decode(this->N, 51260*2) << endl;
                } else {
                    cout << g.decode(this->N, 5126) << endl;
                }
                
                cout.flush();
            }
            pdebug(this->sw.get_milli_time());
            cerr.flush();
            
            
        } else if (this->N < 33 && this->eps > 0.14) {
            MMGraph3 g;
            g.encodes(this->N, this->eps);
            
            for (int i = 0; i < 100; ++i) {
                string s;
                cin >> s;
                cout << g.decode(s) << endl;
                cout.flush();
            }
            pdebug(this->sw.get_milli_time());
            cerr.flush();
        } else if (this->eps < 0.33 || (this->eps < 0.36 && this->N > 75)) {
            MMGraph2 g;
            this->Z = this->N;
            cout << this->Z << endl;
            for (int i = 0; i < this->N; ++i) {
                cout << g.encode(i, this->Z) << endl;
                cout.flush();
            }
            for (int i = 0; i < 100; ++i) {
                string s;
                cin >> s;
                g.set_graph(s, this->Z);
                cout << g.decode(this->N, this->eps) << endl;
                cout.flush();
            }
            pdebug(this->sw.get_milli_time());
            cerr.flush();
            
        } else {
            this->Z = 4;
            cout << this->Z << endl;
            
            for (int i = 0; i < this->N; ++i) {
                string s;
                int k = i % 7;
                for (int j = 0; j < k; ++j) { s += '1'; }
                for (int j = s.size(); j < 6; ++j) { s = '0' + s; }
                cout << s << endl;
                cout.flush();
            }
            for (int i = 0; i < 100; ++i) {
                string s;
                cin >> s;
                int c = 0;
                for (int j = 0; j < 6; ++j) { if (s[j] == '1') { c += 1; } }
                cout << c % this->N << endl;
                cout.flush();
            }
            
            
            
            pdebug(this->sw.get_milli_time());
            cerr.flush();
            
            
        }
        
        
    }
};

int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.solve();
    return 0;
}
