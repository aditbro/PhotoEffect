#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <array>

class Histogram {
    public:
        Histogram(int pixel_range);

        void setValueCount(int pixel_value, int count);
        void addValueCount(int pixel_value);
        int getValueCount(int pixel_value);
        std::vector<int> getHistogramVector();
        int getRange();
        
        std::array<float, 3> getHistogramStatistics();
    
    private:
        int range;
        int* hist;
};

#endif