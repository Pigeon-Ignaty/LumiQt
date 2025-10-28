#include "QtScriptNetworkRunner.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtScriptNetworkRunner w;
    w.show();

    return a.exec();
}
