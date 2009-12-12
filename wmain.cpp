/*******************************************************************************/
/** dicto v 1.1 WMain class implementation file                               **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#include "wmain.h"
#include "wdialog.h"
#include "cdocument.h"
#include "wprepare.h"
#include "wabout.h"
#include "wprops.h"


WMain::WMain(QWidget *parent) : QMainWindow(parent) {
    cDocument=new CDocument ;
    Mode mode=normalMode;
    parent=0;

    this->resize(400, 400);
    createMenus();

    mainWidget=new QWidget(this);
    setCentralWidget(mainWidget);

    searchBar=new QLineEdit;
    listWidget=new QListWidget;

    questionLabel=new QLabel;
        questionLabel->setText(tr("Test!"));
        questionLabel->setAlignment(Qt::AlignCenter);
    answerEdit=new QLineEdit;
    submitWordButton=new QPushButton;
        submitWordButton->setText(tr("OK"));
    cancelTestButton=new QPushButton;
        cancelTestButton->setText(tr("Zakończ test"));

    tableWidget=new QTableWidget;
	tableWidget->setColumnCount(2);
	tableWidget->horizontalHeader()->hide();
	tableWidget->verticalHeader()->hide();
	tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    submitExamButton=new QPushButton;
        submitExamButton->setText(tr("Oddaj egzamin"));
    cancelExamButton=new QPushButton;
        cancelExamButton->setText(tr("Anuluj egzamin"));

    QVBoxLayout *mainLayout=new QVBoxLayout(mainWidget);

        QVBoxLayout *normalLayout=new QVBoxLayout();
        normalLayout->addWidget(searchBar);
        normalLayout->addWidget(listWidget);
        mainLayout->addLayout(normalLayout);

        QVBoxLayout *testLayout=new QVBoxLayout();
            QVBoxLayout *test2Layout=new QVBoxLayout;
            test2Layout->addWidget(questionLabel);
            test2Layout->addWidget(answerEdit);
            test2Layout->addWidget(submitWordButton);
        testLayout->addLayout(test2Layout);
        testLayout->addWidget(cancelTestButton);
        mainLayout->addLayout(testLayout);

        QVBoxLayout *examLayout=new QVBoxLayout();
        examLayout->addWidget(tableWidget);
        examLayout->addWidget(submitExamButton);
        examLayout->addWidget(cancelExamButton);
        mainLayout->addLayout(examLayout);

        progressBar=new QProgressBar;
        progressBar->resize(200, 10);
        progressBar->setMinimum(0);

        statusLabel=new QLabel;
        statusLabel->setText("");

        statusBar()->addPermanentWidget(statusLabel);
        statusBar()->addPermanentWidget(progressBar);
        updateStatusbar();

    setLayout(mainLayout);

   setMode(mode);

       printer = new QPrinter;


    setWindowTitle(tr("dicto"));
    setWindowIcon(QIcon(ICON));

    centerWidgetOnScreen(this);

    connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(updateList()));
    connect(listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editentry()));
    connect(submitWordButton, SIGNAL(clicked()), this, SLOT(check()));
    connect(cancelTestButton, SIGNAL(clicked()), this, SLOT(canceltest()));
    connect(cancelExamButton, SIGNAL(clicked()), this, SLOT(cancelexam()));
    connect(submitExamButton, SIGNAL(clicked()), this, SLOT(checkexam()));

    QShortcut *submitShortcut=new QShortcut(Qt::Key_Return, this);
    connect(submitShortcut, SIGNAL(activated()), this, SLOT(check()));

    QShortcut *hintShortcut=new QShortcut(QKeySequence("Ctrl+H"), this);
    connect(hintShortcut, SIGNAL(activated()), this, SLOT(hint()));
}

WMain::~WMain() {}

void WMain::createMenus() {
    fileMenu=new QMenu(this);
    wordMenu=new QMenu(this);
    testMenu=new QMenu(this);
    helpMenu=new QMenu(this);

    newAction=new QAction(tr("&Nowy"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(tr("Utwórz nowy słownik"));

    openAction=new QAction(tr("&Otwórz..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Otwórz słownik"));

    saveAction=new QAction(tr("&Zapisz"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Zapisz słownik"));

    saveasAction=new QAction(tr("&Zapisz jako..."), this);
    saveasAction->setShortcuts(QKeySequence::SaveAs);
    saveasAction->setStatusTip(tr("Zapisz słownik jako"));

    printAction=new QAction(tr("&Drukuj"), this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(tr("Drukuj słownik"));

    quitAction=new QAction(tr("&Wyjście"), this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setStatusTip(tr("Wyjd z programu"));

    addAction=new QAction(tr("&Dodaj..."), this);
    addAction->setShortcut(Qt::Key_Insert);
    addAction->setStatusTip(tr("Dodaj nowe słowo"));

    editAction=new QAction(tr("&Edytuj..."), this);
    editAction->setStatusTip(tr("Edytuj bieżące słowo"));

    deleteAction=new QAction(tr("&Usuń"), this);
    deleteAction->setShortcut(Qt::Key_Delete);
    deleteAction->setStatusTip(tr("Usuń bieżące słowo"));

    sortAction=new QAction(tr("&Sortuj"), this);
    sortAction->setShortcut(QKeySequence("Ctrl+A"));
    sortAction->setStatusTip(tr("Sortuj słownik alfabetycznie"));

    testAction=new QAction(tr("&Test..."), this);
    testAction->setShortcut(QKeySequence("Ctrl+T"));
    testAction->setStatusTip(tr("Przygotuj test"));

    examAction=new QAction(tr("&Egzamin..."), this);
    examAction->setShortcut(QKeySequence("Ctrl+E"));
    examAction->setStatusTip(tr("Przygotuj egzamin"));

    statsAction=new QAction(tr("&Statystyki..."), this);
    statsAction->setShortcut(QKeySequence("Ctrl+W"));
    statsAction->setStatusTip(tr("Wyświetl statystyki"));

    aboutAction=new QAction(tr("&O dicto"), this);
    aboutAction->setStatusTip(tr("O dicto"));

    fileMenu = menuBar()->addMenu(tr("&Plik"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveasAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    wordMenu = menuBar()->addMenu(tr("&Słowa"));
    wordMenu->addAction(addAction);
    wordMenu->addAction(editAction);
    wordMenu->addAction(deleteAction);
    //wordMenu->addAction(sortAction);

    testMenu = menuBar()->addMenu(tr("&Test"));
    testMenu->addAction(testAction);
    testMenu->addAction(examAction);
    testMenu->addSeparator();
    testMenu->addAction(statsAction);

    helpMenu = menuBar()->addMenu(tr("&Pomoc"));
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



    statusBar()->showMessage(tr("Gotowe"));
}

void WMain::updateList() {
    //cDocument->sortDictionary();
    QString search=searchBar->text();
    listWidget->clear();
    for(unsigned i=0; i<cDocument->dictionary.size(); i++) {
        QString word=cDocument->dictionary[i].word;
        QString translation=cDocument->dictionary[i].translation;
        QString result=word+" - "+translation;
        if(search==""||word.contains(search)||translation.contains(search))
            new QListWidgetItem(result, listWidget);
    }
}

void WMain::addentry() {
    WDialog *wDialog=new WDialog(0, -1);
    wDialog->show();
    setMode(disabledMode);
}

void WMain::editentry() {
    if(cDocument->dictionary.size()>0 && listWidget->currentRow()<=cDocument->dictionary.size()) {
        WDialog *wDialog=new WDialog(0, listWidget->currentRow());
        wDialog->show();
        setMode(disabledMode);
    }
}

void WMain::deleteentry() {
    if(cDocument->dictionary.size()>0) {
        int currentrow=listWidget->currentRow();
        for(unsigned i=currentrow; i<cDocument->dictionary.size()-1; i++)
            qSwap(cDocument->dictionary[i], cDocument->dictionary[i+1]);
        cDocument->dictionary.pop_back();
        cDocument->filechanged=true;
        updateList();
    }
}

void WMain::sortall() {
    if(cDocument->dictionary.size() > 2)
        cDocument->sortDictionary();
    else return;
}

void WMain::newfile() {
    if(cDocument->filechanged) {
         QMessageBox messageBox(this);
          messageBox.setText(tr("Plik został zmieniony. Zapisać?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
          QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
          cancelButton->setText(tr("Anuluj"));
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

void WMain::savefile() {
    cDocument->saveToFile(false);
}

void WMain::saveas() {
    cDocument->saveToFile(true);
}

void WMain::openfile() {
    if(cDocument->filechanged) {
          QMessageBox messageBox(this);
          messageBox.setText(tr("Plik został zmieniony. Zapisać?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
          QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
          cancelButton->setText(tr("Anuluj"));
          messageBox.setIcon(QMessageBox::Warning);
             messageBox.exec();
            if (messageBox.clickedButton() == yesButton)
                cDocument->readFromFile();
            if (messageBox.clickedButton() == cancelButton)
                return;
            if (messageBox.clickedButton() == noButton)
                messageBox.close();
                cDocument->readFromFile();

          }
    else
        cDocument->readFromFile();
}

void WMain::print() {
    if(cDocument->dictionary.size() == 0) return;
    QPrintDialog printDialog(printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
         QPainter painter;
         painter.begin(printer);



        painter.drawText(0, 0, tr("Nazwa pliku: %1").arg(cDocument->filename));
        painter.drawText(0, 12, tr("dicto - program do nauki słówek http://dicto.ugu.pl"));
        for(int i=0; i<cDocument->dictionary.size(); i++) {
            painter.drawText(0, 12*(i+2)+10, tr("%1").arg(cDocument->dictionary[i].word));
            painter.drawText(250, 12*(i+2)+10, tr("%1").arg(cDocument->dictionary[i].translation));
        }

    }
}

void WMain::preparetest() {
    if(this->cDocument->dictionary.size()==0)
        QMessageBox::information(this, tr("Błąd"), tr("Słownik jest pusty!"));
    else if(this->cDocument->dictionary.size()==cDocument->passed())
        QMessageBox::information(this, tr("Gratulacje"), tr("Wszystkie słówka nauczone!"));
    else {
        WPrepare *wPrepare=new WPrepare(0, false);
        wPrepare->show();
    }
    hintsize=1;

}

void WMain::test(unsigned howmany, bool intoforeign, bool include) {
    setMode(testMode);

    this->countdown=howmany;
    this->howmany=howmany;
    this->intoforeign=intoforeign;
    this->include=include;

    updateStatusbar();

    unsigned random;
        do {
            random=rand()%cDocument->dictionary.size();
        } while(include || cDocument->dictionary[random].wordstatus);

        currentEntry=&(cDocument->dictionary[random]);

    if(intoforeign) questionLabel->setText(currentEntry->word);
    else questionLabel->setText(currentEntry->translation);

    answered=false;
    hintsize=1;

    answerEdit->clear();
    answerEdit->setFocus();


}

void WMain::check() {
    if(mode!=testMode)
        return;

    if(!answered) {
        if(currentEntry->check(answerEdit->text(), intoforeign)) {
            questionLabel->setText(tr("Dobrze"));
            if(hintsize < 2) {
                currentEntry->wordstatus=true;
                countdown--;
            }
        }
        else {
            questionLabel->setText(tr("Źle\n(%1 - %2)")
                                                .arg(intoforeign?currentEntry->word:currentEntry->translation)
                                                .arg(intoforeign?currentEntry->translation:currentEntry->word));
        }
        submitWordButton->setText(tr("Dalej"));
        answered=true;
        cDocument->filechanged=true;
        updateStatusbar();
    }
    else {
        if(this->cDocument->dictionary.size()==cDocument->passed()) {
            QMessageBox::information(this, tr("Gratulacje!"), tr("Wszystkie słówka nauczone!\nZresetuj statystyki"));
            setMode(normalMode);
            updateStatusbar();
            return;
        }
        else if(countdown==0) {
            QMessageBox::information(this, tr("Koniec"), tr("Koniec testu!"));
            setMode(normalMode);
            updateStatusbar();
            return;
        }
        unsigned random;
        do {
            random=rand()%cDocument->dictionary.size();
        } while(include || cDocument->dictionary[random].wordstatus);

        currentEntry=&(cDocument->dictionary[random]);
        answerEdit->clear();
    if(intoforeign) questionLabel->setText(currentEntry->word);
    else questionLabel->setText(currentEntry->translation);

    answered=false;
    hintsize=1;

    submitWordButton->setText(tr("OK"));
    answerEdit->setFocus();
    updateStatusbar();
    }
}

void WMain::canceltest() {
    QMessageBox messageBox(this);
          messageBox.setText(tr("Czy na pewno chcesz zakończyć test?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
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

void WMain::hint() {
    if(mode != testMode) return;
    QString answer = intoforeign ? currentEntry->translation : currentEntry->word;
    if(answer.length()<hintsize || answered) return;

    answerEdit->setText(answer.mid(0, hintsize));
    hintsize++;
}

void WMain::prepareexam() {
    if(this->cDocument->dictionary.size()==0)
        QMessageBox::information(this, tr("Błąd"), tr("Słownik jest pusty!"));
    else if(this->cDocument->dictionary.size()==cDocument->passed())
        QMessageBox::information(this, tr("Gratulacje"), tr("Wszystkie słówka nauczone!"));
    else {
        WPrepare *wPrepare=new WPrepare(0, true);
        wPrepare->show();
    }
}

void WMain::exam(unsigned howmany, bool intoforeign, bool include) {
    setMode(examMode);
    this->answered=false;
    srand(time(0));

    tableWidget->clear();
    examTab.clear();

    this->countdown=howmany;
    this->howmany=howmany;
    this->intoforeign=intoforeign;
    this->include=include;

    updateStatusbar();

    tableWidget->setRowCount(howmany);

    unsigned random;
    QTableWidgetItem* firstItem;
    for (unsigned i=0; i<howmany; i++) {
        do {
            random=rand()%cDocument->dictionary.size();
        } while(include || cDocument->dictionary[random].wordstatus);

        cDocument->dictionary[random].wordstatus=true;

        QTableWidgetItem *newItem = new QTableWidgetItem(intoforeign?cDocument->dictionary[random].word:cDocument->dictionary[random].translation);
        newItem->setFlags(Qt::ItemIsEnabled );
        tableWidget->setItem(i, 0, newItem);
        QTableWidgetItem *newItem2=new QTableWidgetItem("");
        tableWidget->setItem(i, 1, newItem2);
        if(i == 0) firstItem=newItem2;
        examTab.push_back(&(cDocument->dictionary[random]));
    }

    tableWidget->setCurrentItem(firstItem);

}

void WMain::checkexam()  {
    if(!answered) {

        QMessageBox messageBox(this);
          messageBox.setText(tr("Czy na pewno chcesz oddać egzamin?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
          messageBox.setIcon(QMessageBox::Question);
          messageBox.exec();

            if (messageBox.clickedButton() == yesButton) {
                unsigned good=0;
                for (unsigned u=0; u<examTab.size(); u++) {
                    if (examTab[u]->check(tableWidget->item(u, 1)->text(), intoforeign)) {
                        tableWidget->item(u, 1)->setText(tr("Dobrze!"));
                        good++;
                        examTab[u]->wordstatus=true;
                        cDocument->filechanged=true;
                    }
                    else {
                        tableWidget->item(u, 1)->setText(tr("Źle (%1)").arg(intoforeign?examTab[u]->translation:examTab[u]->word));
                        examTab[u]->wordstatus=false;
                    }
                    tableWidget->item(u, 1)->setFlags(Qt::ItemIsEnabled);
                }
                answered=true;
                QMessageBox::information(this, tr("Wyniki testu"), tr("Ilość słów: %1\nPoprawnych: %2 (%3%)\nOcena: %4")
                                        .arg(howmany)
                                        .arg(good)
                                        .arg(good*100/howmany)
                                        .arg(this->grade(good, howmany)));

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
            QMessageBox::information(this, tr("Gratulacje!"), tr("Wszystkie słówka nauczone!\nZresetuj statystyki"));
        }
        setNormalMode();
    }
    cDocument->filechanged=true;
}

void WMain:: cancelexam() {
    QMessageBox messageBox(this);
          messageBox.setText(tr("Czy na pewno chcesz zakończyć egzamin?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
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

void WMain::setMode(Mode mode) {
    switch(mode) {

        case normalMode :
            searchBar->show();
            listWidget->show();
            questionLabel->hide();
            answerEdit->hide();
            submitWordButton->hide();
            cancelTestButton->hide();
            tableWidget->hide();
            submitExamButton->hide();
            cancelExamButton->hide();

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

            for(unsigned i=0; i<examTab.size(); i++)
                examTab[i]->wordstatus=false;

            this->mode=normalMode;
            updateStatusbar();
            break;

        case disabledMode :
            this->setEnabled(false);
            this->mode=disabledMode;
            break;

        case enabledMode :
            this->setEnabled(true);
            this->mode=normalMode;
            this->updateStatusbar();
            break;

        case testMode :
            searchBar->hide();
            listWidget->hide();
            questionLabel->show();
            answerEdit->show();
            submitWordButton->show();
            cancelTestButton->show();
            tableWidget->hide();
            submitExamButton->hide();
            cancelExamButton->hide();

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
            tableWidget->show();
			tableWidget->setColumnWidth(0, 150);
			tableWidget->setColumnWidth(1, ((tableWidget->width())/2)-5);
            submitExamButton->show();
            cancelExamButton->show();
			cancelExamButton->setEnabled(true);

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

void WMain::updateStatusbar() {
    statusLabel->setText("");
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
        statusLabel->setText(tr("Postęp testu"));
        progressBar->setMaximum(this->howmany);
        progressBar->setValue(howmany-countdown);
    }
}

void WMain::stats() {
    /*QMessageBox msgBox(this);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(tr("Statystyki\nNazwa pliku: %1\nJęzyk ojczysty: %2\nJęzyk obcy: %3\nIlość słów: %4\nNauczone: %5 (%6%)")
                   .arg(cDocument->filename.isEmpty() ? tr("nieznana") : cDocument->filename)
                   .arg(cDocument->lang_native.isEmpty() ? tr("nieznany") : cDocument->lang_native)
                   .arg(cDocument->lang_foreign.isEmpty() ? tr("nieznany") : cDocument->lang_foreign)
                   .arg(cDocument->dictionary.size())
                   .arg(cDocument->passed())
                   .arg(cDocument->passed()*100/(cDocument->dictionary.size()!=0?cDocument->dictionary.size():1))
                   );
    QAbstractButton *resetButton = msgBox.addButton(tr("Reset statystyk"), QMessageBox::ActionRole);
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.exec();
    if (msgBox.clickedButton() == resetButton)
                cDocument->resetStats();*/
    WProps* wProps = new WProps(0);
    wProps->show();
    setMode(disabledMode);
}

void WMain::about() {
    setMode(disabledMode);
    WAbout* aboutBox = new WAbout(0);
    aboutBox->show();
}

void WMain::centerWidgetOnScreen (QWidget * widget) {
     QRect rect = QApplication::desktop()->availableGeometry();

     widget->move(rect.center() - widget->rect().center());
}

QString WMain::grade(unsigned good, unsigned howmany) {
    double percent = double(good) / double(howmany);

    if(percent < 0.5) return "1";
    if(percent < 0.6) return "2";
    if(percent < 0.7) return "3";
    if(percent < 0.85) return "4";
    if(percent <= 1) return "5";
    else return "nieznana";
}

void WMain::closeEvent(QCloseEvent * e) {
    if(cDocument->filechanged) {
         QMessageBox messageBox(this);
          messageBox.setText(tr("Plik został zmieniony. Zapisać?"));
          QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
          yesButton->setText(tr("Tak"));
          QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
          noButton->setText(tr("Nie"));
          QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
          cancelButton->setText(tr("Anuluj"));
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
