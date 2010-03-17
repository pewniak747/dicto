// dicto v 1.3 CDocument header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef CDOCUMENT_H
#define CDOCUMENT_H

#include <QVector>
#include "centry.h"
	
class CDocument{
public:
	QVector<CEntry> dictionary;
	QString filename;
	bool filechanged;
	QString lang_native;
	QString lang_foreign;

	CDocument();
	int passed();
	void addEntry(QString word, QString translation, speechPart sp);
	void resetStats();
	bool readFromFile(QString newfilename);
	bool saveToFile();
	void sortDictionary();

private:
	bool ifSwap(QString word, QString word2);
};

#endif // CDOCUMENT_H

