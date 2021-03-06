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
using namespace std;
#include <fstream>



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



class InvestmentAdvice {
public:
    int cnt = 0;
    
    
    
    void out (vector<int> recent) {
        static ofstream outputfile("recent.txt");
        static int cnt = 0;
        outputfile << print(cnt++, recent) << endl;
    }
    
    void out2 (vector<int> advice) {
        static ofstream outputfile("advice.txt");
        static int cnt = 0;
        outputfile << print(cnt++, advice) << endl;
    }
    
    void out3 (vector<int> ret) {
        static ofstream outputfile("ret.txt");
        static int cnt = 0;
        outputfile << print(cnt++, ret) << endl;
    }
    
    vector<int> getInvestments(vector<int> advice, vector<int> recent, int money, int timeLeft, int roundsLeft) {
        
        vector<int> ret(advice.size(), 0);
        
        this->out(recent);
        this->out2(advice);
        // cerr << print(recent) << endl;
        vector< pair<int, int> > vii;
        if (cnt++ < 25) {
            for (int i = 0; i < advice.size(); ++i) {
                if (advice[i] >= -2) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= -1) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 0) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 1) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 2) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 3) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 4) {
                    vii.emplace_back(advice[i] , i);
                }
                if (advice[i] >= 5) {
                    vii.emplace_back(advice[i] , i);
                }
            }
            
            sort(vii.begin(), vii.end(), [](const auto &a, const auto &b) { return a.first > b.first; });
            
            int bet = 50000;
            for (int i = 0; i < vii.size(); ++i) {
                if (money > bet) {
                    ret[vii[i].second] += bet;
                    money -= bet;
                } else {
                    break;
                }
            }
            
        } else {
            for (int i = 0; i < advice.size(); ++i) {
                if (advice[i] >= 0) {
                    vii.emplace_back(advice[i] , i);
                }
            }
            
            sort(vii.begin(), vii.end(), [](const auto &a, const auto &b) { return a.first > b.first; });
            
            int bet = 400000;
            for (int i = 0; i < vii.size(); ++i) {
                if (money > bet) {
                    ret[vii[i].second] += bet;
                    money -= bet;
                } else {
                    break;
                }
            }
            
        }
        
        this->out3(ret);
        
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
