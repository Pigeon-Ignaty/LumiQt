#include "QtScriptNetworkRunner.h"
#include <QTimer>
#include <QMessageBox>
QtScriptNetworkRunner::QtScriptNetworkRunner(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // инициализация UI

    //Устанавливаем соотношение 1 к 3
    QTimer::singleShot(0, this, [this]() {
        ui->splitter->setStretchFactor(0, 1);
        ui->splitter->setStretchFactor(1, 3);

        // Принудительно устанавливаем размеры
        int totalWidth = ui->splitter->width();
        if (totalWidth > 100) {
            QList<int> sizes;
            sizes << totalWidth / 4 << (totalWidth * 3) / 4;
            ui->splitter->setSizes(sizes);
        }
    });
    ui->m_scriptField->setReadOnly(true);
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
}

QtScriptNetworkRunner::~QtScriptNetworkRunner()
{
    delete ui;
}

void QtScriptNetworkRunner::notify()
{
    m_socket = new QUdpSocket(this);
    QHostAddress address(m_IP);
    m_socket->bind(address, m_port);//Указываем что слушать

    m_timer = new QTimer(this);//Таймер для отслеживания пакетов
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &QtScriptNetworkRunner::slotTimeOut);//Если за 1 сек не пришёл пакет,
    //то считаем, что все пакеты дошли
    connect(m_socket, &QUdpSocket::readyRead, this, [=](){//Получаем входящие данные на сокет
        if(!m_timer->isActive()){//Если давно не было пакетов, то считаем как новую отправку
            ui->m_scriptField->clear();
            m_packages.clear();
        }
        m_timer->start(1000);

        while(m_socket->hasPendingDatagrams()){//Если есть непрочитанные пакеты
            QByteArray data;
            data.resize(m_socket->pendingDatagramSize());// Устанавливаем размер data равным размеру следующего пакета
            QHostAddress sender;
            quint16 port;
            m_socket->readDatagram(data.data(), data.size(), &sender, &port);//Читаем данные в data
            if(data.size() >= 2){
                int indexPackage = (static_cast<unsigned char>(data[0]) << 8) | static_cast<unsigned char>(data[1]);//Получаем индекс из пакета
                data.remove(0,2);//удаляем индекс
                m_packages[indexPackage] = data;
            }
        }
    });
}

void QtScriptNetworkRunner::slotTimeOut()
{
// Читаем пакеты по индексу и конвертируем их содержимое в текст
    for(const auto& package: m_packages)
        ui->m_scriptField->appendPlainText(QString::fromUtf8(package));//Выводим текст
    m_packages.clear();
}

void QtScriptNetworkRunner::setIP(QString ip)
{
    m_IP = ip;
}

void QtScriptNetworkRunner::setPort(int port)
{
    m_port = port;

}

void QtScriptNetworkRunner::drawFigures(QVector<Figure> figures)
{
    m_scene->clear();//Очищаем сцену
    for(const auto &figure : figures){//Проходимся по списку фигур
        switch (figure.type) {//По типу рисуем фигуру
        case TypeFigure::fillCircle:{
            m_scene->addEllipse(figure.points[0].x(),figure.points[0].y(),figure.radius,figure.radius,QPen(Qt::NoPen), QBrush(figure.color));
            break;
        }
        case TypeFigure::strokeCircle:{
            m_scene->addEllipse(figure.points[0].x(),figure.points[0].y(),figure.radius,figure.radius,QPen(figure.color,2), QBrush(Qt::NoBrush));
            break;
        }
        case TypeFigure::fillTriangle:{
            QPolygonF poly({ figure.points[0], figure.points[1], figure.points[2] });
            m_scene->addPolygon(poly,QPen(Qt::NoPen), QBrush(figure.color));
            break;
        }
        case TypeFigure::strokeTriangle:{
            QPolygonF poly({ figure.points[0], figure.points[1], figure.points[2] });
            m_scene->addPolygon(poly,QPen(figure.color,2), QBrush(Qt::NoBrush));
            break;
        }
        case TypeFigure::fillRectangle:{
            m_scene->addRect(QRectF(figure.points[0],figure.points[1]),QPen(Qt::NoPen), QBrush(figure.color));
            break;
        }
        case TypeFigure::strokeRectangle:{
            m_scene->addRect(QRectF(figure.points[0],figure.points[1]),QPen(figure.color,2), QBrush(Qt::NoBrush));
            break;
        }
        case TypeFigure::line:{
            m_scene->addLine(QLineF(figure.points[0], figure.points[1]),QPen(figure.color,2));
            break;
        }
    }
}
}

void QtScriptNetworkRunner::on_pushButton_clicked()
{
    // Получаем текст и разбиваем на строки
    QString text = ui->m_scriptField->toPlainText();
    QStringList lines = text.split("\n"); // сначала просто разбиваем

    // Убираем строки пустые или состоящие только из пробелов
    QStringList cleanLines;
    for (const QString &line : lines) {
        if (!line.trimmed().isEmpty()) {
            cleanLines.append(line);
        }
    }

    Interpreter inter;
    int error = inter.parseStrings(cleanLines);//Читаем строки с командами

    if(error == 0){// Если нет ошибок, то рисуем фигуры, иначе выводим ошибку
        auto figures = inter.getFigures();
        drawFigures(figures);
    }
    else{
        QMessageBox::warning(this, "Ошибка", QString("Возникла ошибка выполнения скрипта на строчке %1").arg(error));
    }
}


void QtScriptNetworkRunner::on_pushButton_2_clicked()
{
    ui->m_scriptField->clear();
}
