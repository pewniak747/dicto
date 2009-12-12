/*******************************************************************************/
/** dicto v 1.0 CDocument class implementation file                           **/
/** This file is published under GNU/GPL licence                              **/
/** http://www.gnu.org/licenses/gpl-3.0.txt                                   **/
/** author: Tomasz Pewiński "pewniak747"                                      **/
/** contact: pewniak747@gmail.com                                             **/
/** http://dicto.ugu.pl                                                       **/
/*******************************************************************************/

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "cdocument.h"
#include "centry.h"
#include "wmain.h"

CDocument::CDocument()
{
    filename="";
    filechanged=false;
    lang_native="";
    lang_foreign="";
}

void CDocument::saveToFile(bool saveas) {
    if(this->filename=="" || saveas) {
        filename=QFileDialog::getSaveFileName(wMain,
                                              "Wybierz plik",
                                              "./",
                                              "pliki dicto (*.dic *.txt)");
    }

    QFile file(filename);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;

     QTextStream out(&file);

     out << "################################################################################\n";
     out << "# This file was created by dicto v. 1.0                                        #\n";
     out << "# This file is incompatibile with newer versions of dicto, as well as linGO    #\n";
     out << "# Applying changes to this file may cause several program errors               #\n";
     out << "# Proceed with caution                                                         #\n";
     out << "################################################################################\n";
     out << "\n";

     out << "#dictionary:\n";

     for (unsigned i=0; i<this->dictionary.size(); i++)
        out << this->dictionary[i].word<< ";" <<this->dictionary[i].translation << "\n";

     out << "\n";
     out << "#languages:\n";
     out << "lang_native=" << this->lang_native << "\n";
     out << "lang_foreign=" <<this->lang_foreign << "\n";

     out << "\n";
     out << "#learned:\n";

     for (unsigned i=0; i<this->dictionary.size(); i++)
        out << this->dictionary[i].wordstatus;

     filechanged=false;
}

void CDocument::readFromFile() {
    QString newfilename=QFileDialog::getOpenFileName(wMain,
                                                     "Wybierz plik",
                                                     "./",
                                                     "pliki dicto (*.dic *.txt)");

    if (!newfilename.isEmpty()) {
        QFile file(newfilename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        this->dictionary.clear();
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            if(line[0]=='#')
                 continue;
            if(line.contains("=")) {
                QString option=line.section("=", 0, 0);
                if(option == "lang_native")
                    this->lang_native=line.section("=", 1, 1);
                else if(option == "lang_foreign")
                    this->lang_foreign=line.section("=", 1, 1);
                else
                    continue;
            }
            else if(!line.contains(";")) {
                 for(unsigned i=0; i<line.size(); i++)
                    this->dictionary[i].wordstatus=line[i]=='0'?false:true;
            }
            else {
                 CEntry newEntry;
                 newEntry.word=line.section(";",0,0);
                 newEntry.translation=line.section(";",1,1);\
                 newEntry.wordstatus=false;
                 this->dictionary.push_back(newEntry);
                  wMain->updateStatusbar();
            }
         }
         this->filename=newfilename;
         this->filechanged=false;
         wMain->updateList();
     }
     wMain->updateStatusbar();
}

unsigned CDocument::passed() {
    unsigned passed=0;
    for(unsigned i=0; i<dictionary.size(); i++)
        if(dictionary[i].wordstatus) passed++;
    return passed;
}

void CDocument::resetStats() {
    if(dictionary.size() == 0) return;
    for(unsigned i=0; i<dictionary.size(); i++)
        dictionary[i].wordstatus=false;
    this->filechanged=true;
    wMain->updateStatusbar();
}
