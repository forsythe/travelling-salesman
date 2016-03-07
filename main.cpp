#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "Tour.h"
#include "City.h"
#include "CSDLManagerLite.h"
#include "CSDLInputManagerLite.h"
#include "defs.h"

using namespace std;

inline float fast_log2 (float val) {
    int * const    exp_ptr = reinterpret_cast <int *> (&val);
    int            x = *exp_ptr;
    const int      log_2 = ((x >> 23) & 255) - 128;
    x &= ~(255 << 23);
    x += 127 << 23;
    *exp_ptr = x;

    val = ((-1.0f/3) * val + 2) * val - 2.0f/3;   // (1)

    return (val + log_2);
}

inline float fast_log (const float &val) {
    return (fast_log2 (val) * 0.69314718f);
}

bool accPrb(double energy, double new_energy, double temp) {
    if (new_energy < energy)
        return true;

    return expf((energy-new_energy)/temp) > static_cast<float>(rand())/static_cast<float>(RAND_MAX);
}

void update() {
    CSDLManagerLite::getInstance() -> drawFrame();
    CSDLManagerLite::getInstance() -> background();
    CSDLInputManagerLite::getInstance() -> update();
}

bool done_SA = false;
bool done_twoOpt = false;

void simAnneal(Tour &cur) {
    if (done_SA) return;

    Tour best_tour = Tour();
    best_tour.updateCities(cur.cities);

    double cur_energy, new_energy;

    double temp = TEMP;
    const double DENOM = fast_log2(TEMP)/WIDTH;
    int a, b;

    cout << "Starting temperature: " << TEMP << endl;
    cout << "Cooling rate: " << COOL_RATE << endl;

    while (temp > 1) {
        a = rand()%NUM_CITIES, b = rand()%NUM_CITIES;

        cur_energy = cur.getDist();
        cur.swapCities(a, b);
        //cur.twoOptSwap(a, b);

        new_energy = cur.getUpdatedDistWhenSwappedCities(cur_energy, a, b);
        //new_energy = cur.getUpdatedDistWhenTwoOptSwap(cur_energy, a, b);

        if (!accPrb(cur_energy, new_energy, temp))
            cur.swapCities(a, b);
            //cur.twoOptSwap(a, b);

        if(best_tour.getDist() > cur.getDist())
            best_tour.updateCities(cur.cities);

        if (ANIMATE) {
            cur.draw(255, 255, 255);
            CSDLManagerLite::getInstance()->drawRectTLCorner(0, HEIGHT-5, fast_log2(temp)/DENOM, 5); //Linearized progress bar
            update();
        }

        temp *= 1-COOL_RATE;//cout << "Temp: " << temp << "\tDist: " << cur.getDist() << endl;
        if (temp < 1)
            cout << "Final distance after annealing: " << best_tour.getDist() << endl;
    }
    cur.updateCities(best_tour.cities);
    done_SA = true;
}

void twoOpt(Tour &cur) {
    if (done_twoOpt) return;
    Tour best_tour = Tour();
    best_tour.updateCities(cur.cities);

    double cur_energy;

    cur_energy = cur.getDist();
    int start = 0, finish = -1;

    while (finish < start) {
        start = cur.getDist();
        for (int r = 0; r < NUM_CITIES - 1; r++) {
            for (int c = r + 1; c < NUM_CITIES; c++) {
                if (!cur.twoOptSwapIsBeneficial(r, c)) continue;

                if (SHOW_2OPT_STEPS) {
                    int x = r < c? r : c;
                    int y = r > c? r : c;
                    cur.draw(255, 255, 255);
                    CSDLManagerLite::getInstance() -> setColor(0, 255, 0, 255);
                    CSDLManagerLite::getInstance() -> drawLine(cur.cities[x].x, cur.cities[x].y, cur.cities[x==0? NUM_CITIES-1:x-1].x, cur.cities[x==0?NUM_CITIES-1:x-1].y);
                    CSDLManagerLite::getInstance() -> drawLine(cur.cities[y].x, cur.cities[y].y, cur.cities[y==NUM_CITIES-1?0:y+1].x, cur.cities[y==NUM_CITIES-1?0:y+1].y);
                    update();
                    CSDLManagerLite::getInstance() -> delay(DELAY_2OPT_MS);
                }

                cur.twoOptSwap(r, c);
                cur_energy = cur.getUpdatedDistWhenTwoOptSwap(cur_energy, r, c);
            }
            if (ANIMATE) {
                cur.draw(255, 255, 255);
                update();
            }
        }
        finish = cur.getDist();

        if (finish < start)
            best_tour.updateCities(cur.cities);
    }
    cout << "Final distance after 2-opt: " << best_tour.getDist() << endl;
    cur.updateCities(best_tour.cities);
    done_twoOpt = true;
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); //Seed
    CSDLManagerLite::getInstance()->initializeSDL(WIDTH, HEIGHT, TITLE);

    Tour t = Tour();
    cout << "Initial distance: " << t.getDist() << endl;
    cout << "Cities: " << NUM_CITIES << endl;
    while (!CSDLInputManagerLite::getInstance() -> isExit()) {
        if (SA)
            simAnneal(t);
        if (twOPT)
            twoOpt(t);
        t.draw(0, 255, 0);
        update();
    }

    CSDLManagerLite::getInstance()->clean();
    return 0;
}
