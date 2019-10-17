#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <cmath>
#include <memory>
#include <typeinfo>
#include <cmath>
#include <math.h>

void getChannelHistogram(std::shared_ptr<Image> &img, int channel, Histogram* histogram) {
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Color col = img->getColorAt(i, j);
            if (channel == CHAN_R) {
                histogram->addValueCount(col.b);
            }
            else if (channel == CHAN_G) {
                histogram->addValueCount(col.g);
            }
            else if (channel == CHAN_R) {
                histogram->addValueCount(col.r);
            }
        }
    }
}

void invertImage(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            dst->setColorAt(i, j, Color(255 - col.r, 255 - col.g, 255 - col.b));
        }
    }
}

void convertColorOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_g_value = (unsigned char) round(0.299 * col.r + 0.587 * col.g + 0.144 * col.b);
            dst->setColorAt(i, j, Color(new_g_value, new_g_value, new_g_value));
        }
    }
}

void arithmeticOperator(std::shared_ptr<Image> &src1, std::shared_ptr<Image> &src2, std::shared_ptr<Image> &dst, int op) {
    if (src1->getHeight() != src2->getHeight() && src2->getHeight() != dst->getHeight() && src1->getHeight() != dst->getHeight() && 
        src1->getWidth() != src2->getWidth() && src2->getWidth() != dst->getWidth() && src1->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src1->getHeight(); i++) {
        for (int j = 0; j < src1->getWidth(); j++) {
            Color col1 = src1->getColorAt(i, j);
            Color col2 = src2->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (op == OPERATOR_PLUS) {
                new_r = col1.r + col2.r;
                new_g = col1.g + col2.g;
                new_b = col1.b + col2.b;
            }
            else if (op == OPERATOR_MIN) {
                new_r = col1.r - col2.r;
                new_g = col1.g - col2.g;
                new_b = col1.b - col2.b;
            }
            else if (op == OPERATOR_MUL) {
                new_r = (char) round(col1.r * col2.r);
                new_g = (char) round(col1.g * col2.g);
                new_b = (char) round(col1.b * col2.b);
            }
            else if (op == OPERATOR_DIV) {
                new_r = (char) round(col1.r / col2.r);
                new_g = (char) round(col1.g / col2.g);
                new_b = (char) round(col1.b / col2.b);
            }

            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void scalarOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int scalar, int op) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (op == OPERATOR_PLUS) {
                new_r = col.r + scalar;
                new_g = col.g + scalar;
                new_b = col.b + scalar;
            }
            else if (op == OPERATOR_MIN) {
                new_r = col.r - scalar;
                new_g = col.g - scalar;
                new_b = col.b - scalar;
            }
            else if (op == OPERATOR_MUL) {
                new_r = (char) round(col.r * scalar);
                new_g = (char) round(col.g * scalar);
                new_b = (char) round(col.b * scalar);
            }
            else if (op == OPERATOR_DIV) {
                new_r = (char) round(col.r / scalar);
                new_g = (char) round(col.g / scalar);
                new_b = (char) round(col.b / scalar);
            }

            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void booleanOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int op) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (op == OPERATOR_NOT) {
                new_r = !col.r * 255;
                new_g = !col.g * 255;
                new_b = !col.b * 255;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void booleanOperator(std::shared_ptr<Image> &src1, std::shared_ptr<Image> &src2, std::shared_ptr<Image> &dst, int op) {
    if (src1->getHeight() != src2->getHeight() && src2->getHeight() != dst->getHeight() && src1->getHeight() != dst->getHeight() && 
        src1->getWidth() != src2->getWidth() && src2->getWidth() != dst->getWidth() && src1->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src1->getHeight(); i++) {
        for (int j = 0; j < src1->getWidth(); j++) {
            Color col1 = src1->getColorAt(i, j);
            Color col2 = src2->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (op == OPERATOR_AND) {
                new_r = col1.r & col2.r;
                new_g = col1.g & col2.g;
                new_b = col1.b & col2.b;
            }
            else if (op == OPERATOR_OR) {
                new_r = col1.r | col2.r;
                new_g = col1.g | col2.g;
                new_b = col1.b | col2.b;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void brightnessCorrection(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int b, int a) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r = col.r * a + b;
            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            unsigned char new_g = col.g * a + b;
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            unsigned char new_b = col.b * a + b;
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }
            dst->setColorAt(i, j, Color((uint8_t)new_r, (uint8_t)new_g, (uint8_t)new_b));
        }
    }
}

void colorRemapping(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int func, int c, float gamma) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (func == FUNC_LOG) {
                new_r = (char) round(c * log((float) (1 + col.r)));
                new_g = (char) round(c * log((float) (1 + col.g)));
                new_b = (char) round(c * log((float) (1 + col.b)));
            }
            else if (func == FUNC_EXP) {
                new_r = (char) round(c * exp((float)col.r));
                new_g = (char) round(c * exp((float)col.g));
                new_b = (char) round(c * exp((float)col.b));
            }
            else if (func == FUNC_POW) {
                new_r = (char) round(c * pow((float)col.r, gamma));
                new_g = (char) round(c * pow((float)col.g, gamma));
                new_b = (char) round(c * pow((float)col.b, gamma));
            }

            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void contrastStretching(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int xa, int ya, int xb, int yb) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    float alpha = ya / xa;
    float beta = (yb - ya) / (xb - xa);
    float gamma = (255 - yb) / (255 - xb);
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (col.g < xa) {
                new_g = alpha * col.g;
            }
            else if (col.g >= xa && col.g < xb) {
                new_g = beta * (col.g - xa) + ya;
            }
            else {
                new_g = gamma * (col.g - xb) + yb;
            }

            if (col.b < xa) {
                new_b = alpha * col.b;
            }
            else if (col.b >= xa && col.b < xb) {
                new_b = beta * (col.b - xa) + ya;
            }
            else {
                new_b = gamma * (col.b - xb) + yb;
            }

            if (col.r < xa) {
                new_r = alpha * col.r;
            }
            else if (col.r >= xa && col.r < xb) {
                new_r = beta * (col.r - xa) + ya;
            }
            else {
                new_r = gamma * (col.r - xb) + yb;
            }

            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void intensityLevelSlicing(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int a, int b, char highlight_value, bool preserve_background) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;

            if (col.r >= a && col.r <= b) {
                new_r = highlight_value;
            }
            else {
                if (!preserve_background) {
                    new_r = 0;
                }
            }
            if (col.r >= a && col.r <= b) {
                new_r = highlight_value;
            }
            else {
                if (!preserve_background) {
                    new_r = 0;
                }
            }
            if (col.r >= a && col.r <= b) {
                new_r = highlight_value;
            }
            else {
                if (!preserve_background) {
                    new_r = 0;
                }
            }

            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            if (new_b < 0) {
                new_b = 0;
            }
            if (new_b > 255) {
                new_b = 255;
            }

            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
        }
    }
}

void bitLevelSlicing(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int bit_plane) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;
            new_r = ((col.r >> bit_plane) & 1) == 1 ? 255 : 0;
            new_g = ((col.g >> bit_plane) & 1) == 1 ? 255 : 0;
            new_b = ((col.b >> bit_plane) & 1) == 1 ? 255 : 0;

            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
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
                unsigned int new_r = 0;
                unsigned int new_g = 0;
                unsigned int new_b = 0;
                unsigned int k = 0;

                for (int m=-1*pad; m<=pad; m++){
                    for (int n=-1*pad; n<=pad; n++){
                        Color col = img->getColorAt(i+m,j+n);
                        new_r += (int) col.r * filter[k];
                        new_g += (int) col.g * filter[k]; 
                        new_b += (int) col.b * filter[k];
                        k++;
                    }
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
                
                std::cout << "Hasil Konvolusi" << new_r << " " << new_g << " " << new_b << std::endl;
                new_img->setColorAt(i, j, Color((unsigned char) new_r, (unsigned char) new_g, (unsigned char) new_b));
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