#
# QMake build file for assignment 4
#
# It tries to build three targets
# 1. A static library that contains all the code in the project
#    (located at qmake/as4)
# 2. A launchable application
#    (located at qmake/app)
# 3. A Test suite
#    (located at qmake/test)
TEMPLATE = subdirs
SUBDIRS = qmake/as4 qmake/app qmake/test_model
qmake/app.depends = qmake/as4
qmake/test_model.depends = qmake/as4

## Uncomment these two lines to start Problem 1
SUBDIRS += qmake/test_io
qmake/test_io.depends = qmake/as4

HEADERS +=

CONFIG += ordered
