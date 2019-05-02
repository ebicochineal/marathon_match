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


class polyomino {
public:
    int h, w;
    vector< pair<e512pos, int> > pi;
    int ups[4];
    int downs[4];
    
    polyomino () {}
    polyomino (vector<int> a, vector<int> b, int h, int w) {
        this->h = h;
        this->w = w;
        for (int i = 0; i < a.size(); ++i) {
            int x = i % w;
            int y = i / w;
            if (a[x + y * w] == 1) { this->pi.emplace_back(e512pos(x, h-y-1), b[x + y * w]); }
        }
        
        for (int i = 0; i < w; ++i) {
            int up = 0;
            int down = 0;
            
            for (int j = 0; j < h; ++j) {
                int p = i + j*w;
                if (a[p] == 1 && h - j > up) { up = h - j - 1; }
                if (a[p] == 1) { down = -(h - j - 1); }
            }
            this->ups[i] = up;
            this->downs[i] = down;
        }
    }
    void init (vector<int> a, vector<int> b, int h, int w) {
        this->h = h;
        this->w = w;
        for (int i = 0; i < a.size(); ++i) {
            int x = i % w;
            int y = i / w;
            if (a[x + y * w] == 1) { this->pi.emplace_back(e512pos(x, h-y-1), b[x + y * w]); }
        }
        
        for (int i = 0; i < w; ++i) {
            int up = 0;
            int down = 0;
            
            for (int j = 0; j < h; ++j) {
                int p = i + j*w;
                if (a[p] == 1 && h - j > up) { up = h - j - 1; }
                if (a[p] == 1) { down = -(h - j - 1); }
            }
            this->ups[i] = up;
            this->downs[i] = down;
        }
    }
    
    
};

class ImageFromBlocks {
public:
    int bh, bw, x;
    int imageHeight, imageWidth, blockSize, maxDiscard, discard;
    vector<int> image;
    vector<int> rimage;
    vector< vector<polyomino> > polyominos = vector< vector<polyomino> >(10, vector<polyomino>(4));
    
    int bsbs;
    float bsbs765;
    
    StopWatch sw;
    
    float score = 0;
    vector<int> heightboard;
    
