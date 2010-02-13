#include<QtGui>
#include "wsettings.h"
#include "wmain.h"

WSettings::WSettings(QWidget *parent) {
	setWindowTitle(tr("Dicto settings"));
	wMain->centerWidgetOnScreen(this);
	resize(300, 200);
	
	okButton = new QPushButton(tr("OK"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
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
