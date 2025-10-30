#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QUdpSocket>

class QtScriptNetworkEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtScriptNetworkEditor(QWidget *parent = 0);
    ~QtScriptNetworkEditor();
private:
    QPlainTextEdit *m_scriptEdit = nullptr;
    QPushButton *m_openButton = nullptr;
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_sendButton = nullptr;
    QSplitter *m_splitter = nullptr;
    QWidget *m_buttonsWidget  = nullptr;
    QVBoxLayout *m_buttonsLayout  = nullptr;

    QUdpSocket *m_socket = nullptr;
private:
    void setUI();

public slots:
    void slotLoadScripts();
    void slotSaveScripts();
    void slotSendScripts();

};

