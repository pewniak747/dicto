/*******************************************************************************/
/** dicto v 1.0 WDialog class header file                                     **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#ifndef WDIALOG_H
#define WDIALOG_H

#include <QtGui>
#include "wmain.h"

class WDialog : public QWidget
{
    Q_OBJECT

    public:
        WDialog (QWidget *parent, int current = -1);
        ~WDialog();

        int currentrow;

    public slots:
        void submitWord();
        void cancel();

    private:
        QLabel *wordLabel;
        QLabel *translationLabel;
        QLineEdit *wordEdit;
        QLineEdit *translationEdit;
        QPushButton *submitButton;
        QPushButton *cancelButton;

        void closeEvent(QCloseEvent * a);
};

#endif // WDIALOG_H
