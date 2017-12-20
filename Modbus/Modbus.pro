TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    modbus.cpp \
    modbusobject.cpp

HEADERS += \
    modbus.h \
    modbusobject.h
