#include "../lib/image_loader.h"
#include <iostream>

int main() {
    std::cout << "sampesini0" << std::endl;
    std::string image_path = "/home/dionesius/Documents/semester-7/pengcit/PhotoEffect/src/test/resource/bmp_img.bmp";
    std::cout << "sampesini1" << std::endl;
    std::shared_ptr<Image> image = loadBMPImage(image_path);
    std::cout << "sampesini2" << std::endl;

    std::cout << image->getWidth() << std::endl;
    std::cout << image->getHeight() << std::endl;

    return 0;
}