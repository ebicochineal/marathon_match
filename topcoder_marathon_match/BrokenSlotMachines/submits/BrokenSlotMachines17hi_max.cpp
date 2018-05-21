// C++11
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <unordered_map>

using namespace std;

///////////////////////
class Random {
public:
    uint64_t y;
    Random () {
        this->y = 2463534242;
    }
    
    Random (uint64_t seed) {
        this->y = 2463534242 + seed;
    }
    
    int nextInt (int n) {
        return this->xrnd() % n;
    }
    
    int nextInt () {
        return this->xrnd();
    }
    
    uint64_t nextLong () {
        return this->xrnd();
    }
    
    inline uint32_t xrnd() {
        this->y = this->y ^ (this->y << 13);
        this->y = this->y ^ (this->y >> 17);
        return this->y = this->y ^ (this->y << 5);
    }
};

vector< vector<string> > wheels;
int g_coins;
int g_rawcoins;
int g_maxTime;
int g_noteTime;
int g_numMachines;
vector<Random> machineState;
vector<int> payouts;
vector<double> expected;
vector<int> wheelSize;
bool failed = false;

class PlaySlots {
public:
    static int quickPlay (int machineNumber, int times) {
        if (times <= 0 || machineNumber < 0 || machineNumber >= g_numMachines) {
            // longTest.addFatalError("Invalid parameters passed to quickPlay().\n");
            failed = true;
            return -1;
        }
        if (times > g_maxTime) {
            // longTest.addFatalError("Attempted to play after time ran out.\n");
            failed = true;
            return -1;
        }
        g_maxTime -= times;  
        return stoi(doPlay(machineNumber, times)[0]);
        
        
        
        // if (times > g_maxTime) {
        //     //longTest.addFatalError("Attempted to play after time ran out.\n");
        //     cout << "Attempted to play after time ran out.\n";
        //     failed = true;
        //     return -1;
        // }
        // g_maxTime -= times;
        
        // return stoi(doPlay(machineNumber, times)[0]);
    }
    
    static vector<string> notePlay (int machineNumber, int times) {
        
        if (times <= 0 || machineNumber < 0 || machineNumber >= g_numMachines) {
            //longTest.addFatalError("Invalid parameters passed to notePlay().\n");
            failed = true;
            return vector<string>{"-1"};
        }
        if (times > g_maxTime || times * g_noteTime > g_maxTime) {
            //longTest.addFatalError("Attempted to play after time ran out.\n");
            failed = true;
            return vector<string>{"-1"};
        }
        g_maxTime -= times * g_noteTime;
        return doPlay(machineNumber, times);
        
        
        
        // if (times * g_noteTime > g_maxTime) {
        //     // longTest.addFatalError("Attempted to play after time ran out.\n");
        //     cout << "Attempted to play after time ran out.\n";
        //     failed = true;
        //     return vector<string>{"-1"};
        // }
        // g_maxTime -= times * g_noteTime;
        // return doPlay(machineNumber, times);
    }
    
    static vector<string> doPlay(int machineNumber, int times) {
        if (failed) return vector<string>{"-1"};
        int win = 0;
        vector<string> ret(times + 1);
        for (int i = 0; i < times; i++) {
            if (g_coins <= 0) {
                //longTest.addFatalError("Attempted to play after coins ran out.\n");
                cout << "Attempted to play after coins ran out.\n";
                failed = true;
                return vector<string>{"-1"};
            }
            g_coins--;
            Random &r = machineState[machineNumber];
            int w = wheelSize[machineNumber];
            vector<int> res = {r.nextInt(w), r.nextInt(w), r.nextInt(w)};
            ret[i + 1] = "";
            for (int j = -1; j <= 1; j++)
            for (int k = 0; k < 3; k++)
                ret[i + 1] += wheels[machineNumber][k][res[k] + w + j];
            if ((ret[i + 1][3] != ret[i + 1][4]) || (ret[i + 1][3] != ret[i + 1][5]))
            continue;
            if (ret[i + 1][3] == 'A') win += 1000;
            if (ret[i + 1][3] == 'B') win +=  200;
            if (ret[i + 1][3] == 'C') win +=  100;
            if (ret[i + 1][3] == 'D') win +=   50;
            if (ret[i + 1][3] == 'E') win +=   20;
            if (ret[i + 1][3] == 'F') win +=   10;
            if (ret[i + 1][3] == 'G') win +=    5;
        }
        ret[0] = to_string(win);
        g_coins += win;
        return ret;
    }
};
/////////////////////////////
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <unordered_map>

using namespace std;

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

