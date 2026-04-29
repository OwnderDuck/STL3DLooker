#include <iostream>
#include "readSTL.hpp"
using namespace std;
int main() {
    auto t=STLReader::readBinSTL("cube.stl");
    cout<<"cnt: "<<t.size()<<endl;
    for (int i=0; i<t.size(); i++) {
        cout<<i<<":{"<<t[i].v1.x<<","<<t[i].v1.y<<","<<t[i].v1.z
              <<"},{"<<t[i].v2.x<<","<<t[i].v2.y<<","<<t[i].v2.z
              <<"},{"<<t[i].v3.x<<","<<t[i].v3.y<<","<<t[i].v3.z<<"}"<<endl;
    }
    return 0;
}