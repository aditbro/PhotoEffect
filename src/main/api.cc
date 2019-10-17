#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include "../lib/image.h"
#include "../lib/operators.h"
#include <emscripten/emscripten.h>

extern "C" {
    std::shared_ptr<Image> img;

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
    void image_edge_detect() {
        std::vector<int> filter = {0,1,0,1,-4,1,0,1,0};
        std::shared_ptr<Image> img2 = convolute(img, filter);

        for(int i = 0; i < img2->getHeight(); i++) {
            for(int j = 0; j < img2->getWidth(); j++) {
                img->setColorAt(i, j, img2->getColorAt(i, j));
            }
        }
    }
}