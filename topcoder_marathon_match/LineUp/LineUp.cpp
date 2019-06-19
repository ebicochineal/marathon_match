// C++11
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
#include <random>
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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
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

class LineUp {
public:
    StopWatch sw;
    vector<int> heights;
    vector<int> arrangements;
    int n;
    int x;
    int cnt = 0;
    vector<int> getLineup(vector<int> heights, vector<int> arrangements) {
        this->sw = StopWatch();
        this->heights = heights;
        this->arrangements = arrangements;
        this->n = heights.size();
        this->x = arrangements.size() / this->n;
        
        vector<int> ret(arrangements.size(), -1);
        for (int i = 0; i < arrangements.size(); i++) {
            ret[i] = i % heights.size();
        }
        // ret = this->SA0(1000, ret, 2.5, 0.0);
        ret = this->SA(4000, ret, 2.5, 1.0, 16);
        ret = this->SA(2500, ret, 1.2, 0.5, 10);
        ret = this->SA(2500, ret, 1.2, 0.5, 10);
        ret = this->SA(700, ret, 0.5, 0.0, 8);
        
        pdebug(this->sw.get_milli_time(), this->cnt, this->allScore(ret));
        return ret;
    }
    
    
    vector<int> HC (int limit, vector<int> ret) {
        StopWatch sw;
        float bestscore = this->initScore(ret);
        while (sw.get_milli_time() < limit) {
            for (int z = 0; z < 512; ++z) {
                int c = xrnd()%(this->x);
                int a = xrnd()%this->n+this->n*c;
                int b = xrnd()%this->n+this->n*c;
                float tmpscore = this->swapScore(ret, a, b, c);
               
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    this->updateSwap(ret, a, b, c);
                }
            }
        }
        return ret;
    }
    
    vector<int> SA (int limit, vector<int> ret, const float startTemp, const float endTemp, int o) {
        StopWatch sw;
        
        vector<int> bestret = ret;
        float bestscore = this->initScore(ret);
        float lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            const float T = saTimeEnd-saTimeStart;
            const float t = saTimeCurrent-saTimeStart;
            const float temp = startTemp + (endTemp - startTemp) * t / T;
            for (int i = 0; i < this->x; ++i) {
                for (int j = 0; j < this->n-1; ++j) {
                    const int a = j+this->n*i;
                    const int p = min(j + o, this->n);
                    for (int k = j+1; k < p; ++k) {
                        const int b = k+this->n*i;
                        const float tmpscore = this->swapScore(ret, a, b, i);
                        
                        //float probability = exp((tmpscore - lastscore) / temp);// max
                        const float probability = exp((lastscore - tmpscore) / temp);//min
                        const bool FORCE_NEXT = probability > (float)(xrnd() % R) / R;
                        
                        if (tmpscore < lastscore || FORCE_NEXT) {
                            lastscore = tmpscore;
                            this->updateSwap(ret, a, b, i);
                            if (tmpscore < bestscore) {
                                bestscore = tmpscore;
                                bestret = ret;
                            }
                        }
                        this->cnt += 1;
                    }
                }
                
            }
            
        }
        // pdebug(cnt);
        return bestret;
    }
    
    vector<int> tlastPosition;
    int64_t tmovement = 0;
    int64_t tsqErr = 0;
    int64_t stmovement = 0;
    int64_t stsqErr = 0;
    inline float initScore (vector<int>& ret) {
        this->tlastPosition = vector<int>((this->x+2)*this->n, 0);
        int64_t movement = 0;
        int64_t sqErr = 0;
        for (int i = 0; i < this->n; i++) { this->tlastPosition[i] = i; }
        for (int i = 0; i < this->x*this->n; i++) {
            const int c = i / this->n;
            const int64_t err = this->heights[ret[i]] - this->arrangements[i];
            sqErr += err * err;
            movement += abs((i % this->n) - this->tlastPosition[c*this->n+ret[i]]);
            this->tlastPosition[ret[i]+(c+1)*this->n] = i % this->n;
        }
        this->tmovement = movement;
        this->tsqErr = sqErr;
        this->stmovement = movement;
        this->stsqErr = sqErr;
        return movement + sqrt(sqErr);
    }
    
    inline float swapScore (const vector<int>& ret, const int a, const int b, const int c) {
        this->stmovement = this->tmovement;
        this->stsqErr = this->tsqErr;
        
        const int a0 = this->tlastPosition[ret[a]+this->n*(c)];
        const int a1 = this->tlastPosition[ret[a]+this->n*(c+1)];
        const int a2 = this->tlastPosition[ret[a]+this->n*(c+2)];
        const int b0 = this->tlastPosition[ret[b]+this->n*(c)];
        const int b1 = this->tlastPosition[ret[b]+this->n*(c+1)];
        const int b2 = this->tlastPosition[ret[b]+this->n*(c+2)];
        this->stmovement -= abs(a0 - a1) + abs(a1 - a2);
        this->stmovement -= abs(b0 - b1) + abs(b1 - b2);
        this->stmovement += abs(a0 - b1) + abs(b1 - a2);
        this->stmovement += abs(b0 - a1) + abs(a1 - b2);
        
        const int ha = this->heights[ret[a]];
        const int hb = this->heights[ret[b]];
        const int aa = this->arrangements[a];
        const int bb = this->arrangements[b];
        this->stsqErr -= (ha-aa)*(ha-aa)+(hb-bb)*(hb-bb);
        this->stsqErr += (ha-bb)*(ha-bb)+(hb-aa)*(hb-aa);
        
        return this->stmovement + sqrt(this->stsqErr);
    }
    
    inline void updateSwap (vector<int>& ret, const int a, const int b, const int c) {
        this->tmovement = this->stmovement;
        this->tsqErr = this->stsqErr;
        swap(ret[a], ret[b]);
        
        swap(this->tlastPosition[ret[a]+this->n*(c+1)], this->tlastPosition[ret[b]+this->n*(c+1)]);
    }
    
    inline float allScore (vector<int>& ret) {
        static vector<int> lastPosition(n, 0);
        int64_t movement = 0;
        int64_t sqErr = 0;
        for (int i = 0; i < this->n; i++) { lastPosition[i] = i; }
        for (int i = 0; i < this->x*this->n; i++) {
            int64_t err = this->heights[ret[i]] - this->arrangements[i];
            sqErr += err * err;
            movement += abs((i % this->n) - lastPosition[ret[i]]);
            lastPosition[ret[i]] = i % this->n;
        }
        return movement + sqrt(sqErr);
    }
    
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    LineUp sol;
    int size;
    cin >> size;
    vector<int> heights(size);
    getVector(heights);
    cin >> size;
    vector<int> arrangements(size);
    getVector(arrangements);
    vector<int> ret = sol.getLineup(heights, arrangements);
    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++)
      cout << ret[i] << endl;
    cout.flush();
}
