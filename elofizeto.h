#ifndef ELOFIZETO_H_INCLUDED
#define ELOFIZETO_H_INCLUDED

#include "ember.h"
#include "kapcs_callback.h"
#include "ktabla.h"

///elődeklaráció, hogy ismert legyen
class Kapcsolat;

class Elofizeto : public Ember {
    CB_Kapcs &cb;       ///CallBack objektum amin keresztül hozzafer a Központhoz
    Kapcsolat* kapcsolatban;
    int Hivoszam;
    bool Foglalt;
public:
    Elofizeto(Ember e, CB_Kapcs &t , int hivoszam =0, bool foglalt = false);

    Elofizeto(CB_Kapcs &t, String nev="", int ev=0, int honap=0, int nap=0, String szul_hely="", int hivoszam=0, bool foglalt=false);

    Elofizeto(const Elofizeto& e);

    Elofizeto &operator=(const Elofizeto &e);

    void SentCall(Kapcsolat* kap);

    void InCall(Kapcsolat* kap);

    void Call(int tellszam);

    void MSG_Get(int tell, const char* s);

    void MSG_Send(const char* s);

    void KapcsolatVege();

    void Letesz();

    void CallByName(int korzet, const char* nev, int ev, int honap, int nap, const char* szul_hely);

    int GetHivoszam();

    bool GetFoglalt();

    void SetFoglalt(bool f);

    void SetKapcsolatba(Kapcsolat* k);

    virtual ~Elofizeto();

};

#endif // ELOFIZETO_H_INCLUDED
