/*******************************************************************************/
/** dicto v 1.3 CEntry class header file                                      **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#ifndef CENTRY_H
#define CENTRY_H

#include <QString>

enum speechPart {spNone, spVerb, spNoun, spAdjective, spAdverb, spOther};

class CEntry {
public:
    CEntry();
    bool check(QString give, bool intoforeign, bool ignoreSynonyms);

    QString word;
    QString translation;
    bool wordstatus;
    bool passed;
    speechPart sp;
};

#endif // CENTRY_H
