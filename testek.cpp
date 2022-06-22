#include "ember.h"
#include "gtest_lite.h"
#include "string5.h"
#include "Kapcsolohaz.h"
void test_1() {
    TEST(LetrehozasSajtkezuleg, ClassEmber){
        Ember proba("Kardos Bela", 1998, 11, 30, "Kiskunhalas");
        EXPECT_STREQ("Kardos Bela", proba.GetNev().c_str());
        EXPECT_EQ(1998, proba.GetSzulDat().getEv());
        EXPECT_EQ(11, proba.GetSzulDat().getHo());
        EXPECT_EQ(30, proba.GetSzulDat().getNap());
        EXPECT_STREQ("Kiskunhalas", proba.GetSzulHely().c_str());
        }
    TEST(LetrehozasSajatkezuleg, Teljes){
        Ember en("Panczel Bence", 2000, 1, 22, "Esztergom");
        Ember valaki("Kiss Julia", 1997, 2, 28, "Budapest");
        Ember masik("Kardos Bela", 1876, 3, 12, "Pecs");
        Kapcsolohaz khaz(5, 10, 3);
        khaz.GetKozpontok()[0]->UjElofizeto(en);
        khaz.GetKozpontok()[0]->UjElofizeto(valaki);
        khaz.GetKozpontok()[4]->UjElofizeto(masik);
        for(int i = 1; i <10; ++i) {
            EXPECT_EQ(i, khaz.GetKozpontok()[i - 1]->GetKorzet());
        }
        EXPECT_STREQ("Kardos Bela", khaz.GetKozpontok()[4]->GetElof()[0]->GetNev().c_str());
        EXPECT_EQ(5000, khaz.GetKozpontok()[4]->GetElof()[0]->GetHivoszam());
        EXPECT_EQ(1001, khaz.GetKozpontok()[0]->GetElof()[1]->GetHivoszam());
        for(int i = 0; i <9; ++i) {
            EXPECT_EQ(10, khaz.GetKozpontok()[i]->GetMax_Elof());
        }
        for(int i = 0; i <9; ++i) {
            EXPECT_EQ(3, khaz.GetKozpontok()[i]->GetMax_Kapcs());
        }
        EXPECT_EQ(5, khaz.GetMaxTavkapcs());
    }
    TEST(LetrehozasFajlbol, Teljes){
        Kapcsolohaz khaz("../elofizetok.txt", 20, 200, 5);
        EXPECT_EQ(5000, khaz.GetKozpontok()[4]->GetElof()[0]->GetHivoszam());
        EXPECT_EQ(1001, khaz.GetKozpontok()[0]->GetElof()[1]->GetHivoszam());
        for(int i = 0; i <9; ++i) {
            EXPECT_EQ(200, khaz.GetKozpontok()[i]->GetMax_Elof());
        }
        for(int i = 0; i <9; ++i) {
            EXPECT_EQ(5, khaz.GetKozpontok()[i]->GetMax_Kapcs());
        }
        EXPECT_EQ(20, khaz.GetMaxTavkapcs());
        EXPECT_STREQ("Varadi Bence", khaz.GetKozpontok()[3]->GetElof()[8]->GetNev().c_str());
        EXPECT_STREQ("Budapest", khaz.GetKozpontok()[3]->GetElof()[8]->GetSzulHely().c_str());
        EXPECT_EQ(4008,khaz.GetKozpontok()[3]->GetElof()[8]->GetHivoszam());
    }
}
}
}
}
void test_2(){
    TEST(HivasSzammal, LetrejovoKapcsolat){
        Kapcsolohaz khaz("../elofizetok.txt", 20, 200, 5);
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetAktivKapcs());
        int foglalt = 0;
        if(khaz.GetKozpontok()[0]->GetElof()[3]->GetFoglalt()) {
            foglalt = 1;
        }
        EXPECT_EQ(0, foglalt);
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetTabla()[0].GetHivo());
        khaz.GetKozpontok()[0]->GetElof()[3]->Call(1007);
        if(khaz.GetKozpontok()[0]->GetElof()[3]->GetFoglalt()) {
            foglalt = 1;
        }
        EXPECT_EQ(1, foglalt);
        EXPECT_EQ(1, khaz.GetKozpontok()[0]->GetAktivKapcs());
        EXPECT_EQ(1003, khaz.GetKozpontok()[0]->GetTabla()[0].GetHivo());
        khaz.GetKozpontok()[0]->GetElof()[3]->Letesz();
        if(!khaz.GetKozpontok()[0]->GetElof()[3]->GetFoglalt()) {
            foglalt = 0;
        }
        EXPECT_EQ(0, foglalt);
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetAktivKapcs());
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetTabla()[0].GetHivo());
    }
    TEST(HivasNevalapjan, LetrejovoKapsolat){
        Kapcsolohaz khaz("../elofizetok.txt", 20, 200, 5);
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetAktivKapcs());
        khaz.GetKozpontok()[4]->GetElof()[3]->CallByName(1, "Panczel Bence", 2000, 1, 22, "Esztergom");
        EXPECT_EQ(1, khaz.GetKozpontok()[0]->GetAktivKapcs());
        EXPECT_EQ(5003, khaz.GetKozpontok()[0]->GetTabla()[0].GetHivo());
        khaz.GetKozpontok()[0]->GetElof()[4]->Letesz();
    }
    TEST(Hivas, Uzenet){
        Kapcsolohaz khaz("../elofizetok.txt", 20, 200, 5);
        khaz.GetKozpontok()[8]->GetElof()[4]->Call(7002);
        khaz.GetKozpontok()[6]->GetElof()[2]->MSG_Send("Jonapot kivanok!");
        khaz.GetKozpontok()[8]->GetElof()[4]->MSG_Send("Viszont hallasra!");
        khaz.GetKozpontok()[8]->GetElof()[4]->Letesz();
        khaz.GetKozpontok()[3]->GetElof()[5]->Call(1);
        EXPECT_EQ(1, khaz.GetKozpontok()[0]->GetAktivKapcs());
        EXPECT_EQ(1, khaz.GetAktKapcs());
        khaz.GetKozpontok()[3]->GetElof()[5]->MSG_Send("Uzenet az 1-es kozpontnak -vetel-");
        khaz.GetKozpontok()[3]->GetElof()[5]->Letesz();
        EXPECT_EQ(0, khaz.GetKozpontok()[0]->GetAktivKapcs());
        EXPECT_EQ(0, khaz.GetAktKapcs());
    }
}
}
}
}
void test_3(){
    TEST(Hibauzenetek, 1){
        Kapcsolohaz khaz("../elofizetok.txt", 2, 200, 2);
        Ember en("Panczel Bence", 2000, 1, 22, "Esztergom");
        EXPECT_ANY_THROW(khaz.GetKozpontok()[0]->UjElofizeto(en));
        EXPECT_ANY_THROW( khaz.GetKozpontok()[2]->GetElof()[5]->Call(100));
        EXPECT_ANY_THROW( khaz.GetKozpontok()[2]->GetElof().at(10)->Call(1));
        khaz.GetKozpontok()[2]->GetElof()[5]->Call(1000);
        EXPECT_ANY_THROW( khaz.GetKozpontok()[2]->GetElof()[5]->Call(2000));
        khaz.GetKozpontok()[2]->GetElof()[1]->Call(1002);
        EXPECT_ANY_THROW( khaz.GetKozpontok()[2]->GetElof()[4]->Call(6000));
        khaz.GetKozpontok()[2]->GetElof()[5]->Letesz();
        khaz.GetKozpontok()[2]->GetElof()[1]->Letesz();
        EXPECT_ANY_THROW(khaz.GetKozpontok()[2]->GetElof()[5]->Letesz());
        khaz.GetKozpontok()[3]->GetElof()[5]->Call(1000);
        khaz.GetKozpontok()[2]->GetElof()[1]->Call(1002);
        EXPECT_ANY_THROW(khaz.GetKozpontok()[1]->GetElof()[1]->Call(3002));
        khaz.GetKozpontok()[3]->GetElof()[5]->Letesz();
        khaz.GetKozpontok()[2]->GetElof()[1]->Letesz();
    }
}
}
void test_4PeldaProgram(){
    Kapcsolohaz khaz("../elofizetok.txt", 1, 200, 2);
    Ember valaki("Kiss Julia", 1997, 2, 28, "Budapest");
    Ember masik("Kardos Bela", 1876, 3, 12, "Pecs");
    khaz.GetKozpontok()[3]->UjElofizeto(valaki);
    khaz.GetKozpontok()[5]->UjElofizeto(masik);
    khaz.GetKozpontok()[0]->GetElof()[4]->Call(6005);
    khaz.GetKozpontok()[5]->GetElof()[5]->MSG_Send("Halo!");
    try {
        khaz.GetKozpontok()[0]->GetElof()[3]->Call(1004);

    }
    catch(std::string e){
        std::cerr << e <<std::endl;
    }
    try {
        khaz.GetKozpontok()[0]->GetElof()[3]->Letesz();

    }
    catch(std::string e){
        std::cerr << e <<std::endl;
    }
    khaz.GetKozpontok()[5]->GetElof()[5]->Letesz();
    khaz.GetKozpontok()[0]->GetElof()[1]->Call(6000);
    try {
        khaz.GetKozpontok()[0]->GetElof()[4]->Call(6004);
    }
    catch(std::string e){
        std::cerr << e <<std::endl;
    }
    khaz.GetKozpontok()[5]->GetElof()[0]->Letesz();
    khaz.GetKozpontok()[0]->GetElof()[4]->Call(6004);
    khaz.GetKozpontok()[0]->GetElof()[4]->Letesz();


    khaz.GetKozpontok()[0]->GetElof()[0]->Call(1001);
    khaz.GetKozpontok()[0]->GetElof()[2]->Call(1003);
    try {
        khaz.GetKozpontok()[0]->GetElof()[4]->Call(1005);
    }
    catch(std::string e){
        std::cerr << e <<std::endl;
    }
    khaz.GetKozpontok()[0]->GetElof()[0]->Letesz();
    khaz.GetKozpontok()[0]->GetElof()[2]->Letesz();
    khaz.GetKozpontok()[0]->GetElof()[4]->CallByName(1, "Feher Barna", 1998, 6, 21, "Pecs");
    khaz.GetKozpontok()[0]->GetElof()[4]->MSG_Send("Szia Barna vegre szabad a vonal. Megadnad a telefonszamodat?");
    khaz.GetKozpontok()[0]->GetElof()[5]->MSG_Send("Persze, 1005");
    khaz.GetKozpontok()[0]->GetElof()[5]->Letesz();

}