#include<QtGui>
#include "wsettings.h"
#include "wmain.h"

WSettings::WSettings(QWidget *parent) {
	setWindowTitle(tr("Dicto settings"));
	wMain->centerWidgetOnScreen(this);
	resize(300, 200);
	
	okButton = new QPushButton(tr("OK"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);
	default_nativeLabel = new QLabel(tr("Default mother language"), this);
	default_foreignLabel = new QLabel(tr("Default foreign language"), this);
	default_nativeEdit = new QLineEdit;
	default_foreignEdit = new QLineEdit;
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
		QGridLayout *settingsLayout = new QGridLayout;
			settingsLayout->addWidget(default_nativeLabel, 0, 0);
			settingsLayout->addWidget(default_nativeEdit, 0, 1);
			settingsLayout->addWidget(default_foreignLabel, 1, 0);
			settingsLayout->addWidget(default_foreignEdit, 1, 1);
		mainLayout->addLayout(settingsLayout);
		QHBoxLayout *buttonsLayout = new QHBoxLayout;
			buttonsLayout->addWidget(okButton);
			buttonsLayout->addWidget(cancelButton);
		mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(acceptSettings()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void WSettings::acceptSettings() {
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::cancel() {
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::closeEvent(QCloseEvent *e) {
	
}
