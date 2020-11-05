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
        size_t operator()(const e512pos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
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

class SoccerTournament {
public:
    StopWatch sw;
    int N, W, D, X;
    vector<int> scored, conceded, points;
    
    vector<int> isc, ico;
    
    int M = 0;
    int sum = 0;
    double G = 0;
    vector<string> findSolution(int N, int W, int D, int X,   vector<int> scored, vector<int> conceded, vector<int> points) {
        
        this->sw = StopWatch();
        this->N = N;
        this->W = W;
        this->D = D;
        this->X = X;
        this->scored = scored;
        this->conceded = conceded;
        this->points = points;
        
        for (int i = 0; i < this->N-1; ++i) {
            for (int j = i+1; j < this->N; ++j) { this->M += 1; }
        }
        for (auto&& i : this->scored) { this->sum += i; }
        this->G = (double)this->sum / (double)this->M;
        
        
        
        vector< pair<int, int> > va, vb;
        for (int i = 0; i < this->N; ++i) {
            va.emplace_back(this->scored[i], i);
            vb.emplace_back(this->conceded[i], i);
        }
        sort(va.begin(), va.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.first > b.first; });
        sort(vb.begin(), vb.end(), [](const pair<int, int>& a, const pair<int, int>& b) { return a.first > b.first; });
        this->isc = vector<int>(this->N, 0);
        this->ico = vector<int>(this->N, 0);
        for (int i = 0; i < this->N; ++i) {
            this->isc[va[i].second] = i;
            this->ico[vb[i].second] = i;
        }
        
        
        vector<string> results = this->output();
        pdebug(N, W, D, X, this->sw.get_milli_time());
        // pdebug(this->X);
        return results;
    }
    
    void getTeamScore1 (int a, int b, int& ts) {
        
        for (double i = 0.7; i <= 3; i+= 0.01) {
            ts = this->isc[a] < this->N/i && this->ico[b] < this->N/(3.0+0.7-i-0.5) ? 1 : ts;
        }
        for (double i = 0.4; i <= 1.6; i+= 0.01) {
            ts = this->scored[a] >= (this->N-1) * i && this->conceded[b] >= (this->N-1) * (1.5 + 0.4 - i) ? 1 : ts;
        }
    }
    
    void getTeamScore2 (int a, int b, int& ts) {
        for (double i = 1.0, j=0.2; i <= 2.0; i+= 0.01, j-=0.005) {
            ts = this->isc[a] < this->N/i && this->conceded[b] >= (this->N-1) * (2.3+1.0-i + (i < 1.5?j:0)) ? 2 : ts;
        }
        for (double i = 0.8, j=0.1; i <= 2.2; i+= 0.01, j-=0.0025) {
            ts = this->scored[a] >= (this->N-1) * i && this->conceded[b] >= (this->N-1) * (2.2 + 0.8 - i + (i < 1.2?j:0)) ? 2 : ts;
        }
        
        ts = this->isc[a] < this->N/1.3 && this->ico[b] < this->N/8 ? 2 :  ts;
        for (double i = 1.5; i <= 4.0; i+= 0.01) {
            ts = this->isc[a] < this->N/i && this->ico[b] < this->N/(4.0+1.5-i) && (this->conceded[b] >= (this->N-1) * 1.0 && this->scored[a] >= (this->N-1) * 1.0) ? 2 : ts;
        }
        ts = this->isc[a] < this->N/5 && this->ico[b] < this->N/1.4 ? 2 : ts;
        ts = this->isc[a] < this->N/6 && this->ico[b] < this->N/1.3 ? 2 : ts;
        
        
        
    }
    
    void getTeamScore3 (int a, int b, int& ts) {
        for (double i = 1.0; i <= 3.0; i+= 0.01) {
            ts = this->scored[a] >= (this->N-1) * i && this->conceded[b] >= (this->N-1) * (3.0 + 1.0 - i) ? 3 : ts;
        }
        for (double i = 2.1; i <= 2.8; i+= 0.01) {
            ts = this->scored[a] > (this->N-1) * i && this->ico[b] < this->N*(0.2 + i*0.04) ? 3 : ts;
        }
        for (double i = 2.0; i <= 6; i+= 0.01) {
            ts = this->isc[a] < this->N/i && this->scored[a] > (this->N-1) * (1.0+i*0.1) && this->conceded[b] >= (this->N-1) * (2.25-i*0.05) ? 3 : ts;
        }
    }
    
    
    vector<string> output () {
        vector< pair<int, int> > ret;
        
        for (int a = 0; a < this->N-1; ++a) {
            for (int b = a+1; b < this->N; ++b) {
                int ap = this->points[a] >= this->points[b] + (this->W) * ((this->N-1)*0.14) ? 2 : 1;
                int bp = this->points[b] >= this->points[a] + (this->W) * ((this->N-1)*0.14) ? 2 : 1;
                ap=0;
                bp=0;
                
                // 1
                this->getTeamScore1(a, b, ap);
                this->getTeamScore1(b, a, bp);
                
                // 2
                this->getTeamScore2(a, b, ap);
                this->getTeamScore2(b, a, bp);
                
                // 3
                this->getTeamScore3(a, b, ap);
                this->getTeamScore3(b, a, bp);
                
                //
                
                if (abs(this->points[a]-this->points[b]) < this->W*0.8 && abs(ap-bp) < 2) {
                    ap = (ap+bp+0.5) * 0.5;
                    bp = (ap+bp+0.5) * 0.5;
                }
                
                if (abs(this->isc[a]-this->isc[b]) < this->N*0.1 && abs(this->ico[a]-this->ico[b]) < this->N*0.1 && abs(ap-bp) < 2) {
                    ap = (ap+bp+0.5) * 0.5;
                    bp = (ap+bp+0.5) * 0.5;
                }
                
                if (abs(this->points[a]-this->points[b]) < this->W*1.2 && abs(this->isc[a]-this->isc[b]) < this->N*0.2 && abs(this->ico[a]-this->ico[b]) < this->N*0.2 && abs(ap-bp) < 2) {
                    ap = (ap+bp+0.5) * 0.5;
                    bp = (ap+bp+0.5) * 0.5;
                }
                
                if (this->isc[a] > this->N*0.8 && this->ico[b] > this->N*0.7 && this->scored[a] < (this->N-1) * 0.8 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.8 && this->ico[a] > this->N*0.7 && this->scored[b] < (this->N-1) * 0.8 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.7 && this->ico[b] > this->N*0.8 && this->scored[a] < (this->N-1) * 0.8 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.7 && this->ico[a] > this->N*0.8 && this->scored[b] < (this->N-1) * 0.8 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.7 && this->ico[b] > this->N*0.4 && this->scored[a] < (this->N-1) * 0.7 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.7 && this->ico[a] > this->N*0.4 && this->scored[b] < (this->N-1) * 0.7 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.4 && this->ico[b] > this->N*0.7 && this->scored[a] < (this->N-1) * 0.7 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.4 && this->ico[a] > this->N*0.7 && this->scored[b] < (this->N-1) * 0.7 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.6 && this->ico[b] > this->N*0.2 && this->scored[a] < (this->N-1) * 0.6 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.6 && this->ico[a] > this->N*0.2 && this->scored[b] < (this->N-1) * 0.6 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.2 && this->ico[b] > this->N*0.6 && this->scored[a] < (this->N-1) * 0.6 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.2 && this->ico[a] > this->N*0.6 && this->scored[b] < (this->N-1) * 0.6 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.4 && this->ico[b] > this->N*0.4 && this->scored[a] < (this->N-1) * 0.5 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.4 && this->ico[a] > this->N*0.4 && this->scored[b] < (this->N-1) * 0.5 && bp < 2) { bp=0; }
                if (this->isc[a] > this->N*0.6 && this->ico[b] > this->N*0.6 && this->scored[a] < (this->N-1) * 0.4 && ap < 2) { ap=0; }
                if (this->isc[b] > this->N*0.6 && this->ico[a] > this->N*0.6 && this->scored[b] < (this->N-1) * 0.4 && bp < 2) { bp=0; }
                
                
                
                
                ret.emplace_back(ap, bp);
            }
        }
        
        
        return this->toVString(ret);
    }
    
    vector<string> toVString (vector< pair<int, int> >& vp) {
        vector<string> ret;
        for (auto&& i : vp) {
            ret.emplace_back(print(i.first, i.second));
        }
        return ret;
    }
    
};

int main() {
    SoccerTournament prog;
    int N;
    int W;
    int D;
    int X;
    int s;
    int c;
    int p;
    vector<int> scored;
    vector<int> conceded;
    vector<int> points;
    cin >> N;
    cin >> W;
    cin >> D;
    cin >> X;
    for (int i=0; i<N; ++i) {
        cin >> s >> c >> p;
        scored.push_back(s);
        conceded.push_back(c);
        points.push_back(p);
    }  
    
    vector<string> ret = prog.findSolution(N, W, D, X, scored,  conceded, points);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
}