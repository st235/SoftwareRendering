#ifndef SOFTWARERENDERER_SOFTWARERENDERING_H
#define SOFTWARERENDERER_SOFTWARERENDERING_H

#include "../export/bitmap/Bitmap.h"
#include "../export/bitmap/Color.h"

#include "../geometry/Vectors.h"

namespace rendering {

geometry::Vector3f asBarycentric(geometry::Vector2i& a, geometry::Vector2i& b, geometry::Vector2i& c, geometry::Vector2i& p);

void line(int x0, int y0, int x1, int y1, tools::Bitmap& bitmap, const tools::Color& color);

void line(const geometry::Vector2i& start, const geometry::Vector2i& finish, tools::Bitmap& bitmap, const tools::Color& color);

void triangle(geometry::Vector2i& v0, geometry::Vector2i& v1, geometry::Vector2i& v2, tools::Bitmap& bitmap, const tools::Color& color);

void triangle_legacy(geometry::Vector2i& v0, geometry::Vector2i& v1, geometry::Vector2i& v2, tools::Bitmap& bitmap, const tools::Color& color);

} // namespace rendering

#endif //SOFTWARERENDERER_SOFTWARERENDERING_H
