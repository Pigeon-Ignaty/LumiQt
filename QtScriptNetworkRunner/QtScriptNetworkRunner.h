#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QUdpSocket>
#include <QHostAddress>
#include "ui_QtScriptNetworkRunner.h"

class QtScriptNetworkRunner : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtScriptNetworkRunner(QWidget *parent = nullptr);
    ~QtScriptNetworkRunner();

    void notify();
    void setIP(QString ip);
    void setPort(int port);
private:
    Ui::MainWindow *ui = nullptr;
    QUdpSocket *m_socket = nullptr;
    QMap<int, QByteArray> m_packages;
    QTimer *m_timer = nullptr;
    QString m_IP;
    int m_port;
private slots:
    void slotTimeOut();
};
