cmake_minimum_required(VERSION 3.21)
project (telefonkozpont)

set(CMAKE_CXX_STANDARD 11)

add_executable(telefonkozpont main.cpp datum.cpp datum.h elofizeto.h testek.h testek.cpp elofizeto.cpp ember.h ember.cpp Kapcsolat.h Kapcsolat.cpp kozpont.h kozpont.cpp kapcs_callback.h memtrace.h memtrace.cpp gtest_lite.h ktabla.h ktabla.cpp Kapcsolohaz.cpp Kapcsolohaz.h string5.cpp string5.h)
