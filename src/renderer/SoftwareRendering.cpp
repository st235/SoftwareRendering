#include "./SoftwareRendering.h"

#include "../geometry/Vectors.h"

#include "iostream"

namespace rendering {

/**
 * Bresenham's algorithm
 */
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
    for (int x = x0; x <= x1; x += 1) {
        if (reversed) {
            bitmap.pixelAt(y, x, color);
        } else {
            bitmap.pixelAt(x, y, color);
        }

        error += derror;

        // error > 0.5, int => error * 2 > 1 => error * 2 * dx > dx
        if (error > dx) {
            y += (y1 > y0 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void line(const geometry::Vector2i& start, const geometry::Vector2i& finish, tools::Bitmap& bitmap, const tools::Color& color) {
    line(start.x, start.y, finish.x, finish.y, bitmap, color);
}

geometry::Vector3f toBarycentric(geometry::Vector2i& a, geometry::Vector2i& b, geometry::Vector2i& c, geometry::Vector2i& p) {
    geometry::Vector3f cross_product_vector = geometry::Vector3f(b.x - a.x, c.x - a.x, a.x - p.x).crossProduct(geometry::Vector3f(b.y - a.y, c.y - a.y, a.y - p.y));

    if (std::abs(cross_product_vector.z) < 1) {
        return {-1, -1, -1 };
    }

    float u = cross_product_vector.x / cross_product_vector.z;
    float v = cross_product_vector.y / cross_product_vector.z;

    return {1 - v - u, u, v};
}

/**
 * Barycentric algorithm
 */
void triangle(geometry::Vector2i& v0, geometry::Vector2i& v1, geometry::Vector2i& v2, tools::Bitmap& bitmap, const tools::Color& color) {
    geometry::Vector2i min(bitmap.getWidth() - 1, bitmap.getHeight() - 1);
    geometry::Vector2i max(0, 0);

    geometry::Vector2i points[] { v0, v1, v2 };

    for (const auto& point: points) {
        min.x = std::min(min.x, point.x);
        min.y = std::min(min.y, point.y);

        max.x = std::max(max.x, point.x);
        max.y = std::max(max.y, point.y);
    }

    for (auto x = min.x; x <= max.x; x += 1) {
        for (auto y = min.y; y <= max.y; y += 1) {
            geometry::Vector2i point(x, y);

            geometry::Vector3f barycentric_coordinates = toBarycentric(v0, v1, v2, point);

            if (barycentric_coordinates.x < 0 || barycentric_coordinates.y < 0 || barycentric_coordinates.z < 0) {
                continue;
            }

            bitmap.pixelAt(x, y, color);
        }
    }
}

/**
 * Line sweep algorithm
 */
void triangle_legacy(geometry::Vector2i& v0, geometry::Vector2i& v1, geometry::Vector2i& v2, tools::Bitmap& bitmap, const tools::Color& color) {
    // flatten bubble sort to sort all values
    if (v0.y > v1.y) std::swap(v0, v1);
    if (v0.y > v2.y) std::swap(v0, v2);
    if (v1.y > v2.y) std::swap(v1, v2);

    int full_height = std::abs(v2.y - v0.y);

    for (int y = v0.y; y <= v1.y; y++) {
        int part_height = std::abs(v1.y - v0.y);

        int x0 = float(y - v0.y) / float(part_height) * (v1.x - v0.x) + v0.x;
        int x1 = float(y - v0.y) / float(full_height) * (v2.x - v0.x) + v0.x;

        bitmap.pixelAt(x0, y, tools::Color::RED);
        bitmap.pixelAt(x1, y, tools::Color::GREEN);

        for (int x = std::min(x0, x1); x <= std::max(x0, x1); x++) {
            bitmap.pixelAt(x, y, tools::Color::WHITE);
        }
    }

    for (int y = v1.y; y <= v2.y; y++) {
        int part_height = std::abs(v2.y - v1.y);

        int x0 = float(y - v1.y) / float(part_height) * (v2.x - v1.x) + v1.x;
        int x1 = float(y - v0.y) / float(full_height) * (v2.x - v0.x) + v0.x;

        bitmap.pixelAt(x0, y, tools::Color::RED);
        bitmap.pixelAt(x1, y, tools::Color::GREEN);

        for (int x = std::min(x0, x1); x <= std::max(x0, x1); x++) {
            bitmap.pixelAt(x, y, tools::Color::WHITE);
        }
    }
}

}
