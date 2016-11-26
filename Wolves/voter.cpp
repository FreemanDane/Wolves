#include "voter.h"

voter::voter(QWidget *parent) : QDialog(parent)
{
	for (int i = 0; i < 15; ++i)
	{
		target[i] = new QRadioButton(this);
		target[i]->setEnabled(false);
		target[i]->setText(QString(u8"玩家") + QString::number(i + 1));
	}
	layout = new QVBoxLayout(this);
	okButton = new QPushButton(this);
	giveUp = new QRadioButton(this);
	giveUp->setText(u8"放弃");
	giveUp->setEnabled(false);
	okButton->setText(u8"确定");
	for (int i = 0; i < 15; ++i)
	{
		layout->addWidget(target[i]);
	}
	layout->addWidget(giveUp);
	layout->addWidget(okButton);
	setWindowTitle(u8"投票器");
	setGeometry(50, 50, 300, 250);
	connect(okButton, SIGNAL(clicked()), this, SIGNAL(okClicked()));
}

voter::~voter()
{
	for (int i = 0; i < 15; ++i)
	{
		delete target[i];
	}
	delete okButton;
	delete layout;
}

void voter::setUsabel(int i)
{
	target[i]->setEnabled(true);
}

int voter::getChosen()
{
	for (int i = 0; i < 15; ++i)
	{
		if (target[i]->isChecked())
			return i;
	}
	return -1;
}

void voter::canGiveUp(bool b)
{
	giveUp->setEnabled(b);
}

void voter::forbidden()
{
	for (int i = 0; i < 15; ++i)
	{
		target[i]->setEnabled(false);
	}
}