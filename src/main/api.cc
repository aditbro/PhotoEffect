#include <stdlib.h>
#include <iostream>
#include <emscripten/emscripten.h>

extern "C" {
    
    EMSCRIPTEN_KEEPALIVE
    uint8_t* create_buffer(int width, int height) {
        return (uint8_t*)malloc(width * height * 4 * sizeof(uint8_t));
    }

    EMSCRIPTEN_KEEPALIVE
    void destroy_buffer(uint8_t* p) {
        free(p);
    }

    EMSCRIPTEN_KEEPALIVE
    void write_buffer(uint8_t* buff, uint32_t loc, uint8_t val) {
        buff[loc] = val;
    }

    EMSCRIPTEN_KEEPALIVE
    uint8_t get_buffer(uint8_t* buff, uint32_t loc) {
        return buff[loc];
    }
}