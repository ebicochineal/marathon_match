#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

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
    int tstarts = 0;
    int tstartm = 0;
    struct timeb timebuffer;
    StopWatch () {
        ftime(&this->timebuffer);
        this->starts = this->timebuffer.time;
        this->startm = this->timebuffer.millitm;
    }
    inline void stop () {
        ftime(&this->timebuffer);
        this->tstarts = this->timebuffer.time;
        this->tstartm = this->timebuffer.millitm;
    }
    inline void resume () {
        ftime(&this->timebuffer);
        this->starts += this->timebuffer.time - this->tstarts;
        this->startm += this->timebuffer.millitm - this->tstartm;
    }
    inline int get_milli_time () {
        ftime(&this->timebuffer);
        return (this->timebuffer.time - this->starts) * 1000 + (this->timebuffer.millitm - this->startm);
    }
};

string ABCDEFGH = "ABCDEFGH";

class MM {
public:
    int width;
    int height;
    
    unordered_set<string> usdict;
    
    StopWatch sw;
    vector< pair<string, int > > dict;
    vector<int> bdict = vector<int>(800, 0);
    
    unordered_set<string> uws;
    vector<string> ws;
    vector<int> bws = vector<int>(800, 0);
    vector<string> solve (int width, int height, vector< pair<string, int > > dict) {
        sw = StopWatch();
        this->width = width;
        this->height = height;
        this->dict = dict;
        // for (auto &i : dict) { this->usdict.emplace(i); }
        
        vector< vector<char> > ret = vector< vector<char> >(20, vector<char>(20, '.'));
        
        sort(this->dict.begin(), this->dict.end(), [](const pair<string, int >& a, const pair<string, int >& b) { return a.second > b.second; });
        
        sort(this->dict.begin(), this->dict.end(), [](const pair<string, int >& a, const pair<string, int >& b) { return a.first.size() > b.first.size(); });
        
        for (auto&& i : this->dict) {
            this->ws.emplace_back(i.first);
            this->uws.emplace(i.first);
        }
        
        string q = "ABCDEFGH";
        for (int y = 0; y < 20; ++y) {
            vector<char> line = vector<char>(20, 'A');
            int bestscore = this->line_score(line);
            
            line = this->hline_sa(line, 95, 0, 0);
            
            this->line_end_use_update(line);
            for (int i = 0; i < 20; ++i) {
                ret[y][i] = line[i];
            }
        }
        
        // int bestscore = this->ret_score(ret);
        
        // array<char, 20> tmp;
        // int cnt = 0;
        // while (this->sw.get_milli_time() < 1940) {
        //     int y = xrnd()%20;
        //     int n = xrnd()%19;
        //     for (int i = 0; i < 20; ++i) {
        //         tmp[i] = ret[y][i];
        //     }
            
        //     this->shifth(ret, y, n);
        //     int score = this->ret_score(ret);
        //     if (score >= bestscore) {
        //         bestscore = score;
        //     } else {
        //         for (int i = 0; i < 20; ++i) {
        //             ret[y][i] = tmp[i];
        //         }
        //     }
            
        //     cnt += 1;
            
        // }
        
        vector< vector<char> > bestret = ret;
        
        
        // pdebug(cnt);
        
        
        pdebug(this->ret_score(bestret),this->dict.size());
        pdebug("s", (int)(100000000 * (this->ret_score(bestret)/(double)this->dict.size())));
        pdebug("time", sw.get_milli_time());
        
        
        return this->vvc_to_vs(bestret);
    }
    
    void shifth (vector< vector<char> >& g, int line, int n) {
        for (int i = 0; i < 20; ++i) {
            swap(g[line][i], g[line][(i+n)%20]);
        }
    }
    
    
    vector<char> hline_sa (vector<char> v, int etime, double stemp = 256.0, double etemp = 0.0) {
        static vector<char> tt;
        
        
        StopWatch sw;
        int stime = 0;
        const double satime = etime - stime;
        int ntime = stime;
        vector<char> bestv = v;
        double bestscore = this->line_score(v);
        double lastscore = bestscore;
        const int64_t R = 1000000000;
        
        while (true) {
            ntime = sw.get_milli_time();
            if (ntime >= etime) { break; }
            // {
            //     char c = ABCDEFGH[xrnd() % 8];
            //     int p = xrnd() % 20;
            //     swap(v[p], c);
                
                
                
            //     double tmpscore = this->line_score(v);
            //     const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
            //     const double probability = exp((tmpscore - lastscore) / temp);
            //     const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
            //     if (tmpscore >= lastscore || FORCE_NEXT) {
            //         lastscore = tmpscore;
            //         if (tmpscore > bestscore) {
            //             bestscore = tmpscore;
            //             bestv = v;
            //         }
            //     } else {
            //         swap(v[p], c);
            //     }
            // }
            
            {
                int wp = xrnd() % this->ws.size();
                if (this->bws[wp]) { continue; }
                if (this->ws[wp].size() < 3) { continue; }
                tt.clear();
                
                int p = xrnd() % 20;
                for (int i = 0; i < this->ws[wp].size(); ++i) {
                    tt.emplace_back(v[(p+i)%20]);
                    v[(p+i)%20] = this->ws[wp][i];
                }
                
                
                
                char c = ABCDEFGH[xrnd() % 8];
                
                swap(v[p], c);
                
                
                
                double tmpscore = this->line_score(v);
                const double temp = stemp + (etemp - stemp) * (double)(ntime-stime) / satime;
                const double probability = exp((tmpscore - lastscore) / temp);
                const bool FORCE_NEXT = probability > (double)(xrnd() % R) / R;
                if (tmpscore >= lastscore || FORCE_NEXT) {
                    lastscore = tmpscore;
                    if (tmpscore > bestscore) {
                        bestscore = tmpscore;
                        bestv = v;
                    }
                } else {
                    for (int i = 0; i < tt.size(); ++i) {
                        v[(p+i)%20] = tt[i];
                    }
                }
            }
            
        }
        return bestv;
    }
    
