#include "nameInput.h"

nameInput::nameInput(QWidget *parent) : QDialog(parent)
{
	layout = new QVBoxLayout(this);
	edit = new QLineEdit(this);
	okButton = new QPushButton(this);
	setWindowTitle(u8"更改名字");
	okButton->setText(u8"确认更改");
	layout->addWidget(edit);
	layout->addWidget(okButton);
	edit->setText("default");
	connect(okButton, SIGNAL(clicked()), this, SIGNAL(okClicked()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
}

nameInput::~nameInput()
{
	delete okButton;
	delete edit;
	delete layout;
}

QString nameInput::getName()
{
	return edit->text();
}