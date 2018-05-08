QT -= gui
QT += network xml sql

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    ../cwf/configuration.cpp \
    ../cwf/controller.cpp \
    ../cwf/cppwebapplication.cpp \
    ../cwf/cppwebcontroller.cpp \
    ../cwf/cppwebserver.cpp \
    ../cwf/cstlcompiler.cpp \
    ../cwf/cstlcompilerattributes.cpp \
    ../cwf/cstlcompilerfor.cpp \
    ../cwf/cstlcompilerif.cpp \
    ../cwf/cstlcompilerimport.cpp \
    ../cwf/filemanager.cpp \
    ../cwf/filterchain.cpp \
    ../cwf/httpcookie.cpp \
    ../cwf/httpparser.cpp \
    ../cwf/httpreadrequest.cpp \
    ../cwf/metaclassparser.cpp \
    ../cwf/properties.cpp \
    ../cwf/qlistobject.cpp \
    ../cwf/request.cpp \
    ../cwf/requestdispatcher.cpp \
    ../cwf/response.cpp \
    ../cwf/session.cpp \
    ../cwf/sqlquery.cpp \
    ../cwf/urlencoder.cpp

HEADERS += \
    ../cwf/configuration.h \
    ../cwf/constants.h \
    ../cwf/controller.h \
    ../cwf/cppwebapplication.h \
    ../cwf/cppwebcontroller.h \
    ../cwf/cppwebframework_global.h \
    ../cwf/cppwebserver.h \
    ../cwf/cstlcompiler.h \
    ../cwf/cstlcompilerattributes.h \
    ../cwf/cstlcompilerfor.h \
    ../cwf/cstlcompilerif.h \
    ../cwf/cstlcompilerimport.h \
    ../cwf/cstlcompilerobject.h \
    ../cwf/filemanager.h \
    ../cwf/filter.h \
    ../cwf/filterchain.h \
    ../cwf/httpcookie.h \
    ../cwf/httpparser.h \
    ../cwf/httpreadrequest.h \
    ../cwf/metaclassparser.h \
    ../cwf/properties.h \
    ../cwf/qlistobject.h \
    ../cwf/qmapthreadsafety.h \
    ../cwf/request.h \
    ../cwf/requestdispatcher.h \
    ../cwf/response.h \
    ../cwf/session.h \
    ../cwf/sqldatabasestorage.h \
    ../cwf/sqlquery.h \
    ../cwf/urlencoder.h \
    ../cwf/variant.h

INCLUDEPATH += ../cwf/

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

#Strongly recommended
#LIBS += -ljemalloc
