// C++11
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <array>
#include <unordered_set>
#include <unordered_map>
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

// if (r.nextDouble() < accuracy[i]) {
//     reported[i] = (int)Math.round(Math.min(100, Math.max(-100, r.nextGaussian() * stDev[i] + actual[i] * 100)));
// } else {
//     reported[i] = (int)Math.round(100 * Math.min(1, Math.max(-1, r.nextGaussian() * 0.1)));
// }

class InvestmentAdvice {
public:
    int cnt = 0;
    int size = 0;
    vector<int> prevrec;
    vector<int> prevret;
    vector<int> prevadv;
    vector<double> accuracy;
    vector<double> accuracy2;
    vector<int> accuracy_cnt;
    
    // int sprint (vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
    //     cerr << print("ad :", advice.size(), "  le :", roundsLeft);
    //     return 0;
    // }
    
    void calc_accuracy (vector<int> advice, vector<int> recent) {
        vector<double> diff(this->size);
        vector<double> diff2(this->size);
        for (int i = 0; i < this->size; ++i) {
            double d = ((double)this->prevret[i]) / 100.0;
            if (this->prevret[i] > 0) {
                diff[i] = (double)recent[i] / d;
                diff2[i] = abs(this->prevadv[i]-diff[i]);
                // if (diff2[i] > 14) {
                // if (diff2[i] > 12) {
                // if (diff2[i] > 10) {
                // double n = 11.5;
                // if (this->accuracy[i] < 0.95 ) { n = 12; }
                // if (this->accuracy[i] < 0.925) { n = 12.5; }
                // if (this->accuracy[i] < 0.9  ) { n = 13; }
                // if (this->accuracy[i] < 0.875) { n = 13.5; }
                // if (this->accuracy[i] < 0.85 ) { n = 14; }
                // if (this->accuracy[i] < 0.825) { n = 14; }
                // if (this->accuracy[i] < 0.8  ) { n = 14.5; }
                // if (this->accuracy[i] < 0.775) { n = 15; }
                // if (this->accuracy[i] < 0.75 ) { n = 15.5; }
                // if (this->accuracy[i] < 0.725) { n = 16; }
                // if (this->accuracy[i] < 0.6  ) { n = 16.5; }
                // if (diff2[i] > (this->cnt > 16 ? n-2.0 : 10.0)) {
                
                // if (diff2[i] > (this->cnt > 16 ? min(max(8, (int)(4 + this->accuracy[i] * 16) ), 20) : 14)) {
                // if (diff2[i] > (this->cnt > 16.0 ? min(max(6.0, 14.0 - ((this->accuracy[i] * 10.0)-0.6))*2.0, 16.0) : 10.0)) {// b
                // if (diff2[i] > (this->cnt > 16.0 ? min(max(6.0, 15.0 - ((this->accuracy[i] * 10.0)-0.6)*2.0), 16.0) : 10.0)) {
                    
                if (diff2[i] > (this->cnt > 16 ? min(10.0 + (this->cnt * 0.2), 16.0) : 10)) {
                    
                    // x
                } else {
                    // o
                    this->accuracy_cnt[i] += 1;
                }
                this->accuracy2[i] += diff2[i];
                this->accuracy[i] = ((double)this->accuracy_cnt[i] / (double)this->cnt);
                // this->accuracy[i] = (this->accuracy[i]+((double)this->accuracy_cnt[i] / (double)this->cnt))/2.0;
                
            }
        }
        
        // this->accuracy=vector<double>{0.407, 0.658,0.152,0.554,0.487,0.159,0.864,0.583,0.761,0.879,0.004,0.023,0.275,0.610,0.274,0.001,0.48625958231,0.12657499274,0.206,0.406,0.520,0.271,0.228,0.586,0.265,0.878,0.051,0.636,0.340,0.116,0.546,0.015,0.242};
        // this->accuracy=vector<double>{ 0.805, 0.575, 0.352, 0.411, 0.864, 0.576, 0.138, 0.542, 0.810, 0.074, 0.730, 0.116, 0.549, 0.358, 0.097, 0.340, 0.232, 0.207, 0.425, 0.458, 0.546, 0.351, 0.936, 0.917, 0.114, 0.911, 0.185, 0.412, 0.291, 0.170, 0.262, 0.298, 0.949, 0.315, 0.604, 0.132, 0.050, 0.034};
        
        if (this->lastb) {
            // cerr << print(accuracy) << endl;
            // cerr << print(this->prevret) << endl;
            // cerr << print(vector<double>{0.407, 0.658,0.152,0.554,0.487,0.159,0.864,0.583,0.761,0.879,0.004,0.023,0.275,0.610,0.274,0.001,0.48625958231,0.12657499274,0.206,0.406,0.520,0.271,0.228,0.586,0.265,0.878,0.051,0.636,0.340,0.116,0.546,0.015,0.242}) << endl;
            
        }
    }
    
