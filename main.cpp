/*******************************************************************************/
/** dicto v 1.3 main file                                                     **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

/**svn test**/

#include <QtGui>
#include <QApplication>
#include "wmain.h"
#include <iostream>

    QApplication *application;

    WMain *wMain;

int main(int argc, char *argv[]) {
    application = new QApplication (argc, argv);
    
    //some localisation mess
    QTranslator translator;
	translator.load("./dicto_pl");
	QString locale=application->tr("%1").arg(QLocale::system().name());
	//locale="eng";
	if(locale == "pl_PL") {
		application->installTranslator(&translator);
	}

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    wMain=new WMain;
    wMain->show();
    
    if(argc > 1) {
		QDir dir;
		QString fname = argv[1];
		
		if(fname[0] != '/' && (fname.size() > 1 && fname[1] != ':')) {
			fname.prepend(dir.absolutePath()+"/");
		}
		std::cout << "Opening file: " << fname.toStdString() << "\n";
		if(!fname.isEmpty()) wMain->cDocument->readFromFile(fname);
	}
    
    return application->exec();
}
