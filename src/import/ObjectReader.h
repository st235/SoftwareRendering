#ifndef SOFTWARERENDERER_OBJECTREADER_H
#define SOFTWARERENDERER_OBJECTREADER_H

#include "string"
#include "vector"

struct Vector3f {
    float x;
    float y;
    float z;

    Vector3f(float x, float y, float z);
};

class ObjectReader {
private:
    std::string _title;
    std::vector<Vector3f> _points;
    std::vector<std::vector<int>> _faces;

    Vector3f _min;
    Vector3f _max;

public:
    explicit ObjectReader(std::string  title);

    float getWidth();

    float getOffsetX();

    float getHeight();

    float getOffsetY();

    int getFacesCount();

    std::vector<int> getFaceAt(int index);

    Vector3f getPointAt(int index);

};


#endif //SOFTWARERENDERER_OBJECTREADER_H
