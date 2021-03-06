######################################################################
# Automatically generated by qmake (2.01a) ?r. mar 17 18:16:23 2010
######################################################################

TEMPLATE = app
TARGET = dicto
RC_FILE = resources/dicto.rc
DEPENDPATH += . resources src translations
INCLUDEPATH += . src
OBJECTS_DIR = obj/
MOC_DIR = obj/
RCC_DIR = obj/
TRANSLATIONS =  translations/dicto_pl.ts \
                translations/dicto_ru.ts
RESOURCES += resources/dicto.qrc

# Input
HEADERS += src/cdocument.h \
           src/centry.h \
           src/wabout.h \
           src/wdialog.h \
           src/wmain.h \
           src/wprepare.h \
           src/wprint.h \
           src/wprops.h \
           src/wsettings.h
SOURCES += src/cdocument.cpp \
           src/centry.cpp \
           src/main.cpp \
           src/wabout.cpp \
           src/wdialog.cpp \
           src/wmain.cpp \
           src/wmain_exam.cpp \
           src/wmain_test.cpp \
           src/wmain_utils.cpp \
           src/wprepare.cpp \
           src/wprint.cpp \
           src/wprops.cpp \
           src/wsettings.cpp

