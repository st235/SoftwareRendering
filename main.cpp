#include "./src/export/bitmap/Bitmap.h"
#include "./src/export/bitmap/Exporter.h"

#include "./src/renderer/SoftwareRendering.h"
#include "./src/import/ObjectReader.h"
#include "./src/geometry/Vectors.h"

#include "iostream"

int main() {
    int width = 256;
    int height = 256;

    tools::Bitmap scene("Scene", width, height);
    scene.clear(tools::Color::BLACK);

    geometry::Vector2i t0[3] = {geometry::Vector2i(10, 70),   geometry::Vector2i(50, 160),  geometry::Vector2i(70, 80)};
    geometry::Vector2i t1[3] = {geometry::Vector2i(180, 50),  geometry::Vector2i(150, 1),   geometry::Vector2i(70, 180)};
    geometry::Vector2i t2[3] = {geometry::Vector2i(180, 150), geometry::Vector2i(120, 160), geometry::Vector2i(130, 180)};
    rendering::triangle(t0[0], t0[1], t0[2], scene, tools::Color::RED);
    rendering::triangle(t1[0], t1[1], t1[2], scene, tools::Color::WHITE);
    rendering::triangle(t2[0], t2[1], t2[2], scene, tools::Color::GREEN);


//    ObjectReader reader("laurel.obj");

//    for (int f = 0; f < reader.getFacesCount(); f++) {
//        std::vector<int> face = reader.getFaceAt(f);
//
//        float ratio = reader.getWidth() / reader.getHeight();
//
//        for (int i = 0; i < 3; i++) {
//            geometry::Vector3f origin = reader.getPointAt(face[i] - 1);
//            geometry::Vector3f finish = reader.getPointAt(face[(i + 1) % 3] - 1);
//
//            int x0 = (origin.x - reader.getOffsetX()) / reader.getWidth() * width;
//            int y0 = (origin.y - reader.getOffsetY()) / reader.getHeight() * height / ratio;
//            int x1 = (finish.x - reader.getOffsetX()) / reader.getWidth() * width;
//            int y1 = (finish.y - reader.getOffsetY()) / reader.getHeight() * height / ratio;
//
//            rendering::line(x0, y0, x1, y1, scene, tools::Color::BLACK);
//        }
//    }


    auto exporter = tools::Exporter::prepare(&scene);
    exporter->drawScene(&scene);
    return 0;
}
