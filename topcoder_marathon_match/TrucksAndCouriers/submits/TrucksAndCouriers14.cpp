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

// #include <iostream>
// #include <fstream>

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
    
    unordered_set<mpos> warehouses;
    
    vector<string> retmessage;
    vector<EItem> items;
    
    // truck
    int tcost = 0;
    vector<string> tretmessage;
    vector<EItem> titems;
    
    vector< pair <mpos, mpos> > mstree;
    
    inline int manhattan_distance(mpos a, mpos b) {
        return abs(a.x-b.x) + abs(a.y - b.y);
    }
    
    void warehouse_minimum_steiner_tree () {
        vector<mpos> va;
        vector<mpos> vb;
        for (auto &i : this->warehouses) { vb.emplace_back(i); }
        va.emplace_back(vb[vb.size()-1]);
        vb[vb.size()-1] = mpos(-1, -1);
        while (va.size() < this->warehouses.size()) {
            int mindist = 10000;
            int ind_a = -1;
            int ind_b = -1;
            for (int i = 0; i < va.size(); ++i) {
                const mpos a = va[i];
                for (int j = 0; j < vb.size(); ++j) {
                    const mpos b = vb[j];
                    if (b.x < 0) { continue; }
                    int d = this->manhattan_distance(a, b);
                    if (d < mindist) {
                        mindist = d;
                        ind_a = i;
                        ind_b = j;
                    }
                }
            }
            
            if (ind_a > -1) {
                this->mstree.emplace_back(va[ind_a], vb[ind_b]);
                va.emplace_back(vb[ind_b]);
                vb[ind_b].x = -1;
                vb[ind_b].y = -1;
            }
        }
    }
    
    vector< pair<mpos, mpos> > lu;
    vector< pair<mpos, mpos> > ld;
    vector< pair<mpos, mpos> > rd;
    vector< pair<mpos, mpos> > ru;
    void collection_root_lu () {
        mpos tp(0, 0);
        mpos ep;
        int mindist = 10000;
        unordered_map<mpos, int> m;
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(tp, i);
            if (d < mindist) {
                mindist = d;
                ep = i;
            }
            ///
            m.emplace(i, 0);
        }
        
        for (auto &i : this->mstree) {
            m[i.first] += 1;
            m[i.second] += 1;
        }
        
        
        while(this->lu.size() < this->mstree.size()) {
            
            for (auto &i : this->mstree) {
                const mpos a = i.first;
                const mpos b = i.second;
                if (m[a] == 1 && m[b] > 0 && !(a == ep)) {
                    this->lu.emplace_back(a, b);
                    m[a] -= 1;
                    m[b] -= 1;
                } else if (m[b] == 1 && m[a] > 0 && !(b == ep)) {
                    this->lu.emplace_back(b, a);
                    m[a] -= 1;
                    m[b] -= 1;
                }
            }
        }
        
    }
    
    void collection_root_ld () {
        mpos tp(0, 1000);
        mpos ep;
        int mindist = 10000;
        unordered_map<mpos, int> m;
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(tp, i);
            if (d < mindist) {
                mindist = d;
                ep = i;
            }
            ///
            m.emplace(i, 0);
        }
        
        for (auto &i : this->mstree) {
            m[i.first] += 1;
            m[i.second] += 1;
        }
        
        
        while(this->ld.size() < this->mstree.size()) {
            
            for (auto &i : this->mstree) {
                const mpos a = i.first;
                const mpos b = i.second;
                if (m[a] == 1 && m[b] > 0 && !(a == ep)) {
                    this->ld.emplace_back(a, b);
                    m[a] -= 1;
                    m[b] -= 1;
                } else if (m[b] == 1 && m[a] > 0 && !(b == ep)) {
                    this->ld.emplace_back(b, a);
                    m[a] -= 1;
                    m[b] -= 1;
                }
            }
        }
        
    }
    
    void collection_root_rd () {
        mpos tp(1000, 1000);
        mpos ep;
        int mindist = 10000;
        unordered_map<mpos, int> m;
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(tp, i);
            if (d < mindist) {
                mindist = d;
                ep = i;
            }
            ///
            m.emplace(i, 0);
        }
        
        for (auto &i : this->mstree) {
            m[i.first] += 1;
            m[i.second] += 1;
        }
        
        
        while(this->rd.size() < this->mstree.size()) {
            
            for (auto &i : this->mstree) {
                const mpos a = i.first;
                const mpos b = i.second;
                if (m[a] == 1 && m[b] > 0 && !(a == ep)) {
                    this->rd.emplace_back(a, b);
                    m[a] -= 1;
                    m[b] -= 1;
                } else if (m[b] == 1 && m[a] > 0 && !(b == ep)) {
                    this->rd.emplace_back(b, a);
                    m[a] -= 1;
                    m[b] -= 1;
                }
            }
        }
        
    }
    
    void collection_root_ru () {
        mpos tp(1000, 0);
        mpos ep;
        int mindist = 10000;
        unordered_map<mpos, int> m;
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(tp, i);
            if (d < mindist) {
                mindist = d;
                ep = i;
            }
            ///
            m.emplace(i, 0);
        }
        
        for (auto &i : this->mstree) {
            m[i.first] += 1;
            m[i.second] += 1;
        }
        
        
        while(this->ru.size() < this->mstree.size()) {
            
            for (auto &i : this->mstree) {
                const mpos a = i.first;
                const mpos b = i.second;
                if (m[a] == 1 && m[b] > 0 && !(a == ep)) {
                    this->ru.emplace_back(a, b);
                    m[a] -= 1;
                    m[b] -= 1;
                } else if (m[b] == 1 && m[a] > 0 && !(b == ep)) {
                    this->ru.emplace_back(b, a);
                    m[a] -= 1;
                    m[b] -= 1;
                }
            }
        }
        
    }
    
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
    int ignorecnt = 0;
    void move_items (int a, int b) {
        vector<int> needitems(100, 0);
        vector<int> area_item_index;
        for (int i = 0; i < this->titems.size(); ++i) {
            const int x = this->titems[i].x;
            const int y = this->titems[i].y;
            if (this->pos_to_area(x, y) == a) {
                area_item_index.emplace_back(i);
            }
        }
        for (int i = 0; i < this->customerItem.size(); ++i) {
            const int x = this->customerX[i];
            const int y = this->customerY[i];
            if (this->pos_to_area(x, y) == a) {
                needitems[this->customerItem[i]] += 1;
            }
        }
        
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
            } else {
                needitems[n] -= 1;
            }
        }
        int bx, by;
        this->area_pos(b, bx, by);
        
        int ax, ay;
        this->area_pos(a, ax, ay);
        vector<int> notneed_item_indexs;
        for (auto &i : trucks) {
            if (i.second.size() <= this->ignorecnt) { continue; }
            for (int j = 0; j < i.second.size(); ++j) {
                notneed_item_indexs.emplace_back(i.second[j]);
            }
            
            this->go_truck_to_xy(i.second, ax, ay);
        }
        
        
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
    
    int w = 1;
    int h = 1;
    int dx = 0;
    int dy = 0;
    int mdx = 0;
    int mdy = 0;
    
    void init_area_setting (int w, int h, int mx, int my) {
        this->w = max(w, 1);
        this->h = max(h, 1);
        this->dx = 1000 / this->w;
        this->dy = 1000 / this->h;
        this->mdx = min(max(this->dx / 2 + mx, 0), 999);
        this->mdy = min(max(this->dy / 2 + my, 0), 999);
        this->tcost = 0;
        this->tretmessage = vector<string>();
        this->titems = this->items;
        this->tbestscore = 100000000;
    }
    
    
    inline int pos_to_area (const int x, const int y) {
        const int px = min(x / this->dx, this->w - 1);
        const int py = min(y / this->dy, this->h - 1);
        return py * this->w + px;
    }
    
    
    inline void area_pos (const int n, int &px, int &py) {
        const int x = n % this->w;
        const int y = n / this->w;
        px = this->mdx + this->dx * x;
        py = this->mdy + this->dy * y;
    }
    
    void move_truck_items_lu () {
        vector<int> p;
        for (int i = 0; i < this->h; ++i) {
            for (int j = 0; j < this->w; ++j) {
                if (i % 2 == 0) {
                    p.emplace_back(j + this->w * i);
                } else {
                    p.emplace_back(this->w * i + this->w - j - 1);
                }
            }
        }
        
        reverse(p.begin(), p.end());
        for (auto &i : this->lu) {
            vector<int> v;
            for (int j = 0; j < this->titems.size(); ++j) {
                const int x = this->titems[j].x;
                const int y = this->titems[j].y;
                if (i.first == mpos(x, y)) { v.emplace_back(j); }
            }
            this->go_truck_to_xy(v, i.second.x, i.second.y);
        }
        {
            vector<int> v;
            for (int j = 0; j < this->titems.size(); ++j) {
                const int x = this->titems[j].x;
                const int y = this->titems[j].y;
                if (this->lu[this->lu.size()-1].second == mpos(x, y)) { v.emplace_back(j); }
            }
            int gx, gy;
            this->area_pos(p[p.size()-1], gx, gy);
            this->go_truck_to_xy(v, gx, gy);
        }
        
        reverse(p.begin(), p.end());
        for (int i = 0; i < p.size()-1; ++i) { this->move_items(p[i], p[i+1]); }
    }
    
    void move_truck_items_ru () {
        vector<int> p;
        for (int i = 0; i < this->h; ++i) {
            for (int j = 0; j < this->w; ++j) {
                if (i % 2 == 1) {
                    p.emplace_back(j + this->w * i);
                } else {
                    p.emplace_back(this->w * i + this->w - j - 1);
                }
            }
        }
        
        reverse(p.begin(), p.end());
        for (auto &i : this->ru) {
            vector<int> v;
            for (int j = 0; j < this->titems.size(); ++j) {
                const int x = this->titems[j].x;
                const int y = this->titems[j].y;
                if (i.first == mpos(x, y)) { v.emplace_back(j); }
            }
            this->go_truck_to_xy(v, i.second.x, i.second.y);
        }
        {
            vector<int> v;
            for (int j = 0; j < this->titems.size(); ++j) {
                const int x = this->titems[j].x;
                const int y = this->titems[j].y;
                if (this->ru[this->ru.size()-1].second == mpos(x, y)) { v.emplace_back(j); }
            }
            int gx, gy;
            this->area_pos(p[p.size()-1], gx, gy);
            this->go_truck_to_xy(v, gx, gy);
        }
        
        reverse(p.begin(), p.end());
        for (int i = 0; i < p.size()-1; ++i) { this->move_items(p[i], p[i+1]); }
    }
    
    void move_truck_items_r () {
        vector<int> p;
        for (int i = 0; i < this->h; ++i) {
            for (int j = 0; j < this->w; ++j) {
                if (i % 2 == 0) {
                    p.emplace_back(j + this->w * i);
                } else {
                    p.emplace_back(this->w * i + this->w - j - 1);
                }
            }
        }
        if (this->h % 2 == 0) {
            for (auto &i : this->ld) {
                vector<int> v;
                for (int j = 0; j < this->titems.size(); ++j) {
                    const int x = this->titems[j].x;
                    const int y = this->titems[j].y;
                    if (i.first == mpos(x, y)) { v.emplace_back(j); }
                }
                this->go_truck_to_xy(v, i.second.x, i.second.y);
            }
            {
                vector<int> v;
                for (int j = 0; j < this->titems.size(); ++j) {
                    const int x = this->titems[j].x;
                    const int y = this->titems[j].y;
                    if (this->ld[this->ld.size()-1].second == mpos(x, y)) { v.emplace_back(j); }
                }
                int gx, gy;
                this->area_pos(p[p.size()-1], gx, gy);
                this->go_truck_to_xy(v, gx, gy);
            }
        } else {
            for (auto &i : this->rd) {
                vector<int> v;
                for (int j = 0; j < this->titems.size(); ++j) {
                    const int x = this->titems[j].x;
                    const int y = this->titems[j].y;
                    if (i.first == mpos(x, y)) { v.emplace_back(j); }
                }
                this->go_truck_to_xy(v, i.second.x, i.second.y);
            }
            {
                vector<int> v;
                for (int j = 0; j < this->titems.size(); ++j) {
                    const int x = this->titems[j].x;
                    const int y = this->titems[j].y;
                    if (this->rd[this->rd.size()-1].second == mpos(x, y)) { v.emplace_back(j); }
                }
                int gx, gy;
                this->area_pos(p[p.size()-1], gx, gy);
                this->go_truck_to_xy(v, gx, gy);
            }
        }
        
        reverse(p.begin(), p.end());
        
        for (int i = 0; i < p.size()-1; ++i) { this->move_items(p[i], p[i+1]); }
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
            this->warehouses.emplace(warehouseX[i], warehouseY[i]);
            for (int j = 0; j < warehouseQuantity[i]; ++j) {
                this->items.emplace_back(warehouseItem[i], warehouseX[i], warehouseY[i]);
            }
        }
        this->warehouse_minimum_steiner_tree();
        this->collection_root_lu();
        this->collection_root_ld();
        this->collection_root_rd();
        this->collection_root_ru();
        // ofstream outputfile("warehouse_minimum_steiner_tree.txt");
        // for (auto &i : this->mstree) {
        //     outputfile<< print("E", i.first.x, i.first.y, i.second.x, i.second.y) << endl;
        // }
        // outputfile.close();
        
        ///////////////////////////////////
        
        int dlu = 10000;
        int dru = 10000;
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(mpos(0, 0), i);
            if (d < dlu) { dlu = d; }
        }
        for (auto &i : this->warehouses) {
            int d =  this->manhattan_distance(mpos(1000, 0), i);
            if (d < dru) { dru = d; }
        }
        
        
        int dscore = this->best_delivery();
        int besttscore = 100000000;
        vector<EItem> besttitems;
        vector<string> besttretmessage;
        int bestcost = 0;
        int bestw=1;
        int besth=1;
        bool ud =false;
        for (int h = 1; h < 7; ++h) {
            if (sw.get_milli_time() > 6000) { break; }
            for (int w = 1; w < 40; ++w) {
                this->init_area_setting(w, h, 0, 0);
                if (dlu < dru) {
                    this->move_truck_items_lu();
                } else {
                    this->move_truck_items_ru();
                }
                this->best_tdelivery();
                int tscore = this->tbestscore + this->tcost;
                if (tscore < besttscore) {
                    besttscore = tscore;
                    besttitems = this->titems;
                    besttretmessage = this->tretmessage;
                    bestcost = this->tcost;
                    bestw=w;
                    besth=h;
                }
            }
        }
        
        int tw = bestw;
        int th = besth;
        for (int h = max(th-2, 1); h < min(th+2, 7); ++h) {
            if (sw.get_milli_time() > 6000) { break; }
            for (int w = max(tw-2, 1); w < min(tw+2, 40); ++w) {
                this->init_area_setting(w, h, 0, 0);
                this->move_truck_items_r();
                this->best_tdelivery();
                int tscore = this->tbestscore + this->tcost;
                if (tscore < besttscore) {
                    besttscore = tscore;
                    besttitems = this->titems;
                    besttretmessage = this->tretmessage;
                    bestcost = this->tcost;
                    bestw=w;
                    besth=h;
                    ud = true;
                }
            }
        }
        
        for (int i = -16; i <= 16; i+=2) {
            if (sw.get_milli_time() > 6000) { break; }
            for (int j = -16; j <= 16; j+=2) {
                this->init_area_setting(bestw, besth, i, j);
                if (ud) {
                    this->move_truck_items_r();
                } else {
                    if (dlu < dru) {
                        this->move_truck_items_lu();
                    } else {
                        this->move_truck_items_ru();
                    }
                    
                }
                
                this->best_tdelivery();
                int tscore = this->tbestscore + this->tcost;
                if (tscore < besttscore) {
                    besttscore = tscore;
                    besttitems = this->titems;
                    besttretmessage = this->tretmessage;
                    bestcost = this->tcost;
                }
            }
        }
        
        this->titems = besttitems;
        this->tretmessage = besttretmessage;
        
        if (besttscore < dscore) {
            for (int i = 0; i < 200000; ++i) {
                if (i % 200 == 0 && sw.get_milli_time() > 8800) { break; }
                this->best_tdelivery();
                if (i % 50 == 0) { this->best_delivery(); }
            }
            this->best_go_tdelivery();
            int rscore = this->tbestscore + bestcost;
            dscore = this->best_go_delivery();
            
            if (rscore < dscore) {
                return this->tretmessage;
            } else {
                return this->retmessage;
            }
            
        } else {
            for (int i = 0; i < 200000; ++i) {
                if (i % 200 == 0 && sw.get_milli_time() > 8800) { break; }
                this->best_delivery();
            }
            this->best_go_delivery();
            return this->retmessage;
        }
    }
};



//////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>



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
    
    if (false) {
        ofstream outputfile("visout.txt");
        outputfile<< ret.size() << endl;
        for (auto &i : ret) {
            outputfile<< i << endl;
        }
        outputfile.close();
    }
    
    
    
    cout << ret.size() << endl;
    for (auto &i : ret) { cout << i << endl; }
    cout.flush();
}

