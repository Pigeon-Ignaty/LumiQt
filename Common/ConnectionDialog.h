#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class ConnectionDialog  : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionDialog (QWidget *parent = nullptr);
    void setUI();

    // Методы для получения введённых значений
    QString getIp();
    int getPort();
private:
    QLineEdit *m_ipEdit = nullptr;
    QLineEdit *m_portEdit = nullptr;
    QPushButton *m_saveButton = nullptr;
};

