#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
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
#include <bitset>
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

namespace strlib {
    string replace (string str, string old_s, string new_s, int n = 0) {
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.find(old_s, i)) > -1 && n; --n) {
            str.replace(i, old_s.size(), new_s);
            i += new_s.size();
        }
        return str;
    }
    int count (string str, string t) {
        int cnt = 0;
        for (int i = 0; (i = str.find(t, i)) > -1; i += t.size()) { ++cnt; }
        return cnt;
    }
    vector<string> split (string str, string sep = " ", int n = 0) {
        int prev = 0;
        vector<string> v;
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.find(sep, prev)) > -1 && n; --n) {
            v.push_back(str.substr(prev, i - prev));
            prev = i + sep.size();
        }
        v.push_back(str.substr(prev, str.size()));
        return v;
    }
    vector<string> split (string str, char sep = ' ', int n = 0) {
        string s = {sep};
        return split(str, s, n);
    }
    vector<string> rsplit (string str, string sep = " ", int n = 0) {
        int prev = str.size() - 1;
        vector<string> v;
        n = n < 1 ? str.size() : n;
        for (int i = 0; (i = str.rfind(sep, prev)) > -1 && n; --n) {
            v.insert(v.begin(), str.substr(i + sep.size(), prev - i + sep.size() - 1));
            prev = i - 1;
        }
        v.insert(v.begin(), str.substr(0, prev + 1));
        return v;
    }
    vector<string> rsplit (string str, char sep = ' ', int n = 0) {
        string s = {sep};
        return rsplit(str, s, n);
    }
    string slice (string str, int a, int b) {
        int s = a < 0 ? str.size() + a : a;
        int e = b < 0 ? str.size() + b : b;
        e = b == 0 ? str.size() : e;
        return str.substr(s, (s > e ? s : e) - s);
    }
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
        size_t operator()(const e512pos& t) const{ return t.x<<16 | t.y; }
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
const int gmaxN = 1000;
const int gmaxM = 20;
const int gmaxK = 20;
const int gmaxR = 3000;
struct Members {
    int M = gmaxM;
    array< array<int, gmaxK>, gmaxM > minskills;
    array< array<int, gmaxK>, gmaxM > skills;
    array<int, gmaxM> tasks;
    array<int, gmaxM> turns;
    
    array< vector< pair<int, int> >, gmaxM > results;
    
    Members () {
        for (int y = 0; y < this->skills.size(); ++y) {
            for (int x = 0; x < this->skills[y].size(); ++x) {
                this->skills[y][x] = 1;
                this->minskills[y][x] = 0;
            }
        }
        for (int i = 0; i < this->M; ++i) {
            this->tasks[i] = -1;
        }
    }
    
    vector<int> free_menbers () {
        vector<int> r;
        for (int i = 0; i < this->M; ++i) {
            if (this->tasks[i] < 0) { r.emplace_back(i); }
        }
        return r;
    }
    
    void end_tasks (vector<int>& v) {
        for (auto&& m : v) { this->tasks[m] = -1; }
    }
};

struct Tasks {
    array< array<int, gmaxK>, gmaxN > skills;
    array< vector<int>, gmaxN > dependency;
    array< vector<int>, gmaxN > rdependency;
    array< unordered_set<int>, gmaxN > allrdependency;
    array<int, gmaxN> status;
    Tasks () {
        for (int i = 0; i < gmaxN; ++i) { this->status[i] = 0; }
    }
    
    void init_allrdependency () {
        unordered_set<int> us;
        for (int i = 0; i < gmaxN; ++i) {
            if (this->rdependency[i].size() == 0) { us.emplace(i); }
        }
        int cnt = 0;
        unordered_set<int> tus;
        while (us.size() > 0 && cnt < 8) {
            cnt += 1;
            tus.clear();
            for (auto&& p : us) {
                for (auto&& i : this->dependency[p]) {
                    tus.emplace(i);
                    this->allrdependency[i].emplace(p);
                    for (auto&& j : this->allrdependency[p]) {
                        this->allrdependency[i].emplace(j);
                    }
                }
            }
            us = tus;
        }
    }
    
    int sum_skill (int x) {
        int r = 0;
        for (auto&& i : this->skills[x]) { r += i; }
        return r;
    }
    
