// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cstdlib>
#include <complex>

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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
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

#include <time.h>
#include <sys/timeb.h>

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



class Player {
public:
    int atk = 0;
    int def = 0;
    int agg = 0;
    int index = 0;
    Player (string s, int index) {
        auto vs = split(s, ',');
        this->atk = stoi(vs[0]);
        this->def = stoi(vs[1]);
        this->agg = stoi(vs[2]);
        // if (this->agg  > 10) { this->atk *= 0.95; }
        // if (this->agg  > 10) { this->def *= 0.95; }
        // if (this->agg  > 20) { this->atk *= 0.95; }
        // if (this->agg  > 20) { this->def *= 0.95; }
        // if (this->agg  > 30) { this->atk *= 0.9; }
        // if (this->agg  > 30) { this->def *= 0.9; }
        // if (this->agg  > 40) { this->atk *= 0.9; }
        // if (this->agg  > 40) { this->def *= 0.9; }
        
        this->index = index;
    }
};

class Group {
public:
    int flags = 0;
    int atk = 0;
    int def = 0;
    int agg = 0;
    vector<int> indexs;
    Group (string a, string b) {
        auto vs = split(a, ',');
        for (auto &i : vs) {
            int t = stoi(i);
            this->flags |= 1 << t;
            this->indexs.emplace_back(t);
        }
        
        vs = split(b, ',');
        this->atk = stoi(vs[0]);
        this->def = stoi(vs[1]);
        this->agg = stoi(vs[2]);
        // if (this->agg  > 5) { this->atk -= 2; }
        // if (this->agg  > 5) { this->def -= 2; }
        // if (this->agg  > 10) { this->atk -= 8; }
        // if (this->agg  > 10) { this->def -= 8; }
        // if (this->agg  > 15) { this->atk -= 12; }
        // if (this->agg  > 15) { this->def -= 12; }
        // if (this->agg  > 20) { this->atk -= 20; }
        // if (this->agg  > 20) { this->def -= 20; }
        
        if (this->agg  < -5) { this->atk += 2; }
        if (this->agg  < -5) { this->def += 2; }
        if (this->agg  < -10) { this->atk += 2; }
        if (this->agg  < -10) { this->def += 2; }
        if (this->agg  < -15) { this->atk += 2; }
        if (this->agg  < -15) { this->def += 2; }
        if (this->agg  < -20) { this->atk += 2; }
        if (this->agg  < -20) { this->def += 2; }
        if (this->agg  > 5) { this->atk -= 2; }
        if (this->agg  > 5) { this->def -= 2; }
        if (this->agg  > 10) { this->atk -= 4; }
        if (this->agg  > 10) { this->def -= 4; }
        if (this->agg  > 15) { this->atk -= 8; }
        if (this->agg  > 15) { this->def -= 8; }
        if (this->agg  > 20) { this->atk -= 12; }
        if (this->agg  > 20) { this->def -= 12; }
    }
};




class Team {
public:
    vector<Player> players;
    vector<Group> groups;
    int calcatk = 0;
    int calcdef = 0;
    int calceatk = 0;
    int calcedef = 0;
    vector<int> positions;
    unordered_set<int> menber;
    int uses = 0;
    Team () {}
    void InputPlayers(vector<string> players_vs) {
        for (int i = 0; i < players_vs.size(); ++i) {
            this->players.emplace_back(players_vs[i], i);
            this->positions.emplace_back('-');
        }
    }
    void InputGroups(vector<string> groups_vs) {
        for (int i = 0; i < groups_vs.size(); ++i) {
            auto ss = split(groups_vs[i], ' ');
            this->groups.emplace_back(ss[0], ss[1]);
        }
        
        // for (int i = 0; i < groups_vs.size()/2; ++i) {
        //     this->groups.emplace_back(groups_vs[i*2], groups_vs[i*2+1]);
        // }
    }
    
