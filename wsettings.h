#ifndef WSETTINGS_H
#define WSETTINGS_H

#include<QLabel>
#include<QPushButton>

class WSettings : public QWidget {
	Q_OBJECT
	
	public:
		WSettings(QWidget *parent = 0);
		
	private:
		QLabel *default_nativeLabel;
		QLabel *default_foreignLabel;
		QPushButton *okButton;
		QPushButton *cancelButton;
		
		void closeEvent(QCloseEvent *e);
		
	private slots:
		void acceptSettings();
		void cancel();

	
};

#endif //WSETTINGS_H
