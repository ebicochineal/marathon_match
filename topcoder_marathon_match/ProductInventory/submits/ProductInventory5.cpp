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
        //for (auto &i : this->items) {
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
            if (cnt < 1) {
                this->sells[i] += 1;
                //this->sells[i] -= cnt / 2;
            } else {
                this->sells[i] -= cnt / 2;
                
            }
            
            this->rsells[i] -= cnt;
            this->items[i] = v;
        }
    }
    
    
    vector<int> order(vector<int> yesterday) {
        //cerr << "Day: " << day << "\n";
        
        for (int i = 0; i < yesterday.size(); ++i) {
            if (this->day == 0) { this->ssells[i] += yesterday[i];}
            this->sells[i] += yesterday[i];
            this->rsells[i] += yesterday[i];
            
        }
        
        
        this->day++;
        
        auto ret = vector<int>(yesterday.size(), 0);
        
        // for (int i = 0; i < ret.size(); ++i) {
        //     this->VOrder(i, 0, ret);
        // }
        // return ret;
        
        if (this->day == 1) {
            for (int i = 0; i < ret.size(); ++i) {
                this->VOrder(i, max(this->sells[i] / (this->expires[i] < 1 && this->buy_price[i] > 7 ? 6 : 5)+2, 3), ret);
            }
        } else {
            this->Day();
            this->Sell(yesterday);
            this->Disposal();
            for (int i = 0; i < ret.size(); ++i) {
                int n = this->sells[i] / (10 + this->day -1);
                if (0) {
                    
                    int x = (n > 4 || this->expires[i] > 4 ? 5 : 4);
                    //x = (n > 6 && this->expires[i] > 2 && this->sell_price[i] / this->buy_price[i] > 1 ? 8 : x);
                    x -= (n < 2 && this->expires[i] < 1 && this->buy_price[i] > 6 ? 1 : 0);
                    //x += this->profit > 5000 && n < 2 ? 0 : 1;
                    if (this->items[i].size() < x) {
                        this->VOrder(i, max(yesterday[i], x), ret);
                    } else {
                        this->VOrder(i, yesterday[i], ret);
                    }
                    
                } else {
                    if (this->day < 8 && this->expires[i] > 0 && n < 3) {
                        n = this->sells[i] / (10 + this->day - 1);
                        int x = (n > 5 || this->expires[i] > 7 ? max(5, n) : 4);
                        x = (n < 2 && this->expires[i] < 1 && this->buy_price[i] > 6 ? 3 : x);
                        
                        if (this->items[i].size() < x) {
                            this->VOrder(i, max(yesterday[i], x) + (this->day < 5 ? 1 : 0), ret);
                        } else {
                            this->VOrder(i, min(yesterday[i], n), ret);
                        }
                        this->VOrder(i, 1, ret);
                    } else if (this->day < 50) {
                        n = this->sells[i] / (10 + this->day - 1);
                        int x = (n > 5 || this->expires[i] > 7 ? max(5, n) : 4);
                        x = (n < 2 && this->expires[i] < 1 && this->buy_price[i] > 6 ? 3 : x);
                        
                        if (this->items[i].size() < x) {
                            this->VOrder(i, max(yesterday[i], x) + (this->day < 5 ? 1 : 0), ret);
                        } else {
                            this->VOrder(i, min(yesterday[i], n), ret);
                        }
                    } else {
                        n = this->rsells[i] / (10 + this->day - 1);
                        int x = (n > 5 || this->expires[i] > 7 ? max(5, n) : 4);
                        x = (n < 2 && this->expires[i] < 1 && this->buy_price[i] > 5 ? 3 : x);
                        
                        if (this->items[i].size() < x) {
                            this->VOrder(i, max(yesterday[i], x), ret);
                        } else {
                            this->VOrder(i, min(yesterday[i], n), ret);
                        }
                    }
                }
            }
        }
        //if (this->day == 100) { cerr << "<cerr>" <<this->profit << "</cerr>"<< endl; }
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






