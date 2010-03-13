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

enum Language {English=1, Polish=2, Russian=3};

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
	int askUser(QString message);
	int dictionarySize();
	QString processToNice(QString string, QString delimiter);

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
	QAction *settingsAction;
	QAction *quitAction;
	QAction *testAction;
	QAction *examAction;
	QAction *statsAction;
	QAction *aboutAction;
	int maxRecentFiles;
	QAction *recentFilesActions[10];
	QWidget *mainWidget;
	QListWidget *listWidget;
	QLineEdit *searchBar;
	QLabel *questionLabel;
	QLabel *answerLabel;
	QLineEdit *answerEdit;
	QPushButton *submitWordButton;
	QPushButton *cancelTestButton;
	QLabel *examStatusLabel;
	QTableWidget *tableWidget;
	QPushButton *submitExamButton;
	QPushButton *cancelExamButton;
	QProgressBar *progressBar;
	QSystemTrayIcon *trayIcon;

	std::vector <CEntry*> currentList;
	QQueue<CEntry*> testQueue;
	QVector<int> unpassed;
	std::vector <CEntry*> examTab;
	CEntry *currentEntry;
	bool intoforeign;
	bool include;
	bool ignoreSynonyms;
	bool caseSensitive;
	bool answered;
	unsigned countdown;
	unsigned howmany;
	int hintsize;

	void createMenus();
	void createStatusBar();
	void createTrayIcon();
	int pickWord(bool include);
	QString grade(unsigned good, unsigned howmany);
	void endTest(bool display, QString message = "");
	void closeEvent(QCloseEvent * e);
	CEntry *currentRow();
	void saveFileAction(bool saveas = false);
	void openFileAction(QString filename);
	void updateRecentFileActions();
	void setCurrentFile(QString newfilename);
	void setActions(bool status);

private slots:
	void newfile();
	void openfile(QString filename ="");
	void savefile();
	void saveas();
	void show_settings();
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
	void trayactivated(QSystemTrayIcon::ActivationReason reason);
	void openRecentFile();

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

