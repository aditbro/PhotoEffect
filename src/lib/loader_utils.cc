#include "loader_utils.h"
#include <fstream>

int readInt(std::ifstream &file) {
    char *integer = (char*) malloc(4);
    for(int i = 0; i < 4; i++) {
        char bytes;
        file >> bytes;
        integer[i] = bytes;
    }

    return *(int*) integer;
}