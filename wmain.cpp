// dicto v 1.3 WMain class implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wmain.h"
#include "wdialog.h"
#include "cdocument.h"
#include "wprepare.h"
#include "wabout.h"
#include "wprops.h"
#include "wprint.h"

// WMain constructor
WMain::WMain(QWidget *parent) : QMainWindow(parent) {
	// set window properties
	resize(400, 400);
	setWindowTitle(tr("dicto"));
	setWindowIcon(QIcon(ICON));
	centerWidgetOnScreen(this);
	
	// set random seed
	srand(time(0));
	
	//create widgets
	mainWidget = new QWidget(this);
	setCentralWidget(mainWidget);
	searchBar = new QLineEdit;
	listWidget = new QListWidget;
	questionLabel = new QLabel(tr("Test!"), this);
	answerEdit = new QLineEdit;
	submitWordButton = new QPushButton(tr("OK"), this);
	cancelTestButton = new QPushButton(tr("End test"), this);
	examStatusLabel  =  new QLabel;
	tableWidget = new QTableWidget;
	submitExamButton = new QPushButton(tr("Submit exam"), this);
	cancelExamButton = new QPushButton(tr("Cancel exam"), this);
	progressBar = new QProgressBar;
	createMenus();

	// initialize widgets
	questionLabel->setAlignment(Qt::AlignCenter);
	tableWidget->setColumnCount(2);
	tableWidget->horizontalHeader()->hide();
	tableWidget->verticalHeader()->hide();
	tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->horizontalHeader()->setStretchLastSection(true);
	progressBar->setMinimum(0);
	
	// initialize members
	cDocument = new CDocument ;
	printer = new QPrinter;
	mode = normalMode;
	parent = 0;
	
	// add layout
	QVBoxLayout *mainLayout=new QVBoxLayout(mainWidget);
		QVBoxLayout *normalLayout=new QVBoxLayout();
			normalLayout->addWidget(searchBar);
			normalLayout->addWidget(listWidget);
		mainLayout->addLayout(normalLayout);
		QVBoxLayout *testLayout=new QVBoxLayout();
			testLayout->addWidget(questionLabel);
			testLayout->addWidget(answerEdit);
			testLayout->addWidget(submitWordButton);
			testLayout->addWidget(cancelTestButton);
		mainLayout->addLayout(testLayout);
		QVBoxLayout *examLayout=new QVBoxLayout();
			examLayout->addWidget(examStatusLabel);
			examLayout->addWidget(tableWidget);
			examLayout->addWidget(submitExamButton);
			examLayout->addWidget(cancelExamButton);
		mainLayout->addLayout(examLayout);
	mainWidget->setLayout(mainLayout);
	statusBar()->addPermanentWidget(progressBar);
	
	//update widgets
	updateStatusbar();
	setMode(mode);
	   
	// create shortcuts
	QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);
	connect(submitShortcut, SIGNAL(activated()), this, SLOT(check()));
	QShortcut *hintShortcut=new QShortcut(QKeySequence("Ctrl+H"), this);
	connect(hintShortcut, SIGNAL(activated()), this, SLOT(hint()));
	QShortcut *findShortcut=new QShortcut(QKeySequence("Ctrl+f"), this);
	connect(findShortcut, SIGNAL(activated()), this, SLOT(search()));

	// connect signals and slots
	connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(updateList()));
	connect(listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editentry()));
	connect(submitWordButton, SIGNAL(clicked()), this, SLOT(check()));
	connect(cancelTestButton, SIGNAL(clicked()), this, SLOT(canceltest()));
	connect(cancelExamButton, SIGNAL(clicked()), this, SLOT(cancelexam()));
	connect(submitExamButton, SIGNAL(clicked()), this, SLOT(checkexam()));
	
	statusBar()->showMessage(tr("Dicto version %1").arg(VERSION));
}

