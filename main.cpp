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

    float* zbuffer = new float[width * height];

    for (int i = 0; i < width * height; i++) {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }

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
//            int x0 = (origin.x - reader.getMinX()) / reader.getWidth() * width;
//            int y0 = (origin.y - reader.getMinY()) / reader.getHeight() * height / ratio;
//            int x1 = (finish.x - reader.getMinX()) / reader.getWidth() * width;
//            int y1 = (finish.y - reader.getMinY()) / reader.getHeight() * height / ratio;
//
//            rendering::line(x0, y0, x1, y1, scene, tools::Color::BLACK);
//        }
//    }

    for (int f = 0; f < reader.getFacesCount(); f++) {
        std::vector<int> face = reader.getFaceAt(f);

        geometry::Vector3f screen[] {{0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
        geometry::Vector3f world[] {{0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

        for (int i = 0; i < 3; i++) {
            geometry::Vector3f origin = reader.getPointAt(face[i] - 1);

            float x, y, z;

            if (reader.getWidth() > reader.getHeight()) {
                x = (origin.x - reader.getMinX()) / reader.getWidth() * width;

                float yRatio = reader.getHeight() / reader.getWidth();
                y = (origin.y - reader.getMinY() - reader.getHeight() / 2) / reader.getHeight() * (width * yRatio) + height / 2;

                float zRatio = reader.getDepth() / reader.getWidth();
                z = (origin.z - reader.getMinZ()) / reader.getDepth() * (width * zRatio);
            } else {
                y = (origin.y - reader.getMinY()) / reader.getHeight() * height;

                float xRatio = reader.getWidth() / reader.getHeight();
                x = (origin.x - reader.getMinX() - reader.getWidth() / 2) / reader.getWidth() * (height * xRatio) + width / 2;

                float zRatio = reader.getDepth() / reader.getHeight();
                z = (origin.z - reader.getMinZ()) / reader.getDepth() * (height * zRatio);
            }

            screen[i] = { x, y, z };
            world[i] = origin;
        }

        geometry::Vector3f ab = world[1] - world[0];
        geometry::Vector3f ac = world[2] - world[0];

        geometry::Vector3f normal = ac.crossProduct(ab).normalize();

        geometry::Vector3f light_direction(0, 0, -1);

        float intensity = light_direction.dotProduct(normal);

        if (intensity > 0) {
            rendering::triangle(screen[0], screen[1], screen[2], scene, zbuffer,
                                tools::Color::rgb(intensity * 255, intensity * 255, intensity * 255));
        }
    }

    auto exporter = tools::Exporter::prepare(&scene);
    exporter->drawScene(&scene);
    return 0;
}
