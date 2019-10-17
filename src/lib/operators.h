#ifndef OPERATOR_H
#define OPERATOR_H

#include "color.h"
#include "image.h"
#include "histogram.h"
#include <memory>

#define OPERATOR_PLUS 0
#define OPERATOR_MIN 1
#define OPERATOR_MUL 2
#define OPERATOR_DIV 3
#define OPERATOR_NOT 4
#define OPERATOR_AND 5
#define OPERATOR_OR 6

#define FUNC_NEGATIVE 0
#define FUNC_LOG 1
#define FUNC_EXP 2
#define FUNC_POW 3

#define CHAN_R 0
#define CHAN_G 1
#define CHAN_B 2
#define CHAN_ALL 3

#define HIGH_PASS_FILTER_1 0
#define HIGH_PASS_FILTER_2 1
#define HIGH_PASS_FILTER_3 2

#define GRADIENT 0
#define SECOND_DERIVATION 1
#define LAPLACE 2
#define LOG 3
#define SOBEL 4
#define PREWITT 5
#define ROBERTS 6
#define CANNY 7

// Utility
void getChannelHistogram(std::shared_ptr<Image> &img, int channel, Histogram* histogram);

// Channel Operators
void convertColorOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst);
void arithmeticOperator(std::shared_ptr<Image> &src1, std::shared_ptr<Image> &src2, std::shared_ptr<Image> &dst, int op);
void scalarOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int scalar, int op);
void booleanOperator(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int op);
void booleanOperator(std::shared_ptr<Image> &src1, std::shared_ptr<Image> &src2, std::shared_ptr<Image> &dst, int op);

// Image Correction
void brightnessCorrection(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int b, int a = 1);
void colorRemapping(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int func, int c = 1, float gamma = 0.0);
void contrastStretching(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int xa, int ya, int xb, int yb);
void intensityLevelSlicing(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int a, int b, char highlight_value, bool preserve_background = true);
void bitLevelSlicing(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst, int bit_plane);

// Image Transformation
void invertImage(std::shared_ptr<Image> &src, std::shared_ptr<Image> &dst);
void translateImage();
void rotateImage();
void flipImage();

// Convolution
std::shared_ptr<Image> convolute(std::shared_ptr<Image> &img, std::vector<int> filter);
std::shared_ptr<Image> median_convolute(std::shared_ptr<Image> &img, int filter_size);
std::shared_ptr<Image> low_pass_convolute(std::shared_ptr<Image> &img, int filter_size);
std::shared_ptr<Image> high_pass_convolute(std::shared_ptr<Image> &img, int filter);
std::shared_ptr<Image> high_boost(std::shared_ptr<Image> &img, int alpha);
// std::shared_ptr<Image> edge_detection(std::shared_ptr<Image> &img, int type);
std::shared_ptr<Image> laplace(std::shared_ptr<Image> &img);
std::shared_ptr<Image> gaussian_laplace(std::shared_ptr<Image> &img);
std::shared_ptr<Image> sobel(std::shared_ptr<Image> &img, int c);
std::shared_ptr<Image> prewitt(std::shared_ptr<Image> &img);

#endif