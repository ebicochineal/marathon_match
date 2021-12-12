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
    array< array<int, gmaxK>, gmaxM > skills;
    array<int, gmaxM> tasks;
    array<int, gmaxM> turns;
    
    array< vector< pair<int, int> >, gmaxM > results;
    
    Members () {
        for (int y = 0; y < this->skills.size(); ++y) {
            for (int x = 0; x < this->skills[y].size(); ++x) {
                this->skills[y][x] = 0;
            }
        }
        for (int i = 0; i < this->M; ++i) {
            this->tasks[i] = -1;
        }
    }
    
    vector<int> readymember () {
        vector<int> r;
        for (int i = 0; i < this->M; ++i) {
            if (this->tasks[i] < 0) { r.emplace_back(i); }
        }
        return r;
    }
};

struct Tasks {
    array< array<int, gmaxK>, gmaxN > skills;
    array< vector<int>, gmaxN > dependency;
    array< vector<int>, gmaxN > rdependency;
    array< vector<int>, gmaxN > allrdependency;
    array<int, gmaxN> status;
    Tasks () {
        for (int i = 0; i < gmaxN; ++i) { this->status[i] = 0; }
    }
    
    void init_allrdependency (int lm) {
        bitset<gmaxN> f;
        unordered_set<int> us;
        for (int i = 0; i < gmaxN; ++i) {
            if (this->rdependency[i].size() == 0) { us.emplace(i); }
        }
        int cnt = 0;
        unordered_set<int> tus;
        
        for (auto&& i : this->allrdependency) {
            i.clear();
        }
        
        while (us.size() > 0 && cnt < lm) {
            cnt += 1;
        // while (us.size() > 0) {
            tus.clear();
            for (auto&& p : us) {
                for (auto&& i : this->dependency[p]) {
                    tus.emplace(i);
                    
                    f.reset();
                    for (auto&& x : this->allrdependency[i]) { f[x] = true; }
                    if (f[p] == false) { this->allrdependency[i].emplace_back(p); }
                    
                    for (auto&& j : this->allrdependency[p]) {
                        if (f[j] == false) { this->allrdependency[i].emplace_back(j); }
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
    
    vector<int> readytask () {
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

struct BM {
    int turn;
    BM () {}
    BM (int turn) { this->turn; }
    
};

int scores (int K, int m, Members& members, Tasks& tasks) {
    int score = 0;
    for (auto&& i : members.results[m]) {
        const int t = i.first;
        int result = i.second;
        for (int j = 0; j < K; ++j) {
            result -= max(tasks.skills[t][j]-members.skills[m][j], 0);
        }
        score += max(abs(result)-1, 1);
    }
    return score;
}

vector<int> gsv;
int initscores (int K, int m, Members& members, Tasks& tasks) {
    gsv = vector<int>(members.results[m].size(), 0);
    
    int score = 0;
    for (int i = 0; i < members.results[m].size(); ++i) {
        const int t = members.results[m][i].first;
        int result = members.results[m][i].second;
        for (int j = 0; j < K; ++j) {
            result -= max(tasks.skills[t][j]-members.skills[m][j], 0);
        }
        gsv[i] = result;
        score += max(abs(gsv[i])-1, 1);
    }
    return score;
}

int dscores (int K, int m, Members& members, Tasks& tasks, int p, int prev, int next) {
    int score = 0;
    for (int i = 0; i < members.results[m].size(); ++i) {
        const int t = members.results[m][i].first;
        int s = gsv[i];
        s += max(tasks.skills[t][p]-prev, 0);
        s -= max(tasks.skills[t][p]-next, 0);
        score += max(abs(s)-1, 1);
    }
    
    return score;
}

void applyscores (int K, int m, Members& members, Tasks& tasks, int p, int prev, int next) {
    members.skills[m][p] = next;
    for (int i = 0; i < members.results[m].size(); ++i) {
        const int t = members.results[m][i].first;
        int s = gsv[i];
        s += max(tasks.skills[t][p]-prev, 0);
        s -= max(tasks.skills[t][p]-next, 0);
        gsv[i] = s;
    }
}


void sa (int turn, int K, int m, Members& members, Tasks& tasks, int ecnt, double stemp = 256.0, double etemp = 0.0) {
    const double sacnt = ecnt;
    array<int, gmaxK> bestv = members.skills[m];
    double bestscore = initscores(K, m, members, tasks);
    double lastscore = bestscore;
    const int64_t R = 1000000000;
    for (int ncnt = 0; ncnt < ecnt; ++ncnt) {
        {
            int a = xrnd() % K;
            int b = xrnd() % (turn < 100 ? 31 : 61);
            int t = members.skills[m][a];
            
            double tmpscore = dscores(K, m, members, tasks, a, t, b);
            
            // members.skills[m][a] = b;
            // double tmpscore = initscores(K, m, members, tasks);
            const double temp = stemp + (etemp - stemp) * (double)(ncnt) / sacnt;
            const double probability = exp((lastscore - tmpscore) / temp);
            const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            if (tmpscore < lastscore || FORCE_NEXT) {
                lastscore = tmpscore;
                applyscores(K, m, members, tasks, a, t, b);
                if (tmpscore < bestscore) {
                    bestscore = tmpscore;
                    bestv = members.skills[m];
                }
            }
        }
    }
    members.skills[m] = bestv;
}


// file
// #include <fstream>
// #include <iostream>
// void initmemberskill (int N, int M, int K, int R, Members& members) {
//     int n = 0;
//     for (int i = 0; i < 101; ++i) {
//         ifstream ifs("./in/" + to_string(i) + ".txt");
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
// void memberupdate (int time, int K, int turn, int m, Members& members, Tasks& tasks) {}

void initmemberskill (int N, int M, int K, int R, Members& members) {
    for (int y = 0; y < M; ++y) {
        for (int x = 0; x < K; ++x) {
            members.skills[y][x] = 16;
        }
    }
}

void memberupdate (int time, int K, int turn, int m, Members& members, Tasks& tasks) {
    members.results[m].emplace_back(members.tasks[m], turn-members.turns[m]);
    if (time < 2800) { sa(turn, K, m, members, tasks, 5126, 2, 0); }
    
    int bestscore = scores(K, m, members, tasks);
    for (int i = 0; i < 512/2; ++i) {
        int a1 = xrnd() % K;
        int t1 = members.skills[m][a1];
        members.skills[m][a1] = min(t1+1, 60);
        int score = scores(K, m, members, tasks);
        if (score <= bestscore) {
            bestscore = score;
        } else {
            members.skills[m][a1] = t1;
        }
    }
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
        
        initmemberskill(this->N, this->M, this->K, this->R, this->members);
        
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
    void output (vector< pair<int, int> >& v, int turn) {
        string r = to_string(v.size());
        for (int i = 0; i < v.size(); ++i) {
            
            this->members.tasks[v[i].first] = v[i].second;
            this->members.turns[v[i].first] = turn;
            this->tasks.status[v[i].second] = 1;
            
            r += " " + to_string(v[i].first+1) + " " + to_string(v[i].second+1);
        }
        cout << r << endl;
        cout.flush();
    }
    
    
    vector<int> rdt;
    vector<int> rdm;
    array< array<int, gmaxM>, gmaxN> matnm;
    // void tupdate (int turn) {
    //     this->rdt = this->tasks.readytask();
    //     this->rdm = this->members.readymember();
    //     for (auto&& n : this->rdt) {
    //         for (auto&& m : this->rdm) {
    //             int score = 0;
    //             for (int k = 0; k < this->K; ++k) {
    //                 score += max(this->tasks.skills[n][k]-this->members.skills[m][k], 0);
    //             }
    //             this->matnm[n][m] = score;
    //         }
    //     }
    // }
    void tupdate (int turn) {
        this->rdt = this->tasks.readytask();
        this->rdm = this->members.readymember();
        for (auto&& n : this->rdt) {
            int cnt = 0;
            for (auto&& w : this->tasks.rdependency[n]) {
                int tcnt = 0;
                for (auto&& i : this->tasks.dependency[w]) {
                    if (this->tasks.status[i] == 0) { tcnt += 1; }
                }
                if (tcnt == 1) { cnt += 5; }
            }
            // for (auto&& m : this->rdm) {
            for (int m = 0; m < this->M; ++m) {
                int score = 0;
                for (int k = 0; k < this->K; ++k) {
                    score += max(this->tasks.skills[n][k]-this->members.skills[m][k], 0);
                }
                this->matnm[n][m] = score - cnt;
            }
        }
    }
    
    void solve () {
        this->tasks.init_allrdependency(12);
        for (int turn = 0; turn < 2000; ++turn) {
            
            if (turn == 300) { this->tasks.init_allrdependency(2000); }
            
            vector< pair<int, int> > out;
            
            this->tupdate(turn);
            
            // fdebug(turn, this->rdt.size(), this->rdm.size());
            bitset<gmaxM> bsm;
            bitset<gmaxN> bst;
            
            double x = 2.5;
            
            int cnt = 0;
            for (auto&& i : this->tasks.status) { if (i > 0) { cnt += 1; } }
            
            //if (cnt > 900) { x = 3; }
            if (turn < 80 || this->tasks.readytask().size() < this->members.readymember().size()*2) {
                vector<int> rt = this->tasks.readytask();
                sort(rt.begin(), rt.end(), [&](const int& a, const int& b) { return this->tasks.allrdependency[a].size() > this->tasks.allrdependency[b].size(); });
                
                
                for (auto&& i : rt) {
                    if (bst[i]) { continue; }
                    int m = -1;
                    int bestscore = 1000000;
                    
                    vector<int> v;
                    for (int j = 0; j < this->M; ++j) { v.emplace_back(this->matnm[i][j]); }
                    sort(v.begin(), v.end(), [](const int& a, const int& b) { return a < b; });
                    int bestscore2 = (v[0]+v[1])/2;
                    
                    vector<int> rm = this->members.readymember();
                    for (auto&& j : rm) {
                        if (bsm[j]) { continue; }
                        int score = this->matnm[i][j];
                        if (score < bestscore && score <= max(bestscore2, 1)*x) {
                            bestscore = score;
                            m = j;
                        }
                    }
                    if (m > -1) {
                        out.emplace_back(m, i);
                        bsm[m] = true;
                        bst[i] = true;
                    }
                }
            } else {
                int zz = this->members.readymember().size();
                for (int z = 0; z < zz*0.7; ++z) {
                    int bm = -1;
                    int bt = -1;
                    int bestscore = 100000000;
                    vector<int> rt = this->tasks.readytask();
                    for (auto&& i : rt) {
                        
                        vector<int> v;
                        for (int j = 0; j < this->M; ++j) { v.emplace_back(this->matnm[i][j]); }
                        sort(v.begin(), v.end(), [](const int& a, const int& b) { return a < b; });
                        int bestscore2 = (v[0]+v[1])/2;
                    
                        
                        if (bst[i]) { continue; }
                        vector<int> rm = this->members.readymember();
                        for (auto&& j : rm) {
                            if (bsm[j]) { continue; }
                            int score = this->matnm[i][j];
                            score -= this->tasks.allrdependency[i].size() * 0.2;
                            if (score < bestscore && this->matnm[i][j] <= max(bestscore2, 1)*x) {
                                bestscore = score;
                                bm = j;
                                bt = i;
                            }
                        }
                    }
                    if (bm > -1) {
                        out.emplace_back(bm, bt);
                        bsm[bm] = true;
                        bst[bt] = true;
                    }
                }
            }
            {
                vector<int> rt = this->tasks.readytask();
                sort(rt.begin(), rt.end(), [&](const int& a, const int& b) { return this->tasks.allrdependency[a].size() > this->tasks.allrdependency[b].size(); });
                
                
                for (auto&& i : rt) {
                    if (bst[i]) { continue; }
                    int m = -1;
                    int bestscore = 1000000;
                    
                    vector<int> v;
                    for (int j = 0; j < this->M; ++j) { v.emplace_back(this->matnm[i][j]); }
                    sort(v.begin(), v.end(), [](const int& a, const int& b) { return a < b; });
                    int bestscore2 = (v[0]+v[1])/2;
                    
                    
                    vector<int> rm = this->members.readymember();
                    for (auto&& j : rm) {
                        if (bsm[j]) { continue; }
                        int score = this->matnm[i][j];
                        if (score < bestscore && score <= max(bestscore2, 1)*x) {
                            bestscore = score;
                            m = j;
                        }
                    }
                    if (m > -1) {
                        out.emplace_back(m, i);
                        bsm[m] = true;
                        bst[i] = true;
                    }
                }
            }
            this->output(out, turn);
            
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
                
                
                memberupdate(this->sw.get_milli_time(), this->K, turn, m, this->members, this->tasks);
                
                // this->output_skill(m);
                this->members.tasks[m] = -1;
            }
        }
        
    }
};


int main () {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    MM mm;
    mm.input();
    mm.solve();
    
    return 0;
}