    void init_accuracy (vector<int> advice, vector<int> recent) {
        this->accuracy = vector<double>(this->size, 1.0);
        this->accuracy2 = vector<double>(this->size, 0.0);
        this->accuracy_cnt = vector<int>(this->size, 1);
    }
    bool initb = true;
    bool lastb = false;
    int allrounds;
    vector<int> getInvestments(vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
        return this->getInvestmentsB(advice, recent, money, timeLeft, roundsLeft);
    }
    vector<int> getInvestmentsA(vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
        this->cnt += 1;
        if (roundsLeft == 1) { this->lastb = true; }
        if (this->initb) {
            this->size = advice.size();
            this->allrounds = roundsLeft;
            this->initb = false;
            this->init_accuracy(advice, recent);
            
            // this->sprint(advice, recent, money, timeLeft, roundsLeft);
        } else {
            this->calc_accuracy(advice, recent);
        }
        
        int tmoney = money;
        
        vector<int> ret(advice.size(), 0);
        
        vector< pair<int, int> > vii;
        
        for (int i = 0; i < advice.size(); ++i) {
            if (advice[i] >= 0) {
                vii.emplace_back(advice[i] , i);
            }
            
        }
        
        sort(vii.begin(), vii.end(), [](const pair<int, int> &a, const pair<int, int> &b) { return a.first > b.first; });
        
        int bet = 400000;
        for (int i = 0; i < (int)vii.size(); ++i) {
            bet = min(money, 400000);
            
            ret[vii[i].second] = min(ret[vii[i].second]+bet, 400000);
        
            money = tmoney;
            for (auto &i : ret) { money -= i; }
        }
        
        
        this->prevrec = recent;
        this->prevadv = advice;
        this->prevret = ret;
        return ret;
    }
    vector<int> getInvestmentsB(vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
        // cerr << print("a",advice) << endl;
        // cerr << print("r",recent) << endl;
        // cerr << print(money) << endl;
        
        vector<double> adv(advice.size(), 0.0);
        
        this->cnt += 1;
        if (roundsLeft == 1) { this->lastb = true; }
        if (this->initb) {
            this->size = advice.size();
            this->allrounds = roundsLeft;
            this->initb = false;
            this->init_accuracy(advice, recent);
            
            // this->sprint(advice, recent, money, timeLeft, roundsLeft);
        } else {
            this->calc_accuracy(advice, recent);
        }
        
        int tmoney = money;
        
        vector<int> ret(advice.size(), 0);
        
        // if (this->allrounds > 15) {
            int abet = 25;
            // if (this->cnt > 10) { abet -= 2; }
            // if (this->cnt > 20) { abet -= 2; }
            // if (this->cnt > 30) { abet -= 2; }
            // if (this->cnt > 40) { abet -= 2; }
            // if (this->cnt > 50) { abet -= 2; }
            for (int i = 0; i < ret.size(); ++i) {
                if (money > abet) {
                    ret[i] = abet;
                    money -= abet;
                } else {
                    break;
                }
            }
        // }
        
        vector< pair<double, int> > vii;
        
        for (int i = 0; i < advice.size(); ++i) {
            double t = this->accuracy2[i] / this->cnt;
            adv[i] = advice[i];
            if (this->accuracy[i] > 0.9  && this->cnt > 4 ) { adv[i] *= (this->cnt > 16 ? 1.75: 1.5 ); }
            if (this->accuracy[i] > 0.85 && this->cnt > 8 ) { adv[i] *= (this->cnt > 20 ? 1.5: 1.25); }
            if (this->accuracy[i] > 0.75 && this->cnt > 16) { adv[i] *= (this->cnt > 24 ? 1.5: 1.25); }
            if (this->accuracy[i] < 0.8) { adv[i] *= ( this->cnt > 16 ? 0.7 : 0.8); }
            if (this->accuracy[i] < 0.7) { adv[i] *= ( this->cnt > 20 ? 0.8 : 0.9); }
            if (this->accuracy[i] < 0.6) { adv[i] *= ( this->cnt > 24 ? 0.8 : 0.9); }
            if (adv[i] >= 0) {
                vii.emplace_back(adv[i] * 100000 + this->accuracy[i]*100, i);
            }
        }
        
        
        sort(vii.begin(), vii.end(), [](const pair<double, int> &a, const pair<double, int> &b) { return a.first > b.first; });
        
        int bet = 400000;
        
        for (int i = 0; i < vii.size(); ++i) {
            // bet = min(money, (money < 400000 && this->cnt < 6 && ret.size() > 25 ? (int)(400000/(vii.size()/2)) : 400000));
            bet = min(money, 400000);
            
            ret[vii[i].second] = min(ret[vii[i].second]+bet, 400000);
        
            money = tmoney;
            for (auto &i : ret) { money -= i; }
        }
        
        
        this->prevrec = recent;
        this->prevadv = advice;
        this->prevret = ret;
        return ret;
    }
};

