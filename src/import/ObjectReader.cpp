#include "ObjectReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace {
    std::vector<std::string> split (std::string s, std::string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }


    float clamp(float a, float min, float max) {
        return std::max(max, std::min(max, a));
    }
}

ObjectReader::ObjectReader(std::string title): _title(std::move(title)), _min(geometry::Vector3f(9999, 9999, 9999)), _max(geometry::Vector3f(0, 0, 0)) {
    std::ifstream input_model(_title);

    std::string line;
    while (std::getline(input_model, line)) {
        std::istringstream iss(line);

        std::string mode;

        if (!(iss >> mode)) {
            continue;
        }

        if (mode == "v") {
            float x,y,z;

            if (!(iss >> x >> y >> z)) {
                continue;
            }

            _min.x = std::min(_min.x, x);
            _min.y = std::min(_min.y, y);
            _min.z = std::min(_min.z, z);

            _max.x = std::max(_max.x, x);
            _max.y = std::max(_max.y, y);
            _max.z = std::max(_max.z, z);

            this->_points.emplace_back(geometry::Vector3f(x, y, z));
        } else if (mode == "f") {
            std::string a, b, c;

            if (!(iss >> a >> b >> c)) {
                continue;
            }

            std::vector<std::string> a_split = split(a, "/");
            std::vector<std::string> b_split = split(b, "/");
            std::vector<std::string> c_split = split(c, "/");

            std::vector<int> face;

            face.emplace_back(std::stoi(a_split[0]));
            face.emplace_back(std::stoi(b_split[0]));
            face.emplace_back(std::stoi(c_split[0]));

            this->_faces.emplace_back(std::move(face));
        }
    }
}

int ObjectReader::getFacesCount() {
    return this->_faces.size();
}

float ObjectReader::getWidth() {
    return _max.x - _min.x;
}

float ObjectReader::getOffsetX() {
    return _min.x;
}

float ObjectReader::getHeight() {
    return _max.y - _min.y;
}

float ObjectReader::getOffsetY() {
    return _min.y;
}

std::vector<int> ObjectReader::getFaceAt(int i) {
    return this->_faces[i];
}

geometry::Vector3f ObjectReader::getPointAt(int index) {
    return this->_points[index];
}
