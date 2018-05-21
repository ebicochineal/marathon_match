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




class RoadsAndJunctions {
public:
    int NC;
    int S;
    vector< pair<int, int> > bp;// blank x, y
    StopWatch sw;
    vector< pair<int, int> > junctions;// index, pos
    vector< pair<int, int> > ip_cities;
    
    vector<int> cities;
    
    vector< pair<int, int> > cities_graph;
    
    vector<int> blank;
    
    vector<int> buildJunctions (int S, vector<int> cities, double junctionCost, double failureProbability) {
        vector<int> ret;
        if (failureProbability < 0.50) {
            cerr << "A" << endl;
            ret = this->buildJunctionsA(S, cities,junctionCost, failureProbability);
        } else if (failureProbability < 0.30 && junctionCost < 6) {
            cerr << "A" << endl;
            ret = this->buildJunctionsA(S, cities,junctionCost, failureProbability);
        } else {
            cerr << "B" << endl;
            ret = this->buildJunctionsB(S, cities,junctionCost, failureProbability);
        }
        cerr << "S" << S << " C" << junctionCost << " F" << failureProbability << " N" << this->NC << " J" << ret.size() << endl;
        return ret;
    }
    
    
    vector<int> buildJunctionsA (int S, vector<int> cities, double junctionCost, double failureProbability) {
        S += 1;
        //this->sw = StopWatch();
        this->S = S;
        this->NC = cities.size() / 2;
        this->cities = cities;
        this->ip_cities = this->init_cities();
        
        vector<int> v(S * S, 1);// city 0
        vector<int> vf(S * S, 1);
        vector<int> ret;
        
        int pl = S / 2, pr = S / 2, pu = S / 2, pd = S / 2;
        
        for (int i = 0; i < this->NC; ++i) {
            const int x = cities[2 * i];
            const int y = cities[2 * i + 1];
            v[x + y * S] = 0;
            vf[x + y * S] = 0;
            pl = min(pl, x);
            pr = max(pr, x);
            pu = min(pu, y);
            pd = max(pd, y);
            
        }
        
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};
        
        
        for (int i = 0; i < S * S; ++i) {
            int x = i % S;
            int y = i / S;
            if (!(pl < x && x < pr && pu < y && y < pd)) { vf[i] = 0; }
        }
        
        for (int i = 0; i < S * S; ++i) {
            int x = i % S;
            int y = i / S;
            if (vf[i] == 1) {
                this->bp.emplace_back(x, y);
            }
        }
        this->cities_graph = this->ip_to_graph(this->ip_cities);
        
        auto vps = this->to_vps();
        auto cvps = vps;
        double score = this->all_distance(this->cities_graph, vps) - junctionCost;
        double iscore = score;
        int cnt = 0;
        int tnt = 0;
        vector<int> bestppos;
        int tpos = -1;
        int timer = this->sw.get_milli_time();
        int loop = 30;
        
        int nx = (5126 * 10) / this->NC;
        
        while(timer < 9500){
            if (cnt > 1000 && timer < 1000) { loop = 100; }
            if (cnt > 10000 && timer < 1000) { loop = 1000; }
            for (int z = 0; z < loop; ++z) {
                int a = xrnd()%this->bp.size();
                int aa = this->bp[a].first + this->bp[a].second * this->S;
                if (vf[aa] == 0) { continue; }
                auto tvps = this->add_vps(vps, aa);
                auto g = this->ip_to_graph(tvps);
                double tscore = this->all_distance(g, tvps);
                if (tscore < score) {
                    score = tscore;
                    tpos = aa;
                }
                cnt += 1;
                tnt += 1;
            }
            
            if (tnt > nx) {
                if (tpos > -1) {
                    bestppos.emplace_back(tpos);
                    vps = this->add_vps(vps, tpos);
                    tpos = -1;
                    vf[tpos] = 0;
                    score -= junctionCost;
                }
                tnt = 0;
            }
            if (bestppos.size() > this->NC) {
                break;
            }
            
            timer = this->sw.get_milli_time();
        }
        if (tpos > -1) {
            bestppos.emplace_back(tpos);
            vps = this->add_vps(vps, tpos);
            tpos = -1;
            vf[tpos] = 0;
        }
        // for (auto& i : bestppos) {
        //     ret.emplace_back(i % this->S);
        //     ret.emplace_back(i / this->S);
        // }
        
