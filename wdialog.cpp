/*******************************************************************************/
/** dicto v 1.3 WDialog class implementation file                             **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#include "wdialog.h"
#include "wmain.h"
#include "centry.h"

WDialog::WDialog(QWidget *parent, int current) : QWidget(parent) {
    wordLabel=new QLabel(tr("Word:"), this);
    translationLabel=new QLabel(tr("Translation:"), this);
    wordEdit=new QLineEdit(this);
    translationEdit=new QLineEdit(this);
    spLabel = new QLabel(tr("Speech part:"));
    spBox = new QComboBox;
		spBox->addItem(tr("-"));
		spBox->addItem(tr("noun"));
		spBox->addItem(tr("verb"));
		spBox->addItem(tr("adjective"));
		spBox->addItem(tr("adverb"));
		spBox->addItem(tr("other"));
    submitButton=new QPushButton(tr("OK"), this);
    cancelButton=new QPushButton(tr("Cancel"), this);

    QGridLayout *lay1=new QGridLayout;
    lay1->addWidget(wordLabel, 0, 0);
    lay1->addWidget(wordEdit, 0, 1);
    lay1->addWidget(translationLabel, 1, 0);
    lay1->addWidget(translationEdit, 1, 1);
    lay1->addWidget(spLabel, 2, 0);
    lay1->addWidget(spBox, 2, 1);

    QHBoxLayout *lay2=new QHBoxLayout;
    lay2->addWidget(submitButton);
    lay2->addWidget(cancelButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(lay1);
    mainLayout->addLayout(lay2);

    setLayout(mainLayout);
    
	QWidget::setTabOrder(wordEdit, translationEdit);
	QWidget::setTabOrder(translationEdit, spBox);
	QWidget::setTabOrder(spBox, submitButton);
	QWidget::setTabOrder(submitButton, cancelButton);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitWord()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);
    connect(submitShortcut, SIGNAL(activated()), this, SLOT(submitWord()));

    setWindowTitle(tr("Editing word"));
    setWindowIcon(QIcon(ICON));

    this->currentrow=current;

    if(this->currentrow!=-1) {
        wordEdit->setText(wMain->cDocument->dictionary[currentrow].word);
        translationEdit->setText(wMain->cDocument->dictionary[currentrow].translation);
        speechPart spart = wMain->cDocument->dictionary[currentrow].sp;
        int ss;
        if(spart == spNone) ss=0;
        else if(spart == spNoun) ss=1;
        else if(spart == spVerb) ss=2;
        else if(spart == spAdjective) ss=3;
        else if(spart == spAdverb) ss=4;
        else if(spart == spOther) ss=5;
        this->spBox->setCurrentIndex(ss);
    }

	
    wMain->centerWidgetOnScreen(this);
    this->resize(400, 0);
}

void WDialog::submitWord() {
    QString word=wordEdit->text();
    QString translation=translationEdit->text();
    int spart=spBox->currentIndex();
    speechPart sp;
    switch(spart) {
		case 0 : sp = spNone; break;
		case 1 : sp = spNoun; break;
		case 2 : sp = spVerb; break;
		case 3 : sp = spAdjective; break;
		case 4 : sp = spAdverb; break;
		case 5 : sp = spOther; break;
	}
    if(word=="" || translation=="") {
        QMessageBox::information(this, tr("Error"), tr("Please fill both fields"));
    }
    else if(word.contains(";") || word.contains("=") || translation.contains(";") || translation.contains("=")) {
        QMessageBox::information(this, tr("Error"), tr("Words may not contain neihter ';' nor '='!' characters"));
    }
    else {
        if(this->currentrow==-1) {
            CEntry newEntry;
            newEntry.word=word;
            newEntry.translation=translation;
            newEntry.wordstatus=false;
            newEntry.sp = sp;
            wMain->cDocument->dictionary.push_back(newEntry);
        }
        else {
            wMain->cDocument->dictionary[currentrow].word=word;
            wMain->cDocument->dictionary[currentrow].translation=translation;
            wMain->cDocument->dictionary[currentrow].sp = sp;
        }
        wMain->setMode(enabledMode);
        wMain->cDocument->filechanged=true;
        wMain->updateList();
        this->close();
    }

}

void WDialog::cancel() {
    wMain->setMode(enabledMode);
    this->close();
}

WDialog::~WDialog() {
    //wMain->setMode(enabledMode);
}

void WDialog::closeEvent(QCloseEvent * a) {
    wMain->setMode(enabledMode);
    a->accept();
}
