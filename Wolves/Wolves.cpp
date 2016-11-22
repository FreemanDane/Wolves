#include "Wolves.h"

Wolves::Wolves(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionBackground1, SIGNAL(triggered()), this, SLOT(changeBackground1()));
	connect(ui.actionBackground2, SIGNAL(triggered()), this, SLOT(changeBackground2()));
	connect(ui.actionBackground3, SIGNAL(triggered()), this, SLOT(changeBackground3()));
	connect(ui.actionBackground4, SIGNAL(triggered()), this, SLOT(changeBackground4()));
	connect(ui.actionBackground5, SIGNAL(triggered()), this, SLOT(changeBackground5()));
	connect(ui.actionBackground6, SIGNAL(triggered()), this, SLOT(changeBackground6()));
}

void Wolves::changeBackground1()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg1.png"));
}

void Wolves::changeBackground2()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg2.png"));
}

void Wolves::changeBackground3()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg3.png"));
}

void Wolves::changeBackground4()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg4.png"));
}

void Wolves::changeBackground5()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg5.png"));
}

void Wolves::changeBackground6()
{
	ui.label->setPixmap(QPixmap(":/Wolves/bg6.png"));
}
