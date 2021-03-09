#include <iostream>

#include "Rio.h"

using namespace std;

int main() {
    char chs[4];
    // while (rio_readn(0, &c, 4) > 0) {
    //     rio_written(1, &c, 2);
    // }
    while (read(0, chs, 4) > 0) {
        write(1, chs, 4);
    }
}