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

class RectXYR {
public:
    int x, y, z;
    int l = -1;
    int r = -1;
    int u = -1;
    int d = -1;
    RectXYR () {}
    RectXYR (int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    RectXYR (int x, int y, int z, int l, int r, int u, int d) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->l = l;
        this->r = r;
        this->u = u;
        this->d = d;
    }
    
    int area () {
        return (this->r-this->l) * (this->d -this->u);
    }
    
};

class MM {
public:
    StopWatch sw;
    int N;
    int SD;
    vector<RectXYR> rects;
    MM () {
        this->sw = StopWatch();
        this->input();
        
        this->rects = this->SA0(4400, 4800, 40, this->rects, 0.5, 1);
        this->rects = this->SA34(4960-this->sw.get_milli_time(), this->rects);
        pdebug(this->sw.get_milli_time());
        this->output();
    }
    
    
    vector<RectXYR> SA0 (int limit, int limit2, int limit3, vector<RectXYR> ret, float v1, float v2) {
        StopWatch sw;
        
        vector<RectXYR> bestret = ret;
        double bestscore = this->all_score(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        vector<RectXYR> tret;
        int cnt = 0;
        int lcnt = 0;
        const double startTemp   = 1.0 / this->N * 0.04;
        const double endTemp     = 0.0;
        
        vector< pair< int, vector<RectXYR> > > bests;
        bests.emplace_back(bestscore, bestret);
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            
            {
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double v = v1 + (v2 - v1) * t / T;
                tret = ret;
                int x = xrnd()%this->N;
                vector<int> vv;
                vv.emplace_back(x);
                auto vvv = this->testindex(ret, x);
                
                for (auto&& i : vvv) {
                    vv.emplace_back(i);
                    if (xrnd()%2==0) { continue; }
                }
                int m = 2-vv.size();
                for (int i = 0; i < m; ++i) {
                    vv.emplace_back(xrnd()%this->N);
                }
                for (auto&& i : vv) {
                    ret[i].l = ret[i].x;
                    ret[i].r = ret[i].x+1;
                    ret[i].u = ret[i].y;
                    ret[i].d = ret[i].y+1;
                }
                
                for (auto&& i : vv) {
                    for (int k = 0; k < 8; ++k) {
                        if (ret[i].z > 400000) {
                            this->expand_v_i(ret, 2000, 1, v, i);
                            this->expand_v_i(ret, 800, 1, v, i);
                            this->expand_v_i(ret, 400, 1, v, i);
                            this->expand_v_i(ret, 200, 2, v, i);
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        } else if (ret[i].z > 200000) {
                            this->expand_v_i(ret, 2000, 1, v, i);
                            this->expand_v_i(ret, 800, 1, v, i);
                            this->expand_v_i(ret, 400, 1, v, i);
                            this->expand_v_i(ret, 200, 2, v, i);
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        }  else if (ret[i].z > 100000) {
                            this->expand_v_i(ret, 2000, 1, v, i);
                            this->expand_v_i(ret, 400, 1, v, i);
                            this->expand_v_i(ret, 200, 1, v, i);
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        } else if (ret[i].z > 50000) {
                            this->expand_v_i(ret, 2000, 1, v, i);
                            this->expand_v_i(ret, 200, 1, v, i);
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        } else if (ret[i].z > 25000) {
                            this->expand_v_i(ret, 200, 1, v, i);
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        } else {
                            this->expand_v_i(ret, 100, 2, v, i);
                            this->expand_v_i(ret, 50, 2, v, i);
                            this->expand_v_i(ret, 10, 2, v, i);
                            this->expand_v_i(ret, 5, 2, v, i);
                            this->expand_v_i(ret, 1, 2, v, i);
                        }
                    }
                }
                
                double tmpscore = this->all_score(ret);
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        cnt = 0;
                        if (bests.size() > 32) {
                            sort(bests.begin(), bests.end(), [](const pair< int, vector<RectXYR> >& a, const pair< int, vector<RectXYR> >& b) { return a.first > b.first; });
                            bests[bests.size()-1] = pair< int, vector<RectXYR> >(bestscore, bestret);
                        } else {
                            bests.emplace_back(bestscore, bestret);
                        }
                    }
                } else {
                    ret = tret;
                }
                
                cnt += 1;
                if (cnt > 100) {
                    // ret = bestret;
                    // cnt = 0;
                }
                lcnt += 1;
            }
            
        }
        pdebug(lcnt);
        
        sort(bests.begin(), bests.end(), [](const pair< int, vector<RectXYR> >& a, const pair< int, vector<RectXYR> >& b) { return a.first > b.first; });
        bestret = this->SA34(limit3, bestret);
        bestscore = this->all_score(bestret);
        while (sw.get_milli_time() < limit2) {
            ret = this->SA34(limit3, bests[xrnd()%bests.size()].second);
            double tscore = this->all_score(ret);
            if (tscore > bestscore) {
                bestret = ret;
                bestscore = tscore;
            }
        }
        
        return bestret;
    }
    
    vector<RectXYR> SA34 (int limit, vector<RectXYR> ret) {
        StopWatch sw;
        
        vector<RectXYR> bestret = ret;
        double bestscore = this->all_score(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        vector<RectXYR> tret;
        int cnt = 0;
        int lcnt = 0;
        const double startTemp   = 1.0 / this->N * 0.0001;
        const double endTemp     = 0.0;
        
        // pdebug("s", bestscore);
        
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            int x = xrnd() % this->N;
            for (int h = 0; h < 4; ++h) {
                
                tret = ret;
                
                int y = xrnd() % 4;
                int z = xrnd() % 40;
                int ll = xrnd()%2==0 ? z : 0;
                int rr = xrnd()%2==0 ? z : 0;
                int uu = xrnd()%2==0 ? z : 0;
                int dd = xrnd()%2==0 ? z : 0;
                if (this->expand_forced1(ret, x, ll, rr, uu, dd) == false) {
                    ret = tret;
                    continue;
                }
                
                double tmpscore = this->all_score(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                        cnt = 0;
                    }
                } else {
                    ret = tret;
                }
                
                cnt += 1;
                // if (cnt > 5126) {
                //     ret = bestret;
                //     cnt = 0;
                // }
                lcnt += 1;
            }
            // 42
            auto vv = this->testindex(ret, x);
            for (auto&& xx : vv) {
                for (int h = 0; h < 4; ++h) {
                    tret = ret;
                    
                    int y = xrnd() % 4;
                    int z = xrnd() % 40;
                    int ll = xrnd()%2==0 ? z : 0;
                    int rr = xrnd()%2==0 ? z : 0;
                    int uu = xrnd()%2==0 ? z : 0;
                    int dd = xrnd()%2==0 ? z : 0;
                    if (this->expand_forced1(ret, xx, ll, rr, uu, dd) == false) {
                        ret = tret;
                        continue;
                    }
                    
                    double tmpscore = this->all_score(ret);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((tmpscore - lastscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore > lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        if (tmpscore > bestscore) {
                            bestscore = tmpscore;
                            bestret = ret;
                            cnt = 0;
                        }
                    } else {
                        ret = tret;
                    }
                    
                    cnt += 1;
                    // if (cnt > 5126) {
                    //     ret = bestret;
                    //     cnt = 0;
                    // }
                    lcnt += 1;
                }
            }
            
        }
        // pdebug("e", bestscore);
        // pdebug(lcnt);
        return bestret;
    }
    
    
    bool expand_forced1 (vector<RectXYR>& rects, int t, int l, int r, int u, int d) {
        RectXYR rect = rects[t];
        rect.l -= l;
        rect.r += r;
        rect.u -= u;
        rect.d += d;
        if (rect.l < 0) { return false; }
        if (rect.r > 10000) { return false; }
        if (rect.u < 0) { return false; }
        if (rect.d > 10000) { return false; }
        
        // other point inside rect
        for (int i = 0; i < this->N; ++i) {
            if (i == t) { continue; }
            const int x = rects[i].x;
            const int y = rects[i].y;
            if (rect.l <= x && x <= rect.r && rect.u <= y && y <= rect.d) { return false; }
        }
        rects[t].l -= l;
        rects[t].r += r;
        rects[t].u -= u;
        rects[t].d += d;
        
        for (int i = 0; i < this->N; ++i) {
            if (i == t) { continue; }
            if (this->aabb1(rect, rects[i])) {
                int x = -1;
                double tscore = 0;
                double bestscore = 0;
                rects[i].l += r;
                tscore = this->score(rects[i]);
                if (tscore > bestscore && !this->aabb1(rects[i], rect)) {
                    bestscore = tscore;
                    x = 0;
                }
                rects[i].l -= r;
                
                rects[i].r -= l;
                tscore = this->score(rects[i]);
                if (tscore > bestscore && !this->aabb1(rects[i], rect)) {
                    bestscore = tscore;
                    x = 1;
                }
                rects[i].r += l;
                
                rects[i].u += d;
                tscore = this->score(rects[i]);
                if (tscore > bestscore && !this->aabb1(rects[i], rect)) {
                    bestscore = tscore;
                    x = 2;
                }
                rects[i].u -= d;
                
                rects[i].d -= u;
                tscore = this->score(rects[i]);
                if (tscore > bestscore && !this->aabb1(rects[i], rect)) {
                    bestscore = tscore;
                    x = 3;
                }
                rects[i].d += u;
                
                if (x == 0) { rects[i].l += r; }
                else if (x == 1) { rects[i].r -= l; }
                else if (x == 2) { rects[i].u += d; }
                else if (x == 3) { rects[i].d -= u; }
                else { return false; }
            }
        }
        return true;
    }
    
    
    
    void expand_v_i (vector<RectXYR>& rects, int w, int loop, float v, int i) {
        RectXYR& r = rects[i];
        const int t = r.z*v;
        bool lr = (r.r-r.l+w) * (r.d-r.u) > t;
        bool ud = (r.r-r.l) * (r.d-r.u+w) > t;
        
        const int s = 0 + w;
        const int e = 10000 - w;
        for (int j = 0; j < loop; ++j) {
            if (lr && ud) { break; }
            int x = xrnd() % 4;
            const int t = r.z*v;
            
            if (x == 0 && r.l >= s && lr == false) {
                r.l -= w;
                if (this->test(rects, i)) {
                    r.l += w;
                } else {
                    if ((r.r-r.l+w) * (r.d-r.u) > t) { lr = true; }
                    if ((r.r-r.l) * (r.d-r.u+w) > t) { ud = true; }
                }
            } else if (x == 1 && r.r <= e && lr == false) {
                r.r += w;
                if (this->test(rects, i)) {
                    r.r -= w;
                } else {
                    if ((r.r-r.l+w) * (r.d-r.u) > t) { lr = true; }
                    if ((r.r-r.l) * (r.d-r.u+w) > t) { ud = true; }
                }
            } else if (x == 2 && r.u >= s && ud == false) {
                r.u -= w;
                if (this->test(rects, i)) {
                    r.u += w;
                } else {
                    if ((r.r-r.l+w) * (r.d-r.u) > t) { lr = true; }
                    if ((r.r-r.l) * (r.d-r.u+w) > t) { ud = true; }
                }
            } else if (x == 3 && r.d <= e && ud == false) {
                r.d += w;
                if (this->test(rects, i)) {
                    r.d -= w;
                } else {
                    if ((r.r-r.l+w) * (r.d-r.u) > t) { lr = true; }
                    if ((r.r-r.l) * (r.d-r.u+w) > t) { ud = true; }
                }
            }
        }
    }
    
    bool test (vector<RectXYR>& rects, int t) {
        for (int i = 0; i < this->N; ++i) {
            if (i != t && this->aabb1(rects[t], rects[i])) { return true; }
        }
        return false;
    }
    
    vector<int> testindex (vector<RectXYR>& rects, int t) {
        RectXYR trect = rects[t];
        trect.l = max(trect.l-1, 0);
        trect.r = min(trect.r+1, 10000);
        trect.u = max(trect.u-1, 0);
        trect.d = min(trect.d+1, 10000);
        
        vector<int> r;
        for (int i = 0; i < this->N; ++i) {
            if (i != t && this->aabb1(trect, rects[i])) { r.emplace_back(i); }
        }
        return r;
    }
    
    
    void input () {
        cin >> this->N;
        pdebug(this->N);
        this->SD = 1000000000/this->N;
        for (int i = 0; i < this->N; ++i) {
            RectXYR r;
            cin >> r.x >> r.y >> r.z;
            r.l = r.x;
            r.r = r.x+1;
            r.u = r.y;
            r.d = r.y+1;
            this->rects.emplace_back(r);
        }
    }
    
    void output () {
        for (auto&& i : this->rects) {
            cout << print(i.l, i.u, i.r, i.d) << endl;
        }
    }
    
    double all_score (vector<RectXYR>& rects) {
        double r = 0;
        for (auto&& i : rects) { r += this->score(i); }
        return (double)(r / this->N);
    }
    double score (RectXYR& r) {
        if (r.x < r.l || r.x >= r.r || r.y < r.u || r.y >= r.d) { return 0; }
        int s = r.area();
        double t = (1.0 - (double)min(r.z, s)/(double)max(r.z, s));
        return 1.0 - (t*t);
    }
    double score (int x, int y, int sx, int sy, int ex, int ey, int r) {
        if (x < sx || x > ex || y < sy || y > ey) { return 0; }
        int s = abs(sx-ex) * abs(sy-ey);
        double t = (1.0 - (double)min(r, s)/(double)max(r, s));
        return 1.0 - (t*t);
    }
    
    bool aabb1 (RectXYR& r1, RectXYR& r2) {
        return min(r1.r, r2.r) > max(r1.l, r2.l) && min(r1.d, r2.d) > max(r1.u, r2.u);
    }
    bool aabb2 (RectXYR& r1, RectXYR& r2) {
        if (r1.l >= r2.r) { return false; }
        if (r2.l >= r1.r) { return false; }
        if (r1.u >= r2.d) { return false; }
        if (r2.u >= r1.d) { return false; }
        return true;
    }
    
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM();
    
    return 0;
}


