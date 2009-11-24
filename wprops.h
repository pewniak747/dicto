/*******************************************************************************/
/** dicto v 1.3 WProps class header file                                      **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#ifndef WPROPS_H
#define WPROPS_H

#include <QtGui>

class WProps : public QWidget
{
    Q_OBJECT

	public:
		WProps(QWidget *parent);
	protected:

	private:
        QLabel *fileLabel;
        QLabel *file2Label;
        QLabel *nativeLabel;
        QLabel *foreignLabel;
        QLabel *wordsLabel;
        QLabel *words2Label;
        QLabel *passedLabel;
        QLabel *passed2Label;
        QLineEdit *nativeEdit;
        QLineEdit *foreignEdit;
        QPushButton *resetButton;
        QPushButton *okButton;

    private slots:
        void updateProps();
        void resetStats();
        void submitStats();
        void closeEvent(QCloseEvent * e);

};


#endif //WPROPS_H
