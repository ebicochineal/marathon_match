#pragma once

#include "E512W3D.hpp"
#include "E512W3DGUI.hpp"

uint16_t tocolor01 (float v) {
    int r, g, b;
    if (v < 0.5) {
        float x = v * 2.0;
        r =  30.0 * (1.0 - x) + 144.0 * x;
        g = 144.0 * (1.0 - x) + 255.0 * x;
        b = 255.0 * (1.0 - x) +  30.0 * x;
    } else {
        float x = v * 2.0 - 1.0;
        r = 144.0 * (1.0 - x) + 255.0 * x;
        g = 255.0 * (1.0 - x) +  30.0 * x;
        b =  30.0 * (1.0 - x) + 144.0 * x;
    }
    return color565(r, g, b);
}

uint16_t tocolor015 (float v) {
    int r, g, b;
    v *= 1.5;
    if (v < 0.5) {
        float x = v * 2.0;
        r =  30.0 * (1.0 - x) + 144.0 * x;
        g = 144.0 * (1.0 - x) + 255.0 * x;
        b = 255.0 * (1.0 - x) +  30.0 * x;
    } else if (v < 1.0) {
        float x = v * 2.0 - 1.0;
        r = 144.0 * (1.0 - x) + 255.0 * x;
        g = 255.0 * (1.0 - x) +  30.0 * x;
        b =  30.0 * (1.0 - x) + 144.0 * x;
    } else {
        float x = v * 2.0 - 2.0;
        r = 255.0 * (1.0 - x) +  30.0 * x;
        g =  30.0 * (1.0 - x) + 144.0 * x;
        b = 144.0 * (1.0 - x) + 255.0 * x;
    }
    return color565(r, g, b);
}


#include <string>
#include <sstream>
#if !defined(__EMSCRIPTEN__)
#include <fstream>
#endif
using namespace std;


#if defined(__EMSCRIPTEN__)
EM_JS(void, readTextIn, (int n, char* text), {
    var l = Math.min(gem_load_in_text.length+1, 4194304);
    stringToUTF8(gem_load_in_text, text, l);
});
EM_JS(void, readTextOut, (int n, char* text), {
    var l = Math.min(gem_load_out_text.length+1, 4194304);
    stringToUTF8(gem_load_out_text, text, l);
});
EM_JS(void, readTextDebug, (int n, char* text), {});
EM_JS(bool, inputChange, (), {
    let t = gem_inchange || gem_outchange;
    gem_inchange = false;
    gem_outchange = false;
    return t;
});
#else
void readTextIn (int n, char* text) {
    const int maxsize = 4194304;
    string path = "./in/" + to_string(n) + ".txt";;
    ifstream ifs(path);
    int cnt = 0;
    char c;
    while (ifs.get(c) && cnt < maxsize) { if (c != '\r') { text[cnt]=c; cnt += 1; } }
    text[min(cnt, maxsize-1)] = '\0';
    ifs.close();
}
void readTextOut (int n, char* text) {
    const int maxsize = 4194304;
    string path = "./out/" + to_string(n) + ".txt";;
    ifstream ifs(path);
    int cnt = 0;
    char c;
    while (ifs.get(c) && cnt < maxsize) { if (c != '\r') { text[cnt]=c; cnt += 1; } }
    text[min(cnt, maxsize-1)] = '\0';
    ifs.close();
}
void readTextDebug (int n, char* text) {
    const int maxsize = 4194304;
    string path = "./debug/" + to_string(n) + ".txt";
    ifstream ifs(path);
    int cnt = 0;
    char c;
    while (ifs.get(c) && cnt < maxsize) { if (c != '\r') { text[cnt]=c; cnt += 1; } }
    text[min(cnt, maxsize-1)] = '\0';
    ifs.close();
}
#endif

class E512W3DVIS {
public:
    static int vcnt, seed, wcnt, tseed, sx;
        
