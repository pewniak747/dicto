// dicto v 1.3 WDialog header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WDIALOG_H
#define WDIALOG_H

#include <QtGui>
#include "wmain.h"

class WDialog : public QWidget {
	Q_OBJECT

	public:
		WDialog (QWidget *parent, CEntry *entry);

	public slots:
		void submitWord();
		void cancel();

	private:
		QLabel *wordLabel;
		QLabel *translationLabel;
		QLabel *spLabel;
		QLineEdit *wordEdit;
		QLineEdit *translationEdit;
		QComboBox *spBox;
		QPushButton *submitButton;
		QPushButton *cancelButton;
		CEntry *entry;

		void closeEvent(QCloseEvent * a);
};

#endif // WDIALOG_H