// creates all menus
void WMain::createMenus() {
	fileMenu=new QMenu(this);
	wordMenu=new QMenu(this);
	testMenu=new QMenu(this);
	helpMenu=new QMenu(this);

	newAction=new QAction(tr("&New"), this);
	newAction->setShortcuts(QKeySequence::New);
	newAction->setStatusTip(tr("Create new dictionary"));

	openAction=new QAction(tr("&Open..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open dictionary"));

	saveAction=new QAction(tr("&Save"), this);
	saveAction->setShortcuts(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save dictionary"));

	saveasAction=new QAction(tr("&Save as..."), this);
	saveasAction->setShortcuts(QKeySequence::SaveAs);
	saveasAction->setStatusTip(tr("Save dictionary as"));

	printAction=new QAction(tr("&Print"), this);
	printAction->setShortcuts(QKeySequence::Print);
	printAction->setStatusTip(tr("Print dictionary"));

	quitAction=new QAction(tr("&Quit"), this);
	quitAction->setShortcut(QKeySequence("Ctrl+Q"));
	quitAction->setStatusTip(tr("Quit dicto"));

	addAction=new QAction(tr("&Add..."), this);
	addAction->setShortcut(Qt::Key_Insert);
	addAction->setStatusTip(tr("Add new word"));

	editAction=new QAction(tr("&Edit..."), this);
	editAction->setStatusTip(tr("Edit current word"));

	deleteAction=new QAction(tr("&Delete"), this);
	deleteAction->setShortcut(Qt::Key_Delete);
	deleteAction->setStatusTip(tr("Delete current word"));

	sortAction=new QAction(tr("&Sort"), this);
	sortAction->setShortcut(QKeySequence("Ctrl+A"));
	sortAction->setStatusTip(tr("Sort dictionary"));

	testAction=new QAction(tr("&Test..."), this);
	testAction->setShortcut(QKeySequence("Ctrl+T"));
	testAction->setStatusTip(tr("Prepare test"));

	examAction=new QAction(tr("&Exam..."), this);
	examAction->setShortcut(QKeySequence("Ctrl+E"));
	examAction->setStatusTip(tr("Prepare exam"));

	statsAction=new QAction(tr("&Statistics..."), this);
	statsAction->setShortcut(QKeySequence("Ctrl+W"));
	statsAction->setStatusTip(tr("Show statistics"));

	aboutAction=new QAction(tr("&About"), this);
	aboutAction->setStatusTip(tr("About dicto"));

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveasAction);
	fileMenu->addAction(printAction);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);

	wordMenu = menuBar()->addMenu(tr("&Words"));
	wordMenu->addAction(addAction);
	wordMenu->addAction(editAction);
	wordMenu->addAction(deleteAction);
	wordMenu->addSeparator();
	wordMenu->addAction(sortAction);

	testMenu = menuBar()->addMenu(tr("&Test"));
	testMenu->addAction(testAction);
	testMenu->addAction(examAction);
	testMenu->addSeparator();
	testMenu->addAction(statsAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);

	connect(newAction, SIGNAL(triggered()), this, SLOT(newfile()));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openfile()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(savefile()));
	connect(saveasAction, SIGNAL(triggered()), this, SLOT(saveas()));
	connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

	connect(addAction, SIGNAL(triggered()), this, SLOT(addentry()));
	connect(editAction, SIGNAL(triggered()), this, SLOT(editentry()));
	connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteentry()));
	connect(sortAction, SIGNAL(triggered()), this, SLOT(sortall()));

	connect(testAction, SIGNAL(triggered()), this, SLOT(preparetest()));
	connect(examAction, SIGNAL(triggered()), this, SLOT(prepareexam()));
	connect(statsAction, SIGNAL(triggered()), this, SLOT(stats()));

	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

// updates word list
void WMain::updateList() {
	QString search = searchBar->text();
	listWidget->clear();
	currentList.clear();
	for(unsigned i=0; i<cDocument->dictionary.size(); i++) {
		QString word = cDocument->dictionary[i].word;
		QString translation = cDocument->dictionary[i].translation;
		QString result=translation+" - "+word;
		if(search==""||word.contains(search)||translation.contains(search)) {
			QListWidgetItem *newItem = new QListWidgetItem(processToNice(result, " | "), listWidget);
			listWidget->addItem(newItem);
			currentList.push_back(i);
		}
	}
}

// shows add entry window
void WMain::addentry() {
	WDialog *wDialog=new WDialog(0, -1);
	wDialog->show();
	setMode(disabledMode);
}

