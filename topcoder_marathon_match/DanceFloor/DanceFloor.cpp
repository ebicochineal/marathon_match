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
//
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
//
class ColorCnt {
public:
    int a[6] = {0, 0, 0, 0, 0, 0};
    ColorCnt () {}
    int score () {
        int r = 0;
        for (int i = 0; i < 6; ++i) { r += a[i] * a[i]; }
        return r;
    }
    
};

class DPath {
public:
    int d = -1;
    int index = -1;
    vector<char> com;
    vector<e512pos> pos;
    e512pos sp, ep;
    int t = 0;
    
    
};



size_t g_c[50000];
// The size of the dance floor N is chosen between 8 and 50, inclusive.
// The number of colors C is chosen between 2 and 6, inclusive.
// The number of dancers D is chosen between 2 and 10, inclusive.
// The number of steps S is chosen between 50 and 1500, inclusive.
// A margin parameter M is chosen between 0 and 15, inclusive.
class DanceFloor {
public:
    StopWatch sw;
    int N, C, D, S;
    
    int grid[50][50];
    int cntgrid[50][50];
    int colors[50][50][6];
    
    vector< vector<int> > marks;
    
    vector<string> findSolution(int N, int C, int D, int S, vector< vector<string> > &tileColors, vector< vector<int> > marks) {
        this->sw = StopWatch();
        this->N = N;
        this->C = C;
        this->D = D;
        this->S = S;
        this->marks = marks;
        
        for (int i = 0; i < 50000; ++i) {
            g_c[i] = i % C;
        }
        
        
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                for (int z = 0; z < 6; ++z) {
                    this->colors[y][x][z] = -1;
                }
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                for (int z = 0; z < this->C; ++z) {
                    this->colors[y][x][z] = ((int)tileColors[y][x][z]) - ((int)'0');
                }
            }
        }
        
        for (int y = 0; y < 50; ++y) {
            for (int x = 0; x < 50; ++x) {
                this->grid[y][x] = -1;
                this->cntgrid[y][x] = 0;
            }
        }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->grid[y][x] = this->colors[y][x][0];
            }
        }
        
        
        
        vector<string> ret(S);
        vector<int> x(D);
        vector<int> y(D);
        ColorCnt cnts = this->fallScoreCnts();
        for (int i = 0; i < D; i++) {
            x[i] = marks[i][0];
            y[i] = marks[i][1];
        }
        for (int i = 1; i <= S; i++) {
            string cmd = "";
            
            for (int j = 0; j < D; j++) {
                int k = 2;
                for (; k < marks[j].size(); k += 3) {
                    if (marks[j][k] >= i) break;
                }
                
                int xd = marks[j][k - 2];
                int yd = marks[j][k - 1];
                if (false && abs(xd - x[j]) > 0 && abs(yd - y[j]) > 0) {
                    int xdd = xd > x[j] ? 1 : -1;
                    int ydd = yd > y[j] ? 1 : -1;
                    
                    ColorCnt acnts = this->testScoreCnts(cnts, x[j] + xdd, y[j], 1);
                    ColorCnt bcnts = this->testScoreCnts(cnts, x[j], y[j] + ydd, 1);
                    if (acnts.score() < bcnts.score()) {
                        cnts = acnts;
                        x[j] += xdd;
                        this->cntgrid[y[j]][x[j]] += 1;
                        cmd += xdd > 0 ? 'R' : 'L';
                    } else {
                        cnts = bcnts;
                        y[j] += ydd;
                        this->cntgrid[y[j]][x[j]] += 1;
                        cmd += ydd > 0 ? 'D' : 'U';
                    }
                    
                    
                } else if (xd > x[j]) {
                    x[j]++;
                    cmd += 'R';
                    cnts = this->testScoreCnts(cnts, x[j], y[j], 1);
                    this->cntgrid[y[j]][x[j]] += 1;
                    
                } else if (xd < x[j]) {
                    x[j]--;
                    cmd += 'L';
                    cnts = this->testScoreCnts(cnts, x[j], y[j], 1);
                    this->cntgrid[y[j]][x[j]] += 1;
                } else if (yd > y[j]) {
                    y[j]++;
                    cmd += 'D';
                    cnts = this->testScoreCnts(cnts, x[j], y[j], 1);
                    this->cntgrid[y[j]][x[j]] += 1;
                } else if (yd < y[j]) {
                    y[j]--;
                    cmd += 'U';
                    cnts = this->testScoreCnts(cnts, x[j], y[j], 1);
                    this->cntgrid[y[j]][x[j]] += 1;
                } else {
                    cmd += '-';
                }
            }
            ret[i - 1] = cmd;
        }
        
        vector<DPath> dpath = this->retConvDPath(ret);
        cnts = this->fallScoreCnts();
        vector<DPath> bestdpath;
        bestdpath = this->SA(9700, dpath, cnts);
        
        
        
        // int score = this->fallScore();
        // pdebug(score);
        // for (int i = 0; i < 50000; ++i) {
        //     this->testScoreCnts(cnts, i%N, i%N, -1);
        // }
        
        // pdebug("c", cnt);
        
        pdebug("N",N,"C",C,"D",D,"S",S);
        pdebug(this->sw.get_milli_time(), cnts.score());
        return this->dpathConvRet(bestdpath);
    }
    
    vector<DPath> SA (int limit, vector<DPath>& dpath, ColorCnt& cnts) {
        StopWatch sw;
        int bestcntgrid[50][50];
        // for (int y = 0; y < this->N; ++y) {
        //     for (int x = 0; x < this->N; ++x) {
        //         bestcntgrid[y][x] = this->cntgrid[y][x];
        //     }
        // }
        
        vector<DPath> bestdpath = dpath;
        ColorCnt bestcnts = cnts;
        
        
        double bestscore = bestcnts.score();
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        double startTemp1 = 128.0;
        int cnt1 = 0;
        int cnt2 = 0;
        mt19937 mt(xrnd());
        bool f = false;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            if (f) {
                startTemp1 = 2;
            } else {
                startTemp1 = 256;
                if (bestscore < 75000) { startTemp1 = 256.0 - 64.0; }
                if (bestscore < 50000) { startTemp1 = 128.0; }
                if (bestscore < 25000) { startTemp1 = 64.0 + 32.0; }
                if (bestscore < 10000) { startTemp1 = 64.0; }
                if (bestscore < 7500) { startTemp1 = 48.0; }
                if (bestscore < 5000) { startTemp1 =  32.0; }
                if (bestscore < 2500) { startTemp1 =   16.0; }
                if (bestscore < 1000) { startTemp1 =   8.0; }
                if (bestscore < 500) { startTemp1 =   4.0; }
                if (bestscore < 100) { startTemp1 =   2.0; }
            }
            
            
            f = false;
            for (int z = 0; z < 100; ++z) {
                int a = xrnd() % dpath.size();
                int size = dpath[a].com.size();
                if (size < 2) { continue; }
                size -= 1;
                int p = xrnd() % size;
                int dr = -1;
                for (; p < size; ++p) {
                    char& c0 = dpath[a].com[p];
                    char& c1 = dpath[a].com[p+1];
                    if (c0 == 'R' && c1 == 'U') { dr = 0; break; }
                    if (c0 == 'R' && c1 == 'D') { dr = 1; break; }
                    if (c0 == 'L' && c1 == 'U') { dr = 2; break; }
                    if (c0 == 'L' && c1 == 'D') { dr = 3; break; }
                    if (c0 == 'U' && c1 == 'R') { dr = 4; break; }
                    if (c0 == 'U' && c1 == 'L') { dr = 5; break; }
                    if (c0 == 'D' && c1 == 'R') { dr = 6; break; }
                    if (c0 == 'D' && c1 == 'L') { dr = 7; break; }
                }
                if (dr < 0) { continue; }
                e512pos pos = dpath[a].pos[p];
                e512pos tpos = dpath[a].pos[p];
                if (dr == 0) {
                    tpos.x -= 1;
                    tpos.y -= 1;
                }
                if (dr == 1) {
                    tpos.x -= 1;
                    tpos.y += 1;
                }
                if (dr == 2) {
                    tpos.x += 1;
                    tpos.y -= 1;
                }
                if (dr == 3) {
                    tpos.x += 1;
                    tpos.y += 1;
                }
                
                if (dr == 4) {
                    tpos.x += 1;
                    tpos.y += 1;
                }
                if (dr == 5) {
                    tpos.x -= 1;
                    tpos.y += 1;
                }
                if (dr == 6) {
                    tpos.x += 1;
                    tpos.y -= 1;
                }
                if (dr == 7) {
                    tpos.x -= 1;
                    tpos.y -= 1;
                }
                
                
                ColorCnt tcnts = this->testScoreCnts(cnts, pos.x, pos.y, -1);
                this->cntgrid[pos.y][pos.x] -= 1;
                tcnts = this->testScoreCnts(tcnts, tpos.x, tpos.y, 1);
                this->cntgrid[tpos.y][tpos.x] += 1;
                
                
                
                
                double tmpscore = tcnts.score();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                
                const double endTemp     = 0.0;
                const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    if (dr == 0) {
                        dpath[a].com[p] = 'U';
                        dpath[a].com[p+1] = 'R';
                    }
                    if (dr == 1) {
                        dpath[a].com[p] = 'D';
                        dpath[a].com[p+1] = 'R';
                    }
                    if (dr == 2) {
                        dpath[a].com[p] = 'U';
                        dpath[a].com[p+1] = 'L';
                    }
                    if (dr == 3) {
                        dpath[a].com[p] = 'D';
                        dpath[a].com[p+1] = 'L';
                    }
                    
                    if (dr == 4) {
                        dpath[a].com[p] = 'R';
                        dpath[a].com[p+1] = 'U';
                    }
                    if (dr == 5) {
                        dpath[a].com[p] = 'L';
                        dpath[a].com[p+1] = 'U';
                    }
                    if (dr == 6) {
                        dpath[a].com[p] = 'R';
                        dpath[a].com[p+1] = 'D';
                    }
                    if (dr == 7) {
                        dpath[a].com[p] = 'L';
                        dpath[a].com[p+1] = 'D';
                    }
                    
                    
                    dpath[a].pos[p] = move(tpos);
                    cnts = move(tcnts);
                    
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestdpath = dpath;
                        bestcnts = cnts;
                        // for (int y = 0; y < this->N; ++y) {
                        //     for (int x = 0; x < this->N; ++x) {
                        //         bestcntgrid[y][x] = this->cntgrid[y][x];
                        //     }
                        // }
                        f = true;
                    }
                } else {
                    this->cntgrid[tpos.y][tpos.x] -= 1;
                    this->cntgrid[pos.y][pos.x] += 1;
                }
                cnt1 += 1;
            }
            
            if ((saTimeCurrent = sw.get_milli_time()) >= saTimeEnd) { break; }
            
            for (int z = 0; z < 128; ++z) {// remove
                int a = xrnd() % dpath.size();
                int size = dpath[a].com.size();
                if (size < abs(dpath[a].sp.x - dpath[a].ep.x) + abs(dpath[a].sp.y - dpath[a].ep.y)) { continue; }
                if (size < 2) { continue; }
                size -= 1;
                int b = xrnd() % size;
                int dr = -1;
                for (; b < size; ++b) {
                    char& c0 = dpath[a].com[b];
                    char& c1 = dpath[a].com[b+1];
                    if (c0 == 'R' && c1 == 'L') { dr = 0; break; }
                    if (c0 == 'L' && c1 == 'R') { dr = 1; break; }
                    if (c0 == 'D' && c1 == 'U') { dr = 2; break; }
                    if (c0 == 'U' && c1 == 'D') { dr = 3; break; }
                }
                if (dr < 0) { continue; }
                
                auto tcom = dpath[a].com;
                vector<e512pos> tpos;
                tcom.erase(tcom.begin() + b, tcom.begin() + b + 2);
                
                e512pos p = dpath[a].sp;
                
                for (auto&& c : tcom) {
                    if (c == 'U') { p.y -= 1; }
                    if (c == 'D') { p.y += 1; }
                    if (c == 'R') { p.x += 1; }
                    if (c == 'L') { p.x -= 1; }
                    //if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
                    tpos.emplace_back(p.x, p.y);
                }
                //if (tcom.size() != tpos.size()) { continue; }
                
                
                ColorCnt tcnts = this->testScoreCnts(cnts, dpath[a].pos[b].x, dpath[a].pos[b].y, -1);
                this->cntgrid[dpath[a].pos[b].y][dpath[a].pos[b].x] -= 1;
                tcnts = this->testScoreCnts(tcnts, dpath[a].pos[b+1].x, dpath[a].pos[b+1].y, -1);
                this->cntgrid[dpath[a].pos[b+1].y][dpath[a].pos[b+1].x] -= 1;
                
                
                
                // for (auto&& i : dpath[a].pos) {
                //     this->cntgrid[i.y][i.x] -= 1;
                // }
                // for (auto&& i : tpos) {
                //     this->cntgrid[i.y][i.x] += 1;
                // }
                // auto tcnts = cnts;
                // tcnts = this->fallScoreCnts();
                
                
                double tmpscore = tcnts.score();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                
                const double endTemp     = 0.0;
                const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    cnts = tcnts;
                    dpath[a].pos = tpos;
                    dpath[a].com = tcom;
                    
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestdpath = dpath;
                        bestcnts = cnts;
                        // for (int y = 0; y < this->N; ++y) {
                        //     for (int x = 0; x < this->N; ++x) {
                        //         bestcntgrid[y][x] = this->cntgrid[y][x];
                        //     }
                        // }
                        f = true;
                    }
                } else {
                    this->cntgrid[dpath[a].pos[b].y][dpath[a].pos[b].x] += 1;
                    this->cntgrid[dpath[a].pos[b+1].y][dpath[a].pos[b+1].x] += 1;
                }
                cnt2 += 1;
            }
            
            for (int z = 0; z < 64; ++z) {// add
                int a = xrnd() % dpath.size();
                int size = dpath[a].com.size();
                if (size >= dpath[a].t-2) { continue; }
                int b = xrnd() % size;
                
                static char i1[] = {'U','D','R','L'};
                static char i2[] = {'D','U','L','R'};
                int xr = xrnd() % 4;
                
                
                auto tcom = dpath[a].com;
                vector<e512pos> tpos;
                tcom.insert(tcom.begin() + b, i2[xr]);
                tcom.insert(tcom.begin() + b, i1[xr]);
                
                e512pos p = dpath[a].sp;
                
                for (auto&& c : tcom) {
                    if (c == 'U') { p.y -= 1; }
                    if (c == 'D') { p.y += 1; }
                    if (c == 'R') { p.x += 1; }
                    if (c == 'L') { p.x -= 1; }
                    if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
                    tpos.emplace_back(p.x, p.y);
                }
                if (tcom.size() != tpos.size()) { continue; }
                // for (auto&& i : dpath[a].pos) {
                //     this->cntgrid[i.y][i.x] -= 1;
                // }
                // for (auto&& i : tpos) {
                //     this->cntgrid[i.y][i.x] += 1;
                // }
                ColorCnt tcnts = this->testScoreCnts(cnts, tpos[b].x, tpos[b].y, +1);
                this->cntgrid[tpos[b].y][tpos[b].x] += 1;
                tcnts = this->testScoreCnts(tcnts, tpos[b+1].x, tpos[b+1].y, +1);
                this->cntgrid[tpos[b+1].y][tpos[b+1].x] += 1;
                
                
                // auto tcnts = cnts;
                // tcnts = this->fallScoreCnts();
                
                
                double tmpscore = tcnts.score();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                
                const double endTemp     = 0.0;
                const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    cnts = tcnts;
                    dpath[a].pos = tpos;
                    dpath[a].com = tcom;
                    
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestdpath = dpath;
                        bestcnts = cnts;
                        // for (int y = 0; y < this->N; ++y) {
                        //     for (int x = 0; x < this->N; ++x) {
                        //         bestcntgrid[y][x] = this->cntgrid[y][x];
                        //     }
                        // }
                        f = true;
                    }
                } else {
                    // this->cntgrid
                    this->cntgrid[tpos[b].y][tpos[b].x] -= 1;
                    this->cntgrid[tpos[b+1].y][tpos[b+1].x] -= 1;
                
                }
                cnt2 += 1;
            }
            
            
            for (int z = 0; z < 4; ++z) {
                int a = xrnd() % dpath.size();
                int size = dpath[a].com.size();
                // int ap = xrnd() % size;
                // int bp = xrnd() % size;
                // if (ap == bp) { continue; }
                // if (ap > bp) { swap(ap, bp); }
                
                // auto tcom = dpath[a].com;
                // vector<e512pos> tpos;
                // swap(tcom[ap], tcom[bp]);
                
                //shuffle(tcom.begin() + ap, tcom.begin() + bp, mt);
                
                if (size < 6) { continue; }
                size -= 5;
                int ap = xrnd() % size;
                auto tcom = dpath[a].com;
                vector<e512pos> tpos;
                shuffle(tcom.begin() + ap, tcom.begin() + ap + 5, mt);
                
                
                e512pos p = dpath[a].sp;
                
                for (auto&& c : tcom) {
                    if (c == 'U') { p.y -= 1; }
                    if (c == 'D') { p.y += 1; }
                    if (c == 'R') { p.x += 1; }
                    if (c == 'L') { p.x -= 1; }
                    if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
                    tpos.emplace_back(p.x, p.y);
                }
                if (tcom.size() != tpos.size()) { continue; }
                for (auto&& i : dpath[a].pos) {
                    this->cntgrid[i.y][i.x] -= 1;
                }
                for (auto&& i : tpos) {
                    this->cntgrid[i.y][i.x] += 1;
                }
                auto tcnts = cnts;
                tcnts = this->fallScoreCnts();
                
                
                double tmpscore = tcnts.score();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                
                const double endTemp     = 0.0;
                const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    cnts = tcnts;
                    dpath[a].pos = tpos;
                    dpath[a].com = tcom;
                    
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestdpath = dpath;
                        bestcnts = cnts;
                        // for (int y = 0; y < this->N; ++y) {
                        //     for (int x = 0; x < this->N; ++x) {
                        //         bestcntgrid[y][x] = this->cntgrid[y][x];
                        //     }
                        // }
                        f = true;
                    }
                } else {
                    // this->cntgrid
                    for (auto&& i : dpath[a].pos) {
                        this->cntgrid[i.y][i.x] += 1;
                    }
                    for (auto&& i : tpos) {
                        this->cntgrid[i.y][i.x] -= 1;
                    }
                }
                cnt2 += 1;
            }
            
            for (int z = 0; z < 4; ++z) {
                int a = xrnd() % dpath.size();
                int size = dpath[a].com.size();
                // int ap = xrnd() % size;
                // int bp = xrnd() % size;
                // if (ap == bp) { continue; }
                // if (ap > bp) { swap(ap, bp); }
                
                // auto tcom = dpath[a].com;
                // vector<e512pos> tpos;
                // swap(tcom[ap], tcom[bp]);
                
                //shuffle(tcom.begin() + ap, tcom.begin() + bp, mt);
                
                if (size < 6) { continue; }
                size -= 5;
                int ap = xrnd() % size;
                auto tcom = dpath[a].com;
                vector<e512pos> tpos;
                swap(tcom[ap], tcom[ap + 5]);
                
                
                e512pos p = dpath[a].sp;
                
                for (auto&& c : tcom) {
                    if (c == 'U') { p.y -= 1; }
                    if (c == 'D') { p.y += 1; }
                    if (c == 'R') { p.x += 1; }
                    if (c == 'L') { p.x -= 1; }
                    if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
                    tpos.emplace_back(p.x, p.y);
                }
                if (tcom.size() != tpos.size()) { continue; }
                for (auto&& i : dpath[a].pos) {
                    this->cntgrid[i.y][i.x] -= 1;
                }
                for (auto&& i : tpos) {
                    this->cntgrid[i.y][i.x] += 1;
                }
                auto tcnts = cnts;
                tcnts = this->fallScoreCnts();
                
                
                double tmpscore = tcnts.score();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                
                const double endTemp     = 0.0;
                const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    cnts = tcnts;
                    dpath[a].pos = tpos;
                    dpath[a].com = tcom;
                    
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestdpath = dpath;
                        bestcnts = cnts;
                        // for (int y = 0; y < this->N; ++y) {
                        //     for (int x = 0; x < this->N; ++x) {
                        //         bestcntgrid[y][x] = this->cntgrid[y][x];
                        //     }
                        // }
                        f = true;
                    }
                } else {
                    // this->cntgrid
                    for (auto&& i : dpath[a].pos) {
                        this->cntgrid[i.y][i.x] += 1;
                    }
                    for (auto&& i : tpos) {
                        this->cntgrid[i.y][i.x] -= 1;
                    }
                }
                cnt2 += 1;
            }
            
            
        }
        dpath = bestdpath;
        cnts = bestcnts;
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                this->cntgrid[y][x] = bestcntgrid[y][x];
            }
        }
        pdebug(cnt1, cnt2);
        return bestdpath;
    }
