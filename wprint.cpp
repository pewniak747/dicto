/*******************************************************************************/
/** dicto v 1.3 WPrint class implementation file                              **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#include <QGridLayout>
#include <QPrintDialog>
#include "wprint.h"
#include "wmain.h"

WPrint::WPrint(QWidget *parent) {
	this->setWindowTitle(tr("Printing preferences"));
	sizeBox = new QSpinBox;
		sizeBox->setRange(5, 25);
		sizeBox->setValue(12);
	sizeLabel = new QLabel(tr("Font size:"));
	printBox = new QComboBox;
		printBox->addItem(tr("all"));
		printBox->addItem(tr("learned only"));
		printBox->addItem(tr("unlearned only"));
	printLabel = new QLabel(tr("Print:"));
	submitButton = new QPushButton(tr("Next"));
	cancelButton = new QPushButton(tr("Cancel"));
	
	QGridLayout *mainLayout = new QGridLayout;
		mainLayout->addWidget(sizeLabel, 0, 0);
		mainLayout->addWidget(sizeBox, 0, 1);
		mainLayout->addWidget(printLabel, 1, 0);
		mainLayout->addWidget(printBox, 1, 1);
		mainLayout->addWidget(cancelButton, 2, 0);
		mainLayout->addWidget(submitButton, 2, 1);
	this->setLayout(mainLayout);
	
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(submitButton, SIGNAL(clicked()), this, SLOT(print()));
	
	wMain->centerWidgetOnScreen(this);
}

void WPrint::print() {
	this->printmode = printBox->currentIndex();
	this->fontsize = sizeBox->value();
	//QMessageBox::information(wMain, tr(""), tr("%1 %2").arg(fontsize).arg(printmode));
		
	QPrintDialog printDialog(wMain->printer, this);
	this->hide();
    if (printDialog.exec() == QDialog::Accepted) {
		QFont *printFont = new QFont;
		printFont->setPixelSize(fontsize);
		
        wMain->printer->setPageMargins(30, 30, 30, 30, QPrinter::Point);
        QPainter painter;
        painter.begin(wMain->printer);
        
        int where = 0;

        painter.drawText(0, where, tr("Filename: %1").arg(wMain->cDocument->filename));
        where+=20;
        painter.drawText(0, where, tr("dicto - vocabulary learning software http://dicto.sourceforge.net"));
        where+=fontsize+fontsize/3+20;
        painter.setFont(*printFont);
        for(int i=0; i<wMain->cDocument->dictionary.size(); i++) {
			if(printmode == 0 || (printmode == 1 && wMain->cDocument->dictionary[i].wordstatus) || (printmode == 2 && !wMain->cDocument->dictionary[i].wordstatus)) {
				painter.drawText(0, where, tr("%1").arg(wMain->cDocument->dictionary[i].word));
				painter.drawText(250, where, tr("%1").arg(wMain->cDocument->dictionary[i].translation));
				where+=fontsize+fontsize/3;
			}
            
            if(where > 900) {
                wMain->printer->newPage();
                where = 0;
            }
        }
        painter.end();
    }
    this->close();
}

void WPrint::cancel() {
	wMain->setMode(enabledMode);
	this->close();
}

void WPrint::closeEvent(QCloseEvent * e) {
    wMain->setMode(enabledMode);
    e->accept();
}

