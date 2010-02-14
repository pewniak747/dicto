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
#include "wsettings.h"
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
	createTrayIcon();

	// initialize widgets
	//QFont font;
	//font.setPointSize(20);
	//font.setBold(true);
	//questionLabel->setFont(font);
	questionLabel->setTextFormat(Qt::RichText);
	questionLabel->setAlignment(Qt::AlignCenter);
	questionLabel->setWordWrap(true);
	tableWidget->setColumnCount(2);
	tableWidget->horizontalHeader()->hide();
	tableWidget->verticalHeader()->hide();
	tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	tableWidget->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
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
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayactivated(QSystemTrayIcon::ActivationReason)));
	
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
	
	settingsAction=new QAction(tr("&Settings"), this);
	settingsAction->setShortcut(QKeySequence("Ctrl+B"));
	settingsAction->setStatusTip(tr("Settings"));

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
	fileMenu->addAction(settingsAction);
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
	connect(settingsAction, SIGNAL(triggered()), this, SLOT(show_settings()));
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

void WMain::createTrayIcon() {
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(ICON));
	trayIcon->show();
}

// updates word list
void WMain::updateList() {
	QString search = searchBar->text();
	listWidget->clear();
	currentList.clear();
	for(int i=0; i<dictionarySize(); i++) {
		QString word = cDocument->dictionary[i].word;
		QString translation = cDocument->dictionary[i].translation;
		QString result=translation+" - "+word;
		if(search==""||word.contains(search)||translation.contains(search)) {
			QListWidgetItem *newItem = new QListWidgetItem(processToNice(result, " | "), listWidget);
			listWidget->addItem(newItem);
			currentList.push_back(&cDocument->dictionary[i]);
		}
	}
}

// shows add entry window
void WMain::addentry() {
	WDialog *wDialog=new WDialog(0, NULL);
	wDialog->show();
	setMode(disabledMode);
}

// shows edit entry window
void WMain::editentry() {
	if(dictionarySize() > 0 && currentRow()) {
		WDialog *wDialog=new WDialog(0, currentRow());
		wDialog->show();
		setMode(disabledMode);
	}
	else statusBar()->showMessage(tr("Entry not selected"), 10000);
}

// deletes entry
void WMain::deleteentry() {
	if(dictionarySize() > 0) {
		cDocument->dictionary.erase(currentRow());
		cDocument->filechanged=true;
		updateList();
	}
	else {
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
		return;
	}
}

// invokes dictionary sort
void WMain::sortall() {
	if(dictionarySize() > 2)
		cDocument->sortDictionary();
	else {
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
		return;
	}
}

// creates new file
void WMain::newfile() {
	if(cDocument->filechanged) {
		int userAnswer = askUser(tr("File has been changed. Save?"));
		if(userAnswer == 2) saveFileAction();
		else if(userAnswer == 1) return;
	}
	
	delete cDocument;
	cDocument = new CDocument;
	updateList();
	updateStatusbar();
}

// invokes file save
void WMain::savefile() {
	saveFileAction(false);
}

// invokes file save as
void WMain::saveas() {
	saveFileAction(true);
}

void WMain::saveFileAction(bool saveas) {
		if(cDocument->filename=="" || saveas) {
		cDocument->filename=QFileDialog::getSaveFileName(wMain,
											  "Choose file",
											  "./",
											  tr("dicto file(*.dic);;text file(*.txt);;file(*.*)"));
	}
	cDocument->saveToFile();
}

void WMain::openFileAction() {
		QString newfilename=QFileDialog::getOpenFileName(wMain,
			tr("Choose file"),
			"./",
			tr("dicto files (*.dic);;text files (*.txt);;all files(*.*)"));
 
	if(newfilename.isEmpty()) return;
	else cDocument->readFromFile(newfilename);
}

// opens file
void WMain::openfile() {
	if(cDocument->filechanged) {
		int userAnswer = askUser(tr("File has been changed. Save?"));
		if(userAnswer == 2) {
			saveFileAction();
			openFileAction();
		}
		else if(userAnswer == 1) return;
		else openFileAction();
		}
	else
		openFileAction();
}

// shows print window
void WMain::print() {
	if(dictionarySize() == 0) {
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
		return;
	}
	WPrint *wPrint = new WPrint(0);
	wPrint->show();
	this->setMode(disabledMode);
}

void WMain::show_settings() {
	WSettings *wSettings = new WSettings(0);
	wSettings->show();
	this->setMode(disabledMode);
}

// shows display test window
void WMain::preparetest() {
	if(dictionarySize() == 0)
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
	else if(dictionarySize() == cDocument->passed())
		QMessageBox::information(this, tr("Congratulations"), tr("All words learned!"));
	else {
		WPrepare *wPrepare=new WPrepare(0, false);
		wPrepare->show();
	}
	hintsize=1;
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
	if(dictionarySize() == 0)
		statusBar()->showMessage(tr("Dictionary is empty"), 10000);
	else if(dictionarySize() == cDocument->passed())
		QMessageBox::information(this, tr("Congratulations"), tr("All words learned!"));
	else {
		WPrepare *wPrepare=new WPrepare(0, true);
		wPrepare->show();
	}
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
			answerEdit->clear();
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

void WMain::trayactivated(QSystemTrayIcon::ActivationReason reason) {
	//QMessageBox::information(this, "Info", "Tray activated");
	if(mode == disabledMode) return;
	if(this->isHidden()) {
		show();
	}
	else {
		hide();
	}
}

// updates statusbar
void WMain::updateStatusbar() {
	if(this->mode == normalMode) {
		if(dictionarySize() > 0) {
			progressBar->setMaximum(dictionarySize());
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

// focuses on search bar
void WMain::search() {
	if(mode != normalMode) return;
	searchBar->setFocus();
	searchBar->selectAll();
}

// window close event
void WMain::closeEvent(QCloseEvent * e) {
	if(cDocument->filechanged) {
		int userAnswer = askUser(tr("File has been changed. Save?"));
		if (userAnswer == 2) {
			saveFileAction();
			application->quit();
			e->accept();
		}
		else if(userAnswer == 1) e->ignore();
		else if(userAnswer == 0) {
			e->accept();
			application->quit();
		}
		else e->ignore();
		return;
	}
	else
		application->quit();
}

