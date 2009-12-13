// dicto v 1.3 WAbout class header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WABOUT_H
#define WABOUT_H

#include <QLabel>
#include <QPushButton>
	
class WAbout : public QWidget
{
	Q_OBJECT

	public:
		WAbout(QWidget *parent = 0);

	private:
		QPushButton* okButton;
		QLabel * infoLabel;
		QLabel *urlLabel;
		QLabel* image;

		void closeEvent(QCloseEvent * a);
};

#endif //WABOUT_H

