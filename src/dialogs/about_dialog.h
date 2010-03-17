// dicto v 1.3 AboutDialog class header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "wmain.h"
	
class AboutDialog : public QWidget
{
	Q_OBJECT

	public:
		AboutDialog(WMain *mainWindow = 0);

	private:
		QLabel* image;
		QLabel * infoLabel;
		QLabel *urlLabel;
		QTextBrowser *infoField;
		QPushButton* okButton;
		WMain *mainWindow;

		void closeEvent(QCloseEvent * a);
};

#endif //ABOUTDIALOG_H

