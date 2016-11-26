#include "chatDialog.h"

chatDialog::chatDialog(QWidget *parent) :QDialog(parent = nullptr)
{
	layout = new QVBoxLayout(this);
	inputEdit = new QLineEdit(this);
	showEdit = new QTextEdit(this);
	sendButton = new QPushButton(this);
	layout->addWidget(showEdit);
	layout->addWidget(inputEdit);
	layout->addWidget(sendButton);
	sendButton->setText(u8"·¢ËÍ");
	showEdit->setReadOnly(true);
	connect(sendButton, SIGNAL(clicked()), this, SIGNAL(clickSend()));
}

chatDialog::~chatDialog()
{
	delete inputEdit;
	delete showEdit;
	delete sendButton;
	delete layout;
}

QString chatDialog::getInput()
{
	QString a = inputEdit->text();
	inputEdit->setText("");
	return a;
}

void chatDialog::addNewMessage(QString s)
{
	showEdit->append(s);
}