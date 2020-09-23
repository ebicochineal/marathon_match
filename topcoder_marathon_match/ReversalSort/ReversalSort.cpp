#include <cmath>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

template<class F, class S> string in_v_to_str (const pair<F, S> v);
template<class F, class S> string v_to_str (const pair<F, S> v);
string in_v_to_str (const char v) { return "'" + string{v} + "'"; }
string in_v_to_str (const char* v) { return "\"" + string(v) + "\""; }
string in_v_to_str (const string v) { return "\"" + v + "\""; }
template<class T> string in_v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T> string v_to_str (const T v) { stringstream ss; ss << v; return ss.str(); }
template<class T, size_t N> string v_to_str (const array<T, N>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T, size_t N> string v_to_str (const array< array<T, N>, N >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const vector<T>& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << in_v_to_str(v[i]) << ", "; } ss << in_v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[]"; } return ss.str(); }
template<class T> string v_to_str (const vector< vector<T> >& v) { stringstream ss; if (v.size() > 0) { ss << "["; for (int i = 0; i < v.size() - 1; ++i) { ss << v_to_str(v[i]) << ", "; } ss << v_to_str(v[v.size() - 1]) << "]"; } else { ss << "[-]"; } return ss.str(); }
template<class T> string v_to_str (const set<T>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const map<K, V>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class T> string v_to_str (const unordered_set<T>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class K, class V> string v_to_str (const unordered_map<K, V>& v) { stringstream ss; int len = v.size(); ss << (v.size() > 0 ? "{" : "{}"); for (auto& i : v) { ss << in_v_to_str(i.first) << " : " << in_v_to_str(i.second) << (len-- > 1 ? ", " : "}"); } return ss.str(); }
template<class F, class S> string in_v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
template<class F, class S> string v_to_str (const pair<F, S> v) { stringstream ss; ss << "<" << v_to_str(v.first) << ", " << v_to_str(v.second) << ">"; return ss.str(); }
string print () { return ""; }
template<typename F, typename... R> string print (const F& f, const R& ...r) { stringstream ss; ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); } return ss.str(); }

template<typename F, typename... R> void pdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>" << ss.str() << "</cerr>" << endl;
}

template<typename F, typename... R> void fdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerrfile>" << ss.str() << "</cerrfile>" << endl;
}
template<typename F, typename... R> void tdebug (const F& f, const R& ...r) {
    stringstream ss;
    ss << v_to_str(f); if (sizeof...(r) > 0) { ss << " " << print(r...); }
    cerr << "<cerr>[time]" << ss.str() << "</cerr>" << endl;
}

struct e512pos {
public:
    int x;
    int y;
    e512pos () { this->x = 0; this->y = 0; }
    e512pos (int x, int y) {
        this->x = x;
        this->y = y;
    }
    e512pos operator + (const e512pos& t) { return e512pos(this->x + t.x, this->y + t.y); }
    e512pos operator - (const e512pos& t) { return e512pos(this->x - t.x, this->y - t.y); }
    bool operator == (const e512pos& t) const { return this->x == t.x && this->y == t.y; }
};
namespace std {
    template <> class hash<e512pos> {
    public:
        size_t operator()(const e512pos& t) const{ return hash<int>()(t.x<<16) | hash<int>()(t.y); }
    };
}
ostream& operator << (ostream& os, const e512pos& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
};

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

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

int64_t pows[1005];

struct RSRet {
public:
    int l, r;
    vector<int> sequence;
    vector< pair<int, int> > moves;
    int64_t score = 1000000000000;
    int64_t truescore = 1000000000000;
    RSRet () {}
    
    RSRet (int l, int r, vector<int> sequence) {
        this->l = l;
        this->r = r;
        this->sequence = sequence;
    }
    RSRet (int l, int r, vector<int> sequence, vector< pair<int, int> > moves) {
        this->l = l;
        this->r = r;
        this->sequence = sequence;
        this->moves = moves;
    }
};