// shows edit entry window
void WMain::editentry() {
	if(cDocument->dictionary.size()>0 && selectedItem()<=int(cDocument->dictionary.size())) {
		WDialog *wDialog=new WDialog(0, currentList[selectedItem()]);
		wDialog->show();
		setMode(disabledMode);
	}
	else statusBar()->showMessage(tr("Dictionary is empty"), 10000);
}

// deletes entry
void WMain::deleteentry() {
	if(cDocument->dictionary.size()>0) {
		int currentrow = currentList[selectedItem()];
		for(unsigned i=currentrow; i<cDocument->dictionary.size()-1; i++)
			qSwap(cDocument->dictionary[i], cDocument->dictionary[i+1]);
		cDocument->dictionary.pop_back();
		cDocument->filechanged=true;
		updateList();
	}
}

// invokes dictionary sort
void WMain::sortall() {
	if(cDocument->dictionary.size() > 2)
		cDocument->sortDictionary();
	else {
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
		return;
	}
}

// creates new file
void WMain::newfile() {
	if(cDocument->filechanged) {
		 QMessageBox messageBox(this);
		  messageBox.setText(tr("File has been changed. Save?"));
		  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
		  yesButton->setText(tr("Yes"));
		  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
		  noButton->setText(tr("No"));
		  QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
		  cancelButton->setText(tr("Cancel"));
		  messageBox.setIcon(QMessageBox::Warning);
			 messageBox.exec();
			if (messageBox.clickedButton() == yesButton)
				cDocument->saveToFile(false);
			if (messageBox.clickedButton() == cancelButton)
				return;
			if (messageBox.clickedButton() == noButton)

				cDocument->filename="";
				cDocument->dictionary.clear();
				updateList();
				updateStatusbar();

		  }
	cDocument->filename="";
				cDocument->dictionary.clear();
				cDocument->filechanged=false;
				updateList();
				updateStatusbar();

}

// invokes file save
void WMain::savefile() {
	cDocument->saveToFile(false);
}

// inokes file save as
void WMain::saveas() {
	cDocument->saveToFile(true);
}

// opens file
void WMain::openfile() {
	if(cDocument->filechanged) {
		  QMessageBox messageBox(this);
		  messageBox.setText(tr("File has been changed. Save?"));
		  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
		  yesButton->setText(tr("Yes"));
		  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
		  noButton->setText(tr("No"));
		  QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
		  cancelButton->setText(tr("Cancel"));
		  messageBox.setIcon(QMessageBox::Warning);
			 messageBox.exec();
			if (messageBox.clickedButton() == yesButton)
				cDocument->readFromFile("");
			if (messageBox.clickedButton() == cancelButton)
				return;
			if (messageBox.clickedButton() == noButton)
				messageBox.close();
				cDocument->readFromFile("");

		  }
	else
		cDocument->readFromFile("");
}

// shows print window
void WMain::print() {
	if(cDocument->dictionary.size() == 0) {
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
		return;
	}
	WPrint *wPrint = new WPrint(0);
	wPrint->show();
	this->setMode(disabledMode);
}

// shows display test window
void WMain::preparetest() {
	if(this->cDocument->dictionary.size()==0)
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
	else if(this->cDocument->dictionary.size()==cDocument->passed())
		QMessageBox::information(this, tr("Congratulations"), tr("All words learned!"));
	else {
		WPrepare *wPrepare=new WPrepare(0, false);
		wPrepare->show();
	}
	hintsize=1;
}

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
	for(int i=0; i<cDocument->dictionary.size(); i++) cDocument->dictionary[i].passed = false;
	
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
		
		// process wuestion string
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
	QMessageBox messageBox(this);
		  messageBox.setText(tr("Are you sure to cancel test?"));
		  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
		  yesButton->setText(tr("Yes"));
		  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
		  noButton->setText(tr("No"));
		  messageBox.setIcon(QMessageBox::Question);
		  messageBox.exec();

			if (messageBox.clickedButton() == yesButton) {
				setNormalMode();
				return;
			}
			if (messageBox.clickedButton() == noButton) {
				return;
			}
}

// displays hint
void WMain::hint() {
	if(mode != testMode) return;
	QString answer = intoforeign ? currentEntry->translation : currentEntry->word;
	if(answer.length()<hintsize || answered) return;
	answerEdit->setText(answer.mid(0, hintsize));
	hintsize++;
}