inline int count (string s, char t) {
    int cnt = 0;
    for (auto &i : s) { if (i == t) { cnt += 1; } }
    return cnt;
}

inline string sunion (string &a, string &b) {
    int sa = a.size();
    int sb = b.size();
    string r = "";
    
    //  0123
    // 0123
    if (a[0] == b[sb-3] && a[1] == b[sb-2] && a[2] == b[sb-1]) {
        for (int i = 0; i < b.size(); ++i) {
            r += b[i];
        }
        for (int i = 3; i < a.size(); ++i) {
            r += a[i];
        }
        return r;
    }
    // 0123
    //  0123
    if (a[sa-3] == b[0] && a[sa-2] == b[1] && a[sa-1] == b[2]) {
        for (int i = 0; i < a.size(); ++i) {
            r += a[i];
        }
        for (int i = 3; i < b.size(); ++i) {
            r += b[i];
        }
        return r;
    }
    
    //  012
    // 012
    if (a[0] == b[sb-2] && a[1] == b[sb-1]) {
        for (int i = 0; i < b.size(); ++i) {
            r += b[i];
        }
        for (int i = 2; i < a.size(); ++i) {
            r += a[i];
        }
        return r;
    }
    // 012
    //  012
    if (a[sa-2] == b[0] && a[sa-1] == b[1]) {
        for (int i = 0; i < a.size(); ++i) {
            r += a[i];
        }
        for (int i = 2; i < b.size(); ++i) {
            r += b[i];
        }
        return r;
    }
    //   012
    // 012
    if (a[0] == b[sb-1]) {
        for (int i = 0; i < b.size(); ++i) {
            r += b[i];
        }
        for (int i = 1; i < a.size(); ++i) {
            r += a[i];
        }
        return r;
    }
    // 012
    //   012
    if (a[sa-1] == b[0]) {
        for (int i = 0; i < a.size(); ++i) {
            r += a[i];
        }
        for (int i = 1; i < b.size(); ++i) {
            r += b[i];
        }
        return r;
    }
    
    return "";
}

inline string inunion (string a, string b) {
    if (a == b) { return a; }
    if (a.size() < b.size()) {
        if(b.find(a, 0) > -1) { return b; }
    } else {
        if(a.find(b, 0) > -1) { return a; }
    }
    return "";
}

inline string union_string (unordered_set<string> &ss) {
    vector<string> v;
    for (auto &i : ss) { v.emplace_back(i); }
    
    int cnt = 0;
    while (v.size() > 1 && cnt < 256) {
        int a = xrnd() % v.size();
        int b = 0;
        for (; b < v.size(); ++b) {
            if (b == a) { continue; }
            
            string s = sunion(v[a], v[b]);
            if (s != "") {
                if (a < b) { swap(a, b); }
                v.erase(v.begin() + a);
                v.erase(v.begin() + b);
                v.emplace_back(s);
                break;
            }
            
            // s = inunion(v[a], v[b]);
            // if (s != "") {
            //     if (a < b) { swap(a, b); }
            //     v.erase(v.begin() + a);
            //     v.erase(v.begin() + b);
            //     v.emplace_back(s);
            //     break;
            // }
        }
        
        
        cnt += 1;
    }
    string r = "";
    for (auto &i : v) { r += i; }
    
    return r;
}

class BrokenSlotMachines {
public:
    int startingCoins;
    int maxTime;
    int noteTime;
    int numMachines;
    
    int time;
    int coin;
    vector<double> expected;
    vector< vector<string> > wheels;
    
    vector<double> expected2;
    vector< vector<string> > wheels2;
    vector< vector< unordered_set<string> > > wheels2_res;
    
    
    void calculateExpected () {
        vector<int> payouts = vector<int>(this->numMachines);
        this->expected = vector<double>(this->numMachines, 0);
        for (int i = 0; i < this->numMachines; i++) {
            payouts[i] += count(this->wheels[i][0], 'A') * count(this->wheels[i][1], 'A') * count(this->wheels[i][2], 'A') * 1000;
            payouts[i] += count(this->wheels[i][0], 'B') * count(this->wheels[i][1], 'B') * count(this->wheels[i][2], 'B') * 200;
            payouts[i] += count(this->wheels[i][0], 'C') * count(this->wheels[i][1], 'C') * count(this->wheels[i][2], 'C') * 100;
            payouts[i] += count(this->wheels[i][0], 'D') * count(this->wheels[i][1], 'D') * count(this->wheels[i][2], 'D') * 50;
            payouts[i] += count(this->wheels[i][0], 'E') * count(this->wheels[i][1], 'E') * count(this->wheels[i][2], 'E') * 20;
            payouts[i] += count(this->wheels[i][0], 'F') * count(this->wheels[i][1], 'F') * count(this->wheels[i][2], 'F') * 10;
            payouts[i] += count(this->wheels[i][0], 'G') * count(this->wheels[i][1], 'G') * count(this->wheels[i][2], 'G') * 5;
            if (this->wheels[i][0].length() > 0 && this->wheels[i][1].length() > 0 && this->wheels[i][2].length() > 0) {
                this->expected[i] = 1.0 * payouts[i] / this->wheels[i][0].length() / this->wheels[i][1].length() / this->wheels[i][2].length();
            } else {
                this->expected[i] = 0;
            }
        }
    }
    