class ReversalSort {
public:
    StopWatch sw;
    int N, K;
    double X;
    vector<int> sequence;
    vector<int> sorted_sequence;
    vector< pair<int, int> > blankmoves;
    vector<string> findSolution(int N, int K, double X, vector<int> sequence) {
        this->sw = StopWatch();
        this->N = N;
        this->K = K;
        this->X = X;
        this->sequence = sequence;
        this->sorted_sequence = sequence;
        sort(this->sorted_sequence.begin(), this->sorted_sequence.end());
        
        for (int i = 0; i < 1005; ++i) {
            pows[i] = pow((double)i, this->X);
        }
        
        int besttype = 0;
        
        
        RSRet bestret = this->InitRet();
        bestret.moves = this->greedyRet(bestret.sequence, bestret.moves);
        bestret.truescore = this->trueRetScore(bestret.moves);
        
        
        int cnt = 0;
        auto tmp1a = this->sequence;
        vector< pair<int, int> > tmp1b;
        auto tmp2a = this->sequence;
        vector< pair<int, int> > tmp2b;
        
        for (int j = 0; j < 32; ++j) {
            int cnt = 0;
            for (int i = 0; i < 100000; ++i) {
                if (this->sw.get_milli_time() >= 2000) { break; }
                vector< pair<int, int> > moves = tmp2b;
                vector<int> sequence = tmp2a;
                int a = xrnd() % this->N;
                int b = xrnd() % this->N;
                if (a > b) { swap(a, b); }
                if (a == b) { continue; }
                moves.emplace_back(a, b);
                reverse(sequence.begin()+a, sequence.begin()+b+1);
                auto tmoves = this->greedyRet(sequence, moves);
                int64_t score = this->trueRetScore(tmoves);
                if (score < bestret.truescore) {
                    bestret.truescore = score;
                    bestret.moves = tmoves;
                    besttype = 1;
                    tmp1a = sequence;
                    tmp1b = moves;
                }
                cnt += 1;
            }
            tmp2a = tmp1a;
            tmp2b = tmp1b;
            
        }
        
        
        for (int i = 0; i < 1000000; ++i) {
            if (this->sw.get_milli_time() >= 3000) { break; }
            vector< pair<int, int> > moves;
            vector<int> sequence = this->sequence;
            int a = xrnd() % this->N;
            int b = xrnd() % this->N;
            if (a > b) { swap(a, b); }
            if (a == b) { continue; }
            moves.emplace_back(a, b);
            reverse(sequence.begin()+a, sequence.begin()+b+1);
            moves = this->bubbleSort(sequence, moves).moves;
            int64_t score = this->trueRetScore(moves);
            if (score < bestret.truescore) {
                bestret.truescore = score;
                bestret.moves = moves;
                besttype = 2;
            }
            cnt += 1;
        }
        
        RSRet bs;
        
        bs = this->bubbleSort(this->sequence, vector< pair<int, int> >());
        if (bs.truescore < bestret.truescore) {
            bestret = bs;
            besttype = 3;
        }
        
        if (this->bubbleSortCostReverse(this->sequence, 0, this->N-1) < bestret.truescore) {
            vector< pair<int, int> > rvret;
            auto rvsequence = this->sequence;
            rvret.emplace_back(0, this->N-1);
            reverse(rvsequence.begin(), rvsequence.begin()+this->N-1+1);
            bestret = this->bubbleSort(rvsequence, rvret);
            besttype = 4;
        }
        
        bs = this->tSort(this->sequence, vector< pair<int, int> >());
        if (bs.truescore < bestret.truescore) {
            // pdebug(bs.truescore, bestscore);
            // pdebug("[",bs.truescore - bestscore, "]");
            bestret = bs;
            besttype = 5;
        }
        
        
        if (this->sw.get_milli_time() < 8000) {
            bs = this->beamSearch(tmp2a, tmp2b, this->N < 200 ? 512 : 128);
            if (bs.truescore < bestret.truescore) {
                bestret = bs;
                besttype = 6;
            }
        }
        if (this->sw.get_milli_time() < 8000) {
            bs = this->beamSearch(this->sequence, vector< pair<int, int> >(), this->N < 200 ? 512 : 128);
            if (bs.truescore < bestret.truescore) {
                bestret = bs;
                besttype = 7;
            }
        }
        
        if (this->sw.get_milli_time() < 8000) {
            tmp1a = this->sequence;
            tmp1b = this->blankmoves;
            tmp2a = this->sequence;
            tmp2b = this->blankmoves;
            for (int j = 0; j < 32; ++j) {
                int cnt = 0;
                for (int i = 0; i < 1000; ++i) {
                    if (this->sw.get_milli_time() >= 9500) { break; }
                    vector< pair<int, int> > moves = tmp2b;
                    vector<int> sequence = tmp2a;
                    int a = xrnd() % this->N;
                    int b = xrnd() % this->N;
                    if (a > b) { swap(a, b); }
                    if (a == b) { continue; }
                    moves.emplace_back(a, b);
                    reverse(sequence.begin()+a, sequence.begin()+b+1);
                    auto tmoves = this->beamSearch(sequence, moves, 32).moves;
                    int64_t score = this->trueRetScore(tmoves);
                    if (score < bestret.truescore) {
                        bestret.truescore = score;
                        bestret.moves = tmoves;
                        besttype = 8;
                        tmp1a = sequence;
                        tmp1b = moves;
                    }
                    cnt += 1;
                }
                tmp2a = tmp1a;
                tmp2b = tmp1b;
                
            }
        }
        
        
        pdebug("[", besttype, "]");
        // int n = 0;
        // for (auto&& i : bestret) {
        //     n = max(n, i.second-i.first+1);
        // }
        // pdebug(n);
        
        
        pdebug(N, X, K);
        tdebug(this->sw.get_milli_time());
        vector<string> rvs = this->toStringsRet(bestret.moves);
        //pdebug(rvs.size(), N*N/2);
        
        
        //pdebug(N, K, X, cnt, this->sw.get_milli_time());
        return rvs;
        
    }
    
    
    
