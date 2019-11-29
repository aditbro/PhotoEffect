#ifndef OCR_H
#define OCR_H

#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <memory>
#include <vector>

// Utility
double matchImage(std::shared_ptr<Image> &img, std::shared_ptr<Image> &img2);
char recognize_character(std::shared_ptr<Image> &img);

#endif