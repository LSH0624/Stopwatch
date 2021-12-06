#include "QtStopwatch.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtStopwatch w;
    w.show();
    return a.exec();
}