    vector< pair<int, int> > greedyRet (vector<int> sequence, vector< pair<int, int> > moves) {
        int l = 0;
        int r = this->N - 1;
        while (1) {
            while (sequence[l] == this->sorted_sequence[l]) { l += 1; }
            while (sequence[r] == this->sorted_sequence[r]) { r -= 1; }
            if (l+this->N-r-1 >= this->N) { break; }
            
            
            int t = this->sorted_sequence[l];
            int k=-1;
            double bestscore = 1000000000;
            int lr = 0;
            for (int q=l+1; q<=r; ++q) {
                if (sequence[q]!=t) { continue; }
                double cnt = 0;
                double x = 1.0;
                for (int a=l, b=q; b >= l; ++a,--b) {
                    if (sequence[b]==this->sorted_sequence[a]) {
                        cnt += x;
                    } else {
                        break;
                    }
                    x += 0.1;
                }
                
                if (q == r) {
                    if (sequence[l]==this->sorted_sequence[q]) {
                        cnt += x;
                    }
                }
                if (q != r) {
                    if (sequence[l]==sequence[q+1]) {
                        cnt += 0.5;
                    }
                    if (sequence[q]==sequence[q+1]) {
                        cnt -= 0.5;
                    }
                }
                
                
                double score = pows[q-l+1] / cnt;
                if (score < bestscore) {
                    k=q;
                    bestscore = score;
                }
            }
            
            t = this->sorted_sequence[r];
            for (int q=r-1; q>=l; --q) {
                if (sequence[q]!=t) { continue; }
                double cnt = 0;
                double x = 1.0;
                for (int a=r, b=q; b <= r; --a,++b) {
                    if (sequence[b]==this->sorted_sequence[a]) {
                        cnt += x;
                    } else {
                        break;
                    }
                    x += 0.1;
                }
                
                
                if (q == l) {
                    if (sequence[r]==this->sorted_sequence[q]) {
                        cnt += x;
                    }
                }
                if (q != l) {
                    if (sequence[r]==sequence[q-1]) {
                        cnt += 0.5;
                    }
                    if (sequence[q]==sequence[q-1]) {
                        cnt -= 0.5;
                    }
                }
                
                
                
                double score = pows[r-q+1] / cnt;
                if (score < bestscore) {
                    k=q;
                    bestscore = score;
                    lr = 1;
                }
            }
            
            if (lr == 0) {
                moves.emplace_back(l, k);
                reverse(sequence.begin()+l, sequence.begin()+k+1);
            } else {
                moves.emplace_back(k, r);
                reverse(sequence.begin()+k, sequence.begin()+r+1);
            }
        }
        return moves;
    }
    
    
    vector<string> toStringsRet (vector< pair<int, int> > &ret) {
        vector<string> r;
        for (auto&& i : ret) {
            if (i.first < 10000) {
                r.emplace_back(to_string(i.first) + " " + to_string(i.second));
            
            } else {
                
                for (int j = i.second-1-10000; j >= i.first-10000; --j) {
                    r.emplace_back(to_string(j) + " " + to_string(j+1));
                }
            }
            
            
        }
        return r;
    }
    
