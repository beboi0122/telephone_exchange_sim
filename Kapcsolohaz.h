#ifndef CLIONJOBBCSICSKACODEBLOCK_KAPCSOLOHAZ_H
#define CLIONJOBBCSICSKACODEBLOCK_KAPCSOLOHAZ_H

#include <vector>
#include "kozpont.h"
#include "kapcs_callback.h"

class Kapcsolohaz : public CB_Tkapcs {
    std::vector<Kozpont *> Kozpontok;
    int Max_TavKapcs;
    int Akt_TavKapcs;
    Ktabla *TavTabla;
public:
    Kapcsolohaz(int max_tk = 50, int max_KozpontElof = 1000, int max_KozpontKapcs = 20);

    Kapcsolohaz(const char* f, int max_tk = 50, int max_KozpontElof = 1000, int max_KozpontKapcs = 20);

    Kapcsolat* TCall(Elofizeto* ki, int kit);

    bool TLetesz(int ki, int kit);

    int GetMaxTavkapcs();

    int GetAktKapcs();

    int ByName(int korzet, String nev, Datum datum, String szul_hely);

    std::vector<Kozpont *> GetKozpontok();

    ~Kapcsolohaz();
};


#endif //CLIONJOBBCSICSKACODEBLOCK_KAPCSOLOHAZ_H
