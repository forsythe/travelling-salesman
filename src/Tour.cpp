#include "Tour.h"
#include "CSDLManagerLite.h"
#include "defs.h"

Tour::Tour() {
    for (int k = 0; k < NUM_CITIES; k++)
        cities[k] = City(rand()%WIDTH, rand()%HEIGHT);
}

void Tour::updateCities(City t[]) {
    for (int k = 0; k < NUM_CITIES; k++)
        cities[k] = City(t[k].x, t[k].y);
}

double Tour::getDist() {
    double ans = 0;
    for (int k = 0; k < NUM_CITIES-1; k++)
        ans += cities[k].distTo(cities[k+1]);

    ans+= cities[NUM_CITIES-1].distTo(cities[0]);
    return ans;
}

void Tour::swapCities(int a, int b) {
    City temp = cities[a];
    cities[a] = cities[b];
    cities[b] = temp;
}

void Tour::twoOptSwap(int a, int b) {
    int counter = a;
    if (a == b) return;

    if (a > b)
        while (a-b>0)
            swapCities(a--, b++);
    else
        while (b-a>0)
            swapCities(a++, b--);
}

double Tour::getUpdatedDistWhenSwappedCities(int old_dist, int a, int b) {
    swapCities(a, b); //Temporary undo to calculate old partial score
    double amt = 0;

    if (a == 0) amt += (cities[a].distTo(cities[a+1]) + cities[a].distTo(cities[NUM_CITIES-1]));
    else if (a == NUM_CITIES-1) amt += (cities[a-1].distTo(cities[a]) + cities[0].distTo(cities[a]));
    else amt += (cities[a-1].distTo(cities[a]) + cities[a].distTo(cities[a+1]));

    if (b == 0) amt += (cities[b].distTo(cities[b+1]) + cities[b].distTo(cities[NUM_CITIES-1]));
    else if (b == NUM_CITIES-1) amt += (cities[b-1].distTo(cities[b]) + cities[0].distTo(cities[b]));
    else amt += (cities[b-1].distTo(cities[b]) + cities[b].distTo(cities[b+1]));

    old_dist -= amt;
    swapCities(a, b);

    if (a == 0) old_dist += (cities[a].distTo(cities[a+1]) + cities[a].distTo(cities[NUM_CITIES-1]));
    else if (a == NUM_CITIES-1) old_dist += (cities[a-1].distTo(cities[a]) + cities[0].distTo(cities[a]));
    else old_dist += (cities[a-1].distTo(cities[a]) + cities[a].distTo(cities[a+1]));

    if (b == 0) old_dist += (cities[b].distTo(cities[b+1]) + cities[b].distTo(cities[NUM_CITIES-1]));
    else if (b == NUM_CITIES-1) old_dist += (cities[b-1].distTo(cities[b]) + cities[0].distTo(cities[b]));
    else old_dist += (cities[b-1].distTo(cities[b]) + cities[b].distTo(cities[b+1]));


    return old_dist;
}

double Tour::getUpdatedDistWhenTwoOptSwap(int old_dist, int x, int y) {
    if (x == y) return 0;

    int a = x < y? x : y;
    int b = x > y? x : y;

    old_dist -= cities[b].distTo(cities[a==0? NUM_CITIES-1 : a-1]);
    old_dist -= cities[a].distTo(cities[b==NUM_CITIES-1? 0 : b+1]);
    old_dist += cities[a].distTo(cities[a==0? NUM_CITIES-1 : a-1]);
    old_dist += cities[b].distTo(cities[b==NUM_CITIES-1? 0 : b+1]);

    return old_dist;
}

bool Tour::twoOptSwapIsBeneficial(int x, int y) {
    if (x == y) return false;

    int a = x < y? x : y;
    int b = x > y? x : y;

    double ans = 0;
    ans -= cities[a].distTo(cities[a==0? NUM_CITIES-1 : a-1]);
    ans -= cities[b].distTo(cities[b==NUM_CITIES-1? 0 : b+1]);
    ans += cities[b].distTo(cities[a==0? NUM_CITIES-1 : a-1]);
    ans += cities[a].distTo(cities[b==NUM_CITIES-1? 0 : b+1]);
    return ans < 0;
}

void Tour::draw(int r, int b, int g) {
    CSDLManagerLite::getInstance() -> setColor(r, b, g, 255);
    for (int k = 0; k < NUM_CITIES - 1; k++)
        CSDLManagerLite::getInstance() -> drawLine(cities[k].x, cities[k].y, cities[k+1].x, cities[k+1].y);
    CSDLManagerLite::getInstance() -> drawLine(cities[0].x, cities[0].y, cities[NUM_CITIES-1].x, cities[NUM_CITIES-1].y);

    CSDLManagerLite::getInstance() -> setColor(255, 0, 0, 255);
    for (City c : cities)
        c.draw();
}