    int64_t trueRetScore (vector< pair<int, int> > moves) {
        int64_t r = 0;
        for (auto&& i : moves) {
            r += pows[1 + i.second - i.first];
        }
        return r;
    }
    
    void setComplate (RSRet& target) {
        while (target.sequence[target.l] == this->sorted_sequence[target.l]) { target.l += 1; }
        while (target.sequence[target.r] == this->sorted_sequence[target.r]) { target.r -= 1; }
    }
    
    // void setComplateR (RSRet& target, int l, int r) {
    //     while (target.sequence[target.l] == this->sorted_sequence[target.l]) {
    //         target.l += 1;
    //         l += 1;
    //     }
    //     while (target.sequence[target.r] == this->sorted_sequence[target.r]) {
    //         target.r -= 1;
    //         r -= 1;
    //     }
    // }
    
    RSRet bubbleSort (vector<int> sequence, vector< pair<int, int> > ret) {
        RSRet r(0, this->N-1, sequence);
        r.moves = ret;
        this->setComplate(r);
        r.score = this->trueRetScore(ret);
        r.truescore = this->trueRetScore(ret);
        for (int y = 0; y < this->N-1; ++y) {
            for (int x = this->N-1; x > y; --x) {
                if (r.sequence[x-1] > r.sequence[x]) {
                    swap(r.sequence[x-1], r.sequence[x]);
                    r.moves.emplace_back(x-1, x);
                    r.truescore += pows[2];
                    r.score += pows[2];
                }
            }
        }
        return r;
    }
    
    RSRet tSort (vector<int> sequence, vector< pair<int, int> > ret) {
        RSRet t(0, this->N-1, sequence);
        t.moves = ret;
        this->setComplate(t);
        t.score = this->trueRetScore(ret);
        t.truescore = this->trueRetScore(ret);
        
        
        
        for (int y = 0; y < this->N-1; ++y) {
            for (int x = this->N-1; x > y; --x) {
                if (t.sequence[x-1] > t.sequence[x]) {
                    swap(t.sequence[x-1], t.sequence[x]);
                    t.moves.emplace_back(x-1, x);
                    t.truescore += pows[2];
                    t.score += pows[2];
                    if (this->sw.get_milli_time() > 9000) { continue; }
                    
                    for (int n = 2; n >= 2; --n) {
                        for (int i = y; i < this->N-n; ++i) {
                            int64_t a = this->bubbleSortCostReverse(t.sequence, i, i+n);
                            int64_t b = this->bubbleSortCost(t.sequence, i, i+n);
                            
                            if (a-b < 0) {
                                t.moves.emplace_back(i, i+n);
                                t.score += a;
                                t.truescore += a;
                                reverse(t.sequence.begin()+i, t.sequence.begin()+i+n+1);
                                this->bubbleSortAdd(t, i, i+n);
                            }
                        }
                    }
                    
                    // for (int n = 2; n >= 2; --n) {
                    //     for (int i = y; i < this->N-n; ++i) {
                    //         int b = pows[2] * 3;
                    //         if (pows[3] < b && t.sequence[i] > t.sequence[i+1] && t.sequence[i+1] > t.sequence[i+2]) {
                    //             int64_t a = this->bubbleSortCostReverse(t.sequence, i, i+n);
                    //             t.moves.emplace_back(i, i+n);
                    //             t.score += a;
                    //             t.truescore += a;
                    //             reverse(t.sequence.begin()+i, t.sequence.begin()+i+n+1);
                    //             this->bubbleSortAdd(t, i, i+n);
                    //         }
                    //     }
                    // }
                    
                    
                }
            }
            
        }
        return t;
    }
    
    RSRet InitRet () {
        return RSRet(0, this->N-1, this->sequence, this->blankmoves);
    }
    