        // cerr << this->all_distance(this->cities_graph, vps) << endl;
        
        vps = cvps;
        vector<int> ps;
        vector<int> tps;
        double tscore = iscore;
        score = iscore;
        for (int k = 0; k < bestppos.size(); ++k) {
            if (this->sw.get_milli_time() > 9800) { break; }
            if (ret.size() / 2 > this->NC * 2 - 16) { break; }
            ps = tps;
            if (bestppos[k] > -1) {
                // ret.emplace_back(bestppos[k] % this->S);
                // ret.emplace_back(bestppos[k] / this->S);
                ps.emplace_back(bestppos[k]);
                auto tvps = this->add_vps(vps, ps);
                auto g = this->ip_to_graph(tvps);
                tscore = this->all_distance(g, tvps);
                // cerr << tscore << endl;
                if ((score - tscore) / junctionCost > 4 && failureProbability > 0.1) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                if ((score - tscore) / junctionCost > 8 && failureProbability > 0.2) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                if ((score - tscore) / junctionCost > 16 && failureProbability > 0.3) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                // if (tscore < score) {
                score = tscore - junctionCost;
                ret.emplace_back(bestppos[k] % this->S);
                ret.emplace_back(bestppos[k] / this->S);
                tps.emplace_back(bestppos[k]);
            
                v[bestppos[k]] = 0;
                // }
            }
        }
        
        
        
        
        this->junctions = this->ret_to_junctions(ret);
        cerr << "cnt:" << cnt << endl;
        return ret;
    }
    
    vector<int> buildJunctionsB (int S, vector<int> cities, double junctionCost, double failureProbability) {
        S += 1;
        //this->sw = StopWatch();
        this->S = S;
        this->NC = cities.size() / 2;
        this->cities = cities;
        this->ip_cities = this->init_cities();
        
        vector<int> v(S * S, 1);// city 0
        vector<int> vf(S * S, 1);
        vector<int> ret;
        
        int pl = S / 2, pr = S / 2, pu = S / 2, pd = S / 2;
        
        for (int i = 0; i < this->NC; ++i) {
            const int x = cities[2 * i];
            const int y = cities[2 * i + 1];
            v[x + y * S] = 0;
            vf[x + y * S] = 0;
            pl = min(pl, x);
            pr = max(pr, x);
            pu = min(pu, y);
            pd = max(pd, y);
            
        }
        
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};
        
        
        for (int i = 0; i < S * S; ++i) {
            int x = i % S;
            int y = i / S;
            if (!(pl < x && x < pr && pu < y && y < pd)) { vf[i] = 0; }
        }
        
        for (int i = 0; i < S * S; ++i) {
            int x = i % S;
            int y = i / S;
            if (vf[i] == 1) {
                this->bp.emplace_back(x, y);
            }
        }
        
        
        
        int n = 3 + S / 200;
        
        int m = n * n;
        vector< vector < pair<int, int> > > bp(m, vector < pair<int, int> >());
        for (int i = 0; i < S * S; ++i) {
            if (v[i] == 1) {
                int x = i % S;
                int y = i / S;
                int a = (S/n+1);
                
                int d = 2;
                int mx = x % a;
                int my = y % a;
                if (mx > d && mx < a-d && my > d && my < a-d) {
                    bp[x / a + (y / a) * n].emplace_back(x, y);
                }
            }
        }
        
        
        this->cities_graph = this->ip_to_graph(this->ip_cities);
        
        auto vps = this->to_vps();
        double score = this->all_distance(this->cities_graph, vps);
        
        double iscore = score - junctionCost;
        if (failureProbability > 0.1) { iscore -= junctionCost / 2; }
        if (failureProbability > 0.3) { iscore -= junctionCost / 4; }
        
        int cnt = 0;
        vector<int> bestppos(m, -1);
        int timer = this->sw.get_milli_time();
        int loop = 30;
        int dtimer = 0;
        for (int k = 0; k < m; ++k) {
            score = iscore;
            while(timer < (9500/m) * (k+1)){
                
                if (cnt > 1000 && timer < 1000) { loop = 100; }
                if (cnt > 10000 && timer < 1000) { loop = 1000; }
                for (int z = 0; z < loop; ++z) {
                    int a = xrnd()%bp[k].size();
                    int aa = bp[k][a].first + bp[k][a].second * this->S;
                    auto tvps = this->add_vps(vps, aa);
                    auto g = this->ip_to_graph(tvps);
                    double tscore = this->all_distance(g, tvps);
                    if (tscore < score) {
                        score = tscore;
                        bestppos[k] = aa;
                    }
                    cnt += 1;
                }
                // if (timer > (9500/m)*k +((9500/m)/2) && bestppos[k] < 0) {
                //     break;
                // }
                timer = this->sw.get_milli_time();
            }
        }
        
        // bestppos = union_pos(bestppos);
        
        cerr << this->all_distance(this->cities_graph, vps) << endl;
        vector<int> ps;
        vector<int> tps;
        double tscore = iscore;
        
        for (int k = 0; k < bestppos.size(); ++k) {
            if (this->sw.get_milli_time() > 9800) { break; }
            if (ret.size() / 2 > this->NC * 2 - 16) { break; }
            ps = tps;
            if (bestppos[k] > -1) {
                // ret.emplace_back(bestppos[k] % this->S);
                // ret.emplace_back(bestppos[k] / this->S);
                ps.emplace_back(bestppos[k]);
                auto tvps = this->add_vps(vps, ps);
                auto g = this->ip_to_graph(tvps);
                tscore = this->all_distance(g, tvps);
                // cerr << tscore << endl;
                if ((score - tscore) / junctionCost > 4 && failureProbability > 0.3) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                if ((score - tscore) / junctionCost > 8 && failureProbability > 0.3) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                if ((score - tscore) / junctionCost > 16 && failureProbability > 0.3) {
                    int x = bestppos[k] % this->S;
                    int y = bestppos[k] / this->S;
                    
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
                if (tscore < score) {
                    score = tscore - junctionCost;
                    ret.emplace_back(bestppos[k] % this->S);
                    ret.emplace_back(bestppos[k] / this->S);
                    tps.emplace_back(bestppos[k]);
                
                    v[bestppos[k]] = 0;
                }
            }
        }
        
        this->junctions = this->ret_to_junctions(ret);
        cerr << "cnt:" << cnt << endl;
        return ret;
    }
    
    
    vector<int> union_pos(vector<int> &a) {
        vector<int> p;
        vector<int> r;
        for (auto& i : a) {
            if (i > -1) { p.emplace_back(i); }
        }
        
        vector<int> v;
        
        for (int i = 0; i < p.size(); ++i) {
            int ax = p[i] % this->S;
            int ay = p[i] / this->S;
            int sx = ax;
            int sy = ay;
            int cnt = 0;
            bool f = true;
            for (int j = i+1; j < p.size(); ++j) {
                int bx = p[j] % this->S;
                int by = p[j] / this->S;
                double d = distance(ax, ay, bx, by);
                if (d < 8) {
                    sx += bx;
                    sy += by;
                    cnt += 1;
                    f = false;
                }
            }
            if (f) { r.emplace_back(p[i]); }
            if (cnt > 0) {
                v.emplace_back((sx / cnt) + (sy / cnt) * this->S);
            }
            
            
        }
        
        for (auto& i : v) {
            r.emplace_back(i);
        }
        
        return r;
    }
    
    
    inline double all_distance (const vector< pair<int, int> > &g, const vector<int> &vps) {
        double d = 0;
        int ax, ay, bx, by;
        for (auto &i : g) {
            ax = vps[i.first] % this->S;
            ay = vps[i.first] / this->S;
            bx = vps[i.second] % this->S;
            by = vps[i.second] / this->S;
            d += distance(ax, ay, bx, by);
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
    
    // args pair<index, pos> x = pos%this->S, y = pos/this->S
    // return pair<index, index>
    // vector< pair<int, int> > ip_to_graph (vector< pair<int, int> > ip) {
    //     vector< pair<int, int> > r;
    //     vector< pair<int, int> > s;
    //     s.emplace_back(ip[0]);
    //     ip[0].first = -1;
    //     int S = this->S;
    //     while (s.size() < ip.size()) {
    //         int ii = -1;
    //         int ji = -1;
    //         int jj = -1;
    //         double dist = 2000;
    //         for (int i = 0; i < s.size(); ++i) {
    //             const int sx = s[i].second % S;
    //             const int sy = s[i].second / S;
    //             for (int j = 1; j < ip.size(); ++j) {
    //                 if (ip[j].first < 0) { continue; }
    //                 const int px = ip[j].second % S;
    //                 const int py = ip[j].second / S;
    //                 const double tdist = distance(sx, sy, px, py);
    //                 if (tdist < dist) {
    //                     dist = tdist;
    //                     ii = s[i].first;
    //                     ji = ip[j].first;
    //                     jj = j;
    //                 }
    //             }
    //         }
    //         if (ii < 0)  { return r; }
    //         r.emplace_back(ii, ji);
    //         s.emplace_back(ip[jj]);
    //         ip[jj].first = -1;
    //     }
        
    //     return r;
    // }
    
    inline vector< pair<int, int> > ip_to_graph (const vector< pair<int, int> > &ip) {
        unordered_map<int, int> mip;
        for (auto& i : ip) { mip.emplace(i); }
        vector< pair<int, int> > r;
        vector< pair<int, int> > s;
        s.emplace_back(ip[0]);
        mip.erase(ip[0].first);
        int S = this->S;
        while (s.size() < ip.size()) {
            int ii = -1;
            pair<int, int> mm;
            double dist = 2000;
            for (int i = 0; i < s.size(); ++i) {
                const int sx = s[i].second % S;
                const int sy = s[i].second / S;
                //for (int j = 1; j < ip.size(); ++j) {
                for (auto& m : mip) {
                    const int px = m.second % S;
                    const int py = m.second / S;
                    const double tdist = distance(sx, sy, px, py);
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
    inline vector< pair<int, int> > ip_to_graph (const vector<int> &vp) {
        unordered_map<int, int> mip;
        for (int i = 0; i < vp.size(); ++i) {
            mip.emplace(i, vp[i]); 
        }
        vector< pair<int, int> > r;
        vector< pair<int, int> > s;
        s.emplace_back(0, vp[0]);
        mip.erase(0);
        int S = this->S;
        while (s.size() < vp.size()) {
            int ii = -1;
            pair<int, int> mm;
            double dist = 2000;
            for (int i = 0; i < s.size(); ++i) {
                const int sx = s[i].second % S;
                const int sy = s[i].second / S;
                for (auto& m : mip) {
                    const int px = m.second % S;
                    const int py = m.second / S;
                    const double tdist = distance(sx, sy, px, py);
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
    
    vector<int> to_vps () {
        vector<int> v;
        for (auto &i : this->ip_cities) {
            v.emplace_back(i.second);
        }
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
    
    
    vector<int> to_vps (const vector< pair<int, int> > &junctions) {
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
        
        cerr << print("Time", sw.get_milli_time()) << endl;
        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
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
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
