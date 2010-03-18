// dicto v 1.3 PropertiesDialog class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "properties_dialog.h"

// PropertiesDialog constructor
PropertiesDialog::PropertiesDialog(WMain *mainWindow, CDocument *documentObject) {
	if(!mainWindow || !documentObject) return;
	// set window properties
	setWindowTitle(tr("File properties"));
	setWindowIcon(QIcon(ICON));
	mainWindow->centerWidgetOnScreen(this);
	setAttribute(Qt::WA_DeleteOnClose);
	
	//set variables
	this->mainWindow = mainWindow;
	this->documentObject = documentObject;

	// create all widgets
  fileLabel = new QLabel(this);
  nativeLabel = new QLabel(tr("Mother language:"), this);
  foreignLabel = new QLabel(tr("Foreign language:"), this);
	wordsLabel = new QLabel(this);
	passedLabel = new QLabel(this);
	nativeEdit = new QLineEdit(this);
	foreignEdit = new QLineEdit(this);
	okButton = new QPushButton(tr("OK"), this);
	resetButton = new QPushButton(tr("Reset statistics"), this);

	// add layout
	QGridLayout *mainLayout = new QGridLayout;
		mainLayout->addWidget(fileLabel, 0, 0, 1, 2);
		mainLayout->addWidget(nativeLabel, 1, 0);
		mainLayout->addWidget(nativeEdit, 1, 1);
		mainLayout->addWidget(foreignLabel, 2, 0);
		mainLayout->addWidget(foreignEdit, 2, 1);
		mainLayout->addWidget(wordsLabel, 3, 0, 1, 2);
		mainLayout->addWidget(passedLabel, 4, 0, 1, 2);
		QHBoxLayout *buttonLayout = new QHBoxLayout;
			buttonLayout->addWidget(resetButton);
			buttonLayout->addWidget(okButton);
		mainLayout->addLayout(buttonLayout, 5, 0, 1, 2);
	this->setLayout(mainLayout);
	
	// set tabbing order
	QWidget::setTabOrder(nativeEdit, foreignEdit);
	QWidget::setTabOrder(foreignEdit, resetButton);
	QWidget::setTabOrder(resetButton, okButton);

	// connect signals and slots
	connect(okButton, SIGNAL(clicked()), this, SLOT(submitStats()));
	connect(resetButton, SIGNAL(clicked()), this, SLOT(resetStats()));

	// update widgets
	updateProps();
}

// updates widgets with file properties
void PropertiesDialog::updateProps() {
	//TODO prettify this (with DocumentObject functions)
	fileLabel->setText(tr("Filename: %1").arg(documentObject->filename.isEmpty() ? tr("unknown") : documentObject->filename));
	nativeEdit->setText(tr("%1").arg(documentObject->lang_native.isEmpty() ? tr("") : documentObject->lang_native));
	foreignEdit->setText(tr("%1").arg(documentObject->lang_foreign.isEmpty() ? tr("") : documentObject->lang_foreign));
	wordsLabel->setText(tr("Words: %1").arg(documentObject->dictionary.size()));
	passedLabel->setText(tr("Learned: %1 (%2%)").arg(documentObject->passed()).arg(documentObject->passed()*100/(documentObject->dictionary.size()!=0?documentObject->dictionary.size():1)));
}

// submits settings to file
void PropertiesDialog::submitStats() {
	if(!documentObject) return;
	documentObject->lang_native = nativeEdit->text();
	documentObject->lang_foreign = foreignEdit->text();
	close();
}

// resets statistics
void PropertiesDialog::resetStats() {
	documentObject->resetStats();
	updateProps();
}

// closes window
void PropertiesDialog::closeEvent(QCloseEvent * e) {
	mainWindow->setMode(enabledMode);
	e->accept();
}

