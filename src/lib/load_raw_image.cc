#include "color.h"
#include "image_loader.h"
#include "loader_utils.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#define RPIX_PIXEL_ORDER_NORMAL 1
#define RPIX_PIXEL_ORDER_REVERSE 2

#define RPIX_SCANLINE_ORDER_NORMAL 1
#define RPIX_SCANLINE_ORDER_REVERSE 2

#define RPIX_INTERLEAVING_BIP 1
#define RPIX_INTERLEAVING_BIL 2
#define RPIX_INTERLEAVING_BSQ 3

void readImgColor(std::ifstream &file, std::shared_ptr<Image> &img, unsigned char pixel_order, unsigned char scanline_order, unsigned char interleaving_mode, unsigned char n_bands, unsigned char red, unsigned char green, unsigned char blue);

std::shared_ptr<Image> loadRawImage(std::string filename) {
    std::ifstream file(filename);
    if(!file) throw std::exception();

    int width = 0;
    int height = 0;
    char type = FORMAT_RAW;

    char byte;
    int loc = 0;
    int img_start_loc = 0;
    unsigned char pixel_order = 0;
    unsigned char scanline_order = 0;
    unsigned char interleaving_mode = 0;
    unsigned char n_bands = 0;
    unsigned char red_channel = 0;
    unsigned char green_channel = 0;
    unsigned char blue_channel = 0;

    while(file.get(byte)) {
        loc++;

        // file signature: bytes [0,3]
        if(loc == 1 && byte != 0x52) throw std::exception();
        if(loc == 2 && byte != 0x50) throw std::exception();
        if(loc == 3 && byte != 0x49) throw std::exception();
        if(loc == 4 && byte != 0x58) throw std::exception();

        // header length: bytes [4,7]
        if(loc == 4) {
            img_start_loc = 4 + readInt(file);
            loc += 4;
        }

        // image width: bytes [10,13]
        if(loc == 10) {
            width = readInt(file);
            loc += 4;
        }

        // image height: bytes [14,17]
        if(loc == 14) {
            height = readInt(file);
            loc += 4;
        }

        // compression type: byte 18
        if(loc == 18) {
            file >> byte;
            // ain't gonna do decompression bitch (yet)
            if(byte != 0x01) throw std::exception();
            loc++;
        }

        // pixel order: byte 19
        if(loc == 19) {
            file >> byte;
            pixel_order = (unsigned char)byte;
            loc++;
        }

        // scanline order: byte 20
        if(loc == 20) {
            file >> byte;
            scanline_order = (unsigned char)byte;
            loc++;
        }

        // interleaving mode: byte 21
        if(loc == 21) {
            file >> byte;
            interleaving_mode = (unsigned char)byte;
            loc++;
        }

        // number of bands: byte 22
        if(loc == 22) {
            file >> byte;
            n_bands = (unsigned char)byte;
            loc++;
        }
        
        // red channel band: byte 23 (also used as grayscale/BW band)
        if(loc == 23) {
            file >> byte;
            red_channel = (unsigned char)byte;
            loc++;
        }

        if(n_bands > 1) {
            // green channel band: byte 24 (also used as grayscale/BW band)
            if(loc == 24) {
                file >> byte;
                green_channel = (unsigned char)byte;
                loc++;
            }

            // blue channel band: byte 25 (also used as grayscale/BW band)
            if(loc == 25) {
                file >> byte;
                blue_channel = (unsigned char)byte;
                loc++;
            }
        }

        if(loc == img_start_loc) {
            break;
        }
    }

    std::shared_ptr<Image> img(new Image(type, width, height));
    return img;
}

void readImgColor(std::ifstream &file, std::shared_ptr<Image> &img, unsigned char pixel_order, unsigned char scanline_order, unsigned char interleaving_mode, unsigned char n_bands, unsigned char red, unsigned char green, unsigned char blue) {
    char byte;
    int loc = 0;
    int i = img->getHeight() - 1;
    int j = 0;
    char g, b, r;

    // currently only works for normal orderings and PIL interleaving with RGB sequence
    // TODO: handle reverse orderings and other interleaving modes
    while(file.get(byte)) {
        loc++;       
        r = byte;
        file >> byte;
        g = byte;
        file >> byte;
        b = byte;
        
        img->setColorAt(i, j, Color(r, g, b));
        j++;
        
        if(j >= img->getWidth()) {
            i--;
            j = 0;
        }
    }
}