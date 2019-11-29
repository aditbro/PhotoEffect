#include "../lib/image.h"
#include "../lib/image_loader.h"
#include "../lib/histogram.h"
#include "../lib/operators.h"
#include "../lib/complex.h"
#include "../lib/dft.h"
#include <iostream>
#include <vector>

int main() {
    std::string image_path = "/home/dionesius/Documents/PhotoEffect/src/test/resource/w3c_home.bmp";
    std::shared_ptr<Image> image1 = loadBMPImage(image_path);
    // std::shared_ptr<Image> image2 = loadBMPImage(image_path);
    // std::shared_ptr<Image> dst(new Image(1, image1->getWidth(), image1->getHeight()));
    std::vector<std::vector<Complex>> frequency(image1->getHeight(), std::vector<Complex>(image1->getWidth()));
    frequency = fft2d(image1);

    std::shared_ptr<Image> fft_result(new Image('a', image1->getWidth(), image1->getHeight()));
    for (int i = 0; i < fft_result->getHeight(); i++)
    {
        for (int j = 0; j < fft_result->getWidth(); j++)
        {
            float scalar_value = (frequency[i][j]).getScalar();
            if (scalar_value > 255) {
                scalar_value = 255;
            }
            unsigned char color = (unsigned char) scalar_value;
            fft_result->setColorAt(i, j, Color(color, color, color));
        }
    }

    // convertColorOperator(image1, dst);
    // arithmeticOperator(image1, image2, dst, OPERATOR_PLUS);
    // scalarOperator(image1, dst, 2, OPERATOR_MUL);
    // booleanOperator(image1, dst, OPERATOR_NOT);
    // booleanOperator(image1, image2, dst, OPERATOR_AND);

    // brightnessCorrection(image1, dst, 20, 1);
    // colorRemapping(image1, dst, FUNC_EXP);
    // contrastStretching(image1, dst, 50, 25, 150, 200);
    // intensityLevelSlicing(image1, dst, 50, 75, 200, false);
    // bitLevelSlicing(image1, dst, 0);

    // histogramEqualization(image1, dst);

    // invertImage(image1, dst);

    return 0;
}