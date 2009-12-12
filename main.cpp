/*******************************************************************************/
/** dicto v 1.1 main file                                                     **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#include <QtGui>
#include <QApplication>
#include "wmain.h"

    QApplication *application;

    WMain *wMain;

int main(int argc, char *argv[]) {
    application = new QApplication (argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr (QTextCodec::codecForName("UTF-8"));

    wMain=new WMain;
    wMain->show();
    return application->exec();
}