    void bubbleSortAdd (RSRet& t, int l, int r) {
        for (int y = l; y < r; ++y) {
            for (int x = r; x > y; --x) {
                if (t.sequence[x-1] > t.sequence[x]) {
                    swap(t.sequence[x-1], t.sequence[x]);
                    t.moves.emplace_back(x-1, x);
                    t.truescore += pows[2];
                    t.score += pows[2];
                }
            }
        }
    }
    
    int64_t bubbleSortCostReverseDiff (vector<int>& sequence, int l, int r) {
        return this->bubbleSortCostReverse(sequence, l, r) - this->bubbleSortCost(sequence, l, r);
    }
    
    
    int64_t bubbleSortCostReverse (vector<int>& sequence, int l, int r) {
        static int tmp[1000];
        const int p = pows[2];
        int64_t cost = pows[r - l + 1];
        for (int i=l, j=0; i<=r; ++i, ++j) {
            tmp[j] = sequence[i];
        }
        
        for (int y = l; y < r; ++y) {
            for (int x = r; x > y; --x) {
                if (sequence[x-1] < sequence[x]) {
                    swap(sequence[x-1], sequence[x]);
                    cost += p;
                }
            }
        }
        
        for (int i=l, j=0; i<=r; ++i, ++j) {
            sequence[i] = tmp[j];
        }
        return cost;
    }
    
    int64_t bubbleSortCost (vector<int>& sequence, int l, int r) {
        static int tmp[1000];
        const int p = pows[2];
        int64_t cost = 0;
        for (int i=l, j=0; i<=r; ++i, ++j) {
            tmp[j] = sequence[i];
        }
        
        for (int y = l; y < r; ++y) {
            for (int x = r; x > y; --x) {
                if (sequence[x-1] > sequence[x]) {
                    swap(sequence[x-1], sequence[x]);
                    cost += p;
                }
            }
        }
        
        for (int i=l, j=0; i<=r; ++i, ++j) {
            sequence[i] = tmp[j];
        }
        return cost;
    }
    
