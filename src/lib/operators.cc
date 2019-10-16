#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <cmath>
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

std::shared_ptr<Image> convolute(std::shared_ptr<Image> &img, std::vector<int> filter) {
    int width =  img->getWidth();
    int height = img->getHeight();
    int filter_size = (int) sqrt(filter.size());
    int pad = filter_size/2;

    std::shared_ptr<Image> new_img(new Image(img->getType(), width, height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < pad || j < pad || i >= height-pad || j >= width-pad) {
                new_img->setColorAt(i, j, img->getColorAt(i, j));
            } else {
                int new_r = 0;
                int new_g = 0;
                int new_b = 0;
                int k = 0;

                for (int m=-1*pad; m<=pad; m++){
                    for (int n=-1*pad; n<=pad; n++){
                        Color col = img->getColorAt(i+m,j+n);
                        new_r += (int) col.r * filter[k];
                        new_g += (int) col.g * filter[k]; 
                        new_b += (int) col.b * filter[k];
                        k++;
                    }

                    if (new_r > 255){
                        new_r = 255;
                    } else if (new_r < 0) {
                        new_r = 0;
                    }

                    if (new_g > 255){
                        new_g = 255;
                    } else if (new_r < 0) {
                        new_g = 0;
                    }

                    if (new_b > 255){
                        new_b = 255;
                    } else if (new_r < 0) {
                        new_b = 0;
                    }

                    new_img->setColorAt(i, j, Color((unsigned char) new_r, (unsigned char) new_g, (unsigned char) new_b));
                }
                

            }

            // Color col = img->getColorAt(i, j);
            // if (channel == 'b') {
            //     histogram->addValueCount(col.b);
            // }
            // else if (channel == 'g') {
            //     histogram->addValueCount(col.g);
            // }
            // else if (channel == 'r') {
            //     histogram->addValueCount(col.r);
            // }
        }
    }
    return new_img;
}