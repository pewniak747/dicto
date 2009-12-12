/*******************************************************************************/
/** dicto v 1.1 CEntry class header file                                      **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#ifndef CENTRY_H
#define CENTRY_H

#include <QString>

class CEntry {
public:
    CEntry();
    bool check(QString give, bool intoforeign);

    QString word;
    QString translation;
    bool wordstatus;
};

#endif // CENTRY_H
