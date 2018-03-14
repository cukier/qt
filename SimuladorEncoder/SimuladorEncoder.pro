TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT = core serialport

SOURCES += main.cpp \
    encoder.cpp

HEADERS += \
    encoder.h
