#ifndef WSETTINGS_H
#define WSETTINGS_H

#include<QLabel>
#include<QPushButton>
#include<QLineEdit>

class WSettings : public QWidget {
	Q_OBJECT
	
	public:
		WSettings(QWidget *parent = 0);
		
	private:
		QLabel *default_nativeLabel;
		QLabel *default_foreignLabel;
		QLineEdit *default_nativeEdit;
		QLineEdit *default_foreignEdit;
		QPushButton *okButton;
		QPushButton *cancelButton;
		
		void readSettings();
		void closeEvent(QCloseEvent *e);
		
	private slots:
		void acceptSettings();
		void cancel();

	
};

#endif //WSETTINGS_H
