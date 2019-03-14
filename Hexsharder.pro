QT       += core gui widgets network

TARGET = Hexsharder
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    requestwrapper.cpp \
    lootmodel.cpp

HEADERS += \
        mainwindow.h \
    requestwrapper.h \
    lootmodel.h

FORMS += \
        mainwindow.ui
