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
#include "entry_object.h"
#include "wmain.h"

// CDocument constructor
CDocument::CDocument() {
	filename="";
	filechanged = false;
	QSettings settings("dicto.ini", QSettings::IniFormat);
	lang_native=settings.value("dictionaries/default_native").value<QString>();
	lang_foreign=settings.value("dictionaries/default_foreign").value<QString>();
}

//adds entry to dictionary
void CDocument::addEntry(QString word, QString translation, speechPart sp) {
	EntryObject newEntry;
	newEntry.word = word;
	newEntry.translation = translation;
	newEntry.sp = sp;
	dictionary.push_back(newEntry);
}

// saves CDocument to file
bool CDocument::saveToFile() {
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text) || !file.isWritable()) {
		QMessageBox::information(wMain, QObject::tr("Error"), QObject::tr("Can't save to %1").arg(filename));
		return false;
	}
	 
	QTextStream out(&file);
	out << "################################################################################\n";
	out << "# This file was created by dicto v. 1.3                                        #\n";
	out << "# This file is incompatibile with newer versions of dicto, as well as linGO    #\n";
	out << "# Applying changes to this file may cause several program errors               #\n";
	out << "# Proceed with caution                                                         #\n"; 
	out << "################################################################################\n";
	out << "\n";
	out << "#dictionary:\n";

	for (unsigned i=0; i<this->dictionary.size(); i++) {
		out << this->dictionary[i].word<< ";" <<this->dictionary[i].translation;
		if(dictionary[i].sp != spNone) {
			out << ";" << (int)dictionary[i].sp;
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
	return true;
}

// reads data from file
bool CDocument::readFromFile(QString newfilename) {
	QFile file(newfilename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text) || !file.isReadable()) {
		QMessageBox::information(wMain, QObject::tr("Error"), QObject::tr("Can't open %1").arg(filename));
		return false;
	}
	
	dictionary.clear();
	QTextStream in(&file);

	while (!in.atEnd()) {
		QString line = in.readLine();
		if(line[0]=='#') continue;
		if(line.contains("=")) {
			QString option=line.section("=", 0, 0);
			if(option == "lang_native")
				this->lang_native=line.section("=", 1, 1);
			else if(option == "lang_foreign")
				this->lang_foreign=line.section("=", 1, 1);
			else
				continue;
		}
		else if(!line.contains(";") && (line.contains("0") || line.contains("1"))) {
			 for(int i=0; i<line.size(); i++)
				this->dictionary[i].wordstatus=line[i]=='0'?false:true;
		}
		else if(line.contains(";")) {
			QString word = line.section(";",0,0);
			QString translation = line.section(";",1,1);
			speechPart sp = (speechPart)line.section(";", 2, 2).toInt();
			addEntry(word, translation, sp);
			}
		}
		this->filename=newfilename;
		this->filechanged = false;
		wMain->updateList();
		wMain->updateStatusbar();
		return true;
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

int CDocument::dictionarySize() {
	return dictionary.size();
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
