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
	this->intoforeign = intoforeign;
	this->include = include;
	this->ignoreSynonyms = ignoreSynonyms;
	this->answered = true;
	this->hintsize = 1;
	
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
	this->howmany = i+1;
	this->countdown = howmany;
	if(testQueue.empty()) endTest(true, tr("No words match your criteria"));
	check();
}

// checks user input
void WMain::check() {
	if(mode!=testMode) return;

	if(!answered) {
		if(currentEntry->check(answerEdit->text(), intoforeign, ignoreSynonyms)) {
			questionLabel->setText(tr("<b>Good!</b>"));
			if(hintsize < 2) {
				currentEntry->wordstatus = true;
				countdown--;
			}
		}
		else {
			questionLabel->setText(tr("<b>Wrong</b> <br /> (%1 - %2)")
				.arg(intoforeign?currentEntry->word:currentEntry->translation)
				.arg(intoforeign?currentEntry->translation:currentEntry->word));
			testQueue.enqueue(testQueue.head());
		}
		testQueue.dequeue();
		submitWordButton->setText(tr("Next"));
		answered = true;
		cDocument->filechanged = true;
		updateStatusbar();
	}
	else {
		if(testQueue.empty()) endTest(true, tr("All words learned!"));
		currentEntry = testQueue.head();
		
		// process question string
		QString question = intoforeign ? currentEntry->word : currentEntry->translation;
		question = processToNice(question, "<br />");
		
		// append speech part
		if(currentEntry->sp != spNone) {
			speechPart spart = currentEntry->sp;
			if(spart == spVerb) question.append("\n(verb)");
			else if(spart == spNoun) question.append("\n(noun)");
			else if(spart == spAdjective) question.append("\n(adjective)");
			else if(spart == spAdverb) question.append("\n(adverb)");
			else if(spart == spOther) question.append("\n(other)");
		}

		// end
		if(intoforeign) questionLabel->setText("<b>"+question+"</b>");
		else questionLabel->setText("<b>"+question+"</b>");
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
