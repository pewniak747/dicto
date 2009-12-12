/*******************************************************************************/
/** dicto v 1.1 CEntry class implementation file                              **/
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
        if(!this->translation.contains('/')) {
            if(give==this->translation)
                return true;
            else
                return false;
        }
        else {
            QString syn1=this->translation.mid(0, translation.indexOf('/', 0));
            QString syn2=this->translation.mid(translation.indexOf('/')+1);
            if(syn2 == give || syn1 == give) return true;
            else return false;
        }
    }
    else {
        if(!this->word.contains('/')) {
            if(give==this->word)
                return true;
            else
                return false;
            }
        else {
            QString syn1=this->word.mid(0, word.indexOf('/', 0));
            QString syn2=this->word.mid(word.indexOf('/')+1);
            if(syn2 == give || syn1 == give) return true;
            else return false;
        }
    }
}

