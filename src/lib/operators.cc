#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <memory>
#include <typeinfo>

void getChannelHistogram(std::shared_ptr<Image> &img, char channel, Histogram* histogram) {
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Color col = img->getColorAt(i, j);
            if (channel == 'b') {
                histogram->addValueCount(col.b);
            }
            else if (channel == 'g') {
                histogram->addValueCount(col.g);
            }
            else if (channel == 'r') {
                histogram->addValueCount(col.r);
            }
        }
    }
}