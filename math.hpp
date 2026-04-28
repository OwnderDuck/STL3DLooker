#ifndef MATH_HPP
#define MATH_HPP
#include <cmath>
#include <math.h>

struct Vector3 {
    float x,y,z;
    Vector3 operator + (const Vector3& v) const {return {x+v.x,y+v.y,z+v.z};}
    Vector3 operator - (const Vector3& v) const {return {x-v.x,y-v.y,z-v.z};}
    Vector3 cross(const Vector3& v) const {return {
        y*v.z-z*v.y,
        z*v.x-x*v.z,
        x*v.y-y*v.x};
    }
    float dot(const Vector3& v) const {return v.x*v.x+v.y*v.y+v.z*v.z;}
    float length() const {return sqrt(dot(*this));}
    Vector3 normalize() {
        float l=length();
        if (l>0) return {x/l,y/l,z/l};
        else return {0,0,0};
    }
};

#endif //MATH_HPP
