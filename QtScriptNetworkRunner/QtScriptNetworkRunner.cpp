#include "QtScriptNetworkRunner.h"
#include <QTimer>
QtScriptNetworkRunner::QtScriptNetworkRunner(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // инициализация UI

    notify();
}

QtScriptNetworkRunner::~QtScriptNetworkRunner()
{
    delete ui;
}

void QtScriptNetworkRunner::notify()
{
    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::LocalHost, 8000);//Указываем что слушать

    m_timer = new QTimer(this);//Таймер для отслеживания пакетов
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &QtScriptNetworkRunner::slotTimeOut);//Если за 1 сек не пришёл пакет,
    //то считаем, что все пакеты дошли
    connect(m_socket, &QUdpSocket::readyRead, this, [=](){//Получаем входящие данные на сокет
        while(m_socket->hasPendingDatagrams()){//Если есть непрочитанные пакеты
            QByteArray data;
            data.resize(m_socket->pendingDatagramSize());//Делаем размер с пакетом
            QHostAddress sender;
            quint16 port;
            m_socket->readDatagram(data.data(), data.size(), &sender, &port);//Читаем данные в data
            if(data.size() >= 2){
                int indexPackage = (static_cast<unsigned char>(data[0]) << 8) | static_cast<unsigned char>(data[1]);//Получаем индекс из пакета
                data.remove(0,2);//удаляем индекс
                m_packages[indexPackage] = data;
            }
            m_timer->start(1000);
        }
    });
}

void QtScriptNetworkRunner::slotTimeOut()
{
    //читаем отсортированные по индексу пакеты и преобразовываем в текст
    for(const auto& package: m_packages)
        ui->m_scriptField->appendPlainText(QString::fromUtf8(package));//Выводим текст
    m_packages.clear();
}
