#include <iostream>
#include <iomanip>
#include "datum.h"
#include "memtrace.h"

std::ostream& operator<<(std::ostream& os, const Datum& d){
    return os<< d.getEv() << "." << std::setw(2) << std::setfill('0') << d.getHo() << "." << std::setw(2) << std::setfill('0') << d.getNap();
}