/*******************************************************************************/
/** dicto v 1.0 CEntry class implementation file                              **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/


#include "centry.h"

CEntry::CEntry()
{
    wordstatus=true;
}

bool CEntry::check(QString give, bool intoforeign)
{
    if(intoforeign) {
        if(give==this->translation)
            return true;
        else
            return false;
    }
    else {
        if(give==this->word)
            return true;
        else
            return false;
        }
    }

