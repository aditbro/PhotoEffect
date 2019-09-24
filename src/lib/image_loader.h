#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <memory>
#include "color.h"
#include "image.h"
#include "loader_utils.h"

std::shared_ptr<Image> loadBMPImage(std::string filename);
std::shared_ptr<Image> loadRawImage(std::string filename);

#endif