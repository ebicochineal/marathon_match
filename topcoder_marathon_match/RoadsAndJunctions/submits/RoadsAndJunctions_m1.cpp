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
        
        vector<int> blank = v;
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};
        
        for (int i = 0; i < S * S; ++i) {
            if (v[i] == 1) {
                this->bp.emplace_back(i % S, i / S);
            } else {////
                const int x = i % S;
                const int y = i / S;
                int cnt = failureProbability > 0.4 || (junctionCost < 2 && failureProbability > 0.1) ? 2 : 1;
                for (int j = 0; j < 4; ++j) {
                    const int px = x + dx[j];
                    const int py = y + dy[j];
                    if (px > -1 && px < S && py > -1 && py < S) {
                        if (blank[px + py * S] == 1) {
                            ret.emplace_back(px);
                            ret.emplace_back(py);
                            blank[px + py * S] = 0;
                            cnt -= 1;
                            if (cnt < 1) { break; }
                        }
                    }
                }
            }
        }
        
        this->junctions = this->ret_to_junctions(ret);
        
        
        cerr << print("S", S, "Cost", junctionCost, "Pr", failureProbability, "City", this->NC) << endl;
        return ret;
    }
    
    // index cnt
    unordered_map<int, int> road_cnt_pos () {
        unordered_map<int, int> s;
        
        
        
        return s;
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
            j.emplace_back(i, cx + cy * this->S);
        }
        return j;
    }
    
    vector< pair<int, int> > x_junctions (const vector< pair<int, int> > &junctions, const vector<int> &junctionStatus) {
        vector< pair<int, int> > j;
        for (int i = 0; i < junctionStatus.size(); ++i) {
            if (junctionStatus[i] == 0) { continue; }
            j.emplace_back(junctions[i]);
        }
        return j;
    }
    
    int min_dint_junc (int cx, int cy, const vector< pair<int, int> > &juncs) {
        int r = -1;
        double dist = 2000;
        for (auto &i : juncs) {
            const double tdist = distance(cx, cy, i.second % this->S, i.second / this->S);
            if (tdist < dist) {
                dist = tdist;
                r = i.first;
            }
        }
        return r;
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
    
    vector<int> buildRoads(vector<int> junctionStatus) {
        vector<int> ret;
        vector< pair<int, int> > juncs = this->x_junctions(this->junctions, junctionStatus);
        for(int i = 0; i < this->NC; i++) {
            const int cx = this->cities[2 * i];
            const int cy = this->cities[2 * i + 1];
            ret.emplace_back(i);
            ret.emplace_back(this->NC + this->min_dint_junc(cx, cy, juncs));
        }
        vector< pair<int, int> > jp = ip_to_graph (juncs);
        for (auto &i : jp) {
            ret.emplace_back(this->NC + i.first);
            ret.emplace_back(this->NC + i.second);
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
