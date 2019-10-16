#include "../lib/image.h"
#include "../lib/image_loader.h"
#include "../lib/histogram.h"
#include "../lib/operators.h"
#include <iostream>
#include <vector>

int main() {
    std::string image_path = "/home/dionesius/Documents/semester-7/pengcit/PhotoEffect/src/test/resource/bmp_img.bmp";
    std::shared_ptr<Image> image1 = loadBMPImage(image_path);
    std::shared_ptr<Image> image2 = loadBMPImage(image_path);
    std::shared_ptr<Image> dst(new Image(1, image1->getWidth(), image1->getHeight()));

    convertColorOperator(image1, dst);
    arithmeticOperator(image1, image2, dst, OPERATOR_PLUS);
    scalarOperator(image1, dst, 2, OPERATOR_MUL);
    booleanOperator(image1, dst, OPERATOR_NOT);
    booleanOperator(image1, image2, dst, OPERATOR_AND);

    brightnessCorrection(image1, dst, 20, 1);
    colorRemapping(image1, dst, FUNC_EXP);
    contrastStretching(image1, dst, 50, 25, 150, 200);
    intensityLevelSlicing(image1, dst, 50, 75, 200, false);
    bitLevelSlicing(image1, dst, 0);

    invertImage(image1, dst);

    return 0;
}