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
        return ((this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm));
    }
};

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

float skill[205];
float raw[205];
float tskill[205];
double scores[25];
double tscorea;
double tscoreb;

class ContestOrganizer {
public:
    int N, M;
    vector< vector<int> > wins;
    StopWatch sw;
    
    int gcnt = 0;
    float o;
    
    vector< vector<float> > rskills;
    
    vector<string> makeTeams (int M, vector<string> wins) {
        this->sw = StopWatch();
        this->N = wins.size();
        this->M = M;
        
        this->wins = this->vstovvi(wins);
        this->initSkill1();
        
        for (int i = 0; i < this->N; ++i) {
            tskill[i] = skill[i];
        }
        this->skillSA(300);
        this->skillSA(300);
        this->skillSA(300);
        
        vector<string> ret(this->M, "");
        for(int i = 0; i < this->N; i++) {
            int t = i % this->M;
            if(ret[t] == "") {
                ret[t] = to_string(i);
            } else {
                ret[t] += " " + to_string(i);
            }
        }
        
        auto vviret = this->vstovvi(ret);
        auto bestret = vviret;
        double bestscore = this->allScoreR(bestret);
        
        vector< pair<double, vector< vector<int> > > > vret;
        
        int p = (9800 - this->sw.get_milli_time()) / 25;
        
        for (int i = 0; i < 25; ++i) {
            auto tret = this->SA(p, vviret);
            double score = this->allScore(tret);
            
            vret.emplace_back(score, tret);
            // if (score > bestscore) {
            //     bestscore = score;
            //     bestret = tret;
            // }
        }
        
        sort(vret.begin(), vret.end(), [](const pair<double, vector< vector<int> > >& a, const pair<double, vector< vector<int> > >& b) { return a.first > b.first; });
        
        for (int i = 0; i < 10; ++i) {
            auto tret = vret[i].second;
            double score = this->allScoreR(tret);
            
            if (score > bestscore) {
                bestscore = score;
                bestret = tret;
            }
        }
        // bestret = this->SA2(800, bestret);
        
        pdebug(this->gcnt);
        pdebug(this->allScore(bestret));
        pdebug(this->N, this->M);
        pdebug("t", this->sw.get_milli_time());
        
        pdebug(this->o*(21-this->M));
        
        return this->vvitovs(bestret);
    }
    
    void initSkill1 () {
        
        for (int i = 0; i < 8; ++i) {
            vector<float> t;
            for (int j = 0; j < this->N; ++j) {
                t.emplace_back(xrnd()%65-32);
            }
            this->rskills.emplace_back(t);
        }
        
        for (int i = 0; i < this->N; ++i) { skill[i] = 550; }
        this->o = 3;
        this->o = max(this->wins[0][1]+this->wins[1][0], (int)this->o);
        this->o = max(this->wins[1][2]+this->wins[2][1], (int)this->o);
        this->o = max(this->wins[2][3]+this->wins[3][2], (int)this->o);
        pdebug(this->o);
        
        vector<double> sums(this->N);
        
        for (int i = 0; i < 16; ++i) {
            for (int n = 0; n < this->N; ++n) {
                sums[n] = 0;
                for (int k = 0; k < this->N; ++k) {
                    sums[n] += this->wins[n][k] * max((double)skill[k], 0.1);
                }
            }
            for (int y = 0; y < this->N; ++y) {
                for (int x = 0; x < this->N; ++x) {
                    if (x == y) { continue; }
                    double a = this->wins[x][y];
                    double b = this->wins[y][x];
                    
                    double w = a / this->o;
                    double l = b / this->o;
                    // sums[x] = 0;
                    // for (int k = 0; k < this->N; ++k) {
                    //     sums[x] += this->wins[x][k] * max((double)skill[k], 0.1);
                    // }
                    // sums[y] = 0;
                    // for (int k = 0; k < this->N; ++k) {
                    //     sums[y] += this->wins[y][k] * max((double)skill[k], 0.1);
                    // }
                    
                    if (sums[x] > sums[y]) {
                        skill[x] = skill[x] + 16 * l;
                        skill[y] = skill[y] - 16 * w;
                    }
                    if (sums[y] > sums[x]) {
                        skill[x] = skill[x] - 16 * l;
                        skill[y] = skill[y] + 16 * w;
                    }
                }
            }
            
            
        }
        
        
        float m = skill[0];
        for (int i = 0; i < this->N; ++i) { m = min(m, skill[i]); }
        for (int i = 0; i < this->N; ++i) { skill[i] += -m + 1; }
        
        m = 0;
        for (int i = 0; i < this->N; ++i) { m = max(m, skill[i]); }
        
        double vmax = 900 - (50-this->o) * 10.0;
        double vmin = 100 + (50-this->o) * 5.0;
        
        for (int i = 0; i < this->N; ++i) {
            skill[i] = (((float)skill[i])/m)*vmax+vmin;
        }
        for (int i = 0; i < this->N; ++i) { raw[i] = skill[i]; }
        
        //for (int i = 0; i < this->N; ++i) { fdebug(skill[i]); }// file
        
        
    }
    
