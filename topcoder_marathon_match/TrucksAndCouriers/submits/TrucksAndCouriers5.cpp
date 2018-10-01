#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <utility>
#include <complex>
#include <array>
#include <random>
using namespace std;

#include <time.h>
#include <sys/timeb.h>

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

class EItem {
public:
    int itemNumber;
    int x;
    int y;
    
    EItem (int itemNumber, int x, int y) {
        this->itemNumber = itemNumber;
        this->x = x;
        this->y = y;
    }
};


class TrucksAndCouriers {
public:
    int truckFixed;
    int truckVariable;
    vector<int> warehouseX;
    vector<int> warehouseY;
    vector<int> warehouseItem;
    vector<int> warehouseQuantity;
    vector<int> customerX;
    vector<int> customerY;
    vector<int> customerItem;
    
    
    vector<string> retmessage;
    vector<EItem> items;
    
    // truck
    int tcost = 0;
    vector<string> tretmessage;
    vector<EItem> titems;
    
    // truck
    int tcost2 = 0;
    vector<string> tretmessage2;
    vector<EItem> titems2;
    
    // void go_truck_to_xy (int itemindex, int ex, int ey) {
    //     int sx = this->titems[itemindex].x;
    //     int sy = this->titems[itemindex].y;
        
    //     if (sx == ex && sy == ey) { return; }
        
    //     this->tcost += this->truckFixed;
    //     this->tcost += (abs(sx - ex) +  + abs(sy - ey)) * this->truckVariable;
        
    //     string s = "T," + to_string(sx) + "," + to_string(sy) + "," + to_string(ex) + "," + to_string(ey) + "," + to_string(this->titems[itemindex].itemNumber);
    //     this->titems[itemindex].x = ex;
    //     this->titems[itemindex].y = ey;
    //     this->tretmessage.emplace_back(s);
    // }
    
    void go_truck_to_xy (vector<int> itemindexs, int ex, int ey) {
        int sx = this->titems[itemindexs[0]].x;
        int sy = this->titems[itemindexs[0]].y;
        
        if (sx == ex && sy == ey) { return; }
        
        this->tcost += this->truckFixed;
        this->tcost += (abs(sx - ex) +  + abs(sy - ey)) * this->truckVariable;
        
        
        string s = "T," + to_string(sx) + "," + to_string(sy) + "," + to_string(ex) + "," + to_string(ey);
        for (auto &i : itemindexs) {
            s += "," + to_string(this->titems[i].itemNumber);
            this->titems[i].x = ex;
            this->titems[i].y = ey;
        }
        
        this->tretmessage.emplace_back(s);
    }
    
    void move_items (int a, int b) {
        vector<int> needitems(100, 0);
        vector<int> area_item_index;
        for (int i = 0; i < this->titems.size(); ++i) {
            int x = this->titems[i].x;
            int y = this->titems[i].y;
            if (this->pos_to_area(x, y) == a) {
                area_item_index.emplace_back(i);
            }
        }
        for (int i = 0; i < this->customerItem.size(); ++i) {
            int x = this->customerX[i];
            int y = this->customerY[i];
            if (this->pos_to_area(x, y) == a) {
                needitems[this->customerItem[i]] += 1;
            }
        }
        
        vector<int> notneed_item_indexs;
        unordered_map<mpos, vector<int>> trucks;
        for (auto &i : area_item_index) {
            const int n = this->titems[i].itemNumber;
            const int x = this->titems[i].x;
            const int y = this->titems[i].y;
            const mpos m = mpos(x, y);
            if (needitems[n] < 1) {
                if (trucks.find(m) == trucks.end()) {
                    trucks.emplace(m, vector<int>());
                }
                trucks[m].emplace_back(i);
                notneed_item_indexs.emplace_back(i);
            } else {
                needitems[n] -= 1;
            }
        }
        
        for (auto &i : trucks) {
            int ax, ay;
            this->area_pos(a, ax, ay);
            this->go_truck_to_xy(i.second, ax, ay);
        }
        
        int bx, by;
        this->area_pos(b, bx, by);
        if (notneed_item_indexs.size() > 0) {
            this->go_truck_to_xy(notneed_item_indexs, bx, by);
        }
    }
    
