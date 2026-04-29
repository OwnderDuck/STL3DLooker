#ifndef READSTL_HPP
#define READSTL_HPP
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "math.hpp"
struct STLTriangle {
    Vector3 normal;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    uint16_t attr;
};
class STLReader {
public:
    static std::vector<STLTriangle> readBinSTL(const std::string path) {
        std::ifstream file(path,std::ios::binary);
        if (!file) {
            std::cerr<<"FATAL: Cannot open "<<path<<std::endl;
            return {};
        }
        file.seekg(80,std::ios::beg); //skip Header, 80 bytes
        // read triangle cnt
        uint32_t triangleCnt;
        file.read((char*)&triangleCnt,sizeof(uint32_t));
        // new vector
        std::vector<STLTriangle> triangles;
        triangles.reserve(triangleCnt);
        // read each triangle, 50 bytes per triangle
        STLTriangle t{};
        for (uint32_t i=0;i<triangleCnt;i++) {
            file.read((char*)&t,sizeof(STLTriangle));

        }
    }
};
#endif //READSTL_HPP
