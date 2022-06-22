#include "ktabla.h"
#include "memtrace.h"

Ktabla::Ktabla(int hivo, int fogado): Hivo(hivo), Fogado(fogado){}
Ktabla::Ktabla(const Ktabla &k):Hivo(k.Hivo), Fogado(k.Fogado) {}

void Ktabla::UjKapcs(int hivo, int fogado) {
    Hivo = hivo;
    Fogado = fogado;
}

int Ktabla::GetHivo() {
    return Hivo;
}

void Ktabla::SetHivo(int h) {
    Hivo = h;
}

void Ktabla::SetFogado(int f) {
    Fogado = f;
}
