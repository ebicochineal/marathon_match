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
#include <time.h>
#include <sys/timeb.h>

using namespace std;

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

template<class T>
void pdebug (T s) {
    stringstream ss;
    ss << "<cerr>" << print(s) << "</cerr>";
    cerr << ss.str();
}

inline uint32_t xrnd() {
    static uint32_t y = 2463534242;
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    return y = y ^ (y << 5);
}

class E512Font {
public:
    int w, h;
    vector<int> mask;
    vector<mpos> pos;
    E512Font (int w, int h, vector<int> mask) {
        this->w = w; this->h = h;
        this->mask = mask;
        
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if ((this->mask[y] >> x) & 1) {
                    this->pos.emplace_back(x, y);
                }
            }
        }
    }
    
};

class E512Fonts {
public:
    vector<E512Font> fonts;
    vector<int> chars;
    int id;
    int size;
    int len;
    bool completed = false;
    E512Fonts (string s, int id, int size) {
        this->len = s.size();
        this->id = id; this->size = size;
        for (auto &i : s) { this->chars.emplace_back(i); }
    }
    
    void nextInputFont (int w, int h, vector<int> mask) {
        this->fonts.emplace_back(w, h, mask);
        if (this->len == this->fonts.size()) { this->completed = true; }
    }
    
    vector<int> nextGetFont () {
        return vector<int>{this->chars[this->fonts.size()] , this->id, this->size};
    }
    
};



class TypesetterArt {
private:
    int nRenders;
    int nFonts;
    int precision;
    int width;
    int height;
    vector<int> original;

    int letterW;
    int letterH;
    
    int fontId = 0;
    int letterId = 31;
    int fontSize = 8;
    
    vector< vector< vector<int> > > kyxoriginal;
    vector< vector< vector<int> > > kyxtmp;
    
    
    vector<E512Fonts> fonts;
    
