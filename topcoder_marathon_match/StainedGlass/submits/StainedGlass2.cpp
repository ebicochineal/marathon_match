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
        
        pdebug(this->N);
        pdebug(this->H);
        pdebug(this->W);
        
        
        this->testPut(this->gridNum(), this->xyc);
        this->fixColor(this->xyc);
        this->subtractiveColor(this->xyc);
        
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
                // t.emplace_back(((this->W + 200) / n) * x - 100,  ((this->H + 200) / n) * y - 100, 0);
                // t.emplace_back(((this->W) / n) * x,  ((this->H) / n) * y, 0);
                t.emplace_back(((this->W + (this->W/n*2)) / n) * x - (this->W/n),  ((this->H + (this->H/n*2)) / n) * y - (this->H/n), 0);
            }
        }
        
        for (int i = 0; i < this->N - n * n; ++i) {
            t.emplace_back(-500 + i, -500, 0);
        }
    }
    
    void fixColor(vector<XYC> &t) {
        vector< array<int, 255> > rcs(t.size(), array<int, 255>());
        vector< array<int, 255> > gcs(t.size(), array<int, 255>());
        vector< array<int, 255> > bcs(t.size(), array<int, 255>());
        
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
                
                rcs[index][r] += 1;
                gcs[index][g] += 1;
                bcs[index][b] += 1;
            }
        }
        vector<int> zeroindexs;
        int last_true_index = 0;
        for (int i = 0; i < t.size(); ++i) {
            int minr = 255000000;
            int ming = 255000000;
            int minb = 255000000;
            int r = 0;
            int g = 0;
            int b = 0;
            for (int j = 0; j < 255; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 255; ++k) {
                    rsum += abs(k - j) * rcs[i][k];
                    gsum += abs(k - j) * gcs[i][k];
                    bsum += abs(k - j) * bcs[i][k];
                }
                if (rsum < minr) {
                    minr = rsum;
                    r = j;
                }
                if (gsum < ming) {
                    ming = gsum;
                    g = j;
                }
                if (bsum < minb) {
                    minb = bsum;
                    b = j;
                }
            }
            
            int cnt = 0;
            for (int k = 0; k < 255; ++k) {
                cnt += rcs[i][k];
            }
            if (cnt == 0) {
                zeroindexs.emplace_back(i);
            } else {
                t[i].r = r;
                t[i].g = g;
                t[i].b = b;
                last_true_index = i;
            }
        }
        for (auto &i : zeroindexs) {
            t[i].r = t[last_true_index].r;
            t[i].g = t[last_true_index].g;
            t[i].b = t[last_true_index].b;
        }
    }
    
    void fixColor2(vector<XYC> &t, unordered_map<int, vector<int> > &cols) {
        vector< array<int, 255> > rcs(t.size(), array<int, 255>());
        vector< array<int, 255> > gcs(t.size(), array<int, 255>());
        vector< array<int, 255> > bcs(t.size(), array<int, 255>());
        
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
                
                rcs[index][r] += 1;
                gcs[index][g] += 1;
                bcs[index][b] += 1;
            }
        }
        
        for (auto &i : cols) {
            if (i.second.size() < 2) { continue; }
            array<int, 255> tr;
            array<int, 255> tg;
            array<int, 255> tb;
            for (auto &j : i.second) {
                for (int k = 0; k < 255; ++k) {
                    tr[k] = rcs[j][k];
                    tg[k] = gcs[j][k];
                    tb[k] = bcs[j][k];
                }
            }
            for (auto &j : i.second) {
                for (int k = 0; k < 255; ++k) {
                    rcs[j][k] = tr[k];
                    gcs[j][k] = tg[k];
                    bcs[j][k] = tb[k];
                }
            }
        }
        
        
        vector<int> zeroindexs;
        int last_true_index = 0;
        for (int i = 0; i < t.size(); ++i) {
            int minr = 255000000;
            int ming = 255000000;
            int minb = 255000000;
            int r = 0;
            int g = 0;
            int b = 0;
            for (int j = 0; j < 255; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 255; ++k) {
                    rsum += abs(k - j) * rcs[i][k];
                    gsum += abs(k - j) * gcs[i][k];
                    bsum += abs(k - j) * bcs[i][k];
                }
                if (rsum < minr) {
                    minr = rsum;
                    r = j;
                }
                if (gsum < ming) {
                    ming = gsum;
                    g = j;
                }
                if (bsum < minb) {
                    minb = bsum;
                    b = j;
                }
            }
            
            int cnt = 0;
            for (int k = 0; k < 255; ++k) {
                cnt += rcs[i][k];
            }
            if (cnt == 0) {
                zeroindexs.emplace_back(i);
            } else {
                t[i].r = r;
                t[i].g = g;
                t[i].b = b;
                last_true_index = i;
            }
        }
        for (auto &i : zeroindexs) {
            t[i].r = t[last_true_index].r;
            t[i].g = t[last_true_index].g;
            t[i].b = t[last_true_index].b;
        }
    }
    
    
    
    
    
    void subtractiveColor(vector<XYC> &t) {
        unordered_map<int, vector<int> > cols;
        
        for (int i = 0; i < t.size(); ++i) {
            int r = t[i].r - t[i].r % 32;
            int g = t[i].g - t[i].g % 32;
            int b = t[i].b - t[i].b % 32;
            int c = (r << 16) + (g << 8) + b;
            cols[c].emplace_back(i);
            
        }
        
        fixColor2(t, cols);
        
        // for (auto &i : t) {
        //     int r = i.r - i.r % 24;
        //     int g = i.g - i.g % 24;
        //     int b = i.b - i.b % 24;
        //     int c = (r << 16) + (g << 8) + b;
        //     if (cols[c].size() > 2) {
        //         i.r = r;
        //         i.g = g;
        //         i.b = b;
        //     }
        // }
        
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
