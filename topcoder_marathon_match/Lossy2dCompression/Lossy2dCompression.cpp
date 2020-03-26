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


class Lossy2dCompression {
public:
    int MH = 2;
    int MW = 2;
    double P;
    int N;
    vector< vector<string> > cgrids;
    vector< vector< vector<int> > > grids;
    StopWatch sw;
    int cnt = 0;
    
    // Y X
    
    vector<string> findSolution(double P, int N, vector< vector<string> > grids) {
        if (P > 0.26) {
            return findSolution1(P, N, grids);
        } else {
            return findSolution2(P, N, grids);
        }
    }
    
    
    vector<string> findSolution1(double P, int N, vector< vector<string> > grids) {
        this->sw = StopWatch();
        this->P = P;
        this->N = N;
        this->cgrids = grids;
        
        for (auto&& i : grids) {
            vector< vector<int> > vv;
            for (auto&& j : i) {
                vector<int> v;
                for (auto&& k : j) {
                    v.emplace_back(k-(int)'A');
                }
                vv.emplace_back(v);
            }
            this->grids.emplace_back(vv);
            
        }
        
        //this->setHW();
        this->MH = 100;
        this->MW = 100;
        
        
        vector< vector<int> > out1(this->MH);
        
        for (int r=0; r<this->MH; r++) {
            for (int c=0; c<this->MW; c++) {
                out1[r].emplace_back(xrnd()%26);
            }
        }
        
        vector<e512pos> out2;
        vector<int> pin;
        for (int i = 0; i < this->N; ++i) {
            out2.emplace_back(e512pos(0, 0));
            pin.emplace_back(i);
        }
        
        auto tmpout1 = out1;
        auto tmpout2 = out2;
        auto bestout1 = out1;
        auto bestout2 = out2;
        double bestscore = this->trueScore(out1, out2);
        for (int i = 0; i < 2; ++i) {
            this->setHW();
            this->MH *= 1.0 + i * 0.1;
            this->MW *= 1.0 + i * 0.1;
            out1 = tmpout1;
            out2 = tmpout2;
            this->SA0(0, pin, out1, out2);
            this->SA(600, out1, out2);
            double tscore = this->trueScore(out1, out2);
            if (tscore < bestscore) {
                bestscore = tscore;
                bestout1 = out1;
                bestout2 = out2;
            }
        }
        for (int i = 1; i < 6; ++i) {
            this->setHW();
            this->MH *= 1.2 + i * 0.4;
            this->MW *= 1.2 + i * 0.4;
            out1 = tmpout1;
            out2 = tmpout2;
            this->SA0(0, pin, out1, out2);
            this->SA(600, out1, out2);
            double tscore = this->trueScore(out1, out2);
            if (tscore < bestscore) {
                bestscore = tscore;
                bestout1 = out1;
                bestout2 = out2;
            }
        }
        
        
        
        out1 = bestout1;
        out2 = bestout2;
        
        
        int TMH = 0;
        int TMW = 0;
        for (int i = 0; i < this->N; ++i) {
            TMH = max(TMH, (int)this->grids[i].size()+out2[i].y);
            TMW = max(TMW, (int)this->grids[i][0].size()+out2[i].x);
        }
        
        this->MH = TMH;
        this->MW = TMW;
        if (this->P < 0.16 && this->N > 40) {
            this->MH = TMH + 1;
            this->MW = TMW + 1;
        } else if (this->P < 0.16 && this->N > 60) {
            this->MH = TMH + 2;
            this->MW = TMW + 2;
        }
        this->MH = min(this->MH, 80);
        this->MW = min(this->MW, 80);
        
        auto tout1 = out1;
        auto tout2 = out2;
        double tscore = this->trueScore(out1, out2);
        this->SA(1200, out1, out2);
        if (this->trueScore(out1, out2) < tscore) {
            
        } else {
            out1 = tout1;
            out2 = tout2;
        }
        
        TMH = 0;
        TMW = 0;
        for (int i = 0; i < this->N; ++i) {
            TMH = max(TMH, (int)this->grids[i].size()+out2[i].y);
            TMW = max(TMW, (int)this->grids[i][0].size()+out2[i].x);
        }
        
        this->MH = TMH;
        this->MW = TMW;
        
        this->SA2(9800-this->sw.get_milli_time(), out1, out2);
        
        
        TMH = 0;
        TMW = 0;
        for (int i = 0; i < this->N; ++i) {
            TMH = max(TMH, (int)this->grids[i].size()+out2[i].y);
            TMW = max(TMW, (int)this->grids[i][0].size()+out2[i].x);
        }
        this->MH = TMH;
        this->MW = TMW;
        
        vector<string> ret;
        
        int SH = 100;
        int SW = 100;
        for (int i = 0; i < this->N; ++i) {
            SH = min(SH, out2[i].y);
            SW = min(SW, out2[i].x);
        }
        
        for (int i = SH; i < this->MH; ++i) {
            string t = "";
            for (int j = SW; j < this->MW; ++j) {
                t += (char)((int)'A' + out1[i][j]);
            }
            
            ret.emplace_back(t);
        }
        for (auto&& i : out2) {
            ret.emplace_back(print(i.y-SH, i.x-SW));
        }
        
        
        
        // pdebug(out);
        // pdebug(P, N, grids);
        pdebug(P, N, this->sw.get_milli_time(), this->MH-SH, this->MW-SW, this->cnt);
        return ret;
    }
    
