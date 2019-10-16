#include "../lib/image.h"
#include "../lib/image_loader.h"
#include "../lib/histogram.h"
#include "../lib/operators.h"
#include <iostream>
#include <vector>

int main() {
    std::string image_path = "/home/dionesius/Documents/semester-7/pengcit/PhotoEffect/src/test/resource/bmp_img.bmp";
    std::shared_ptr<Image> image = loadBMPImage(image_path);

    Histogram histogram_r(256);
    
    getChannelHistogram(image, 'r', &histogram_r);

    std::vector<int> hv;
    hv = histogram_r.getHistogramVector();
    for (int i = 0; i < histogram_r.getRange(); i++) {
        std::cout << i << ' ' << hv[i] << ' ' << histogram_r.getValueCount(i) << std::endl;
    }

    return 0;
}