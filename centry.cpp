/*******************************************************************************/
/** dicto v 1.3 CEntry class implementation file                              **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.sourceforge.net                                              **/
/*******************************************************************************/


#include "centry.h"
#include <vector>

CEntry::CEntry()
{
    wordstatus=false;
    passed = false;
    sp = spNone;
}

bool CEntry::check(QString give, bool intoforeign, bool ignoreSynonyms) {
    std::vector <QString> answers;
    QString answer="";
    for(int i=0; i<give.size(); i++) {
        if(give[i] == '/') {
            answers.push_back(answer);
            answer="";
        }
        else {
            answer+=give[i];
        }
    }
    answers.push_back(answer);

    std::vector <QString> questions;
    QString question = intoforeign ? translation : word;
    answer="";
    for(int i=0; i<question.size(); i++) {
        if(question[i] == '/') {
            questions.push_back(answer);
            answer="";
        }
        else {
            answer+=question[i];
        }
    }
    questions.push_back(answer);
    
    //performing case-insensitive
    
    for(int i=0; i<answers.size(); i++) answers[i] = answers[i].toLower();
    for(int i=0; i<questions.size(); i++) questions[i] = questions[i].toLower();

    //checking
	
	int pass=0;
    for(int i=0; i<answers.size(); i++) {
        for(int l=0; l<questions.size(); l++) {
            if(answers[i] == questions[l]) {
				pass++;
				questions[l] = "secrethaxxcode";
				break;				
			}
        }
    }
    if(pass == 0) return false;
    else if(pass > 0 && !ignoreSynonyms) return true;
    else if(pass == questions.size() && ignoreSynonyms) return true;
    else return false;
}

