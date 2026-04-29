#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <cstdint>
#include <fstream>
#include <iosfwd>
#include <ostream>
#include <vector>
#pragma pack(push, 1)
struct Color {
    uint8_t r, g, b;
    Color(uint32_t c):r(c>>16&0xFF),g(c>>8&0xFF),b(c&0xFF){}
};
#pragma pack(pop)
class Canvas {
private:
    int w,h;
    std::vector<Color> buffer;
public:
    Canvas(int w, int h):w(w),h(h),buffer(w*h,0){}
    void clear(Color c=0) {
        std::fill(buffer.begin(),buffer.end(),c);
    }
    void drawPixel(int x, int y, uint32_t c) {
        if (x>=0&&x<w&&y>=0&&y<h) {
            buffer[y*w+x]=(Color)c;
        }
    }
    void saveAsPPM(const std::string& filename) {
        std::ofstream out(filename,std::ios::binary);
        out<<"P6"<<std::endl<<w<<" "<<h<<" "<<std::endl<<255<<std::endl;
        out.write((char*)buffer.data(),w*h*3);
    }
};
#endif //CANVAS_HPP