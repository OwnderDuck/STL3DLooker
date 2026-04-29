#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>

struct Vector3 {
    float x,y,z;
    Vector3 operator + (const Vector3& o) const {return {x+o.x,y+o.y,z+o.z};}
    Vector3 operator - (const Vector3& o) const {return {x-o.x,y-o.y,z-o.z};}
    [[nodiscard]] Vector3 cross(const Vector3& o) const {return {
        y*o.z-z*o.y,
        z*o.x-x*o.z,
        x*o.y-y*o.x};
    }
    [[nodiscard]] float dot(const Vector3& o) const {return x*o.x+y*o.y+z*o.z;}
    [[nodiscard]] float length() const {return std::sqrt(dot(*this));}
    [[nodiscard]] Vector3 normalize() const {
        float l=length();
        if (l>0) return {x/l,y/l,z/l};
        else return {0,0,0};
    }
};

struct Matrix4 {
    float m[4][4]={0};
    float* operator[](int o) {return m[o];}
    const float* operator[](int o) const {return m[o];}
    static Matrix4 identity() {
        Matrix4 _m;
        _m[0][0]=1;_m[0][1]=0;_m[0][2]=0;_m[0][3]=0;
        _m[1][0]=0;_m[1][1]=1;_m[1][2]=0;_m[1][3]=0;
        _m[2][0]=0;_m[2][1]=0;_m[2][2]=1;_m[2][3]=0;
        _m[3][0]=0;_m[3][1]=0;_m[3][2]=0;_m[3][3]=1;
        return _m;
    }
    Matrix4 operator*(const Matrix4& o) {
        Matrix4 ans;
        for (int i=0;i<4;i++) {for (int j=0;j<4;j++) {for (int k=0;k<4;k++) {
            ans[i][j]+=m[i][k]*o[k][j];
        }}}
        return ans;
    }
    [[nodiscard]] Vector3 transform(const Vector3 o) const {
        float x=o.x*m[0][0]+o.y*m[0][1]+o.z*m[0][2]+m[0][3];
        float y=o.x*m[1][0]+o.y*m[1][1]+o.z*m[1][2]+m[1][3];
        float z=o.x*m[2][0]+o.y*m[2][1]+o.z*m[2][2]+m[2][3];
        float w=o.x*m[3][0]+o.y*m[3][1]+o.z*m[3][2]+m[3][3];
        if (w!=0) return {x/w,y/w,z/w};
        return {0,0,0};
    }
};

#endif //MATH_HPP
