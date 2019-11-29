#include <iostream>
#include <memory>
#include "lib/image_loader.h"
#include "lib/image.h"
#include "lib/operators.h"
#include "lib/ocr.h"


int main(int argc, char** argv) {
    std::string image_path = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/char/I.bmp";

    std::string image_path2 = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/char/I.bmp";
    std::string image_path3 = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/char/Y.bmp";

    std::shared_ptr<Image> image1 = loadBMPImage(image_path);
    std::shared_ptr<Image> image2 = loadBMPImage(image_path3);
    // std::shared_ptr<Image> image3 = loadBMPImage(image_path2);
    // std::shared_ptr<Image> image4 = loadBMPImage(image_path3);


    // std::cout << matchImage(image1,image2) << std::endl;
    // std::cout << matchImage(image1,image3) << std::endl;
    // std::cout << matchImage(image3,image4) << std::endl;
    // std::cout << matchImage(image1,image4) << std::endl;

    std::cout <<  "Answer : " << recognize_character(image1) << std::endl;
    std::cout <<  "Answer : " << recognize_character(image2) << std::endl;
   

    return 0;
}