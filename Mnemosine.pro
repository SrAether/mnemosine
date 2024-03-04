TEMPLATE = app
TARGET = Mnemosine
QT = core gui multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += \
    main.cpp \
    manejoFicheros.cpp \
    ventana.cpp

HEADERS += \
    manejoFicheros.h \
    ventana.h

