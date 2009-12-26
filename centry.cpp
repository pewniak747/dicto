// dicto v 1.3 CEntry class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "centry.h"
#include <QObject>
#include <vector>

CEntry::CEntry() {
	wordstatus=false;
	passed = false;
	sp = spNone;
}

QString CEntry::spToString() {
	speechPart spart = this->sp;
	if(spart == spNone) return QObject::tr("None");
	else if(spart == spVerb) return QObject::tr("Verb");
	else if(spart == spNoun) return QObject::tr("Noun");
	else if(spart == spAdjective) return QObject::tr("Adjective");
	else if(spart == spAdverb) return QObject::tr("Adverb");
	else if(spart == spOther) return QObject::tr("Other");
	}


bool CEntry::check(QString give, bool intoforeign, bool ignoreSynonyms) {
	//split give into answers array
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
	
	//split questions into questions array
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
	
	//perform case-insensitive
	for(unsigned i=0; i<answers.size(); i++) answers[i] = answers[i].toLower();
	for(unsigned i=0; i<questions.size(); i++) questions[i] = questions[i].toLower();

	// perform checking
	unsigned size = questions.size();
	unsigned asize = answers.size();
	for(unsigned i=0; i<answers.size(); i++) {
		for(unsigned l=0; l<questions.size(); l++) {
			if(answers[i] == questions[l]) {
				for(unsigned u=l; u<questions.size()-1; u++)
            qSwap(questions[u], questions[u+1]);
        questions.pop_back();
				break;				
			}
		}
	}
	if(ignoreSynonyms && questions.empty() && size == asize) return true;
	else if(!ignoreSynonyms && questions.size() < size) return true;
	else return false;
}

