#ifndef SOFTWARERENDERER_SOFTWARERENDERER_H
#define SOFTWARERENDERER_SOFTWARERENDERER_H

#include "../export/bitmap/Bitmap.h"
#include "../export/bitmap/Color.h"

namespace rendering {

    void line(int x0, int y0, int x1, int y1, tools::Bitmap& bitmap, const tools::Color& color);

} // namespace rendering

#endif //SOFTWARERENDERER_SOFTWARERENDERER_H
