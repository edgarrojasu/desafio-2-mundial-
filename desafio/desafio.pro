TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += estadisticasjugador.h\
           estadisticasequipo.h\
           estadisticaspartido.h\
           jugador.h\
           equipo.h\
           lectorcsv.h

SOURCES += main.cpp \
           estadisticasjugador.cpp \
           estadisticasequipo.cpp\
           estadisticaspartido.cpp\
           jugador.cpp\
           equipo.cpp\
           lectorcsv.cpp
