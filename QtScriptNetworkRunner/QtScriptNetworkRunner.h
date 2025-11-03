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
#include "Interpreter.h"
#include <QGraphicsScene>
class QtScriptNetworkRunner : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtScriptNetworkRunner(QWidget *parent = nullptr);
    ~QtScriptNetworkRunner();

    void notify();//Слот уведомления
    void setIP(QString ip);
    void setPort(int port);
    void drawFigures(QVector<Figure> figures);//Отрисовка фигур
private:
    Ui::MainWindow *ui = nullptr;
    QUdpSocket *m_socket = nullptr;
    QMap<int, QByteArray> m_packages;
    QTimer *m_timer = nullptr;
    QString m_IP;
    int m_port;
    QGraphicsScene *m_scene = nullptr;
private slots:
    void slotTimeOut();
    void on_pushButton_clicked();//Кнопка выполнения скрипта
    void on_pushButton_2_clicked();//Кнопка очистки поля скрипта
};
