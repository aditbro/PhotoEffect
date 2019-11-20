#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include <memory>
#include <vector>

std::vector<std::vector<int>> get_possible_chars_box(std::shared_ptr<Image> img);
std::vector<int> get_plate_region_of_interest(std::vector<std::vector<int>> bounding_boxes);
void draw_region_of_interest(std::shared_ptr<Image> img, std::vector<int> boxes, Color col);
