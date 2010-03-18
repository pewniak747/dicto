// dicto v 1.3 PropertiesDialog class header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WPROPS_H
#define WPROPS_H

#include "wmain.h"
#include "cdocument.h"

class PropertiesDialog : public QWidget 
{
  Q_OBJECT

	public:
		PropertiesDialog(WMain *mainWindow, CDocument *documentObject);

	private:
		QLabel *fileLabel;
		QLabel *nativeLabel;
		QLabel *foreignLabel;
		QLabel *wordsLabel;
		QLabel *passedLabel;
		QLineEdit *nativeEdit;
		QLineEdit *foreignEdit;
		QPushButton *resetButton;
		QPushButton *okButton;
		
		WMain *mainWindow;
		CDocument *documentObject;

	private slots:
		void updateProps();
		void resetStats();
		void submitStats();
		void closeEvent(QCloseEvent * e);
};

#endif //WPROPS_H

