#include "kozpont.h"
#include "memtrace.h"
#include "Kapcsolat.h"
#include <sstream>

///Kostruktorok********************************************************************************************
Kozpont::Kozpont(const Kozpont &k) : cb(k.cb), kapcsolat(k.kapcsolat), FoglatUgyfelSz(k.FoglatUgyfelSz),
                                     Korzet(k.Korzet), max_elofizeto(k.max_elofizeto), max_kapcsolat(k.max_kapcsolat),
                                     elofizeto_szam(k.elofizeto_szam), aktiv_kapcs(k.aktiv_kapcs) {}

Kozpont::Kozpont(CB_Tkapcs &t, int korz, const int max_elf, const int max_kapcs) : cb(t), kapcsolat(nullptr),
                                                                                   FoglatUgyfelSz(false), Korzet(korz),
                                                                                   elofizeto_szam(0), aktiv_kapcs(0) {
    if (max_elf > 1000) { throw "Az elofizetok maximalis szama egy kozpontban nem haladhatja meg az 1000-t"; }
    if (max_kapcs > 600) { throw "A maximalis kapcsolatok szama nem haladhatja meg a 600-at"; }
    max_kapcsolat = max_kapcs;
    max_elofizeto = max_elf;
    elofizetok = std::vector<Elofizeto *>(0);
    tabla = new Ktabla[max_kapcs];
}

Kozpont::~Kozpont() {
    for (int i = 0; i != elofizeto_szam; ++i) {
        delete elofizetok[i];
    }
    delete[] tabla;
}

///Get-er Set-er*******************************************************************************
Ktabla *Kozpont::GetTabla() {
    return tabla;
}

int Kozpont::GetKorzet() {
    return Korzet;
}

void Kozpont::SetFoglalt(bool f) {
    FoglatUgyfelSz = f;
}

bool Kozpont::GetFoglalt() {
    return FoglatUgyfelSz;
}

void Kozpont::SetKapcsolat(Kapcsolat *k) {
    kapcsolat = k;
}

int Kozpont::GetAktivKapcs() {
    return aktiv_kapcs;
}

int Kozpont::GetMax_Elof() {
    return max_elofizeto;
}

int Kozpont::GetMax_Kapcs() {
    return max_kapcsolat;
}

std::vector<Elofizeto *> &Kozpont::GetElof() {
    return elofizetok;
}
///Fugvenyek*************************************************************************************************
void Kozpont::UjElofizeto(const Ember e) {
    if (max_elofizeto < elofizeto_szam + 1) {
        throw "Ebbe a kozpontban az elofizetok szama elerte a maximumot";
    }
    for (int i = 0; i < elofizeto_szam; ++i) {
        if (e.GetNev() == elofizetok[i]->GetNev() && e.GetSzulDat() == elofizetok[i]->GetSzulDat() &&
            e.GetSzulHely() == elofizetok[i]->GetSzulHely()) {
            std::stringstream err;
            err << "HIBA:\tEz az ember mar elofizeto ebben a kozpontban!";
            throw err.str();
        }
    }
    Elofizeto *tmp = new Elofizeto(e, *this, 1000 * Korzet + elofizeto_szam, false);
    elofizetok.push_back(tmp);
    ++elofizeto_szam;
}

void Kozpont::MSG_Get(int tell, const char *s) {
    std::cout << "A " << Korzet << " szamu korzet a kovetkezo uzenetek kapta " << tell << " hivoszamu elofizetotol:"
              << std::endl
              << "\t" << s << std::endl;
}

void Kozpont::InCall(Kapcsolat *kap) {
    kapcsolat = kap;
    FoglatUgyfelSz = true;
    std::cout << Korzet << " szamu korzet hivast fogadott " << kapcsolat->GetHivo()->GetHivoszam()
              << " telefonszamu elofizetotol!" << std::endl;
}

