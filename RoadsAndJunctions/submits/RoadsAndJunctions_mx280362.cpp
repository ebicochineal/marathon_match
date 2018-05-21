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
    return hypot(ax - bx, ay - by);
}
inline double distance (const int &ax, const int &ay, const int &bx, const int &by) {
    return hypot(ax - bx, ay - by);
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
    vector<int> buildJunctions(int S, vector<int> cities, double junctionCost, double failureProbability) {
        S += 1;
        //this->sw = StopWatch();
        this->S = S;
        this->NC = cities.size() / 2;
        this->cities = cities;
        this->ip_cities = this->init_cities();
        
        vector<int> v(S * S, 1);// city 0
        vector<int> ret;
        for (int i = 0; i < this->NC; ++i) {
            const int x = cities[2 * i];
            const int y = cities[2 * i + 1];
            v[x + y * S] = 0;
        }
        
        // vector<int> blank = v;
        // vector<int> dx = {-1, 1, 0, 0};
        // vector<int> dy = {0, 0, -1, 1};
        
        for (int i = 0; i < S * S; ++i) { if (v[i] == 1) { this->bp.emplace_back(i % S, i / S); } }
        
        this->cities_graph = this->ip_to_graph(this->ip_cities);
        
        auto vps = this->to_vps();
        double score = this->all_distance(this->cities_graph, vps);
        
        int cnt = 0;
        int bestppos = -1;
        while(this->sw.get_milli_time() < 9000){
            vector<int> ps;
            int a = xrnd()%this->bp.size();
            int aa = this->bp[a].first + this->bp[a].second * this->S;
            ps.emplace_back(aa);
            auto tvps = this->add_vps(vps, ps);
            auto tips = this->add_ips(ps);
            auto g = this->ip_to_graph(tips);
            double tscore = this->all_distance(g, tvps) + junctionCost;
            if (tscore < score) {
                score = tscore;
                bestppos = aa;
            }
            cnt += 1;
        }
        
        if (bestppos > -1) {
            ret.emplace_back(bestppos % this->S);
            ret.emplace_back(bestppos / this->S);
        }
        
        
        this->junctions = this->ret_to_junctions(ret);
        cerr << "cnt:" << cnt << endl;
        cerr << print("S", S, "Co", junctionCost, "Pr", failureProbability, "Ci", this->NC, "J", ret.size()/2) << endl;
        return ret;
    }
    
    double all_distance (const vector< pair<int, int> > &g, const vector<int> &vps) {
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
    vector< pair<int, int> > ip_to_graph (vector< pair<int, int> > ip) {
        vector< pair<int, int> > r;
        vector< pair<int, int> > s;
        s.emplace_back(ip[0]);
        ip[0].first = -1;
        int S = this->S;
        while (s.size() < ip.size()) {
            int ii = -1;
            int ji = -1;
            int jj = -1;
            double dist = 2000;
            for (int i = 0; i < s.size(); ++i) {
                const int sx = s[i].second % S;
                const int sy = s[i].second / S;
                for (int j = 1; j < ip.size(); ++j) {
                    if (ip[j].first < 0) { continue; }
                    const int px = ip[j].second % S;
                    const int py = ip[j].second / S;
                    const double tdist = distance(sx, sy, px, py);
                    if (tdist < dist) {
                        dist = tdist;
                        ii = s[i].first;
                        ji = ip[j].first;
                        jj = j;
                    }
                }
            }
            if (ii < 0)  { return r; }
            r.emplace_back(ii, ji);
            s.emplace_back(ip[jj]);
            ip[jj].first = -1;
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
    
    
    vector<int> add_vps (vector<int> &vps, vector<int> ps) {
        vector<int> v = vps;
        for (auto &i : ps) { v.emplace_back(i); }
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
