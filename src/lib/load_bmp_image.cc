#include "image_loader.h"
#include <string>

std::shared_ptr<Image> loadBMPImage(std::string filename) {
    std::shared_ptr<Image> img(new Image(1, 400, 300));
    return img;
}