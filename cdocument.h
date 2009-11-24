/*******************************************************************************/
/** dicto v 1.3 CDocument class header file                                   **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/

#ifndef CDOCUMENT_H
#define CDOCUMENT_H

#include <vector>
#include "centry.h"

class CDocument {
public:
    CDocument();
    unsigned passed();
    void resetStats();

    std::vector <CEntry> dictionary;
    QString filename;
    bool filechanged;
    QString lang_native;
    QString lang_foreign;

public:
    void readFromFile(QString newfilename);
    void saveToFile(bool saveas=false);
    void sortDictionary();

private:
    bool ifSwap(QString word, QString word2);
};

#endif // CDOCUMENT_H
