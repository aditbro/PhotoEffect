#include "image.h"

Image::Image(char type, int width, int height){
    this->type = type;
    this->width = width;
    this->height = height;

    img.reserve(width * height);
}

Color Image::getColorAt(int i, int j) {
    int index = (width * i) + j;
    return img.at(index);
}

void Image::setColorAt(int i, int j, Color c) {
    int index = (width * i) + j;
    img.at(index) = c;
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