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
    #include <random>
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

void output (vector<int> v) {
    ostringstream out;
    for (auto&& i : v) { out << i << " "; }
    cout << out.str() << endl;
    cout.flush();
}


void solve2 (int N, int edges, vector< vector<int> >& g, vector<int>& ret, int& score, StopWatch& sw) {
    vector<int> v(N, -1);
    unordered_set<int> us;
    bitset<2085050> bvs;
    bitset<2085050> bes;
    int m = 0;
    
    
    vector<int> indexs;
    for(int i = 0; i < N; i++) { indexs.emplace_back(i); }
    
    // mt19937 mt(xrnd());
    // shuffle(indexs.begin(), indexs.end(), mt);
    sort(indexs.begin(), indexs.end(), [&g](const int& a, const int& b) { return g[a].size() > g[b].size(); });
    
    v[indexs[0]] = 0;
    bvs[0] = true;
    int cnt = 1;
    double d = 1.15;
    if (edges < 50000) { d = 1.30; }
    if (edges < 40000) { d = 1.35; }
    if (edges < 30000) { d = 1.40; }
    if (edges < 20000) { d = 1.45; }
    if (edges < 10000) { d = 1.50; }
    if (edges < 5000) {  d = 1.60; }
    for (int j = 1; j < 2085050; ++j) {
        if (j % 100 == 0) {
            if (sw.get_milli_time() > 4000) { d = 1.1; }
            if (sw.get_milli_time() > 8000) { d = 1.05; }
            if (sw.get_milli_time() > 9000) { break; }
        }
        if (bvs[j]) { continue; }
        if (cnt == N) { break;}
        int tcnt = 0;
        
        
        for (auto&& i : indexs) {
            if (tcnt > cnt * d) { break; }
            tcnt += 1;
            if (v[i] >= 0) { continue; }
            
            bool f = false;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (bes[j-v[k]]) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) { continue; }
            
            bvs[j] = true;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    bes[j-v[k]] = true;
                }
            }
            v[i] = j;
            m = j;
            cnt += 1;
            break;
        }
    }
    
    int s = m;
    for (auto&& i : indexs) {
        if (v[i] >= 0) { continue; }
        for (int j = m; j < 2085050; ++j) {
            if (bvs[j]) { continue; }
            bool f = false;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (bes[abs(j-v[k])]) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) { continue; }
            us.clear();
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (us.find(abs(j-v[k])) != us.end()) {
                        f = true;
                        break;
                    }
                    us.emplace(abs(j-v[k]));
                }
            }
            
            if (f) { continue; }
            bvs[j] = true;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    bes[abs(j-v[k])] = true;
                }
            }
            v[i] = j;
            m = max(m, j);
            break;
        }
        
    }
    
    
    ret = v;
    score = m;
}

void rndsolve3 (int N, int edges, vector< vector<int> >& g, vector<int>& ret, int& score, vector<int> indexs, StopWatch& sw, int etime) {
    vector<int> v(N, -1);
    static unordered_set<int> us;
    static bitset<2085050> bvs;
    static bitset<2085050> bes;
    
    us.clear();
    bvs.reset();
    bes.reset();
    
    int m = 0;
    
    double d = 1.15;
    if (edges < 50000) { d = 1.30; }
    if (edges < 40000) { d = 1.35; }
    if (edges < 30000) { d = 1.40; }
    if (edges < 20000) { d = 1.45; }
    if (edges < 10000) { d = 1.50; }
    if (edges < 5000) {  d = 1.60; }
    
    v[indexs[0]] = 0;
    bvs[0] = true;
    int cnt = 1;
    for (int j = 1; j < 2085050; ++j) {
        if (j % 100 == 0) {
            if (sw.get_milli_time() > etime) {
                score = 2085050;
                return;
            }
        }
        if (bvs[j]) { continue; }
        if (cnt == N) { break;}
        
        
        int tcnt = 0;
        for (auto&& i : indexs) {
            if (tcnt > cnt * d) { break; }
            tcnt += 1;
            if (v[i] >= 0) { continue; }
            
            bool f = false;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (bes[j-v[k]]) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) { continue; }
            
            bvs[j] = true;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    bes[j-v[k]] = true;
                }
            }
            v[i] = j;
            m = j;
            cnt += 1;
            break;
        }
    }
    
    ret = v;
    score = m;
}
void orndsolve4 (int N, int edges, vector< vector<int> >& g, vector<int>& ret, int& score, vector<int> indexs, StopWatch& sw) {
    vector<int> v(N, -1);
    unordered_set<int> us;
    bitset<2085050> bvs;
    bitset<2085050> bes;
    int m = 0;
    
    bool t = true;
    
    for (auto&& i : indexs) {
    
    // for (int z = 0; z < indexs.size(); ++z) {
    //     int i = indexs[z];
    //     if (i >= indexs.size()-5) { d = 0; }
        double d = 1.0-(xrnd()%11)*0.1;
        if (t) {
            bvs[0] = true;
            v[i] = 0;
            t = false;
            continue;
        }
        // for (int j = m; j < 2085050; ++j) {
        for (int j = m*d; j < 2085050; ++j) {
            if (bvs[j]) { continue; }
            bool f = false;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (bes[abs(j-v[k])]) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) { continue; }
            
            us.clear();
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (us.find(abs(j-v[k])) != us.end()) {
                        f = true;
                        break;
                    }
                    us.emplace(abs(j-v[k]));
                }
            }
            
            if (f) { continue; }
            bvs[j] = true;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    bes[abs(j-v[k])] = true;
                }
            }
            v[i] = j;
            m = max(m, j);
            break;
        }
        
        if (sw.get_milli_time() > 9500) {
            score = 2085050;
            return;
        }
        
    }
    
    ret = v;
    score = m;
}



