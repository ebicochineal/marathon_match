// C++11
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
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

template<class T>
void pdebug (T s) {
    stringstream ss;
    ss << "<cerr>" << print(s) << "</cerr>";
    cerr << ss.str();
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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

// inline double distance (const int ax, const int ay, const int bx, const int by) {
//     return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
// }

inline int distance (const int ax, const int ay, const int bx, const int by) {
    return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}


inline void getRGB (int c, int &r, int &g, int &b) {
    r = (c >> 16);
    g = (c >> 8) & 0xff;
    b = c & 0xff;
}


class XYC {
public:
    int x, y, r, g, b;
    XYC (int x, int y, int c) {
        this->x = x;
        this->y = y;
        getRGB(c, this->r, this->g, this->b);
    }
    
    XYC (int x, int y, int r, int g, int b) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    int color () {
        return (this->r << 16) | (this->g << 8) | this->b;
    }
    
};


class StainedGlass {
public:
    StopWatch sw;
    int H, W, N;
    vector<int> pixels;
    
    vector<XYC> xyc;
    
    vector<int> create(int H, vector<int> pixels, int N) {
        this->sw = StopWatch();
        
        this->N = N;
        this->H = H;
        this->W = pixels.size() / H;
        
        
        this->pixels = pixels;
        
        pdebug(this->gridNum());
        pdebug(this->H);
        pdebug(this->W);
        
        // this->xyc.emplace_back( 130,  50, 0xDA70D6);
        // this->xyc.emplace_back( 180, 150, 0x6495ED);
        // this->xyc.emplace_back(280,  200, 0x00C957);
        // this->xyc.emplace_back( 30,  200, 0xFFE7BA);
        // this->xyc.emplace_back( 80,  250, 0xD2691E);
        
        this->testPut(this->gridNum(), this->xyc);
        this->fixColor(this->xyc);
        
        
        pdebug((int64_t)this->allScore(this->xyc));
        pdebug("time " + to_string(this->sw.get_milli_time()));
        
        return this->toRet(this->xyc);
    }
    
    int gridNum () {
        int n = 1;
        while ((n+1) * (n+1) <= this->N) { n += 1; }
        return n;
    }
    
    void testPut (int n, vector<XYC> &t) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                //t.emplace_back(((this->W + 200) / n) * x - 100 + (y%2<1?50:0),  ((this->H + 200) / n) * y - 100, 0);
                t.emplace_back(((this->W + 200) / n) * x - 100,  ((this->H + 200) / n) * y - 100, 0);
                // t.emplace_back(((this->W) / n) * x,  ((this->H) / n) * y, 0);
                // t.emplace_back(((this->W + (this->W/n*2)) / n) * x - (this->W/n),  ((this->H + (this->H/n*2)) / n) * y - (this->H/n), 0);
            }
        }
        
        for (int i = 0; i < this->N - n * n; ++i) {
            t.emplace_back(-500 + i, -500, 0);
        }
    }
    
    void fixColor(vector<XYC> &t) {
        
        vector<int> cnts(t.size(), 0);
        vector<int> rcs(t.size(), 0);
        vector<int> gcs(t.size(), 0);
        vector<int> bcs(t.size(), 0);
        
        
        
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                int index = 0;
                int dist = 100000000;
                for (int i = 0; i < t.size(); ++i) {
                    int tdist = distance(x, y, t[i].x, t[i].y);
                    if (tdist < dist) {
                        dist = tdist;
                        index = i;
                    }
                }
                int r, g, b;
                getRGB(this->pixels[x + this->W * y], r, g, b);
                
                cnts[index] += 1;
                rcs[index] += r;
                gcs[index] += g;
                bcs[index] += b;
            }
        }
        
        for (int i = 0; i < t.size(); ++i) {
            
            if (cnts[i] > 0) {
                t[i].r = rcs[i] / cnts[i];
                t[i].g = gcs[i] / cnts[i];
                t[i].b = bcs[i] / cnts[i];
            }
            
        }
        
        
        
        
        
        
    }
    
    vector<int> toRet (vector<XYC> &t) {
        vector<int> ret;
        for (int i = 0; i < t.size(); ++i) {
            ret.emplace_back(t[i].y);
            ret.emplace_back(t[i].x);
            ret.emplace_back(t[i].color());
        }
        return ret;
    }
    
    double allScore (vector<XYC> &t) {
        int64_t score = 0;
        unordered_set<int> cols;
        for (int y = 0; y < this->H; ++y) {
            for (int x = 0; x < this->W; ++x) {
                int index = 0;
                int dist = 1000000000;
                for (int i = 0; i < t.size(); ++i) {
                    int tdist = distance(x, y, t[i].x, t[i].y);
                    if (tdist < dist) {
                        dist = tdist;
                        index = i;
                    }
                }
                int r, g, b;
                getRGB(this->pixels[x + this->W * y], r, g, b);
                
                score += abs(r - t[index].r) + abs(g - t[index].g) + abs(b - t[index].b);
            }
        }
        
        for (auto &i : t) { cols.emplace(i.color()); }
        
        double m = 1 + (double)cols.size() / t.size();
        return score * m * m;
    }
    
    
};








// -------8<------- end of the solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i)
        cin >> v[i];
}

int main() {
    StainedGlass sg;
    int H;
    cin >> H;
    int S;
    cin >> S;
    vector<int> pixels(S);
    getVector(pixels);
    
    int N;
    cin >> N;
    
    vector<int> ret = sg.create(H, pixels, N);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
