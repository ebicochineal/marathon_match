#include "E512W3D.hpp"
#include "E512W3DTileMap.hpp"
#include "E512W3DGUI.hpp"
#include "E512W3DVIS.hpp"

#include <sstream>

E512W3DWindow w;
Object3D camera;

struct Vis {
    int h=0, w=0;
    string s;
};
E512W3DGUISlider s;
Vis v;
void load () {
    s = E512W3DGUISlider(0, 0, 200);
    v = Vis();
    E512W3DVIS::read();
    stringstream ss = E512W3DVIS::toStringStream(E512W3DVIS::u8_in);
    ss >> v.h >> v.w;
    ss = E512W3DVIS::toStringStream(E512W3DVIS::u8_out);
    ss >> v.s;
    s.setMaxValue(v.s.size());
}

void setup () {
    M5.begin();
    M5.Lcd.setRotation(1);
    M5.Axp.ScreenBreath(9);
    M5.MPU6886.Init();
    
    e512w3d.width = 160*3;
    e512w3d.height = 80*3;
    w.width = e512w3d.width;
    w.height = e512w3d.height;
    w.setCamera(camera);
    w.ambient = 1;
    e512w3d.add(w);
    e512w3d.begin();
}

void loop () {
    if (e512w3d.isFixedTime()) {
        E512W3DInput::update();
        e512w3d.clear();
        w.begin();
        
        E512W3DVIS::update(w);
        E512W3DVIS::draw(w);
        
        if (E512W3DVIS::ischange) { load(); }
        
        if (v.h > 0) {
            if (E512W3DVIS::vcnt > 0) { w.println(""); }
            int sx = 200;
            int sy = w.text_sub_cursor_y;
            w.print("in:");
            for (int i = 0; i < min((int)E512W3DVIS::u8_in.size(), 64); ++i) { w.print(E512W3DVIS::u8_in[i]); }
            w.print("out:");
            for (int i = 0; i < min((int)E512W3DVIS::u8_out.size(), 64); ++i) {
                if (i == s.getValue()-1) { w.text_color = color565(255, 0, 0); }
                w.print(E512W3DVIS::u8_out[i]);
                w.text_color = color565(255, 255, 255);
            }
            
            // line
            for (int i = 0; i < v.h+1; ++i) { w.drawLine(sx+0, sy+i*16, sx+v.w*16, sy+i*16); }
            for (int i = 0; i < v.w+1; ++i) { w.drawLine(sx+i*16, sy+0, sx+i*16, sy+v.h*16); }
            
            // slider
            s.y = w.text_sub_cursor_y;
            s.guiUpdate(w);
            s.guiDraw(w);
            s.popupDraw(w);
            
            // move
            int px = 0, py = 0;
            for (int i = 0; i < s.getValue(); ++i) {
                if (v.s[i] == 'R') { px += 16; }
                if (v.s[i] == 'L') { px -= 16; }
                if (v.s[i] == 'D') { py += 16; }
                if (v.s[i] == 'U') { py -= 16; }
            }
            // ebi
            w.setTextCursor(sx+px-1, sy+py+5);
            w.print((uint8_t)5); w.print((uint8_t)1); w.print((uint8_t)2);
        }
        
        e512w3d.pushScreen();
    }
}
