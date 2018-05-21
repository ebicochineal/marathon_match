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
    while (v.size() > 1 && cnt < 128) {
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
            
            s = inunion(v[a], v[b]);
            if (s != "") {
                if (a < b) { swap(a, b); }
                v.erase(v.begin() + a);
                v.erase(v.begin() + b);
                v.emplace_back(s);
                break;
            }
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
    
    void calculateExpected2 (int i) {
        this->resset_to_string(i);
        vector<int> payouts = vector<int>(this->numMachines);
        this->expected2[i] = 0;
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
        this->expected = vector<double>(this->numMachines, 0);
        this->expected2 = vector<double>(this->numMachines, 0);
        
        
        //if (startingCoins < 300 && maxTime < 300 && noteTime > 5 && numMachines > 5) { return 0; }
        this->hi(startingCoins, maxTime, noteTime, numMachines);
        
        
        return 0;
    }
    
    void hi (int startingCoins, int maxTime, int noteTime, int numMachines) {
        int index;
        double rate;
        int tt = max(min(maxTime / numMachines / noteTime / 12, 30), 16);
        // if (maxTime / numMachines / noteTime < tt) { return 0; }
        tt = min(maxTime / numMachines / noteTime / 3, tt);
        // int tt = min(maxTime / numMachines / noteTime / 10, 30);
        // tt = numMachines > 8 ? tt * 1.2 : tt;
        // tt = numMachines < 4 ? tt * 0.9 : tt;
        
        for (int i = 0; i < numMachines; ++i) {
            for (int j = 0; j < tt; ++j) {
                if (this->coin < 10 || this->time < noteTime) { break; }
                this->notePlay(i);
            }
            this->calculateExpected2(i);
            this->get_max_index_rate2(index, rate);
            // if (rate > 1) { v.emplace_back(i); }
            // if (rate > 2 && noteTime > 8 && maxTime < 3000 && i < 5 && numMachines > 8) { break; }
            if (rate > 3 && noteTime > 5) { break; }
            if (rate > 5) { break; }
        }
        int pindex = 0;
        double prate = 0;
        this->get_max_index_rate2(index, rate);
        this->get_prev_max_index_rate2(pindex, prate);
        if (prate < rate - 2 || prate < 0.9) {
            pindex = index;
            prate = rate;
        }
        if (rate < 0.95) { return; }
        
        int halftime = this->time / 2;
        int tcoin = this->coin;
        if (rate > 0.95) {
            while (this->time > halftime && this->coin > tcoin / 4) {
                this->quickPlay(index, 1);
            }
        } else {
            return;
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
        int prevcoin;
        if (rate > 0.90) {
            
            while (this->time > 0 && this->coin > 0) {
                prevcoin = this->coin;
                this->quickPlay(index, 1);
                if (rate < 1.5 && this->coin > prevcoin + 100 && this->time < 50) { return; }
            }
        }
        
        
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
        
        index = 0;
        rate = 0;
        for (int i = 0; i < numMachines; ++i) {
            double tmp = this->expected2[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
            }
        }
    }
    
    inline void get_prev_max_index_rate2 (int &index, double &rate) {
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
                
                string mins = union_string(this->wheels2_res[m][x]);
                for (int i = 0; i < 8; ++i) {
                    string t = union_string(this->wheels2_res[m][x]);
                    if (t.size() < mins.size()) {
                        mins = t;
                    }
                }
                
                string maxs = union_string(this->wheels2_res[m][x]);
                for (int i = 0; i < 8; ++i) {
                    string t = union_string(this->wheels2_res[m][x]);
                    if (t.size() > maxs.size()) {
                        maxs = t;
                    }
                }
                this->wheels2[m][x] = mins + mins + mins + maxs;
            }
        }
    }
    
    inline void resset_to_string (int m) {
        for (int x = 0; x < 3; ++x) {
            
            // string mins = union_string(this->wheels2_res[m][x]);
            // for (int i = 0; i < 15; ++i) {
            //     string t = union_string(this->wheels2_res[m][x]);
            //     if (t.size() < mins.size()) {
            //         mins = t;
            //     }
            // }
            
            // string maxs = union_string(this->wheels2_res[m][x]);
            // for (int i = 0; i < 15; ++i) {
            //     string t = union_string(this->wheels2_res[m][x]);
            //     if (t.size() > maxs.size()) {
            //         maxs = t;
            //     }
            // }
            // this->wheels2[m][x] = mins + mins + mins + maxs;
            
            vector<string> v;
            string t = "";
            for (int k = 0; k < 16; ++k) {
                v.clear();
                for (int i = 0; i < 16; ++i) { v.emplace_back(union_string(this->wheels2_res[m][x])); }
                sort(v.begin(), v.end(), [](const string &a, const string &b) { return a.size() < b.size(); } );
                t += v[0];
            }
            
            this->wheels2[m][x] = t;
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
            if (this->coin == 0 || this->time == 0) { return rwin; }
            this->time -= 1;
            this->coin -= 1;
            int win = PlaySlots::quickPlay(m, 1);
            this->coin += win;
            rwin += win;
        }
        return rwin;
    }
    
};


