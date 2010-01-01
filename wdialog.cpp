// dicto v 1.3 WDialog implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wdialog.h"
#include "wmain.h"
#include "centry.h"

WDialog::WDialog(QWidget *parent, CEntry *entry) : QWidget(parent) {
	// set window properties
	setWindowTitle(tr("Editing word"));
	setWindowIcon(QIcon(ICON));
	wMain->centerWidgetOnScreen(this);
	resize(400, 0);
	
	// initialize variables
	this->entry = entry;
	
	// create widgets
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

	// add layout
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
	
	// set tabbing order
	QWidget::setTabOrder(wordEdit, translationEdit);
	QWidget::setTabOrder(translationEdit, spBox);
	QWidget::setTabOrder(spBox, submitButton);
	QWidget::setTabOrder(submitButton, cancelButton);

	// connect signals and slots
	connect(submitButton, SIGNAL(clicked()), this, SLOT(submitWord()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

	// create shortcuts
	QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);
	connect(submitShortcut, SIGNAL(activated()), this, SLOT(submitWord()));
	
	// set values
	if(entry) {
		wordEdit->setText(entry->word);
		translationEdit->setText(entry->translation);
		spBox->setCurrentIndex((int)entry->sp);
	}
}
	
void WDialog::submitWord() {
	QString word = wordEdit->text();
	QString translation = translationEdit->text();
	
	// some validation
	if(word=="" || translation=="") {
		QMessageBox::information(this, tr("Error"), tr("Please fill both fields"));
		return;
	}
	if(word.contains(";") || word.contains("=") || translation.contains(";") || translation.contains("=")) {
		QMessageBox::information(this, tr("Error"), tr("Words may not contain neihter ';' nor '='!' characters"));
		return;
	}	
	
	// update entry
	if(!entry) {
		/*
		CEntry newEntry;
		newEntry.word = word;
		newEntry.translation = translation;
		newEntry.sp = (speechPart)spBox->currentIndex();
		wMain->cDocument->dictionary.push_back(newEntry);
		*/
		wMain->cDocument->addEntry(word, translation, (speechPart)spBox->currentIndex());
	}
	else {
		entry->word = word;
		entry->translation = translation;
		entry->sp = (speechPart)spBox->currentIndex();
	}
	// end
	wMain->setMode(enabledMode);
	wMain->cDocument->filechanged = true;
	wMain->updateList();
	close();
}

void WDialog::cancel() {
	wMain->setMode(enabledMode);
	close();
}

void WDialog::closeEvent(QCloseEvent * a) {
	wMain->setMode(enabledMode);
	a->accept();
}
