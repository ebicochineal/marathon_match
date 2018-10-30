#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

#include <time.h>
#include <sys/timeb.h>

int gcnt = 0;

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

class ProductInventory {
private:
    int day = 0;
    vector<int> buy_price;
    vector<int> sell_price;
    vector<int> expires;

public:
    vector< vector<int> > items;
    vector<int> sells;
    vector<int> rsells;
    vector<int> ssells;
    vector<int> profits;
    
    vector<int> maxsell;
    vector<int> minsell;
    
    int profit = 0;
    
    int init(vector<int> buy, vector<int> sell, vector<int> expiration) {
        buy_price = buy;
        sell_price = sell;
        expires = expiration;
        
        for (int i = 0; i < buy.size(); ++i) {
            this->items.emplace_back(vector<int>());
            this->sells.emplace_back(0);
            this->rsells.emplace_back(0);
            this->ssells.emplace_back(0);
            this->profits.emplace_back(0);
            this->maxsell.emplace_back(0);
            this->minsell.emplace_back(10000);
        }
        
        return 0;
    }
    
    
    void VOrder (int index, int n, vector<int> &ret) {
        for (int i = 0; i < n; ++i) {
            this->items[index].emplace_back(this->expires[index]);
            
        }
        this->profit -= n * this->buy_price[index];
        this->profits[index] -= n * this->buy_price[index];
        ret[index] += n;
    }
    
    void Day () {
        for (auto &i : this->items) {
            for (auto &j : i) {
                j -= 1;
            }
        }
    }
    
    void Sell (vector<int> yesterday) {
        
        for (int i = 0; i < yesterday.size(); ++i) {
            if (yesterday[i] == this->items[i].size()) { this->rsells[i] += max(this->day/16, 2); }
            
            vector<int> v;
            for (int j = yesterday[i]; j < this->items[i].size(); ++j) {
                v.emplace_back(this->items[i][j]);
            }
            this->items[i] = v;
            this->profit += yesterday[i] * this->sell_price[i];
            this->profits[i] += yesterday[i] * this->sell_price[i];
        }
    }
    
    void Disposal () {
        
        for (int i = 0; i < this->items.size(); ++i) {
            vector<int> v;
            int cnt = 0;
            for (auto &j : this->items[i]) {
                if (j >= 0) { v.emplace_back(j); }
                if (j < 0) {
                    gcnt += 1;
                    cnt += 1;
                }
            }
            
            this->rsells[i] -= cnt * max((this->day / 16), 2);
            
            this->items[i] = v;
        }
    }
    
    
    vector<int> order(vector<int> yesterday) {
        //cerr << "Day: " << day << "\n";
        
        for (int i = 0; i < yesterday.size(); ++i) {
            if (this->day == 0) {
                this->ssells[i] += yesterday[i];
                this->maxsell[i] = max(this->maxsell[i], yesterday[i]/10);
                this->minsell[i] = min(this->minsell[i], yesterday[i]/10);
            }
            this->sells[i] += yesterday[i];
            this->rsells[i] += yesterday[i];
            this->maxsell[i] = max(this->maxsell[i], yesterday[i]);
            this->minsell[i] = min(this->minsell[i], yesterday[i]);
        }
        
        this->day++;
        
        auto ret = vector<int>(yesterday.size(), 0);
        
        if (this->day == 1) {
            for (int i = 0; i < ret.size(); ++i) {
                this->VOrder(i, max(this->sells[i] / (this->buy_price[i] > 7 ? 6 : 5)+this->expires[i] / 3 + 1, 3+this->expires[i] / 3), ret);
            }
        } else {
            this->Day();
            this->Sell(yesterday);
            this->Disposal();
            for (int i = 0; i < ret.size(); ++i) {
                int n = this->rsells[i] / (10 + this->day -1);
                
                double t = 0;
                if (this->expires[i] < 7) {
                    t += (double)ret.size()/((n>4 ? 50.0 : 40.0));
                } else {
                    t += (double)ret.size()/(40.0+this->day);
                }
                
                t += min((this->expires[i] - 3) * 0.2, 2.0);
                if (this->expires[i] < 3) { t -= (2 - this->expires[i])*0.2; }
                t += ((double)this->sell_price[i]/(double)this->buy_price[i] - 1)*0.4;
                t += (2 - this->buy_price[i])*0.2;
                t += 4.0 - (max(this->day - 40.0, 0.0) / 60.0)*2.0;
                n += t;
                if (this->items[i].size() < n) {
                    this->VOrder(i, max(yesterday[i], n - (int)this->items[i].size()), ret);
                }
                
            }
        }
        //if (this->day == 1) { cerr << "<cerr>" << 1 << "</cerr>"<< endl; }
        
        return ret;
    }
};







// Do not submit the main.
int main() {
    int n;
    vector<int> buy;
    vector<int> sell;
    vector<int> expiration;
    vector<int> yesterday;
    vector<int> res;

    cin >> n;
    buy.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> buy[i];
    }

    cin >> n;
    sell.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> sell[i];
    }

    cin >> n;
    expiration.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> expiration[i];
    }

    ProductInventory *sol = new ProductInventory;
    cout << sol->init(buy, sell, expiration) << "\n";
    cout << flush;

    for (int k = 0; k < 100; k++) {
        cin >> n;
        yesterday.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> yesterday[i];
        }

        res = sol->order(yesterday);

        cout << res.size() << "\n";
        for (int i = 0; i < (int)res.size(); i++) {
            cout << res[i] << "\n";
        }
        
        cout << flush;
    }
    
    
    
    delete sol;
    return 0;
}