    int go_tdelivery () {
        vector<bool> itemb(this->titems.size(), false);
        int score = 0;
        for (int i = 0; i < this->customerItem.size(); ++i) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->titems.size(); ++j) {
                if (itemb[j] || this->titems[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems[j].x - cpx);
                int diffy = abs(this->titems[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->titems[itemsindex].x;
            int dpy = this->titems[itemsindex].y;
            score += mindist;
            this->tretmessage.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        return score;
    }
    
    
    int pos_to_area (const int x, const int y) {
        int px = min(x / 50, 19);
        int py = min(y / 333, 2);
        return py * 20 + px;
    }
    
    void area_pos (const int n, int &px, int &py) {
        const int x = n % 20;
        const int y = n / 20;
        px = 25 + 50 * x;
        py = 166 + 333 * y;
    }
    
    void move_truck_items () {
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(0+i, 1+i);
        }
        this->move_items(19, 39);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(39-i, 38-i);
        }
        this->move_items(20, 40);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(40+i, 41+i);
        }
        
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(59-i, 58-i);
        }
        this->move_items(40, 20);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(20+i, 21+i);
        }
        this->move_items(39, 19);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items(19-i, 18-i);
        }
        
    }
    
    ////////////////////////////////////////////////
    
    void go_truck_to_xy2 (vector<int> itemindexs, int ex, int ey) {
        int sx = this->titems2[itemindexs[0]].x;
        int sy = this->titems2[itemindexs[0]].y;
        
        if (sx == ex && sy == ey) { return; }
        
        this->tcost2 += this->truckFixed;
        this->tcost2 += (abs(sx - ex) +  + abs(sy - ey)) * this->truckVariable;
        
        
        string s = "T," + to_string(sx) + "," + to_string(sy) + "," + to_string(ex) + "," + to_string(ey);
        for (auto &i : itemindexs) {
            s += "," + to_string(this->titems2[i].itemNumber);
            this->titems2[i].x = ex;
            this->titems2[i].y = ey;
        }
        
        this->tretmessage2.emplace_back(s);
    }
    
    void move_items2 (int a, int b) {
        vector<int> needitems(100, 0);
        vector<int> area_item_index;
        for (int i = 0; i < this->titems2.size(); ++i) {
            int x = this->titems2[i].x;
            int y = this->titems2[i].y;
            if (this->pos_to_area2(x, y) == a) {
                area_item_index.emplace_back(i);
            }
        }
        for (int i = 0; i < this->customerItem.size(); ++i) {
            int x = this->customerX[i];
            int y = this->customerY[i];
            if (this->pos_to_area2(x, y) == a) {
                needitems[this->customerItem[i]] += 1;
            }
        }
        
        vector<int> notneed_item_indexs;
        unordered_map<mpos, vector<int>> trucks;
        for (auto &i : area_item_index) {
            const int n = this->titems2[i].itemNumber;
            const int x = this->titems2[i].x;
            const int y = this->titems2[i].y;
            const mpos m = mpos(x, y);
            if (needitems[n] < 1) {
                if (trucks.find(m) == trucks.end()) {
                    trucks.emplace(m, vector<int>());
                }
                trucks[m].emplace_back(i);
                notneed_item_indexs.emplace_back(i);
            } else {
                needitems[n] -= 1;
            }
        }
        
        for (auto &i : trucks) {
            int ax, ay;
            this->area_pos2(a, ax, ay);
            this->go_truck_to_xy2(i.second, ax, ay);
        }
        
        int bx, by;
        this->area_pos2(b, bx, by);
        if (notneed_item_indexs.size() > 0) {
            this->go_truck_to_xy2(notneed_item_indexs, bx, by);
        }
    }
    
    int go_tdelivery2 () {
        vector<bool> itemb(this->titems2.size(), false);
        int score = 0;
        for (int i = 0; i < this->customerItem.size(); ++i) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->titems2.size(); ++j) {
                if (itemb[j] || this->titems2[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems2[j].x - cpx);
                int diffy = abs(this->titems2[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->titems2[itemsindex].x;
            int dpy = this->titems2[itemsindex].y;
            score += mindist;
            this->tretmessage2.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        return score;
    }
    
    
    int pos_to_area2 (const int x, const int y) {
        int px = min(x / 50,19);
        int py = min(y / 200, 4);
        return py * 20 + px;
    }
    
    
    void area_pos2 (const int n, int &px, int &py) {
        const int x = n % 20;
        const int y = n / 20;
        px = 25 + 50 * x;
        py = 100 + 200 * y;
    }
    
    void move_truck_items2 () {
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(0+i, 1+i);
        }
        this->move_items2(19, 39);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(39-i, 38-i);
        }
        this->move_items2(20, 40);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(40+i, 41+i);
        }
        this->move_items2(59, 79);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(79-i, 78-i);
        }
        this->move_items2(60, 80);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(80+i, 81+i);
        }
        
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(99-i, 98-i);
        }
        this->move_items2(80, 60);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(60+i, 61+i);
        }
        this->move_items2(79, 59);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(59-i, 58-i);
        }
        this->move_items2(40, 20);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(20+i, 21+i);
        }
        this->move_items2(39, 19);
        for (int i = 0; i < 20-1; ++i) {
            this->move_items2(19-i, 18-i);
        }
    }
    
    void go_delivery () {
        vector<bool> itemb(this->items.size(), false);
        int score = 0;
        for (int i = 0; i < this->customerItem.size(); ++i) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->items.size(); ++j) {
                if (itemb[j] || this->items[j].itemNumber != inum) { continue; }
                int diffx = abs(this->items[j].x - cpx);
                int diffy = abs(this->items[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->items[itemsindex].x;
            int dpy = this->items[itemsindex].y;
            score += mindist;
            this->retmessage.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        // cerr << "score " << score << endl;
    }
    
    int get_score () {
        vector<bool> itemb(this->items.size(), false);
        int score = 0;
        for (int i = 0; i < this->customerItem.size(); ++i) {
            const int inum = this->customerItem[i];
            const int cpx = this->customerX[i];
            const int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            for (int j = 0; j < this->items.size(); ++j) {
                if (itemb[j] || this->items[j].itemNumber != inum) { continue; }
                int diffx = abs(this->items[j].x - cpx);
                int diffy = abs(this->items[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            itemb[itemsindex] = true;
            score += mindist;
        }
        return score;
    }
    
    vector<int> best;
    int bestscore = 100000000;
    int best_delivery () {
        vector<bool> itemb(this->items.size(), false);
        vector<int> tmp;
        for(int i = 0; i < this->customerItem.size(); i++) {
            tmp.emplace_back(i);
        }
        mt19937 mt(xrnd());
        shuffle(tmp.begin(), tmp.end(), mt);
        int score = 0;
        for (auto &i : tmp) {
            const int inum = this->customerItem[i];
            const int cpx = this->customerX[i];
            const int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            for (int j = 0; j < this->items.size(); ++j) {
                if (itemb[j] || this->items[j].itemNumber != inum) { continue; }
                int diffx = abs(this->items[j].x - cpx);
                int diffy = abs(this->items[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            itemb[itemsindex] = true;
            score += mindist;
        }
        if (score <= this->bestscore) {
            this->best = tmp;
            this->bestscore = score;
        }
        return score;
    }
    
    int best_go_delivery () {
        vector<bool> itemb(this->items.size(), false);
        
        int score = 0;
        for (auto &i : this->best) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->items.size(); ++j) {
                if (itemb[j] || this->items[j].itemNumber != inum) { continue; }
                int diffx = abs(this->items[j].x - cpx);
                int diffy = abs(this->items[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->items[itemsindex].x;
            int dpy = this->items[itemsindex].y;
            score += mindist;
            this->retmessage.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        return score;
    }
    
    vector<int> tbest;
    int tbestscore = 100000000;
    int best_tdelivery () {
        vector<bool> itemb(this->titems.size(), false);
        vector<int> tmp;
        for(int i = 0; i < this->customerItem.size(); i++) {
            tmp.emplace_back(i);
        }
        mt19937 mt(xrnd());
        shuffle(tmp.begin(), tmp.end(), mt);
        int score = 0;
        for (auto &i : tmp) {
            const int inum = this->customerItem[i];
            const int cpx = this->customerX[i];
            const int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            for (int j = 0; j < this->titems.size(); ++j) {
                if (itemb[j] || this->titems[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems[j].x - cpx);
                int diffy = abs(this->titems[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            itemb[itemsindex] = true;
            score += mindist;
        }
        if (score <= this->tbestscore) {
            this->tbest = tmp;
            this->tbestscore = score;
        }
        return score;
    }
    
    int best_go_tdelivery () {
        vector<bool> itemb(this->titems.size(), false);
        
        int score = 0;
        for (auto &i : this->tbest) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->titems.size(); ++j) {
                if (itemb[j] || this->titems[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems[j].x - cpx);
                int diffy = abs(this->titems[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->titems[itemsindex].x;
            int dpy = this->titems[itemsindex].y;
            score += mindist;
            this->tretmessage.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        return score;
    }
    
    
    vector<int> tbest2;
    int tbestscore2 = 100000000;
    int best_tdelivery2 () {
        vector<bool> itemb(this->titems2.size(), false);
        vector<int> tmp;
        for(int i = 0; i < this->customerItem.size(); i++) {
            tmp.emplace_back(i);
        }
        mt19937 mt(xrnd());
        shuffle(tmp.begin(), tmp.end(), mt);
        int score = 0;
        for (auto &i : tmp) {
            const int inum = this->customerItem[i];
            const int cpx = this->customerX[i];
            const int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            for (int j = 0; j < this->titems2.size(); ++j) {
                if (itemb[j] || this->titems2[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems2[j].x - cpx);
                int diffy = abs(this->titems2[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            itemb[itemsindex] = true;
            score += mindist;
        }
        if (score <= this->tbestscore2) {
            this->tbest2 = tmp;
            this->tbestscore2 = score;
        }
        return score;
    }
    
    int best_go_tdelivery2 () {
        vector<bool> itemb(this->titems2.size(), false);
        
        int score = 0;
        for (auto &i : this->tbest2) {
            int inum = this->customerItem[i];
            int cpx = this->customerX[i];
            int cpy = this->customerY[i];
            int mindist = 10000;
            int itemsindex = -1;
            
            for (int j = 0; j < this->titems2.size(); ++j) {
                if (itemb[j] || this->titems2[j].itemNumber != inum) { continue; }
                int diffx = abs(this->titems2[j].x - cpx);
                int diffy = abs(this->titems2[j].y - cpy);
                int dist = diffx + diffy;
                if (dist <= mindist) {
                    mindist = dist;
                    itemsindex = j;
                }
            }
            
            itemb[itemsindex] = true;
            int dpx = this->titems2[itemsindex].x;
            int dpy = this->titems2[itemsindex].y;
            score += mindist;
            this->tretmessage2.emplace_back("C," + to_string(dpx) + "," + to_string(dpy) + "," + to_string(cpx) + "," + to_string(cpy) + "," + to_string(inum));
        }
        return score;
    }
    
    
    vector<string> planShipping(int truckFixed, int truckVariable, vector<int> warehouseX, vector<int> warehouseY, vector<int> warehouseItem, vector<int> warehouseQuantity, vector<int> customerX, vector<int> customerY, vector<int> customerItem) {
        StopWatch sw;
        this->truckFixed = truckFixed;
        this->truckVariable = truckVariable;
        this->warehouseX = warehouseX;
        this->warehouseY = warehouseY;
        this->warehouseItem = warehouseItem;
        this->warehouseQuantity = warehouseQuantity;
        this->customerX = customerX;
        this->customerY = customerY;
        this->customerItem = customerItem;
        
        for (int i = 0; i < warehouseItem.size(); ++i) {
            for (int j = 0; j < warehouseQuantity[i]; ++j) {
                this->items.emplace_back(warehouseItem[i], warehouseX[i], warehouseY[i]);
            }
        }
        this->titems = this->items;
        this->titems2 = this->items;
        ////////////////////////////////////////////////////////////////
        
        
        int dscore = this->best_delivery();
        
        this->move_truck_items();
        int tscore = this->best_tdelivery() + this->tcost;
        
        this->move_truck_items2();
        int tscore2 = this->best_tdelivery2() + this->tcost2;
        // cerr << print('T', tscore) << endl;
        
        if (tscore < dscore) {
            if (tscore2 < tscore) {
                for (int i = 0; i < 90000; ++i) {
                    if (i % 100 == 0 && sw.get_milli_time() > 6000) { break; }
                    this->best_tdelivery2();
                }
                this->best_go_tdelivery2();
                return this->tretmessage2;
            } else {
                for (int i = 0; i < 90000; ++i) {
                    if (i % 100 == 0 && sw.get_milli_time() > 6000) { break; }
                    this->best_tdelivery();
                }
                this->best_go_tdelivery();
                return this->tretmessage;
            }
        } else {
            if (tscore2 < dscore) {
                for (int i = 0; i < 90000; ++i) {
                    if (i % 100 == 0 && sw.get_milli_time() > 6000) { break; }
                    this->best_tdelivery2();
                }
                this->best_go_tdelivery2();
                return this->tretmessage2;
            } else {
                for (int i = 0; i < 90000; ++i) {
                    if (i % 100 == 0 && sw.get_milli_time() > 6000) { break; }
                    this->best_delivery();
                }
                this->best_go_delivery();
                return this->retmessage;
            }
        }
    }
};




// >>v
// v<<
// >>>
//
// <<<
// >>^
// ^<<

//////////////////////////////////////////////////////////////////

vector<int> readVector () {
    int n, t; cin >> n;
    vector<int> ret;
    for (int i = 0; i < n; ++i) { cin >> t; ret.emplace_back(t); }
    return ret;
}

int main () {
    TrucksAndCouriers sol;
    
    int truckFixed; cin >> truckFixed;
    int truckVariable; cin >> truckVariable;
    auto warehouseX = readVector();
    auto warehouseY = readVector();
    auto warehouseItem = readVector();
    auto warehouseQuantity = readVector();
    auto customerX = readVector();
    auto customerY = readVector();
    auto customerItem = readVector();
    StopWatch sw;
    vector<string> ret = sol.planShipping(truckFixed, truckVariable, warehouseX, warehouseY,
                        warehouseItem, warehouseQuantity, customerX, customerY, customerItem);
    cerr << sw.get_milli_time();
    cout << ret.size() << endl;
    for (auto &i : ret) { cout << i << endl; }
    cout.flush();
}


