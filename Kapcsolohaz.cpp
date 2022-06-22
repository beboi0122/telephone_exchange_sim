#include "Kapcsolohaz.h"
#include "memtrace.h"
#include <fstream>
#include <sstream>

Kapcsolohaz::Kapcsolohaz(int max_tk, int max_KozpontElof, int max_KozpontKapcs) : Max_TavKapcs(max_tk), Akt_TavKapcs(0) {
    for (int i = 1; i != 10; ++i) {
        Kozpont *tmp = new Kozpont(*this, i, max_KozpontElof, max_KozpontKapcs);
        Kozpontok.push_back(tmp);
    }
    TavTabla = new Ktabla[max_tk];
}

Kapcsolohaz::Kapcsolohaz(const char* f, int max_tk, int max_KozpontElof, int max_KozpontKapcs): Max_TavKapcs(max_tk), Akt_TavKapcs(0) {
    for (int i = 1; i != 10; ++i) {
        Kozpont *tmp = new Kozpont(*this, i, max_KozpontElof, max_KozpontKapcs);
        Kozpontok.push_back(tmp);
    }
    TavTabla = new Ktabla[max_tk];
    std::ifstream data;
    data.open(f);
    if(data.fail()){
        std::cerr << "Gond van";
    }
    int k = -1;
    std::string sor;
    while(!data.eof()){
        while(getline(data, sor)){
            if(sor[0] == '#'){
                ++k;
                break;
            }
            std::stringstream ss(sor);
            getline(ss, sor, ';');
            String nev = sor.c_str();

            getline(ss, sor, ';');
            int ev = std::stoi(sor);

            getline(ss, sor, ';');
            int honap = std::stoi(sor);

            getline(ss, sor, ';');
            int nap = std::stoi(sor);

            getline(ss, sor, ';');
            String szulhely = sor.c_str();

            Kozpontok[k]->UjElofizeto(Ember(nev, ev, honap, nap, szulhely));
        }
    }
    data.close();
}

Kapcsolat* Kapcsolohaz::TCall(Elofizeto* ki, int kit) {
    if(Max_TavKapcs < Akt_TavKapcs+1){
        std::stringstream err;
        err << "\tHIBA:\tA tavolsagi hivasok szama elerte a maximumot!";
        throw err.str();
    }
    int idx;
    if(kit < 10){
        idx = kit-1;
    }
    else{
        idx = (kit / 1000)-1;
    }
    ++Akt_TavKapcs;
    return Kozpontok[idx]->BeTav(ki,kit);
}

bool Kapcsolohaz::TLetesz(int ki, int kit) {
    int idx;
    if(kit < 10){
        idx = kit-1;
    }
    else{
        idx = (kit / 1000)-1;
    }
    --Akt_TavKapcs;
    return Kozpontok[idx]->LeTav(ki, kit);
}

int Kapcsolohaz::ByName(int korzet, String nev, Datum datum, String szul_hely) {
    if(Max_TavKapcs < Akt_TavKapcs+1){
        std::stringstream err;
        err << "\tHIBA:\tA tavolsagi hivasok szama elerte a maximumot!";
        throw err.str();
    }
    ++Akt_TavKapcs;
    return Kozpontok[korzet-1]->HolVan(nev, datum, szul_hely);
}

Kapcsolohaz::~Kapcsolohaz() {
    for (int i = 0; i != 9; ++i) {
        delete Kozpontok[i];
    }
    delete[] TavTabla;
}

std::vector<Kozpont *> Kapcsolohaz::GetKozpontok() {
    return Kozpontok;
}

int Kapcsolohaz::GetMaxTavkapcs() {
    return Max_TavKapcs;
}

int Kapcsolohaz::GetAktKapcs() {
    return Akt_TavKapcs;
}





