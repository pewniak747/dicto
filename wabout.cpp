/*****************************************************************************/
/** dicto v 1.1 WAbout class implementation ile                             **/
/** This file is published under GNU/GPL licence                            **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                 **/
/** author: Tomasz Pewinski "pewniak747"                                    **/
/** contact: pewniak747@gmail.com                                           **/
/** http://dicto.ugu.pl                                                     **/
/*****************************************************************************/

#include "wabout.h"
#include "wmain.h"

WAbout::WAbout(QWidget *parent) : QWidget(parent) {

    this->setWindowTitle(tr("O dicto"));
    okButton = new QPushButton();
    okButton->setText(tr("OK"));
    infoLabel = new QLabel();
    infoLabel->setText(tr("dicto v. %1\nProgram stworzony przez Tomasza Pewińskiego\nhttp://dicto.ugu.pl").arg(VERSION));
    infoLabel->setWordWrap(true);
    QPixmap pixmap(":/pewniak747.jpg");
    image = new QLabel;
    image->setPixmap(pixmap);
    QVBoxLayout *lay = new QVBoxLayout;
        lay->addWidget(image);
        lay->addWidget(infoLabel);
        lay->addWidget(okButton);
    this->setLayout(lay);
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
    this->setFixedSize(185, 300);
    this->setWindowIcon(QIcon(ICON));
    wMain->centerWidgetOnScreen(this);
    this->show();
}

void WAbout::closeEvent(QCloseEvent * a) {
    wMain->setMode(enabledMode);
    a->accept();
}

WAbout::~WAbout() {

}
