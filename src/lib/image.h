#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "color.h"

/*
 * Image type code
 * BMP = 1
 * Can we just use macros for this?
 */
#define FORMAT_BMP 1
#define FORMAT_RAW 2
#define FORMAT_PBM 3
#define FORMAT_PGM 4
#define FORMAT_PPM 5

#define CHANNEL_BGR 1
#define CHANNEL_GRAY 2
#define CHANNEL_MONO 3

class Image {
    public:
        Image(char type, int width, int height);

        Color getColorAt(int i, int j);
        void setColorAt(int i, int j, Color c);

        int getWidth();
        int getHeight();
        char getType();

    private:
        std::vector<Color> img;
        int width;
        int height;
        char type;
        void checkIndex(int i, int j);
};

#endif