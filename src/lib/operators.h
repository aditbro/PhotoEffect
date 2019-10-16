#ifndef OPERATOR_H
#define OPERATOR_H

#include "color.h"
#include "image.h"
#include "histogram.h"
#include <memory>

void getChannelHistogram(std::shared_ptr<Image> &img, char channel, Histogram* histogram);

#endif