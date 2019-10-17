#include <stdlib.h>
#include <iostream>
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
}