#include "nameInput.h"

nameInput::nameInput(QWidget *parent) : QDialog(parent)
{
	layout = new QVBoxLayout(this);
	edit = new QLineEdit(this);
	okButton = new QPushButton(this);
	setWindowTitle(u8"��������");
	okButton->setText(u8"ȷ�ϸ���");
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