#include "Wolves.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(codec);
    Wolves w;
    w.show();
    return a.exec();
}
