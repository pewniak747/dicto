#include "wprops.h"
#include "wmain.h"

WProps::WProps(QWidget *parent) : QWidget(parent) {
    fileLabel = new QLabel(tr("Nazwa pliku:"), this);
    file2Label = new QLabel(this);
    nativeLabel = new QLabel(tr("Język ojczysty:"), this);
    foreignLabel = new QLabel(tr("Język obcy:"), this);
    wordsLabel = new QLabel(tr("Ilość słów:"), this);
    words2Label = new QLabel(this);
    passedLabel = new QLabel(tr("Nauczonych słów:"), this);
    passed2Label = new QLabel(this);
    nativeEdit = new QLineEdit(this);
    foreignEdit = new QLineEdit(this);
    okButton = new QPushButton(tr("OK"), this);
    resetButton = new QPushButton(tr("Zresetuj statystyki"), this);

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

    this->setWindowTitle(tr("Właściwości pliku"));
    this->setWindowIcon(QIcon(ICON));
    wMain->centerWidgetOnScreen(this);

    connect(okButton, SIGNAL(clicked()), this, SLOT(submitStats()));
    connect(resetButton, SIGNAL(clicked()), this, SLOT(resetStats()));

    this->updateProps();

}

void WProps::updateProps() {
    file2Label->setText(tr("%1").arg(wMain->cDocument->filename.isEmpty() ? tr("nieznana") : wMain->cDocument->filename));
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