    void calculateExpected2 () {
        this->resset_to_string();
        vector<int> payouts = vector<int>(this->numMachines);
        this->expected2 = vector<double>(this->numMachines, 0);
        for (int i = 0; i < this->numMachines; i++) {
            payouts[i] += count(this->wheels2[i][0], 'A') * count(this->wheels2[i][1], 'A') * count(this->wheels2[i][2], 'A') * 1000;
            payouts[i] += count(this->wheels2[i][0], 'B') * count(this->wheels2[i][1], 'B') * count(this->wheels2[i][2], 'B') * 200;
            payouts[i] += count(this->wheels2[i][0], 'C') * count(this->wheels2[i][1], 'C') * count(this->wheels2[i][2], 'C') * 100;
            payouts[i] += count(this->wheels2[i][0], 'D') * count(this->wheels2[i][1], 'D') * count(this->wheels2[i][2], 'D') * 50;
            payouts[i] += count(this->wheels2[i][0], 'E') * count(this->wheels2[i][1], 'E') * count(this->wheels2[i][2], 'E') * 20;
            payouts[i] += count(this->wheels2[i][0], 'F') * count(this->wheels2[i][1], 'F') * count(this->wheels2[i][2], 'F') * 10;
            payouts[i] += count(this->wheels2[i][0], 'G') * count(this->wheels2[i][1], 'G') * count(this->wheels2[i][2], 'G') * 5;
            if (this->wheels2[i][0].length() > 0 && this->wheels2[i][1].length() > 0 && this->wheels2[i][2].length() > 0) {
                this->expected2[i] = 1.0 * payouts[i] / this->wheels2[i][0].length() / this->wheels2[i][1].length() / this->wheels2[i][2].length();
            } else {
                this->expected2[i] = 0;
            }
        }
    }
    
    int playSlots (int startingCoins, int maxTime, int noteTime, int numMachines) {
        this->startingCoins = startingCoins;
        this->maxTime = maxTime;
        this->noteTime = noteTime;
        this->numMachines = numMachines;
        this->wheels = vector< vector<string> >(numMachines, vector<string>(3));
        this->wheels2 = vector< vector<string> >(numMachines, vector<string>(3));
        this->wheels2_res = vector< vector< unordered_set<string> > >(numMachines, vector< unordered_set<string> >(3));
        this->time = maxTime;
        this->coin = startingCoins;
        
        int index;
        double rate;
        
        // if (startingCoins < 300 && maxTime < 300 && numMachines > 5 && noteTime > 5) { return 0; }
        
        
        int tt = max(min(maxTime / numMachines / noteTime / 10, 30), 10);
        // if (maxTime / numMachines / noteTime < tt) { return 0; }
        tt = min(maxTime / numMachines / noteTime / 3, tt);
        // int tt = min(maxTime / numMachines / noteTime / 10, 30);
        tt = numMachines > 8 ? tt * 1.2 : tt;
        tt = numMachines < 4 ? tt * 0.9 : tt;
        
        // vector<int> v;
        for (int i = 0; i < numMachines; ++i) {
            for (int j = 0; j < tt; ++j) {
                if (this->coin < 10 || this->time < noteTime) { break; }
                this->notePlay(i);
            }
            this->get_max_index_rate2(index, rate);
            // if (rate > 1) { v.emplace_back(i); }
            if (rate > 3 && noteTime > 3) { break; }
            if (rate > 5) { break; }
        }
        
        // this->get_max_index_rate(index, rate);
        // cout << "--" << tt << "--" << endl;
        // for (auto &i : this->expected) {
        //     cout << i << endl;
        // }
        
        this->get_max_index_rate2(index, rate);
        
        // cout << "--" << tt << "--" << endl;
        // for (auto &i : this->expected2) {
        //     cout << i << endl;
        // }
        
        int halftime = this->time / 2 + 10;
        int tcoin = this->coin;
        if (rate > 0.95) {
            while (this->time > halftime && this->coin > 20) {
                this->quickPlay(index, 10);
            }
        } else {
            return 0;
        }
        double trate = rate;
        int tindex = index;
        if (this->coin < tcoin) {
            this->get_prev_max_index_rate2(index, rate);
        }
        if (rate < trate - 2) {
            index = tindex;
            rate = trate;
        }
        
        
        
        if (rate > 0.90) {
            while (this->time > 10 && this->coin > 20) {
                this->quickPlay(index, 10);
            }
            this->quickPlay(index, 20);
        }
        
        ////
        
        // double m =0;
        // int ind = 0;
        // for (int i = 0; i < v.size(); ++i) {
        //     if (v[i] > m) {
        //         m = v[i];
        //         ind = i;
        //     }
        // }
        
        // if (m > 1) {
        //     //PlaySlots::quickPlay(ind, maxTime); 
        //     while (maxTime > 100) {
        //         PlaySlots::quickPlay(ind, 100);
        //         maxTime -= 100;
        //     } 
        // }
        
        return 0;
    }
    