    StopWatch sw;
    
    

public:
    int init(int nRenders, int nFonts, int precision, int width, int height, vector<int> image) {
        this->nRenders = nRenders;
        this->nFonts = nFonts;
        this->precision = precision;
        this->width = width;
        this->height = height;
        this->original = image;
        
        // You can convert the image argument to 3D array as follows:
        this->kyxoriginal = vector< vector< vector<int> > >(4, vector< vector<int> >(height, vector<int>(width, 0)));
        this->kyxtmp = vector< vector< vector<int> > >(4, vector< vector<int> >(height, vector<int>(width, 0)));
        int index = 0;
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    this->kyxoriginal[k][i][j] = image[index++];
                }
            }
        }
        
        
        for (int i = 0; i < nFonts; ++i) {
            if (precision == 1) {
                this->fonts.emplace_back(" l|8T", i, 8);
                this->fonts.emplace_back(" l|8T", i, 9);
                this->fonts.emplace_back(" l|8T", i, 10);
                this->fonts.emplace_back(" l|8T", i, 8);
            } else {
                this->fonts.emplace_back(" l|.8T-[]:'", i, 8);
                this->fonts.emplace_back(" l|.8T-[]:'", i, 9);
                this->fonts.emplace_back(" l|.8T-[]:'", i, 10);
                this->fonts.emplace_back(" l|.8T-[]:'", i, 8);
            }
        }
        
        
        pdebug(print(width, height, precision, nFonts, nRenders));
        // pdebug(this->sw.get_milli_time());
        return 0;
    }
    
    
    bool completed = false;
    void nextInput (int width, int height, vector<int> bitmask, int remainingMillis) {
        if (width == 0 && height == 0) { return; }
        
        for (auto &i : this->fonts) {
            if (i.completed) { continue; }
            i.nextInputFont(width, height, bitmask);
            break;
        }
        
        bool pcomp = true;
        for (auto &i : this->fonts) {
            if (i.completed) { continue; }
            pcomp = false;
        }
        
        this->completed = pcomp;
    }
    
    vector<int> nextGlyphFont () {
        for (auto &i : this->fonts) {
            if (i.completed) { continue; }
            return i.nextGetFont();
        }
        
        return vector<int>();
    }
    
    
    inline double diffScore (const E512Font &f, int x, int y, int k, int z) {
        unordered_map<mpos, int> um;
        if ( ! (y < 0 || x < 0 || y >= this->height || x >= this->width) ) {
            if (y+f.h >= this->height || x+f.w >= this->width) {
                for (auto &i : f.pos) {
                    const int px = x + i.x;
                    const int py = y + i.y;
                    if (py >= this->height || px >= this->width) { continue; }
                    const mpos p(px/this->precision, py/this->precision);
                    const int tmp = min(this->kyxtmp[k][py][px] + z, 255) - this->kyxtmp[k][py][px];
                    if (um.find(p) != um.end()) {
                        um[p] += tmp;
                    } else {
                        um.emplace(p, tmp);
                    }
                }
            } else {
                for (auto &i : f.pos) {
                    const int px = x + i.x;
                    const int py = y + i.y;
                    const mpos p(px/this->precision, py/this->precision);
                    const int tmp = min(this->kyxtmp[k][py][px] + z, 255) - this->kyxtmp[k][py][px];
                    if (um.find(p) != um.end()) {
                        um[p] += tmp;
                    } else {
                        um.emplace(p, tmp);
                    }
                }
            }
        }
        
        double ares = 0;
        double res = 0;
        int div = 0;
        for (auto &i : um) {
            double originalSum = 0;
            double actualSum = 0;
            double dSum = 0;
            int n = 0;
            const int ix = i.first.x * this->precision;
            const int iy = i.first.y * this->precision;
            for (int top = 0; top < this->precision && top + iy < this->height; top++) {
                for (int left = 0; left < this->precision && left + ix < this->width; left++) {
                    originalSum += this->kyxoriginal[k][iy + top][ix + left];
                    actualSum += this->kyxtmp[k][iy + top][ix + left];
                    n++;
                }
            }
            if (n != 0) {
                dSum = actualSum + i.second;
                originalSum /= n * 255;
                actualSum /= n * 255;
                dSum /= n * 255;
                // double tmp = dSum - originalSum;
                // res += pow(1.0 - abs(actualSum - originalSum), 2);
                // ares += pow(1.0 - abs(tmp > 0 ? tmp + this->precision * 0.006 : tmp), 2);
                res += pow(1.0 - abs(actualSum - originalSum), 2);
                ares += pow(1.0 - abs(dSum - originalSum), 2);
                div++;
            }
        }
        return ares / max(div, 1) - res / max(div, 1);
    }
    
    inline double diffScore2 (const E512Font &f, int x, int y, int k, int z) {
        unordered_map<mpos, int> um;
        if ( ! (y < 0 || x < 0 || y >= this->height || x >= this->width) ) {
            if (y+f.h >= this->height || x+f.w >= this->width) {
                for (auto &i : f.pos) {
                    const int px = x + i.x;
                    const int py = y + i.y;
                    if (py >= this->height || px >= this->width) { continue; }
                    const mpos p(px/this->precision, py/this->precision);
                    const int tmp = min(this->kyxtmp[k][py][px] + z, 255) - this->kyxtmp[k][py][px];
                    if (um.find(p) != um.end()) {
                        um[p] += tmp;
                    } else {
                        um.emplace(p, tmp);
                    }
                }
            } else {
                for (auto &i : f.pos) {
                    const int px = x + i.x;
                    const int py = y + i.y;
                    const mpos p(px/this->precision, py/this->precision);
                    const int tmp = min(this->kyxtmp[k][py][px] + z, 255) - this->kyxtmp[k][py][px];
                    if (um.find(p) != um.end()) {
                        um[p] += tmp;
                    } else {
                        um.emplace(p, tmp);
                    }
                }
            }
        }
        
        double ares = 0;
        double res = 0;
        int div = 0;
        for (auto &i : um) {
            double originalSum = 0;
            double actualSum = 0;
            double dSum = 0;
            int n = 0;
            const int ix = i.first.x * this->precision;
            const int iy = i.first.y * this->precision;
            for (int top = 0; top < this->precision && top + iy < this->height; top++) {
                for (int left = 0; left < this->precision && left + ix < this->width; left++) {
                    originalSum += this->kyxoriginal[k][iy + top][ix + left];
                    actualSum += this->kyxtmp[k][iy + top][ix + left];
                    n++;
                }
            }
            if (n != 0) {
                dSum = actualSum + i.second;
                originalSum /= n * 255;
                actualSum /= n * 255;
                dSum /= n * 255;
                double tmp = dSum - originalSum;
                res += pow(1.0 - abs(actualSum - originalSum), 2);
                ares += pow(1.0 - abs(tmp > 0 ? tmp + this->precision * 0.006 : tmp), 2);
                // res += pow(1.0 - abs(actualSum - originalSum), 2);
                // ares += pow(1.0 - abs(dSum - originalSum), 2);
                div++;
            }
        }
        return ares / max(div, 1) - res / max(div, 1);
    }
    
    inline void drawFont (const E512Font &f, int x, int y, int k, int z) {
        if (y < 0 || x < 0 || y >= this->height || x >= this->width) { return; }
        // for (auto &i : f.pos) {
        //     const int px = x + i.x;
        //     const int py = y + i.y;
        //     if (py >= this->height || px >= this->width) { continue; }
        //     this->kyxtmp[k][py][px] = min(this->kyxtmp[k][py][px] + z, 255);
        // }
        if (y+f.h >= this->height || x+f.w >= this->width) {
            for (auto &i : f.pos) {
                const int px = x + i.x;
                const int py = y + i.y;
                if (py >= this->height || px >= this->width) { continue; }
                if (py >= this->height || px >= this->width) { continue; }
                this->kyxtmp[k][py][px] = min(this->kyxtmp[k][py][px] + z, 255);
            }
        } else {
            for (auto &i : f.pos) {
                const int px = x + i.x;
                const int py = y + i.y;
                if (py >= this->height || px >= this->width) { continue; }
                this->kyxtmp[k][py][px] = min(this->kyxtmp[k][py][px] + z, 255);
            }
        }
    }
    
    double allScore () {
        double res = 0;
        int div = 0;
        for (int i = 0; i < this->height; i += this->precision) {
            for (int j = 0; j < this->width; j += this->precision) {
                for (int k = 0; k < 4; k++) {
                    double originalSum = 0;
                    double actualSum = 0;
                    int n = 0;
                    for (int top = 0; top < this->precision && top + i < this->height; top++) {
                        for (int left = 0; left < this->precision && left + j < this->width; left++) {
                            originalSum += this->kyxoriginal[k][i + top][j + left];
                            actualSum += this->kyxtmp[k][i + top][j + left];
                            n++;
                        }
                    }
                    if (n != 0) {
                        originalSum /= n * 255;
                        actualSum /= n * 255;
                        res += pow(1.0 - abs(actualSum - originalSum), 2);
                        
                        div++;
                    }
                    
                }
            }
        }

        res /= div;
        
        return res * 1000000;
    }
    
    
    vector<int> nextGlyph (int width, int height, vector<int> bitmask, int remainingMillis) {
        this->nextInput(width, height,  bitmask, remainingMillis);
        if (this->completed) {
            return vector<int> { };
        } else {
            return this->nextGlyphFont();
        }
    }
    
    vector< vector<int> > bestret;
    double bestscore = 0;
    vector<int> render (int iteration, int remainingMillis) {
        
        if (iteration == 0) { this->initrender(remainingMillis); }
        if (iteration == this->nRenders-1) { pdebug(this->sw.get_milli_time()); }
        
        return this->bestret[iteration];
    }
    
    void initrender (int limit) {
        this->sw = StopWatch();
        double score;
        vector< vector<int> > ret;
        int cnt = 0;
        for (int i = 0; i < 256; ++i) {
            if (this->sw.get_milli_time() > limit - 500) { break; }
            this->prerender(score, ret, i, limit);
            if (score > this->bestscore) {
                this->bestscore = score;
                this->bestret = ret;
            }
            cnt += 1;
        }
        pdebug(cnt);
    }
    
    void prerender (double &score, vector< vector<int> > &lret, int n, int limit) {
        lret = vector< vector<int> >();
        this->kyxtmp = vector< vector< vector<int> > >(4, vector< vector<int> >(height, vector<int>(width, 0)));
        int time = 0;
        
        int o = this->nRenders - this->nRenders % 4;
        for (int p = 0; p < this->nRenders; ++p) {
            time = this->sw.get_milli_time();
            if (time > limit - 500 && this->bestscore > 0) {
                score = 0;
                return;
            }
            int z = 255;
            if (this->precision == 1) { z = 60 + xrnd() % 160; }
            int k = (p+n) % 4;
            
            E512Fonts f = this->fonts[(min(n*4, this->nFonts)+p/4) % this->fonts.size()];
            vector<int> ret = vector<int> { f.id, f.size, k, z };
            int y = 0; int x = 0;
            while (y < this->height) {
                ////////
                if (limit - time < 1500 && y % 16 == 15) {
                    time = this->sw.get_milli_time();
                    if (time > limit - 500 && this->bestscore > 0) {
                        score = 0;
                        return;
                    }
                }
                ////////
                if (p > o) {
                    x = 0;
                    while (x < this->width) {
                        int bestindex = 0;
                        double bestscore = 0;
                        for (int i = 1; i < f.fonts.size(); ++i) {
                            const double score = this->diffScore(f.fonts[i], x, y, k, z);
                            if (score > bestscore) {
                                bestscore = score;
                                bestindex = i;
                            }
                        }
                        ret.emplace_back(f.chars[bestindex]);
                        this->drawFont(f.fonts[bestindex], x, y, k, z);
                        x += f.fonts[bestindex].w;
                        
                    }
                    ret.emplace_back('\n');
                    y += f.fonts[0].h;
                } else {
                    x = 0;
                    while (x < this->width) {
                        int bestindex = 0;
                        double bestscore = 0;
                        for (int i = 1; i < f.fonts.size(); ++i) {
                            const double score = this->diffScore2(f.fonts[i], x, y, k, z);
                            if (score > bestscore) {
                                bestscore = score;
                                bestindex = i;
                            }
                        }
                        ret.emplace_back(f.chars[bestindex]);
                        this->drawFont(f.fonts[bestindex], x, y, k, z);
                        x += f.fonts[bestindex].w;
                        
                    }
                    ret.emplace_back('\n');
                    y += f.fonts[0].h;
                }
            }
            lret.emplace_back(ret);
        }
        score = this->allScore();
        // pdebug(score);
    }
    
    
};



