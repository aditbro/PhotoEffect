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
            image->setColorAt(i, j, Color(i*j, j+1, i+j));
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < image->getHeight(); i++) {
        for (int j = 0; j < image->getWidth(); j++) {
            Color col = image->getColorAt(i, j);
            col.print();
            std::cout << "  ";
        }
        std::cout << std::endl;
    }


    std::cout << image->getType() << " " << image->getWidth() << "x" << image->getHeight() << std::endl;
    
    std::vector<int> filter = {100, 100, 100, 100, 100, 100, 100, 100, 100};
    std::shared_ptr<Image> conv_image = convolute(image, filter);
    
    std::cout << "Conv Test" << std::endl;
    std::cout << conv_image->getType() << " " << conv_image->getWidth() << "x" << conv_image->getHeight() << std::endl;
    for (int i = 0; i < conv_image->getHeight(); i++) {
        for (int j = 0; j < conv_image->getWidth(); j++) {
            Color col = conv_image->getColorAt(i, j);
            col.print();
            std::cout << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << "Median Test" << std::endl;
    std::shared_ptr<Image> med_image = median_convolute(image, 3);
    for (int i = 0; i < med_image->getHeight(); i++) {
        for (int j = 0; j < med_image->getWidth(); j++) {
            Color col = med_image->getColorAt(i, j);
            col.print();
            std::cout << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << "    " << std::endl;
    std::shared_ptr<Image> high_image = high_boost(image, 9);
    for (int i = 0; i < high_image->getHeight(); i++) {
        for (int j = 0; j < high_image->getWidth(); j++) {
            Color col = high_image->getColorAt(i, j);
            col.print();
            std::cout << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << "Coba Geometri" << std::endl;
    std::shared_ptr<Image> transformed_image = rotate(image, -90);
    for (int i = 0; i < transformed_image->getHeight(); i++) {
        for (int j = 0; j < transformed_image->getWidth(); j++) {
            Color col = transformed_image->getColorAt(i, j);
            col.print();
            std::cout << "  ";
        }
        std::cout << std::endl;
    }
    return 0;
}