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
	this->countdown = howmany;
	this->howmany = howmany;
	this->intoforeign = intoforeign;
	this->include = include;
	this->ignoreSynonyms = ignoreSynonyms;
	this->answered = false;
	this->hintsize = 1;
	this->previousEntry = NULL;
	
	// reset all words to unpassed
	for(unsigned i=0; i<dictionarySize(); i++) cDocument->dictionary[i].passed = false;
	
	// pick new word
	int newWord = pickWord(include);
	if(newWord == -1) {
		setMode(normalMode);
		updateStatusbar();
		return;
	}
	currentEntry=&(cDocument->dictionary[newWord]);
	
	// process question string
	QString question = intoforeign ? currentEntry->word : currentEntry->translation;
	question = processToNice(question, "\n");
	 
	// append speech part
	if(currentEntry->sp != spNone) {
		speechPart spart = currentEntry->sp;
		if(spart == spVerb) question.append("\n(verb)");
		else if(spart == spNoun) question.append("\n(noun)");
		else if(spart == spAdjective) question.append("\n(adjective)");
		else if(spart == spAdverb) question.append("\n(adverb)");
		else if(spart == spOther) question.append("\n(other)");
	}

	// set questionLabel
	if(intoforeign) questionLabel->setText(question);
	else questionLabel->setText(question);

	// end
	answerEdit->clear();
	answerEdit->setFocus();
	updateStatusbar();
}

// checks user input
void WMain::check() {
	if(mode!=testMode) return;

	if(!answered) {
		if(currentEntry->check(answerEdit->text(), intoforeign, ignoreSynonyms)) {
			questionLabel->setText(tr("Good!"));
			if(hintsize < 2) {
				currentEntry->wordstatus = true;
				currentEntry->passed = true;
				countdown--;
			}
		}
		else {
			questionLabel->setText(tr("Wrong\n(%1 - %2)")
												.arg(intoforeign?currentEntry->word:currentEntry->translation)
												.arg(intoforeign?currentEntry->translation:currentEntry->word));
		}
		previousEntry = currentEntry;
		submitWordButton->setText(tr("Next"));
		answered = true;
		cDocument->filechanged = true;
		updateStatusbar();
	}
	else {
		// pick new word
		int newWord = pickWord(include);
		if(newWord == -1) {
			setMode(normalMode);
			updateStatusbar();
			return;
		}
		currentEntry=&(cDocument->dictionary[newWord]);
		
		// process question string
		QString question = intoforeign ? currentEntry->word : currentEntry->translation;
		question = processToNice(question, "\n");
		
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
		if(intoforeign) questionLabel->setText(question);
		else questionLabel->setText(question);
		answered = false;
		hintsize=1;
		submitWordButton->setText(tr("OK"));
		answerEdit->clear();
		answerEdit->setFocus();
		updateStatusbar();
	}
}

// cancels test
void WMain::canceltest() {
	int userAnswer = askUser(tr("Are you sure to cancel test?"));
	if(userAnswer == 2) {
		setNormalMode();
		return;
	}
	else if(userAnswer == 1) return;
	else return;
}
