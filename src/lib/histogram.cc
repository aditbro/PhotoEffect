#include <memory>
#include <vector>
#include <array>
#include <numeric>
#include <math.h>
#include "histogram.h"

Histogram::Histogram(int pixel_range) {
    this->range = pixel_range;
    this->hist = (int*) malloc(this->range * sizeof(int));
    for (int i = 0; i < this->range; i++) {
        this->hist[i] = 0;
    }
}

void Histogram::setValueCount(int pixel_value, int count) {
    this->hist[pixel_value] = count;
}

void Histogram::addValueCount(int pixel_value) {
    this->hist[pixel_value] += 1;
}

int Histogram::getValueCount(int pixel_value) {
    return this->hist[pixel_value];
}

std::vector<int> Histogram::getHistogramVector() {
    std::vector<int> hist_vector;
    for (int i = 0; i < this->range; i++) {
        hist_vector.push_back(this->hist[i]);        
    }

    return hist_vector;
}

int Histogram::getRange() {
    return this->range;
}

std::array<float, 3> Histogram::getHistogramStatistics() {
    std::array<float, 3> stats;
    std::vector<int> hist_vector = this->getHistogramVector();
    
    stats[0] = std::accumulate(hist_vector.begin(), hist_vector.end(), 0.0) / hist_vector.size();

    float sq_diff = 0.0;
    for (int i = 0; i < this->range; i++) {
        sq_diff += pow(hist_vector[i] - stats[0], 2);
    }

    stats[1] = sq_diff / this->range;
    stats[2] = (float) sqrt(stats[1]);

    return stats;
}