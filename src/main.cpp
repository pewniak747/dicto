// dicto v 1.3 main file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include <QtGui>
#include <QApplication>
#include "wmain.h"

QApplication *application;
WMain *wMain;

int main(int argc, char *argv[]) {
	application = new QApplication (argc, argv);
	
		// set codecs
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	
	// localisation mess
	QTranslator translator;
	translator.load("./translations/dicto_pl");
	QString locale=application->tr("%1").arg(QLocale::system().name());
	if(locale == "pl_PL") application->installTranslator(&translator);
	
	// create main window
	wMain = new WMain;
	
	//parse argv
	if(argc > 1) {
		QDir dir;
		QString filename = argv[1];
		if(filename[0] != '/' && (filename.size() > 1 && filename[1] != ':')) 
			filename.prepend(dir.absolutePath()+"/");
		if(!filename.isEmpty()) wMain->cDocument->readFromFile(filename);
	}
	
	//show main window
	wMain->show();
	return application->exec();
}
