// C++11
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <time.h>
#include <sys/timeb.h>

#include <string>
#include <array>
#include <cstdlib>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <random>
#include <utility>
using namespace std;

string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char *v) { return '"' + v + '"'; }
string in_v_to_str (const string v) { return '"' + v + '"'; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N> &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; }
        ss << in_v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[]";
    }
    return ss.str();
}
template<class T, size_t N> string v_to_str (const array< array<T, N>, N > &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; }
        ss << v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[-]";
    }
    return ss.str();
}
template<class T> string v_to_str (const vector<T> &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; }
        ss << in_v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[]";
    }
    return ss.str();
}
template<class T> string v_to_str (const vector< vector<T> > &v) {
    stringstream ss;
    if (v.size() > 0) {
        ss << "[";
        for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; }
        ss << v_to_str(v[v.size() - 1]) << "]";
    } else {
        ss << "[-]";
    }
    return ss.str();
}
template<class T> string v_to_str (const set<T> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class K, class V> string v_to_str (const map<K, V> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class T> string v_to_str (const unordered_set<T> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
template<class K, class V> string v_to_str (const unordered_map<K, V> &v) {
    stringstream ss;
    int len = v.size();
    ss << (v.size() > 0 ? "{" : "{}");
    for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); }
    return ss.str();
}
string print () { return ""; }
template<typename F, typename... R> string print (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f);
    if (sizeof...(r) > 0) { ss << " " << print(r...); }
    return ss.str();
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

//////
inline double distance (const double &ax, const double &ay, const double &bx, const double &by) {
    // return hypot(ax - bx, ay - by);
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline double distance (const int &ax, const int &ay, const int &bx, const int &by) {
    // return hypot(ax - bx, ay - by);
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

int cnt = 0;

class RoadsAndJunctions {
public:
    
    class mgraph {
    public:
        vector< pair<int, int> > g;// index inxex
        vector< pair<int, pair<int, int> > > s;// vpindex x y
        
        mgraph (int vpi, int x, int y) {
            this->s.emplace_back(vpi, make_pair(x, y));
        }
        
        void add_graph (int a, int b) { this->g.emplace_back(a, b); }
        
        void gunion (mgraph &bg) {
            for (auto &i : bg.g) { this->g.emplace_back(i); }
            for (auto &i : bg.s) { this->s.emplace_back(i); }
        }
        
        int size () { return this->s.size(); }
        
        double mindist (RoadsAndJunctions &out, mgraph tg, int &ti, int &mi) {
            double dist = 2000;
            for (auto &a : this->s) {
                for (auto &b : tg.s) {
                    double tdist = out.tdistance(a.second.first, a.second.second, b.second.first, b.second.second);
                    if (tdist < dist) {
                        dist = tdist;
                        mi = a.first;
                        ti = b.first;
                    }
                    
                }
            }
            return dist;
        }
    };
    
    int NC;
    int S;
    vector<int> bp;// blank
    StopWatch sw;
    vector< pair<int, int> > junctions;// index, pos
    vector< pair<int, int> > ip_cities;
    
    vector<int> cities;
    
    vector< pair<int, int> > cities_graph;
    
    vector<int> bmap;
    vector<int> bmap2;
    
    vector< vector<double> > distmap;
    
    vector<int> buildJunctions (int S, vector<int> cities, double junctionCost, double failureProbability) {
        vector<int> ret;
        S += 1;
        this->S = S;
        this->init_distmap();
        this->NC = cities.size() / 2;
        this->cities = cities;
        this->ip_cities = this->init_cities();
        
        
        int pl = S / 2, pr = S / 2, pu = S / 2, pd = S / 2;
        this->bmap = vector<int>(S*S, 1);
        for (int i = 0; i < this->NC; ++i) {
            const int x = cities[2 * i];
            const int y = cities[2 * i + 1];
            this->bmap[x + y * S] = 0;
            pl = min(pl, x);
            pr = max(pr, x);
            pu = min(pu, y);
            pd = max(pd, y);
            
        }
        this->bmap2 = this->bmap;
        for (int i = 0; i < S * S; ++i) {
            int x = i % S;
            int y = i / S;
            if (!(pl < x && x < pr && pu < y && y < pd)) { this->bmap2[i] = 0; }
        }
        
        if ((this->NC > 30 && S > 400) || this->NC > 70) {
            for (int i = 0; i < S * S; ++i) {
                int x = i % S;
                int y = i / S;
                if (x%2<1 && y%2<1 &&this->bmap2[i] == 1) { this->bp.emplace_back(i); }
            }
        } else {
            for (int i = 0; i < S * S; ++i) {
                if (this->bmap2[i] == 1) { this->bp.emplace_back(i); }
            }
        }
        this->cities_graph = this->ip_to_graph(this->ip_cities);
        
        if (this->NC < 60) {
            ret = this->buildJunctionsA(S, cities,junctionCost, failureProbability);
        } else {
            ret = this->buildJunctionsB(S, cities,junctionCost, failureProbability);
        }
        
        //cerr << "cnt:" << cnt << endl;
        
        return ret;
    }
    
    
    vector<int> buildJunctionsA (int S, vector<int> cities, double junctionCost, double failureProbability) {
        //this->sw = StopWatch();
        vector<int> ret;
        
        vector<int> v = this->bmap;
        vector<int> vf = this->bmap2;
        
        auto vps = this->init_vps();
        
        double iscore = this->all_distance(this->cities_graph, vps);
        double score = iscore;
        int tnt = 0;
        vector<int> putpos;
        int tpos = -1;
        int timer = this->sw.get_milli_time();
        int loop = 30;
        
        int nx = (5126 * 32) / this->NC;
        if (this->NC > 30) { nx = (5126 * 32 / 2) / this->NC; }
        if (this->NC > 50) { nx = (5126 * 28 / 3) / this->NC; }
        if (this->NC > 70) { nx = (5126 * 24 / 3) / this->NC; }
        if (this->NC > 90) { nx = (5126 * 20 / 3) / this->NC; }
        
        double jc = junctionCost * (1.0 + failureProbability);//;
        score -= jc;
        
        while(timer < 9000){
            if (cnt > 1000 && timer < 1000) { loop = 100; }
            if (cnt > 10000 && timer < 1000) { loop = 1000; }
            for (int z = 0; z < loop; ++z) {
                int a = xrnd()%this->bp.size();
                int p = this->bp[a];
                if (vf[p] == 0) { continue; }
                auto tvps = this->add_vps(vps, p);
                auto g = this->ip_to_graph(tvps);
                double tscore = this->all_distance(g, tvps);
                if (tscore < score) {
                    score = tscore;
                    tpos = p;
                }
                cnt += 1;
                tnt += 1;
            }
            
            if (tnt > nx) {
                if (tpos > -1) {
                    putpos.emplace_back(tpos);
                    vps = this->add_vps(vps, tpos);
                    vf[tpos] = 0;
                    score -= jc;
                }
                tpos = -1;
                tnt = 0;
            }
            if (putpos.size() > this->NC) { break; }
            timer = this->sw.get_milli_time();
        }
        
        // if (tpos > -1) {
        //     putpos.emplace_back(tpos);
        //     vps = this->add_vps(vps, tpos);
        //     tpos = -1;
        //     vf[tpos] = 0;
        // }
        
        vector<int> dx = {-1, 1, 0, 0, -1, 1, -1, 1};
        vector<int> dy = {0, 0, -1, 1, -1, 1, 1, -1};
        {
            vps = this->init_vps();
            vector<int> ps;
            vector<int> tps;
            score = iscore - jc;
            int zloop = 24;
            for (int k = 0; k < putpos.size(); ++k) {
                if (this->sw.get_milli_time() > 9500) { zloop = 8; }
                if (this->sw.get_milli_time() > 9800) { break; }
                if (ret.size() / 2 > this->NC * 2 - 16) { break; }
                ps = tps;
                if (putpos[k] > -1 && v[putpos[k]] == 1) {
                    
                    ps.emplace_back(putpos[k]);
                    auto tvps = this->add_vps(vps, ps);
                    auto g = this->ip_to_graph(tvps);
                    double bestscore = this->all_distance(g, tvps);
                    int bestprevpos = -1;
                    
                    for (int z = 0; z < zloop; ++z) {
                        bool f = false;
                        int x = putpos[k] % this->S;
                        int y = putpos[k] / this->S;
                        
                        for (int p = 0; p < 4; ++p) {
                            const int px = x + dx[p];
                            const int py = y + dy[p];
                            const int ipos = px + py * S;
                            if (bestprevpos == ipos) { continue; }
                            if (px > -1 && px < S && py > -1 && py < S && v[ipos] == 1) {
                                auto zps = tps;
                                zps.emplace_back(ipos);
                                auto ztvps = this->add_vps(vps, zps);
                                auto zg = this->ip_to_graph(ztvps);
                                double tscore = this->all_distance(zg, ztvps);
                                if (tscore < bestscore) {
                                    bestscore = tscore;
                                    bestprevpos = putpos[k];
                                    putpos[k] = ipos;
                                    f = true;
                                    break;
                                }
                            }
                        }
                        if (f = false) { break; }
                    }
                    
                    if (bestprevpos > -1 && (score - bestscore - 2) > junctionCost * 3 && failureProbability > 0.1) {
                        const int px = bestprevpos % this->S;
                        const int py = bestprevpos / this->S;
                        if (px > -1 && px < S && py > -1 && py < S) {
                            if (v[px + py * S] == 1) {
                                ret.emplace_back(px);
                                ret.emplace_back(py);
                                v[px + py * S] = 0;
                            }
                        }
                    } else if ((score - bestscore - 2) > junctionCost * 3 && failureProbability > 0.1) {
                        int x = putpos[k] % this->S;
                        int y = putpos[k] / this->S;
                        
                        for (int i = 0; i < 4; ++i) {
                            const int px = x + dx[i];
                            const int py = y + dy[i];
                            if (px > -1 && px < S && py > -1 && py < S) {
                                if (v[px + py * S] == 1) {
                                    ret.emplace_back(px);
                                    ret.emplace_back(py);
                                    v[px + py * S] = 0;
                                    break;
                                }
                            }
                        }
                    }
                    
                    // if (bestscore < score - junctionCost || k < putpos.size() - 3) {
                        score = bestscore - jc;
                        ret.emplace_back(putpos[k] % this->S);
                        ret.emplace_back(putpos[k] / this->S);
                        tps.emplace_back(putpos[k]);
                    
                        v[putpos[k]] = 0;
                    // }
                }
            }
        }
        
        
        this->junctions = this->ret_to_junctions(ret);
        return ret;
    }
    
    vector<int> buildJunctionsB (int S, vector<int> cities, double junctionCost, double failureProbability) {
        //this->sw = StopWatch();
        vector<int> ret;
        
        vector<int> v = this->bmap;
        vector<int> vf = this->bmap2;
        
        auto vps = this->init_vps();
        
        double iscore = this->all_distance(this->cities_graph, vps);
        double score = iscore;
        int tnt = 0;
        vector<int> putpos;
        int tpos = -1;
        int timer = this->sw.get_milli_time();
        int loop = 30;
        
        int nx = (5126 * 32) / this->NC;
        if (this->NC > 30) { nx = (5126 * 32 / 2) / this->NC; }
        if (this->NC > 50) { nx = (5126 * 28 / 3) / this->NC; }
        if (this->NC > 70) { nx = (5126 * 24 / 3) / this->NC; }
        if (this->NC > 90) { nx = (5126 * 20 / 3) / this->NC; }
        
        double jc = junctionCost * (1.0 + failureProbability);//;
        score -= jc;
        
        while(timer < 6500){
            if (cnt > 1000 && timer < 1000) { loop = 100; }
            if (cnt > 10000 && timer < 1000) { loop = 1000; }
            for (int z = 0; z < loop; ++z) {
                int a = xrnd()%this->bp.size();
                int p = this->bp[a];
                if (vf[p] == 0) { continue; }
                auto tvps = this->add_vps(vps, p);
                auto g = this->ip_to_graph(tvps);
                double tscore = this->all_distance(g, tvps);
                if (tscore < score) {
                    score = tscore;
                    tpos = p;
                }
                cnt += 1;
                tnt += 1;
            }
            
            if (tnt > nx) {
                if (tpos > -1) {
                    putpos.emplace_back(tpos);
                    vps = this->add_vps(vps, tpos);
                    vf[tpos] = 0;
                    score -= jc;
                }
                tpos = -1;
                tnt = 0;
            }
            if (putpos.size() > this->NC) { break; }
            timer = this->sw.get_milli_time();
        }
        nx /= 2;
        while(timer < 8500){
            for (int z = 0; z < loop; ++z) {
                int a = xrnd()%this->bp.size();
                int p = this->bp[a];
                if (vf[p] == 0) { continue; }
                auto tvps = this->add_vps(vps, p);
                auto g = this->ip_to_graph(tvps);
                double tscore = this->all_distance(g, tvps);
                if (tscore < score) {
                    score = tscore;
                    tpos = p;
                }
                cnt += 1;
                tnt += 1;
            }
            
            if (tnt > nx) {
                if (tpos > -1) {
                    putpos.emplace_back(tpos);
                    vps = this->add_vps(vps, tpos);
                    vf[tpos] = 0;
                    score -= jc;
                }
                tpos = -1;
                tnt = 0;
            }
            if (putpos.size() > this->NC) { break; }
            timer = this->sw.get_milli_time();
        }
        
        vector<int> dx = {-1, 1, 0, 0, -1, 1, -1, 1};
        vector<int> dy = {0, 0, -1, 1, -1, 1, 1, -1};
        {
            vps = this->init_vps();
            vector<int> ps;
            vector<int> tps;
            score = iscore - jc;
            int zloop = 24;
            for (int k = 0; k < putpos.size(); ++k) {
                if (this->sw.get_milli_time() > 9500) { zloop = 8; }
                if (this->sw.get_milli_time() > 9800) { break; }
                if (ret.size() / 2 > this->NC * 2 - 16) { break; }
                ps = tps;
                if (putpos[k] > -1 && v[putpos[k]] == 1) {
                    
                    ps.emplace_back(putpos[k]);
                    auto tvps = this->add_vps(vps, ps);
                    auto g = this->ip_to_graph(tvps);
                    double bestscore = this->all_distance(g, tvps);
                    int bestprevpos = -1;
                    
                    for (int z = 0; z < zloop; ++z) {
                        bool f = false;
                        int x = putpos[k] % this->S;
                        int y = putpos[k] / this->S;
                        
                        for (int p = 0; p < 4; ++p) {
                            const int px = x + dx[p];
                            const int py = y + dy[p];
                            const int ipos = px + py * S;
                            if (bestprevpos == ipos) { continue; }
                            if (px > -1 && px < S && py > -1 && py < S && v[ipos] == 1) {
                                auto zps = tps;
                                zps.emplace_back(ipos);
                                auto ztvps = this->add_vps(vps, zps);
                                auto zg = this->ip_to_graph(ztvps);
                                double tscore = this->all_distance(zg, ztvps);
                                if (tscore < bestscore) {
                                    bestscore = tscore;
                                    bestprevpos = putpos[k];
                                    putpos[k] = ipos;
                                    f = true;
                                    break;
                                }
                            }
                        }
                        if (f = false) { break; }
                    }
                    
                    if (bestprevpos > -1 && (score - bestscore - 2) > junctionCost * 3 && failureProbability > 0.1) {
                        const int px = bestprevpos % this->S;
                        const int py = bestprevpos / this->S;
                        if (px > -1 && px < S && py > -1 && py < S) {
                            if (v[px + py * S] == 1) {
                                ret.emplace_back(px);
                                ret.emplace_back(py);
                                v[px + py * S] = 0;
                            }
                        }
                    } else if ((score - bestscore - 2) > junctionCost * 3 && failureProbability > 0.1) {
                        int x = putpos[k] % this->S;
                        int y = putpos[k] / this->S;
                        
                        for (int i = 0; i < 4; ++i) {
                            const int px = x + dx[i];
                            const int py = y + dy[i];
                            if (px > -1 && px < S && py > -1 && py < S) {
                                if (v[px + py * S] == 1) {
                                    ret.emplace_back(px);
                                    ret.emplace_back(py);
                                    v[px + py * S] = 0;
                                    break;
                                }
                            }
                        }
                    }
                    
                    // if (bestscore < score - junctionCost || k < putpos.size() - 3) {
                        score = bestscore - jc;
                        ret.emplace_back(putpos[k] % this->S);
                        ret.emplace_back(putpos[k] / this->S);
                        tps.emplace_back(putpos[k]);
                    
                        v[putpos[k]] = 0;
                    // }
                }
            }
        }
        
        this->junctions = this->ret_to_junctions(ret);
        return ret;
    }
    
    
    void init_distmap () {
        this->distmap = vector< vector<double> >(2048, vector<double>(2048, 2000));
        
        for (int x = 0; x < this->S; ++x) {
            for (int y = 0; y < this->S; ++y) {
                double d = distance(0, 0, x, y);
                this->distmap[1024 + x][1024 + y] = d;
                this->distmap[1024 - x][1024 + y] = d;
                this->distmap[1024 + x][1024 - y] = d;
                this->distmap[1024 - x][1024 - y] = d;
            }
        }
    }
    
    inline double tdistance (const int ax, const int ay, const int bx, const int by) {
        const int x = 1024 + ax - bx;
        const int y = 1024 + ay - by;
        return this->distmap[x][y];
    }
    
    inline double all_distance (const vector< pair<int, int> > &g, const vector<int> &vps) {
        double d = 0;
        int ax, ay, bx, by;
        for (auto &i : g) {
            ax = vps[i.first] % this->S;
            ay = vps[i.first] / this->S;
            bx = vps[i.second] % this->S;
            by = vps[i.second] / this->S;
            d += this->tdistance(ax, ay, bx, by);
        }
        return d;
    }
    
    // args index, index
    // return index cnt
    vector<int> road_cnt_pos (vector< pair<int, int> > &road) {
        vector<int> r(this->NC, 0);
        for (auto &i : road) {
            r[i.first] += 1;
            r[i.second] += 1;
        }
        return r;
    }
    
    vector< pair<int, int> > init_cities () {
        vector< pair<int, int> > j;
        for(int i = 0; i < this->cities.size() / 2; i++) {
            const int cx = this->cities[2 * i];
            const int cy = this->cities[2 * i + 1];
            j.emplace_back(i, cx + cy * this->S);
        }
        return j;
    }
    
    vector< pair<int, int> > ret_to_junctions (const vector<int> &ret) {
        vector< pair<int, int> > j;
        for(int i = 0; i < ret.size() / 2; i++) {
            const int cx = ret[2 * i];
            const int cy = ret[2 * i + 1];
            j.emplace_back(i + this->NC, cx + cy * this->S);
        }
        return j;
    }
    
    inline vector< pair<int, int> > ip_to_graph (const vector< pair<int, int> > &ip) {
        unordered_map<int, pair<int, int>> mip;
        for (auto& i : ip) { mip.emplace(i.first, make_pair(i.second % S, i.second / S)); }
        vector< pair<int, int> > r;
        vector< pair<int, pair<int, int> > > s;
        s.emplace_back(0, mip[0]);
        mip.erase(0);
        int S = this->S;
        while (s.size() < ip.size()) {
            int ii = -1;
            pair<int, pair<int, int> > mm;
            double dist = 2000;
            for (int i = 0; i < s.size(); ++i) {
                const int sx = s[i].second.first;
                const int sy = s[i].second.second;
                for (auto& m : mip) {
                    const int px = m.second.first;
                    const int py = m.second.second;
                    const double tdist = this->tdistance(sx, sy, px, py);
                    if (tdist < dist) {
                        dist = tdist;
                        ii = s[i].first;
                        mm = m;
                    }
                }
            }
            if (ii < 0)  { return r; }
            r.emplace_back(ii, mm.first);
            s.emplace_back(mm);
            mip.erase(mm.first);
        }
        
        return r;
    }
    
    unordered_map<int, pair<int, int> > mip;
    vector< pair<int, int> > gret;
    vector< pair<int, pair<int, int> > > setv;
    inline vector< pair<int, int> > ip_to_graph (const vector<int> &vp) {
        this->gret.clear();
        this->setv.clear();
        this->mip.clear();
        for (int i = 1; i < vp.size(); ++i) {
            this->mip.emplace(i, make_pair(vp[i] % S, vp[i] / S)); 
        }
        
        
        this->setv.emplace_back(0, make_pair(vp[0] % S, vp[0] / S));
        this->mip.erase(0);
        int S = this->S;
        while (setv.size() < vp.size()) {
            int ii = -1;
            pair<int, pair<int, int> > mm;
            double dist = 2000;
            // for (int i = 0; i < s.size(); ++i) {
            //     const int sx = s[i].second.first;
            //     const int sy = s[i].second.second;
            for (auto &t : this->setv) {
                for (auto& m : this->mip) {
                    const int px = m.second.first;
                    const int py = m.second.second;
                    const double tdist = this->tdistance(t.second.first, t.second.second, px, py);
                    if (tdist < dist) {
                        dist = tdist;
                        ii = t.first;
                        mm = m;
                    }
                }
            }
            // if (ii < 0)  { return r; }
            this->gret.emplace_back(ii, mm.first);
            this->setv.emplace_back(mm);
            this->mip.erase(mm.first);
        }
        return this->gret;
    }
    
    inline vector< pair<int, int> > ip_to_graph2 (const vector<int> &vp) {
        
        vector<mgraph> vg;
        
        for (int i = 0; i < vp.size(); ++i) {
            vg.emplace_back(mgraph(i, vp[i] % S, vp[i] / S));
        }
        
        while (vg.size() > 1) {
            int a = 0;
            int msize = vg[0].size();
            for (int i = 1; i < vg.size(); ++i) {
                if(vg[i].size() < msize) {
                    msize = vg[i].size();
                    a = i;
                }
            }
            
            int bgi = a;
            int bi = -1;
            int ai = -1;
            double mdist = 2000;
            for (int i = 0; i < vg.size(); ++i) {
                if (i == a) { continue; }
                int tai = -1;
                int tbi = -1;
                double tdist = vg[i].mindist(*this, vg[a], tai, tbi);
                if (tdist < mdist) {
                    bgi = i;
                    ai = tai;
                    bi = tbi;
                    mdist = tdist;
                }
            }
            
            vg[a].gunion(vg[bgi]);
            vg[a].add_graph(ai, bi);
            
            vector<mgraph> tg;
            for (int i = 0; i < vg.size(); ++i) {
                if (i == bgi) { continue; }
                tg.emplace_back(vg[i]);
            }
            vg = tg;
            
        }
        
        return vg[0].g;
    }
    
    inline pair<double, pair<int, int> > min_index (vector< pair<double, pair<int, int> > > &minindex, const pair<int, pair<int, int> > t, const unordered_map<int, pair<int, int> > &mip) {
        const int x = t.second.first;
        const int y = t.second.second;
        for (auto &m : mip) {
            const int px = m.second.first;
            const int py = m.second.second;
            const double tdist = this->tdistance(x, y, px, py);
            // dist sindex mindex
            minindex.emplace_back(tdist, make_pair(t.first, m.first));
        }
        
        vector< pair<double, pair<int, int> > > r;
        
        
        for (auto &i : minindex) {
            if (i.second.second != t.first) { r.emplace_back(i); }
        }
        minindex = r;
        
        if (minindex.size() < 1) { return pair<double, pair<int, int> >(-1, make_pair(-1 , -1)); }
        pair<double, pair<int, int> > m = minindex[0];
        for (auto &i : minindex) {
            if (i.first < m.first) {
                m = i;
            }
        }
        
        
        //sort(minindex.begin(), minindex.end());
        
        return m;
    }
    
    inline vector< pair<int, int> > ip_to_graph3 (const vector<int> &vp) {
        unordered_map<int, pair<int, int> > mip;
        for (int i = 0; i < vp.size(); ++i) {
            mip.emplace(i, make_pair(vp[i] % S, vp[i] / S)); 
        }
        vector< pair<int, int> > r;
        vector< pair<int, pair<int, int> > > s;
        s.emplace_back(0, make_pair(vp[0] % S, vp[0] / S));
        
        // dist sindex mindex
        vector< pair<double, pair<int, int> > > minindex;
        pair<double, pair<int, int> > m = this->min_index(minindex, s[0], mip);
        
        mip.erase(0);
        int S = this->S;
        while (!(m.first < 0)) {
            pair<int, pair<int, int> > t = make_pair(m.second.second, make_pair(vp[m.second.second] % S, vp[m.second.second] / S));
            r.emplace_back(m.second);
            s.emplace_back(t);
            mip.erase(m.second.second);
            
            m = this->min_index(minindex, t, mip);
            
        }
        return r;
    }
    
    
    
    vector< pair<int, int> > ips (const vector< pair<int, int> > &junctions, const vector<int> &junctionStatus) {
        vector< pair<int, int> > j = this->ip_cities;
        
        for (int i = 0; i < junctionStatus.size(); ++i) {
            if (junctionStatus[i] == 0) { continue; }
            j.emplace_back(junctions[i].first, junctions[i].second);
        }
        return j;
    }
    
    vector< pair<int, int> > add_ips (const vector<int> &ps) {
        vector< pair<int, int> > j = this->ip_cities;
        
        for (int i = 0; i < ps.size(); ++i) {
            j.emplace_back(this->NC + i, ps[i]);
        }
        return j;
    }
    
    vector<int> init_vps () {
        vector<int> v;
        for (auto &i : this->ip_cities) { v.emplace_back(i.second); }
        return v;
    }
    
    
    vector<int> add_vps (const vector<int> &vps, vector<int> ps) {
        vector<int> v = vps;
        for (auto &i : ps) { v.emplace_back(i); }
        return v;
    }
    
    inline vector<int> add_vps (const vector<int> &vps, int p) {
        vector<int> v = vps;
        v.emplace_back(p);
        return v;
    }
    
    
    vector<int> init_vps (const vector< pair<int, int> > &junctions) {
        vector<int> v;
        for (auto &i : this->ip_cities) {
            v.emplace_back(i.second);
        }
        
        
        for (int i = 0; i < junctions.size(); ++i) {
            v.emplace_back(junctions[i].second);
        }
        return v;
    }
    
    
    vector<int> buildRoads(vector<int> junctionStatus) {
        vector<int> ret;
        vector< pair<int, int> > ips = this->ips(this->junctions, junctionStatus);
        
        vector< pair<int, int> > g = ip_to_graph (ips);
        for (auto &i : g) {
            ret.emplace_back(i.first);
            ret.emplace_back(i.second);
        }
        
        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    StopWatch sw;
    RoadsAndJunctions rj;
    int S, C;
    cin >> S >> C;
    vector<int> cities(C);
    getVector(cities);
    double junctionCost, failureProbability;
    cin >> junctionCost >> failureProbability;
    
    vector<int> ret = rj.buildJunctions(S, cities, junctionCost, failureProbability);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
    
    int J;
    cin >> J;
    vector<int> junctionStatus(J);
    getVector(junctionStatus);

    ret = rj.buildRoads(junctionStatus);
    
    cerr << "cnt:" << cnt << endl;
    cerr << " S:" << S;
    cerr << " C:" << junctionCost;
    cerr << " F:" << failureProbability;
    cerr << " NC:" << C/2;
    cerr << " Time:" << sw.get_milli_time();
    
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
