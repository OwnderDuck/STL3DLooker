#include <gtest/gtest.h>
#include "math.hpp"
#include "readSTL.hpp"
#include "canvas.hpp"

TEST(MathTest,VectorAddition){
    Vector3 a{1.0f,2.0f,3.0f};
    Vector3 b{4.0f,5.0f,6.0f};
    Vector3 c=a+b;

    EXPECT_FLOAT_EQ(c.x,5.0f);
    EXPECT_FLOAT_EQ(c.y,7.0f);
    EXPECT_FLOAT_EQ(c.z,9.0f);
}

TEST(MathTest,MatrixIdentity){
        Matrix4 id=Matrix4::identity();
        Vector3 p{10.0f,20.0f,30.0f};
        Vector3 ans=id.transform(p);
        EXPECT_FLOAT_EQ(ans.x,10.0f);
        EXPECT_FLOAT_EQ(ans.y,20.0f);
        EXPECT_FLOAT_EQ(ans.z,30.0f);
}

TEST(MathTest,CrossProduct){
    Vector3 a{1,0,0};
    Vector3 b{0,1,0};
    Vector3 c=a.cross(b);
    EXPECT_FLOAT_EQ(c.x,0.0f);
    EXPECT_FLOAT_EQ(c.y,0.0f);
    EXPECT_FLOAT_EQ(c.z,1.0f);
}
TEST(CanvasTest, SaveFileExists) {
    Canvas canvas(100, 100);
    canvas.clear(0x0000FF);
    for(int i=0; i<100; i++) {
        canvas.drawPixel(i, i, 0xFFFF00);
    }
    std::string filename = "testOutput.ppm";
    canvas.saveAsPPM(filename);
    std::ifstream f(filename);
    f.close();
    int ret=system("cmp -s testOutput.ppm rightTestOutput.ppm");
    EXPECT_EQ(WEXITSTATUS(ret), 0)<<"diff!!!return:"<<ret;
    //std::remove(filename.c_str());
}