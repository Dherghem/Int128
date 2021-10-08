TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    longlong.cpp \
    cparser.cpp \
    fromstring.tab.c

HEADERS += \
    longlong.hpp \
    cparser.h \
    fromstring.tab.h

#ccomp.input  = CSOURCES
#ccomp.output = ${QMAKE_FILE_BASE}.o
#ccomp.commands = gcc -c $$QMAKE_CXXFLAGS ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
#QMAKE_EXTRA_COMPILERS += ccomp

#CSOURCES += fromstring.tab.c
