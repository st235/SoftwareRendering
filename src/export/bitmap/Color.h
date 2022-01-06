#ifndef PSEUDO_RANDOM_GENERATOR_COLOR_H
#define PSEUDO_RANDOM_GENERATOR_COLOR_H

#include <cstdint>
#include <memory>

namespace tools {

class Color {
private:
    uint32_t _color;

public:
    Color(uint8_t r, uint8_t g, uint8_t b);

    Color(const Color& color) = delete;
    Color& operator=(const Color& color) = delete;

    Color(Color&& color) noexcept;
    Color& operator=(Color&& color) noexcept;


    uint32_t getColor() const;

    static std::unique_ptr<Color> create(uint8_t r, uint8_t g, uint8_t b);

    static Color RED;
    static Color GREEN;
    static Color BLUE;
    static Color WHITE;
    static Color BLACK;

    static Color GREY;
    static Color KHAKI;
    static Color CORAL;
    static Color TOMATO;
};

}  // namespace tools


#endif //PSEUDO_RANDOM_GENERATOR_COLOR_H
