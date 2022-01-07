#include "Vectors.h"

namespace geometry {

    Vector2i::Vector2i(int x, int y) : x(x), y(y) {
    }

    Vector2i::Vector2i(const Vector2i &that) {
        this->x = that.x;
        this->y = that.y;
    }

    Vector2i &Vector2i::operator=(const Vector2i &that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
        }

        return *this;
    }

    Vector2f::Vector2f(float x, float y) : x(x), y(y) {
    }

    Vector2f::Vector2f(const Vector2f &that) {
        this->x = that.x;
        this->y = that.y;
    }

    Vector2f &Vector2f::operator=(const Vector2f &that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
        }

        return *this;
    }

    Vector3i::Vector3i(int x, int y, int z) : x(x), y(y), z(z) {
    }

    Vector3i::Vector3i(const Vector3i &that) {
        this->x = that.x;
        this->y = that.y;
        this->z = that.z;
    }

    Vector3i &Vector3i::operator=(const Vector3i &that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
            this->z = that.z;
        }

        return *this;
    }

    Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {

    }

    Vector3f::Vector3f(const Vector3f &that) {
        this->x = that.x;
        this->y = that.y;
        this->z = that.z;
    }

    Vector3f &Vector3f::operator=(const Vector3f &that) {
        if (this != &that) {
            this->x = that.x;
            this->y = that.y;
            this->z = that.z;
        }

        return *this;
    }

    Vector3f Vector3f::crossProduct(const Vector3f &that) {
        return {this->y * that.z - this->z * that.y, - (this->x * that.z - this->z * that.x), this->x * that.y - this->y * that.x };
    }

}
