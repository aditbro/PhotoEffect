#include "plate_recognizer.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <map>
#include <stdlib.h>
#include <cmath>

std::vector<int> get_bounding_box(std::shared_ptr<Image> img, std::vector<bool> &visited, int is, int js) {
    Color white = Color((uint8_t)255,(uint8_t)255,(uint8_t)255);
    std::queue<std::pair<int, int>> coordinate_q;
    int leftmost = js;
    int rightmost = js;
    int topmost = is;
    int bottom = is;

    coordinate_q.push(std::make_pair(is, js));
    while(!coordinate_q.empty()) {
        std::pair<int, int> current_coord = coordinate_q.front();
        coordinate_q.pop();

        int curr_i = current_coord.first;
        int curr_j = current_coord.second;

        topmost = std::min(topmost, current_coord.first);
        bottom = std::max(bottom, current_coord.first);
        leftmost = std::min(leftmost, current_coord.second);
        rightmost = std::max(rightmost, current_coord.second);

        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                int now_i = (curr_i + i);
                int now_j = (curr_j + j);
                if(now_i >= 0 && now_i < img->getHeight() && now_j >= 0 && now_j < img->getWidth()) {
                    if(!visited[now_i * img->getWidth() + now_j] && img->getColorAt(now_i, now_j) == white) {
                        coordinate_q.push(std::make_pair(now_i, now_j));
                        visited[now_i * img->getWidth() + now_j] = true;
                    }
                }
            }
        }

    }

    std::vector<int> retval = {topmost, rightmost, bottom, leftmost};
    return retval;
}

float get_box_ratio(std::vector<int> box) {
    float divisor = (box[1] - box[3]);
    float divisee = (box[2] - box[0]);

    if(divisor == 0) {
        return 0;
    } else {
        return divisee / divisor;
    }
}

float get_box_height(std::vector<int> box) {
    return box[2] - box[0];
}

std::vector<std::vector<int>> get_possible_chars_box(std::shared_ptr<Image> img) {
    Color white = Color((uint8_t)255,(uint8_t)255,(uint8_t)255);
    std::vector<bool> visited;
    std::vector<std::vector<int>> char_boxes;
    float min_aspect_ratio = 1;
    float max_aspect_ratio = 10;
    float max_box_height_ratio = 50;

    visited.reserve(img->getHeight() * img->getWidth());
    for(int i = 0; i < img->getHeight(); i++) {
        for(int j = 0; j < img->getHeight(); j++) {
            visited[i * img->getWidth() + j] = false;
        }
    }

    for(int i = 0; i < img->getHeight(); i++) {
        for(int j = 0; j < img->getWidth(); j++) {
            if(!visited[i * img->getWidth() + j] && img->getColorAt(i, j) == white) {
                std::vector<int> bound_box = get_bounding_box(img, visited, i, j);
                float box_ratio = get_box_ratio(bound_box);
                float box_height_ratio = img->getHeight() / get_box_height(bound_box);

                if(box_ratio >= min_aspect_ratio && box_ratio <= max_aspect_ratio && box_height_ratio < max_box_height_ratio) {
                    char_boxes.push_back(bound_box);
                }
            }
        }
    }

    return char_boxes;
}

void draw_region_of_interest(std::shared_ptr<Image> img, std::vector<int> boxes, Color col) {
    // vector box format {topmost, rightmost, bottom, leftmost}
    for(int i = boxes[0]; i <= boxes[2]; i++) {
        if(i == boxes[0] || i == boxes[2]) {
            for(int j = boxes[3]; j <= boxes[1]; j++) {
                img->setColorAt(i, j, col);
            }
        } else {
            img->setColorAt(i, boxes[1], col);
            img->setColorAt(i, boxes[3], col);
        }
    }
}

std::vector<int> get_plate_region_of_interest(std::vector<std::vector<int>> bounding_boxes) {
    std::vector<std::pair<int, int>> box_avg;
    float max_i_delta = 5;
    float max_j_delta = 500;
    float max_height_delta = 5;
    int min_char_in_line = 3;

    for(int i = 0; i < bounding_boxes.size(); i++) {
        std::vector<int> box = bounding_boxes[i];
        int height = (box[2] + box[0])/2;
        int width = (box[1] + box[3])/2;
        box_avg.push_back(std::make_pair(height, width));
    }

    std::vector<int> dist_mat;
    std::vector<int> inline_char(bounding_boxes.size(), 0);
    dist_mat.reserve(bounding_boxes.size() * bounding_boxes.size());

    for(int i = 0; i < bounding_boxes.size(); i++) {
        for(int j = 0; j < bounding_boxes.size(); j++) {
            std::vector<int> box1 = bounding_boxes[i];
            std::vector<int> box2 = bounding_boxes[j];
            int height_diff = std::abs((box1[2] - box1[0]) - (box2[2] - box2[0]));
            int i_diff = std::abs(box_avg[i].first - box_avg[j].first);
            int j_diff = std::abs(box_avg[i].second - box_avg[j].second);

            if(i_diff <= max_i_delta
               && j_diff <= max_j_delta
               && height_diff <= max_height_delta) {
                std::cout << i_diff << " " << max_i_delta << std::endl;
                std::cout << j_diff << " " << max_j_delta << std::endl;
                std::cout << height_diff << " " << max_height_delta << std::endl;
                std::cout << std::endl;
                std::cout << std::endl;
                dist_mat[i * bounding_boxes.size() + j] = i_diff + j_diff;
                dist_mat[j * bounding_boxes.size() + i] = i_diff + j_diff;
                inline_char[i] += 1;
            } else {
                dist_mat[i * bounding_boxes.size() + j] = -1;
                dist_mat[j * bounding_boxes.size() + i] = -1;
            }
        }
    }

    int max_i = std::max_element(inline_char.begin(),inline_char.end()) - inline_char.begin();

    int leftmost = bounding_boxes[max_i][3];
    int rightmost = bounding_boxes[max_i][1];
    int topmost = bounding_boxes[max_i][0];
    int bottom = bounding_boxes[max_i][2];

    for(int j = 0; j < bounding_boxes.size(); j++) {
        if(dist_mat[max_i * bounding_boxes.size() + j] > -1) {
            leftmost = std::min(leftmost, bounding_boxes[j][3]);
            rightmost = std::max(rightmost, bounding_boxes[j][1]);
            topmost = std::min(topmost, bounding_boxes[j][0]);
            bottom = std::max(bottom, bounding_boxes[j][2]);
        }
    }

    std::cout << topmost << " " << rightmost << " " << bottom << " " << leftmost << std::endl;

    std::vector<int> result = {topmost, rightmost, bottom, leftmost};
    return result;
}