    void updateb (const vector< vector<char> > &ret) {
        
        string a;
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20+12; ++x) {
                a += ret[y][x%20];
            }
            a += " ";
        }
        for (int x = 0; x < 20; ++x) {
            for (int y = 0; y < 20+12; ++y) {
                a += ret[y%20][x];
            }
            a += " ";
        }
        
        
        for (int i = 0; i < this->dict.size(); ++i) {
            if (a.find(this->dict[i].first) != string::npos) {
                this->bdict[i] = 1;
            }
        }
        
    }
    
    vector<string> vvc_to_vs (vector< vector<char> > vvc) {
        
        
        vector<string> r;
        if (this->ret_score(vvc) == this->dict.size()) {
            for (auto &i : vvc) {
                string s = "";
                for (int j = 0; j < width; ++j) {
                    s += i[j] == '.' ? '.' : i[j];
                    // s += i[j] == '-' ? "ABCDFEGH"[xrnd()%8] : i[j];
                    //s += "ABCDFEGH"[xrnd()%8];
                }
                r.emplace_back(s);
            }
        } else {
            for (auto &i : vvc) {
                string s = "";
                for (int j = 0; j < width; ++j) {
                    s += i[j] == '.' ? ABCDEFGH[xrnd()%8] : i[j];
                    
                    
                    //s += "ABCDFEGH"[xrnd()%8];
                }
                r.emplace_back(s);
            }
        }
        
        return r;
    }
    int ret_score (const vector< vector<char> > &ret) {
        int score = 0;
        string a;
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20+12; ++x) {
                a += ret[y][x%20];
            }
            a += " ";
        }
        for (int x = 0; x < 20; ++x) {
            for (int y = 0; y < 20+12; ++y) {
                a += ret[y%20][x];
            }
            a += " ";
        }
        
        
        for (auto&& i : this->dict) {
            if (a.find(i.first) != string::npos) {
                score += i.second;
            }
        }
        
        return score;
    }
    
    // int all_y_score (const vector< vector<char> >& g) {
    //     int score = 0;
        
    //     for (int i = 0; i < this->ws.size(); ++i) {
    //         if (this->bws[i]) { continue; }
    //         int e = 20 - this->ws[i].size();
    //         for (int p = 0; p < e; ++p) {
    //             bool wb = true;
    //             for (int w = 0; w < this->ws[i].size(); ++w) {
    //                 if (this->ws[i][w] != g[p+w]) {
    //                     wb = false;
    //                     break;
    //                 }
    //             }
    //             if (wb) {
    //                 score += 1;
    //                 break;
    //             }
    //         }
    //     }
    //     return score;
    // }
    
    
    int line_score (const vector<char>& line) {
        int score = 0;
        
        for (int i = 0; i < this->ws.size(); ++i) {
            if (this->bws[i]) { continue; }
            if (this->ws[i].size() < 3) { continue; }
            int e = 20 - this->ws[i].size();
            for (int p = 0; p < e; ++p) {
                bool wb = true;
                for (int w = 0; w < this->ws[i].size(); ++w) {
                    if (this->ws[i][w] != line[p+w]) {
                        wb = false;
                        break;
                    }
                }
                if (wb) {
                    score += 1;
                    break;
                }
            }
        }
        return score;
    }
    void line_end_use_update (const vector<char>& line) {
        for (int i = 0; i < this->ws.size(); ++i) {
            if (this->bws[i]) { continue; }
            int e = 20 - this->ws[i].size();
            for (int p = 0; p < e; ++p) {
                bool wb = true;
                for (int w = 0; w < this->ws[i].size(); ++w) {
                    if (this->ws[i][w] != line[p+w]) {
                        wb = false;
                        break;
                    }
                }
                if (wb) {
                    this->bws[i] = true;
                }
            }
        }
    }
    
    
};

int main() {
    MM mm;
    vector< pair<string, int> > dict;
    
    
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        dict.emplace_back(s, 1);
    }
    
    
    // while (1) {
    //     vector< pair<string, int> > tdict;
        
    //     for (int i = 0; i < dict.size(); ++i) {
    //         int b = -1;
    //         for (int j = 0; j < dict.size(); ++j) {
    //             if (i==j) { continue; }
    //             if (dict[j].first.find(dict[i].first) != string::npos) {
    //                 b = j;
    //                 break;
    //             }
    //         }
    //         if (b < 0) {
    //             tdict.emplace_back(dict[i]);
    //         } else {
    //             dict[b].second += dict[i].second;
    //         }
    //     }
        
        
        
        
    //     if (tdict.size() == dict.size()) {break; }
    //     dict = tdict;
    // }
    
    
    vector<string> ret = mm.solve(20, 20, dict);
    
    // for (int i = 0; i < 20; ++i) {
    //     fdebug(ret[i]);
    // }
    
    
    for (int i = 0; i < 20; ++i) {
        cout << ret[i] << endl;
    }
    
    cout.flush();
}