    static bool ischange, isdrag;
    static E512Array<uint8_t> u8_in, u8_out, u8_debug;
    
    
    static void update (E512W3DWindow& w) {
#if defined(__EMSCRIPTEN__)
        if (inputChange()) { E512W3DVIS::ischange = true; }
        E512W3DVIS::vcnt = 0;
#else
        if (E512W3DVIS::vcnt > 0) { E512W3DVIS::vcnt -= 1; }
        if (E512W3DVIS::wcnt > 0) {
            E512W3DVIS::wcnt -= 1;
            if (E512W3DVIS::wcnt == 0) { E512W3DVIS::ischange = true; }
        }
        if (E512W3DVIS::isdrag || (w.getCursorX() >= 0 && w.getCursorX() < w.width && w.getCursorY() >= 0 && w.getCursorY() < 12)) {
            E512W3DVIS::vcnt = 30;
        }
        
        if ((w.getCursorX() >= 0 && w.getCursorX() < w.width && w.getCursorY() >= 0 && w.getCursorY() < 12) && E512W3DInput::getButtonDown(0)) {
            E512W3DVIS::sx = w.getCursorX();
            E512W3DVIS::tseed = E512W3DVIS::seed;
            E512W3DVIS::isdrag = true;
        }
        
        if (E512W3DVIS::isdrag) {
            int d = w.getCursorX() - E512W3DVIS::sx;
            int v = d / 4;
            E512W3DVIS::seed = max(E512W3DVIS::tseed+v, 0);
            E512W3DVIS::wcnt = 15;
        }
        
        if (E512W3DInput::getButtonUp(0)) { E512W3DVIS::isdrag = false; }
#endif
    }
    
    static void draw (E512W3DWindow& w) {
#if defined(__EMSCRIPTEN__)
#else
        if (E512W3DVIS::vcnt == 0) { return; }
        w.drawRect(0, 0, w.width, 12, color565(255*(E512W3DVIS::vcnt/30.0), 40, 40));
        E512W3DWindowTextCursor tc(w);
        w.text_cursor_x     = 0;
        w.text_cursor_y     = 0;
        w.text_sub_cursor_x = 0;
        w.text_sub_cursor_y = 0;
        w.text_bgcolor      = 0;
        w.text_color        = color565(255, 255, 255);
        w.text_size         = 1;
        w.text_use_bgcolor  = false;
        
        w.print((char)5);
        w.print((char)1);
        w.print((char)2);
        
        w.print(" seed = ");
        w.print(E512W3DVIS::seed);
        w.text_color        = color565(180, 180, 180);
        w.setTextCursor(6*16, 0);
        w.print("<drag>");
        tc.load(w);
#endif
    }
    
    static void read () {
        const int maxsize = 4194304;
        char* text = new char[maxsize];
        text[0] = '\0';
        readTextIn(E512W3DVIS::seed, text);
        E512W3DVIS::u8_in = E512W3DVIS::cpToU8(text);
        text[0] = '\0';
        readTextOut(E512W3DVIS::seed, text);
        E512W3DVIS::u8_out = E512W3DVIS::cpToU8(text);
        text[0] = '\0';
        readTextDebug(E512W3DVIS::seed, text);
        E512W3DVIS::u8_debug = E512W3DVIS::cpToU8(text);
        E512W3DVIS::ischange = false;
        delete[] text;
    }
    
    static E512Array<uint8_t> cpToU8 (char* cp) {
        const int maxsize = 4194304;
        E512Array<uint8_t> r;
        int cnt = 0;
        while (cp[cnt] != '\0' && cnt < maxsize) {
            r.emplace_back(cp[cnt]);
            cnt += 1;
        }
        return r;
    }
    static stringstream toStringStream (E512Array<uint8_t>& u8) {
        stringstream r;
        for (auto&& i : u8) { r << i; }
        return r;
    }
    static E512Array<string> toStringLines (E512Array<uint8_t>& u8) {
        E512Array<string> r;
        string t;
        for (auto&& i : u8) {
            if (i == '\n') {
                r.emplace_back(t);
                t.clear();
            } else {
                t += i;
            }
        }
        if (t.size() > 0) { r.emplace_back(t); }
        return r;
    }
    static E512Array<string> toStringSplit (E512Array<uint8_t>& u8) {
        E512Array<string> r;
        stringstream ss = E512W3DVIS::toStringStream(u8);
        string s;
        while (true) {
            ss >> s;
            if (ss.eof()) { break; }
            r.emplace_back(s);
        }
        return r;
    }
    static E512Array<uint8_t> stringToU8 (string& s) {
        E512Array<uint8_t> r;
        for (auto&& i : s) { r.emplace_back(i); }
        return r;
    }
};
bool E512W3DVIS::ischange = false;
bool E512W3DVIS::isdrag = false;
E512Array<uint8_t> E512W3DVIS::u8_in = E512Array<uint8_t>();
E512Array<uint8_t> E512W3DVIS::u8_out = E512Array<uint8_t>();
E512Array<uint8_t> E512W3DVIS::u8_debug = E512Array<uint8_t>();
int E512W3DVIS::vcnt = 30;
int E512W3DVIS::wcnt = 15;
int E512W3DVIS::seed = 0;
int E512W3DVIS::tseed = 0;
int E512W3DVIS::sx = 0;