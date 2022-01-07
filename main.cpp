#include "./src/export/bitmap/Bitmap.h"
#include "./src/export/bitmap/Exporter.h"

#include "./src/renderer/SoftwareRendering.h"
#include "./src/import/ObjectReader.h"
#include "./src/geometry/Vectors.h"

#include "iostream"

int main() {
    int width = 512;
    int height = 512;

    tools::Bitmap scene("Scene", width, height);
    scene.clear(tools::Color::BLACK);

    ObjectReader reader("laurel.obj");

// mesh
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


    for (int f = 0; f < reader.getFacesCount(); f++) {
        std::vector<int> face = reader.getFaceAt(f);

        float ratio = reader.getWidth() / reader.getHeight();

        geometry::Vector2i triangle[] { {0, 0}, {0, 0}, {0, 0} };

        for (int i = 0; i < 3; i++) {
            geometry::Vector3f origin = reader.getPointAt(face[i] - 1);

            int x0 = (origin.x - reader.getOffsetX()) / reader.getWidth() * width;
            int y0 = (origin.y - reader.getOffsetY()) / reader.getHeight() * height / ratio;

            triangle[i] = { x0, y0 };
        }

        rendering::triangle(triangle[0], triangle[1], triangle[2], scene, tools::Color::random());
    }

    auto exporter = tools::Exporter::prepare(&scene);
    exporter->drawScene(&scene);
    return 0;
}
