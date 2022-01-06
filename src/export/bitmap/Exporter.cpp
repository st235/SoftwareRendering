#include "Exporter.h"

#include <fstream>
#include <utility>

namespace tools {

Exporter::Exporter(std::string filename, std::string extension): _filename(std::move(filename)), _extension(std::move(extension)) {
}

Exporter::Exporter(Exporter &&renderer) noexcept {
    _filename = std::move(renderer._filename);
    _extension = std::move(renderer._extension);
}

Exporter & Exporter::operator=(Exporter &&renderer) noexcept {
    if (this == &renderer) {
        return *this;
    }

    _filename = std::move(renderer._filename);
    _extension = std::move(renderer._extension);

    return *this;
}

std::string Exporter::getFilename() const {
    return _filename + DELIMITER_DOT + _extension;
}

void Exporter::drawScene(const Bitmap *bitmap) {
    auto image_name = getFilename();
    FILE* imageFile = fopen(image_name.c_str(), "wb");

    uint8_t padding[3] = { 0, 0, 0 };

    fwrite(bitmap->getFileHeader(), 1, tools::Bitmap::getFileHeaderSizeInBytes(), imageFile);
    fwrite(bitmap->getInfoHeader(), 1, tools::Bitmap::getInfoHeaderSizeInBytes(), imageFile);

    for(int i = 0; i < bitmap->getHeight(); i++) {
        fwrite(bitmap->getImageData() + (i * bitmap->getWidth() * Bitmap::getBytesPerPixel()), Bitmap::getBytesPerPixel(), bitmap->getWidth(), imageFile);
        fwrite(padding, 1, bitmap->getPaddingSize(), imageFile);
    }

    fclose(imageFile);
}

std::unique_ptr<Exporter> Exporter::prepare(const Bitmap *bitmap) {
    return std::make_unique<Exporter>(bitmap->getTitle(), EXT_BMP);
}

std::string Exporter::EXT_BMP = "bmp";

std::string Exporter::DELIMITER_DOT = ".";

}
