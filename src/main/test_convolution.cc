#include <iostream>
#include <memory>
#include "lib/image_loader.h"
#include "lib/image.h"
#include "lib/operators.h"

int main(int argc, char** argv) {
    std::string image_path = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/baboon24.bmp";
    // std::shared_ptr<Image> image = new Image('a',4,4);
    std::shared_ptr<Image> image(new Image('a', 4, 4));

    for (int i = 0; i < image->getHeight(); i++) {
        for (int j = 0; j < image->getWidth(); j++) {
            image->setColorAt(i, j, Color(i, j, i));
        }
    }

    for (int i = 0; i < image->getHeight(); i++) {
        for (int j = 0; j < image->getWidth(); j++) {
            Color col = image->getColorAt(i, j);
            col.print();
        }
    }


    std::cout << image->getType() << " " << image->getWidth() << "x" << image->getHeight() << std::endl;
    
    std::vector<int> filter = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::shared_ptr<Image> conv_image = convolute(image, filter);
    
    std::cout << conv_image->getType() << " " << conv_image->getWidth() << "x" << conv_image->getHeight() << std::endl;

    for (int i = 0; i < conv_image->getHeight(); i++) {
        for (int j = 0; j < conv_image->getWidth(); j++) {
            Color col = conv_image->getColorAt(i, j);
            col.print();
        }
    }
    return 0;
}