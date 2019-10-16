#include <iostream>
#include <memory>
#include "lib/image_loader.h"
#include "lib/image.h"
#include "lib/operators.h"

int main(int argc, char** argv) {
    std::string image_path = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/baboon24.bmp";
    std::shared_ptr<Image> image = loadBMPImage(image_path);

    std::cout << image->getType() << " " << image->getWidth() << "x" << image->getHeight() << std::endl;
    
    std::vector<int> filter = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    std::shared_ptr<Image> conv_image = convolute(image, filter);
    
    std::cout << conv_image->getType() << " " << conv_image->getWidth() << "x" << conv_image->getHeight() << std::endl;

    return 0;
}