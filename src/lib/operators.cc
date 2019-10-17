#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <cmath>
#include <memory>
#include <typeinfo>
#include <cmath>
#include <algorithm>
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

<<<<<<< HEAD

=======
>>>>>>> a55cc80e08b2d0c5ad18bd1bca91b4c05f091332
void invertImage(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst) {
    if (src->getHeight() != dst->getHeight() && src->getWidth() != dst->getWidth()) throw std::exception();
    for (int i = 0; i < src->getHeight(); i++) {
        for (int j = 0; j < src->getWidth(); j++) {
            Color col = src->getColorAt(i, j);
            unsigned char new_r, new_g, new_b;
            new_r = 255 - col.r;
            new_g = 255 - col.g;
            new_b = 255 - col.b;
            dst->setColorAt(i, j, Color(new_r, new_g, new_b));
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
            unsigned int new_r, new_g, new_b;

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
                new_r = (unsigned char) round(col1.r * col2.r);
                new_g = (unsigned char) round(col1.g * col2.g);
                new_b = (unsigned char) round(col1.b * col2.b);
            }
            else if (op == OPERATOR_DIV) {
                new_r = (unsigned char) round(col1.r / col2.r);
                new_g = (unsigned char) round(col1.g / col2.g);
                new_b = (unsigned char) round(col1.b / col2.b);
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
            unsigned int new_r, new_g, new_b;

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
                new_r = (unsigned int) round(col.r * scalar);
                new_g = (unsigned int) round(col.g * scalar);
                new_b = (unsigned int) round(col.b * scalar);
            }
            else if (op == OPERATOR_DIV) {
                new_r = (unsigned int) round(col.r / scalar);
                new_g = (unsigned int) round(col.g / scalar);
                new_b = (unsigned int) round(col.b / scalar);
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
            unsigned int new_r = col.r * a + b;
            if (new_r < 0) {
                new_r = 0;
            }
            if (new_r > 255) {
                new_r = 255;
            }
            int new_g = col.g * a + b;
            if (new_g < 0) {
                new_g = 0;
            }
            if (new_g > 255) {
                new_g = 255;
            }
            int new_b = col.b * a + b;
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
                new_r = (unsigned char) round(c * log((float) (1 + col.r)));
                new_g = (unsigned char) round(c * log((float) (1 + col.g)));
                new_b = (unsigned char) round(c * log((float) (1 + col.b)));
            }
            else if (func == FUNC_EXP) {
                new_r = (unsigned char) round(c * exp((float)col.r));
                new_g = (unsigned char) round(c * exp((float)col.g));
                new_b = (unsigned char) round(c * exp((float)col.b));
            }
            else if (func == FUNC_POW) {
                new_r = (unsigned char) round(c * pow((float)col.r, gamma));
                new_g = (unsigned char) round(c * pow((float)col.g, gamma));
                new_b = (unsigned char) round(c * pow((float)col.b, gamma));
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
            if (col.g >= a && col.g <= b) {
                new_r = highlight_value;
            }
            else {
                if (!preserve_background) {
                    new_g = 0;
                }
            }
            if (col.b >= a && col.b <= b) {
                new_b = highlight_value;
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
        }
    }
    return new_img;
}

unsigned char find_median(std::vector<unsigned char> vec){
    size_t size = vec.size();

    if (size == 0) {
        return 0;  // Undefined, really.
    } else {
        std::sort(vec.begin(), vec.end());
        if (size % 2 == 0){
            return (unsigned char) ((int) vec[size / 2 - 1] + (int)vec[size / 2]) / 2;
        } else {
            return vec[size / 2];
        }
    }
}

std::shared_ptr<Image> low_pass_convolute(std::shared_ptr<Image> &img, int filter_size) {
    int width =  img->getWidth();
    int height = img->getHeight();
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

                for (int m=-1*pad; m<=pad; m++){
                    for (int n=-1*pad; n<=pad; n++){
                        Color col = img->getColorAt(i+m,j+n);
                        new_r += (int) col.r;
                        new_g += (int) col.g; 
                        new_b += (int) col.b;
                    }
                }

                new_r = floor(new_r/pow(filter_size,2));
                new_g = floor(new_r/pow(filter_size,2));
                new_b = floor(new_r/pow(filter_size,2));
                
                new_img->setColorAt(i, j, Color((unsigned char) new_r, (unsigned char) new_g, (unsigned char) new_b));
            }
        }
    }
    return new_img;
}

std::shared_ptr<Image> median_convolute(std::shared_ptr<Image> &img, int filter_size) {
    int width =  img->getWidth();
    int height = img->getHeight();
    int pad = filter_size/2;

    std::shared_ptr<Image> new_img(new Image(img->getType(), width, height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < pad || j < pad || i >= height-pad || j >= width-pad) {
                new_img->setColorAt(i, j, img->getColorAt(i, j));
            } else {
                std::vector<unsigned char> r_vec;
                std::vector<unsigned char> g_vec;
                std::vector<unsigned char> b_vec;

                for (int m=-1*pad; m<=pad; m++){
                    for (int n=-1*pad; n<=pad; n++){
                        Color col = img->getColorAt(i+m,j+n);
                        r_vec.push_back(col.r);
                        g_vec.push_back(col.g);
                        b_vec.push_back(col.b);
                    }
                }
                
                new_img->setColorAt(i, j, Color(find_median(r_vec),find_median(g_vec), find_median(b_vec)));
            }
        }
    }
    return new_img;
}

