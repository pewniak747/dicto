/*******************************************************************************/
/** dicto v 1.1 WDialog class implementation file                             **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#include "wdialog.h"
#include "wmain.h"
#include "centry.h"

WDialog::WDialog(QWidget *parent, int current) : QWidget(parent) {
    wordLabel=new QLabel(tr("Słowo:"), this);
    translationLabel=new QLabel(tr("Tłumaczenie:"), this);
    wordEdit=new QLineEdit(this);
    translationEdit=new QLineEdit(this);
    submitButton=new QPushButton(tr("OK"), this);

    cancelButton=new QPushButton(tr("Anuluj"), this);

    QGridLayout *lay1=new QGridLayout;
    lay1->addWidget(wordLabel, 0, 0);
    lay1->addWidget(wordEdit, 0, 1);
    lay1->addWidget(translationLabel, 1, 0);
    lay1->addWidget(translationEdit, 1, 1);

    QHBoxLayout *lay2=new QHBoxLayout;
    lay2->addWidget(submitButton);
    lay2->addWidget(cancelButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(lay1);
    mainLayout->addLayout(lay2);

    setLayout(mainLayout);

    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitWord()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);
    connect(submitShortcut, SIGNAL(activated()), this, SLOT(submitWord()));

    setWindowTitle(tr("Edycja słowa"));
    setWindowIcon(QIcon(ICON));

    this->currentrow=current;

    if(this->currentrow!=-1) {
        wordEdit->setText(wMain->cDocument->dictionary[currentrow].word);
        translationEdit->setText(wMain->cDocument->dictionary[currentrow].translation);
    }

    wMain->centerWidgetOnScreen(this);
}

void WDialog::submitWord() {
    QString word=wordEdit->text();
    QString translation=translationEdit->text();
    if(word=="" || translation=="") {
        QMessageBox::information(this, tr("Błąd"), tr("Wypełnij oba pola"));
    }
    else if(word.contains(";") || word.contains("=") || translation.contains(";") || translation.contains("=")) {
        QMessageBox::information(this, tr("Błąd"), tr("Słowa nie mogą zawierać znaków ';' ani '='!"));
    }
    else {
        if(this->currentrow==-1) {
            CEntry newEntry;
            newEntry.word=word;
            newEntry.translation=translation;
            newEntry.wordstatus=false;
            wMain->cDocument->dictionary.push_back(newEntry);
        }
        else {
            wMain->cDocument->dictionary[currentrow].word=word;
            wMain->cDocument->dictionary[currentrow].translation=translation;
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
