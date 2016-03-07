#include <math.h>
#include "City.h"
#include "CSDLManagerLite.h"

City::City() {}

City::City(int x_rhs, int y_rhs) {
    x = x_rhs;
    y = y_rhs;
}

float fastSqrt(float x) {
    unsigned int i = *(unsigned int*) &x;
    i  += 127 << 23;    // adjust bias
    i >>= 1;    // approximation of square root
    return *(float*) &i;
}

float City::distTo(City c) {
    return sqrt((x-c.x)*(x-c.x) + (y-c.y)*(y-c.y));
}

void City::draw() {
    CSDLManagerLite::getInstance() -> drawRectCenter(x, y, 4, 4);
}
