#include "QtScriptNetworkEditor.h"
#include <QApplication>
#include "ConnectionDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConnectionDialog dialog;
    dialog.setWindowIcon(QIcon(":/editorLogo.png"));
    int state = dialog.exec();
    if (state == QDialog::Rejected){
        return 0;
    }
    QtScriptNetworkEditor w;
    w.setIP(dialog.getIp());
    w.setPort(dialog.getPort());
    w.show();

    return a.exec();
}