///ez a fugveny dolgozza fel az osszes bejovo hivast
void Kozpont::Call_callBack(int tol, int nak) {
    int idx = tol % 1000;
    if (nak <= 0 || (nak > 9 && nak < 1000) || nak >= 10000) {
        std::stringstream err;
        err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
            << "\tHIBA:\tA hivott szamon elofizeto nem kapcsolhato!";
        throw err.str();
    }
    if (max_kapcsolat < aktiv_kapcs + 1) {
        std::stringstream err;
        err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
            << "\tHIBA:\tA rendszer tulterhelt, probalkozzon ujra kesobb!";
        throw err.str();
    }
    if (tol == nak) {
        std::stringstream err;
        err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
            << "\tHIBA:\tSajat iranyba torteno hivas nem lehetseges!";
        throw err.str();
    }
    int idx_nak = nak % 1000;
    if ((tol / 1000) == (nak / 1000)) {
        if (idx_nak >= elofizeto_szam) {
            std::stringstream err;
            err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tA hivott szamon elofizeto nem kapcsolhato!!";
            throw err.str();
        }
        if (elofizetok[idx_nak]->GetFoglalt()) {
            std::stringstream err;
            err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tA hivott szam jelenleg nem elerheto!";
            throw err.str();
        }
        tabla[aktiv_kapcs].UjKapcs(tol, nak);
        Kapcsolat *tmp = new Kapcsolat(elofizetok[idx], elofizetok[idx_nak]);
        elofizetok[idx]->SentCall(tmp);
        elofizetok[idx_nak]->InCall(tmp);
        ++aktiv_kapcs;
        return;
    }
    if (nak == Korzet) {

        if (GetFoglalt()) {
            std::stringstream err;
            err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tA hivott szam jelenleg nem elerheto!";
            throw err.str();
        }
        tabla[aktiv_kapcs].UjKapcs(tol, nak);
        Kapcsolat *tmp = new Kapcsolat(elofizetok[idx], nullptr, this);
        elofizetok[idx]->SentCall(tmp);
        InCall(tmp);
        ++aktiv_kapcs;
        return;
    }
    if (nak < 10) {
        Kapcsolat *tmp = cb.TCall(elofizetok[idx], nak);
        if (tmp == nullptr) {
            std::stringstream err;
            err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tA hivott szam jelenleg nem elerheto!";
            throw err.str();
        }
        tabla[aktiv_kapcs].UjKapcs(tol, nak);
        elofizetok[idx]->SentCall(tmp);
        ++aktiv_kapcs;
        return;
    }
    if ((nak > 10) && ((nak / 1000) != Korzet)) {
        Kapcsolat *tmp = cb.TCall(elofizetok[idx], nak);
        if (tmp == nullptr) {
            std::stringstream err;
            err << "A " << tol << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tA hivott szamon elofizeto nem kapcsolhato VAGY a hivott szam jelenleg nem elerheto!";
            throw err.str();
        }
        tabla[aktiv_kapcs].UjKapcs(tol, nak);
        elofizetok[idx]->SentCall(tmp);
        ++aktiv_kapcs;
        return;
    }
}

void Kozpont::Letesz(int ki, int kit) {
    int idx_ki = ki % 1000;
    int idx_kit = kit % 1000;
    if ((ki / 1000) == (kit / 1000)) {
        for (int i = 0; i < max_kapcsolat; ++i) {
            if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                tabla[i].SetHivo(0);
                tabla[i].SetFogado(0);
                break;
            }
        }
        elofizetok[idx_ki]->SetFoglalt(false);
        elofizetok[idx_kit]->SetFoglalt(false);
        elofizetok[idx_ki]->KapcsolatVege();
        elofizetok[idx_ki]->SetKapcsolatba(nullptr);
        elofizetok[idx_kit]->SetKapcsolatba(nullptr);
        std::cout << ki << " es " << kit << " hivoszamu elofizetok kozotti kapcsolat megszakitva!" << std::endl;
        --aktiv_kapcs;
        return;
    }
    if (kit == Korzet) {
        for (int i = 0; i < max_kapcsolat; ++i) {
            if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                tabla[i].SetHivo(0);
                tabla[i].SetHivo(0);
                break;
            }
        }
        elofizetok[idx_ki]->SetFoglalt(false);
        SetFoglalt(false);
        elofizetok[idx_ki]->KapcsolatVege();
        elofizetok[idx_ki]->SetKapcsolatba(nullptr);
        SetKapcsolat(nullptr);
        std::cout << ki << " hivoszamu elofizeto es a(z) " << kit << " korzet kozponja kozotti kapcsolat megszakitva!"
                  << std::endl;
        --aktiv_kapcs;
        return;
    }
    if(kit < 10){
        if(cb.TLetesz(ki, kit)){
            for (int i = 0; i < max_kapcsolat; ++i) {
                if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                    tabla[i].SetHivo(0);
                    tabla[i].SetHivo(0);
                    break;
                }
            }
            elofizetok[idx_ki]->SetFoglalt(false);
            elofizetok[idx_ki]->KapcsolatVege();
            elofizetok[idx_ki]->SetKapcsolatba(nullptr);
            std::cout << ki << " hivoszamu elofizeto es a(z) " << kit << " korzet kozponja kozotti kapcsolat megszakitva!"
                      << std::endl;
            --aktiv_kapcs;
            return;
        }
        std::cerr << "EZ NEM LEHET \n";
    }
    if((kit > 10) && ((kit / 1000) != Korzet)){
        if(cb.TLetesz(ki, kit)){
            for (int i = 0; i < max_kapcsolat; ++i) {
                if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                    tabla[i].SetHivo(0);
                    tabla[i].SetFogado(0);
                    break;
                }
            }
            elofizetok[idx_ki]->SetFoglalt(false);
            elofizetok[idx_ki]->KapcsolatVege();
            elofizetok[idx_ki]->SetKapcsolatba(nullptr);
            std::cout << ki << " es " << kit << " hivoszamu elofizetok kozotti kapcsolat megszakitva!"
                      << std::endl;
            --aktiv_kapcs;
            return;

        }
    }

}

