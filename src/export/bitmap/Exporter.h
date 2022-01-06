#ifndef PSEUDO_RANDOM_GENERATOR_RENDERER_H
#define PSEUDO_RANDOM_GENERATOR_RENDERER_H

#include <string>

#include "./Bitmap.h"

namespace tools {

class Exporter {
private:
    std::string _filename;
    std::string _extension;

    static std::string DELIMITER_DOT;

public:
    Exporter(std::string filename, std::string extension);
    Exporter(const Exporter& renderer) = delete;
    Exporter& operator=(const Exporter& renderer) = delete;
    Exporter(Exporter&& renderer) noexcept;
    Exporter& operator=(Exporter&& renderer) noexcept;

    std::string getFilename() const;

    void drawScene(const Bitmap* bitmap);

    static std::unique_ptr<Exporter> prepare(const Bitmap* bitmap);

    static std::string EXT_BMP;
};

}


#endif //PSEUDO_RANDOM_GENERATOR_RENDERER_H