    vector< vector<int> > vstovvi (vector<string> vs) {
        vector< vector<int> > r;
        for (auto&& i : vs) {
            auto t = split(i);
            vector<int> vi;
            for (auto&& j : t) {  vi.emplace_back(stoi(j)); }
            r.emplace_back(vi);
        }
        return r;
    }
    
    vector<string> vvitovs (vector< vector<int> > vvi) {
        vector<string> r;
        for (auto&& i : vvi) {
            string s;
            for (auto&& j : i) {
                if(s == "") {
                    s = to_string(j);
                } else {
                    s += " " + to_string(j);
                }
            }
            r.emplace_back(s);
        }
        return r;
    }
    
    double allScore2 (vector< vector<int> >& ret) {
        double minStrength = 999999;
        double maxStrength = 0;
        for (int i = 0; i < this->M; i++) {
            vector<int> team(ret[i].size());
            for (int j = 0; j < ret[i].size(); j++) {
                team[j] = skill[ret[i][j]];
            }
            sort(team.begin(), team.end(), [](const int& a, const int& b) { return a < b; });
            
            double total = 0;
            for (int j = 0; j < team.size(); j++) {
                total += (j + 0.90) * team[j];
            }
            total *= 2;
            total /= team.size();
            total /= team.size() + 1;
            scores[i] = total;
            minStrength = min(minStrength, total);
            maxStrength = max(maxStrength, total);
            //fdebug(total);
        }
        
        const double score = 1000 / (1 + maxStrength - minStrength);
        
        return score;
    }
    
    
    double allScoreR (vector< vector<int> >& ret) {
        double score = 0;
        
        for (int i = 0; i < this->rskills.size(); ++i) {
            for (int j = 0; j < this->N; ++j) {
                skill[j] = raw[j] + this->rskills[i][j];
            }
            
            score += this->allScore2(ret);
        }
        
        for (int j = 0; j < this->N; ++j) {
            skill[j] = raw[j];
        }
        score /= this->rskills.size();
        score += this->allScore2(ret);
        return score;
    }
    
    double allScore (vector< vector<int> >& ret) {
        double minStrength = 999999;
        double maxStrength = 0;
        for (int i = 0; i < this->M; i++) {
            vector<int> team(ret[i].size());
            for (int j = 0; j < ret[i].size(); j++) {
                team[j] = skill[ret[i][j]];
            }
            sort(team.begin(), team.end(), [](const int& a, const int& b) { return a < b; });
            
            double total = 0;
            for (int j = 0; j < team.size(); j++) {
                total += (j + 1) * team[j];
            }
            total *= 2;
            total /= team.size();
            total /= team.size() + 1;
            scores[i] = total;
            minStrength = min(minStrength, total);
            maxStrength = max(maxStrength, total);
            //fdebug(total);
        }
        
        const double score = 1000 / (1 + maxStrength - minStrength);
        
        return score;
    }
    
