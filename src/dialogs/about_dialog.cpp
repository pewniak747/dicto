// dicto v 1.3 AboutDialog class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "about_dialog.h"

// AboutDialog constructor
AboutDialog::AboutDialog(WMain *mainWindow) {
	if(!mainWindow) return;
	
	// set window properties
	setWindowTitle(tr("dicto %1").arg(VERSION));
	setFixedWidth(350);
	setFixedHeight(320);
	setWindowIcon(QIcon(ICON));
	mainWindow->centerWidgetOnScreen(this);
	
	setAttribute(Qt::WA_DeleteOnClose);
	this->mainWindow = mainWindow;
	mainWindow->setMode(disabledMode);
	
	// create widgets
	image = new QLabel;
		QPixmap pixmap(ICON);
		pixmap = pixmap.scaledToWidth(128, Qt::SmoothTransformation);
		pixmap = pixmap.scaledToHeight(128, Qt::SmoothTransformation);
		image->setPixmap(pixmap);
	infoLabel = new QLabel(tr("dicto %1").arg(VERSION), this);
	infoField = new QTextBrowser();
	okButton = new QPushButton(tr("OK"), this);
	urlLabel = new QLabel("<a href='http://pewniak747.github.com/dicto'>"+tr("Visit website")+"</a>", this);
		
		
	// set default values
	infoLabel->setAlignment(Qt::AlignHCenter);
	urlLabel->setTextFormat(Qt::RichText);
	urlLabel-> setOpenExternalLinks(true);
	urlLabel->setAlignment(Qt::AlignHCenter);
	image->setAlignment(Qt::AlignHCenter);
	QFont boldFont;
	boldFont.setBold(true);
	infoLabel->setFont(boldFont);
	infoField->setReadOnly(true);
	infoField->setText(tr("Created by Tomasz 'pewniak747' Pewiński\n")+
tr("Contributors:\n"));

	// add layout
	QVBoxLayout *mainLayout = new QVBoxLayout;
		mainLayout->addWidget(image);
		mainLayout->addWidget(infoLabel);
		mainLayout->addWidget(urlLabel);
		mainLayout->addWidget(infoField);
		mainLayout->addWidget(okButton);
	setLayout(mainLayout);
	
	//connect signals and slots
	connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
}

// closes window
void AboutDialog::closeEvent(QCloseEvent * a) {
	mainWindow->setMode(enabledMode);
	a->accept();
}

