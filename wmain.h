/*******************************************************************************/
/** dicto v 1.1 WMain class header file                                       **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#ifndef WMAIN_H
#define WMAIN_H

#include <QtGui>
#include <QMainWindow>
#include "cdocument.h"
#include "centry.h"
#include "wabout.h"

#define VERSION "1.1"
#define ICON ":/dictologo.png"

enum Mode {normalMode, disabledMode, enabledMode, testMode, examMode};

class WMain : public QMainWindow {
    Q_OBJECT

public:
    WMain(QWidget *parent = 0);
    ~WMain();
    void test(unsigned howmany, bool intoforeign, bool include);
    void exam(unsigned howmany, bool intoforeign, bool include);
    void centerWidgetOnScreen(QWidget*);

    CDocument *cDocument;
    Mode mode;

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
    QTableWidget *tableWidget;
    QPushButton *submitExamButton;
    QPushButton *cancelExamButton;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    QPrinter *printer;

    bool intoforeign;
    bool include;
    unsigned countdown;
    unsigned howmany;
    CEntry *currentEntry;
    std::vector <CEntry*> examTab;
    bool answered;
    unsigned hintsize;

    void createMenus();
    void createStatusBar();
    QString grade(unsigned good, unsigned howmany);
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