    vector<RSRet> bms;
    int len = 0;
    RSRet beamSearch (vector<int> sequence, vector< pair<int, int> > moves, int bw=8) {
        int time = this->sw.get_milli_time();
        RSRet start(0, this->N-1, sequence);
        start.moves = moves;
        this->setComplate(start);
        start.score = this->trueRetScore(moves);
        start.truescore = this->trueRetScore(moves);
        
        vector<RSRet> rets;
        RSRet bestcomplete(0, this->N-1, sequence);
        
        rets.emplace_back(start);
        
        
        vector<RSRet> trets;
        while (rets.size() > 0) {
            // if (this->sw.get_milli_time() > 2500) {
            //     bw = min(bw, 64);
            // }
            // if (this->sw.get_milli_time() > 5000) {
            //     bw = min(bw, 32);
            // }
            if (this->sw.get_milli_time() > 7000) {
                bw = min(bw, 64);
            }
            if (this->sw.get_milli_time() > 8000) {
                bw = min(bw, 32);
            }
            if (this->sw.get_milli_time() > 9000) {
                bw = min(bw, 16);
            }
            if (this->sw.get_milli_time() > 9500) {
                bw = min(bw, 2);
            }
            sort(rets.begin(), rets.end(), [](const RSRet& a, const RSRet& b) { return a.score < b.score; });
            
            trets.clear();
            
            double prevscore = -1;
            for (int i = 0; i < rets.size(); ++i) {
                if (rets[i].l+this->N-rets[i].r-1 < this->N) {
                    // tret emplace
                    if (rets[i].score == prevscore) { continue; }
                    prevscore = rets[i].score;
                    
                    if (trets.size() < bw) {
                        trets.emplace_back(move(rets[i]));
                    }
                } else {
                    // update return
                    if (rets[i].truescore < bestcomplete.truescore) {
                        bestcomplete = rets[i];
                    }
                }
            }
            rets.clear();
            
            
            for (auto&& i : trets) {
                //
                
                for (int q=i.l+1; q<=i.r; ++q) {
                    if (i.sequence[q]!=this->sorted_sequence[i.l]) { continue; }
                    double cnt = 0;
                    double x = 1.0;
                    for (int a=i.l, b=q; b >= i.l; ++a,--b) {
                        if (i.sequence[b]==this->sorted_sequence[a]) {
                            cnt += x;
                        } else {
                            break;
                        }
                        x += 0.1;
                    }
                    if (q == i.r) {
                        if (i.sequence[i.l]==this->sorted_sequence[q]) {
                            cnt += x;
                        }
                    }
                    if (q != i.r) {
                        if (i.sequence[i.l]==i.sequence[q+1]) {
                            cnt += 0.5;
                        }
                        if (i.sequence[q]==i.sequence[q+1]) {
                            cnt -= 0.5;
                        }
                    }
                    
                    double score = pows[q-i.l+1] / cnt;
                    RSRet t = i;
                    
                    t.moves.emplace_back(i.l, q);
                    reverse(t.sequence.begin()+i.l, t.sequence.begin()+q+1);
                    t.score += score;
                    t.truescore += pows[q-i.l+1];
                    this->setComplate(t);
                    
                    if (rets.size() >= bw) {
                        rets[bw-1] = move(t);
                    } else {
                        rets.emplace_back(move(t));
                    }
                    sort(rets.begin(), rets.end(), [](const RSRet& a, const RSRet& b) { return a.score < b.score; });
                }
                
                for (int q=i.r-1; q>=i.l; --q) {
                    if (i.sequence[q]!=this->sorted_sequence[i.r]) { continue; }
                    double cnt = 0;
                    double x = 1.0;
                    for (int a=i.r, b=q; b <= i.r; --a,++b) {
                        if (i.sequence[b]==this->sorted_sequence[a]) {
                            cnt += x;
                        } else {
                            break;
                        }
                        x += 0.1;
                    }
                    if (q == i.l) {
                        if (i.sequence[i.r]==this->sorted_sequence[q]) {
                            cnt += x;
                        }
                    }
                    
                    if (q != i.l) {
                        if (i.sequence[i.r]==i.sequence[q-1]) {
                            cnt += 0.5;
                        }
                        if (i.sequence[q]==i.sequence[q-1]) {
                            cnt -= 0.5;
                        }
                    }
                    
                    double score = pows[i.r-q+1] / cnt;
                    
                    RSRet t = i;
                    t.moves.emplace_back(q, i.r);
                    reverse(t.sequence.begin()+q, t.sequence.begin()+i.r+1);
                    t.score += score;
                    t.truescore += pows[i.r-q+1];
                    this->setComplate(t);
                    
                    if (rets.size() >= bw) {
                        rets[bw-1] = move(t);
                    } else {
                        rets.emplace_back(move(t));
                    }
                    sort(rets.begin(), rets.end(), [](const RSRet& a, const RSRet& b) { return a.score < b.score; });
                }
                
                // for (int q=i.l+1; q<=i.r; ++q) {
                //     if (i.sequence[q]!=this->sorted_sequence[i.l]) { continue; }
                //     double score = pows[2] * abs(q-i.l);
                //     RSRet t = i;
                //     t.moves.emplace_back(i.l+10000, q+10000);
                    
                //     for (int j = q-1; j >= i.l; --j) {
                //         swap(t.sequence[j], t.sequence[j+1]);
                //     }
                //     t.score += score;
                //     t.truescore += pows[2] * abs(q-i.l);
                //     this->setComplate(t);
                    
                //     if (rets.size() >= bw) {
                //         rets[bw-1] = move(t);
                //     } else {
                //         rets.emplace_back(move(t));
                //     }
                //     sort(rets.begin(), rets.end(), [](const RSRet& a, const RSRet& b) { return a.score < b.score; });
                    
                //     break;
                // }
                
            }
            
        }
        // pdebug(this->sw.get_milli_time()-time);
        return bestcomplete;
    }
    
    
    void vreverse (vector<int> &seq, int pos1, int pos2) {
        for (int i=pos1,k=pos2; i<k; i++,k--) {
            int temp=seq[i];
            seq[i]=seq[k];
            seq[k]=temp;
        }
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    ReversalSort prog;
    int N, K;
    int temp;
    double X;
    vector<int> sequence;
    cin >> N;
    cin >> K;
    cin >> X;

    for (int i=0; i<N; i++) {
        cin >> temp;
        sequence.push_back(temp);
    }
  
    vector<string> ret = prog.findSolution(N, K, X, sequence);
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    
    cout.flush();
}