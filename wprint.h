/*******************************************************************************/
/** dicto v 1.3 WPrint class header file                                      **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#ifndef WPRINT_H
#define WPRINT_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

class WPrint : public QWidget {
	Q_OBJECT
	
	public:
	WPrint(QWidget *parent = 0);
	
	private:
	QSpinBox *sizeBox;
	QLabel *sizeLabel;
	QComboBox *printBox;
	QLabel *printLabel;
	QPushButton *submitButton;
	QPushButton *cancelButton;
	
	int fontsize;
	int printmode;
	
	private slots:
	void print();
	void cancel();
    void closeEvent(QCloseEvent * e);
};

#endif //WPRINT_H

