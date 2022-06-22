#ifndef CLIONJOBBCSICSKACODEBLOCK_KTABLA_H
#define CLIONJOBBCSICSKACODEBLOCK_KTABLA_H

#include <iostream>

class Ktabla{
    int Hivo;
    int Fogado;
public:
    Ktabla(int hivo=0, int fogado=0);
    Ktabla(const Ktabla& k);

    void UjKapcs(int hivo, int fogado);

    int GetHivo();

    void SetHivo(int h);

    void SetFogado(int f);
};

#endif //CLIONJOBBCSICSKACODEBLOCK_KTABLA_H
