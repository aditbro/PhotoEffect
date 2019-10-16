#include <exception>
#include "image.h"


Image::Image(char type, int width, int height){
    this->type = type;
    this->width = width;
    this->height = height;

    img.reserve(width * height);
}

Color Image::getColorAt(int i, int j) {
    int index = (width * i) + j;
    return img[index];
}

void Image::setColorAt(int i, int j, Color c) {
    checkIndex(i, j);
    int index = (width * i) + j;
    img[index] = c;
}

int Image::getWidth() {
    return width;
}

int Image::getHeight() {
    return height;
}

char Image::getType() {
    return type;
}

void Image::checkIndex(int i, int j) {
    if(i >= height || i < 0 || j >= width || j < 0) {
        throw std::invalid_argument(std::to_string(i) + " " + std::to_string(j) + " Image index out of range");
    }
}

int Image::getPixelRange() {
    return this->pixel_range;
}