std::shared_ptr<Image> high_pass_convolute(std::shared_ptr<Image> &img, int filter) {
    std::vector <int> vec_filter;
    if (filter == HIGH_PASS_FILTER_1){
        vec_filter = {-1,-1,-1,-1,8,-1,-1,-1,-1};
    } else if (filter == HIGH_PASS_FILTER_2){
        vec_filter = {-1,-1,-1,-1,9,-1,-1,-1,-1};
    } else if (filter == HIGH_PASS_FILTER_3){
        vec_filter = {1,-2,1,-2,4,-2,1,-2,1};
    }
    
    std::shared_ptr<Image> new_img = convolute(img, vec_filter);
    return new_img;
}

std::shared_ptr<Image> unsharp_mask(std::shared_ptr<Image> &img, int filter_size) { 
    std::shared_ptr<Image> lowpass_img = low_pass_convolute(img, filter_size);
    
    std::shared_ptr<Image> highpass_img(new Image(img->getType(), img->getWidth(), img->getHeight()));
    arithmeticOperator(img, lowpass_img, highpass_img, OPERATOR_MIN);

    std::shared_ptr<Image> sharpen_img(new Image(img->getType(), img->getWidth(), img->getHeight()));
    arithmeticOperator(img, highpass_img, sharpen_img, OPERATOR_PLUS);
    
    return sharpen_img;
}

std::shared_ptr<Image> high_boost(std::shared_ptr<Image> &img, int alpha){
    std::vector <int> vec_filter = {-1,-1,-1,-1, 9*alpha-1,-1,-1,-1,-1};
    std::shared_ptr<Image> boosted_img = convolute(img, vec_filter);
    
    return boosted_img;
}

std::shared_ptr<Image> laplace(std::shared_ptr<Image> &img, int type){
    std::vector <int> vec_filter = {0,1,0,1,-4,1,0,1,0};
    std::shared_ptr<Image> new_img = convolute(img, vec_filter);
    return new_img;          
}

std::shared_ptr<Image> gaussian_laplace(std::shared_ptr<Image> &img, int type){
    std::vector <int> vec_filter = {0,0,-1,0,0,
                                    0,-1,-2,-1,0,
                                    -1,-2,16,-2,-1,
                                    0,-2,-2,-1,0,
                                    0,0,-1,0,0};
    std::shared_ptr<Image> new_img = convolute(img, vec_filter);
    return new_img;    
}

std::shared_ptr<Image> sobel(std::shared_ptr<Image> &img, int c) {
    int width =  img->getWidth();
    int height = img->getHeight();
    std::vector <int> vec_filter_x = {-1,0,1,-1*c,0,c,-1,0,1};
    std::vector <int> vec_filter_y = {1,c,1,0,0,0,-1,-1*c,-1};

    int filter_size = (int) sqrt(vec_filter_x.size());
    int pad = filter_size/2;
    

    std::shared_ptr<Image> new_img(new Image(img->getType(), width, height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i < pad || j < pad || i >= height-pad || j >= width-pad) {
                new_img->setColorAt(i, j, img->getColorAt(i, j));
            } else {
                int rx = 0;
                int gx = 0;
                int bx = 0;
                int ry = 0;
                int gy = 0;
                int by = 0;
                int k = 0;

                for (int m=-1*pad; m<=pad; m++){
                    for (int n=-1*pad; n<=pad; n++){
                        Color col = img->getColorAt(i+m,j+n);
                        rx += (int) col.r * vec_filter_x[k];
                        gx += (int) col.g * vec_filter_x[k]; 
                        bx += (int) col.b * vec_filter_x[k];

                        ry += (int) col.r * vec_filter_y[k];
                        gy += (int) col.g * vec_filter_y[k]; 
                        by += (int) col.b * vec_filter_y[k];
                        k++;
                    }
                }

                int new_r = abs(rx) + abs(ry);
                int new_g = abs(gx) + abs(gy);
                int new_b = abs(bx) + abs(by);

                if (new_r > 255){
                    new_r = 255;
                }

                if (new_g > 255){
                    new_g = 255;
                }

                if (new_b > 255){
                    new_b = 255;
                } 
                
                std::cout << "Hasil Konvolusi" << new_r << " " << new_g << " " << new_b << std::endl;
                new_img->setColorAt(i, j, Color((unsigned char) new_r, (unsigned char) new_g, (unsigned char) new_b));
            }
        }
    }
    return new_img;
}

std::shared_ptr<Image> prewitt(std::shared_ptr<Image> &img){
    std::shared_ptr<Image> new_img = sobel(img, 1);
    return new_img;          
}