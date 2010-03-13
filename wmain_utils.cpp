// dicto v 1.3 WMain utilities implementation file
// This file is published under GNU/GPL licence
// http://www.gnu.org/licenses/gpl-3.0.txt
// author: Tomasz Pewiński "pewniak747"
// contact: pewniak747@gmail.com
// http://pewniak747.github.com/dicto

#include "wmain.h"

// returns number of random entry, -1 if no is available
int WMain::pickWord(bool include) {
	if(dictionarySize() == cDocument->passed()) {
		QMessageBox::information(this, tr("Congratulations"), tr("All words learned!\nReset statistics"));
			return -1;
	}
	else if(countdown==0) {
		QMessageBox::information(this, tr("End"), tr("End of test!"));
		return -1;
	}
	/*
	unsigned random;
	do {
			random=rand()%dictionarySize();
		} while(!((include || !cDocument->dictionary[random].wordstatus) && !cDocument->dictionary[random].passed));
	*/
	unpassed.clear();
	for(int i=0; i<dictionarySize(); i++) {
		if(((include || !cDocument->dictionary[i].wordstatus) && !cDocument->dictionary[i].passed))
			unpassed.push_back(i);
	}
	if(unpassed.empty()) return -1;
	else return unpassed[rand()%unpassed.size()];
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

CEntry* WMain::currentRow() {
	if(listWidget->currentRow() != -1)
		return currentList[listWidget->currentRow()];
	else return NULL;
}

// returns 0 if user asked no, 1 if cancel, 2 if yes
int WMain::askUser(QString message) {
	QMessageBox messageBox(wMain);
	  messageBox.setText(message);
	  QAbstractButton *yesButton = messageBox.addButton(QMessageBox::Yes);
	  yesButton->setText(tr("Yes"));
	  QAbstractButton *noButton = messageBox.addButton(QMessageBox::No);
	  noButton->setText(tr("No"));
	  QAbstractButton *cancelButton = messageBox.addButton(QMessageBox::Cancel);
	  cancelButton->setText(tr("Cancel"));
	  messageBox.setIcon(QMessageBox::Question);
	  messageBox.exec();
	if (messageBox.clickedButton() == yesButton) return 2;
	else if (messageBox.clickedButton() == cancelButton) return 1;
	else if (messageBox.clickedButton() == noButton) return 0;
	else return 0;
}

// returns dictionary size
int WMain::dictionarySize() {
	return cDocument->dictionary.size();
}

void WMain::updateRecentFileActions() {
	QSettings settings("dicto.ini", QSettings::IniFormat);
	QStringList files;
	if(settings.contains("recentFileList")) {
		files = settings.value("recentFileList").toStringList();
	}
	int numRecentFiles = qMin(files.size(), maxRecentFiles);
	for (int i = 0; i < numRecentFiles; ++i) {
		QString text = tr("&%1 %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
		recentFilesActions[i]->setText(text);
		recentFilesActions[i]->setData(files[i]);
		recentFilesActions[i]->setVisible(true);
	}
	for (int j = numRecentFiles; j < 10; ++j)
		recentFilesActions[j]->setVisible(false);
}

void WMain::setCurrentFile(QString newfilename) {
	if(newfilename.isEmpty()) return;
	QSettings settings("dicto.ini", QSettings::IniFormat);
	QStringList files;
	if(settings.contains("recentFileList")) {
	files = settings.value("recentFileList").toStringList();
	}
		files.removeAll(newfilename);
		files.prepend(newfilename);
		while (files.size() > maxRecentFiles)
			files.removeLast();

		settings.setValue("recentFileList", files);
		updateRecentFileActions();
}

void WMain::openRecentFile() {
	QAction *action = qobject_cast<QAction *>(sender());
	if (action) openfile(action->data().toString());
}

void WMain::setActions(bool status) {
	newAction->setEnabled(status);
	openAction->setEnabled(status);
	saveAction->setEnabled(status);
	saveasAction->setEnabled(status);
	printAction->setEnabled(status);
	settingsAction->setEnabled(status);
	for(int i=0; i<10; i++) recentFilesActions[i]->setEnabled(status);
	addAction->setEnabled(status);
	editAction->setEnabled(status);
	deleteAction->setEnabled(status);
	sortAction->setEnabled(status);
	testAction->setEnabled(status);
	examAction->setEnabled(status);
	statsAction->setEnabled(status);
	aboutAction->setEnabled(status);
}