    string init(int imageHeight, int blockSize, int maxDiscard, vector<int> image) {
        this->sw = StopWatch();
        this->x = 0;
        this->bw = image.size() / imageHeight / blockSize;
        this->bh = imageHeight / blockSize;
        this->imageHeight = imageHeight;
        this->imageWidth = image.size() / imageHeight;
        this->blockSize = blockSize;
        this->bsbs = this->blockSize * this->blockSize;
        this->bsbs765 = 765.0 * this->bsbs;
        
        this->discard = maxDiscard;
        this->maxDiscard = maxDiscard;
        this->image = image;
        for (int y = this->imageHeight - 1; y >= 0; --y) {
            for (int x = 0; x < this->imageWidth; ++x) {
                int p = x + y * this->imageWidth;
                this->rimage.emplace_back(this->image[p]);
            }
        }
        
        for (int i = 0; i < this->bw; ++i) { this->heightboard.emplace_back(0); }
        
        
        this->polyominos[0][0].init({1, 1}, {0, 1}, 1, 2);
        this->polyominos[0][1].init({1, 1}, {0, 1}, 2, 1);
        this->polyominos[0][2].init({1, 1}, {1, 0}, 1, 2);
        this->polyominos[0][3].init({1, 1}, {1, 0}, 2, 1);
        this->polyominos[1][0].init({1, 1, 1}, {0, 1, 2}, 1, 3);
        this->polyominos[1][1].init({1, 1, 1}, {0, 1, 2}, 3, 1);
        this->polyominos[1][2].init({1, 1, 1}, {2, 1, 0}, 1, 3);
        this->polyominos[1][3].init({1, 1, 1}, {2, 1, 0}, 3, 1);
        this->polyominos[2][0].init({1, 0, 1, 1}, {0, 1, 2, 3}, 2, 2);
        this->polyominos[2][1].init({1, 1, 1, 0}, {2, 0, 3, 1}, 2, 2);
        this->polyominos[2][2].init({1, 1, 0, 1}, {3, 2, 1, 0}, 2, 2);
        this->polyominos[2][3].init({0, 1, 1, 1}, {1, 3, 0, 2}, 2, 2);
        this->polyominos[3][0].init({1, 1, 1, 1}, {0, 1, 2, 3}, 1, 4);
        this->polyominos[3][1].init({1, 1, 1, 1}, {0, 1, 2, 3}, 4, 1);
        this->polyominos[3][2].init({1, 1, 1, 1}, {3, 2, 1, 0}, 1, 4);
        this->polyominos[3][3].init({1, 1, 1, 1}, {3, 2, 1, 0}, 4, 1);
        this->polyominos[4][0].init({1, 1, 1, 1}, {0, 1, 2, 3}, 2, 2);
        this->polyominos[4][1].init({1, 1, 1, 1}, {2, 0, 3, 1}, 2, 2);
        this->polyominos[4][2].init({1, 1, 1, 1}, {3, 2, 1, 0}, 2, 2);
        this->polyominos[4][3].init({1, 1, 1, 1}, {1, 3, 0, 2}, 2, 2);
        this->polyominos[5][0].init({0, 1, 0, 1, 1, 1}, {0, 1, 2, 3, 4, 5}, 2, 3);
        this->polyominos[5][1].init({1, 0, 1, 1, 1, 0}, {3, 0, 4, 1, 5, 2}, 3, 2);
        this->polyominos[5][2].init({1, 1, 1, 0, 1, 0}, {5, 4, 3, 2, 1, 0}, 2, 3);
        this->polyominos[5][3].init({0, 1, 1, 1, 0, 1}, {2, 5, 1, 4, 0, 3}, 3, 2);
        this->polyominos[6][0].init({1, 1, 0, 0, 1, 1}, {0, 1, 2, 3, 4, 5}, 2, 3);
        this->polyominos[6][1].init({0, 1, 1, 1, 1, 0}, {3, 0, 4, 1, 5, 2}, 3, 2);
        this->polyominos[6][2].init({1, 1, 0, 0, 1, 1}, {5, 4, 3, 2, 1, 0}, 2, 3);
        this->polyominos[6][3].init({0, 1, 1, 1, 1, 0}, {2, 5, 1, 4, 0, 3}, 3, 2);
        this->polyominos[7][0].init({0, 1, 1, 1, 1, 0}, {0, 1, 2, 3, 4, 5}, 2, 3);
        this->polyominos[7][1].init({1, 0, 1, 1, 0, 1}, {3, 0, 4, 1, 5, 2}, 3, 2);
        this->polyominos[7][2].init({0, 1, 1, 1, 1, 0}, {5, 4, 3, 2, 1, 0}, 2, 3);
        this->polyominos[7][3].init({1, 0, 1, 1, 0, 1}, {2, 5, 1, 4, 0, 3}, 3, 2);
        this->polyominos[8][0].init({1, 0, 0, 1, 1, 1}, {0, 1, 2, 3, 4, 5}, 2, 3);
        this->polyominos[8][1].init({1, 1, 1, 0, 1, 0}, {3, 0, 4, 1, 5, 2}, 3, 2);
        this->polyominos[8][2].init({1, 1, 1, 0, 0, 1}, {5, 4, 3, 2, 1, 0}, 2, 3);
        this->polyominos[8][3].init({0, 1, 0, 1, 1, 1}, {2, 5, 1, 4, 0, 3}, 3, 2);
        this->polyominos[9][0].init({0, 0, 1, 1, 1, 1}, {0, 1, 2, 3, 4, 5}, 2, 3);
        this->polyominos[9][1].init({1, 0, 1, 0, 1, 1}, {3, 0, 4, 1, 5, 2}, 3, 2);
        this->polyominos[9][2].init({1, 1, 1, 1, 0, 0}, {5, 4, 3, 2, 1, 0}, 2, 3);
        this->polyominos[9][3].init({1, 1, 0, 1, 0, 1}, {2, 5, 1, 4, 0, 3}, 3, 2);
        
        pdebug(this->blockSize, this->maxDiscard);
        
        
        return "";
    }
    
    string placePiece(int pieceHeight, vector<int> piece, int timeLeft) {
        int pieceWidth = piece.size() / pieceHeight; 
        // if (this->x + pieceWidth > this->bw) { this->x = 0; }
        // string ret = to_string(0) + " " + to_string(this->x);
        
        int pmindex = this->find_polypmino_index(pieceHeight, pieceWidth, piece);
        
        this->x += pieceWidth;
        // if (this->score > 0) { pdebug(this->score); return "0 -1"; }
        float bestscore = -100;
        int bestrot = 0;
        int bestx = 0;
        for (int r = 0; r < 4; ++r) {
            for (int x = 0; x < this->bw; ++x) {
                float tscore = this->put_test_score(pmindex, r, x, piece);
                if (tscore > bestscore) {
                    bestscore = tscore;
                    bestx = x;
                    bestrot = r;
                }
            }
        }
        string ret = "D";
        
        float xx = this->polyominos[pmindex][0].pi.size() * 0.5;
        
        float dis = xx;
        if (this->discard < 1000) { dis = xx * 0.9; }
        if (this->discard < 500) { dis = xx * 0.8; }
        if (this->discard < 250) { dis = xx * 0.7; }
        if (this->discard < 125) { dis = xx * 0.5; }
        if (this->discard < 64 ) { dis = xx * 0.25; }
        if (this->discard < 32 ) { dis = xx * 0.1; }
        dis = xx * ((float)this->discard / (float)this->maxDiscard);
        
        if (bestscore > dis || this->discard <= 0 || timeLeft < 500) {
            if(!this->put(pmindex, bestrot, bestx, piece)){ pdebug(this->score, this->sw.get_milli_time(), timeLeft); };
            ret = to_string(bestrot) + " " + to_string(bestx);
        } else  {
            this->discard -= 1;
        }
        
        return ret;
    }
    
