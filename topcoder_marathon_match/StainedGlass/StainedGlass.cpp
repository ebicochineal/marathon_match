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
#include <algorithm>
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

struct mpos {
public:
    int x;
    int y;
    mpos () { this->x = 0; this->y = 0; }
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <> class hash<mpos> {
    public:
        size_t operator()(const mpos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
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
    int H, W, N, G;
    int gw, gh;
    vector<int> pixels;
    vector<int> vpixels;
    
    vector< vector<int> > rcs;
    vector< vector<int> > gcs;
    vector< vector<int> > bcs;
    
    vector< vector<int> > rcs2;
    vector< vector<int> > gcs2;
    vector< vector<int> > bcs2;
    
    vector<int> create(int H, vector<int> pixels, int N) {
        this->sw = StopWatch();
        
        this->N = N;
        this->H = H;
        this->W = pixels.size() / H;
        
        this->G = this->N > 100 ? 32 : 24;
        this->G = this->N > 200 ? 64 : this->G;
        this->gw = (2000 + this->W) / this->G;
        this->gh = (2000 + this->H) / this->G;
        this->pixels = pixels;
        this->vpixels = pixels;
        this->rcs = vector< vector<int> >(N, vector<int>(256, 0));
        this->gcs = vector< vector<int> >(N, vector<int>(256, 0));
        this->bcs = vector< vector<int> >(N, vector<int>(256, 0));
        
        this->rcs2 = vector< vector<int> >(N, vector<int>(256, 0));
        this->gcs2 = vector< vector<int> >(N, vector<int>(256, 0));
        this->bcs2 = vector< vector<int> >(N, vector<int>(256, 0));
        
        pdebug(this->N);
        pdebug(this->H);
        pdebug(this->W);
    
        int cnt = 0;
        vector<XYC> best;
        this->testPut2(this->gridNum(), best);
        int64_t bestscore = this->fixColorScore(4, best);
        
        this->fixColor2p(4, best);
        this->subtractiveColor0(4, 64, 0, best);
        unordered_set<int> cus;
        for (auto &i : best) {
            cus.emplace(i.color());
        }
        for (int x = 0; x < this->W; ++x) {
            for (int y = 0; y < this->H; ++y) {
                int r, g, b;
                getRGB(this->pixels[x + this->W * y], r, g, b);
                ;
                int mincdist = 3000;
                for (auto &i : cus) {
                    int tr, tg, tb;
                    getRGB(this->pixels[x + this->W * y], tr, tg, tb);
                    int dist = abs(r - tr) + abs(g - tg) + abs(b - tb);
                    if (dist < mincdist) {
                        mincdist = dist;
                        this->vpixels[x + this->W * y] = (tr << 16) + (tg << 8) + tb;
                    }
                }
            }
        }
        
        
        
        
        for (int i = 0; i < 640 * (N < 50 ? 1 : 0); ++i) {
            vector<XYC> a;
            this->testPut2r(this->gridNum(), i, a);
            int64_t ascore = this->fixColorScore(4, a);
            if (ascore < bestscore) {
                bestscore = ascore;
                best = a;
            }
        }
        // this->testPut4(best);
        
        int m = 4;
        unordered_set<mpos> tus;
        for (auto &i : best) { tus.emplace(i.x, i.y); }
        bestscore = 0;
        vector<int> bestscores = this->fixColorScores(m, best);
        for (auto &i : bestscores) { bestscore += i; }
        
        while (1) {
            if (cnt>0 && cnt%8==0 && this->sw.get_milli_time() > 6000) { break; }
            cnt += 1;
            vector<XYC> a = best;
            for (int p = 0; p < N; ++p) {
                int vx = (xrnd()%3 - 1)*(xrnd()%3+1);
                int vy = (xrnd()%3 - 1)*(xrnd()%3+1);
                if (a[p].x + vx < -200 || a[p].x + vx > this->W + 200) { continue; }
                if (a[p].y + vy < -200 || a[p].y + vy > this->H + 200) { continue; }
                if (tus.find(mpos(a[p].x + vx, a[p].y + vy)) != tus.end()) { continue; }
                a[p].x += vx;
                a[p].y += vy;
                tus.emplace(a[p].x, a[p].y);
            }
            vector<int> tscores = this->fixColorScores(m, a);
            vector<XYC> b = best;
            for (int p = 0; p < N; ++p) {
                if (tscores[p] <= bestscores[p]) {
                    b[p] = a[p];
                } else {
                    b[p] = best[p];
                }
            }
            tscores = this->fixColorScores(m, b);
            int64_t tscore = 0;
            for (auto &i : tscores) { tscore += i; }
            
            if (tscore < bestscore) {
                best = b;
                bestscore = tscore;
                bestscores = tscores;
            }
            tus.clear();
            for (auto &i : best) { tus.emplace(i.x, i.y); }
        }
        
        m = 1;
        bestscore = 0;
        bestscores = this->fixColorScores(m, best);
        for (auto &i : bestscores) { bestscore += i; }
        
        while (1) {
            if (cnt>0 && cnt%8==0 && this->sw.get_milli_time() > 15000 + (N < 300 ? 1000 : 0) - (N > 800 ? 1000 : 0)) { break; }
            cnt += 1;
            vector<XYC> a = best;
            for (int p = 0; p < N; ++p) {
                int vx = (xrnd()%3 - 1);
                int vy = (xrnd()%3 - 1);
                if (a[p].x + vx < -200 || a[p].x + vx > this->W + 200) { continue; }
                if (a[p].y + vy < -200 || a[p].y + vy > this->H + 200) { continue; }
                if (tus.find(mpos(a[p].x + vx, a[p].y + vy)) != tus.end()) { continue; }
                a[p].x += vx;
                a[p].y += vy;
                tus.emplace(a[p].x, a[p].y);
            }
            vector<int> tscores = this->fixColorScores(m, a);
            vector<XYC> b = best;
            for (int p = 0; p < N; ++p) {
                if (tscores[p] <= bestscores[p]) {
                    b[p] = a[p];
                } else {
                    b[p] = best[p];
                }
            }
            tscores = this->fixColorScores(m, b);
            int64_t tscore = 0;
            for (auto &i : tscores) { tscore += i; }
            
            if (tscore < bestscore) {
                best = b;
                bestscore = tscore;
                bestscores = tscores;
            }
            tus.clear();
            for (auto &i : best) { tus.emplace(i.x, i.y); }
        }
        m = 4;
        bestscore = this->fixColorScore(m, best);
        unordered_set<mpos> us;
        for (auto &i : best) { us.emplace(i.x, i.y); }
        int  limit = (N < 80 ? 17000 : 16000) - (N > 800 ? 1000 : 0);
        while (1) {
            if (cnt>0 && cnt%8==0 && this->sw.get_milli_time() > limit) { break; }
            cnt += 1;
            int p = xrnd() % this->N;
            int vx = (xrnd()%3 - 1) * 2;
            int vy = (xrnd()%3 - 1) * 2;
            if (best[p].x + vx < -200 || best[p].x + vx > this->W + 200) { continue; }
            if (best[p].y + vy < -200 || best[p].y + vy > this->H + 200) { continue; }
            if (us.find(mpos(best[p].x + vx, best[p].y + vy)) != us.end()) { continue; }
            us.erase(mpos(best[p].x, best[p].y));
            best[p].x += vx;
            best[p].y += vy;
            int64_t tscore = this->fixColorScore(m, best);
            if (tscore < bestscore) {
                bestscore = tscore;
                
            } else {
                best[p].x -= vx;
                best[p].y -= vy;
            }
            us.emplace(best[p].x, best[p].y);
        }
        
        vector<XYC> tmp = best;
        vector<XYC> tmp2 = tmp;
        int64_t bscore;
        this->fixColor2p(1, best);
        bestscore = this->allScore2(1, best);
        int ccnt = 0;
        for (int i = 0; i < 8; ++i) {
            tmp2 = tmp;
            this->subtractiveColor0(1, 16 + i*24, i, tmp2);
            bscore = this->allScore2(1, tmp2);
            if (bscore < bestscore) {
                bestscore = bscore;
                best = tmp2;
            }
            ccnt += 1;
            if (this->sw.get_milli_time() > 18500 + (N < 100 ? 500 : 0)) { break; }
        }
        pdebug("time " + to_string(this->sw.get_milli_time()));
        pdebug("loop " + to_string(cnt));
        pdebug("loop " + to_string(ccnt));
        
        pdebug(bestscore);
        return this->toRet(best);
        
    }
    
    int gridNum () {
        int n = 1;
        while ((n+1) * (n+1) <= this->N) { n += 1; }
        return n;
    }
    
    inline vector< vector< vector<int> > > initGrid (const vector<XYC> &t) {
        vector< vector< vector<int> > > r(this->G, vector< vector<int> >(this->G, vector<int>()));
        for (int i = 0; i < t.size(); ++i) {
            r[(t[i].x + 1000) / this->gw][(t[i].y + 1000) / this->gh].emplace_back(i);
        }
        return r;
    }
    
    
    void testPut (int n, vector<XYC> &t) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                t.emplace_back((this->W/n) * x + (this->W/n/2), (this->H/n) * y + (this->H/n/2), 0);
            }
        }
        