/////////////////////////////////////////////////////////////


// Do not submit the main.
int main() {
    TypesetterArt *sol = new TypesetterArt;
     
    int nRenders;
    int nFonts;
    int precision;
    int width;
    int height;
    
    cin >> nRenders >> nFonts >> precision >> width >> height;
    {    
        int n;
        
        cin >> n;
        vector<int> image(n);

        for (int i = 0; i < n; i++) {
            cin >> image[i];
        }

        cerr << "Calling init\n";

        int d = sol->init(nRenders, nFonts, precision, width, height, image);

        cerr << "Return from init: " << d;

        cout << d << "\n" << flush;
    }
    
    bool callNext = true;
    while (callNext) {
        int glyphWidth;
        int glyphHeight;
        int n;
        
        cin >> glyphWidth >> glyphHeight >> n;
        
        vector<int> bitmask(n);
        for (int i = 0; i < n; i++) {
            cin >> bitmask[i];
        }
        int remainingMillis;
        cin >> remainingMillis;
        
        cerr << "Calling next glyph\n";
        
        vector<int> ret = sol->nextGlyph(glyphWidth, glyphHeight, bitmask, remainingMillis);
        
        cerr << "Return from next glyph size: " << ret.size() << "\n";
        
        if (ret.size() == 0) {
            callNext = false;
            cout << "\n";
        }
        else {
            cout << ret[0] << " " << ret[1] << " " << ret[2] << "\n" << flush;
        }
    }
    
    for (int i = 0; i < nRenders; i++) {
        int remainingMillis;
        cin >> remainingMillis;
        
        cerr << "Calling render\n";
        
        vector<int> ret = sol->render(i, remainingMillis);
        
        cerr << "Return from render size: " << ret.size() << "\n";
        
        cout << ret.size() << "\n";
        for (int x : ret) {
            cout << x << "\n";
        }
        cout << flush;
    }
    
    delete sol;
    return 0;
}

