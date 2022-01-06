cmake_minimum_required(VERSION 3.21)
project(SoftwareRenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(SoftwareRenderer
        main.cpp
        src/export/bitmap/Bitmap.h
        src/export/bitmap/Bitmap.cpp
        src/export/bitmap/Exporter.h
        src/export/bitmap/Exporter.cpp
        src/export/bitmap/Color.h
        src/export/bitmap/Color.cpp src/renderer/SoftwareRenderer.h src/renderer/SoftwareRenderer.cpp src/import/ObjectReader.cpp src/import/ObjectReader.h)
