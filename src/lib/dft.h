#ifndef DFT_H
#define DFT_H

#include <iostream>
#include "image.h"

std::vector<std::vector<Complex>> fft2d(const std::shared_ptr<Image> &img);
std::shared_ptr<Image> ifft2d(const std::vector<std::vector<Complex>> &frequencies);

#endif