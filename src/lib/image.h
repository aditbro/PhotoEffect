#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "color.h"

/*
 * Image type code
 * BMP = 1
 */

class Image {
    public:
        Image(char type, int width, int height);

        Color getColorAt(int i, int j);
        void setColorAt(int i, int j, Color c);

        int getWidth();
        int getHeight();
        int getPixelRange();
        char getType();

        char* getVectorBegin();
        char* getVectorEnd();

        void copyImageVector(std::shared_ptr<Image>);
    private:
        std::vector<char> img;
        int width;
        int height;
        int pixel_range;
        char type;
        void checkIndex(int i, int j);
};

#endif