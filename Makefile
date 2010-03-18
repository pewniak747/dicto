#############################################################################
# Makefile for building: dicto
# Generated by qmake (2.01a) (Qt 4.6.2) on: czw. mar 18 19:59:25 2010
# Project:  dicto.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile dicto.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Isrc -Isrc/mainwindow -Isrc/objects -Isrc/dialogs -I. -Isrc -Iobj
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/main.cpp \
		src/dialogs/about_dialog.cpp \
		src/dialogs/word_dialog.cpp \
		src/dialogs/prepare_dialog.cpp \
		src/dialogs/wprint.cpp \
		src/dialogs/properties_dialog.cpp \
		src/dialogs/wsettings.cpp \
		src/mainwindow/wmain.cpp \
		src/mainwindow/wmain_utils.cpp \
		src/objects/cdocument.cpp \
		src/objects/centry.cpp \
		src/widgets/wmain_exam.cpp \
		src/widgets/wmain_test.cpp obj/moc_about_dialog.cpp \
		obj/moc_word_dialog.cpp \
		obj/moc_prepare_dialog.cpp \
		obj/moc_wprint.cpp \
		obj/moc_properties_dialog.cpp \
		obj/moc_wsettings.cpp \
		obj/moc_wmain.cpp \
		obj/qrc_dicto.cpp
OBJECTS       = obj/main.o \
		obj/about_dialog.o \
		obj/word_dialog.o \
		obj/prepare_dialog.o \
		obj/wprint.o \
		obj/properties_dialog.o \
		obj/wsettings.o \
		obj/wmain.o \
		obj/wmain_utils.o \
		obj/cdocument.o \
		obj/centry.o \
		obj/wmain_exam.o \
		obj/wmain_test.o \
		obj/moc_about_dialog.o \
		obj/moc_word_dialog.o \
		obj/moc_prepare_dialog.o \
		obj/moc_wprint.o \
		obj/moc_properties_dialog.o \
		obj/moc_wsettings.o \
		obj/moc_wmain.o \
		obj/qrc_dicto.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		dicto.pro
QMAKE_TARGET  = dicto
DESTDIR       = 
TARGET        = dicto

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: dicto.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile dicto.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile dicto.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/dicto1.0.0 || $(MKDIR) obj/dicto1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/dicto1.0.0/ && $(COPY_FILE) --parents src/dialogs/about_dialog.h src/dialogs/word_dialog.h src/dialogs/prepare_dialog.h src/dialogs/wprint.h src/dialogs/properties_dialog.h src/dialogs/wsettings.h src/mainwindow/wmain.h src/objects/cdocument.h src/objects/centry.h obj/dicto1.0.0/ && $(COPY_FILE) --parents resources/dicto.qrc obj/dicto1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/dialogs/about_dialog.cpp src/dialogs/word_dialog.cpp src/dialogs/prepare_dialog.cpp src/dialogs/wprint.cpp src/dialogs/properties_dialog.cpp src/dialogs/wsettings.cpp src/mainwindow/wmain.cpp src/mainwindow/wmain_utils.cpp src/objects/cdocument.cpp src/objects/centry.cpp src/widgets/wmain_exam.cpp src/widgets/wmain_test.cpp obj/dicto1.0.0/ && $(COPY_FILE) --parents translations/dicto_pl.ts translations/dicto_ru.ts obj/dicto1.0.0/ && (cd `dirname obj/dicto1.0.0` && $(TAR) dicto1.0.0.tar dicto1.0.0 && $(COMPRESS) dicto1.0.0.tar) && $(MOVE) `dirname obj/dicto1.0.0`/dicto1.0.0.tar.gz . && $(DEL_FILE) -r obj/dicto1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: obj/moc_about_dialog.cpp obj/moc_word_dialog.cpp obj/moc_prepare_dialog.cpp obj/moc_wprint.cpp obj/moc_properties_dialog.cpp obj/moc_wsettings.cpp obj/moc_wmain.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) obj/moc_about_dialog.cpp obj/moc_word_dialog.cpp obj/moc_prepare_dialog.cpp obj/moc_wprint.cpp obj/moc_properties_dialog.cpp obj/moc_wsettings.cpp obj/moc_wmain.cpp
obj/moc_about_dialog.cpp: src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h \
		src/dialogs/about_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/about_dialog.h -o obj/moc_about_dialog.cpp

