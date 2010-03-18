// dicto v 1.3 WordDialog implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "word_dialog.h"

WordDialog::WordDialog(WMain *mainWindow, EntryObject *entry) {
	if(!mainWindow) return;
	
	// set window properties
	setWindowTitle(tr("Editing word"));
	setWindowIcon(QIcon(ICON));
	mainWindow->centerWidgetOnScreen(this);
	resize(400, 0);
	setAttribute(Qt::WA_DeleteOnClose);
	
	// initialize variables
	this->entry = entry;
	this->mainWindow = mainWindow;
	
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
	
	QShortcut *quitShortcut=new QShortcut(Qt::Key_Escape, this);
	connect(quitShortcut, SIGNAL(activated()), this, SLOT(cancel()));
	
	// set values
	if(entry) {
		wordEdit->setText(entry->word);
		translationEdit->setText(entry->translation);
		spBox->setCurrentIndex((int)entry->sp);
	}
}
	
void WordDialog::submitWord() {
	QString word = wordEdit->text();
	QString translation = translationEdit->text();
	
	// validation
	if(word.isEmpty() || translation.isEmpty()) {
		QMessageBox::information(this, tr("Error"), tr("Please fill both fields"));
		return;
	}
	else if(word.contains(";") || word.contains("=") || translation.contains(";") || translation.contains("=")) {
		QMessageBox::information(this, tr("Error"), tr("Words may not contain neihter ';' nor '='!' characters"));
		return;
	}	
	
	// update entry
	if(!entry) {
		mainWindow->cDocument->addEntry(word, translation, (speechPart)spBox->currentIndex());
	}
	else {
		entry->word = word;
		entry->translation = translation;
		entry->sp = (speechPart)spBox->currentIndex();
	}
	// end
	
	mainWindow->cDocument->filechanged = true;
	mainWindow->setMode(enabledMode);
	mainWindow->updateList();
	close();
}

void WordDialog::cancel() {
	close();
}

void WordDialog::closeEvent(QCloseEvent * a) {
	mainWindow->setMode(enabledMode);
	a->accept();
}
