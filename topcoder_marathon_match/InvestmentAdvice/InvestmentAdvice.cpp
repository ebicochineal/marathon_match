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

class InvestmentAdvice {
public:
    int cnt = 0;
    int size = 0;
    vector<int> prevret;
    vector<int> prevadv;
    vector<double> accuracy;
    vector<int> accuracy_cnt;
    
    void calc_accuracy (vector<int> advice, vector<int> recent) {
        vector<double> diff(this->size);
        vector<double> diff2(this->size);
        for (int i = 0; i < this->size; ++i) {
            double d = ((double)this->prevret[i]) / 100.0;
            if (this->prevret[i] > 0) {
                diff[i] = ((double)recent[i]) / d;
                diff2[i] = abs(this->prevadv[i]-diff[i]);
                
                if (diff2[i] > (this->cnt > 16 ? min(10.0 + (this->cnt * 0.2) + ((this->accuracy[i] * 10.0)-0.6)*0.2, 20.0) : 10)) {
                } else {
                    this->accuracy_cnt[i] += 1;
                }
                
                if (this->cnt > 32) {
                    this->accuracy[i] = (this->accuracy[i]+((double)this->accuracy_cnt[i] / (double)this->cnt))/2.0;
                } else {
                    this->accuracy[i] = (double)this->accuracy_cnt[i] / (double)this->cnt;
                }
            }
        }
    }
    
    void init_accuracy (vector<int> advice, vector<int> recent) {
        this->accuracy = vector<double>(this->size, 1.0);
        this->accuracy_cnt = vector<int>(this->size, 1);
    }
    
    bool initb = true;
    int allrounds;
    
    vector<int> getInvestments(vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
        vector<double> adv(advice.size(), 0.0);
        
        this->cnt += 1;
        if (this->initb) {
            this->size = advice.size();
            this->allrounds = roundsLeft;
            this->initb = false;
            this->init_accuracy(advice, recent);
        } else {
            this->calc_accuracy(advice, recent);
        }
        
        int tmoney = money;
        
        vector<int> ret(advice.size(), 0);
        int abet = 24;
        for (int i = 0; i < ret.size(); ++i) {
            if (money > abet) {
                ret[i] = abet;
                money -= abet;
            } else {
                break;
            }
        }
        
        vector< pair<double, int> > vii;
        
        for (int i = 0; i < advice.size(); ++i) {
            adv[i] = advice[i];
            if (this->accuracy[i] > 0.9  && this->cnt > 4 ) { adv[i] *= (this->cnt > 32 ? 1.75: 1.5 ); }
            if (this->accuracy[i] > 0.85 && this->cnt > 8 ) { adv[i] *= (this->cnt > 40 ? 1.5: 1.25); }
            if (this->accuracy[i] > 0.75 && this->cnt > 12) { adv[i] *= (this->cnt > 48 ? 1.5: 1.25); }
            if (this->accuracy[i] < 0.8) { adv[i] *= ( this->cnt > 32 ? 0.7 : 0.8); }
            if (this->accuracy[i] < 0.7) { adv[i] *= ( this->cnt > 32 ? 0.8 : 0.9); }
            if (this->accuracy[i] < 0.6) { adv[i] *= ( this->cnt > 32 ? 0.8 : 0.9); }
            if (adv[i] >= 0) {
                vii.emplace_back(adv[i] * 100000 + this->accuracy[i]*100, i);
            }
        }
        
        
        sort(vii.begin(), vii.end(), [](const pair<double, int> &a, const pair<double, int> &b) { return a.first > b.first; });
        
        int bet = 400000;
        
        for (int i = 0; i < vii.size(); ++i) {
            bet = min(money, 400000);
            
            ret[vii[i].second] = min(ret[vii[i].second]+bet, 400000);
        
            money = tmoney;
            for (auto &i : ret) { money -= i; }
        }
        
        this->prevadv = advice;
        this->prevret = ret;
        return ret;
    }
};

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
