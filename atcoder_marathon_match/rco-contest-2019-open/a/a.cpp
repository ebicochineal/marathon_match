#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <random>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <time.h>
#include <sys/timeb.h>

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

template<typename F, typename... R> void pdebug (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>" << ss.str() << "</cerr>" << endl;
}

template<typename F, typename... R> void fdebug (const F &f, const R &...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerrfile>" << ss.str() << "</cerrfile>" << endl;
}

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

struct mpos {
public:
    int x;
    int y;
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <>
    class hash<mpos> {
    public:
        size_t operator()(const mpos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
}

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

inline double distance (const double &ax, const double &ay, const double &bx, const double &by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline double distance (const int &ax, const int &ay, const int &bx, const int &by) {
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}
inline float distance (const mpos &a, const mpos &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


class MM {
public:
    StopWatch sw;
    MM () {
        this->sw = StopWatch();
        
        int n, t;
        int score = 0;
        cin >> n >> t;
        vector<int> cards(n, -1);
        int oc = -1;
        int p = 0;
        
        int tin = -1;
        int cnt = 0;
        
        unordered_set<int> s;
        while (t > 0) {
            // fdebug(cards);
            cnt += 1;
            if (oc < 0) {
                // pdebug(score);
                cout << p << endl;
                cin >> tin;
                cards[p] = tin;
                oc = tin;
            }
            
            int jp = -1;
            bool allopen = true;
            for (auto &i : cards) { if (i < 0) { allopen = false; } }
            
            for (int i = 0; i < n; ++i) {
                if (p == i) { continue; }
                if (oc == cards[i]) {
                    jp = i;
                }
            }
            
            
            
            
            if (allopen && jp == -1) {
                jp = (p + 1) % n;
            }
            
            
            
            
            if (jp < 0) {
                int np = -1;
                int cost = 1000000;
                for (int i = 0; i < n; ++i) {
                    int tcost = abs(p - i);
                    if (cards[i] < 0 && tcost < cost) {
                        np = i;
                        cost = tcost;
                    }
                }
                if (cost < 1000000) {
                    if (t - cost < 0) { break; }
                    t -= cost;
                    cout << np << endl;
                    
                    cin >> tin;
                    if (oc == tin) {
                        score += oc;
                        oc = -1;
                        cards[p] = -1;
                        cards[np] = -1;
                        
                        // pdebug(score);
                    } else {
                        cards[np] = tin;
                        oc = tin;
                    }
                    
                    p = np;
                } else {
                    
                    
                }
                
                
            } else {
                int cost = abs(p - jp);
                if (t - cost < 0) { break; }
                t -= cost;
                cout << jp << endl;
                cin >> tin;
                if (oc == tin) {
                    score += oc;
                    oc = -1;
                    cards[p] = -1;
                    cards[jp] = -1;
                    
                } else {
                    oc = tin;
                }
                p = jp;
                
                
                // pdebug(score);
            }
            
            
            
        }
        
        cout << -1 << endl;
        
        
        // pdebug(n, m);
        
        
        
    }
    
    
    
};

int main() {
    // cin.tie(0);
    // ios::sync_with_stdio(false);
    
    MM();
    
    return 0;
}