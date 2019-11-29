#include "color.h"
#include "image.h"
#include "histogram.h"
#include "operators.h"
#include "image_loader.h"
#include <memory>
#include <vector>
#include <cmath>


// Utility
double matchImage(std::shared_ptr<Image> &img, std::shared_ptr<Image> &img2){
    int match_count = 0;

    img = convertToBiner(img,128);
    img2 = convertToBiner(img2,128);


    double x_scale =img2->getWidth() / (double) img->getWidth();
    double y_scale =img2->getHeight() / (double) img->getHeight();
    // std::cout << x_scale << std::endl;
    // std::cout << y_scale << std::endl;
    for (int i = 0; i < img->getHeight(); i++) {
        for (int j = 0; j < img->getWidth(); j++) {
            Color col1 = img->getColorAt(i, j);

            int i2 = (int) floor(i * x_scale);
            int j2 = (int) floor(j * y_scale);

            Color col2 = img2->getColorAt(i2, j2);
            // std::cout << "col1" << std::endl;
            // col1.print();
            // std::cout << "col2" << std::endl;
            // col2.print();

            if(col1 == col2){
                // std::cout << "oke";
                match_count++;
            }
        }
    }
    // std::cout << match_count << std::endl;
    return match_count/(double)(img->getHeight()*img->getWidth());
}

char recognize_character(std::shared_ptr<Image> &img){
    std::vector<char> possible_char = {'A','B','C','D','G','J','K','M','N','O','P','Q','R','S','U','V','W','X','Y','Z','0','2','3','4','5','6','7','8','9'};
    std::string char_folder = "/home/cha/Informatika/Pengcit/PhotoEffect/src/test/resource/char/";
    double max_similarity = -1;
    char result = '-';

    for(std::size_t i=0; i<possible_char.size(); ++i) {
        std::string char_path = char_folder + possible_char[i] + ".bmp";
        std::shared_ptr<Image> char_img = loadBMPImage(char_path);
        double similarity = matchImage(img, char_img);

        if (similarity > max_similarity){
            max_similarity = similarity;
            result = possible_char[i];
        }
        // std::cout << possible_char[i] << '\n'; 
    }

    return result;
}