    inline void get_max_index_rate (int &index, double &rate) {
        this->calculateExpected();
        index = 0;
        rate = 0;
        for (int i = 0; i < numMachines; ++i) {
            double tmp = this->expected[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
            }
        }
    }
    
    inline void get_prev_max_index_rate (int &index, double &rate) {
        this->calculateExpected();
        this->get_max_index_rate(index, rate);
        int tindex = index;
        double trate = rate;
        index = 0;
        rate = 0;
        
        for (int i = 0; i < numMachines; ++i) {
            if (i == index) { continue; }
            double tmp = this->expected[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
            }
        }
        if (rate > 0) { return; }
        this->get_max_index_rate(index, rate);
    }
    
    
    inline void get_max_index_rate2 (int &index, double &rate) {
        
        vector<double> v(this->numMachines, 0);
        for (int i = 0; i < 15; ++i) {
            this->calculateExpected2();
            for (int j = 0; j < this->numMachines; ++j) {
                v[j] += this->expected2[j];
            }
        }
        for (int j = 0; j < this->numMachines; ++j) {
            v[j] /= 15;
        }
        
        
        index = 0;
        rate = 0;
        for (int i = 0; i < numMachines; ++i) {
            double tmp = v[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
            }
        }
        
        // index = 0;
        // rate = 0;
        // for (int i = 0; i < numMachines; ++i) {
        //     double tmp = this->expected2[i];
        //     if (tmp > rate) {
        //         rate = tmp;
        //         index = i;
        //     }
        // }
    }
    
    inline void get_prev_max_index_rate2 (int &index, double &rate) {
        this->calculateExpected2();
        this->get_max_index_rate2(index, rate);
        int tindex = index;
        double trate = rate;
        index = 0;
        rate = 0;
        
        for (int i = 0; i < numMachines; ++i) {
            if (i == index) { continue; }
            double tmp = this->expected2[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
            }
        }
        if (rate > 0) { return; }
        this->get_max_index_rate2(index, rate);
    }
    
    inline void resset_to_string () {
        for (int m = 0; m < this->numMachines; ++m) {
            for (int x = 0; x < 3; ++x) {
                this->wheels2[m][x] = union_string(this->wheels2_res[m][x]);
            }
        }
    }
    
    inline void notePlay (int m) {
        this->time -= this->noteTime;
        this->coin -= 1;
        vector<string> np = PlaySlots::notePlay(m, 1);
        this->coin += stoi(np[0]);
        
        for (int i = 1; i < np.size(); ++i) {
            string s = np[i];
            for (int x = 0; x < 3; ++x) {
                string t = "";
                for (int y = 0; y < 3; ++y) {
                    this->wheels[m][x] += s[x + y * 3];
                    t += s[x + y * 3];
                }
                this->wheels2_res[m][x].emplace(t);
            }
        }
    }
    
    
    inline int quickPlay (int m, int n) {
        int rwin = 0;
        for (int i = 0; i < n; ++i) {
            this->time -= 1;
            this->coin -= 1;
            int win = PlaySlots::quickPlay(m, 1);
            this->coin += win;
            rwin += win;
            if (this->coin < 1 || this->time < 1) {
                return rwin;
            }
        }
        return rwin;
    }
    
};


// -------8<------- end of solution submitted to the website -------8<-------



void output_testcace () {
    cout << "--------------" << endl;
    cout << "coin        : " << g_coins << endl;
    cout << "maxTime     : " << g_maxTime << endl;
    cout << "noteTime    : " << g_noteTime << endl;
    cout << "numMachines : " << g_numMachines << endl;
}