    double abScore (vector< vector<int> >& ret, int ia, int ib) {
        double minStrength = 999999;
        double maxStrength = 0;
        
        for (int i = 0; i < this->M; ++i) {
            if (i == ia || i == ib) { continue; }
            minStrength = min(minStrength, scores[i]);
            maxStrength = max(maxStrength, scores[i]);
        }
        
        {
            int i = ia;
            vector<int> team(ret[i].size());
            for (int j = 0; j < ret[i].size(); j++) {
                team[j] = skill[ret[i][j]];
            }
            sort(team.begin(), team.end(), [](const int& a, const int& b) { return a < b; });
            
            double total = 0;
            for (int j = 0; j < team.size(); j++) {
                total += (j + 1) * team[j];
            }
            total *= 2;
            total /= team.size();
            total /= team.size() + 1;
            tscorea = total;
            minStrength = min(minStrength, total);
            maxStrength = max(maxStrength, total);
            //fdebug(total);
        }
        
        {
            int i = ib;
            vector<int> team(ret[i].size());
            for (int j = 0; j < ret[i].size(); j++) {
                team[j] = skill[ret[i][j]];
            }
            sort(team.begin(), team.end(), [](const int& a, const int& b) { return a < b; });
            
            double total = 0;
            for (int j = 0; j < team.size(); j++) {
                total += (j + 1) * team[j];
            }
            total *= 2;
            total /= team.size();
            total /= team.size() + 1;
            tscoreb = total;
            minStrength = min(minStrength, total);
            maxStrength = max(maxStrength, total);
            //fdebug(total);
        }
        
        const double score = 1000 / (1 + maxStrength - minStrength);
        
        return score;
    }
    
    vector< vector<int> > SA (int limit, vector< vector<int> > ret) {
        StopWatch sw;
        
        vector< vector<int> > bestret = ret;
        double bestscore = this->allScore(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 32; ++z) {
                int ma = xrnd() % ret.size();
                if (ret[ma].size() < 2) { continue; }
                int pa = xrnd() % ret[ma].size();
                int mb = xrnd() % ret.size();
                int pb = xrnd() % ret[mb].size();
                if (ma == mb) { continue; }
                int v = ret[ma][pa];
                ret[ma].erase(ret[ma].begin() + pa);
                ret[mb].insert(ret[mb].begin() + pb, v);
                double tmpscore = this->abScore(ret, ma, mb);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 32.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    scores[ma] = tscorea;
                    scores[mb] = tscoreb;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    ret[mb].erase(ret[mb].begin() + pb);
                    ret[ma].insert(ret[ma].begin() + pa, v);
                }
                this->gcnt += 1;
            }
            
