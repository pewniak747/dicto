#include<QtGui>
#include<QSettings>
#include "wsettings.h"
#include "wmain.h"

WSettings::WSettings(QWidget *parent) {
	setWindowTitle(tr("Dicto settings"));
	wMain->centerWidgetOnScreen(this);
	resize(300, 100);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowIcon(QIcon(ICON));
	
	okButton = new QPushButton(tr("OK"), this);
	cancelButton = new QPushButton(tr("Cancel"), this);
	default_nativeLabel = new QLabel(tr("Default mother language"), this);
	default_foreignLabel = new QLabel(tr("Default foreign language"), this);
	caseSensitiveLabel = new QLabel(tr("Case sensitive"), this);
	maxRecentFilesLabel = new QLabel(tr("Maximum recent files"), this);
	interfaceLangLabel = new QLabel(tr("Interface language"), this);
	default_nativeEdit = new QLineEdit;
	default_foreignEdit = new QLineEdit;
	caseSensitiveBox = new QCheckBox(this);
	maxRecentFilesBox = new QSpinBox(this);
	maxRecentFilesBox->setRange(1, 10);
	interfaceLangCombo = new QComboBox(this);
	interfaceLangCombo->addItem(tr("English"));
	interfaceLangCombo->addItem(tr("Polish"));
	interfaceLangCombo->addItem(tr("Russian"));
	
	
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
		QGridLayout *settingsLayout = new QGridLayout;
			settingsLayout->addWidget(default_nativeLabel, 0, 0);
			settingsLayout->addWidget(default_nativeEdit, 0, 1);
			settingsLayout->addWidget(default_foreignLabel, 1, 0);
			settingsLayout->addWidget(default_foreignEdit, 1, 1);
			settingsLayout->addWidget(caseSensitiveLabel, 2, 0);
			settingsLayout->addWidget(caseSensitiveBox, 2, 1);
			settingsLayout->addWidget(maxRecentFilesLabel, 3, 0);
			settingsLayout->addWidget(maxRecentFilesBox, 3, 1);
			settingsLayout->addWidget(interfaceLangLabel, 4, 0);
			settingsLayout->addWidget(interfaceLangCombo, 4, 1);
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
		caseSensitiveBox->setChecked(settings.value("testing/case_sensitive").value<bool>());
		maxRecentFilesBox->setValue(settings.value("general/max_recent_files").value<int>());
}

void WSettings::acceptSettings() {
	QSettings settings("dicto.ini", QSettings::IniFormat);
		settings.setValue("dictionaries/default_native", default_nativeEdit->text());
		settings.setValue("dictionaries/default_foreign", default_foreignEdit->text());
		settings.setValue("general/max_recent_files", maxRecentFilesBox->value());
		settings.setValue("testing/case_sensitive", caseSensitiveBox->isChecked());
		wMain->maxRecentFiles = settings.value("general/max_recent_files").value<int>();
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::cancel() {
	wMain->setMode(enabledMode);
	this->close();
}

void WSettings::closeEvent(QCloseEvent *e) {
	wMain->setMode(enabledMode);
	e->accept();
}
