#include "morph_operators.h"

// assume kernel_dim always odd
int get_kernel_score(std::shared_ptr<Image> img, int kernel_dim, int i, int j) {
    int kernel_score = 0;
    Color white = Color((uint8_t)255,(uint8_t)255,(uint8_t)255);
    for(int is = i - (kernel_dim/2); is <= (i + kernel_dim/2); is++) {
        for(int js = j - (kernel_dim/2); js <= (j + kernel_dim/2); js++) {
            if(is >= img->getHeight() || js >= img->getWidth() || is < 0 || js < 0) {

            } else if(img->getColorAt(is, js) == white) {
                kernel_score++;
            }
        }
    }

    return kernel_score;
}

void fill_color(std::shared_ptr<Image> img, Color col, int start_i, int start_j, int size_i, int size_j) {
    if(start_i < 0) { start_i = 0; }
    if(start_j < 0) { start_j = 0; }
    for(int i = start_i; (i - start_i) < size_i && i < img->getHeight(); i++) {
        for(int j = start_j; (j - start_j) < size_j && j < img->getWidth(); j++) {
            img->setColorAt(i, j, col);
        }
    }
}

std::shared_ptr<Image> erode(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    int padding = kernel_dim / 2;
    Color white = Color((uint8_t)255,(uint8_t)255,(uint8_t)255);
    
    for(int i = 0; i < img->getHeight(); i++) {
        for(int j = 0; j < img->getWidth(); j++) {
            if(img->getColorAt(i, j) == white) {
                if(get_kernel_score(img, kernel_dim, i, j) == kernel_dim * kernel_dim) {
                    img2->setColorAt(i, j, white);
                } else {
                    img2->setColorAt(i, j, Color(0,0,0));
                }
            } else {
                img2->setColorAt(i, j, Color(0,0,0));
            }
        }
    }

    return img2;
}

std::shared_ptr<Image> dilate(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    int padding = kernel_dim / 2;
    Color white = Color((uint8_t)255,(uint8_t)255,(uint8_t)255);
    
    for(int i = 0; i < img->getHeight(); i++) {
        for(int j = 0; j < img->getWidth(); j++) {
            if(img->getColorAt(i, j) == white) {
                fill_color(img2, white, i - padding, j - padding, kernel_dim, kernel_dim);
            } else if(!(img2->getColorAt(i, j) == white)) {
                img2->setColorAt(i, j, Color(0,0,0));
            }
        }
    }

    return img2;
}

std::shared_ptr<Image> opening(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    img2 = erode(img, kernel_dim);
    img2 = dilate(img2, kernel_dim);

    return img2;
}

std::shared_ptr<Image> closing(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    img2 = dilate(img, kernel_dim);
    img2 = erode(img2, kernel_dim);

    return img2;
}

std::shared_ptr<Image> top_hat(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    img2 = opening(img2, kernel_dim);
    
    // substract img by img2
    arithmeticOperator(img, img2, img2, 1);

    return img2;
}

std::shared_ptr<Image> black_hat(std::shared_ptr<Image> img, int kernel_dim) {
    std::shared_ptr<Image> img2(new Image('a', img->getWidth(), img->getHeight()));
    img2 = closing(img2, kernel_dim);
    
    // substract img2 by img
    arithmeticOperator(img2, img, img2, 1);

    return img2;
}