// test 1 100
// Sum : 1002033721.0     PrevSum : 971686549.0
// up : 78     down : 22
//   3.663273%   4.261739%  -0.598466%

// test 100 100
// Sum : 872083979.0     PrevSum : 841285113.0
// up : 80     down : 20
//   4.007496%   4.510315%  -0.502820%

// test 200 100
// Sum : 1020809940.0     PrevSum : 996930556.0
// up : 67     down : 33
//   2.644865%   3.368513%  -0.723648%

// test 5126 1000
// Sum : 9169759765.0     PrevSum : 8914151222.0
// up : 736     down : 264
//   3.274258%   3.967097%  -0.692839%

// test 51260 1000
// Sum : 9490987953.0     PrevSum : 9252200555.0
// up : 731     down : 269
//   3.001505%   3.730156%  -0.728651%

// test 512600 1000
// Sum : 8964517777.0     PrevSum : 8698678458.0
// up : 762     down : 238
//   3.524526%   4.234862%  -0.710336%

// test 5126 10000
// Sum : 90891525266.0     PrevSum : 88481041659.0
// up : 7344     down : 2656
//   3.115242%   3.857560%  -0.742319%

// test 100000 10000
// Sum : 90806198642.0     PrevSum : 88385324459.0
// up : 7339     down : 2661
//   3.131532%   3.889808%  -0.758276%


// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
    InvestmentAdvice sol;
    int roundsLeft = 99;
    while (roundsLeft > 1) {
        int A;
        cin >> A;
        vector<int> advice(A);
        getVector(advice);
        int R;
        cin >> R;
        vector<int> recent(R);
        getVector(recent);
        int money;
        int timeLeft;
        cin >> money;
        cin >> timeLeft;
        cin >> roundsLeft;
        vector<int> ret = sol.getInvestments(advice, recent, money, timeLeft, roundsLeft);
        cout << ret.size() << endl;
        for (int i = 0; i < (int)ret.size(); ++i)
            cout << ret[i] << endl;
        cout.flush();
        
        
    }
}