    int cnt = 0;
    string NextMaxPlayer () {
        this->cnt += 1;
        int bestscore = 0;
        int tscore = 0;
        int index = -1;
        string p = "";
        int tatk = 0;
        int tdef = 0;
        for (auto &i : this->players) {
            if (this->uses & (1 << i.index)) { continue; }
            
            if (this->cnt % 2 == 1) {
                // atk
                tatk = this->calcatk + i.atk *2;
                tdef = this->calcdef;
                this->PreGroupEffect(i.index, tatk, tdef);
                tscore = tatk + tdef;
                if (tscore > bestscore) {
                    bestscore = tscore;
                    index = i.index;
                    p = "F ";
                }
            } else {
                // def
                tatk = this->calcatk;
                tdef = this->calcdef + i.def *2;
                this->PreGroupEffect(i.index, tatk, tdef);
                tscore = tatk + tdef;
                if (tscore > bestscore) {
                    bestscore = tscore;
                    index = i.index;
                    p = "D ";
                }
            }
        }
        if (p == "F ") {
            this->calcatk += this->players[index].atk * 2;
            this->Use(index, 'F');
        }
        if (p == "M ") {
            this->calcatk += this->players[index].atk;
            this->calcdef += this->players[index].def;
            this->Use(index, 'M');
        }
        if (p == "D ") {
            this->calcdef += this->players[index].def * 2;
            this->Use(index, 'D');
        }
        
        this->GroupEffect();
        return p + to_string(index);
    }
    
    void PrintUse () {
        cerr << "b";
        for (int i = 0; i < 30; ++i) {
            if (this->uses & (1 << i)) {
                cerr << "1";
            } else {
                cerr << "0";
            }
        }
        cerr << endl;
    }
    
    void Use (int index, char position) {
        this->uses |= 1 << index;
        this->positions[index] = position;
    }
    
    
    void Remove (int index) {
        this->uses ^= 1 << index;
        this->positions[index] = '-';
    }
    
    
    void ResetUse () { this->uses = 0; }
    
    void GroupEffect () {
        this->calceatk = 0;
        this->calcedef = 0;
        for (auto &i : this->groups) {
            int t = this->uses & i.flags;
            if (t == i.flags) {
                this->calceatk += i.atk;
                this->calcedef += i.def;
            }
        }
    }
    
    void PreGroupEffect (int index, int &atk, int &def) {
        int preuses = this->uses | (1 << index);
        for (auto &i : this->groups) {
            if ((preuses & i.flags) == i.flags) {
                atk += i.atk;
                def += i.def;
            }
        }
    }
    
    int All_Score () {
        int atk = 0;
        int def = 0;
        for (int i = 0; i < 30; ++i) {
            if (this->positions[i] == '-') { continue; }
            
            if (this->positions[i] == 'F') {
                atk += this->players[i].atk * 2;
            } else if (this->positions[i] == 'D') {
                def += this->players[i].def * 2;
            } else {
                atk += this->players[i].atk;
                def += this->players[i].def;
            }
        }
        for (auto &i : this->groups) {
            if ((this->uses & i.flags) == i.flags) {
                for (auto &j : i.indexs) {
                    if (this->positions[j] == 'F') {
                        atk += i.atk * 2;
                    } else if (this->positions[j] == 'D') {
                        def += i.def * 2;
                    } else {
                        atk += i.atk;
                        def += i.def;
                    }
                }
            }
        }
        
        return min(atk, def) + (atk+def)/2;////////////////////
    }
    int All_Score2 () {
        int atk = 0;
        int def = 0;
        int agg = 0;
        for (int i = 0; i < 30; ++i) {
            if (this->positions[i] == '-') { continue; }
            
            if (this->positions[i] == 'F') {
                atk += this->players[i].atk * 2;
            } else if (this->positions[i] == 'D') {
                def += this->players[i].def * 2;
            } else {
                atk += this->players[i].atk;
                def += this->players[i].def;
            }
            agg += this->players[i].agg;
        }
        cerr << "r" << min(atk, def)*5 << "(" << agg << ")" << endl;
        for (auto &i : this->groups) {
            if ((this->uses & i.flags) == i.flags) {
                for (auto &j : i.indexs) {
                    if (this->positions[j] == 'F') {
                        atk += i.atk * 2;
                    } else if (this->positions[j] == 'D') {
                        def += i.def * 2;
                    } else {
                        atk += i.atk;
                        def += i.def;
                    }
                    agg += i.agg;
                }
            }
        }
        cerr << "e" << min(atk, def)*5 << "(" << agg << ")" << endl;
        return min(atk, def);
    }
    vector<string> ToRet () {
        vector<string> ret;
        for (int i = 0; i < 30; ++i) {
            if (this->positions[i] == '-') { continue; }
            ret.emplace_back(print((char)this->positions[i], i));
        }
        return ret;
    }
    
