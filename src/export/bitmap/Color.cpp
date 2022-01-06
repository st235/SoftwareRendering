#include "Color.h"

namespace tools {

Color::Color(uint8_t r, uint8_t g, uint8_t b): _color((static_cast<uint32_t>(r) << 16U) | (static_cast<uint32_t>(g) << 8U) | (b)) {
}

Color::Color(Color&& color) noexcept {
    this->_color = color._color;
    color._color = 0;
}

Color & Color::operator=(Color&& color) noexcept {
    if (this == &color) {
        return *this;
    }

    _color = color._color;
    color._color = 0;

    return *this;
}

std::unique_ptr<Color> Color::create(uint8_t r, uint8_t g, uint8_t b) {
    return std::make_unique<Color>(r, g, b);
}

uint32_t Color::getColor() const {
    return _color;
}

Color Color::BLACK = Color(0, 0, 0);
Color Color::WHITE = Color(255, 255, 255);
Color Color::RED = Color(255, 0, 0);
Color Color::GREEN = Color(0, 255, 0);
Color Color::BLUE = Color(0, 0, 255);

Color Color::GREY = Color(192, 192, 192);
Color Color::KHAKI = Color(240, 230, 140);
Color Color::CORAL = Color(255, 127, 80);
Color Color::TOMATO = Color(255, 99, 71);


}  // namespace tools
