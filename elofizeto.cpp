#include "elofizeto.h"
#include "memtrace.h"
#include "ember.h"
#include "string5.h"
#include "Kapcsolat.h"
#include <sstream>

Elofizeto::Elofizeto(Ember e, CB_Kapcs &t, int hivoszam, bool foglalt) : Ember(e), cb(t), kapcsolatban(nullptr) , Hivoszam(hivoszam), Foglalt(foglalt){}

Elofizeto::Elofizeto(CB_Kapcs &t, String nev, int ev, int honap, int nap, String szul_hely, int hivoszam, bool foglalt)
        :Ember(nev, ev, honap, nap, szul_hely), cb(t), kapcsolatban(nullptr), Hivoszam(hivoszam), Foglalt(foglalt) {}

Elofizeto::Elofizeto(const Elofizeto &e) : Ember(e), cb(e.cb), kapcsolatban(e.kapcsolatban) , Hivoszam(e.Hivoszam), Foglalt(e.Foglalt) {}


Elofizeto &Elofizeto::operator=(const Elofizeto &e) {
    SetNev(e.GetNev());
    SetSzulDat(e.GetSzulDat());
    SetSzulHely(e.GetSzulHely());
    cb = e.cb;
    kapcsolatban = e.kapcsolatban;
    Hivoszam = e.Hivoszam;
    Foglalt = e.Foglalt;
    return *this;
}

void Elofizeto::SentCall(Kapcsolat* kap) {
    kapcsolatban = kap;
    Foglalt = true;
    std::cout << Hivoszam << " telefonszamu elofizeto hivast kezdemenyezett " << kapcsolatban->GetFogadoszam() << " telefonszamu elofizeto/kozpont fele!" << std::endl;
}

void Elofizeto::InCall(Kapcsolat* kap) {
    kapcsolatban = kap;
    Foglalt = true;
    std::cout << Hivoszam << " telefonszamu elofizeto hivast fogadott " << kapcsolatban->GetHivoszam() << " telefonszamu elofizetotol!" << std::endl;
}


void Elofizeto::Call(int tellszam) {
    if(GetFoglalt()){
        std::stringstream err;
        err << "HIBA:\tEz az elofizeto jelenleg aktiv hivasban";
        throw err.str();
    }
    cb.Call_callBack(Hivoszam, tellszam);
}

int Elofizeto::GetHivoszam() {
    return Hivoszam;
}

bool Elofizeto::GetFoglalt() {
    return Foglalt;
}

void Elofizeto::SetFoglalt(bool f) {
    Foglalt = f;
}

void Elofizeto::MSG_Get(int tell, const char *s) {
    std::cout << "A " << Hivoszam << " hivoszamu elofizeto a kovetkezo uzenetek kapta " << tell << " hivoszamu elofizetotol:" << std::endl
            << "\t" << s <<std::endl;
}

void Elofizeto::MSG_Send(const char *s) {
    if(!GetFoglalt()){
        std::stringstream err;
        err << "HIBA:\tEz az elofizeto jelenleg nincs aktiv hivasban";
        throw err.str();
    }
    std::cout << "A " << Hivoszam << " hivoszamu elofizeto uzenetet kuldott!" << std:: endl;
    kapcsolatban->SendMSG(Hivoszam ,s);
}
void Elofizeto::KapcsolatVege(){
    delete kapcsolatban;
}

void Elofizeto::SetKapcsolatba(Kapcsolat *k) {
    kapcsolatban = k;
}

void Elofizeto::Letesz() {
    if(!GetFoglalt()){
        std::stringstream err;
        err << "HIBA:\tEz az elofizeto jelenleg nincs aktiv hivasban";
        throw err.str();
    }
    if(Hivoszam == kapcsolatban->GetFogadoszam()) {
        cb.Letesz(Hivoszam, kapcsolatban->GetHivoszam());
    } else{
        cb.Letesz(Hivoszam, kapcsolatban->GetFogadoszam());
    }
}

void Elofizeto::CallByName(int korzet, const char* nev, int ev, int honap, int nap, const char* szul_hely) {
    String n(nev);
    Datum d(ev, honap, nap);
    String sz(szul_hely);
    cb.ByName(GetHivoszam(), korzet, n, d, sz);
}

Elofizeto::~Elofizeto() {}









