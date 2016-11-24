#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

class CreateServerDialog : public QDialog
{
	Q_OBJECT

private:
	QLabel *ipLabel;
	QLabel *portLabel;
	QVBoxLayout *layout;
	QHBoxLayout *ipLayout;
	QHBoxLayout *portLayout;
	QHBoxLayout *buttonLayout;
	QLineEdit *ipEdit;
	QLineEdit *portEdit;
	QPushButton *okButton;
	QPushButton *cancelButton;

public:
	CreateServerDialog(QWidget *parent);
	~CreateServerDialog();
	QString getIP();
	QString getPort();

signals:
	void okClicked();

public slots:
	void setIP(QString a);
	void setPort(QString a);
};