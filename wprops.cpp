/*****************************************************************************/
/** dicto v 1.3 WProps class implementation ile                             **/
/** This file is published under GNU/GPL licence                            **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                 **/
/** author: Tomasz Pewinski "pewniak747"                                    **/
/** contact: pewniak747@gmail.com                                           **/
/** http://dicto.sourceforge.net                                            **/
/*****************************************************************************/

#include "wprops.h"
#include "wmain.h"

WProps::WProps(QWidget *parent) : QWidget(parent) {
    fileLabel = new QLabel(tr("Filename:"), this);
    file2Label = new QLabel(this);
    nativeLabel = new QLabel(tr("Mother language:"), this);
    foreignLabel = new QLabel(tr("Foreign language:"), this);
    wordsLabel = new QLabel(tr("Words:"), this);
    words2Label = new QLabel(this);
    passedLabel = new QLabel(tr("Learned:"), this);
    passed2Label = new QLabel(this);
    nativeEdit = new QLineEdit(this);
    foreignEdit = new QLineEdit(this);
    okButton = new QPushButton(tr("OK"), this);
    resetButton = new QPushButton(tr("Reset statistics"), this);

    QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(fileLabel, 0, 0);
        mainLayout->addWidget(file2Label, 0, 1);
        mainLayout->addWidget(nativeLabel, 1, 0);
        mainLayout->addWidget(nativeEdit, 1, 1);
        mainLayout->addWidget(foreignLabel, 2, 0);
        mainLayout->addWidget(foreignEdit, 2, 1);
        mainLayout->addWidget(wordsLabel, 3, 0);
        mainLayout->addWidget(words2Label, 3, 1);
        mainLayout->addWidget(passedLabel, 4, 0);
        mainLayout->addWidget(passed2Label, 4, 1);
        mainLayout->addWidget(resetButton, 5, 0);
        mainLayout->addWidget(okButton, 5, 1);
    this->setLayout(mainLayout);

    this->setWindowTitle(tr("File properties"));
    this->setWindowIcon(QIcon(ICON));
    wMain->centerWidgetOnScreen(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(submitStats()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetStats()));

    this->updateProps();

}

void WProps::updateProps() {
    file2Label->setText(tr("%1").arg(wMain->cDocument->filename.isEmpty() ? tr("unknown") : wMain->cDocument->filename));
    nativeEdit->setText(tr("%1").arg(wMain->cDocument->lang_native.isEmpty() ? tr("") : wMain->cDocument->lang_native));
    foreignEdit->setText(tr("%1").arg(wMain->cDocument->lang_foreign.isEmpty() ? tr("") : wMain->cDocument->lang_foreign));
    words2Label->setText(tr("%1").arg(wMain->cDocument->dictionary.size()));
    passed2Label->setText(tr("%1 (%2%)").arg(wMain->cDocument->passed()).arg(wMain->cDocument->passed()*100/(wMain->cDocument->dictionary.size()!=0?wMain->cDocument->dictionary.size():1)));
}

void WProps::submitStats() {
    wMain->cDocument->lang_native = nativeEdit->text();
    wMain->cDocument->lang_foreign = foreignEdit->text();
    this->close();
}

void WProps::resetStats() {
    wMain->cDocument->resetStats();
    this->updateProps();
}

void WProps::closeEvent(QCloseEvent * e) {
    wMain->setMode(enabledMode);
    e->accept();
}