    vector<string> findSolution2(double P, int N, vector< vector<string> > grids) {
        this->sw = StopWatch();
        this->P = P;
        this->N = N;
        this->cgrids = grids;
        
        for (auto&& i : grids) {
            vector< vector<int> > vv;
            for (auto&& j : i) {
                vector<int> v;
                for (auto&& k : j) {
                    v.emplace_back(k-(int)'A');
                }
                vv.emplace_back(v);
            }
            this->grids.emplace_back(vv);
            
        }
        
        //this->setHW();
        this->MH = 1000;
        this->MW = 1000;
        
        
        vector< vector<int> > out1(this->MH);
        
        for (int r=0; r<this->MH; r++) {
            for (int c=0; c<this->MW; c++) {
                out1[r].emplace_back(xrnd()%26);
            }
        }
        
        vector<e512pos> out2;
        vector<int> pin;
        for (int i = 0; i < this->N; ++i) {
            out2.emplace_back(e512pos(0, 0));
            pin.emplace_back(i);
        }
        
        int bestscore = 10000;
        auto bestout1 = out1;
        auto bestout2 = out2;
        for (int i = 0; i < 16; ++i) {
            this->SA02(500, pin, out1, out2, 10+1*i);
            int tscore = this->MH * this->MW;
            if (tscore < bestscore) {
                bestscore = tscore;
                bestout1 = out1;
                bestout2 = out2;
            }
            
        }
        out1 = bestout1;
        out2 = bestout2;
        
        this->MH = 0;
        this->MW = 0;
        for (int i = 0; i < this->N; ++i) {
            this->MH = max(this->MH, (int)this->grids[i].size()+out2[i].y);
            this->MW = max(this->MW, (int)this->grids[i][0].size()+out2[i].x);
        }
        
        
        this->SA2(9800-this->sw.get_milli_time(), out1, out2);
        
        
        this->MH = 0;
        this->MW = 0;
        for (int i = 0; i < this->N; ++i) {
            this->MH = max(this->MH, (int)this->grids[i].size()+out2[i].y);
            this->MW = max(this->MW, (int)this->grids[i][0].size()+out2[i].x);
        }
        
        
        vector<string> ret;
        
        int SH = 1000;
        int SW = 1000;
        for (int i = 0; i < this->N; ++i) {
            SH = min(SH, out2[i].y);
            SW = min(SW, out2[i].x);
        }
        
        for (int i = SH; i < this->MH; ++i) {
            string t = "";
            for (int j = SW; j < this->MW; ++j) {
                t += (char)((int)'A' + out1[i][j]);
            }
            
            ret.emplace_back(t);
        }
        for (auto&& i : out2) {
            ret.emplace_back(print(i.y-SH, i.x-SW));
        }
        
        pdebug(P, N, this->sw.get_milli_time(), this->MH-SH, this->MW-SW, this->cnt);
        return ret;
    }
    
    
    void setHW () {
        this->MH = 0;
        this->MW = 0;
        for (auto&& i : this->grids) {
            this->MH = max(this->MH, (int)i.size());
            this->MW = max(this->MW, (int)i[0].size());
        }
        if (P < 0.08) {
            this->MH *= 2.4;
            this->MW *= 2.4;
        } else if (P < 0.125) {
            this->MH *= 2.2;
            this->MW *= 2.2;
        } else if (P < 0.15) {
            this->MH *= 2.0;
            this->MW *= 2.0;
        } else if (P < 0.25) {
            this->MH *= 1.8;
            this->MW *= 1.8;
        } else if (P < 0.275) {
            this->MH *= 1.4;
            this->MW *= 1.4;
        } else if (P < 0.35) {
            this->MH *= 1.1;
            this->MW *= 1.1;
        }
    }
    
