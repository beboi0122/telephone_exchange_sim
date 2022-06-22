#ifndef HAZI_KAPCSOLAT_H
#define HAZI_KAPCSOLAT_H

///elődeklaráció, hogy ismert legyen
class Elofizeto;
class Kozpont;

class Kapcsolat {
    Elofizeto* Hivo;
    Elofizeto* Fogado;
    Kozpont* Kp;           /// ha ez nem nullptr akkor a kapcsolat elofizeto es kozpont kozott van.
public:
    Kapcsolat(Elofizeto* Hivo = nullptr, Elofizeto* Fogado = nullptr, class Kozpont* kozp = nullptr);

    void SendMSG(int ki, const char* s);

    Elofizeto* GetFogado();

    Elofizeto* GetHivo();

    int GetFogadoszam();

    int GetHivoszam();

    virtual ~Kapcsolat();

};


#endif //HAZI_KAPCSOLAT_H
