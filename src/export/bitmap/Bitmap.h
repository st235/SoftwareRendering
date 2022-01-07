#ifndef PSEUDO_RANDOM_GENERATOR_BITMAP_H
#define PSEUDO_RANDOM_GENERATOR_BITMAP_H

#include <string>
#include <memory>

#include "./Color.h"

namespace tools {

class Bitmap {
private:
    std::string _title;
    uint16_t _width;
    uint16_t _height;
    uint32_t _paddingSize;

    uint8_t* _image_data;

    uint32_t calculateFileSize() const;

public:
    Bitmap(std::string&& title, uint16_t width, uint16_t height);
    Bitmap(const Bitmap& bitmap) = delete;
    Bitmap& operator=(const Bitmap& bitmap) = delete;
    Bitmap(Bitmap&& bitmap) noexcept;
    Bitmap& operator=(Bitmap&& bitmap) noexcept;

    std::string getTitle() const;

    uint16_t getWidth() const;

    uint16_t getHeight() const;

    uint32_t getPaddingSize() const;

    uint8_t* getFileHeader() const;

    uint8_t* getInfoHeader() const;

    uint8_t* getImageData() const;

    void clear(const Color& color);

    void pixelAt(uint32_t x, uint32_t y, const Color& color);

    bool isPointWithinBoundaries(uint32_t x, uint32_t y);

    ~Bitmap();

    static std::unique_ptr<Bitmap> create(std::string&& title, uint16_t width, uint16_t height);

    static uint8_t getFileHeaderSizeInBytes();

    static uint8_t getInfoHeaderSizeInBytes();

    static uint8_t getBytesPerPixel();
};

}  // namespace tools


#endif //PSEUDO_RANDOM_GENERATOR_BITMAP_H
