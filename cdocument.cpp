// dicto v 1.3 CDocument implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "cdocument.h"
#include "centry.h"
#include "wmain.h"

// CDocument constructor
CDocument::CDocument() {
	filename="";
	filechanged = false;
	lang_native="";
	lang_foreign="";
}

// saves CDocument to file
void CDocument::saveToFile(bool saveas) {
	if(this->filename=="" || saveas) {
		filename=QFileDialog::getSaveFileName(wMain,
											  "Choose file",
											  "./",
											  tr("dicto file(*.dic);;text file(*.txt);;file(*.*)"));
	}

	QFile file(filename);
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		 QMessageBox::information(wMain, tr("Error"), tr("Can't save to %1").arg(filename));
		 return;
	 }

	 QTextStream out(&file);

	 out << "################################################################################\n";
	 out << "# This file was created by dicto v. 1.3									                    	#\n";
	 out << "# This file is incompatibile with newer versions of dicto, as well as linGO	  #\n";
	 out << "# Applying changes to this file may cause several program errors			     	    #\n";
	 out << "# Proceed with caution																													#\n"; 
	 out << "################################################################################\n";
	 out << "\n";

	 out << "#dictionary:\n";

	 for (unsigned i=0; i<this->dictionary.size(); i++) {
		out << this->dictionary[i].word<< ";" <<this->dictionary[i].translation;
		if(dictionary[i].sp != spNone) {
			int ss = NULL;
			speechPart spart = dictionary[i].sp;
			if(spart == spNoun) ss=1;
			else if(spart == spVerb) ss=2;
			else if(spart == spAdjective) ss=3;
			else if(spart == spAdverb) ss=4;
			else if(spart == spOther) ss=5;
			out << ";" << ss;
		}
		out << "\n";
	}
	
	 out << "\n";
	 out << "#languages:\n";
	 out << "lang_native=" << this->lang_native << "\n";
	 out << "lang_foreign=" <<this->lang_foreign << "\n";

	 out << "\n";
	 out << "#learned:\n";

	 for (unsigned i=0; i<this->dictionary.size(); i++)
		out << this->dictionary[i].wordstatus;

	 filechanged=false;
}

// reads data from file
void CDocument::readFromFile(QString newfilename) {
    if(newfilename.isEmpty()) {
newfilename=QFileDialog::getOpenFileName(wMain,
                                                     tr("Choose file"),
                                                     "./",
                                                     tr("dicto files (*.dic);;text files (*.txt);;all files(*.*)"));
}
 
    if (!newfilename.isEmpty()) {
        QFile file(newfilename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
 
        this->dictionary.clear();
        QTextStream in(&file);
 
        while (!in.atEnd()) {
            QString line = in.readLine();
            if(line[0]=='#')
                 continue;
            if(line.contains("=")) {
                QString option=line.section("=", 0, 0);
                if(option == "lang_native")
                    this->lang_native=line.section("=", 1, 1);
                else if(option == "lang_foreign")
                    this->lang_foreign=line.section("=", 1, 1);
                else
                    continue;
            }
            else if(!line.contains(";")) {
                 for(int i=0; i<line.size(); i++)
                    this->dictionary[i].wordstatus=line[i]=='0'?false:true;
            }
            else {
                 CEntry newEntry;
                 newEntry.word=line.section(";",0,0);
                 newEntry.translation=line.section(";",1,1);
                 if(line.count(";") == 2) {
speechPart sp;
int spart = line.section(";", 2, 2).toInt();
switch(spart) {
case 0 : sp = spNone; break;
case 1 : sp = spNoun; break;
case 2 : sp = spVerb; break;
case 3 : sp = spAdjective; break;
case 4 : sp = spAdverb; break;
case 5 : sp = spOther; break;
default : sp = spOther; break;
}
newEntry.sp = sp;
}
                 newEntry.wordstatus=false;
                 this->dictionary.push_back(newEntry);
                  wMain->updateStatusbar();
            }
         }
         this->filename=newfilename;
         this->filechanged=false;
         wMain->updateList();
     }
     wMain->updateStatusbar();
}



// returns number of learned words
int CDocument::passed() {
	int passed=0;
	for(unsigned i=0; i<dictionary.size(); i++)
		if(dictionary[i].wordstatus) passed++;
	return passed;
}

// resets dictionary's statistics
void CDocument::resetStats() {
	if(dictionary.size() == 0) return;
	for(unsigned i=0; i<dictionary.size(); i++)
		dictionary[i].wordstatus=false;
	this->filechanged = true;
	wMain->updateStatusbar();
}

// sorts dictionary
void CDocument::sortDictionary() {
	for(unsigned i = 0; i < dictionary.size(); i++) {
		bool swapped=false;
		for(unsigned l = dictionary.size()-1; l>i; l--) {
			if(ifSwap(dictionary[l].translation, dictionary[l-1].translation)) {
				std::swap(dictionary[l], dictionary[l-1]);
				swapped = true;
				filechanged = true;
			}
		}
		if(!swapped) break;
	}
	wMain->updateList();
}

// returns true if words are not sorted alphabetically
bool CDocument::ifSwap(QString word, QString word2) {
	for(int i=0; i<word.size(); i++) {
		if(word[i] < word2[i]) return true;
		else if(word[i] > word2[i]) return false;
	}
	return true;
}

