#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>

struct V3 {
    float x,y,z;
    V3 operator + (const V3& o) const {return {x+o.x,y+o.y,z+o.z};}
    V3 operator - (const V3& o) const {return {x-o.x,y-o.y,z-o.z};}
    [[nodiscard]] V3 cross(const V3& o) const {return {
        y*o.z-z*o.y,
        z*o.x-x*o.z,
        x*o.y-y*o.x};
    }
    [[nodiscard]] float dot(const V3& o) const {return x*o.x+y*o.y+z*o.z;}
    [[nodiscard]] float length() const {return std::sqrt(dot(*this));}
    [[nodiscard]] V3 normalize() const {
        float l=length();
        if (l>0) return {x/l,y/l,z/l};
        else return {0,0,0};
    }
};

struct Matrix4 {
    float m[4][4]={0};
    Matrix4() {
        m[0][0]=0;m[0][1]=0;m[0][2]=0;m[0][3]=0;
        m[1][0]=0;m[1][1]=0;m[1][2]=0;m[1][3]=0;
        m[2][0]=0;m[2][1]=0;m[2][2]=0;m[2][3]=0;
        m[3][0]=0;m[3][1]=0;m[3][2]=0;m[3][3]=0;
    }
    Matrix4(float m00,float m01,float m02,float m03,float m10,float m11,float m12,float m13,float m20,float m21,float m22,float m23,float m30,float m31,float m32,float m33) {
        m[0][0]=m00;m[0][1]=m01;m[0][2]=m02;m[0][3]=m03;
        m[1][0]=m10;m[1][1]=m11;m[1][2]=m12;m[1][3]=m13;
        m[2][0]=m20;m[2][1]=m21;m[2][2]=m22;m[2][3]=m23;
        m[3][0]=m30;m[3][1]=m31;m[3][2]=m32;m[3][3]=m33;
    }
    float* operator[](int o) {return m[o];}
    const float* operator[](int o) const {return m[o];}
    static Matrix4 identity() {
        return {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1};
    }
    Matrix4 operator*(const Matrix4& o) {
        Matrix4 ans;
        for (int i=0;i<4;i++) {for (int j=0;j<4;j++) {for (int k=0;k<4;k++) {
            ans[i][j]+=m[i][k]*o[k][j];
        }}}
        return ans;
    }
    bool operator==(const Matrix4& o) const {
        const float eps = 1e-5f;
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                if (std::abs(m[i][j]-o.m[i][j])>eps) {
                    return 0;
                }
            }
        }
        return 1;
    }
    [[nodiscard]] V3 transform(const V3 o) const {
        float x=o.x*m[0][0]+o.y*m[0][1]+o.z*m[0][2]+m[0][3];
        float y=o.x*m[1][0]+o.y*m[1][1]+o.z*m[1][2]+m[1][3];
        float z=o.x*m[2][0]+o.y*m[2][1]+o.z*m[2][2]+m[2][3];
        float w=o.x*m[3][0]+o.y*m[3][1]+o.z*m[3][2]+m[3][3];
        if (w!=0) return {x/w,y/w,z/w};
        return {0,0,0};
    }
    static Matrix4 lookAt(const V3& eye,const V3& target,const V3& up) {
        V3 f=(eye-target).normalize(); //front
        V3 upToUse=up;
        if (std::abs(f.dot(upToUse))>1-(1e-6)) {upToUse=V3(0,0,f.y>0?1:-1);}
        V3 r=upToUse.cross(f).normalize(); //right
        V3 u=f.cross(r); //up
        return {
            r.x,u.x,f.x,-r.dot(eye),
            r.y,u.y,f.y,-u.dot(eye),
            r.z,u.z,f.z,-f.dot(eye),
            0,0,0,0
        };
    }
};

#endif //MATH_HPP