    vector<int> possibletasks () {
        vector<int> r;
        for (int i = 0; i < gmaxN; ++i) {
            if (this->possible(i)) { r.emplace_back(i); }
        }
        return r;
    }
    
    bool possible (int x) {
        if (this->status[x] > 0) { return false; }
        for (auto&& i : this->dependency[x]) {
            if (this->status[i] < 2) { return false; }
        }
        return true;
    }
};

// file
// #include <fstream>
// #include <iostream>
// void zzz (int N, int M, int K, int R, Members& members) {
//     int n = 0;
//     for (int i = 0; i < 100; ++i) {
//         ifstream ifs("./in/" + to_string(i+1) + ".txt");
//         string s;
//         getline(ifs, s);
//         vector<string> t = strlib::split(s, " ");
//         if (stoi(t[0]) != N) { continue; }
//         if (stoi(t[1]) != M) { continue; }
//         if (stoi(t[2]) != K) { continue; }
//         if (stoi(t[3]) != R) { continue; }
//         pdebug(i+1);
//         for (int i = 0; i < N; ++i) { getline(ifs, s); }
//         for (int i = 0; i < R; ++i) { getline(ifs, s); }
//         for (int m = 0; m < M; ++m) {
//             getline(ifs, s);
//             vector<string> st = strlib::split(s, " ");
//             for (int k = 0; k < K; ++k) {
//                 members.skills[m][k] = stoi(st[k]);
//                 n = max(n, members.skills[m][k]);
//             }
//         }
//     }
//     pdebug(n);
// }
// void zzzz (int K, int turn, int m, Members& members, Tasks& tasks) {}

int scores (int K, int m, Members& members, Tasks& tasks) {
    int score = 0;
    for (auto&& i : members.results[m]) {
        const int t = i.first;
        int result = i.second;
        for (int j = 0; j < K; ++j) {
            result -= max(tasks.skills[t][j]-members.skills[m][j], 0);
        }
        score += abs(result) * abs(result);
    }
    return score;
}

void sa (int K, int m, Members& members, Tasks& tasks, int ecnt, double stemp = 256.0, double etemp = 0.0) {
    const double sacnt = ecnt;
    array<int, gmaxK> bestv = members.skills[m];
    double bestscore = scores(K, m, members, tasks);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
        int a1 = xrnd() % K;
        int b1 = xrnd() % 61;
        int t1 = members.skills[m][a1];
        // int a2 = xrnd() % K;
        // int b2 = xrnd() % 61;
        // int t2 = members.skills[m][a2];
        members.skills[m][a1] = b1;
        // members.skills[m][a2] = b2;
        double tmpscore = scores(K, m, members, tasks);
        const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
        const double probability = exp((lastscore - tmpscore) / temp);
        const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
        if (tmpscore < lastscore || FORCE_NEXT) {
            lastscore = tmpscore;
            if (tmpscore < bestscore) {
                bestscore = tmpscore;
                bestv = members.skills[m];
            }
        } else {
            members.skills[m][a1] = t1;
            // members.skills[m][a2] = t2;
        }
    }
    members.skills[m] = bestv;
}
void zzz (int N, int M, int K, int R, Members& members) {}

void zzzz (int K, int turn, int m, Members& members, Tasks& tasks) {
    members.results[m].emplace_back(members.tasks[m], turn-members.turns[m]);
    sa(K, m, members, tasks, 2048, 6, 0);
    
    // int bestscore = scores(K, m, members, tasks);
    // for (int i = 0; i < 512; ++i) {
    //     int a1 = xrnd() % K;
    //     int t1 = members.skills[m][a1];
    //     members.skills[m][a1] = max(t1-1, 0);
    //     int score = scores(K, m, members, tasks);
    //     if (score <= bestscore) {
    //         bestscore = score;
    //     } else {
    //         members.skills[m][a1] = t1;
    //     }
    // }
}



