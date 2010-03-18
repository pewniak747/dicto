// dicto v 1.3 WordDialog header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WORDDIALOG_H
#define WORDDIALOG_H

#include "wmain.h"
#include "entry_object.h"

class WordDialog : public QWidget {
	Q_OBJECT

	public:
		WordDialog (WMain *mainWindow, EntryObject *entry);

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
		EntryObject *entry;
		WMain *mainWindow;

		void closeEvent(QCloseEvent * a);
};

#endif // WORDDIALOG_H
