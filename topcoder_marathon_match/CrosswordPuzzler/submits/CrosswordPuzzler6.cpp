// C++11
#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <random>
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

struct mpos {
public:
    int x;
    int y;
    mpos () { this->x = 0; this->y = 0; }
    mpos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    mpos operator + (const mpos &t) { return mpos(this->x + t.x, this->y + t.y); }
    mpos operator - (const mpos &t) { return mpos(this->x - t.x, this->y - t.y); }
    bool operator == (const mpos &t) const { return this->x == t.x && this->y == t.y; }
};

namespace std {
    template <> class hash<mpos> {
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

class CrosswordPuzzler {
public:
    int width;
    int height;
    vector<string> dict;
    unordered_set<string> usdict;
    
    StopWatch sw;
    
    vector<string> createPuzzle (int width, int height, vector<string> dict) {
        sw = StopWatch();
        this->width = width;
        this->height = height;
        this->dict = dict;
        for (auto &i : dict) { this->usdict.emplace(i); }
        
        
        // vector<string> ret;
        vector< vector<char> > ret;
        
        
        sort(dict.begin(), dict.end(), [](const string &a, const string &b) { return a.size() < b.size(); });
        vector<string> dict2 = dict;
        sort(dict2.begin(), dict2.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
        int f = dict.size() - 1;
        int f2 = dict.size() - 1;
        
        unordered_set<string> us = this->usdict;
        for(int i = 0; i < 200; i++) {
            // if (ret.size() < height) {
            //     ret.emplace_back(vector<char>());
            //     while (ret.size() > 0 && ret[ret.size()-1].size() < width) {
            //         ret[ret.size()-1].emplace_back('-');
            //     }
            // }
            
            if (ret.size() < height) {
                ret.emplace_back(vector<char>());
                while (ret[ret.size()-1].size() + dict[f].size()+1 < width) {
                    us.erase(dict[f]);
                    for (auto &j : dict[f--]) { ret[ret.size()-1].emplace_back(j); }
                    ret[ret.size()-1].emplace_back('-');
                }
                while (ret.size() > 0 && ret[ret.size()-1].size() < width) {
                    ret[ret.size()-1].emplace_back('-');
                }
            }
            
            if (ret.size() < height) {
                ret.emplace_back(vector<char>());
                while (ret.size() > 0 && ret[ret.size()-1].size() < width) {
                    ret[ret.size()-1].emplace_back('-');
                }
            }
            if (ret.size() == height) { break; }
        }
        
        vector<string> vs;
        for (auto &i : us) { vs.emplace_back(i); }
        sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
        for (auto &i : vs) { this->test_put(ret, i); }
        int bestscore = this->ret_score(ret);
        vector< vector<char> > bestret = ret;
        {
            ret.clear();
            for (int i = 0; i < this->height; ++i) {
                ret.emplace_back( vector<char>(this->width, '-') );
            }
            vs = this->dict;
            sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
            
            for (auto &i : vs) { this->test_put(ret, i); }
            int tscore = this->ret_score(ret);
            if (tscore > bestscore) {
                bestret = ret;
                bestscore = tscore;
            }
        }
        int lcnt = 0;
        int e = this->sw.get_milli_time();
        mt19937 mt(xrnd());
        
        if (false) {
        // if (height >= 5 && width >= 12) {
        //     this->height = 12;
        //     this->width = 12;
        //     vector< vector<char> > pbestret;
        //     int pbestscore = 0;
        //     while(this->sw.get_milli_time() < 4000) {
        //         ret.clear();
        //         for (int i = 0; i < height; ++i) {
        //             ret.emplace_back( vector<char>(width, '-') );
        //         }
        //         vs = this->dict;
                
        //         sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
                
        //         shuffle(vs.begin(), min(vs.end(), vs.begin() + 32), mt);
                
        //         for (auto &i : vs) {
        //             this->test_put(ret, i);
        //         }
        //         int tscore = this->ret_score(ret);
        //         if (tscore > pbestscore) {
        //             pbestret = ret;
        //             pbestscore = tscore;
        //         }
        //         break;
        //     }
            
        //     this->height = height;
        //     this->width = width;
            
        //     while(this->sw.get_milli_time() < 9000 - (e > 800 ? 200 : 0) + (e < 100 ? 500 : 0) + (e < 200 ? 200 : 0)) {
        //         ret = pbestret;
        //         // for (int i = 0; i < this->height; ++i) {
        //         //     ret.emplace_back( vector<char>(this->width, '-') );
        //         // }
        //         vs = this->dict;
        //         sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
        //         shuffle(vs.begin(), min(vs.end(), vs.begin() + min((int)(3 + (lcnt / 25)), 3) + min((int)(4 + (lcnt / 100)), 4)), mt);
        //         this->shuffle_word(vs);
        //         for (auto &i : vs) {
        //             if (xrnd() % 3 > 0) {
        //                 this->test_put(ret, i);
        //             } else {
        //                 this->test_put2(ret, i);
        //             }
        //         }
        //         int tscore = this->ret_score(ret);
        //         if (tscore > bestscore) {
        //             bestret = ret;
        //             bestscore = tscore;
        //         }
        //         lcnt += 1;
        //     }
            
        } else {
            while(this->sw.get_milli_time() < 9000 - (e > 800 ? 200 : 0) + (e < 100 ? 500 : 0) + (e < 200 ? 200 : 0)) {
                ret.clear();
                for (int i = 0; i < this->height; ++i) {
                    ret.emplace_back( vector<char>(this->width, '-') );
                }
                vs = this->dict;
                
                sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
                
                shuffle(vs.begin(), min(vs.end(), vs.begin() + min((int)(3 + (lcnt / 25)), 3) + min((int)(4 + (lcnt / 100)), 4)), mt);
                
                // this->shuffle_word(vs);
                
                for (auto &i : vs) {
                    if (xrnd() % 3 > 0) {
                        this->test_put(ret, i);
                    } else {
                        this->test_put2(ret, i);
                    }
                }
                
                int tscore = this->ret_score(ret);
                if (tscore > bestscore) {
                    bestret = ret;
                    bestscore = tscore;
                }
                lcnt += 1;
            }
        }
        
        pdebug(width, height);
        // pdebug(max(score, 0));
        // pdebug(dict.size(), usdict.size());
        
        
        // for (int i = 0; i < 100000; ++i) {
        //     this->ret_score(ret);
        // }
        
        
        
        
        pdebug("cnt", lcnt);
        // for (auto &i : ret) { pdebug(i); }
        pdebug("time", sw.get_milli_time());
        
        this->info(bestret);
        // this->finfo(bestret);
        return this->vvc_to_vs(bestret);
    }
    
    void info (vector< vector<char> > vvc) {
        vector<int> sizes(10, 0);
        for (auto &i : this->dict) {
            sizes[i.size()-3] += 1;
        }
        for (auto &i : this->use_words(vvc)) {
            sizes[i.size()-3] -= 1;
        }
        
        pdebug(sizes);
    }
    
    void finfo (vector< vector<char> > vvc) {
        fdebug(this->width, this->height);
        fdebug(this->dict.size());
        vector<string> vs = this->dict;
        sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
        for (auto &i : vs) {
            fdebug(i);
        }
        
        for (auto &i : this->vvc_to_vs(vvc)) {
            fdebug(i);
        }
    }
    
    
    void shuffle_word (vector<string> &vs) {
        sort(vs.begin(), vs.end(), [](const string &a, const string &b) { return a.size() > b.size(); });
        vector<int> w;
        w.emplace_back(0);
        for (int i = 0; i < vs.size()-1; ++i) {
            if (vs[i].size() > vs[i+1].size()) {
                w.emplace_back(i);
            }
        }
        
        mt19937 mt(xrnd());
        for (int i = 0; i < w.size()-1; ++i) {
            shuffle(vs.begin() + w[i], vs.begin() + w[i+1], mt);
        }
    }
    
    vector<string> vvc_to_vs (vector< vector<char> > vvc) {
        vector<string> r;
        for (auto &i : vvc) {
            string s = "";
            for (int j = 0; j < width; ++j) {
                s += i[j];
            }
            r.emplace_back(s);
        }
        return r;
    }
    
    inline int word_score (string w) {
        static int x[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
        return x[w.size()];
    }
    
    void test_put (vector< vector<char> > &ret, string w) {
        
        int twidth = this->width - w.size() + 1;
        int theight = this->height - w.size() + 1;
        vector<char> tmp(w.size(), '-');
        for (int y = 0; y < theight; ++y) {
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] == '-' || ret[y][x] == w[0]) {
                    int ecnt = 0;
                    int bcnt = 0;
                    for (int a = 0; a < w.size(); ++a) {
                        ecnt += (ret[y+a][x] != '-' && ret[y+a][x] != w[a]);
                        bcnt += ret[y+a][x] == '-';
                        tmp[a] = ret[y+a][x];
                        ret[y+a][x] = w[a];
                    }
                    if (bcnt > 0 && ecnt == 0 && this->test_h(ret, x, y, w.size()) && this->ret_score(ret) > -1) {
                        return;
                    } else {
                        for (int a = 0; a < w.size(); ++a) { ret[y+a][x] = tmp[a]; }
                    }
                }
            }
        }
        
        for (int y = 0; y < this->height; ++y) {
            for (int x = 0; x < twidth; ++x) {
                if (ret[y][x] == '-' || ret[y][x] == w[0]) {
                    int ecnt = 0;
                    int bcnt = 0;
                    for (int a = 0; a < w.size(); ++a) {
                        ecnt += (ret[y][x+a] != '-' && ret[y][x+a] != w[a]);
                        bcnt += ret[y][x+a] == '-';
                        tmp[a] = ret[y][x+a];
                        ret[y][x+a] = w[a];
                    }
                    if (bcnt > 0 && ecnt == 0 && this->test_w(ret, x, y, w.size()) && this->ret_score(ret) > -1) {
                        return;
                    } else {
                        for (int a = 0; a < w.size(); ++a) { ret[y][x+a] = tmp[a]; }
                    }
                }
            }
        }
    }
    
    void test_put2 (vector< vector<char> > &ret, string w) {
        
        int twidth = this->width - w.size() + 1;
        int theight = this->height - w.size() + 1;
        vector<char> tmp(w.size(), '-');
        
        for (int y = 0; y < this->height; ++y) {
            for (int x = 0; x < twidth; ++x) {
                if (ret[y][x] == '-' || ret[y][x] == w[0]) {
                    int ecnt = 0;
                    int bcnt = 0;
                    for (int a = 0; a < w.size(); ++a) {
                        ecnt += (ret[y][x+a] != '-' && ret[y][x+a] != w[a]);
                        bcnt += ret[y][x+a] == '-';
                        tmp[a] = ret[y][x+a];
                        ret[y][x+a] = w[a];
                    }
                    if (bcnt > 0 && ecnt == 0 && this->test_w(ret, x, y, w.size()) && this->ret_score(ret) > -1) {
                        return;
                    } else {
                        for (int a = 0; a < w.size(); ++a) { ret[y][x+a] = tmp[a]; }
                    }
                }
            }
        }
        
        for (int y = 0; y < theight; ++y) {
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] == '-' || ret[y][x] == w[0]) {
                    int ecnt = 0;
                    int bcnt = 0;
                    for (int a = 0; a < w.size(); ++a) {
                        ecnt += (ret[y+a][x] != '-' && ret[y+a][x] != w[a]);
                        bcnt += ret[y+a][x] == '-';
                        tmp[a] = ret[y+a][x];
                        ret[y+a][x] = w[a];
                    }
                    if (bcnt > 0 && ecnt == 0 && this->test_h(ret, x, y, w.size()) && this->ret_score(ret) > -1) {
                        return;
                    } else {
                        for (int a = 0; a < w.size(); ++a) { ret[y+a][x] = tmp[a]; }
                    }
                }
            }
        }
    }
    
    
    inline bool test_w (vector< vector<char> > &ret, int px, int py, int wlen) {
        unordered_set<string> w;
        
        string t = "";
        for (int x = px; x < px + wlen; ++x) {
            t.clear();
            for (int y = 0; y < this->height; ++y) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return false; }
                        if (w.find(t) != w.end()) { return false; }
                        w.emplace(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return false; }
                if (w.find(t) != w.end()) { return false; }
                w.emplace(t);
            }
        }
        
        t.clear();
        for (int x = 0; x < this->width; ++x) {
            if (ret[py][x] != '-') {
                t += ret[py][x];
            } else {
                if (t.size() > 1) {
                    if (this->usdict.find(t) == this->usdict.end()) { return false; }
                    if (w.find(t) != w.end()) { return false; }
                    w.emplace(t);
                }
                t.clear();
            }
        }
        if (t.size() > 1) {
            if (this->usdict.find(t) == this->usdict.end()) { return false; }
            if (w.find(t) != w.end()) { return false; }
            w.emplace(t);
        }
        return true;
    }
    
    inline bool test_h (vector< vector<char> > &ret, int px, int py, int wlen) {
        unordered_set<string> w;
        
        string t = "";
        for (int y = py; y < py + wlen; ++y) {
            t.clear();
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return false; }
                        if (w.find(t) != w.end()) { return false; }
                        w.emplace(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return false; }
                if (w.find(t) != w.end()) { return false; }
                w.emplace(t);
            }
        }
        
        t.clear();
        for (int y = 0; y < this->height; ++y) {
            if (ret[y][px] != '-') {
                t += ret[y][px];
            } else {
                if (t.size() > 1) {
                    if (this->usdict.find(t) == this->usdict.end()) { return false; }
                    if (w.find(t) != w.end()) { return false; }
                    w.emplace(t);
                }
                t.clear();
            }
        }
        if (t.size() > 1) {
            if (this->usdict.find(t) == this->usdict.end()) { return false; }
            if (w.find(t) != w.end()) { return false; }
            w.emplace(t);
        }
        return true;
    }
    
    int ret_score (vector< vector<char> > &ret) {
        int score = 0;
        unordered_set<string> w;
        
        string t = "";
        for (int y = 0; y < this->height; ++y) {
            t.clear();
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                        if (w.find(t) != w.end()) { return -1; }
                        w.emplace(t);
                        score += this->word_score(t);
                    }
                    t.clear();
                    score -= 1;// - cnt
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                if (w.find(t) != w.end()) { return -1; }
                w.emplace(t);
            }
        }
        
        for (int x = 0; x < this->width; ++x) {
            t.clear();
            for (int y = 0; y < this->height; ++y) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                        if (w.find(t) != w.end()) { return -1; }
                        w.emplace(t);
                        score += this->word_score(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                if (w.find(t) != w.end()) { return -1; }
                w.emplace(t);
            }
        }
        
        return max(score, 0);
    }
    
    int ret_score (vector<string> &ret) {
        int score = 0;
        unordered_set<string> w;
        
        string t = "";
        for (int y = 0; y < this->height; ++y) {
            t.clear();
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                        if (w.find(t) != w.end()) { return -1; }
                        w.emplace(t);
                        score += this->word_score(t);
                    }
                    t.clear();
                    score -= 1;// - cnt
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                if (w.find(t) != w.end()) { return -1; }
                w.emplace(t);
            }
        }
        
        for (int x = 0; x < this->width; ++x) {
            t.clear();
            for (int y = 0; y < this->height; ++y) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                        if (w.find(t) != w.end()) { return -1; }
                        w.emplace(t);
                        score += this->word_score(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                if (this->usdict.find(t) == this->usdict.end()) { return -1; }
                if (w.find(t) != w.end()) { return -1; }
                w.emplace(t);
            }
        }
        
        return max(score, 0);
    }
    
    
    unordered_set<string> use_words (vector< vector<char> > &ret) {
        unordered_set<string> w;
        
        string t = "";
        for (int y = 0; y < this->height; ++y) {
            t.clear();
            for (int x = 0; x < this->width; ++x) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        w.emplace(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                w.emplace(t);
            }
        }
        
        for (int x = 0; x < this->width; ++x) {
            t.clear();
            for (int y = 0; y < this->height; ++y) {
                if (ret[y][x] != '-') {
                    t += ret[y][x];
                } else {
                    if (t.size() > 1) {
                        w.emplace(t);
                    }
                    t.clear();
                }
            }
            if (t.size() > 1) {
                w.emplace(t);
            }
        }
        
        return w;
    }
};



//////////////////////////////////////////////

int main() {
    CrosswordPuzzler sol;
    int width;
    int height;
    int size;
    vector<string> dict;
    string s;
    getline(cin, s);
    width = atoi(s.c_str());
    getline(cin, s);
    height = atoi(s.c_str());
    getline(cin, s);
    size = atoi(s.c_str());
    for (int i = 0; i < size; i++) {
        getline(cin, s);
        dict.push_back(s);
    }
    vector<string> ret = sol.createPuzzle(width, height, dict);
    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++) { cout << ret[i] << endl; }
    cout.flush();
}
