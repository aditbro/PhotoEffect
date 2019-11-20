#include <iostream>
#include <memory>
#include "../lib/image_loader.h"
#include "../lib/image.h"
#include "../lib/operators.h"
#include "../lib/morph_operators.h"

int main(int argc, char** argv) {
    std::shared_ptr<Image> img(new Image('a', 6, 6));
    Color white = Color(255,255,255);
    Color black = Color(0,0,0);
    for(int i = 0; i < 6; i++) {
        for(int j = 1; j < 5; j++) {
            img->setColorAt(i, j, white);
        }
    }

    img->setColorAt(0, 0, white);

    std::shared_ptr<Image> img2 = erode(img, 3);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            img2->getColorAt(i, j).print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    img2 = dilate(img2, 3);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            img2->getColorAt(i, j).print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}