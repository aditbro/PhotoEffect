#include <exception>
#include "image.h"


Image::Image(char type, int width, int height){
    this->type = type;
    this->width = width;
    this->height = height;

    img.reserve(width * height * 4);
}

Color Image::getColorAt(int i, int j) {
    int index = (width * 4 * i) + j * 4;
    char r = img[index];
    char g = img[index+1];
    char b = img[index+2];
    return Color(r,g,b);
}

void Image::setColorAt(int i, int j, Color c) {
    checkIndex(i, j);
    int index = (width * 4 * i) + j * 4;
    img[index] = c.r;
    img[index+1] = c.g;
    img[index+2] = c.b;
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

char* Image::getVectorBegin() {
    return this->img.data();
}

char* Image::getVectorEnd() {
    return &this->img.back();
}

void Image::copyImageVector(std::shared_ptr<Image> src) {
    this->img.assign(src->getVectorBegin(), src->getVectorEnd());
}