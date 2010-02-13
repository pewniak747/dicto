#include<QtGui>
#include<QSettings>
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
	
	readSettings();
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(acceptSettings()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

void WSettings::readSettings() {
	QSettings settings("dicto.ini", QSettings::IniFormat);
		default_nativeEdit->setText(settings.value("dictionaries/default_native").value<QString>());
		default_foreignEdit->setText(settings.value("dictionaries/default_foreign").value<QString>());
}

void WSettings::acceptSettings() {
	QSettings settings("dicto.ini", QSettings::IniFormat);
		settings.setValue("dictionaries/default_native", default_nativeEdit->text());
		settings.setValue("dictionaries/default_foreign", default_foreignEdit->text());
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::cancel() {
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::closeEvent(QCloseEvent *e) {
	
}
