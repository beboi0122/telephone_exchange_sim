#ifndef HAZI_HEADER_H
#define HAZI_HEADER_H

#include "string5.h"
#include "Kapcsolat.h"
#include "datum.h"

class CB_Kapcs{
public:
    virtual void Call_callBack(int tol, int nak) = 0;

    virtual void Letesz(int ki, int kit) = 0;

    virtual void ByName(int ki, int korzet, String nev, Datum datum, String szul_hely) = 0;
};

class CB_Tkapcs{
public:
    virtual  Kapcsolat* TCall(Elofizeto* ki, int kit) = 0;

    virtual bool TLetesz(int ki, int kit) = 0;

    virtual int ByName(int korzet, String nev, Datum datum, String szul_hely) = 0;
};

#endif //HAZI_HEADER_H
