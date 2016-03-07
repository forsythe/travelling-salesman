#ifndef CITY_H
#define CITY_H


class City {
public:
    City(int, int);
    City();
    int x;
    int y;
    float distTo(City);
    void draw();
};

#endif // CITY_H