void orndsolve3 (int N, int edges, vector< vector<int> >& g, vector<int>& ret, int& score, vector<int> indexs, StopWatch& sw, double d) {
    vector<int> v(N, -1);
    unordered_set<int> us;
    bitset<2085050> bvs;
    bitset<2085050> bes;
    int m = 0;
    
    bool t = true;
    
    for (auto&& i : indexs) {
    
    // for (int z = 0; z < indexs.size(); ++z) {
    //     int i = indexs[z];
    //     if (i >= indexs.size()-5) { d = 0; }
        // double d = 0.8;
        if (t) {
            bvs[0] = true;
            v[i] = 0;
            t = false;
            continue;
        }
        // for (int j = m; j < 2085050; ++j) {
        for (int j = m*d; j < 2085050; ++j) {
            if (bvs[j]) { continue; }
            bool f = false;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (bes[abs(j-v[k])]) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) { continue; }
            
            us.clear();
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    if (us.find(abs(j-v[k])) != us.end()) {
                        f = true;
                        break;
                    }
                    us.emplace(abs(j-v[k]));
                }
            }
            
            if (f) { continue; }
            bvs[j] = true;
            for (auto&& k : g[i]) {
                if (v[k] >= 0) {
                    bes[abs(j-v[k])] = true;
                }
            }
            v[i] = j;
            m = max(m, j);
            break;
        }
        
        if (sw.get_milli_time() > 9500) {
            score = 2085050;
            return;
        }
    }
    
    ret = v;
    score = m;
}

class Rev {
public:
    int a, b;
    Rev (vector<int>& v, int l, int r) {// left margin size   right margin size
        int t = max(((int)v.size() - l - r), 1);
        this->a = xrnd() % t + l;
        this->b = xrnd() % t + l;
        if (this->a > this->b) { swap(this->a, this->b); }
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
    void cancel (vector<int>& v) {
        reverse(v.begin()+this->a, v.begin()+this->b+1);
    }
};

vector<int> sa (vector<int> v, int edges, vector< vector<int> >& g, StopWatch& sw, double& refscore, int etime, double stemp = 256.0, double etemp = 0.0) {
    
    int stime = sw.get_milli_time();
    const double satime = etime - stime;
    int ntime = stime;
    vector<int> bestv = v;
    double bestscore = refscore;
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    int cnt = 0;
    
    vector<int> indexs;
    for(int i = 0; i < v.size(); i++) { indexs.emplace_back(i); }
    sort(indexs.begin(), indexs.end(), [&g](const int& a, const int& b) { return g[a].size() > g[b].size(); });
    
    while (true) {
        ntime = sw.get_milli_time();
        if (ntime >= etime) { break; }
        
        {
            int a = xrnd() % (v.size()/2);
            int b = xrnd() % (v.size()/2);
            swap(indexs[a], indexs[b]);
            
            int score;
            rndsolve3(v.size(), edges, g, v, score, indexs, sw, etime);
            
            
            double tmpscore = score;
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
                swap(indexs[a], indexs[b]);
            }
            cnt += 1;
        }
        {
            Rev rev(indexs, 0, v.size()/2);
            
            int score;
            rndsolve3(v.size(), edges, g, v, score, indexs, sw, etime);
            
            double tmpscore = score;
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
                rev.cancel(indexs);
            }
            cnt += 1;
        }
    }
    
    pdebug(cnt);
    
    refscore = bestscore;
    return bestv;
}


