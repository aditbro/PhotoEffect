#include "color.h"
#include "image_loader.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

int readInt(std::ifstream &file);
void readImgColor(std::ifstream &file, std::shared_ptr<Image> &img);

std::shared_ptr<Image> loadBMPImage(std::string filename) {
    std::ifstream file(filename);
    if(!file) throw std::exception();
    
    int width = 0;
    int height = 0;
    char type = 1;

    char byte;
    int loc = 0;
    int img_start_loc = 0;

    while(file.get(byte)) {
        loc++;
        if(loc + 1 == 11) {
            img_start_loc = readInt(file);
            loc += 4;
        }

        if(loc + 1 == 19) {
            width = readInt(file);
            loc += 4;
        }

        if(loc + 1 == 23) {
            height = readInt(file);
            loc += 4;
        }

        if(loc + 1 == img_start_loc) {
            break;
        }
    }

    std::shared_ptr<Image> img(new Image(type, width, height));
    readImgColor(file, img);
    return img;
}

int readInt(std::ifstream &file) {
    char *integer = (char*) malloc(4);
    for(int i = 0; i < 4; i++) {
        char bytes;
        file >> bytes;
        integer[i] = bytes;
    }

    return *(int*) integer;
}

void readImgColor(std::ifstream &file, std::shared_ptr<Image> &img) {
    char byte;
    int loc = 0;
    int i = img->getHeight() - 1;
    int j = 0;
    char g, b, r;

    while(file.get(byte)) {
        loc++;       
        b = byte;
        file >> byte;
        g = byte;
        file >> byte;
        r = byte;
        
        img->setColorAt(i, j, Color(r, g, b));
        j++;
        
        if(j >= img->getWidth()) {
            i--;
            j = 0;
        }
    }
}