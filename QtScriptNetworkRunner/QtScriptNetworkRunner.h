#pragma once

#include <QMainWindow>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>

class QtScriptNetworkRunner : public QMainWindow
{
    Q_OBJECT

public:
    QtScriptNetworkRunner(QWidget *parent = 0);
    ~QtScriptNetworkRunner();
private:
    void setUI();
    QPlainTextEdit *m_scriptEdit = nullptr;
    QPushButton *m_openButton = nullptr;
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_sendButton = nullptr;
    QSplitter *m_splitter = nullptr;
    QWidget *m_buttonsWidget  = nullptr;
    QVBoxLayout *m_buttonsLayout  = nullptr;
};
