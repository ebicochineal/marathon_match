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
#include <time.h>
#include <sys/timeb.h>
#include <bitset>
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



inline bool insidexywh (const int x, const int y, const int w, const int h) {
    return (0 <= x && x < w && 0 <= y && y < h);
}
inline int distance (e512pos a, e512pos b) { return abs(a.x-b.x)+abs(a.y-b.y); }


class Random2optSwap {
public:
    int a, b;
    Random2optSwap (vector<e512pos>& v, int l, int r) {// left margin size   right margin size
        int t = max(((int)v.size() - l - r), 1);
        this->a = xrnd() % t + l;
        this->b = xrnd() % t + l;
        if (this->a > this->b) { swap(this->a, this->b); }
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
    void cancel (vector<e512pos>& v) {
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
};
int sumscore (vector<e512pos>& v) {
    e512pos p = v[0];
    int score = 0;
    for (auto&& i : v) {
        score += distance(p, i);
        p = i;
    }
    return score;
    }

vector<e512pos> minimize_sa (vector<e512pos> v, double& refscore, int etime, double stemp = 256.0, double etemp = 0.0) {
    StopWatch sw;
    int stime = 0;
    const double satime = etime - stime;
    int ntime = stime;
    vector<e512pos> bestv = v;
    double bestscore = sumscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    int cnt = 0;
    while (true) {
        {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            Random2optSwap rs(v, 1, 51);
            double tmpscore = sumscore(v);
            const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                rs.cancel(v);
            }
            cnt += 1;
        }
        {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            Random2optSwap rs(v, 51, 1);
            double tmpscore = sumscore(v);
            const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                rs.cancel(v);
            }
            cnt += 1;
        }
    }
    refscore = bestscore;
    return bestv;
}

vector<e512pos> minimize_sa_fixedstep (vector<e512pos> v, double& refscore, int ecnt, double stemp = 256.0, double etemp = 0.0) {
    const double sacnt = ecnt;
    vector<e512pos> bestv = v;
    double bestscore = sumscore(v);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
        {
            Random2optSwap rs(v, 1, 51);
            double tmpscore = sumscore(v);
            const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                rs.cancel(v);
            }
        }
        {
            Random2optSwap rs(v, 51, 1);
            double tmpscore = sumscore(v);
            const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestv = v;
                }
            } else {
                rs.cancel(v);
            }
        }
        
        
    }
    refscore = bestscore;
    return bestv;
}
class MM {
public:
    StopWatch sw;
    
    int N = 1000;
    array<e512pos, 1000> S;
    array<e512pos, 1000> E;
    bitset<1000> bs;
    MM () { this->sw = StopWatch(); }
    void input () {
        for (int i = 0; i < 1000; ++i) {
            cin >> S[i].x >> S[i].y >> E[i].x >> E[i].y;
        }
    }
    vector<int> bestret1;
    vector<e512pos> bestret2;
    void output () {
        string s1 = to_string(this->bestret1.size());
        string s2 = to_string(this->bestret2.size());
        for (int i = 0; i < this->bestret1.size(); ++i) {
            s1 += " " + to_string(this->bestret1[i]+1);
        }
        for (int i = 0; i < this->bestret2.size(); ++i) {
            s2 += " " + to_string(this->bestret2[i].x) + " " + to_string(this->bestret2[i].y);
        }
        cout << s1 << endl;
        cout << s2 << endl;
    }
    void solve0 (vector<int>& bestret1, vector<e512pos>& bestret2, double n) {
        vector<int> ret1;
        vector<e512pos> ret2;
        ret2.emplace_back(400, 400);
        unordered_set<int> e;
        unordered_set<int> s;
        for (int i = 0; i < 1000; ++i) {
            if (xrnd()%8>0) { s.emplace(i); }
        }
        
        for (int i = 0; i < 1000; ++i) {
            if (s.size() > 800) { break; }
            s.emplace(i);
        }
        double m = 1.0 + (xrnd()%11)*0.1;
        int ecnt = 0;
        int scnt = 0;
        
        e512pos o;
        o.x = (xrnd()%401-200);
        o.y = (xrnd()%401-200);
        while (scnt < 50) {
            int best = -1;
            int bestdist = 1000000;
            e512pos p = ret2.back();
            int t = -1;
            if (scnt < 50) {
                for (auto&& i : s) {
                    int dist = distance(p, this->S[i])+distance(e512pos(400, 400)+o, this->E[i]) * n;
                    if (dist < bestdist) {
                        bestdist = dist;
                        best = i;
                        t = 0;
                    }
                }
            }
            if (t == 0) {
                scnt += 1;
                e.emplace(best);
                s.erase(best);
                ret1.emplace_back(best);
                ret2.emplace_back(this->S[best]);
            }
            if (t == 1) {
                ecnt += 1;
                e.erase(best);
                ret2.emplace_back(this->E[best]);
            }
        }
        while (ecnt < 50) {
            int best = -1;
            int bestdist = 1000000;
            e512pos p = ret2.back();
            int t = -1;
            for (auto&& i : e) {
                int dist = distance(p, this->E[i]);
                if (dist < bestdist) {
                    bestdist = dist;
                    best = i;
                    t = 1;
                }
            }
            
            if (t == 0) {
                scnt += 1;
                e.emplace(best);
                s.erase(best);
                ret1.emplace_back(best);
                ret2.emplace_back(this->S[best]);
            }
            if (t == 1) {
                ecnt += 1;
                e.erase(best);
                ret2.emplace_back(this->E[best]);
            }
            
        }
        ret2.emplace_back(400, 400);
        bestret1 = ret1;
        bestret2 = ret2;
    }
    
    
    
    void solve () {
        this->solve0(this->bestret1, this->bestret2, 0);
        double bestscore = sumscore(bestret2);
        while (this->sw.get_milli_time() < 1600) {
            for (int i = 0; i < 8; ++i) {
                vector<int> ret1;
                vector<e512pos> ret2;
                this->solve0(ret1, ret2, i*0.025);
                double score = sumscore(ret2);
                //ret2 = minimize_sa_fixedstep(ret2, score, 51260, 32, 0);
                if (score < bestscore) {
                    bestscore = score;
                    this->bestret1 = ret1;
                    this->bestret2 = ret2;
                }
            }
        }
        this->bestret2 = minimize_sa(this->bestret2, bestscore, 1940-this->sw.get_milli_time(), 32, 0);
        
        pdebug(this->sw.get_milli_time());
        
    }
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    
    return 0;
}

