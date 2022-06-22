#include "Kapcsolat.h"
#include "elofizeto.h"
#include "kozpont.h"

Kapcsolat::Kapcsolat(Elofizeto *Hivo, Elofizeto *Fogado, class Kozpont* kozp) : Hivo(Hivo), Fogado(Fogado), Kp(kozp) {}


void Kapcsolat::SendMSG(int ki, const char *s) {
    if(Fogado != nullptr) {
        if (ki == Hivo->GetHivoszam()) {
            Fogado->MSG_Get(ki, s);
        } else {
            Hivo->MSG_Get(ki, s);
        }
    }
    else{
        Kp->MSG_Get(ki, s);
    }
}

Elofizeto *Kapcsolat::GetFogado() {
    return Fogado;
}

Elofizeto *Kapcsolat::GetHivo() {
    return Hivo;
}

int Kapcsolat::GetFogadoszam() {
    if(Kp == nullptr){
        return Fogado->GetHivoszam();
    }
    else{
        return Kp->GetKorzet();
    }
}

int Kapcsolat::GetHivoszam(){
    return Hivo->GetHivoszam();
}

Kapcsolat::~Kapcsolat() {}





