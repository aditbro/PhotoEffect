#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>

class Histogram {
    public:
        Histogram(int pixel_range);

        void setValueCount(int pixel_value, int count);
        void addValueCount(int pixel_value);
        int getValueCount(int pixel_value);
        std::vector<int> getHistogramVector();
        int getRange();
    
    private:
        int range;
        int* hist;
};

#endif