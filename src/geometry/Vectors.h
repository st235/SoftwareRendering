#ifndef SOFTWARERENDERER_VECTORS_H
#define SOFTWARERENDERER_VECTORS_H

#include <cmath>

namespace geometry {

template<class V>
struct Vector2 {
public:
    V x;
    V y;
    
    Vector2(V x, V y) : x(x), y(y) {
    }

    Vector2(const Vector2 &that) {
        this->x = that.x;
        this->y = that.y;
    }

    Vector2 &operator=(const Vector2 &that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
        }

        return *this;
    }

    Vector2 operator+(const Vector2 &that) const {
        return { x + that.x, y + that.y };
    }

    Vector2 operator-(const Vector2 &that) const {
        return { x - that.x, y - that.y };
    }

    Vector2 operator*(float val) const {
        return { x * val, y * val };
    }

    Vector2 operator/(float val) const {
        return { x / val, y / val };
    }

    V length() const {
        return sqrt(x * x + y * y);
    }

    Vector2 normalize() const {
        V length = this->length();
        return { x / length, y / length };
    }

    V dotProduct(const Vector2 &that) const {
        return sqrt(x * that.x + y * that.y);
    }

};

template<typename V>
struct Vector3 {
public:
    V x;
    V y;
    V z;

    Vector3(V x, V y, V z): x(x), y(y), z(z) {
        //empty on purpose
    }
    
    Vector3(const Vector3& that) {
        this->x = that.x;
        this->y = that.y;
        this->z = that.z;
    }
    
    Vector3&  operator=(const Vector3& that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
            this->z = that.z;
        }

        return *this;
    }

    Vector3 operator+(const Vector3 &that) const {
        return { x + that.x, y + that.y, z + that.z };
    }

    Vector3 operator-(const Vector3 &that) const {
        return { x - that.x, y - that.y, z - that.z };
    }

    Vector3 operator*(float val) const {
        return { x * val, y * val, z * val };
    }

    Vector3 operator/(float val) const {
        return { x / val, y / val, z / val };
    }

    Vector3 crossProduct(const Vector3 &that) const {
        return {this->y * that.z - this->z * that.y, - (this->x * that.z - this->z * that.x), this->x * that.y - this->y * that.x };
    }

    V length() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 normalize() const {
        V length = this->length();
        return { x / length, y / length, z / length };
    }

    V dotProduct(const Vector3 &that) const {
        return sqrt(x * that.x + y * that.y + z * that.z);
    }

};

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

} // namespace geometry

#endif //SOFTWARERENDERER_VECTORS_H
