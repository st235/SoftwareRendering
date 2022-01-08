#ifndef SOFTWARERENDERER_VECTORS_H
#define SOFTWARERENDERER_VECTORS_H

namespace geometry {

struct Vector2i {
public:
    int x;
    int y;

    Vector2i(int x, int y);
    Vector2i(const Vector2i& that);
    Vector2i&  operator=(const Vector2i& that);
};

struct Vector2f {
public:
    float x;
    float y;

    Vector2f(float x, float y);
    Vector2f(const Vector2f& that);
    Vector2f&  operator=(const Vector2f& that);
};

struct Vector3i {
public:
    int x;
    int y;
    int z;

    Vector3i(int x, int y, int z);
    Vector3i(const Vector3i& that);
    Vector3i&  operator=(const Vector3i& that);
};

struct Vector3f {
public:
    float x;
    float y;
    float z;

    Vector3f(float x, float y, float z);
    Vector3f(const Vector3f& that);
    Vector3f&  operator=(const Vector3f& that);

    Vector3f operator-(const Vector3f& that) const;
    Vector3f operator+(const Vector3f& that) const;

    Vector3f operator/(float val) const;
    Vector3f operator*(float val) const;

    Vector3f crossProduct(const Vector3f& that) const;

    float length() const;

    Vector3f normalize() const;

    float dotProduct(const Vector3f& that) const;

};

} // namespace geometry

#endif //SOFTWARERENDERER_VECTORS_H
