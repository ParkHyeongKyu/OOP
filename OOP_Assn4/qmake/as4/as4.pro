#
# Common build settings for assignment 4 library
#

include(../assignment4.pri)

TEMPLATE = lib
CONFIG += debug staticlib c++1z
TARGET = as4
WARNINGS += -Wall

QT += widgets \
        multimedia \
        core

# Add source files for this project
# If your .cpp file is not specified in here, it will not be compiled
SOURCES += \
    $$mySRC_DIR/model/note.cpp \
    $$mySRC_DIR/model/pitch.cpp \
    $$mySRC_DIR/model/seq.cpp \
    $$mySRC_DIR/model/time.cpp \
    $$mySRC_DIR/model/song.cpp \
    $$mySRC_DIR/model/play.cpp \
    $$mySRC_DIR/io/seqio.cpp \
    $$mySRC_DIR/io/songio.cpp \
    $$mySRC_DIR/util/require.cpp \

# Add header files for this project
# If your .h file is not specified in here, you might not be able to include
# in other source files.
HEADERS += \
    $$myINCLUDE_DIR/model/note.h \
    $$myINCLUDE_DIR/model/pitch.h \
    $$myINCLUDE_DIR/model/seq.h \
    $$myINCLUDE_DIR/model/time.h \
    $$myINCLUDE_DIR/model/song.h \
    $$myINCLUDE_DIR/model/play.h \
    $$myINCLUDE_DIR/io/seqio.h \
    $$myINCLUDE_DIR/io/songio.h \
    $$myINCLUDE_DIR/util/require.h \ \

## Build target configuration
DESTDIR = $$myDEST_ROOT/as4

RESOURCES += \
    drum.qrc \
    melody.qrc
