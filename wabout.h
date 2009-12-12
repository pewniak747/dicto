/*****************************************************************************/
/** dicto v 1.1 WAbout class declaration ile                                **/
/** This file is published under GNU/GPL licence                            **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                 **/
/** author: Tomasz Pewinski "pewniak747"                                    **/
/** contact: pewniak747@gmail.com                                           **/
/** http://dicto.ugu.pl                                                     **/
/*****************************************************************************/

#ifndef WABOUT_H
#define WABOUT_H

#include <QtGui>

class WAbout : public QWidget {
    Q_OBJECT

	public:
		WAbout(QWidget *parent = 0);
		~WAbout();
	protected:
        void closeEvent(QCloseEvent * a);

	private:
        QPushButton* okButton;
        QLabel * infoLabel;
        QLabel* image;


};

#endif //WABOUT_H
