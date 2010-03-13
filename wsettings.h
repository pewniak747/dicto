#ifndef WSETTINGS_H
#define WSETTINGS_H

#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QSpinBox>
#include<QCheckBox>

class WSettings : public QWidget {
	Q_OBJECT
	
	public:
		WSettings(QWidget *parent = 0);
		
	private:
		QLabel *default_nativeLabel;
		QLabel *default_foreignLabel;
		QLabel *caseSensitiveLabel;
		QLabel *maxRecentFilesLabel;
		QLabel *interfaceLangLabel;
		QLineEdit *default_nativeEdit;
		QLineEdit *default_foreignEdit;
		QCheckBox *caseSensitiveBox;
		QSpinBox *maxRecentFilesBox;
		QComboBox *interfaceLangCombo;
		QPushButton *okButton;
		QPushButton *cancelButton;
		
		void readSettings();
		void closeEvent(QCloseEvent *e);
		
	private slots:
		void acceptSettings();
		void cancel();

	
};

#endif //WSETTINGS_H
