// dicto v 1.3 WMain header file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#ifndef WMAIN_H
#define WMAIN_H

#include <QtGui>
#include <QMainWindow>
#include <vector>
#include "cdocument.h"
#include "centry.h"
#include "wabout.h"

#define VERSION "1.3"
#define ICON ":/dictologo.png"

enum Mode {normalMode, disabledMode, enabledMode, testMode, examMode};

class WMain : public QMainWindow {
	Q_OBJECT

public:
	CDocument *cDocument;
	Mode mode;
	QPrinter *printer;
	
	WMain(QWidget *parent = 0);
	void test(unsigned howmany, bool intoforeign, bool include, bool ignoreSynonyms);
	void exam(unsigned howmany, bool intoforeign, bool include, bool ignoreSynonyms);
	void centerWidgetOnScreen(QWidget*);
	int selectedItem();

private:
	QMenu *fileMenu;
	QMenu *wordMenu;
	QMenu *testMenu;
	QMenu *helpMenu;
	QAction *addAction;
	QAction *editAction;
	QAction *deleteAction;
	QAction *sortAction;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveasAction;
	QAction *printAction;
	QAction *quitAction;
	QAction *testAction;
	QAction *examAction;
	QAction *statsAction;
	QAction *aboutAction;
	QWidget *mainWidget;
	QListWidget *listWidget;
	QLineEdit *searchBar;
	QLabel *questionLabel;
	QLineEdit *answerEdit;
	QPushButton *submitWordButton;
	QPushButton *cancelTestButton;
	QLabel *examStatusLabel;
	QTableWidget *tableWidget;
	QPushButton *submitExamButton;
	QPushButton *cancelExamButton;
	QProgressBar *progressBar;

	std::vector <int> currentList;
	std::vector <CEntry*> examTab;
	CEntry *currentEntry;
	CEntry *previousEntry;
	bool intoforeign;
	bool include;
	bool ignoreSynonyms;
	bool answered;
	unsigned countdown;
	unsigned howmany;
	unsigned hintsize;

	void createMenus();
	void createStatusBar();
	int pickWord(bool include);
	QString grade(unsigned good, unsigned howmany);
	QString processToNice(QString string, QString delimiter);
	void closeEvent(QCloseEvent * e);

private slots:
	void newfile();
	void openfile();
	void savefile();
	void saveas();
	void print();
	void addentry();
	void editentry();
	void sortall();
	void deleteentry();
	void preparetest();
	void prepareexam();
	void stats();
	void check();
	void checkexam();
	void about();
	void hint();
	void canceltest();
	void cancelexam();
	void search();

public slots:
	void updateList();
	void updateStatusbar();
	void setMode(Mode mode);
	void setNormalMode() {setMode(normalMode);}
	void setTestMode() {setMode(testMode);}
	void setExamMode() {setMode(examMode);}
};

extern WMain *wMain;
extern QApplication *application;


#endif // WMAIN_H

