TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt
QT  += core gui widgets

SOURCES += main.cpp \
    window.cpp \
    pizza.cpp

HEADERS += \
    window.h \
    pizza.h
