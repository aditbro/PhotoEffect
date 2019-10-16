#include <memory>
#include <vector>
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