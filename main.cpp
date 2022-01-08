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

    ObjectReader reader("miata.obj");

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

        geometry::Vector2i screen[] {{0, 0}, {0, 0}, {0, 0} };
        geometry::Vector3f world[] {{0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

        for (int i = 0; i < 3; i++) {
            geometry::Vector3f origin = reader.getPointAt(face[i] - 1);

            int x0, y0;

            if (reader.getWidth() > reader.getHeight()) {
                float ratio = reader.getHeight() / reader.getWidth();
                x0 = (origin.x - reader.getOffsetX()) / reader.getWidth() * width;
                y0 = (origin.y - reader.getOffsetY() - reader.getHeight() / 2) / reader.getHeight() * (width * ratio) + height / 2;
            } else {
                float ratio = reader.getWidth() / reader.getHeight();
                y0 = (origin.y - reader.getOffsetY()) / reader.getHeight() * height;
                x0 = (origin.x - reader.getOffsetX() - reader.getWidth() / 2) / reader.getWidth() * (height * ratio) + width / 2;
            }

            screen[i] = {x0, y0 };
            world[i] = origin;
        }

        geometry::Vector3f ab = world[1] - world[0];
        geometry::Vector3f ac = world[2] - world[0];

        geometry::Vector3f normal = ac.crossProduct(ab).normalize();

        geometry::Vector3f light_direction(0, 0, -1);

        float intensity = light_direction.dotProduct(normal);

        if (intensity > 0) {
            rendering::triangle(screen[0], screen[1], screen[2], scene,
                                tools::Color::rgb(intensity * 255, intensity * 255, intensity * 255));
        }
    }

    auto exporter = tools::Exporter::prepare(&scene);
    exporter->drawScene(&scene);
    return 0;
}