void calculateExpected() {
    payouts = vector<int>(g_numMachines);
    expected = vector<double>(g_numMachines);
    for (int i = 0; i < g_numMachines; i++) {
        payouts[i] += count(wheels[i][0], 'A') * count(wheels[i][1], 'A') * count(wheels[i][2], 'A') * 1000;
        payouts[i] += count(wheels[i][0], 'B') * count(wheels[i][1], 'B') * count(wheels[i][2], 'B') * 200;
        payouts[i] += count(wheels[i][0], 'C') * count(wheels[i][1], 'C') * count(wheels[i][2], 'C') * 100;
        payouts[i] += count(wheels[i][0], 'D') * count(wheels[i][1], 'D') * count(wheels[i][2], 'D') * 50;
        payouts[i] += count(wheels[i][0], 'E') * count(wheels[i][1], 'E') * count(wheels[i][2], 'E') * 20;
        payouts[i] += count(wheels[i][0], 'F') * count(wheels[i][1], 'F') * count(wheels[i][2], 'F') * 10;
        payouts[i] += count(wheels[i][0], 'G') * count(wheels[i][1], 'G') * count(wheels[i][2], 'G') * 5;
        expected[i] = 1.0 * payouts[i] / wheels[i][0].length() / wheels[i][1].length() / wheels[i][2].length();
    }
}


int generateTestCase(uint64_t seed) {
    Random r(seed);
    g_coins = 100 + r.nextInt(9901);
    g_maxTime = 100 + r.nextInt(9901);
    g_noteTime = 2 + r.nextInt(9);
    g_numMachines = r.nextInt(8) + 3;
    machineState = vector<Random>(g_numMachines);
    wheels = vector< vector<string> >(g_numMachines, vector<string>(3));
    wheelSize = vector<int>(g_numMachines);
    g_rawcoins = g_coins;
    // output_testcace();
    
    for (int i = 0; i < g_numMachines; i++) {
        machineState[i] = Random(r.nextLong());
        if (seed == 0 && i == 0)  {
            wheels[i][0] = wheels[i][1] = wheels[i][2] = "AABBBBCCCCCDDDDDDEEEEEEFFFFFFFGGGGGGGG";
            wheelSize[i] = wheels[i][0].length();
            continue;
        }
        
        // cout << "machine" << i << endl;/////
        
        wheelSize[i] = 10 + r.nextInt(21);
        for (int j = 0; j < 3; j++) {
            wheels[i][j] = "";
            for (int k = 0; k < wheelSize[i]; k++)
            wheels[i][j] += "AABBBBCCCCCDDDDDDEEEEEEFFFFFFFGGGGGGGG"[r.nextInt(38)];
            
            // cout << wheels[i][j] << endl;/////
            
            wheels[i][j] += wheels[i][j] + wheels[i][j];
        }
    }
    
    calculateExpected();
    double d = 0;
    for (auto &i : expected) { d = max(d, i); }
    int score = g_coins;
    if (d > 1) { score = g_coins + g_maxTime * d; }
    
    // for (auto &i : expected) { cout << i << endl; }
    return score;
}

double runTest() {
    static uint64_t sui = 0;
    sui += 1;
    failed = false;
    int score = generateTestCase(sui);
    //lt.setTimeLimit(TIME_LIMIT);
    BrokenSlotMachines bsm;
    bsm.playSlots(g_coins, g_maxTime, g_noteTime, g_numMachines);
    //int timeLeft = TIME_LIMIT - lt.getTime();
    // if (timeLeft < 10) {
    //     lt.addFatalError("Time limit exceeded.\n");
    //     return -1;
    // }
    // if (!lt.getStatus()) {
    //     lt.addFatalError("Error calling playSlots()\n");
    //     return -1;
    // }
    // int x = lt.getResult_playSlots();
    // if (!lt.getStatus()) {
    //     lt.addFatalError("Error getting result from playSlots()\n");
    //     return -1;
    // }  
    // if (failed) { return -1; }
    
    // cout << g_coins << "/" << score << " " << g_coins / ((double)score) << endl;
    
    return g_coins / ((double)score);
}



int main() {
    double d;
    double sum = 0;
    int zerocnt = 0;
    int lowcnt = 0;
    for (int i = 0; i < 10000; ++i) {
        d = runTest();
        sum += d;
        if (d == 0) { zerocnt += 1; }
        cout << "Score:" << d << endl;
    }
    cout << "Sum:" << sum << endl;
    cout << "ZeroCnt:" << zerocnt << endl;
    return 0;
}