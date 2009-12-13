// dicto v 1.3 WPrepare class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wprepare.h"
#include "cdocument.h"
#include "wmain.h"

// WPrepare constructor
WPrepare::WPrepare(QWidget *parent, bool exam) : QWidget(parent) {
	// set window properties
	wMain->setMode(disabledMode);
	setWindowTitle(exam?tr("Prepare exam"):tr("Prepare test"));
	setWindowIcon(QIcon(ICON));
	resize(400, 100);
	wMain->centerWidgetOnScreen(this);
	
	// create widgets
	numberLabel=new QLabel(tr("Words:"), this);
	intoforeignLabel=new QLabel(tr("Translation:"), this);
	numberSlider=new QSlider(Qt::Horizontal, this);
	numberBox = new QSpinBox;
	intoforeignCombo=new QComboBox(this);
	includeLabel = new QLabel(tr("Include learned"));
	includeBox = new QCheckBox;
	ignoreLabel = new QLabel(tr("Ignore synonyms"));
	ignoreBox = new QCheckBox;
	startButton=new QPushButton(tr("Start!"), this);
	cancelButton=new QPushButton(tr("Cancel"), this);
	
	//set default values to widgets
	includeChanged(0);
	numberSlider->setValue(numberSlider->maximum());
	numberBox->setValue(numberBox->maximum());
	intoforeignCombo->addItem(tr("%1 - %2")
		.arg(wMain->cDocument->lang_native==""?tr("mother language"):wMain->cDocument->lang_native)
		.arg(wMain->cDocument->lang_foreign==""?tr("foreign language"):wMain->cDocument->lang_foreign));
	intoforeignCombo->addItem(tr("%1 - %2")
		.arg(wMain->cDocument->lang_foreign==""?tr("foreign language"):wMain->cDocument->lang_foreign)
		.arg(wMain->cDocument->lang_native==""?tr("mother language"):wMain->cDocument->lang_native));
	includeBox->setChecked(false);
	ignoreBox->setChecked(false);
	
	// add layout
	QVBoxLayout *mainLayout=new QVBoxLayout;
		QGridLayout *gridLayout=new QGridLayout;
		gridLayout->addWidget(numberLabel, 0, 0);
		gridLayout->addWidget(intoforeignLabel, 1, 0);
		gridLayout->addWidget(includeLabel, 2, 0);
		gridLayout->addWidget(ignoreLabel, 3, 0);
		QHBoxLayout *lay2=new QHBoxLayout;
			lay2->addWidget(numberSlider);
			lay2->addWidget(numberBox);
		gridLayout->addLayout(lay2, 0, 1);
		gridLayout->addWidget(intoforeignCombo, 1, 1);
		gridLayout->addWidget(includeBox, 2, 1);
		gridLayout->addWidget(ignoreBox, 3, 1);
	mainLayout->addLayout(gridLayout);
		QHBoxLayout *buttonLayout=new QHBoxLayout;
		buttonLayout->addWidget(startButton);
		buttonLayout->addWidget(cancelButton);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	// create shortcuts
	QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);

	// connect signals and slots
	if(exam) {
		connect(startButton, SIGNAL(clicked()), this, SLOT(startExam()));
		connect(submitShortcut, SIGNAL(activated()), this, SLOT(startExam()));
	}
	else {
		connect(startButton, SIGNAL(clicked()), this, SLOT(startTest()));
		connect(submitShortcut, SIGNAL(activated()), this, SLOT(startTest()));
	}
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(numberSlider, SIGNAL(valueChanged(int)), numberBox, SLOT(setValue(int)));
	connect(numberBox, SIGNAL(valueChanged(int)), numberSlider, SLOT(setValue(int)));
	connect(includeBox, SIGNAL(stateChanged(int)), this, SLOT(includeChanged(int)));
}

// starts test
void WPrepare::startTest() {
	bool intoforeign=false;
	switch(intoforeignCombo->currentIndex()) {
		case 0 : intoforeign=true; break;
		case 1 : intoforeign=false; break;
	}
	this->close();
	wMain->test(numberBox->value(), intoforeign, includeBox->isChecked(), ignoreBox->isChecked());
	
}

// starts exam
void WPrepare::startExam() {
	bool intoforeign=false;
	switch(intoforeignCombo->currentIndex()) {
		case 0 : intoforeign=true; break;
		case 1 : intoforeign=false; break;
	}
	this->close();
	wMain->exam(numberBox->value(), intoforeign, includeBox->isChecked(), ignoreBox->isChecked());
}

// updates slider and box with new values
void WPrepare::includeChanged(int state) {
	if(state == 2) {
		numberBox->setRange(1, wMain->cDocument->dictionary.size());
		numberSlider->setRange(1, wMain->cDocument->dictionary.size());
	}
	else  {
		numberBox->setRange(1, wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
		numberSlider->setRange(1, wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
	}
	numberSlider->setValue(numberSlider->maximum());
}

// closes window
void WPrepare::closeEvent(QCloseEvent * a) {
	wMain->setMode(enabledMode);
	a->accept();
}