    static vector<string> ToRet (Team t, vector<int> positions) {
        vector<string> ret;
        for (int i = 0; i < 30; ++i) {
            if (positions[i] == '-') { continue; }
            ret.emplace_back(print((char)positions[i], i));
        }
        
        for (int j = 0; j < 10; ++j) {
            if (ret[j][0] == 'F') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].atk > point) {
                        index = i;
                        point = t.players[i].atk;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
            if (ret[j][0] == 'D') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].def > point) {
                        index = i;
                        point = t.players[i].def;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
            if (ret[j][0] == 'M') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].atk+t.players[i].def - abs(t.players[i].atk-t.players[i].def)/2 > point) {
                        index = i;
                        point = t.players[i].atk+t.players[i].def - abs(t.players[i].atk-t.players[i].def)/2;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
        }
        
        for (int j = 0; j < 10; ++j) {
            if (ret[j][0] == 'F') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].atk > point) {
                        index = i;
                        point = t.players[i].atk;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
            if (ret[j][0] == 'D') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].def > point) {
                        index = i;
                        point = t.players[i].def;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
            if (ret[j][0] == 'M') {
                int point = -1;
                int index = 0;
                for (int i = 0; i < 30; ++i) {
                    if (positions[i] != '-') { continue; }
                    if (t.players[i].atk+t.players[i].def - abs(t.players[i].atk-t.players[i].def)/2 > point) {
                        index = i;
                        point = t.players[i].atk+t.players[i].def - abs(t.players[i].atk-t.players[i].def)/2;
                    }
                }
                ret[j] += ',' + to_string(index);
                positions[index] = 'x';
            }
        }
        
        
        
        //cerr << print(ret) << endl;
        
        
        return ret;
    }
};


class WorldCupLineup {
public:
    Team team;
    StopWatch sw;
    vector<string> selectPositions(vector<string> players, vector<string> groups) {
        
        vector<string> ret;
        this->team.InputPlayers(players);
        this->team.InputGroups(groups);
        
        for (int j = 0; j < 10; ++j) {
            ret.emplace_back(this->team.NextMaxPlayer());
            // this->team.Use(j, 'F');
        }
        
        //this->team.All_Score2();
        return Team::ToRet(this->team, this->SA(3000));
        // return this->team.ToRet();
    }
    