// -------8<------- end of solution submitted to the website -------8<-------


int g_rawcoins;
int g_rawtime;


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


void generateTestCase(uint64_t seed) {
    Random r(seed);
    g_coins = 100 + r.nextInt(9901);
    g_maxTime = 100 + r.nextInt(9901);
    g_noteTime = 2 + r.nextInt(9);
    g_numMachines = r.nextInt(8) + 3;
    machineState = vector<Random>(g_numMachines);
    wheels = vector< vector<string> >(g_numMachines, vector<string>(3));
    wheelSize = vector<int>(g_numMachines);
    g_rawcoins = g_coins;
    g_rawtime = g_maxTime;
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
    
    
    // for (auto &i : expected) { cout << i << endl; }
}

int iscore = 0;
double dscore = 0;


double runTest() {
    static uint64_t sui = 0;
    sui += 1;
    failed = false;
    generateTestCase(sui);
    //lt.setTimeLimit(TIME_LIMIT);
    BrokenSlotMachines bsm;
    bsm.playSlots(g_coins, g_maxTime, g_noteTime, g_numMachines);
    double d = 0;
    for (auto &i : expected) { d = max(d, i); }
    int score = g_rawcoins;
    if (d > 1) { score = g_rawcoins + g_rawtime * d; }
    iscore = g_coins;
    dscore = g_coins / ((double)score);
    return 0;
}

double dscore_sum (vector<double> a) {
    if (a.size() == 0) { return 0; }
    double r = 0;
    for (auto& i : a) { r += i; }
    return r / a.size();
}

int main() {
    double d;
    double dsum = 0;
    int isum = 0;
    int zerocnt = 0;
    int lowcnt = 0;
    int aisum = 0;
    double adsum = 0;
    
    vector< vector<double> > notesum = vector< vector<double> >(9, vector<double>());
    
    for (int y = 0; y < 100; ++y) {
        isum = 0;
        dsum = 0;
        zerocnt = 0;
        for (int i = 0; i < 1000; ++i) {
            runTest();
            dsum += dscore;
            notesum[g_noteTime - 2].emplace_back(dscore);
            isum += iscore;
            if (iscore == 0) { zerocnt += 1; }
        }
        aisum += isum;
        adsum += dsum;
        
        // for (int k = 0; k < 9; ++k) {
        //     cout << k + 2 << ':' << dscore_sum(notesum[k]) << " ";
        // }
        // cout << endl;
        cout << y << " Sum:" << dsum << " " << isum << endl;
        // cout << "ZeroCnt:" << zerocnt << endl;
        notesum = vector< vector<double> >(9, vector<double>());
    }
    cout << "Sum:" << adsum << " " << aisum << endl;
    
    cout << "30" << endl;
}

// 60639
// 60662