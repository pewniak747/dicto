/*******************************************************************************/
/** dicto v 1.3 WPrepare class implementation file                            **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#include "wprepare.h"
#include "wmain.h"
#include "cdocument.h"

WPrepare::WPrepare(QWidget *parent, bool exam) : QWidget(parent) {
    wMain->setMode(disabledMode);
    if(!exam) this->setWindowTitle(tr("Prepare test"));
    else this->setWindowTitle(tr("Prepare exam"));

    setWindowIcon(QIcon(ICON));

    numberLabel=new QLabel(tr("Words:"), this);
    intoforeignLabel=new QLabel(tr("Translation:"), this);
    //includeLabel=new QLabel(tr("Dodaj nauczone"), this);
    //counterLabel=new QLabel(tr("c"), this);

    numberSlider=new QSlider(Qt::Horizontal, this);
        numberSlider->setRange(1, wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
        numberSlider->setValue(numberSlider->maximum());//wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
        updateSlider();
    numberBox = new QSpinBox;
		numberBox->setRange(1, wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
		numberBox->setValue(numberBox->maximum());

    //includeBox=new QCheckBox(this);
    intoforeignCombo=new QComboBox(this);
        intoforeignCombo->addItem(tr("%1 - %2")
                                            .arg(wMain->cDocument->lang_native==""?tr("mother language"):wMain->cDocument->lang_native)
                                            .arg(wMain->cDocument->lang_foreign==""?tr("foreign language"):wMain->cDocument->lang_foreign));
        intoforeignCombo->addItem(tr("%1 - %2")
                                            .arg(wMain->cDocument->lang_foreign==""?tr("foreign language"):wMain->cDocument->lang_foreign)
                                            .arg(wMain->cDocument->lang_native==""?tr("mother language"):wMain->cDocument->lang_native));

    startButton=new QPushButton(tr("Start!"), this);
    cancelButton=new QPushButton(tr("Cancel"), this);
    
    includeLabel = new QLabel(tr("Include learned"));
    includeBox = new QCheckBox;
		includeBox->setChecked(false);
	
	ignoreLabel = new QLabel(tr("Ignore synonyms"));
	ignoreBox = new QCheckBox;
		ignoreBox->setChecked(false);


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

    resize(400, 100);

    QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);

    if(!exam) {
        connect(startButton, SIGNAL(clicked()), this, SLOT(startTest()));
        connect(submitShortcut, SIGNAL(activated()), this, SLOT(startTest()));
    }
    else {
        connect(startButton, SIGNAL(clicked()), this, SLOT(startExam()));
        connect(submitShortcut, SIGNAL(activated()), this, SLOT(startExam()));
    }
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(numberSlider, SIGNAL(valueChanged(int)), this, SLOT(updateSlider()));
    connect(numberSlider, SIGNAL(valueChanged(int)), numberBox, SLOT(setValue(int)));
    connect(numberBox, SIGNAL(valueChanged(int)), numberSlider, SLOT(setValue(int)));
    connect(includeBox, SIGNAL(stateChanged(int)), this, SLOT(includeChanged()));
    


    wMain->centerWidgetOnScreen(this);
}

void WPrepare::cancel() {
    wMain->setMode(enabledMode);
    this->close();
}

void WPrepare::startTest() {
    unsigned howmany=numberSlider->value();
    bool include = includeBox->isChecked();
    bool ignoreSynonyms = ignoreBox->isChecked();
    bool intoforeign=false;
    switch(intoforeignCombo->currentIndex()) {
        case 0 : intoforeign=true; break;
        case 1 : intoforeign=false; break;
    }

    wMain->setMode(enabledMode);
    this->close();
    wMain->test(howmany, intoforeign, include, ignoreSynonyms);
}

void WPrepare::startExam() {
    unsigned howmany=numberSlider->value();
    bool include = includeBox->isChecked();
    bool ignoreSynonyms = ignoreBox->isChecked();
    bool intoforeign=false;
    switch(intoforeignCombo->currentIndex()) {
        case 0 : intoforeign=true; break;
        case 1 : intoforeign=false; break;
    }

    wMain->setMode(enabledMode);
    this->close();
    wMain->exam(howmany, intoforeign, include, ignoreSynonyms);
}

void WPrepare::includeChanged() {
	bool state = includeBox->isChecked();
	
	if(state) {
		numberBox->setMaximum(wMain->cDocument->dictionary.size());
		numberSlider->setMaximum(wMain->cDocument->dictionary.size());
	}
	else  {
		numberBox->setMaximum(wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
		numberSlider->setMaximum(wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
	}
	
	numberSlider->setValue(numberSlider->maximum());
}

void WPrepare::updateSlider() {
    /*counterLabel->setText(tr("%1/%2")
                          .arg(numberSlider->value())
                          .arg(wMain->cDocument->dictionary.size()-wMain->cDocument->passed())
                          );*/
    //numberBox->setValue(1);//numberSlider->value());
}

void WPrepare::closeEvent(QCloseEvent * a) {
    wMain->setMode(enabledMode);
    a->accept();
}
