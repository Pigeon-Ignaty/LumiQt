#include "ConnectionDialog.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QHostAddress>
ConnectionDialog::ConnectionDialog (QWidget *parent) : QDialog(parent)
{
    setUI();
}

void ConnectionDialog::setUI()
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);//Убираем ?
    //Компануем виджеты для ввода ip и порта
    setWindowTitle("Введите ip и port");
    QGridLayout *layout = new QGridLayout(this);

    QFont font;
    font.setPointSize(12);

    QLabel *ipLabel = new QLabel("IP");
    ipLabel->setFont(font);
    m_ipEdit = new QLineEdit;
    m_ipEdit->setFont(font);
    QRegularExpression ipRegex( //Маска воода до 255
        R"(^((25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d\d|[1-9]?\d)$)"
    );
    m_ipEdit->setValidator(new QRegularExpressionValidator(ipRegex, m_ipEdit));
    m_ipEdit->setText("127.0.0.1");

    QLabel *portLabel = new QLabel("Port");
    portLabel->setFont(font);
    m_portEdit = new QLineEdit;
    m_portEdit->setFont(font);
    m_portEdit->setValidator(new QIntValidator(minPort, maxPort, this));//Ограничение порта
    m_portEdit->setText("8080");

    m_saveButton = new QPushButton("Сохранить");
    m_saveButton->setFont(font);
    m_saveButton->setFixedHeight(50);

    //Проверка значения порта
    connect(m_saveButton, &QPushButton::clicked, this, [this]() {
        //Проверка ip
        QHostAddress address;
        bool valid = address.setAddress(m_ipEdit->text());
        if (!valid) {
            QMessageBox::warning(this, "Ошибка", "Некорректный IP-адрес");
            return;
        }

        //Проверка порта
        bool ok;
        int port = m_portEdit->text().toInt(&ok);
        if (!ok || port < minPort || port > maxPort) {
            QMessageBox::warning(this, "Ошибка", "Порт содержит некорректные значения. Допустимый диапазон 1024–65535");
            return;
        }
        accept();
    });
    //Добавление в компановщик
    layout->addWidget(ipLabel, 0, 0);
    layout->addWidget(m_ipEdit, 0, 1);
    layout->addWidget(portLabel, 1, 0);
    layout->addWidget(m_portEdit, 1, 1);
    layout->addWidget(m_saveButton, 2, 0, 1, 2);

    setFixedSize(500, 200);
}

QString ConnectionDialog::getIp()
{
    return m_ipEdit->text();
}

int ConnectionDialog::getPort()
{
    return m_portEdit->text().toInt();
}
