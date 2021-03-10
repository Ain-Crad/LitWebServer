#include <iostream>

#include "Rio.h"

using namespace std;

int main() {
    char c;
    int cnt;
    while (rio_readn(0, &c, 1) > 0) {
        rio_written(1, &c, 1);
    }
}