obj/moc_word_dialog.cpp: src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h \
		src/dialogs/word_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/word_dialog.h -o obj/moc_word_dialog.cpp

obj/moc_prepare_dialog.cpp: src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h \
		src/dialogs/prepare_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/prepare_dialog.h -o obj/moc_prepare_dialog.cpp

obj/moc_wprint.cpp: src/dialogs/wprint.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/wprint.h -o obj/moc_wprint.cpp

obj/moc_properties_dialog.cpp: src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h \
		src/dialogs/properties_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/properties_dialog.h -o obj/moc_properties_dialog.cpp

obj/moc_wsettings.cpp: src/dialogs/wsettings.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/dialogs/wsettings.h -o obj/moc_wsettings.cpp

obj/moc_wmain.cpp: src/objects/cdocument.h \
		src/objects/centry.h \
		src/mainwindow/wmain.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/mainwindow/wmain.h -o obj/moc_wmain.cpp

compiler_rcc_make_all: obj/qrc_dicto.cpp
compiler_rcc_clean:
	-$(DEL_FILE) obj/qrc_dicto.cpp
obj/qrc_dicto.cpp: resources/dicto.qrc \
		resources/dictologo.png \
		resources/pewniak747.jpg
	/usr/bin/rcc -name dicto resources/dicto.qrc -o obj/qrc_dicto.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

obj/main.o: src/main.cpp src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/about_dialog.o: src/dialogs/about_dialog.cpp src/dialogs/about_dialog.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/about_dialog.o src/dialogs/about_dialog.cpp

obj/word_dialog.o: src/dialogs/word_dialog.cpp src/dialogs/word_dialog.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/word_dialog.o src/dialogs/word_dialog.cpp

obj/prepare_dialog.o: src/dialogs/prepare_dialog.cpp src/dialogs/prepare_dialog.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/prepare_dialog.o src/dialogs/prepare_dialog.cpp

obj/wprint.o: src/dialogs/wprint.cpp src/dialogs/wprint.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wprint.o src/dialogs/wprint.cpp

obj/properties_dialog.o: src/dialogs/properties_dialog.cpp src/dialogs/properties_dialog.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/properties_dialog.o src/dialogs/properties_dialog.cpp

obj/wsettings.o: src/dialogs/wsettings.cpp src/dialogs/wsettings.h \
		src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wsettings.o src/dialogs/wsettings.cpp

obj/wmain.o: src/mainwindow/wmain.cpp src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h \
		src/dialogs/word_dialog.h \
		src/dialogs/wsettings.h \
		src/dialogs/about_dialog.h \
		src/dialogs/properties_dialog.h \
		src/dialogs/wprint.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain.o src/mainwindow/wmain.cpp

obj/wmain_utils.o: src/mainwindow/wmain_utils.cpp src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_utils.o src/mainwindow/wmain_utils.cpp

obj/cdocument.o: src/objects/cdocument.cpp src/objects/cdocument.h \
		src/objects/centry.h \
		src/mainwindow/wmain.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/cdocument.o src/objects/cdocument.cpp

obj/centry.o: src/objects/centry.cpp src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/centry.o src/objects/centry.cpp

obj/wmain_exam.o: src/widgets/wmain_exam.cpp src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_exam.o src/widgets/wmain_exam.cpp

obj/wmain_test.o: src/widgets/wmain_test.cpp src/mainwindow/wmain.h \
		src/objects/cdocument.h \
		src/objects/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_test.o src/widgets/wmain_test.cpp

obj/moc_about_dialog.o: obj/moc_about_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_about_dialog.o obj/moc_about_dialog.cpp

obj/moc_word_dialog.o: obj/moc_word_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_word_dialog.o obj/moc_word_dialog.cpp

obj/moc_prepare_dialog.o: obj/moc_prepare_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_prepare_dialog.o obj/moc_prepare_dialog.cpp

obj/moc_wprint.o: obj/moc_wprint.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wprint.o obj/moc_wprint.cpp

obj/moc_properties_dialog.o: obj/moc_properties_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_properties_dialog.o obj/moc_properties_dialog.cpp

obj/moc_wsettings.o: obj/moc_wsettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wsettings.o obj/moc_wsettings.cpp

obj/moc_wmain.o: obj/moc_wmain.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wmain.o obj/moc_wmain.cpp

obj/qrc_dicto.o: obj/qrc_dicto.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qrc_dicto.o obj/qrc_dicto.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

