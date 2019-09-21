#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <memory>
#include "color.h"
#include "image.h"

std::shared_ptr<Image> loadBMPImage(std::string filename);

#endif