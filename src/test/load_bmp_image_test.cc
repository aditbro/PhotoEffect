#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lib/image_loader.h"

TEST(testBMPLoader, whenImageExistsAndValid) {
    std::string image_path = "resource/bmp_img.bmp";
    int width = 400;
    int height = 300;
    char type = 1;

    std::shared_ptr<Image> image = loadBMPImage(image_path);

    EXPECT_EQ(image->getHeight(), height);
    EXPECT_EQ(image->getWidth(), width);
    EXPECT_EQ(image->getType(), type);
}