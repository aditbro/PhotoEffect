#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include "../lib/image.h"
#include "../lib/operators.h"
#include "../lib/morph_operators.h"
#include "../lib/plate_recognizer.h"
#include <emscripten/emscripten.h>

extern "C" {
    std::shared_ptr<Image> img;

    void render_img(std::shared_ptr<Image> img2) {
        for(int i = 0; i < img2->getHeight(); i++) {
            for(int j = 0; j < img2->getWidth(); j++) {
                img->setColorAt(i, j, img2->getColorAt(i, j));
            }
        }
    }

    EMSCRIPTEN_KEEPALIVE
    uint8_t* create_image(int width, int height) {
        img = std::shared_ptr<Image>(new Image(1, width, height));
        return (uint8_t*)img->getVectorBegin();
    }

    EMSCRIPTEN_KEEPALIVE
    void image_brightness_correction(int alpha, int constant) {
        brightnessCorrection(img, img, constant, alpha);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_invert() {
        invertImage(img, img);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_convert_color() {
        convertColorOperator(img, img);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_scalar_operator(char operation, int scalar) {
        scalarOperator(img, img, scalar, operation);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_scalar_boolean_operator(char operation) {
        booleanOperator(img, img, operation);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_color_remapping(int func, int c, float gamma) {
        std::cout << gamma << std::endl;
        colorRemapping(img, img, func, c, gamma);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_contrast_stretching(int xa, int ya, int xb, int yb) {
        contrastStretching(img, img, xa, ya, xb, yb);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_intensity_slice(int a, int b, char highlight_value, bool preserve_background) {
        intensityLevelSlicing(img, img, a, b, highlight_value, preserve_background);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_bit_slice(int bit_plane) {
        bitLevelSlicing(img, img, bit_plane);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_edge_detect(int threshold) {
        std::shared_ptr<Image> img2 = gaussian_blur(img);
        img2 = gaussian_blur(img2);
        img2 = sobel(img2, threshold);

        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_histogram_normalization() {
        histogramEqualization(img, img);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_erode(int kernel_dim) {
        std::shared_ptr<Image> img2 = erode(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_dilate(int kernel_dim) {
        std::shared_ptr<Image> img2 = dilate(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_opening(int kernel_dim) {
        std::shared_ptr<Image> img2 = opening(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_closing(int kernel_dim) {
        std::shared_ptr<Image> img2 = closing(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_top_hat(int kernel_dim) {
        std::shared_ptr<Image> img2 = top_hat(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_black_hat(int kernel_dim) {
        std::shared_ptr<Image> img2 = black_hat(img, kernel_dim);
        render_img(img2);
    }

    EMSCRIPTEN_KEEPALIVE
    void image_find_char() {
        Color col = Color((uint8_t)255, (uint8_t)0, (uint8_t)255);
        std::vector<std::vector<int>> char_box = get_possible_chars_box(img);
        std::vector<int> plate_box = get_plate_region_of_interest(char_box);

        draw_region_of_interest(img, plate_box, col);
    }
}