#ifndef KOZPONT_H_INCLUDED
#define KOZPONT_H_INCLUDED

#include <vector>
#include "ktabla.h"
#include "elofizeto.h"
#include "kapcs_callback.h"

class Kapcsolat;


class Kozpont: public CB_Kapcs{
    CB_Tkapcs& cb;   ///CallBack objektum amin keresztül elérhető a Kapcsoloház
    Kapcsolat* kapcsolat;
    bool FoglatUgyfelSz;
    int Korzet;
    int max_elofizeto;
    int max_kapcsolat;
    int elofizeto_szam;
    int aktiv_kapcs;
    std::vector<Elofizeto*> elofizetok;
    Ktabla *tabla;      ///

public:
    Kozpont(CB_Tkapcs& t, int korz=0, const int max_elf=1000, const int max_kapcs=20);

    int GetMax_Elof();

    std::vector<Elofizeto*>& GetElof();

    int GetMax_Kapcs();

    bool GetFoglalt();

    void SetFoglalt(bool f);

    void SetKapcsolat(Kapcsolat* k);

    void Call_callBack(int tol, int nak);

    void Letesz(int ki, int kit);

    void MSG_Get(int tell, const char *s);

    Ktabla* GetTabla();

    Kozpont(const Kozpont &k);

    void UjElofizeto(const Ember e);

    virtual ~Kozpont();

    void InCall(Kapcsolat* kap);

    int GetKorzet();

    int GetAktivKapcs();

    Kapcsolat* BeTav(Elofizeto* ki, int kit);

    bool LeTav(int ki, int kit);

    void ByName(int ki, int korzet, String nev, Datum datum, String szul_hely);

    int HolVan(String nev, Datum datum, String szul_hely);
};


#endif // KOZPONT_H_INCLUDED