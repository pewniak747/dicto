// dicto v 1.3 WAbout class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wabout.h"
#include "wmain.h"

// WAbout constructor
WAbout::WAbout(QWidget *parent) : QWidget(parent) {
	// set window properties
	setWindowTitle(tr("dicto %1").arg(VERSION));
	setFixedSize(200, 300);
	setWindowIcon(QIcon(ICON));
	wMain->centerWidgetOnScreen(this);
	
	// create widgets
	image = new QLabel;
		QPixmap pixmap(":/pewniak747.jpg");
		pixmap.scaledToWidth(185);
		pixmap.scaledToHeight(185);
		image->setPixmap(pixmap);
	okButton = new QPushButton(tr("OK"), this);
	infoLabel = new QLabel(tr("dicto - version %1\nCreated by Tomasz 'pewniak747' Pewiński").arg(VERSION), this);
	urlLabel = new QLabel(tr("<a href='http://pewniak747.github.com/dicto'>Visit website</a>"), this);
		
		
	// set default values
	infoLabel->setWordWrap(true);
	infoLabel->setAlignment(Qt::AlignHCenter);
	urlLabel->setTextFormat(Qt::RichText);
	urlLabel-> setOpenExternalLinks(true);
	urlLabel->setAlignment(Qt::AlignHCenter);

	// add layout
	QVBoxLayout *mainLayout = new QVBoxLayout;
		mainLayout->addWidget(image);
		mainLayout->addWidget(infoLabel);
		mainLayout->addWidget(urlLabel);
		mainLayout->addWidget(okButton);
	this->setLayout(mainLayout);
	
	//connect signals and slots
	connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
}

// closes window
void WAbout::closeEvent(QCloseEvent * a) {
	wMain->setMode(enabledMode);
	a->accept();
}

