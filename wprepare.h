/*******************************************************************************/
/** dicto v 1.3 WPrepare class header file                                    **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#ifndef WPREPARE_H
#define WPREPARE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QSlider>

class WPrepare : public QWidget {
    Q_OBJECT

public:
    WPrepare(QWidget *parent = 0, bool exam=false);

private:
    QLabel *numberLabel;
    QLabel *intoforeignLabel;
    QLabel *includeLabel;
    QLabel *ignoreLabel;

    QSlider *numberSlider;
    QSpinBox *numberBox;
    QCheckBox *includeBox;
    QCheckBox *ignoreBox;
    QComboBox *intoforeignCombo;

    QPushButton *startButton;
    QPushButton *cancelButton;

    void closeEvent(QCloseEvent * a);

private slots:
    void startTest();
    void startExam();
    void cancel();
    void updateSlider();
	void includeChanged();
};

#endif // WPREPARE_H
