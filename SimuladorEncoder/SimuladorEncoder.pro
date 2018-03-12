TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT = core serialport

SOURCES += main.cpp \
    serialreader.cpp \
    serialwriter.cpp \
    encoder.cpp

HEADERS += \
    serialreader.h \
    serialwriter.h \
    encoder.h
