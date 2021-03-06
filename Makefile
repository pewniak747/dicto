#############################################################################
# Makefile for building: dicto
# Generated by qmake (2.01a) (Qt 4.6.2) on: ?r. mar 17 18:20:11 2010
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
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Isrc -Iobj
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

SOURCES       = src/cdocument.cpp \
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
		src/wsettings.cpp obj/moc_wabout.cpp \
		obj/moc_wdialog.cpp \
		obj/moc_wmain.cpp \
		obj/moc_wprepare.cpp \
		obj/moc_wprint.cpp \
		obj/moc_wprops.cpp \
		obj/moc_wsettings.cpp \
		obj/qrc_dicto.cpp
OBJECTS       = obj/cdocument.o \
		obj/centry.o \
		obj/main.o \
		obj/wabout.o \
		obj/wdialog.o \
		obj/wmain.o \
		obj/wmain_exam.o \
		obj/wmain_test.o \
		obj/wmain_utils.o \
		obj/wprepare.o \
		obj/wprint.o \
		obj/wprops.o \
		obj/wsettings.o \
		obj/moc_wabout.o \
		obj/moc_wdialog.o \
		obj/moc_wmain.o \
		obj/moc_wprepare.o \
		obj/moc_wprint.o \
		obj/moc_wprops.o \
		obj/moc_wsettings.o \
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
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/dicto1.0.0/ && $(COPY_FILE) --parents src/cdocument.h src/centry.h src/wabout.h src/wdialog.h src/wmain.h src/wprepare.h src/wprint.h src/wprops.h src/wsettings.h obj/dicto1.0.0/ && $(COPY_FILE) --parents resources/dicto.qrc obj/dicto1.0.0/ && $(COPY_FILE) --parents src/cdocument.cpp src/centry.cpp src/main.cpp src/wabout.cpp src/wdialog.cpp src/wmain.cpp src/wmain_exam.cpp src/wmain_test.cpp src/wmain_utils.cpp src/wprepare.cpp src/wprint.cpp src/wprops.cpp src/wsettings.cpp obj/dicto1.0.0/ && $(COPY_FILE) --parents translations/dicto_pl.ts translations/dicto_ru.ts obj/dicto1.0.0/ && (cd `dirname obj/dicto1.0.0` && $(TAR) dicto1.0.0.tar dicto1.0.0 && $(COMPRESS) dicto1.0.0.tar) && $(MOVE) `dirname obj/dicto1.0.0`/dicto1.0.0.tar.gz . && $(DEL_FILE) -r obj/dicto1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: obj/moc_wabout.cpp obj/moc_wdialog.cpp obj/moc_wmain.cpp obj/moc_wprepare.cpp obj/moc_wprint.cpp obj/moc_wprops.cpp obj/moc_wsettings.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) obj/moc_wabout.cpp obj/moc_wdialog.cpp obj/moc_wmain.cpp obj/moc_wprepare.cpp obj/moc_wprint.cpp obj/moc_wprops.cpp obj/moc_wsettings.cpp
obj/moc_wabout.cpp: src/wabout.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wabout.h -o obj/moc_wabout.cpp

obj/moc_wdialog.cpp: src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h \
		src/wdialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wdialog.h -o obj/moc_wdialog.cpp

obj/moc_wmain.cpp: src/cdocument.h \
		src/centry.h \
		src/wabout.h \
		src/wmain.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wmain.h -o obj/moc_wmain.cpp

obj/moc_wprepare.cpp: src/wprepare.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wprepare.h -o obj/moc_wprepare.cpp

obj/moc_wprint.cpp: src/wprint.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wprint.h -o obj/moc_wprint.cpp

obj/moc_wprops.cpp: src/wprops.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wprops.h -o obj/moc_wprops.cpp

obj/moc_wsettings.cpp: src/wsettings.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/wsettings.h -o obj/moc_wsettings.cpp

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

obj/cdocument.o: src/cdocument.cpp src/cdocument.h \
		src/centry.h \
		src/wmain.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/cdocument.o src/cdocument.cpp

obj/centry.o: src/centry.cpp src/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/centry.o src/centry.cpp

obj/main.o: src/main.cpp src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/wabout.o: src/wabout.cpp src/wabout.h \
		src/wmain.h \
		src/cdocument.h \
		src/centry.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wabout.o src/wabout.cpp

obj/wdialog.o: src/wdialog.cpp src/wdialog.h \
		src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wdialog.o src/wdialog.cpp

obj/wmain.o: src/wmain.cpp src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h \
		src/wdialog.h \
		src/wprepare.h \
		src/wsettings.h \
		src/wprops.h \
		src/wprint.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain.o src/wmain.cpp

obj/wmain_exam.o: src/wmain_exam.cpp src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_exam.o src/wmain_exam.cpp

obj/wmain_test.o: src/wmain_test.cpp src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_test.o src/wmain_test.cpp

obj/wmain_utils.o: src/wmain_utils.cpp src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wmain_utils.o src/wmain_utils.cpp

obj/wprepare.o: src/wprepare.cpp src/wprepare.h \
		src/cdocument.h \
		src/centry.h \
		src/wmain.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wprepare.o src/wprepare.cpp

obj/wprint.o: src/wprint.cpp src/wprint.h \
		src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wprint.o src/wprint.cpp

obj/wprops.o: src/wprops.cpp src/wprops.h \
		src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wprops.o src/wprops.cpp

obj/wsettings.o: src/wsettings.cpp src/wsettings.h \
		src/wmain.h \
		src/cdocument.h \
		src/centry.h \
		src/wabout.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wsettings.o src/wsettings.cpp

obj/moc_wabout.o: obj/moc_wabout.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wabout.o obj/moc_wabout.cpp

obj/moc_wdialog.o: obj/moc_wdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wdialog.o obj/moc_wdialog.cpp

obj/moc_wmain.o: obj/moc_wmain.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wmain.o obj/moc_wmain.cpp

obj/moc_wprepare.o: obj/moc_wprepare.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wprepare.o obj/moc_wprepare.cpp

obj/moc_wprint.o: obj/moc_wprint.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wprint.o obj/moc_wprint.cpp

obj/moc_wprops.o: obj/moc_wprops.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wprops.o obj/moc_wprops.cpp

obj/moc_wsettings.o: obj/moc_wsettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_wsettings.o obj/moc_wsettings.cpp

obj/qrc_dicto.o: obj/qrc_dicto.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/qrc_dicto.o obj/qrc_dicto.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

