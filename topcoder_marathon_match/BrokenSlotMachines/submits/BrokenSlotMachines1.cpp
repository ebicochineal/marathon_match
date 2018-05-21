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
    
    
    void calculateExpected () {
        vector<int> payouts = vector<int>(this->numMachines);
        this->expected = vector<double>(this->numMachines);
        for (int i = 0; i < this->numMachines; i++) {
            payouts[i] += count(this->wheels[i][0], 'A') * count(this->wheels[i][1], 'A') * count(this->wheels[i][2], 'A') * 1000;
            payouts[i] += count(this->wheels[i][0], 'B') * count(this->wheels[i][1], 'B') * count(this->wheels[i][2], 'B') * 200;
            payouts[i] += count(this->wheels[i][0], 'C') * count(this->wheels[i][1], 'C') * count(this->wheels[i][2], 'C') * 100;
            payouts[i] += count(this->wheels[i][0], 'D') * count(this->wheels[i][1], 'D') * count(this->wheels[i][2], 'D') * 50;
            payouts[i] += count(this->wheels[i][0], 'E') * count(this->wheels[i][1], 'E') * count(this->wheels[i][2], 'E') * 20;
            payouts[i] += count(this->wheels[i][0], 'F') * count(this->wheels[i][1], 'F') * count(this->wheels[i][2], 'F') * 10;
            payouts[i] += count(this->wheels[i][0], 'G') * count(this->wheels[i][1], 'G') * count(this->wheels[i][2], 'G') * 5;
            this->expected[i] = 1.0 * payouts[i] / this->wheels[i][0].length() / this->wheels[i][1].length() / this->wheels[i][2].length();
        }
    }
    
    int playSlots (int startingCoins, int maxTime, int noteTime, int numMachines) {
        this->startingCoins = startingCoins;
        this->maxTime = maxTime;
        this->noteTime = noteTime;
        this->numMachines = numMachines;
        this->wheels = vector< vector<string> >(numMachines, vector<string>(3));
        this->time = maxTime;
        this->coin = startingCoins;
        
        int index;
        double rate;
        if (this->noteTime > 8 && this->maxTime < 2000) {
            int t = min(maxTime / 2 / numMachines, 256);
            t = min(startingCoins / (numMachines * 2), t);
            int maxcoin = t;
            index = 0;
            for (int i = 0; i < numMachines; ++i) {
                int tmp = PlaySlots::quickPlay(i, t);
                if (tmp > maxcoin) {
                    maxcoin = tmp;
                    index = i;
                }
            }
            if (maxcoin > t) {
                while (time > 10) {
                    this->quickPlay(index, 10);
                }
            }
            return 0;
        }
        
        int tt = min(maxTime / numMachines / noteTime / 10, 30);
        for (int i = 0; i < numMachines; ++i) {
            for (int j = 0; j < tt; ++j) {
                this->notePlay(i);
            }
            this->get_max_index_rate(index, rate);
            if (rate > 5) { break; }
        }
        
        this->get_max_index_rate(index, rate);
        if (rate > 1 || (tt < 5 || rate > 0.9)) { 
            while (this->time > 10 && this->coin > 20) {
                this->get_max_index_rate(index, rate);
                this->quickPlay(index, 10);
            } 
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
            int tmp = this->expected[i];
            if (tmp > rate) {
                rate = tmp;
                index = i;
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
                for (int y = 0; y < 3; ++y) {
                    this->wheels[m][x] += s[x + y * 3];
                }
            }
        }
    }
    
    inline void quickPlay (int m, int n) {
        for (int i = 0; i < n; ++i) {
            this->time -= 1;
            this->coin -= 1;
            int win = PlaySlots::quickPlay(m, 1);
            this->coin += win;
            
        }
        
    }
    
    // A A A : 1,000
    // B B B :   200
    // C C C :   100
    // D D D :    50
    // E E E :    20
    // F F F :    10
    // G G G :     5
    
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
void generateTestCase(uint64_t seed) {
    Random r(seed);
    g_coins = 100 + r.nextInt(9901);
    g_maxTime = 100 + r.nextInt(9901);
    g_noteTime = 2 + r.nextInt(9);
    g_numMachines = r.nextInt(8) + 3;
    machineState = vector<Random>(g_numMachines);
    wheels = vector< vector<string> >(g_numMachines, vector<string>(3));
    wheelSize = vector<int>(g_numMachines);
    
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
    
    // for (auto &i : expected) {
    //     cout << i << endl;
    // }
    
}

double runTest() {
    static uint64_t sui = 0;
    sui += 1;
    failed = false;
    generateTestCase(sui);
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
    return g_coins;
}

int main() {
    //BrokenSlotMachines bsm;
    //bsm.playSlots(0, 0, 0, 0);
    double d;
    int64_t sum = 0;
    int zerocnt = 0;
    for (int i = 0; i < 100; ++i) {
        d = runTest();
        sum += (int)d;
        if (d < 1) { zerocnt += 1; }
        cout << "Score:" << d << endl;
    }
    cout << "Sum:" << sum << endl;
    cout << "ZeroCnt:" << zerocnt << endl;
    return 0;
}