            for (int z = 0; z < 32; ++z) {
                int ma = xrnd() % ret.size();
                int pa = xrnd() % ret[ma].size();
                int mb = xrnd() % ret.size();
                int pb = xrnd() % ret[mb].size();
                if (ma == mb) { continue; }
                swap(ret[ma][pa], ret[mb][pb]);
                double tmpscore = this->abScore(ret, ma, mb);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 16.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    scores[ma] = tscorea;
                    scores[mb] = tscoreb;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    swap(ret[ma][pa], ret[mb][pb]);
                }
                this->gcnt += 1;
            }
        }
        return bestret;
    }
    
    vector< vector<int> > SA2 (int limit, vector< vector<int> > ret) {
        StopWatch sw;
        
        vector< vector<int> > bestret = ret;
        double bestscore = this->allScoreR(ret);
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 8; ++z) {
                int ma = xrnd() % ret.size();
                if (ret[ma].size() < 2) { continue; }
                int pa = xrnd() % ret[ma].size();
                int mb = xrnd() % ret.size();
                int pb = xrnd() % ret[mb].size();
                if (ma == mb) { continue; }
                int v = ret[ma][pa];
                ret[ma].erase(ret[ma].begin() + pa);
                ret[mb].insert(ret[mb].begin() + pb, v);
                double tmpscore = this->allScoreR(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 32.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    ret[mb].erase(ret[mb].begin() + pb);
                    ret[ma].insert(ret[ma].begin() + pa, v);
                }
                this->gcnt += 1;
            }
            
            for (int z = 0; z < 8; ++z) {
                int ma = xrnd() % ret.size();
                int pa = xrnd() % ret[ma].size();
                int mb = xrnd() % ret.size();
                int pb = xrnd() % ret[mb].size();
                if (ma == mb) { continue; }
                swap(ret[ma][pa], ret[mb][pb]);
                double tmpscore = this->allScoreR(ret);
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 16.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore > lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    scores[ma] = tscorea;
                    scores[mb] = tscoreb;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestret = ret;
                    }
                } else {
                    swap(ret[ma][pa], ret[mb][pb]);
                }
                this->gcnt += 1;
            }
        }
        return bestret;
    }
    
    
    void skillSA (int limit) {
        StopWatch sw;
        
        float bestskill[205];
        for (int n = 0; n < this->N; ++n) { bestskill[n] = skill[n]; }
        
        double bestscore = this->skillAllScore();
        double lastscore = bestscore;
        int saTimeStart = sw.get_milli_time();
        int saTimeEnd   = limit;
        int saTimeCurrent = saTimeStart;
        int64_t R = 1000000000;
        int cnt = 0;
        while ((saTimeCurrent = sw.get_milli_time()) < saTimeEnd) {
            for (int z = 0; z < 8; ++z) {
                int v = xrnd()%17 - 8;
                int a = xrnd()%this->N;
                float tv = skill[a];
                skill[a] = max(min(skill[a]+v, 900.0f), 100.0f);
                
                double tmpscore = this->skillAllScore();
                
                const double T = saTimeEnd-saTimeStart;
                const double t = saTimeCurrent-saTimeStart;
                const double startTemp   = 8.0;
                const double endTemp     = 0.0;
                const double temp        = startTemp + (endTemp - startTemp) * t / T;
                const double probability = exp((lastscore - tmpscore) / temp);
                const bool FORCE_NEXT    = probability > (double)(xrnd() % R) / R;
                
                if (tmpscore < lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    
                    if (tmpscore < bestscore) {
                        bestscore = tmpscore;
                        for (int n = 0; n < this->N; ++n) { bestskill[n] = skill[n]; }
                        cnt += 1;
                    }
                } else {
                    skill[a] = tv;
                }
                
            }
        }
        
        for (int i = 0; i < 1; ++i) {
            vector<float> vf;
            for (int j = 0; j < this->N; ++j) {
                vf.emplace_back(bestskill[i]-tskill[i]);
            }
            this->rskills.emplace_back(vf);
        }
        
        
        for (int i = 0; i < this->N; ++i) {
            skill[i] = tskill[i];
        }
        
        
        pdebug(cnt);
    }
    
    float skillAllScore () {
        float score = 0;
        for (int i = 0; i < this->N; ++i) {
            for (int j = 0; j < this->N; ++j) {
                
                if (skill[i] < skill[j]) {
                    score += this->diffSkillWin(skill[i], skill[j], this->wins[i][j], this->wins[j][i]);
                } else {
                    score += this->diffSkillWinR(skill[i], skill[j], this->wins[i][j], this->wins[j][i]);
                }
                
            }
        }
        return score;
    }
    
    
    float skillLScore(int i) {
        float score = 0;
        for (int j = i+1; j < this->N; ++j) {
            score += this->diffSkillWin(skill[i], skill[j], this->wins[i][j], this->wins[j][i]);
        }
        return score;
    }
    
    inline float diffSkillWin (const float& sa, const float& sb, const int& wa, const int& wb) {
        const float x = sa/sb;
        const float y = ((float)wa*10000.0+1) / ((float)wb*10000.0+1);
        
        return abs(x-(y+0.125));
        
    }
    
    inline float diffSkillWinR (const float& sb, const float& sa, const int& wb, const int& wa) {
        const float x = sa/sb;
        const float y = ((float)wa*10000.0+1) / ((float)wb*10000.0+1);
        
        return abs(x-(y+0.15));
        
    }
    
};

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) { getline(cin, v[i]); }
}

int main() {
    ContestOrganizer co;
    
    string s;
    int M, N;
    getline(cin, s);
    M = atoi(s.c_str());
    getline(cin, s);
    N = atoi(s.c_str());
    
    vector<string> wins(N);
    getVector(wins);
    
    vector<string> ret = co.makeTeams(M, wins);
    cerr.flush();
    
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) { cout << ret[i] << endl; }
    cout.flush();

    return 0;
}