// displays prepare exam window
void WMain::prepareexam() {
	if(this->cDocument->dictionary.size()==0)
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
	else if(this->cDocument->dictionary.size()==cDocument->passed())
		QMessageBox::information(this, tr("Congratulations"), tr("All words learned!"));
	else {
		WPrepare *wPrepare=new WPrepare(0, true);
		wPrepare->show();
	}
}

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

	updateStatusbar();
	tableWidget->clear();
	tableWidget->setRowCount(howmany);
	
	// resets all words to unpassed
	for(int i=0; i<cDocument->dictionary.size(); i++) cDocument->dictionary[i].passed = false;

	// create exam word table
	QTableWidgetItem* firstItem;
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
		QMessageBox messageBox(this);
		  messageBox.setText(tr("Are you sure to submit exam?"));
		  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
		  yesButton->setText(tr("Yes"));
		  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
		  noButton->setText(tr("No"));
		  messageBox.setIcon(QMessageBox::Question);
		  messageBox.exec();

			if (messageBox.clickedButton() == yesButton) {
				unsigned good=0;
				for (unsigned u=0; u<examTab.size(); u++) {
					if (examTab[u]->check(tableWidget->item(u, 1)->text(), intoforeign, ignoreSynonyms)) {
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
			if (messageBox.clickedButton() == noButton) {
				return;
			}
	}
	else {
		if(cDocument->passed() == cDocument->dictionary.size()) {
			QMessageBox::information(this, tr("Congratulations"), tr("All words learned\nReset statistics"));
		}
		setNormalMode();
	}
	cDocument->filechanged=true;
}

// cancels exam
void WMain:: cancelexam() {
	QMessageBox messageBox(this);
	  messageBox.setText(tr("Are you sure to cancel exam?"));
	  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
	  yesButton->setText(tr("Yes"));
	  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
	  noButton->setText(tr("No"));
	  messageBox.setIcon(QMessageBox::Question);
	  messageBox.exec();
	if (messageBox.clickedButton() == yesButton) {
			setNormalMode();
			return;
	}
	if (messageBox.clickedButton() == noButton) return;
}

// sets main window mode
void WMain::setMode(Mode mode) {
	switch(mode) {

		case normalMode :
			searchBar->show();
			listWidget->show();
			questionLabel->hide();
			answerEdit->hide();
			submitWordButton->hide();
			cancelTestButton->hide();
			examStatusLabel->hide();
			tableWidget->hide();
			submitExamButton->hide();
			cancelExamButton->hide();

			progressBar->show();

			newAction->setEnabled(true);
			openAction->setEnabled(true);
			saveAction->setEnabled(true);
			saveasAction->setEnabled(true);
			printAction->setEnabled(true);
			addAction->setEnabled(true);
			editAction->setEnabled(true);
			deleteAction->setEnabled(true);
			sortAction->setEnabled(true);
			testAction->setEnabled(true);
			examAction->setEnabled(true);
			statsAction->setEnabled(true);
			aboutAction->setEnabled(true);

			this->mode=normalMode;
			updateStatusbar();
			break;

		case disabledMode :
			this->setEnabled(false);
			this->mode=disabledMode;
			break;

		case enabledMode :
			this->setEnabled(true);
			setMode(normalMode);
			break;

		case testMode :
			searchBar->hide();
			listWidget->hide();
			questionLabel->show();
			answerEdit->show();
			submitWordButton->show();
			cancelTestButton->show();
			examStatusLabel->hide();
			tableWidget->hide();
			submitExamButton->hide();
			cancelExamButton->hide();

			progressBar->show();

			newAction->setEnabled(false);
			openAction->setEnabled(false);
			saveAction->setEnabled(false);
			saveasAction->setEnabled(false);
			printAction->setEnabled(false);
			addAction->setEnabled(false);
			editAction->setEnabled(false);
			deleteAction->setEnabled(false);
			sortAction->setEnabled(false);
			testAction->setEnabled(false);
			examAction->setEnabled(false);
			statsAction->setEnabled(false);
			aboutAction->setEnabled(false);

			this->mode=testMode;
			break;
		case examMode :
			searchBar->hide();
			listWidget->hide();
			questionLabel->hide();
			answerEdit->hide();
			submitWordButton->hide();
			cancelTestButton->hide();
			examStatusLabel->show();
			tableWidget->show();
			tableWidget->setColumnWidth(0, (tableWidget->width())/2);
			submitExamButton->show();
			cancelExamButton->show();
			cancelExamButton->setEnabled(true);

			progressBar->hide();

			newAction->setEnabled(false);
			openAction->setEnabled(false);
			saveAction->setEnabled(false);
			saveasAction->setEnabled(false);
			printAction->setEnabled(false);
			addAction->setEnabled(false);
			editAction->setEnabled(false);
			deleteAction->setEnabled(false);
			sortAction->setEnabled(false);
			testAction->setEnabled(false);
			examAction->setEnabled(false);
			statsAction->setEnabled(false);
			aboutAction->setEnabled(false);

			this->mode=examMode;
			break;
	}
}

// updates statusbar
void WMain::updateStatusbar() {
	if(this->mode == normalMode) {
		if(cDocument->dictionary.size()>0) {
			progressBar->setMaximum(cDocument->dictionary.size());
			progressBar->setValue(cDocument->passed());
		}
		else {
			progressBar->setMaximum(1);
			progressBar->setValue(0);
		}
	}
	else if(this->mode == testMode || this->mode == examMode) {
		progressBar->setMaximum(this->howmany);
		progressBar->setValue(howmany-countdown);
	}
}

// show stats box
void WMain::stats() {
	WProps* wProps = new WProps(0);
	wProps->show();
	setMode(disabledMode);
}

// shows about box
void WMain::about() {
	setMode(disabledMode);
	WAbout* aboutBox = new WAbout(0);
	aboutBox->show();
}

// centers widget on screen
void WMain::centerWidgetOnScreen (QWidget * widget) {
	 QRect rect = QApplication::desktop()->availableGeometry();
	 widget->move(rect.center() - widget->rect().center());
}

// calculates and returns qstring of grade
QString WMain::grade(unsigned good, unsigned howmany) {
	double percent = double(good) / double(howmany);

	if(percent < 0.5) return tr("E");
	if(percent < 0.6) return tr("D");
	if(percent < 0.7) return tr("C");
	if(percent < 0.85) return tr("B");
	if(percent <= 1) return tr("A");
	else return tr("unknown");
}

// focuses on search bar
void WMain::search() {
	if(mode != normalMode) return;
	searchBar->setFocus();
	searchBar->selectAll();
}

// returns number of random entry, -1 if no is available
int WMain::pickWord(bool include) {
	if(cDocument->dictionary.size() == cDocument->passed()) {
		QMessageBox::information(this, tr("Congratulations"), tr("All world learned!\nReset statistics"));
			return -1;
	}
	else if(countdown==0) {
		QMessageBox::information(this, tr("End"), tr("End of test!"));
		return -1;
	}
	unsigned random;
	do {
			random=rand()%cDocument->dictionary.size();
		} while(!((include || !cDocument->dictionary[random].wordstatus) && !cDocument->dictionary[random].passed));
	return random;
}

// window close event
void WMain::closeEvent(QCloseEvent * e) {
	if(cDocument->filechanged) {
		 QMessageBox messageBox(this);
		  messageBox.setText(tr("File has been changed. Save?"));
		  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
		  yesButton->setText(tr("Yes"));
		  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
		  noButton->setText(tr("No"));
		  QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
		  cancelButton->setText(tr("Cancel"));
		  messageBox.setIcon(QMessageBox::Warning);
		  messageBox.exec();

			if (messageBox.clickedButton() == yesButton) {
				cDocument->saveToFile(false);
				application->quit();
				e->accept();
				return;
			}
			if (messageBox.clickedButton() == cancelButton) {
				e->ignore();
				return;
			}
			if (messageBox.clickedButton() == noButton) {
				e->accept();
				application->quit();
				return;
			}

		   }
	else
		application->quit();
}

// replaces every '/' in string with delimiter
QString WMain::processToNice(QString string, QString delimiter) {
	int j = 0;
	while ((j = string.indexOf("/", j)) != -1) {
		string.replace(j, 1, delimiter);
	 ++j;
	}
	return string;
}

// returns index of selected item or -1
int WMain::selectedItem() {
	return listWidget->currentRow();
}

