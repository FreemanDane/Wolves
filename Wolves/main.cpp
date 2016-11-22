#include "Wolves.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wolves w;
    w.show();
    return a.exec();
}
