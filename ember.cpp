#include "ember.h"
#include "memtrace.h"

    Ember::Ember(const String& nev, int ev, int honap, int nap, const String& szul_hely): Nev(nev), Szuletesi_datum(ev, honap, nap), Szuletesi_hely(szul_hely){}

    Ember::Ember(const Ember& e){
        Nev = e.GetNev();
        Szuletesi_hely = e.GetSzulHely();
        Szuletesi_datum = e.GetSzulDat();
    }
    bool Ember::operator==(const Ember& e){
        return Nev==e.Nev && Szuletesi_datum==e.Szuletesi_datum && Szuletesi_hely==e.Szuletesi_hely;
    }
    Ember& Ember::operator=(const Ember& e){
        SetNev(e.GetNev());
        SetSzulDat(e.GetSzulDat());
        SetSzulHely(e.GetSzulHely());
        return *this;
    }
    String Ember::GetNev() const {return Nev;}
    Datum Ember::GetSzulDat() const {return Szuletesi_datum;}
    String Ember::GetSzulHely() const {return Szuletesi_hely;}

    void Ember::SetNev(const String e){
        Nev = e;
    }

    void Ember::SetSzulDat(const Datum d) {
        Szuletesi_datum = d;
    }

    void Ember::SetSzulHely(const String s) {
        Szuletesi_hely = s;
    }