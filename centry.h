// dicto v 1.3 CEntry class header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef CENTRY_H
#define CENTRY_H

#include <QString>

enum speechPart {spNone = 0, spVerb = 1, spNoun = 2, spAdjective = 3, spAdverb = 4, spOther = 5};

class CEntry {
	public:
		QString word;
		QString translation;
		bool wordstatus;
		bool passed;
		speechPart sp;
		
		CEntry();
		bool check(QString give, bool intoforeign, bool ignoreSynonyms);
};

#endif // CENTRY_H

