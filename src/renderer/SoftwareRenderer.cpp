#include "./SoftwareRenderer.h"

namespace rendering {

void line(int x0, int y0, int x1, int y1, tools::Bitmap& bitmap, const tools::Color& color) {
    bool reversed = false;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    if (dx < dy) {
        std::swap(x0, y0);
        std::swap(x1, y1);

        reversed = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    dx = std::abs(x1 - x0);
    dy = std::abs(y1 - y0);

    // dy/dx is a rate, so derror is dy/dx * dx * 2 to avoid 0.5 comparison
    int derror = std::abs(dy) * 2;
    int error = 0;

    int y = y0;
    for (int x = x0; x < x1; x += 1) {
        if (reversed && y >= 0 && y < bitmap.getWidth() && x >= 0 && x < bitmap.getHeight()) {
            bitmap.putPixelAt(y, x, color);
        } else if (x >= 0 && x < bitmap.getWidth() && y >= 0 && y < bitmap.getHeight()) {
            bitmap.putPixelAt(x, y, color);
        }

        error += derror;

        // error > 0.5, int => error * 2 > 1 => error * 2 * dx > dx
        if (error > dx) {
            y += (y1 > y0 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

}
