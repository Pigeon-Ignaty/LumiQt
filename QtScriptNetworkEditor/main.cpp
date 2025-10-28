#include "QtScriptNetworkEditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtScriptNetworkEditor w;
    w.show();

    return a.exec();
}