class MM {
public:
    StopWatch sw;
    int N, M, K, R;
    Tasks tasks;
    Members members;
    MM () { this->sw = StopWatch(); }
    void input () {
        cin >> this->N >> this->M >> this->K >> this->R;
        
        array< array<int, gmaxK>, gmaxN > skills;
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < this->K; ++j) {
                cin >> this->tasks.skills[i][j];
            }
        }
        
        for (int i = 0; i < this->R; ++i) {
            int u, v;
            cin >> u >> v;
            this->tasks.dependency[v - 1].emplace_back(u - 1);
            this->tasks.rdependency[u - 1].emplace_back(v - 1);
        }
        this->tasks.init_allrdependency();
        
        zzz(this->N, this->M, this->K, this->R, this->members);
        
        // this->output_skill();
        
    }
    string output_skill () {
        for (int m = 0; m < this->M; ++m) {
            string r = "#s " + to_string(m+1);
            for (int k = 0; k < this->K; ++k) {
                r += " " + to_string(this->members.skills[m][k]);
            }
            cout << r << endl;
        }
        cout.flush();
    }
    string output_skill (int m) {
        // for (int m = 0; m < this->M; ++m) {
            string r = "#s " + to_string(m+1);
            for (int k = 0; k < this->K; ++k) {
                r += " " + to_string(this->members.skills[m][k]);
            }
            cout << r << endl;
        // }
        cout.flush();
    }
    string v_to_str (vector< pair<int, int> >& v) {
        string r = to_string(v.size());
        for (int i = 0; i < v.size(); ++i) {
            r += " " + to_string(v[i].first) + " " + to_string(v[i].second);
        }
        return r;
    }
    
    
    void output () {
        
        for (int turn = 0; turn < 2000; ++turn) {
            
            vector< pair<int, int> > out;
            
            if (turn < 400 || this->tasks.possibletasks().size() < 10) {
                vector<int> pt = this->tasks.possibletasks();
                sort(pt.begin(), pt.end(), [&](const int& a, const int& b) { return this->tasks.allrdependency[a].size() > this->tasks.allrdependency[b].size(); });
                
                // fdebug(this->members.free_menbers().size(), pt.size());
                for (auto&& i : pt) {
                    int m = -1;
                    int bestscore = 1000000;
                    vector<int> fm = this->members.free_menbers();
                    for (auto&& j : fm) {
                        int score = 0;
                        for (int k = 0; k < this->K; ++k) {
                            score += max(this->tasks.skills[i][k]-this->members.skills[j][k], 0);
                        }
                        // score /= turn < 200 ? 2 : 1;
                        score -= this->tasks.rdependency[i].size() > 0;
                        if (score < bestscore) {
                            bestscore = score;
                            m = j;
                        }
                    }
                    if (m > -1) {
                        out.emplace_back(m+1, i+1);
                        this->members.tasks[m] = i;
                        this->members.turns[m] = turn;
                        this->tasks.status[i] = 1;
                    }
                    
                }
            } else {
                int zz = this->members.free_menbers().size();
                for (int z = 0; z < zz; ++z) {
                    int bm = -1;
                    int bt = -1;
                    int bestscore = 1000000;
                    vector<int> pt = this->tasks.possibletasks();
                    for (auto&& t : pt) {
                        vector<int> fm = this->members.free_menbers();
                        for (auto&& m : fm) {
                            int score = 0;
                            for (int k = 0; k < this->K; ++k) {
                                score += max(this->tasks.skills[t][k]-this->members.skills[m][k], 0);
                            }
                            // score /= turn < 200 ? 2 : 1;
                            score -= this->tasks.rdependency[t].size() > 0;
                            if (score < bestscore) {
                                bestscore = score;
                                bm = m;
                                bt = t;
                            }
                        }
                    }
                    if (bm > -1) {
                        out.emplace_back(bm+1, bt+1);
                        this->members.tasks[bm] = bt;
                        this->members.turns[bm] = turn;
                        this->tasks.status[bt] = 1;
                    }
                }
            }
            
            cout << this->v_to_str(out) << endl;
            cout.flush();
            
            int r;
            cin >> r;
            if (r == -1) {
                pdebug(turn, this->sw.get_milli_time());
                return;
            }
            
            for (int i = 0; i < r; ++i) {
                int m;
                cin >> m;
                m -= 1;
                
                this->tasks.status[this->members.tasks[m]] = 2;
                
                
                zzzz(this->K, turn, m, this->members, this->tasks);
                
                // this->output_skill(m);
                this->members.tasks[m] = -1;
            }
        }
        
    }
    void solve () {}
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    mm.output();
    
    return 0;
}
