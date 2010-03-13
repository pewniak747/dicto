// dicto v 1.3 WMain exam implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wmain.h"

// starts exam
void WMain::exam(unsigned howmany, bool intoforeign, bool include, bool ignoreSynonyms) {
	// set exam variables
	setMode(examMode);
	this->answered = false;
	examTab.clear();
	this->countdown=howmany;
	this->howmany=howmany;
	this->intoforeign=intoforeign;
	this->include=include;
	this->ignoreSynonyms=ignoreSynonyms;
	this->caseSensitive = QSettings("dicto.ini", QSettings::IniFormat).value("testing/case_sensitive").value<bool>();

	updateStatusbar();
	tableWidget->clear();
	tableWidget->setRowCount(howmany);
	
	// resets all words to unpassed
	for(unsigned i=0; i<dictionarySize(); i++) cDocument->dictionary[i].passed = false;

	// create exam word table
	QTableWidgetItem* firstItem = NULL;
	for (unsigned i=0; i<howmany; i++) {
		// pick new word
		int newWord = pickWord(include);
		cDocument->dictionary[newWord].passed = true;

		QTableWidgetItem *newItem = new QTableWidgetItem(processToNice(intoforeign?cDocument->dictionary[newWord].word:cDocument->dictionary[newWord].translation, " | "));
		newItem->setFlags(Qt::ItemIsEnabled );
		tableWidget->setItem(i, 0, newItem);
		QTableWidgetItem *newItem2=new QTableWidgetItem("");
		tableWidget->setItem(i, 1, newItem2);
		if(i == 0) firstItem=newItem2;
		examTab.push_back(&(cDocument->dictionary[newWord]));
	}

	// end
	examStatusLabel->setText(tr("Exam status: pending"));
	tableWidget->setCurrentItem(firstItem);
}

// checks exam
void WMain::checkexam()  {
	if(!answered) {
		int userAnswer = askUser(tr("Are you sure to submit exam?"));
		if(userAnswer != 2) return;
	
		unsigned good=0;
			for (unsigned u=0; u<examTab.size(); u++) {
				if (examTab[u]->check(tableWidget->item(u, 1)->text(), intoforeign, ignoreSynonyms, caseSensitive)) {
					tableWidget->item(u, 1)->setText(tr("Good!"));
					good++;
					examTab[u]->wordstatus = true;
					cDocument->filechanged = true;
				}
				else {
					tableWidget->item(u, 1)->setText(tr("Wrong (%1)").arg(intoforeign?examTab[u]->translation:examTab[u]->word));
				}
				tableWidget->item(u, 1)->setFlags(Qt::ItemIsEnabled);
			}
			answered = true;
			examStatusLabel->setText(tr("Exam status: ended\nMistakes: %1, Grade: %2 (%3%)")
									.arg(howmany-good)
									.arg(grade(good, howmany))
									.arg(good*100/howmany));
			cancelExamButton->setEnabled(false);
			examTab.clear();
			return;
		}
	else {
		if(cDocument->passed() == dictionarySize()) {
			QMessageBox::information(this, tr("Congratulations"), tr("All words learned\nReset statistics"));
		}
		setNormalMode();
	}
	cDocument->filechanged=true;
}

// cancels exam
void WMain:: cancelexam() {
	int userAnswer = askUser(tr("Are you sure to cancel exam?"));
	if(userAnswer == 2) {
		setNormalMode();
	}
	return;
}

