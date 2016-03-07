#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <unordered_map>

#include "City.h"
#include "defs.h"

class Tour {
public:
    Tour();

    City cities[NUM_CITIES];
    double dist;

    double getDist();
    void updateCities(City[]);

    void swapCities(int, int);
    double getUpdatedDistWhenSwappedCities(int old_energy, int a, int b);

    void twoOptSwap(int, int);
    double getUpdatedDistWhenTwoOptSwap(int old_energy, int a, int b);
    bool twoOptSwapIsBeneficial(int, int);

    void draw(int r, int b, int g);
};

#endif // TOUR_H
