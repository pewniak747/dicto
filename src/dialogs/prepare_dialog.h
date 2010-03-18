// dicto v 1.3 PrepareDialog class header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WPREPARE_H
#define WPREPARE_H

#include "wmain.h"

class PrepareDialog : public QWidget
{
	Q_OBJECT

	public:
		PrepareDialog(WMain *mainWindow, bool exam = false);

	private:
		QLabel *numberLabel;
		QSlider *numberSlider;
		QSpinBox *numberBox;
		QLabel *intoforeignLabel;
		QComboBox *intoforeignCombo;
		QLabel *includeLabel;
		QCheckBox *includeBox;
		QLabel *ignoreLabel;
		QCheckBox *ignoreBox;
		QPushButton *startButton;
		QPushButton *cancelButton;
		
		WMain *mainWindow;

	private slots:
		void startTest();
		void startExam();
		void includeChanged(int state);
		void closeEvent(QCloseEvent * a);
};
	
#endif // WPREPARE_H
