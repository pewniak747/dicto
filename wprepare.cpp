/*******************************************************************************/
/** dicto v 1.1 WPrepare class implementation file                            **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#include "wprepare.h"
#include "wmain.h"
#include "cdocument.h"

WPrepare::WPrepare(QWidget *parent, bool exam) : QWidget(parent) {
    wMain->setMode(disabledMode);
    if(!exam) this->setWindowTitle(tr("Przygotuj test"));
    else this->setWindowTitle(tr("Przygotuj egzamin"));

    setWindowIcon(QIcon(ICON));

    numberLabel=new QLabel(tr("Liczba słów"), this);
    intoforeignLabel=new QLabel(tr("Tłumaczenie:"), this);
    //includeLabel=new QLabel(tr("Dodaj nauczone"), this);
    counterLabel=new QLabel(tr("c"), this);

    numberSlider=new QSlider(Qt::Horizontal, this);
        numberSlider->setRange(1, wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
        numberSlider->setValue(wMain->cDocument->dictionary.size()-wMain->cDocument->passed());
        updateSlider();

    //includeBox=new QCheckBox(this);
    intoforeignCombo=new QComboBox(this);
        intoforeignCombo->addItem(tr("%1 - %2")
                                            .arg(wMain->cDocument->lang_native==""?"ojczysty":wMain->cDocument->lang_native)
                                            .arg(wMain->cDocument->lang_foreign==""?"obcy":wMain->cDocument->lang_foreign));
        intoforeignCombo->addItem(tr("%1 - %2")
                                            .arg(wMain->cDocument->lang_foreign==""?"obcy":wMain->cDocument->lang_foreign)
                                            .arg(wMain->cDocument->lang_native==""?"ojczysty":wMain->cDocument->lang_native));

    startButton=new QPushButton(tr("Start!"), this);
    cancelButton=new QPushButton(tr("Anuluj"), this);

    QVBoxLayout *mainLayout=new QVBoxLayout;
        QGridLayout *gridLayout=new QGridLayout;
        gridLayout->addWidget(numberLabel, 0, 0);
        gridLayout->addWidget(intoforeignLabel, 1, 0);
        //gridLayout->addWidget(includeLabel, 2, 0);
        QHBoxLayout *lay2=new QHBoxLayout;
            lay2->addWidget(numberSlider);
            lay2->addWidget(counterLabel);
        gridLayout->addLayout(lay2, 0, 1);
        gridLayout->addWidget(intoforeignCombo, 1, 1);
       //gridLayout->addWidget(includeBox, 2, 1);
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


    wMain->centerWidgetOnScreen(this);
}

void WPrepare::cancel() {
    wMain->setMode(enabledMode);
    this->close();
}

void WPrepare::startTest() {
    unsigned howmany=numberSlider->value();
    bool include=false;
    bool intoforeign=false;
    switch(intoforeignCombo->currentIndex()) {
        case 0 : intoforeign=true; break;
        case 1 : intoforeign=false; break;
    }

    wMain->setMode(enabledMode);
    this->close();
    wMain->test(howmany, intoforeign, include);
}

void WPrepare::startExam() {
    unsigned howmany=numberSlider->value();
    bool include=false;
    bool intoforeign=false;
    switch(intoforeignCombo->currentIndex()) {
        case 0 : intoforeign=true; break;
        case 1 : intoforeign=false; break;
    }

    wMain->setMode(enabledMode);
    this->close();
    wMain->exam(howmany, intoforeign, include);
}

void WPrepare::updateSlider() {
    counterLabel->setText(tr("%1/%2")
                          .arg(numberSlider->value())
                          .arg(wMain->cDocument->dictionary.size()-wMain->cDocument->passed())
                          );
}

void WPrepare::closeEvent(QCloseEvent * a) {
    wMain->setMode(enabledMode);
    a->accept();
}