        for (int i = 0; i < this->N - n * n; ++i) {
            t.emplace_back(-500 + i, -500, 0);
        }
    }
    
    void testPut2 (int n, vector<XYC> &t) {
        unordered_set<mpos> a;
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                int px = (this->W / n) * x + (this->W/n/2) + (y%2<1?(this->W/n)/2:0);
                int py = (this->H / n) * y + (this->H/n/2);
                t.emplace_back(px, py, 0);
                a.emplace(mpos(px, py));
            }
        }
        while (a.size() < this->N) {
            int x = xrnd() % (this->W);
            int y = xrnd() % (this->H);
            if (a.find(mpos(x, y)) == a.end()) {
                a.emplace(mpos(x, y));
                t.emplace_back(x, y, 0);
            }
        }
        
    }
    
    
    void testPut2r (int n, int m, vector<XYC> &t) {
        unordered_set<mpos> a;
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                int px = (this->W / n) * x + (this->W/n/2) + (y%2<1?(this->W/n)/2:0);
                int py = xrnd()%(min(32, this->H/n-1))-16 + (this->H / n) * y + (this->H/n/2);
                t.emplace_back(px, py, 0);
                a.emplace(mpos(px, py));
            }
        }
        
        // int p = -800;
        while (a.size() < this->N) {
            int x = xrnd() % (this->W);
            int y = xrnd() % (this->H);
            if (a.find(mpos(x, y)) == a.end()) {
                a.emplace(mpos(x, y));
                t.emplace_back(x, y, 0);
            }
            // int x = p;
            // int y = -800;
            // if (a.find(mpos(x, y)) == a.end()) {
            //     a.emplace(mpos(x, y));
            //     t.emplace_back(x, y, 0);
            // }
            // p += 1;
        }
        
    }
    
    void testPut3 (int n, vector<XYC> &t) {
        unordered_set<mpos> a;
        while (a.size() < this->N) {
            int x = xrnd() % (this->W);
            int y = xrnd() % (this->H);
            if (a.find(mpos(x, y)) == a.end()) {
                a.emplace(mpos(x, y));
                t.emplace_back(x, y, 0);
            }
        }
    }
    
    
    void testPut4 (vector<XYC> &t) {
        vector<int> scores = this->fixColorScores(4, t);
        vector< pair<int, int> > si;
        unordered_set<mpos> us;
        vector<int> z;
        for (int i = 0; i < this->N; ++i) {
            si.emplace_back(scores[i], i);
            us.emplace(t[i].x ,t[i].y);
            if (t[i].y < -500) { z.emplace_back(i); }
        }
        sort(si.begin(), si.end(), [](const pair<int, int> &a, const pair<int, int> &b) { return a.first > b.first; });
        for (int i = 0; i < z.size(); ++i) {
            mpos p = mpos(t[si[i].second].x + 1, t[si[i].second].y);
            if (us.find(p) == us.end()) {
                us.emplace(p);
                t[z[i]].x = p.x;
                t[z[i]].y = p.y;
            }
        }
    }
    
    inline void tmpClear () {
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < 256; ++j) {
                this->rcs[i][j] = 0;
                this->gcs[i][j] = 0;
                this->bcs[i][j] = 0;
            }
        }
    }
    
    //////
    int64_t fixColorScore(const int o, vector<XYC> &t) {
        int64_t score = 0;
        this->tmpClear();
        
        vector< vector< vector<int> > > grid = this->initGrid(t);
        
        // for (auto &i : t) {
        //     int r, g, b;
        //     getRGB(this->vpixels[min(max(i.x, 0), this->W-1) + this->W * min(max(i.y, 0), this->H-1)], r, g, b);
        //     i.r = r;
        //     i.g = g;
        //     i.b = b;
        // }
        
        for (int y = 0; y < this->H; y+=o) {
            for (int x = 0; x < this->W; x+=o) {
                int index = 0;
                int dist = 100000000;
                int px = (x + 1000) / this->gw;
                int py = (y + 1000) / this->gh;
                int m = 16;
                for (int v = 1; v < m; ++v) {
                    const int vv = v*2-1;
                    const int d = v-1;
                    for (int xx = 0; xx < vv; ++xx) {
                        const int ppx = px + xx - d;
                        for (int yy = 0; yy < vv; ++yy) {
                            if (xx > 0 && xx < vv-1 && yy > 0 && yy < vv-1) { continue; }
                            const int ppy = py + yy - d;
                            if (ppx < 0 || ppy < 0 || ppx >= this->G || ppy >= this->G) { continue; }
                            for (auto &i : grid[ppx][ppy]) {
                                int tdist = distance(x, y, t[i].x, t[i].y);
                                if (tdist < dist) {
                                    dist = tdist;
                                    index = i;
                                }
                            }
                        }
                    }
                    if (m == 16 && dist < 100000000) { m = v + 2; }
                }
                
                int r, g, b;
                getRGB(this->vpixels[x + this->W * y], r, g, b);
                this->rcs[index][r] += 1;
                this->gcs[index][g] += 1;
                this->bcs[index][b] += 1;
                
                
                // int r, g, b;
                // getRGB(this->vpixels[x + this->W * y], r, g, b);
                // score += abs(r - t[index].r) + abs(g - t[index].g) + abs(b - t[index].b);
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
            
            int cnt = 0;
            for (int j = 0; j < 256; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 256; ++k) {
                    rsum += abs(k - j) * this->rcs[i][k];
                    gsum += abs(k - j) * this->gcs[i][k];
                    bsum += abs(k - j) * this->bcs[i][k];
                    
                    cnt += this->rcs[i][k];
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
            
            if (cnt == 0) {
                zeroindexs.emplace_back(i);
            } else {
                score += minr + ming + minb;
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
        
        return score;
    }
    
    //////
    vector<int> fixColorScores(const int o, vector<XYC> &t) {
        this->tmpClear();
        
        vector< vector< vector<int> > > grid = this->initGrid(t);
        
        vector<int> scores(this->N, 0);
        
        for (auto &i : t) {
            int r, g, b;
            getRGB(this->vpixels[min(max(i.x, 0), this->W-1) + this->W * min(max(i.y, 0), this->H-1)], r, g, b);
            i.r = r;
            i.g = g;
            i.b = b;
        }
        
        for (int y = 0; y < this->H; y+=o) {
            for (int x = 0; x < this->W; x+=o) {
                int index = 0;
                int dist = 100000000;
                int px = (x + 1000) / this->gw;
                int py = (y + 1000) / this->gh;
                int m = 16;
                for (int v = 1; v < m; ++v) {
                    const int vv = v*2-1;
                    const int d = v-1;
                    for (int xx = 0; xx < vv; ++xx) {
                        const int ppx = px + xx - d;
                        for (int yy = 0; yy < vv; ++yy) {
                            if (xx > 0 && xx < vv-1 && yy > 0 && yy < vv-1) { continue; }
                            const int ppy = py + yy - d;
                            if (ppx < 0 || ppy < 0 || ppx >= this->G || ppy >= this->G) { continue; }
                            for (auto &i : grid[ppx][ppy]) {
                                int tdist = distance(x, y, t[i].x, t[i].y);
                                if (tdist < dist) {
                                    dist = tdist;
                                    index = i;
                                }
                            }
                        }
                    }
                    if (m == 16 && dist < 100000000) { m = v + 2; }
                }
                int r, g, b;
                getRGB(this->vpixels[x + this->W * y], r, g, b);
                // this->rcs[index][r] += 1;
                // this->gcs[index][g] += 1;
                // this->bcs[index][b] += 1;
                
                scores[index] += abs(r - t[index].r) + abs(g - t[index].g) + abs(b - t[index].b);
            }
        }
        // vector<int> zeroindexs;
        // int last_true_index = 0;
        // for (int i = 0; i < t.size(); ++i) {
        //     int minr = 255000000;
        //     int ming = 255000000;
        //     int minb = 255000000;
        //     int r = 0;
        //     int g = 0;
        //     int b = 0;
            
        //     int cnt = 0;
        //     for (int j = 0; j < 256; ++j) {
        //         int rsum = 0;
        //         int gsum = 0;
        //         int bsum = 0;
                
        //         for (int k = 0; k < 256; ++k) {
        //             rsum += abs(k - j) * this->rcs[i][k];
        //             gsum += abs(k - j) * this->gcs[i][k];
        //             bsum += abs(k - j) * this->bcs[i][k];
                    
        //             cnt += this->rcs[i][k];
        //         }
        //         if (rsum < minr) {
        //             minr = rsum;
        //             r = j;
        //         }
        //         if (gsum < ming) {
        //             ming = gsum;
        //             g = j;
        //         }
        //         if (bsum < minb) {
        //             minb = bsum;
        //             b = j;
        //         }
        //     }
            
        //     if (cnt == 0) {
        //         zeroindexs.emplace_back(i);
        //     } else {
        //         scores[i] = minr + ming + minb;
        //         t[i].r = r;
        //         t[i].g = g;
        //         t[i].b = b;
        //         last_true_index = i;
        //     }
            
        // }
        // for (auto &i : zeroindexs) {
            
        //     t[i].r = t[last_true_index].r;
        //     t[i].g = t[last_true_index].g;
        //     t[i].b = t[last_true_index].b;
        // }
        
        return scores;
    }
    
    //////
    void fixColor(const int o, vector<XYC> &t) {
        this->tmpClear();
        vector< vector< vector<int> > > grid = this->initGrid(t);
        
        for (int y = 0; y < this->H; y+=o) {
            for (int x = 0; x < this->W; x+=o) {
                int index = 0;
                int dist = 100000000;
                int px = (x + 1000) / this->gw;
                int py = (y + 1000) / this->gh;
                int m = 16;
                for (int v = 1; v < m; ++v) {
                    const int vv = v*2-1;
                    const int d = v-1;
                    for (int xx = 0; xx < vv; ++xx) {
                        const int ppx = px + xx - d;
                        for (int yy = 0; yy < vv; ++yy) {
                            if (xx > 0 && xx < vv-1 && yy > 0 && yy < vv-1) { continue; }
                            const int ppy = py + yy - d;
                            if (ppx < 0 || ppy < 0 || ppx >= this->G || ppy >= this->G) { continue; }
                            for (auto &i : grid[ppx][ppy]) {
                                int tdist = distance(x, y, t[i].x, t[i].y);
                                if (tdist < dist) {
                                    dist = tdist;
                                    index = i;
                                }
                            }
                        }
                    }
                    if (m == 16 && dist < 100000000) { m = v + 2; }
                }
                int r, g, b;
                getRGB(this->pixels[x + this->W * y], r, g, b);
                this->rcs[index][r] += 1;
                this->gcs[index][g] += 1;
                this->bcs[index][b] += 1;
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
            for (int j = 0; j < 256; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 256; ++k) {
                    rsum += abs(k - j) * this->rcs[i][k];
                    gsum += abs(k - j) * this->gcs[i][k];
                    bsum += abs(k - j) * this->bcs[i][k];
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
            for (int k = 0; k < 256; ++k) {
                cnt += this->rcs[i][k];
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
    
    //////
    void fixColor2p(const int o, vector<XYC> &t) {
        this->tmpClear();
        
        vector< vector< vector<int> > > grid = this->initGrid(t);
        
        for (int y = 0; y < this->H; y+=o) {
            for (int x = 0; x < this->W; x+=o) {
                int index = 0;
                int dist = 100000000;
                int px = (x + 1000) / this->gw;
                int py = (y + 1000) / this->gh;
                int m = 16;
                for (int v = 1; v < m; ++v) {
                    const int vv = v*2-1;
                    const int d = v-1;
                    for (int xx = 0; xx < vv; ++xx) {
                        const int ppx = px + xx - d;
                        for (int yy = 0; yy < vv; ++yy) {
                            if (xx > 0 && xx < vv-1 && yy > 0 && yy < vv-1) { continue; }
                            const int ppy = py + yy - d;
                            if (ppx < 0 || ppy < 0 || ppx >= this->G || ppy >= this->G) { continue; }
                            for (auto &i : grid[ppx][ppy]) {
                                int tdist = distance(x, y, t[i].x, t[i].y);
                                if (tdist < dist) {
                                    dist = tdist;
                                    index = i;
                                }
                            }
                        }
                    }
                    if (m == 16 && dist < 100000000) { m = v + 2; }
                }
                int r, g, b;
                getRGB(this->pixels[x + this->W * y], r, g, b);
                this->rcs[index][r] += 1;
                this->gcs[index][g] += 1;
                this->bcs[index][b] += 1;
            }
        }
    }
    
    
    void fixColor2(const int o, vector<XYC> &t, unordered_map<int, vector<int> > &cols) {
        
        for (auto &i : cols) {
            if (i.second.size() < 2) { continue; }
            vector<int> tr(256, 0);
            vector<int> tg(256, 0);
            vector<int> tb(256, 0);
            for (auto &j : i.second) {
                for (int k = 0; k < 256; ++k) {
                    tr[k] += this->rcs[j][k];
                    tg[k] += this->gcs[j][k];
                    tb[k] += this->bcs[j][k];
                }
            }
            for (auto &j : i.second) {
                for (int k = 0; k < 256; ++k) {
                    this->rcs2[j][k] = tr[k];
                    this->gcs2[j][k] = tg[k];
                    this->bcs2[j][k] = tb[k];
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
            for (int j = 0; j < 256; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 256; ++k) {
                    rsum += abs(k - j) * this->rcs2[i][k];
                    gsum += abs(k - j) * this->gcs2[i][k];
                    bsum += abs(k - j) * this->bcs2[i][k];
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
            for (int k = 0; k < 256; ++k) {
                cnt += this->rcs[i][k];
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
        
        
        last_true_index = 0;
        cols.clear();
        for (int i = 0; i < t.size(); ++i) {
            int minc = 255000000*3;
            int c = 0;
            for (auto &u : t) {
                int asum = 0;
                for (int k = 0; k < 256; ++k) {
                    asum += abs(k - u.r) * this->rcs[i][k]+abs(k - u.g) * this->gcs[i][k]+abs(k - u.b) * this->bcs[i][k];
                }
                if (asum < minc) {
                    minc = asum;
                    c = (u.r << 16) + (u.g << 8) + u.b;
                }
                
            }
            cols[c].emplace_back(i);
            
        }
        fixColor3(o, t, cols);
        
        // last_true_index = 0;
        // for (int i = 0; i < t.size(); ++i) {
        //     int minc = 255000000*3;
        //     int r = 0;
        //     int g = 0;
        //     int b = 0;
        //     for (auto &u : t) {
        //         int asum = 0;
        //         int gsum = 0;
        //         int bsum = 0;
                
        //         for (int k = 0; k < 256; ++k) {
        //             asum += abs(k - u.r) * this->rcs[i][k]+abs(k - u.g) * this->gcs[i][k]+abs(k - u.b) * this->bcs[i][k];
        //         }
        //         if (asum < minc) {
        //             minc = asum;
        //             r = u.r;
        //             g = u.g;
        //             b = u.b;
        //         }
        //     }
        //     int cnt = 0;
        //     for (int k = 0; k < 256; ++k) {
        //         cnt += this->rcs[i][k];
        //     }
        //     if (cnt == 0) {
        //         zeroindexs.emplace_back(i);
        //     } else {
        //         t[i].r = r;
        //         t[i].g = g;
        //         t[i].b = b;
        //         last_true_index = i;
        //     }
        // }
        
    }
    
    void fixColor3(const int o, vector<XYC> &t, unordered_map<int, vector<int> > &cols) {
        
        for (auto &i : cols) {
            if (i.second.size() < 2) { continue; }
            vector<int> tr(256, 0);
            vector<int> tg(256, 0);
            vector<int> tb(256, 0);
            for (auto &j : i.second) {
                for (int k = 0; k < 256; ++k) {
                    tr[k] += this->rcs[j][k];
                    tg[k] += this->gcs[j][k];
                    tb[k] += this->bcs[j][k];
                }
            }
            for (auto &j : i.second) {
                for (int k = 0; k < 256; ++k) {
                    this->rcs2[j][k] = tr[k];
                    this->gcs2[j][k] = tg[k];
                    this->bcs2[j][k] = tb[k];
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
            for (int j = 0; j < 256; ++j) {
                int rsum = 0;
                int gsum = 0;
                int bsum = 0;
                
                for (int k = 0; k < 256; ++k) {
                    rsum += abs(k - j) * this->rcs2[i][k];
                    gsum += abs(k - j) * this->gcs2[i][k];
                    bsum += abs(k - j) * this->bcs2[i][k];
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
            for (int k = 0; k < 256; ++k) {
                cnt += this->rcs[i][k];
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
    
    
    void subtractiveColor0(const int o, const int q, const int w, vector<XYC> &t) {
        unordered_map<int, vector<int> > cols;
        for (int i = 0; i < t.size(); ++i) {
            int minc = 0;
            int mincdist = 3000;
            for (int r = 0; r < 256; r += q) {
                for (int g = 0; g < 256; g += q) {
                    for (int b = 0; b < 256; b += q) {
                        int c = (r << 16) + (g << 8) + b;
                        int dist = abs(r - t[i].r) + abs(g - t[i].g) + abs(b - t[i].b);
                        if (dist < mincdist) {
                            mincdist = dist;
                            minc = c;
                        }
                    }
                }
            }
            cols[minc].emplace_back(i);
        }
        
            for (int k = 0; k < 8; ++k) {
                vector<int> cols2;
                for (auto &i : cols) {
                    int r=0;
                    int g=0;
                    int b=0;
                    for (auto &j : i.second) {
                        r += t[j].r;
                        g += t[j].g;
                        b += t[j].b;
                    }
                    if (i.second.size() > 0) {
                        r /= i.second.size();
                        g /= i.second.size();
                        b /= i.second.size();
                        cols2.emplace_back((r << 16) + (g << 8) + b);
                    }
                }
                cols.clear();
                for (int i = 0; i < t.size(); ++i) {
                    int minc = 0;
                    int mincdist = 3000;
                    int r,g,b;
                    for (auto &j : cols2) {
                        getRGB(j, r, g, b);
                        int c = (r << 16) + (g << 8) + b;
                        int dist = abs(g - t[i].g) + abs(b - t[i].b);
                        if (dist < mincdist) {
                            mincdist = dist;
                            minc = c;
                        }
                    }
                    cols[minc].emplace_back(i);
                }
            }
            
        
        fixColor2(o, t, cols);
    }
    
    void subtractiveColor1(const int o, const int q, const int w, vector<XYC> &t) {
        unordered_map<int, vector<int> > cols;
        for (int i = 0; i < t.size(); ++i) {
            int minc = 0;
            int mincdist = 3000;
            for (int r = q/2; r < 256; r += q) {
                for (int g = q/2; g < 256; g += q) {
                    for (int b = q/2; b < 256; b += q) {
                        int c = (r << 16) + (g << 8) + b;
                        int dist = abs(g - t[i].g) + abs(b - t[i].b);
                        if (dist < mincdist) {
                            mincdist = dist;
                            minc = c;
                        }
                        
                    }
                }
            }
            cols[minc].emplace_back(i);
        }
        if (w % 2 == 0) {
            vector<int> cols2;
            for (auto &i : cols) {
                int r=0;
                int g=0;
                int b=0;
                for (auto &j : i.second) {
                    r += t[j].r;
                    g += t[j].g;
                    b += t[j].b;
                }
                if (i.second.size() > 0) {
                    r /= i.second.size();
                    g /= i.second.size();
                    b /= i.second.size();
                }
                cols2.emplace_back((r << 16) + (g << 8) + b);
            }
            cols.clear();
            for (int i = 0; i < t.size(); ++i) {
                int minc = 0;
                int mincdist = 3000;
                int r,g,b;
                for (auto &j : cols2) {
                    getRGB(j, r, g, b);
                    int c = (r << 16) + (g << 8) + b;
                    int dist = abs(g - t[i].g) + abs(b - t[i].b);
                    if (dist < mincdist) {
                        mincdist = dist;
                        minc = c;
                    }
                }
                cols[minc].emplace_back(i);
            }
        }
        fixColor2(o, t, cols);
    }
    
    void subtractiveColor2(const int o, const int q, const int w, vector<XYC> &t) {
        unordered_map<int, vector<int> > cols;
        for (int i = 0; i < t.size(); ++i) {
            int minc = 0;
            int mincdist = 3000;
            for (int r = q/2; r < 256; r += q) {
                for (int g = q/2; g < 256; g += q) {
                    for (int b = q/2; b < 256; b += q) {
                        int c = (r << 16) + (g << 8) + b;
                        int dist = abs(r - t[i].r) + abs(b - t[i].b);
                        if (dist < mincdist) {
                            mincdist = dist;
                            minc = c;
                        }
                        
                    }
                }
            }
            cols[minc].emplace_back(i);
        }
        if (w % 2 == 0) {
            vector<int> cols2;
            for (auto &i : cols) {
                int r=0;
                int g=0;
                int b=0;
                for (auto &j : i.second) {
                    r += t[j].r;
                    g += t[j].g;
                    b += t[j].b;
                }
                if (i.second.size() > 0) {
                    r /= i.second.size();
                    g /= i.second.size();
                    b /= i.second.size();
                }
                cols2.emplace_back((r << 16) + (g << 8) + b);
            }
            cols.clear();
            for (int i = 0; i < t.size(); ++i) {
                int minc = 0;
                int mincdist = 3000;
                int r,g,b;
                for (auto &j : cols2) {
                    getRGB(j, r, g, b);
                    int c = (r << 16) + (g << 8) + b;
                    int dist = abs(g - t[i].g) + abs(b - t[i].b);
                    if (dist < mincdist) {
                        mincdist = dist;
                        minc = c;
                    }
                }
                cols[minc].emplace_back(i);
            }
        }
        fixColor2(o, t, cols);
    }
    
    void subtractiveColor3(const int o, const int q, const int w, vector<XYC> &t) {
        unordered_map<int, vector<int> > cols;
        for (int i = 0; i < t.size(); ++i) {
            int minc = 0;
            int mincdist = 3000;
            for (int r = q/2; r < 256; r += q) {
                for (int g = q/2; g < 256; g += q) {
                    for (int b = q/2; b < 256; b += q) {
                        int c = (r << 16) + (g << 8) + b;
                        int dist = abs(r - t[i].r) + abs(g - t[i].g);
                        if (dist < mincdist) {
                            mincdist = dist;
                            minc = c;
                        }
                    }
                }
            }
            cols[minc].emplace_back(i);
        }
        if (w % 2 == 0) {
            vector<int> cols2;
            for (auto &i : cols) {
                int r=0;
                int g=0;
                int b=0;
                for (auto &j : i.second) {
                    r += t[j].r;
                    g += t[j].g;
                    b += t[j].b;
                }
                if (i.second.size() > 0) {
                    r /= i.second.size();
                    g /= i.second.size();
                    b /= i.second.size();
                }
                cols2.emplace_back((r << 16) + (g << 8) + b);
            }
            cols.clear();
            for (int i = 0; i < t.size(); ++i) {
                int minc = 0;
                int mincdist = 3000;
                int r,g,b;
                for (auto &j : cols2) {
                    getRGB(j, r, g, b);
                    int c = (r << 16) + (g << 8) + b;
                    int dist = abs(g - t[i].g) + abs(b - t[i].b);
                    if (dist < mincdist) {
                        mincdist = dist;
                        minc = c;
                    }
                }
                cols[minc].emplace_back(i);
            }
        }
        fixColor2(o, t, cols);
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
    
    double allScore (const int o, vector<XYC> &t) {
        int64_t score = 0;
        unordered_set<int> cols;
        
        for (int y = 0; y < this->H; y+=o) {
            for (int x = 0; x < this->W; x+=o) {
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
    
    double allScore2 (const int o, vector<XYC> &t) {
        int64_t score = 0;
        unordered_set<int> cols;
        for (int i = 0; i < t.size(); ++i) {
            for (int k = 0; k < 256; ++k) {
                score += abs(k - t[i].r) * this->rcs[i][k];
                score += abs(k - t[i].g) * this->gcs[i][k];
                score += abs(k - t[i].b) * this->bcs[i][k];
            }
            cols.emplace(t[i].color());
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

