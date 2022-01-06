#include "./src/export/bitmap/Bitmap.h"
#include "./src/export/bitmap/Exporter.h"

#include "./src/renderer/SoftwareRenderer.h"
#include "./src/import/ObjectReader.h"

int main() {
    int width = 1024;
    int height = 1024;

    tools::Bitmap scene("Scene", width, height);
    scene.fillWithColor(tools::Color::BLACK);

    ObjectReader reader("laurel.obj");

    for (int f = 0; f < reader.getFacesCount(); f++) {
        std::vector<int> face = reader.getFaceAt(f);

        float ratio = reader.getWidth() / reader.getHeight();

        for (int i = 0; i < 3; i++) {
            Vector3f origin = reader.getPointAt(face[i] - 1);
            Vector3f finish = reader.getPointAt(face[(i + 1) % 3] - 1);

            int x0 = (origin.x - reader.getOffsetX()) / reader.getWidth() * width;
            int y0 = (origin.y - reader.getOffsetY()) / reader.getHeight() * height / ratio;
            int x1 = (finish.x - reader.getOffsetX()) / reader.getWidth() * width;
            int y1 = (finish.y - reader.getOffsetY()) / reader.getHeight() * height / ratio;

            rendering::line(x0, y0, x1, y1, scene, tools::Color::WHITE);
        }
    }


    auto exporter = tools::Exporter::prepare(&scene);
    exporter->drawScene(&scene);
    return 0;
}
