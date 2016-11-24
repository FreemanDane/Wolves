#include "createServerDialog.h"

CreateServerDialog::CreateServerDialog(QWidget *parent) : QDialog(parent)
{
	ipLabel = new QLabel(this);
	portLabel = new QLabel(this);
	layout = new QVBoxLayout(this);
	ipLayout = new QHBoxLayout(this);
	portLayout = new QHBoxLayout(this);
	buttonLayout = new QHBoxLayout(this);
	okButton = new QPushButton(this);
	cancelButton = new QPushButton(this);
	ipEdit = new QLineEdit(this);
	portEdit = new QLineEdit(this);
	ipLayout->addWidget(ipLabel);
	ipLayout->addWidget(ipEdit);
	portLayout->addWidget(portLabel);
	portLayout->addWidget(portEdit);
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	ipLabel->setText(u8"IP地址");
	portLabel->setText(u8"端口号");
	okButton->setText(u8"确定");
	cancelButton->setText(u8"取消");
	layout->addLayout(ipLayout);
	layout->addLayout(portLayout);
	layout->addLayout(buttonLayout);
	QRegExp ipRange("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
	QRegExp portRange("[0-9]{1,4}");
	ipEdit->setValidator(new QRegExpValidator(ipRange));
	portEdit->setValidator(new QRegExpValidator(portRange));
	connect(okButton, SIGNAL(clicked()), this, SIGNAL(okClicked()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(hide()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));
}

CreateServerDialog::~CreateServerDialog()
{
	delete ipLabel;
	delete portLabel;
	delete okButton;
	delete cancelButton;
	delete ipEdit;
	delete portEdit;
	delete buttonLayout;
	delete ipLayout;
	delete portLayout;
	delete layout;
}

QString CreateServerDialog::getIP()
{
	return ipEdit->text();
}

QString CreateServerDialog::getPort()
{
	return portEdit->text();
}

void CreateServerDialog::setIP(QString a)
{
	ipEdit->setText(a);
}

void CreateServerDialog::setPort(QString a)
{
	portEdit->setText(a);
}