#ifndef SOFTWARERENDERER_OBJECTREADER_H
#define SOFTWARERENDERER_OBJECTREADER_H

#include "string"
#include "vector"

#include "../geometry/Vectors.h"

class ObjectReader {
private:
    std::string _title;
    std::vector<geometry::Vector3f> _points;
    std::vector<std::vector<int>> _faces;

    geometry::Vector3f _min;
    geometry::Vector3f _max;

public:
    explicit ObjectReader(std::string  title);

    float getWidth();

    float getMinX();

    float getHeight();

    float getMinY();

    float getDepth();

    float getMinZ();

    int getFacesCount();

    std::vector<int> getFaceAt(int index);

    geometry::Vector3f getPointAt(int index);

};


#endif //SOFTWARERENDERER_OBJECTREADER_H
