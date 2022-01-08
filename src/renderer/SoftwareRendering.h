#ifndef SOFTWARERENDERER_SOFTWARERENDERING_H
#define SOFTWARERENDERER_SOFTWARERENDERING_H

#include "../export/bitmap/Bitmap.h"
#include "../export/bitmap/Color.h"

#include "../geometry/Vectors.h"

namespace rendering {

void line(int x0, int y0, int x1, int y1, tools::Bitmap& bitmap, const tools::Color& color);

void line(const geometry::Vector2i& start, const geometry::Vector2i& finish, tools::Bitmap& bitmap, const tools::Color& color);

void triangle(geometry::Vector3f& v0, geometry::Vector3f& v1, geometry::Vector3f& v2, tools::Bitmap& bitmap, float* zbuffer, const tools::Color& color);

void triangle_legacy(geometry::Vector2i& v0, geometry::Vector2i& v1, geometry::Vector2i& v2, tools::Bitmap& bitmap, const tools::Color& color);

} // namespace rendering

#endif //SOFTWARERENDERER_SOFTWARERENDERING_H
