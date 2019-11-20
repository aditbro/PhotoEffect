#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <memory>

std::shared_ptr<Image> erode(std::shared_ptr<Image> img, int kernel_dim);
std::shared_ptr<Image> dilate(std::shared_ptr<Image> img, int kernel_dim);

std::shared_ptr<Image> opening(std::shared_ptr<Image> img, int kernel_dim);
std::shared_ptr<Image> closing(std::shared_ptr<Image> img, int kernel_dim);

std::shared_ptr<Image> top_hat(std::shared_ptr<Image> img, int kernel_dim);
std::shared_ptr<Image> black_hat(std::shared_ptr<Image> img, int kernel_dim);