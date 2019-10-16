#ifndef OPERATOR_H
#define OPERATOR_H

#include "color.h"
#include "image.h"
#include "histogram.h"
#include <memory>

void getChannelHistogram(std::shared_ptr<Image> &img, char channel, Histogram* histogram);
std::shared_ptr<Image> convolute(std::shared_ptr<Image> &img, std::vector<int> filter);

#endif