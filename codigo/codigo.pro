TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        LZ78.cpp \
        RLE.cpp \
        archivos.cpp \
        encriptacion_bits.cpp \
        main.cpp

HEADERS += \
    LZ78.h \
    RLE.h \
    archivos.h \
    encriptacion_bits.h

DISTFILES += \
    texto_5_4
