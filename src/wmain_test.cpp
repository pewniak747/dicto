// dicto v 1.3 WMain test implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wmain.h"

// starts test
void WMain::test(unsigned howmany, bool intoforeign, bool include, bool ignoreSynonyms) {
	// prepare test variables
	setMode(testMode);
	this->howmany = howmany;
	this->countdown = howmany;
	this->intoforeign = intoforeign;
	this->include = include;
	this->ignoreSynonyms = ignoreSynonyms;
	this->answered = true;
	this->hintsize = 1;
	this->caseSensitive = QSettings("dicto.ini", QSettings::IniFormat).value("testing/case_sensitive").value<bool>();
	
	// reset all words to unpassed
	for(unsigned i=0; i<dictionarySize(); i++) cDocument->dictionary[i].passed = false;
	
	// prepare test queue
	testQueue.clear();
	int i;
	for(i=0; i<howmany; i++) {
		int newWord = pickWord(include);
		if(newWord == -1) {
			setMode(normalMode);
			updateStatusbar();
			break;
		}
		testQueue.enqueue(&cDocument->dictionary[newWord]);
		cDocument->dictionary[newWord].passed = true;
	}
	if(testQueue.empty()) { // not supposed to happen
		endTest(true, tr("No words match your criteria"));
		return;
	}
	check();
}

// checks user input
void WMain::check() {
	if(mode!=testMode) return;

	if(!answered) {
		if(currentEntry->check(answerEdit->text(), intoforeign, ignoreSynonyms, caseSensitive)) {
			questionLabel->setText(tr("Good!"));
			answerLabel->clear();
			if(hintsize < 2) {
				currentEntry->wordstatus = true;
				countdown--;
				testQueue.dequeue();
			}
			else {
				testQueue.enqueue(currentEntry);
				testQueue.dequeue();
			}
		}
		else {
			questionLabel->setText(tr("Wrong"));
			answerLabel->setText(tr("%1 - %2")
				.arg(processToNice(intoforeign?currentEntry->word:currentEntry->translation, "\n"))
				.arg(processToNice(intoforeign?currentEntry->translation:currentEntry->word, "\n")));
			testQueue.enqueue(currentEntry);
			testQueue.dequeue();
		}
		submitWordButton->setText(tr("Next"));
		answered = true;
		cDocument->filechanged = true;
		updateStatusbar();
	}
	else {
		if(testQueue.empty()) {
			endTest(true, tr("All words learned!"));
			return;
		}
		currentEntry = testQueue.head();
		
		// process question string
		QString question = intoforeign ? currentEntry->word : currentEntry->translation;
		question = processToNice(question, "\n");
		
		// append speech part
		if(currentEntry->sp != spNone) question.append("("+currentEntry->spToString()+")");

		// end
		questionLabel->setText(question);
		answerLabel->clear();
		answered = false;
		hintsize=1;
		submitWordButton->setText(tr("OK"));
		answerEdit->clear();
		answerEdit->setFocus();
		updateStatusbar();
	}
}

// displays message and ends test 
void WMain::endTest(bool display, QString message) {
	if(display) {
		QMessageBox::information(this, tr("Test ended"), message);
	}
	setMode(normalMode);
	updateStatusbar();
	return;
}

// cancels test
void WMain::canceltest() {
	int userAnswer = askUser(tr("Are you sure to cancel test?"));
	if(userAnswer == 2) endTest(false);
	else if(userAnswer == 1) return;
	else return;
}
