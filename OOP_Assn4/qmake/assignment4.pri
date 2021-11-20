#
# Common build settings for assignment 4
#
myROOT_DIR = $$absolute_path($$PWD)

# Variable declaration for convenience
mySRC_DIR = $$myROOT_DIR/../src
myINCLUDE_DIR = $$myROOT_DIR/../include
myTEST_DIR = $$myROOT_DIR/../test
myDEST_ROOT = $$myROOT_DIR/../build

mySRC_DIR = $$clean_path($$mySRC_DIR)
myINCLUDE_DIR = $$clean_path($$myINCLUDE_DIR)
myTEST_DIR = $$clean_path($$myTEST_DIR)
myDEST_DIR = $$clean_path($$myDEST_DIR)

# Make include files visible
INCLUDEPATH += $$myINCLUDE_DIR

OBJECTS_DIR = $$myDEST_ROOT/objects
MOC_DIR = $$myDEST_ROOT/moc
RCC_DIR = $$myDEST_ROOT/rcc
UI_DIR = $$myDEST_ROOT/ui