    void SA0 (int limit, vector<int> pin, vector< vector<int> >& out1, vector<e512pos>& out2) {
        StopWatch sw;
        
        vector< vector<int> > bestout1 = out1;
        vector<e512pos> bestout2 = out2;
        double bestscore = this->testSetOut1Out2(pin, out1, out2);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int a = xrnd() % this->N;
                int b = xrnd() % this->N;
                swap(pin[a], pin[b]);
                
                double tmpscore = this->testSetOut1Out2(pin, out1, out2);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 4.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestout1 = out1;
                        bestout2 = out2;
                    }
                } else {
                    swap(pin[a], pin[b]);
                }
            }
            cnt += 1;
        }
        out1 = bestout1;
        out2 = bestout2;
    }
    
    
    void SA (int limit, vector< vector<int> >& out1, vector<e512pos>& out2) {
        StopWatch sw;
        
        vector< vector<int> > bestret = out1;
        vector<e512pos> bestret2 = out2;
        double bestscore = this->testAllScore(out1, out2);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        auto tmp1 = out1;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int a = xrnd() % this->MH;
                int b = xrnd() % this->MW;
                int v = xrnd()%26;
                double tmpscore = lastscore + this->diffScore(out1, out2, a, b, v);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    out1[a][b] = v;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                bestret[y][x] = out1[y][x];
                            }
                        }
                        bestret2 = out2;
                    }
                } else {
                    
                }
                this->cnt += 1;
            }
            for (int z = 0; z < 64; ++z) {
                int a = xrnd() % out2.size();
                auto tmp = out2[a];
                tmp.x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                tmp.y = xrnd() % (this->MH + 1 - this->grids[a].size());
                
                double tmpscore = lastscore + this->diffScore(out1, out2, a, tmp);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    out2[a] = tmp;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                bestret[y][x] = out1[y][x];
                            }
                        }
                        bestret2 = out2;
                    }
                } else {
                    
                }
                this->cnt += 1;
            }
            if (this->P >= 0.3) {
                for (int z = 0; z < 8; ++z) {
                    int a = xrnd() % out2.size();
                    for (int y = 0; y < this->MH; ++y) {
                        for (int x = 0; x < this->MW; ++x) {
                            tmp1[y][x] = out1[y][x];
                        }
                    }
                    auto tmp2 = out2[a];
                    out2[a].x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                    out2[a].y = xrnd() % (this->MH + 1 - this->grids[a].size());
                    const int h = this->grids[a].size();
                    const int w = this->grids[a][0].size();
                    for (int y = 0; y < h; ++y) {
                        for (int x = 0; x < w; ++x) {
                            //out1[out2[a].y+y][out2[a].x+x] = this->grids[a][y][x];
                            this->setC(out1, out2, out2[a].y+y, out2[a].x+x);
                        }
                    }
                    
                    double tmpscore = this->testAllScore(out1, out2);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double startTemp   = 2.0;
                    const double endTemp     = 0.0;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore <= lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            for (int y = 0; y < this->MH; ++y) {
                                for (int x = 0; x < this->MW; ++x) {
                                    bestret[y][x] = out1[y][x];
                                }
                            }
                            bestret2 = out2;
                        }
                    } else {
                        out2[a] = tmp2;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                out1[y][x] = tmp1[y][x];
                            }
                        }
                    }
                    this->cnt += 1;
                }
            } else {
                for (int z = 0; z < 32; ++z) {
                    int a = xrnd() % out2.size();
                    for (int y = 0; y < this->MH; ++y) {
                        for (int x = 0; x < this->MW; ++x) {
                            tmp1[y][x] = out1[y][x];
                        }
                    }
                    auto tmp2 = out2[a];
                    out2[a].x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                    out2[a].y = xrnd() % (this->MH + 1 - this->grids[a].size());
                    const int h = this->grids[a].size();
                    const int w = this->grids[a][0].size();
                    for (int y = 0; y < h; ++y) {
                        for (int x = 0; x < w; ++x) {
                            out1[out2[a].y+y][out2[a].x+x] = this->grids[a][y][x];
                        }
                    }
                    
                    double tmpscore = this->testAllScore(out1, out2);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double startTemp   = 12.0;
                    const double endTemp     = 0.0;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore <= lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            for (int y = 0; y < this->MH; ++y) {
                                for (int x = 0; x < this->MW; ++x) {
                                    bestret[y][x] = out1[y][x];
                                }
                            }
                            bestret2 = out2;
                        }
                    } else {
                        out2[a] = tmp2;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                out1[y][x] = tmp1[y][x];
                            }
                        }
                    }
                    this->cnt += 1;
                }
            }
            
        }
        out1 = bestret;
        out2 = bestret2;
        //return bestret;
        
        for (int y = 0; y < this->MH; ++y) {
            for (int x = 0; x < this->MW; ++x) {
                this->setC(out1, out2, y, x);
            }
        }
    }
    
    
    void SA2 (int limit, vector< vector<int> >& out1, vector<e512pos>& out2) {
        StopWatch sw;
        
        vector< vector<int> > bestret = out1;
        vector<e512pos> bestret2 = out2;
        double bestscore = this->testAllScore(out1, out2);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        bestscore = this->trueScore(out1, out2, lastscore);
        double ttruescore = this->trueScore(out1, out2, lastscore);
        
        auto tmp1 = out1;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int a = xrnd() % this->MH;
                int b = xrnd() % this->MW;
                int v = xrnd()%26;
                double tmpscore = lastscore + this->diffScore(out1, out2, a, b, v);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    out1[a][b] = v;
                    
                    ttruescore = this->trueScore(out1, out2, lastscore);
                    if (ttruescore < bestscore) {
                        bestscore = ttruescore;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                bestret[y][x] = out1[y][x];
                            }
                        }
                        bestret2 = out2;
                    }
                } else {
                    
                }
                this->cnt += 1;
            }
            for (int z = 0; z < 64; ++z) {
                int a = xrnd() % out2.size();
                auto tmp = out2[a];
                tmp.x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                tmp.y = xrnd() % (this->MH + 1 - this->grids[a].size());
                
                double tmpscore = lastscore + this->diffScore(out1, out2, a, tmp);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    out2[a] = tmp;
                    ttruescore = this->trueScore(out1, out2, lastscore);
                    if (ttruescore < bestscore) {
                        bestscore = ttruescore;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                bestret[y][x] = out1[y][x];
                            }
                        }
                        bestret2 = out2;
                    }
                } else {
                    
                }
                this->cnt += 1;
            }
            if (this->P >= 0.3) {
                for (int z = 0; z < 8; ++z) {
                    int a = xrnd() % out2.size();
                    for (int y = 0; y < this->MH; ++y) {
                        for (int x = 0; x < this->MW; ++x) {
                            tmp1[y][x] = out1[y][x];
                        }
                    }
                    auto tmp2 = out2[a];
                    out2[a].x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                    out2[a].y = xrnd() % (this->MH + 1 - this->grids[a].size());
                    const int h = this->grids[a].size();
                    const int w = this->grids[a][0].size();
                    for (int y = 0; y < h; ++y) {
                        for (int x = 0; x < w; ++x) {
                            //out1[out2[a].y+y][out2[a].x+x] = this->grids[a][y][x];
                            this->setC(out1, out2, out2[a].y+y, out2[a].x+x);
                        }
                    }
                    
                    double tmpscore = this->testAllScore(out1, out2);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double startTemp   = 2.0;
                    const double endTemp     = 0.0;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore <= lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        ttruescore = this->trueScore(out1, out2, lastscore);
                        if (ttruescore < bestscore) {
                            bestscore = ttruescore;
                            for (int y = 0; y < this->MH; ++y) {
                                for (int x = 0; x < this->MW; ++x) {
                                    bestret[y][x] = out1[y][x];
                                }
                            }
                            bestret2 = out2;
                        }
                    } else {
                        out2[a] = tmp2;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                out1[y][x] = tmp1[y][x];
                            }
                        }
                    }
                    this->cnt += 1;
                }
            } else {
                for (int z = 0; z < 32; ++z) {
                    int a = xrnd() % out2.size();
                    for (int y = 0; y < this->MH; ++y) {
                        for (int x = 0; x < this->MW; ++x) {
                            tmp1[y][x] = out1[y][x];
                        }
                    }
                    auto tmp2 = out2[a];
                    out2[a].x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                    out2[a].y = xrnd() % (this->MH + 1 - this->grids[a].size());
                    const int h = this->grids[a].size();
                    const int w = this->grids[a][0].size();
                    for (int y = 0; y < h; ++y) {
                        for (int x = 0; x < w; ++x) {
                            out1[out2[a].y+y][out2[a].x+x] = this->grids[a][y][x];
                        }
                    }
                    
                    double tmpscore = this->testAllScore(out1, out2);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double startTemp   = 12.0;
                    const double endTemp     = 0.0;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore <= lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        
                        ttruescore = this->trueScore(out1, out2, lastscore);
                        if (ttruescore < bestscore) {
                            bestscore = ttruescore;
                            for (int y = 0; y < this->MH; ++y) {
                                for (int x = 0; x < this->MW; ++x) {
                                    bestret[y][x] = out1[y][x];
                                }
                            }
                            bestret2 = out2;
                        }
                    } else {
                        out2[a] = tmp2;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                out1[y][x] = tmp1[y][x];
                            }
                        }
                    }
                    this->cnt += 1;
                }
            }
        }
        out1 = bestret;
        out2 = bestret2;
        
        for (int y = 0; y < this->MH; ++y) {
            for (int x = 0; x <this->MW ; ++x) {
                this->setC(out1, out2, y, x);
            }
        }
        //return bestret;
    }
    
    
    void SA3 (int limit, vector< vector<int> >& out1, vector<e512pos>& out2) {
        StopWatch sw;
        
        vector< vector<int> > bestret = out1;
        vector<e512pos> bestret2 = out2;
        double bestscore = this->testAllScore(out1, out2);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        bestscore = this->trueScore(out1, out2, lastscore);
        double ttruescore = this->trueScore(out1, out2, lastscore);
        
        auto tmp1 = out1;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            
            for (int z = 0; z < 64; ++z) {
                int a = xrnd() % out2.size();
                auto tmp = out2[a];
                
                int h = this->grids[a].size();
                int w = this->grids[a][0].size();
                double tmpscore = lastscore;
                for (int y = 0; y < this->MH; ++y) {
                    for (int x = 0; x < this->MW; ++x) {
                        tmpscore -= this->pScore(out2, y, x);
                    }
                }
                out2[a].x = xrnd() % (this->MW + 1 - this->grids[a][0].size());
                out2[a].y = xrnd() % (this->MH + 1 - this->grids[a].size());
                
                for (int y = 0; y < this->MH; ++y) {
                    for (int x = 0; x < this->MW; ++x) {
                        tmpscore += this->pScore(out2, y, x);
                    }
                }
                
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    
                    ttruescore = this->trueScore(out1, out2, lastscore);
                    if (ttruescore < bestscore) {
                        bestscore = ttruescore;
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x <this->MW ; ++x) {
                                this->setC(out1, out2, y, x);
                            }
                        }
                        for (int y = 0; y < this->MH; ++y) {
                            for (int x = 0; x < this->MW; ++x) {
                                bestret[y][x] = out1[y][x];
                            }
                        }
                        bestret2 = out2;
                    }
                } else {
                    out2[a] = tmp;
                }
                this->cnt += 1;
            }
            
            
        }
        out1 = bestret;
        out2 = bestret2;
        
        for (int y = 0; y < this->MH; ++y) {
            for (int x = 0; x <this->MW ; ++x) {
                this->setC(out1, out2, y, x);
            }
        }
        
        //return bestret;
    }
    
    
    void SA02 (int limit, vector<int> pin, vector< vector<int> >& out1, vector<e512pos>& out2, int o) {
        StopWatch sw;
        
        vector< vector<int> > bestout1 = out1;
        vector<e512pos> bestout2 = out2;
        double bestscore = this->xxxx(10, out2, pin);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int a = xrnd() % this->N;
                int b = xrnd() % this->N;
                swap(pin[a], pin[b]);
                
                double tmpscore = this->xxxx(o, out2, pin);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 2.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore <= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        bestout2 = out2;
                    }
                } else {
                    swap(pin[a], pin[b]);
                }
            }
            cnt += 1;
        }
        
        out2 = bestout2;
        
        this->MH = 0;
        this->MW = 0;
        for (int i = 0; i < this->N; ++i) {
            this->MH = max(this->MH, (int)this->grids[i].size()+out2[i].y);
            this->MW = max(this->MW, (int)this->grids[i][0].size()+out2[i].x);
        }
        
        for (int y = 0; y < this->MH; ++y) {
            for (int x = 0; x <this->MW ; ++x) {
                this->setC(out1, out2, y, x);
            }
        }
    }
    
    
    void HC (int limit, vector< vector<int> >& out1, vector<e512pos>& out2) {
        StopWatch sw;
        
        vector< vector<int> > bestret = out1;
        vector<e512pos> bestret2 = out2;
        double bestscore = this->testAllScore(out1, out2);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        auto tmp1 = out1;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int b = 0; b < this->MW; ++b) {
                for (int a = 0; a < this->MH; ++a) {
                    int v = xrnd()%26;
                    double tmpscore = lastscore + this->diffScore(out1, out2, a, b, v);
                    
                    const double T = saTimeEnd-saTimeStart;
                    const double t = saTimeCurrent-saTimeStart;
                    const double startTemp   = 0.0;
                    const double endTemp     = 0.0;
                    const double temp        = startTemp + (endTemp - startTemp) * t / T;
                    const double probability = exp((lastscore - tmpscore) / temp);
                    const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                    
                    if (tmpscore <= lastscore || FORCE_NEXT) {
                        lastscore = tmpscore;
                        out1[a][b] = v;
                        if (tmpscore < bestscore) {
                            bestscore = tmpscore;
                            for (int y = 0; y < this->MH; ++y) {
                                for (int x = 0; x < this->MW; ++x) {
                                    bestret[y][x] = out1[y][x];
                                }
                            }
                            bestret2 = out2;
                        }
                    } else {
                        
                    }
                    this->cnt += 1;
                }
            }
            
        }
        out1 = bestret;
        out2 = bestret2;
        //return bestret;
    }
    
    int testSetOut1Out2 (vector<int>& pin, vector< vector<int> >& out1, vector<e512pos>& out2) {
        for (int r=0; r < this->MH; r++) {
            for (int c = 0; c < this->MW; c++) {
                out1[r][c] = -1;
            }
        }
        for (auto&& i : pin) {
            int h = this->grids[i].size();
            int w = this->grids[i][0].size();
            int bestscore = 10000;
            int bestx = 0;
            int besty = 0;
            for (int y = 0; y < this->MH+1-h; ++y) {
                for (int x = 0; x < this->MW+1-w; ++x) {
                    int tscore = this->testScore0(i, h, w, y, x, out1);
                    if (tscore < bestscore) {
                        besty = y;
                        bestx = x;
                        bestscore = tscore;
                    }
                }
            }
            out2[i].x = bestx;
            out2[i].y = besty;
            this->addColors(i, h, w, besty, bestx, out1);
        }
        for (int r = 0; r < this->MH; r++) {
            for (int c = 0; c < this->MW; c++) {
                if (out1[r][c] < 0) { out1[r][c] = xrnd()%26; }
            }
        }
        return this->testAllScore(out1, out2);
    }
    
    int testScore0 (int i, int h, int w, int sy, int sx, vector< vector<int> >& b) {
        int score = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (this->grids[i][y][x] < 0) {
                    // score += (sy+y+sx+x)/8;
                } else {
                    score += abs(this->grids[i][y][x] - b[sy+y][sx+x]);
                }
            }
        }
        return score;
    }
    void addColors (int i, int h, int w, int sy, int sx, vector< vector<int> >& b) {
        int score = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (this->grids[i][y][x] < 0) {
                    b[sy+y][sx+x] = this->grids[i][y][x];
                } else {
                    b[sy+y][sx+x] = (b[sy+y][sx+x] + this->grids[i][y][x]) / 2;
                }
            }
        }
    }
    
    int testScore (vector<string>& a, int h, int w, int sy, int sx, vector< vector<int> >& b) {
        int score = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                score += abs(a[y][x] - b[sy+y][sx+x]);
            }
        }
        return score;
    }
    int testAllScore (vector< vector<int> >& out1, vector<e512pos>& out2) {
        int score = 0;
        for (int i = 0; i < N; ++i) {
            const int h = this->grids[i].size();
            const int w = this->grids[i][0].size();
            const int sx = out2[i].x;
            const int sy = out2[i].y;
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    score += abs(this->grids[i][y][x] - out1[sy+y][sx+x]);
                }
            }
        }
        return score;
    }
    
    int diffScore (vector< vector<int> >& out1, vector<e512pos>& out2, int py, int px, int v) {
        int score = 0;
        
        for (int i = 0; i < N; ++i) {
            const int h = this->grids[i].size();
            const int w = this->grids[i][0].size();
            const int sx = out2[i].x;
            const int sy = out2[i].y;
            if (sy <= py && py < sy + h && sx <= px && px < sx + w) {
                score -= abs(this->grids[i][py-sy][px-sx] - out1[py][px]);
                score += abs(this->grids[i][py-sy][px-sx] - v);
            }
            
        }
        return score;
    }
    
    int diffScore (vector< vector<int> >& out1, vector<e512pos>& out2, int i, e512pos& p) {
        int score = 0;
        const int h = this->grids[i].size();
        const int w = this->grids[i][0].size();
        {
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    score -= abs(this->grids[i][y][x] - out1[out2[i].y+y][out2[i].x+x]);
                }
            }
        }
        {
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    score += abs(this->grids[i][y][x] - out1[p.y+y][p.x+x]);
                }
            }
        }
        return score;
    }
    
    double trueScore (vector< vector<int> >& out1, vector<e512pos>& out2) {
        int H = 0;
        int W = 0;
        int T = 0;
        for (int i = 0; i < this->N; ++i) {
            H = max(H, (int)this->grids[i].size()+out2[i].y);
            W = max(W, (int)this->grids[i][0].size()+out2[i].x);
            T += this->grids[i].size() * this->grids[i][0].size();
        }
        double compressionScore  = (double)(H*W) / T * this->P;
        double lossinessScore = this->testAllScore(out1, out2) / (12.5 * T) * (1.0 - this->P);
        
        return compressionScore + lossinessScore;
    }
    
    double trueScore (vector< vector<int> >& out1, vector<e512pos>& out2, double score) {
        int H = 0;
        int W = 0;
        int T = 0;
        for (int i = 0; i < this->N; ++i) {
            H = max(H, (int)this->grids[i].size()+out2[i].y);
            W = max(W, (int)this->grids[i][0].size()+out2[i].x);
            T += this->grids[i].size() * this->grids[i][0].size();
        }
        double compressionScore  = (double)(H*W) / T * this->P;
        double lossinessScore = score / (12.5 * T) * (1.0 - this->P);
        
        return compressionScore + lossinessScore;
    }
    
    int pScore (vector<e512pos>& out2, int py, int px) {
        static vector<int> iv = vector<int>(100, 0);
        iv.clear();
        int score = 0;
        for (int i = 0; i < N; ++i) {
            const int h = this->grids[i].size();
            const int w = this->grids[i][0].size();
            const int sx = out2[i].x;
            const int sy = out2[i].y;
            if (sy <= py && py < sy + h && sx <= px && px < sx + w) {
                iv.emplace_back(this->grids[i][py-sy][px-sx]);
            }
        }
        if (iv.size() > 0) {
            sort(iv.begin(), iv.end());
            int v = iv[iv.size()/2];
            for (auto&& i : iv) {
                score += abs(i - v);
            }
        }
        return score;
    }
    int setC (vector< vector<int> >& out1, vector<e512pos>& out2, int py, int px) {
        static vector<int> iv = vector<int>(100, 0);
        iv.clear();
        int score = 0;
        for (int i = 0; i < N; ++i) {
            const int h = this->grids[i].size();
            const int w = this->grids[i][0].size();
            const int sx = out2[i].x;
            const int sy = out2[i].y;
            if (sy <= py && py < sy + h && sx <= px && px < sx + w) {
                iv.emplace_back(this->grids[i][py-sy][px-sx]);
            }
        }
        if (iv.size() > 0) {
            sort(iv.begin(), iv.end());
            out1[py][px] = iv[iv.size()/2];
        }
        
    }
    
    
    int xxxx (int maxh, vector<e512pos>& out2, vector<int>& pin) {
        static vector<int> ws = vector<int>(200, 0);
        for (int i = 0; i < maxh; ++i) { ws[i] = 0; }
        
        int maxw = 0;
        
        for (auto&& i : pin) {
            const int h = this->grids[i].size();
            const int w = this->grids[i][0].size();
            int best = 0;
            int bestscore = 10000;
            int d = maxh + 1 - h;
            for (int y = 0; y < d; ++y) {
                int score = 0;
                for (int yy = 0; yy < h; ++yy) {
                    score = max(score, ws[yy+y]);
                }
                if (score < bestscore) {
                    bestscore = score;
                    best = y;
                }
            }
            
            out2[i].x = bestscore;
            out2[i].y = best;
            maxw = max(bestscore, maxw);
            for (int y = 0; y < h; ++y) {
                ws[best + y] = bestscore + w;
            }
            
        }
        
        return maxw * maxh;
    }
    
};

int main() {
    double P;
    cin >> P;
    int N;
    cin >> N;
    vector< vector<string> > grids;
    for (int i=0;i<N;i++) {
        int H;
        cin >> H;
        vector<string> grid(H);
        for (int y=0;y<H;y++) {
            cin >> grid[y];
        }
        grids.push_back(grid);
    }
    
    Lossy2dCompression prog;
    vector<string> ret = prog.findSolution(P, N, grids);
    cout << ret.size()-N << endl;
    for (int i=0;i<ret.size();i++) {
        cout << ret[i] << endl;
    }
    cout.flush();
}
