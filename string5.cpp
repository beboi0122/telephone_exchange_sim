#include <iostream>
#include <cstring>
#include "memtrace.h"
#include "string5.h"

using std::cin;
using std::ios_base;

/// Konstruktor: egy char karakterből (createStrFromChar)
String::String(char ch) {
    len = 1;
    pData = new char[len+1];
    pData[0] = ch;
    pData[1] = '\0';
}


String::String(const char *p) {
    len = strlen(p);
    pData = new char[len+1];
    strcpy(pData, p);
}

String::String(const String& s1) {
    len = s1.len;
    pData = new char[len+1];
    strcpy(pData, s1.pData);
}

String& String::operator=(const String& rhs_s) {
    if (this != &rhs_s) {
        delete[] pData;
        len = rhs_s.len;
        pData = new char[len+1];
        strcpy(pData, rhs_s.pData);
    }
    return *this;
}

char& String::operator[](unsigned int idx) {
    if (idx >= len) throw "String: indexelesi hiba";
    return pData[idx];
}

const char& String::operator[](unsigned int idx) const {
    if (idx >= len) throw "String: indexelesi hiba";
    return pData[idx];
}

String String::operator+(const String& rhs_s) const {
    String temp;
    temp.len = len + rhs_s.len;
    delete []temp.pData;
    temp.pData = new char[temp.len+1];
    strcpy(temp.pData, pData);
    strcat(temp.pData, rhs_s.pData);

    return temp;

}
bool String::operator==(const String& s){
    if(len!=s.len){return false;}
    for(unsigned i=0; i!=len; ++i){
        if(pData[i]!=s.pData[i]){
            return false;
        }
    }
    return true;
}
bool String::operator!=(const String& s){
    if(len!=s.len){return true;}
    for(unsigned i=0; i!=len; ++i){
        if(pData[i]!=s.pData[i]){
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const String& s0) {
    os << s0.c_str();
    return os;
}


