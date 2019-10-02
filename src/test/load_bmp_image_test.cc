#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lib/image_loader.h"

TEST(testBMPLoader, whenGreenImageExistsAndValid) {
    std::string image_path = "/Users/pt.gojekindonesia/Documents/PhotoEffect/src/test/resource/german_flag.bmp";
    int width = 1280;
    int height = 768;
    char type = 1;
    Color middleColor = Color(0, 153, 51);

    std::shared_ptr<Image> image = loadBMPImage(image_path);

    EXPECT_EQ(height, image->getHeight());
    EXPECT_EQ(width, image->getWidth());
    EXPECT_EQ(type, image->getType());
    EXPECT_TRUE(middleColor == image->getColorAt(height/2, width/2));
}