Kapcsolat *Kozpont::BeTav(Elofizeto *ki, int kit) {
    if (kit == Korzet) {
        if (GetFoglalt()) {
            return nullptr;
        }
        tabla[aktiv_kapcs].UjKapcs(ki->GetHivoszam(), kit);
        Kapcsolat *tmp = new Kapcsolat(ki, nullptr, this);
        InCall(tmp);
        ++aktiv_kapcs;
        return tmp;
    }
    if (kit % 1000 > elofizeto_szam) {
        return nullptr;
    }
    if (elofizetok[kit % 1000]->GetFoglalt()) {
        return nullptr;
    }
    tabla[aktiv_kapcs].UjKapcs(ki->GetHivoszam(), kit);
    Kapcsolat *tmp = new Kapcsolat(ki, elofizetok[kit % 1000]);
    elofizetok[kit % 1000]->InCall(tmp);
    ++aktiv_kapcs;
    return tmp;
}

bool Kozpont::LeTav(int ki, int kit) {
    if(kit == Korzet) {
        for (int i = 0; i < max_kapcsolat; ++i) {
            if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                tabla[i].SetHivo(0);
                tabla[i].SetHivo(0);
                break;
            }
        }
        SetFoglalt(false);
        SetKapcsolat(nullptr);
        --aktiv_kapcs;
        return true;
    }
    if(kit / 1000 == Korzet){
        for (int i = 0; i < max_kapcsolat; ++i) {
            if (tabla[i].GetHivo() == ki || tabla[i].GetHivo() == kit) {
                tabla[i].SetHivo(0);
                tabla[i].SetFogado(0);
                break;
            }
        }
        elofizetok[kit % 1000]->SetFoglalt(false);
        elofizetok[kit % 1000]->SetKapcsolatba(nullptr);
        --aktiv_kapcs;
        return true;
    }
    return false;
}

void Kozpont::ByName(int ki, int korzet, String nev, Datum datum, String szul_hely) {
    if(korzet == Korzet){
        int nak = HolVan(nev, datum, szul_hely);
        if(nak == -1){
            std::stringstream err;
            err << "A " << ki << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tIlyen elofizeto nem letezik";
            throw err.str();
        }
        Call_callBack(ki, nak+1000);
    }
    else{
        int nak = cb.ByName(korzet, nev, datum, szul_hely);
        if(nak == -1){
            std::stringstream err;
            err << "A " << ki << " hivoszamu elofizeto, a kovetkezo uzenetet kapta a kozponttol:" << std::endl
                << "\tHIBA:\tIlyen elofizeto nem letezik";
            throw err.str();
        }
        Call_callBack(ki, nak+1000);
    }
}

int Kozpont::HolVan(String nev, Datum datum, String szul_hely) {
    int itt = -1;
    for (int i = 0; i < elofizeto_szam; ++i) {
        if (nev == elofizetok[i]->GetNev() && datum == elofizetok[i]->GetSzulDat() && szul_hely == elofizetok[i]->GetSzulHely()) {
            itt = i;
            break;
        }
    }
    return itt;
}
