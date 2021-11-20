#
# QMake build configuration for assignment4 test suite
#
#   Executable will be located under ./build/test/ after build
include(../assignment4.pri)

CONFIG += debug testcase c++1z
TARGET = test_model

QT += testlib

SOURCES += \
        $$myTEST_DIR/test_model.cpp

## Build target configuration
DESTDIR = $$myDEST_ROOT/test

PRE_TARGETDEPS += $$myDEST_ROOT/as4/libas4.a
LIBS += -L$$myDEST_ROOT/as4 -las4