    vector<int> SA (int limit) {
        vector<int> ret = this->team.positions;
        double bestscore = this->team.All_Score();
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        
        int loop = 500;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            
            for (int i = 0; i < loop; ++i) {
                
                int a = xrnd() % 30;
                int b = xrnd() % 30;
                char tp = this->team.positions[a];
                double btscore = 0;
                char bp = 'F';
                if (this->team.positions[a] == '-') { continue; }
                if (this->team.positions[b] != '-') { continue; }
                
                // {
                //     this->team.Remove(a);
                //     this->team.Use(b, 'F');
                //     int tscore = this->team.All_Score();
                //     if (tscore > btscore) {
                //         btscore = (double)tscore;
                //         bp = 'F';
                //     }
                //     this->team.Remove(b);
                //     this->team.Use(a, tp);
                // }
                // {
                //     this->team.Remove(a);
                //     this->team.Use(b, 'D');
                //     int tscore = this->team.All_Score();
                //     if (tscore > btscore) {
                //         btscore = (double)tscore;
                //         bp = 'D';
                //     }
                //     this->team.Remove(b);
                //     this->team.Use(a, tp);
                // }
                // {
                //     this->team.Remove(a);
                //     this->team.Use(b, 'M');
                //     int tscore = this->team.All_Score();
                //     if (tscore > (double)btscore) {
                //         btscore = tscore;
                //         bp = 'M';
                //     }
                //     this->team.Remove(b);
                //     this->team.Use(a, tp);
                // }
                
                {
                    this->team.Remove(a);
                    bp = "FMD"[xrnd()%3];
                    this->team.Use(b, bp);
                    btscore = (double)this->team.All_Score();
                    this->team.Remove(b);
                    this->team.Use(a, tp);
                }
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                double startTemp   = 256.0;
                double endTemp     = 0.0;
                double temp        = startTemp + (endTemp - startTemp) * t / T;
                double probability = exp((btscore - lastscore) / temp);
                bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (btscore > lastscore || (FORCE_NEXT)) {
                    lastscore = btscore;
                    
                    this->team.Remove(a);
                    this->team.Use(b, bp);
                    
                    if (btscore > bestscore) {
                        bestscore = btscore;
                        ret = this->team.positions;
                    }
                } else {
                    
                }
            }
            
            for (int i = 0; i < 30; ++i) {
                int a = i;
                char tp = this->team.positions[a];
                double btscore = 0;
                char bp = 'F';
                if (this->team.positions[a] == '-') { continue; }
                
                {
                    this->team.Remove(a);
                    this->team.Use(a, 'F');
                    int tscore = this->team.All_Score();
                    if (tscore > btscore) {
                        btscore = (double)tscore;
                        bp = 'F';
                    }
                    this->team.Remove(a);
                    this->team.Use(a, tp);
                }
                {
                    this->team.Remove(a);
                    this->team.Use(a, 'D');
                    int tscore = this->team.All_Score();
                    if (tscore > btscore) {
                        btscore = (double)tscore;
                        bp = 'D';
                    }
                    this->team.Remove(a);
                    this->team.Use(a, tp);
                }
                {
                    this->team.Remove(a);
                    this->team.Use(a, 'M');
                    int tscore = this->team.All_Score();
                    if (tscore > (double)btscore) {
                        btscore = tscore;
                        bp = 'M';
                    }
                    this->team.Remove(a);
                    this->team.Use(a, tp);
                }
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                double startTemp   = 256.0;
                double endTemp     = 0.0;
                double temp        = startTemp + (endTemp - startTemp) * t / T;
                double probability = exp((btscore - lastscore) / temp);
                bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (btscore > lastscore || (FORCE_NEXT)) {
                    lastscore = btscore;
                    
                    this->team.Remove(a);
                    this->team.Use(a, bp);
                    
                    if (btscore > bestscore) {
                        bestscore = btscore;
                        ret = this->team.positions;
                    }
                } else {
                    
                }
            }
        }
        
        return ret;
    }
    
    
    
    
    
    
    
};



// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        // string a = "";
        // string b = "";
        // cin >> a >> b;
        // v[i] = a + " " + b;
        cin >> v[i];
        // getline(cin, v[i]);
    }
}

template<class T> void getVector2(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
        string a = "";
        string b = "";
        cin >> a >> b;
        v[i] = a + " " + b;
        
        // getline(cin, v[i]);
    }
}

int main() {
    WorldCupLineup sol;
    int H;
    cin >> H;
    vector<string> players(H);
    getVector(players);
    cin >> H;
    vector<string> groups(H);
    getVector2(groups);

    vector<string> ret = sol.selectPositions(players, groups);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i)
        cout << ret[i] << endl;
    cout.flush();
}