    int find_polypmino_index (int pieceHeight, int pieceWidth, vector<int>& piece) {
        if (piece.size() == 2) { return 0; }
        if (piece.size() == 3) { return 1; }
        if (piece.size() == 4) {
            if (piece[1] < 0) { return 2; }
            if (pieceWidth == 4) { return 3; }
            return 4;
        }
        if (piece.size() == 6) {
            if (piece[0] < 0 && piece[2] < 0) { return 5; }
            if (piece[2] < 0 && piece[3] < 0) { return 6; }
            if (piece[0] < 0 && piece[5] < 0) { return 7; }
            if (piece[1] < 0 && piece[2] < 0) { return 8; }
            return 9;
        }
        return 0;
    }
    
    bool put (int index, int rot, int sx, vector<int>& piece) {
        const polyomino& mino = this->polyominos[index][rot];
        int mdown = 10000;
        for (int i = 0; i < mino.w; ++i) {
            const int col = this->bh - this->heightboard[sx+i] - mino.downs[i];
            if (col < mdown) { mdown = col; }
        }
        int p = bh - mdown;
        
        if (p + mino.h > this->bh) { return false; }
        
        for (auto&& i : mino.pi) {
            this->score += this->calc_block_score(piece[i.second], sx+i.first.x, p+i.first.y);
        }
        for (int i = 0; i < mino.w; ++i) {
            this->heightboard[sx+i] = mino.ups[i] + p + 1;
        }
        return true;
    }
    
    float put_test_score (int index, int rot, int sx, vector<int>& piece) {
        const polyomino& mino = this->polyominos[index][rot];
        int mdown = 10000;
        float r = 0;
        if (mino.w + sx > this->bw) { return -100; }
        for (int i = 0; i < mino.w; ++i) {
            const int col = this->bh - this->heightboard[sx+i] - mino.downs[i];
            if (col < mdown) { mdown = col; }
        }
        int p = bh - mdown;
        if (p + mino.h > this->bh) { return -100; }
        
        for (auto&& i : mino.pi) {
            r += this->calc_block_score(piece[i.second], sx+i.first.x, p+i.first.y);
        }
        
        for (int i = 0; i < mino.w; ++i) {
            r -= ((p - mino.downs[i]) - this->heightboard[sx+i]) * 20.0;
        }
        int minh = 10000;
        for (int i = 0; i < this->heightboard.size(); ++i) {
            if (this->heightboard[i] < minh) { minh = this->heightboard[i]; }
        }
        
        for (int i = 0; i < mino.w; ++i) {
            r -= ((p - mino.downs[i]) - minh) * 0.05;
        }
        
        return r;
    }
    
    inline void color_decode (int& t, int& r, int& g, int& b) {
        r = (t >> 16) & 0xFF; g = (t >> 8) & 0xFF; b = t & 0xFF;
    }
    
    inline float calc_block_score (int& color, int x, int y) {
        const int p = x + y * this->bw;
        float err = 0;
        int r, g, b;
        this->color_decode(color, r, g, b);
        for (int dy = 0; dy < this->blockSize; ++dy) {
            const int ipy = (dy + this->blockSize * y) * this->imageWidth;
            for (int dx = 0; dx < this->blockSize; ++dx) {
                const int px = dx + this->blockSize * x;
                const int imp = px + ipy;
                int tr, tg, tb;
                this->color_decode(this->rimage[imp], tr, tg, tb);
                err += (abs(tr-r) + abs(tg-g) + abs(tb-b));
            }
        }
        err = 1.0 - err / this->bsbs765;
        return err * err;
    }
    
};



// -------8<------- end of the solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < (int)v.size(); ++i)
        cin >> v[i];
}

int main() {
    ImageFromBlocks sol;
    int imageHeight;
    cin >> imageHeight;
    int blockSize;
    cin >> blockSize;
    int maxDiscard;
    cin >> maxDiscard;
    int imageLength;
    cin >> imageLength;
    vector<int> image(imageLength);
    getVector(image);
    
    string ret = sol.init(imageHeight, blockSize, maxDiscard, image);
    cout << ret << endl;
    cout.flush();

    while (true) {
        int pieceHeight;
        cin >> pieceHeight;
        int pieceLength;
        cin >> pieceLength;
        vector<int> piece(pieceLength);
        getVector(piece);
        int timeLeft;
        cin >> timeLeft;
        ret = sol.placePiece(pieceHeight, piece, timeLeft);
        cout << ret << endl;
        cout.flush();
    }
}

