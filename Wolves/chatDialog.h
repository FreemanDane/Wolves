#pragma once
#include <qdialog.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qscrollbar.h>
#include <qlayout.h>
#include <qlineedit.h>

class chatDialog : public QDialog
{
	Q_OBJECT

public:
	QTextEdit *showEdit;
	QLineEdit *inputEdit;
	QVBoxLayout *layout;
	QPushButton *sendButton;
public:
	chatDialog(QWidget *parent);
	~chatDialog();
signals:
	void clickSend();
public slots:
	QString getInput();
	void addNewMessage(QString s);
};
