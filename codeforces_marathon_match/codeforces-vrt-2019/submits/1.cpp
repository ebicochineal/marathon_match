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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

struct work {
public:
    int x, y, d, p, l, h, c;
    work (int x, int y, int d, int p, int l, int h) {
        this->x = x;
        this->y = y;
        this->d = d;
        this->p = p;
        this->l = l;
        this->h = h;
        this->c = d * p * (p + 5);
    }
};

class MM {
public:
    StopWatch sw;
    int hx, hy;
    vector<work> works;
    
    vector< vector<int> > pworks;
    
    vector< vector<int> > workers;
    vector<bool> bworks;
    double score = 0;
    
    MM () {
        this->sw = StopWatch();
        this->init();
        
        
        bool b = true;
        
        vector<int> fwork(this->works.size(), 0);
        int c = 0;
        int p = 7;
        while (p > 0) {
            vector<int> path;
            
            int t = 0;
            int px = this->hx;
            int py = this->hy;
            
            while (1) {
                int bestc = -1;
                int best_w_index = -1;
                for (int j = 0; j < this->works.size(); ++j) {
                    work& w = this->works[j];
                    int wd = this->workdist(px, py, w);
                    int wst = wd + t;
                    int wet = max(wst, w.l) + w.d;
                    int pc = max(0, w.c - (wet - t));// / max(w.p, 1);
                    if (wet + this->homedist(w.x, w.y) <= 1000 && wst <= w.l && pc > bestc && p >= w.p && fwork[j] == 0 && w.p == p) {
                        bestc = w.c;
                        best_w_index = j;
                    }
                }
                if (bestc < 1) {
                    break;
                } else {
                    c += bestc;
                    path.emplace_back(best_w_index);
                    fwork[best_w_index] = 1;
                    work& w = this->works[best_w_index];
                    int wd = this->workdist(px, py, w);
                    int wst = wd + t;
                    int wet = max(wst, w.l) + w.d;
                    t = wet;
                    px = w.x;
                    py = w.y;
                }
                
                
                
            }
            
            
            
            if (path.size() < 1) {
                p -= 1;
                continue;
            }
            
            int credit = 0;
            for (auto&& i : path) { credit += this->works[i].c; }
            
            int st = 0;
            int et = 0;
            t = 0;
            px = this->hx;
            py = this->hy;
            for (int i = 0; i < path.size(); ++i) {
                work& w = this->works[path[i]];
                if (i == 0) {
                    t = w.l - this->workdist(px, py, w);
                    st = t;
                }
                t += this->workdist(px, py, w);
                t = max(t, w.l);
                t = t+w.d;
                px = w.x;
                py = w.y;
            }
            credit -= ((t + this->homedist(px, py)) - st + 240) * p;
            
            if (credit > 0) {
                for (int j = 0; j < p; ++j) {
                    this->workers.emplace_back(path);
                }
            } else {
                // for (auto&& i : path) { fwork[i] = 0; }
                // p -= 1;
            }
            
            
            
            
        }
        
        
        
        pdebug("T", this->sw.get_milli_time());
        pdebug("W", this->workers.size());
        // for (auto&& i : this->pworks) {
        //     pdebug(i.size());
        // }
        // FRet();
        Ret();
    }
    
    void Ret () {
        
        for (auto&& v : this->workers) {
            int t = 0;
            int px = this->hx;
            int py = this->hy;
            for (int i = 0; i < v.size(); ++i) {
                work& w = this->works[v[i]];
                
                if (i == 0) {
                    t = w.l - this->workdist(px, py, w);
                    cout << print("start", t, 1) << endl;
                }
                t += this->workdist(px, py, w);
                cout << print("arrive", t, v[i]+1) << endl;
                t = max(t, w.l);
                cout << print("work", t, t+w.d, v[i]+1) << endl;
                t = t+w.d;
                px = w.x;
                py = w.y;
            }
            t += this->homedist(px, py);
            cout << print("arrive", t, 1) << endl;
            cout << print("end") << endl;
        }
    }
    
    void FRet () {
        
        for (auto&& v : this->workers) {
            int t = 0;
            int px = this->hx;
            int py = this->hy;
            for (int i = 0; i < v.size(); ++i) {
                work& w = this->works[v[i]];
                
                if (i == 0) {
                    t = w.l - this->workdist(px, py, w);
                    fdebug("start", t, 1);
                }
                t += this->workdist(px, py, w);
                fdebug("arrive", t, v[i]);
                t = max(t, w.l);
                fdebug("work", t, t+w.d, v[i]);
                t = t+w.d;
                px = w.x;
                py = w.y;
            }
            t += this->homedist(px, py);
            fdebug("arrive", t, 1);
            fdebug("end");
        }
        
    }
    
    
    inline int workdist (int& px, int& py, work& w) {
        return abs(w.x - px) + abs(w.y - py);
    }
    inline int homedist (int& px, int& py) {
        return abs(px - this->hx) + abs(py - this->hy);
    }
    
    void init () {
        this->pworks = vector< vector<int> >(8);
        
        int n;
        cin >> n;
        int x, y, d, p, l, h;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y >> d >> p >> l >> h;
            if (i == 0) {
                this->hx = x;
                this->hy = y;
            }
            this->works.emplace_back(x, y, d, p, l, h);
            this->pworks[p].emplace_back(i);
        }
    }
    
    
    
    
    

    
private:
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    
    MM();
    
    return 0;
}