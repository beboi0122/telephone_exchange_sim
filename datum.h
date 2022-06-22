#ifndef DATUM_H_INCLUDED
#define DATUM_H_INCLUDED
#include <iostream>
#include <iomanip>
#include "datum.h"


class Datum{
    int ev;
    int honap;
    int nap;
public:
    Datum(int ev = 0, int honap = 0, int nap=0): ev(ev), honap(honap), nap(nap){}

    int getEv() const { return ev;}

    int getHo() const { return honap;}

    int getNap() const { return nap;}

    bool operator==(const Datum& d) const {
        return ev == d.ev && honap == d.honap && nap == d.nap;
    }
};
std::ostream& operator<<(std::ostream& os, const Datum& d);
#endif // DATUM_H_INCLUDED