vector<int> osa (vector<int> v, int edges, vector< vector<int> >& g, StopWatch& sw, double& refscore, vector<int>& refindexs, int etime, double stemp = 256.0, double etemp = 0.0) {
    
    int stime = sw.get_milli_time();
    const double satime = etime - stime;
    int ntime = stime;
    vector<int> bestv = v;
    double bestscore = refscore;
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    int cnt = 0;
    
    vector<int> indexs = refindexs;
    
    while (true) {
        ntime = sw.get_milli_time();
        if (ntime >= etime) { break; }
        int a = xrnd() % v.size();
        int b = xrnd() % v.size();
        swap(indexs[a], indexs[b]);
        
        // Rev rev(indexs, 0, 0);
        
        
        int score;
        orndsolve3(v.size(), edges, g, v, score, indexs, sw, 0.7);
        
        
        double tmpscore = score;
        const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
        const double probability = exp((lastscore - tmpscore) / temp);
        const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
        if (tmpscore < lastscore || FORCE_NEXT) {
            lastscore = tmpscore;
            if (tmpscore < bestscore) {
                bestscore = tmpscore;
                bestv = v;
                refindexs = indexs;
            }
        } else {
            swap(indexs[a], indexs[b]);
            // rev.cancel(indexs);
        }
        cnt += 1;
    }
    
    pdebug(cnt);
    
    refscore = bestscore;
    return bestv;
}


int main() {
    int N;
    cin >> N;
    int edges;
    cin >> edges;
    StopWatch sw;
    vector<vector<bool> > graph(N,vector<bool>(N,false));
    
    vector< vector<int> > g(N, vector<int>());
    
    
    for(int i = 0; i < edges; i++) {
        int node1,node2;
        cin >> node1 >> node2;
        graph[node1][node2] = true;
        graph[node2][node1] = true;
        g[node1].emplace_back(node2);
        g[node2].emplace_back(node1);
    }
    int bestscore;
    vector<int> bestv;
    solve2(N, edges, g, bestv, bestscore, sw);
    pdebug("st", sw.get_milli_time());
    
    if (edges < 1500) {
        int cnt = 0;
        
        
        double refscorea = bestscore;
        double refscoreb = bestscore;
        vector<int> refva = bestv;
        vector<int> refvb = bestv;
        
        refva = sa(refva, edges, g, sw, refscorea, 2000, max(refscorea / 5126.0, 2.0), 0.0);
        
        
        vector<int> indexs;
        for(int i = 0; i < N; i++) { indexs.emplace_back(i); }
        sort(indexs.begin(), indexs.end(), [&g](const int& a, const int& b) { return g[a].size() > g[b].size(); });
        refvb = osa(refvb, edges, g, sw, refscoreb, indexs, 9000, max(refscorea / 5126.0, 2.0), 0.0);
        
        bestv = refscorea < refscoreb ? refva : refvb;
        bestscore = refscorea < refscoreb ? refscorea : refscoreb;
        
        while (sw.get_milli_time() < 9500) {
            int score;
            vector<int> v;
            orndsolve4(N, edges, g, v, score, indexs, sw);
            
            if (score < bestscore) {
                bestscore = score;
                bestv = v;
            }
            cnt += 1;
        }
        pdebug("##1");
    } else {
        int cnt = 0;
        double refscore = bestscore;
        bestv = sa(bestv, edges, g, sw, refscore, 9500, max(bestscore / 5126.0, 2.0), 0.0);
        bestscore = refscore;
        
        pdebug("##2");
    }
    
    
    pdebug(N, edges);
    tdebug(sw.get_milli_time());
    // pdebug(v);
    // pdebug(g);
    output(bestv);
    return 0;
}