//
    // vector<DPath> SA (int limit, vector<DPath>& dpath, ColorCnt& cnts) {
    //     StopWatch sw;
    //     int bestcntgrid[50][50];
    //     // for (int y = 0; y < this->N; ++y) {
    //     //     for (int x = 0; x < this->N; ++x) {
    //     //         bestcntgrid[y][x] = this->cntgrid[y][x];
    //     //     }
    //     // }
        
    //     vector<DPath> bestdpath = dpath;
    //     ColorCnt bestcnts = cnts;
        
        
    //     double bestscore = bestcnts.score();
    //     double lastscore = bestscore;
    //     int saTimeStart = sw.get_milli_time();
    //     int saTimeEnd   = limit;
    //     int saTimeCurrent = saTimeStart;
    //     int64_t R = 1000000000;
    //     double startTemp1 = 256.0;
    //     int cnt1 = 0;
    //     int cnt2 = 0;
    //     mt19937 mt(xrnd());
    //     bool f = false;
    //     while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
    //         if (f) {
    //             startTemp1 = 2;
    //         } else {
    //             startTemp1 = 256;
    //             if (bestscore < 100000) { startTemp1 = 128.0; }
    //             if (bestscore < 50000) { startTemp1 = 64.0; }
    //             if (bestscore < 10000) { startTemp1 =  32.0; }
    //             if (bestscore < 5000) { startTemp1 =   16.0; }
    //             if (bestscore < 1000) { startTemp1 =   8.0; }
    //             if (bestscore < 500) { startTemp1 =   4.0; }
    //             if (bestscore < 100) { startTemp1 =   2.0; }
    //         }
    //         f = false;
    //         for (int z = 0; z < 100; ++z) {
    //             int a = xrnd() % dpath.size();
    //             int size = dpath[a].com.size();
    //             if (size < 2) { continue; }
    //             size -= 1;
    //             int p = xrnd() % size;
    //             int dr = -1;
    //             for (; p < size; ++p) {
    //                 char& c0 = dpath[a].com[p];
    //                 char& c1 = dpath[a].com[p+1];
    //                 if (c0 == 'R' && c1 == 'U') { dr = 0; break; }
    //                 if (c0 == 'R' && c1 == 'D') { dr = 1; break; }
    //                 if (c0 == 'L' && c1 == 'U') { dr = 2; break; }
    //                 if (c0 == 'L' && c1 == 'D') { dr = 3; break; }
    //                 if (c0 == 'U' && c1 == 'R') { dr = 4; break; }
    //                 if (c0 == 'U' && c1 == 'L') { dr = 5; break; }
    //                 if (c0 == 'D' && c1 == 'R') { dr = 6; break; }
    //                 if (c0 == 'D' && c1 == 'L') { dr = 7; break; }
    //             }
    //             if (dr < 0) { continue; }
    //             e512pos pos = dpath[a].pos[p];
    //             e512pos tpos = dpath[a].pos[p];
    //             if (dr == 0) {
    //                 tpos.x -= 1;
    //                 tpos.y -= 1;
    //             }
    //             if (dr == 1) {
    //                 tpos.x -= 1;
    //                 tpos.y += 1;
    //             }
    //             if (dr == 2) {
    //                 tpos.x += 1;
    //                 tpos.y -= 1;
    //             }
    //             if (dr == 3) {
    //                 tpos.x += 1;
    //                 tpos.y += 1;
    //             }
                
    //             if (dr == 4) {
    //                 tpos.x += 1;
    //                 tpos.y += 1;
    //             }
    //             if (dr == 5) {
    //                 tpos.x -= 1;
    //                 tpos.y += 1;
    //             }
    //             if (dr == 6) {
    //                 tpos.x += 1;
    //                 tpos.y -= 1;
    //             }
    //             if (dr == 7) {
    //                 tpos.x -= 1;
    //                 tpos.y -= 1;
    //             }
                
                
    //             ColorCnt tcnts = this->testScoreCnts(cnts, pos.x, pos.y, -1);
    //             this->cntgrid[pos.y][pos.x] -= 1;
    //             tcnts = this->testScoreCnts(tcnts, tpos.x, tpos.y, 1);
    //             this->cntgrid[tpos.y][tpos.x] += 1;
                
                
                
                
    //             double tmpscore = tcnts.score();
                
    //             const double T = saTimeEnd-saTimeStart;
    //             const double t = saTimeCurrent-saTimeStart;
                
    //             const double endTemp     = 0.0;
    //             const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
    //             const double probability = exp((lastscore - tmpscore) / temp);
    //             const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
    //             if (tmpscore < lastscore || FORCE_NEXT) {
    //                 if (dr == 0) {
    //                     dpath[a].com[p] = 'U';
    //                     dpath[a].com[p+1] = 'R';
    //                 }
    //                 if (dr == 1) {
    //                     dpath[a].com[p] = 'D';
    //                     dpath[a].com[p+1] = 'R';
    //                 }
    //                 if (dr == 2) {
    //                     dpath[a].com[p] = 'U';
    //                     dpath[a].com[p+1] = 'L';
    //                 }
    //                 if (dr == 3) {
    //                     dpath[a].com[p] = 'D';
    //                     dpath[a].com[p+1] = 'L';
    //                 }
                    
    //                 if (dr == 4) {
    //                     dpath[a].com[p] = 'R';
    //                     dpath[a].com[p+1] = 'U';
    //                 }
    //                 if (dr == 5) {
    //                     dpath[a].com[p] = 'L';
    //                     dpath[a].com[p+1] = 'U';
    //                 }
    //                 if (dr == 6) {
    //                     dpath[a].com[p] = 'R';
    //                     dpath[a].com[p+1] = 'D';
    //                 }
    //                 if (dr == 7) {
    //                     dpath[a].com[p] = 'L';
    //                     dpath[a].com[p+1] = 'D';
    //                 }
                    
                    
    //                 dpath[a].pos[p] = tpos;
    //                 cnts = tcnts;
                    
    //                 lastscore = tmpscore;
    //                 if (tmpscore < bestscore) {
    //                     bestscore = tmpscore;
    //                     bestdpath = dpath;
    //                     bestcnts = cnts;
    //                     // for (int y = 0; y < this->N; ++y) {
    //                     //     for (int x = 0; x < this->N; ++x) {
    //                     //         bestcntgrid[y][x] = this->cntgrid[y][x];
    //                     //     }
    //                     // }
    //                     f = true;
    //                 }
    //             } else {
    //                 this->cntgrid[tpos.y][tpos.x] -= 1;
    //                 this->cntgrid[pos.y][pos.x] += 1;
    //             }
    //             cnt1 += 1;
    //         }
            
            
    //         // for (int z = 0; z < 4; ++z) {
    //         //     int a = xrnd() % dpath.size();
    //         //     int size = dpath[a].com.size();
    //         //     int ap = xrnd() % size;
    //         //     int bp = xrnd() % size;
    //         //     if (ap == bp) { continue; }
    //         //     if (ap > bp) { swap(ap, bp); }
                
    //         //     auto tcom = dpath[a].com;
    //         //     vector<e512pos> tpos;
    //         //     swap(tcom[ap], tcom[bp]);
                
    //         //     //shuffle(tcom.begin() + ap, tcom.begin() + bp, mt);
                
    //         //     // if (size < 5) { continue; }
    //         //     // size -= 4;
    //         //     // int ap = xrnd() % size;
    //         //     // auto tcom = dpath[a].com;
    //         //     // vector<e512pos> tpos;
    //         //     // shuffle(tcom.begin() + ap, tcom.begin() + ap + 4, mt);
                
                
                
                
                
    //         //     e512pos p = dpath[a].sp;
                
    //         //     for (auto&& c : tcom) {
    //         //         if (c == 'U') { p.y -= 1; }
    //         //         if (c == 'D') { p.y += 1; }
    //         //         if (c == 'R') { p.x += 1; }
    //         //         if (c == 'L') { p.x -= 1; }
    //         //         if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
    //         //         tpos.emplace_back(p.x, p.y);
    //         //     }
    //         //     if (tcom.size() != tpos.size()) { continue; }
    //         //     for (auto&& i : dpath[a].pos) {
    //         //         this->cntgrid[i.y][i.x] -= 1;
    //         //     }
    //         //     for (auto&& i : tpos) {
    //         //         this->cntgrid[i.y][i.x] += 1;
    //         //     }
    //         //     auto tcnts = cnts;
    //         //     tcnts = this->fallScoreCnts();
                
                
    //         //     double tmpscore = tcnts.score();
                
    //         //     const double T = saTimeEnd-saTimeStart;
    //         //     const double t = saTimeCurrent-saTimeStart;
                
    //         //     const double endTemp     = 0.0;
    //         //     const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
    //         //     const double probability = exp((lastscore - tmpscore) / temp);
    //         //     const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
    //         //     if (tmpscore < lastscore || FORCE_NEXT) {
    //         //         cnts = tcnts;
    //         //         dpath[a].pos = tpos;
    //         //         dpath[a].com = tcom;
                    
    //         //         lastscore = tmpscore;
    //         //         if (tmpscore < bestscore) {
    //         //             bestscore = tmpscore;
    //         //             bestdpath = dpath;
    //         //             bestcnts = cnts;
    //         //             // for (int y = 0; y < this->N; ++y) {
    //         //             //     for (int x = 0; x < this->N; ++x) {
    //         //             //         bestcntgrid[y][x] = this->cntgrid[y][x];
    //         //             //     }
    //         //             // }
    //         //             f = true;
    //         //         }
    //         //     } else {
    //         //         // this->cntgrid
    //         //         for (auto&& i : dpath[a].pos) {
    //         //             this->cntgrid[i.y][i.x] += 1;
    //         //         }
    //         //         for (auto&& i : tpos) {
    //         //             this->cntgrid[i.y][i.x] -= 1;
    //         //         }
    //         //     }
    //         //     cnt2 += 1;
    //         // }
            
    //         for (int z = 0; z < 8; ++z) {
    //             int a = xrnd() % dpath.size();
    //             int size = dpath[a].com.size();
    //             // int ap = xrnd() % size;
    //             // int bp = xrnd() % size;
    //             // if (ap == bp) { continue; }
    //             // if (ap > bp) { swap(ap, bp); }
                
    //             // auto tcom = dpath[a].com;
    //             // vector<e512pos> tpos;
    //             // swap(tcom[ap], tcom[bp]);
                
    //             //shuffle(tcom.begin() + ap, tcom.begin() + bp, mt);
    //             int bsize = xrnd() % 5 + 2;
    //             if (size < bsize+1) { continue; }
    //             size -= bsize;
    //             int ap = xrnd() % size;
    //             auto tcom = dpath[a].com;
    //             vector<e512pos> tpos;
                
    //             reverse(tcom.begin() + ap, tcom.begin() + ap + bsize);
                
                
    //             e512pos p = dpath[a].sp;
                
    //             for (auto&& c : tcom) {
    //                 if (c == 'U') { p.y -= 1; }
    //                 if (c == 'D') { p.y += 1; }
    //                 if (c == 'R') { p.x += 1; }
    //                 if (c == 'L') { p.x -= 1; }
    //                 if (p.x < 0 || p.x >= this->N || p.y < 0 || p.y >= this->N) { break; }
    //                 tpos.emplace_back(p.x, p.y);
    //             }
    //             if (tcom.size() != tpos.size()) { continue; }
    //             for (auto&& i : dpath[a].pos) {
    //                 this->cntgrid[i.y][i.x] -= 1;
    //             }
    //             for (auto&& i : tpos) {
    //                 this->cntgrid[i.y][i.x] += 1;
    //             }
    //             auto tcnts = cnts;
    //             tcnts = this->fallScoreCnts();
                
                
    //             double tmpscore = tcnts.score();
                
    //             const double T = saTimeEnd-saTimeStart;
    //             const double t = saTimeCurrent-saTimeStart;
                
    //             const double endTemp     = 0.0;
    //             const double temp        = startTemp1 + (endTemp - startTemp1) * t / T;
    //             const double probability = exp((lastscore - tmpscore) / temp);
    //             const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
    //             if (tmpscore < lastscore || FORCE_NEXT) {
    //                 cnts = tcnts;
    //                 dpath[a].pos = tpos;
    //                 dpath[a].com = tcom;
                    
    //                 lastscore = tmpscore;
    //                 if (tmpscore < bestscore) {
    //                     bestscore = tmpscore;
    //                     bestdpath = dpath;
    //                     bestcnts = cnts;
    //                     // for (int y = 0; y < this->N; ++y) {
    //                     //     for (int x = 0; x < this->N; ++x) {
    //                     //         bestcntgrid[y][x] = this->cntgrid[y][x];
    //                     //     }
    //                     // }
    //                     f = true;
    //                 }
    //             } else {
    //                 // this->cntgrid
    //                 for (auto&& i : dpath[a].pos) {
    //                     this->cntgrid[i.y][i.x] += 1;
    //                 }
    //                 for (auto&& i : tpos) {
    //                     this->cntgrid[i.y][i.x] -= 1;
    //                 }
    //             }
    //             cnt2 += 1;
    //         }
    //     }
    //     dpath = bestdpath;
    //     cnts = bestcnts;
        
    //     for (int y = 0; y < this->N; ++y) {
    //         for (int x = 0; x < this->N; ++x) {
    //             this->cntgrid[y][x] = bestcntgrid[y][x];
    //         }
    //     }
    //     pdebug(cnt1, cnt2);
    //     return bestdpath;
    // }
