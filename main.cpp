#include <iostream>
#include "datum.h"
#include "elofizeto.h"
#include "ember.h"
#include "gtest_lite.h"
#include "kozpont.h"
#include "memtrace.h"
#include "string5.h"
#include "kapcs_callback.h"
#include "Kapcsolohaz.h"
#include "Kapcsolat.h"
#include "testek.h"
#include <sstream>

int main(){
#ifdef JPORTA_INPUT_SIM
    std::ifstream in("standard_input.txt");
    std::cin.rdbuf(in.rdbuf());
#endif // JPORTASIM
    std::cout << "A teszeleshez irjon be egy szamot 1-4-ig (a programot a 0-val allithatja le):" << std::endl;
    int szam;
    while (std::cin >> szam && szam != 0) {
        std::cout << szam << ". teszt:\n\n" << std::endl;
        switch (szam) {
            case 1:
                test_1();
                break;
            case 2:
                test_2();
                break;
            case 3:
                test_3();
                break;
            case 4:
                test_4PeldaProgram();
                break;
            default:
                std::cout << "Ilyen teszt nincs csak 0-4-ig irjon szamokat" << std::endl;
                break;
        }
    }


    return 0;
}
