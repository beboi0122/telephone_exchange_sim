#ifndef EMBER_H_INCLUDED
#define EMBER_H_INCLUDED

#include "string5.h"
#include "datum.h"

class Ember{
    String Nev;
    Datum Szuletesi_datum;
    String Szuletesi_hely;
public:
    Ember(const String& nev = "N/D", int ev=0, int honap=0, int nap=0, const String& szul_hely="N/D");
    Ember(const Ember& e);
    String GetNev() const;
    Datum GetSzulDat() const;
    String GetSzulHely() const;
    void SetNev(const String e);
    void SetSzulDat(const Datum d);
    void SetSzulHely(const String s);
    bool operator==(const Ember& e);
    Ember& operator=(const Ember& e);
    virtual ~Ember(){};
};

#endif // EMBER_H_INCLUDED