//
    
    vector<DPath> retConvDPath (vector<string>& v) {
        vector<DPath> r;
        for (int d = 0; d < this->D; ++d) {
            int mm = this->marks[d].size() / 3 - 1;
            int endtime = 0;
            for (int m = 0; m < mm; ++m) {
                int m1 = m+1;
                DPath dp;
                dp.d = d;
                dp.index = m;
                dp.t = this->marks[d][m1*3+2] - endtime;
                dp.sp = e512pos(this->marks[d][m*3], this->marks[d][m*3+1]);
                dp.ep = e512pos(this->marks[d][m1*3], this->marks[d][m1*3+1]);
                
                e512pos p = dp.sp;
                for (int t = endtime; t < this->marks[d][m1*3+2]; ++t) {
                    char c = v[t][d];
                    if (c != '-') {
                        dp.com.emplace_back(c);
                        if (c == 'U') { p.y -= 1; }
                        if (c == 'D') { p.y += 1; }
                        if (c == 'R') { p.x += 1; }
                        if (c == 'L') { p.x -= 1; }
                        dp.pos.emplace_back(p.x, p.y);
                    }
                }
                int cnt=0;
                while (dp.com.size() < dp.t - 1) {
                    string s;
                    if (dp.ep.x > 0) { s += "L"; }
                    if (dp.ep.x < this->N-1) { s += "R"; }
                    if (dp.ep.y > 0) { s += "U"; }
                    if (dp.ep.y < this->N-1) { s += "D"; }
                    
                    char c = s[cnt % s.size()];
                    char c2;
                    if (c == 'U') { c2 = 'D'; }
                    if (c == 'D') { c2 = 'U'; }
                    if (c == 'R') { c2 = 'L'; }
                    if (c == 'L') { c2 = 'R'; }
                    dp.com.emplace_back(c);
                    dp.com.emplace_back(c2);
                    e512pos p = dp.ep;
                    if (c == 'U') { p.y -= 1; }
                    if (c == 'D') { p.y += 1; }
                    if (c == 'R') { p.x += 1; }
                    if (c == 'L') { p.x -= 1; }
                    this->cntgrid[p.y][p.x] += 1;
                    this->cntgrid[dp.ep.y][dp.ep.x] += 1;
                    dp.pos.emplace_back(p);
                    dp.pos.emplace_back(dp.ep);
                    cnt += 1;
                }
                
                
                endtime = this->marks[d][m1*3+2];
                r.emplace_back(dp);
                //pdebug(dp.t - dp.com.size());
            }
            //pdebug("-");
        }
        //pdebug("--");
        
        return r;
    }
    
    vector<string> dpathConvRet (vector<DPath>& v) {
        vector<string> r;
        vector<string> tr;
        for (int d = 0; d < this->D; ++d) {
            string s;
            vector<DPath> t;
            for (auto&& i : v) {
                if (i.d != d) { continue; }
                for (auto&& j : i.com) { s += j; }
                for (int j = 0; j < i.t-i.com.size(); ++j) { s += "-"; }
            }
            tr.emplace_back(s);
        }
        for (int t = 0; t < this->S; ++t) {
            string s;
            for (int d = 0; d < this->D; ++d) { s += tr[d][t]; }
            r.emplace_back(s);
        }
        
        return r;
    }
    
    
    int allScore () {
        static int dx[] = {0, 1, 0, -1};
        static int dy[] = {-1, 0, 1, 0};
        int cnts[6];
        bool f[50][50];
        int grid[50][50];
        for (int i = 0; i < 6; ++i) { cnts[i] = 0; }
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                f[y][x] = false;
            }
        }
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y][x] = this->colors[y][x][this->cntgrid[y][x] % this->C];
            }
        }
        
        
        vector<e512pos> q;
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                if (f[y][x]) { continue; }
                int c = grid[y][x];
                cnts[c] += 1;
                q.clear();
                q.emplace_back(x, y);
                f[y][x] = true;
                int s = 0;
                while (s < q.size()) {
                    int e = q.size();
                    for (int i = s; i < e; ++i) {
                        for (int d = 0; d < 4; ++d) {
                            int px = q[i].x + dx[d];
                            int py = q[i].y + dy[d];
                            if (px < 0 || px >= this->N || py < 0 || py >= this->N) { continue; }
                            if (f[py][px] || grid[py][px] != c) { continue; }
                            f[py][px] = true;
                            q.emplace_back(px, py);
                        }
                    }
                    s = e;
                }
                
            }
        }
        int score = 0;
        for (int i = 0; i < 6; ++i) {
            score += cnts[i] * cnts[i];
        }
        return score;
    }
    int fallScore () {
        static int dx[] = {0, 1, 0, -1};
        static int dy[] = {-1, 0, 1, 0};
        int cnts[6];
        bool f[52][52];
        int grid[52][52];
        for (int i = 0; i < 6; ++i) { cnts[i] = 0; }
        for (int y = 1; y <= this->N; ++y) {
            for (int x = 1; x <= this->N; ++x) {
                f[y][x] = false;
            }
        }
        for (int i = 0; i <= this->N+1; ++i) {
            f[0][i] = true;
            f[i][0] = true;
            f[this->N+1][i] = true;
            f[i][this->N+1] = true;
        }
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y+1][x+1] = this->colors[y][x][this->cntgrid[y][x] % this->C];
            }
        }
        
        vector<e512pos> q;
        for (int y = 1; y <= this->N; ++y) {
            for (int x = 1; x <= this->N; ++x) {
                if (f[y][x]) { continue; }
                int c = grid[y][x];
                cnts[c] += 1;
                q.clear();
                q.emplace_back(x, y);
                f[y][x] = true;
                int s = 0;
                while (s < q.size()) {
                    int e = q.size();
                    for (int i = s; i < e; ++i) {
                        for (int d = 0; d < 4; ++d) {
                            int px = q[i].x + dx[d];
                            int py = q[i].y + dy[d];
                            if (f[py][px] || grid[py][px] != c) { continue; }
                            f[py][px] = true;
                            q.emplace_back(px, py);
                        }
                    }
                    s = e;
                }
                
            }
        }
        int score = 0;
        for (int i = 0; i < 6; ++i) {
            score += cnts[i] * cnts[i];
        }
        return score;
    }
    
    
    ColorCnt fallScoreCnts () {
        static int dx[] = {0, 1, 0, -1};
        static int dy[] = {-1, 0, 1, 0};
        static vector<e512pos> q;
        static bool f[52][52];
        static int grid[52][52];
        ColorCnt cnts;
        
        for (int i = 0; i < 6; ++i) { cnts.a[i] = 0; }
        for (int y = 1; y <= this->N; ++y) {
            for (int x = 1; x <= this->N; ++x) {
                f[y][x] = false;
            }
        }
        for (int i = 0; i <= this->N+1; ++i) {
            f[0][i] = true;
            f[i][0] = true;
            f[this->N+1][i] = true;
            f[i][this->N+1] = true;
        }
        
        for (int y = 0; y < this->N; ++y) {
            for (int x = 0; x < this->N; ++x) {
                grid[y+1][x+1] = this->colors[y][x][g_c[this->cntgrid[y][x]]];
            }
        }
        
        
        for (int y = 1; y <= this->N; ++y) {
            for (int x = 1; x <= this->N; ++x) {
                if (f[y][x]) { continue; }
                int c = grid[y][x];
                cnts.a[c] += 1;
                q.clear();
                q.emplace_back(x, y);
                f[y][x] = true;
                int s = 0;
                while (s < q.size()) {
                    int e = q.size();
                    for (int i = s; i < e; ++i) {
                        for (int d = 0; d < 4; ++d) {
                            int px = q[i].x + dx[d];
                            int py = q[i].y + dy[d];
                            if (f[py][px] || grid[py][px] != c) { continue; }
                            f[py][px] = true;
                            q.emplace_back(px, py);
                        }
                    }
                    s = e;
                }
            }
        }
        
        return cnts;
    }
    
    ColorCnt testScoreCnts (ColorCnt cnts, int x, int y, int p) {
        static int dx[] = {0, 1, 0, -1};
        static int dy[] = {-1, 0, 1, 0};
        static bool f[52][52];
        static vector<e512pos> q;
        for (int i = 0; i <= this->N+1; ++i) {
            f[0][i] = true;
            f[i][0] = true;
            f[this->N+1][i] = true;
            f[i][this->N+1] = true;
        }
        
        for (int py = 1; py < this->N+1; ++py) {
            for (int px = 1; px < this->N+1; ++px) {
                f[py][px] = false;
            }
        }
        f[y+1][x+1] = true;
        int c1 = this->colors[y][x][g_c[this->cntgrid[y][x]]];
        int c2 = this->colors[y][x][g_c[this->cntgrid[y][x] + p]];
        
        
        int cnt = 0;
        for (int d = 0; d < 4; ++d) {
            int px = x + dx[d];
            int py = y + dy[d];
            if (f[py+1][px+1]) { continue; }
            int dc = this->colors[py][px][g_c[this->cntgrid[py][px]]];
            if (dc != c1) { continue; }
            cnt += 1;
            q.clear();
            q.emplace_back(px, py);
            f[py+1][px+1] = true;
            int s = 0;
            while (s < q.size()) {
                int e = q.size();
                for (int i = s; i < e; ++i) {
                    for (int d = 0; d < 4; ++d) {
                        const int dpx = q[i].x + dx[d];
                        const int dpy = q[i].y + dy[d];
                        if (f[dpy+1][dpx+1] || this->colors[dpy][dpx][g_c[this->cntgrid[dpy][dpx] ]] != c1) { continue; }
                        f[dpy+1][dpx+1] = true;
                        q.emplace_back(dpx, dpy);
                    }
                }
                s = e;
            }
        }
        
        cnts.a[c1] += -1 + cnt;
        
        for (int py = 1; py < this->N+1; ++py) {
            for (int px = 1; px < this->N+1; ++px) {
                f[py][px] = false;
            }
        }
        cnt = 0;
        for (int d = 0; d < 4; ++d) {
            int px = x + dx[d];
            int py = y + dy[d];
            if (f[py+1][px+1]) { continue; }
            int dc = this->colors[py][px][g_c[this->cntgrid[py][px]]];
            if (dc != c2) { continue; }
            
            cnt += 1;
            q.clear();
            q.emplace_back(px, py);
            f[py+1][px+1] = true;
            int s = 0;
            while (s < q.size()) {
                int e = q.size();
                for (int i = s; i < e; ++i) {
                    for (int d = 0; d < 4; ++d) {
                        int dpx = q[i].x + dx[d];
                        int dpy = q[i].y + dy[d];
                        if (f[dpy+1][dpx+1] || this->colors[dpy][dpx][g_c[this->cntgrid[dpy][dpx]]] != c2) { continue; }
                        f[dpy+1][dpx+1] = true;
                        q.emplace_back(dpx, dpy);
                    }
                }
                s = e;
            }
        }
        
        cnts.a[c2] += 1 - cnt;
        
        return move(cnts);
    }
    
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    int N, C, D, S;
    cin >> N >> C >> D >> S;

    vector< vector<string> > tileColors(N, vector<string>(N));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> tileColors[y][x];
        }
    }

    vector<vector<int>> marks(D);
    for (int i = 0; i < D; i++) {
        int numMarks;
        cin >> numMarks;
        marks[i].resize(3 * numMarks);
        for (int j = 0; j < 3 * numMarks; j++) {
            cin >> marks[i][j];
        }
    }

    DanceFloor sol;
    vector<string> ret = sol.findSolution(N, C, D, S, tileColors, marks);

    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
    cout.flush();
    return 0;
}
