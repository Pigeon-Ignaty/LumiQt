#include "QtScriptNetworkEditor.h"
#include <QCoreApplication>
#include <QMessageBox>
#include <QTextStream>
#include <QTimer>
QtScriptNetworkEditor::QtScriptNetworkEditor(QWidget *parent): QMainWindow(parent)
{
    setUI();
    m_socket = new QUdpSocket(this);

}

QtScriptNetworkEditor::~QtScriptNetworkEditor()
{

}

void QtScriptNetworkEditor::setIP(QString ip)
{
    m_IP = ip;
}

void QtScriptNetworkEditor::setPort(int port)
{
    m_port = port;
}

void QtScriptNetworkEditor::setUI()
{
    resize(1280, 720);
    setWindowTitle("Редактор скриптов");
    setWindowIcon(QIcon(":/editorLogo.png"));
    //Шрифт
    QFont font;
    font.setPointSize(12);

    //Инициализация виджетов
    m_scriptEdit = new QPlainTextEdit(this);
    m_scriptEdit->setFont(font);
    m_scriptEdit->setMinimumWidth(300);

    m_buttonsWidget = new QWidget(this);
    m_buttonsLayout = new QVBoxLayout(m_buttonsWidget);

    //Кнопки
    m_openButton = new QPushButton("Открыть скрипт", this);
    m_openButton->setFont(font);
    m_openButton->setMinimumWidth(300);
    m_openButton->setMinimumHeight(50);

    m_saveButton = new QPushButton("Сохранить скрипт", this);
    m_saveButton->setFont(font);
    m_saveButton->setMinimumWidth(100);
    m_saveButton->setMinimumHeight(50);

    m_sendButton = new QPushButton("Отправить скрипт", this);
    m_sendButton->setFont(font);
    m_sendButton->setMinimumWidth(100);
    m_sendButton->setMinimumHeight(50);

    //Подключение слотов
    connect(m_openButton,&QPushButton::clicked, this,&QtScriptNetworkEditor::slotLoadScripts);
    connect(m_saveButton,&QPushButton::clicked, this,&QtScriptNetworkEditor::slotSaveScripts);
    connect(m_sendButton,&QPushButton::clicked, this,&QtScriptNetworkEditor::slotSendScripts);

    //Добавление кнопок в layout
    m_buttonsLayout->addWidget(m_openButton);
    m_buttonsLayout->addWidget(m_saveButton);
    m_buttonsLayout->addWidget(m_sendButton);
    m_buttonsLayout->addStretch();

    //Инициализация сплиттера
    m_splitter = new QSplitter(this);
    m_splitter->addWidget(m_buttonsWidget);
    m_splitter->addWidget(m_scriptEdit);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);
    m_splitter->setSizes({1, 3});
    //Устанавливаем соотношение 1 к 3
    QTimer::singleShot(0, this, [this]() {
        m_splitter->setStretchFactor(0, 1);
        m_splitter->setStretchFactor(1, 3);

        // Принудительно устанавливаем размеры
        int totalWidth = m_splitter->width();
        if (totalWidth > 100) {
            QList<int> sizes;
            sizes << totalWidth / 4 << (totalWidth * 3) / 4;
            m_splitter->setSizes(sizes);
        }
    });
    //Установка центрального виджета
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    centralLayout->addWidget(m_splitter);
    setCentralWidget(centralWidget);
}

void QtScriptNetworkEditor::slotLoadScripts()
{
    //Получаем путь до файла
    QString pathFile = QFileDialog::getOpenFileName(this,"Выберите .qs файл","Z:\\VS\\LumiQt","Qt Script файлы (*.qs)");

    if(pathFile.isEmpty())//Проверка на пустой файл
        return;
    //Если файл не открыт, то выводим ошибку
    QFile file(pathFile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл;\n" + pathFile);
        return;
    }
    //Читаем весь файл и записываем в поле скрипта
    QTextStream input(&file);
    QString strings = input.readAll();
    m_scriptEdit->setPlainText(strings);

    file.close();
}

void QtScriptNetworkEditor::slotSaveScripts()
{
    //Сохраняем файл
    QString savePath = QFileDialog::getSaveFileName(this,"Сохранить как","Z:\\VS\\LumiQt\\Скрипт.qs","Qt Script файлы (*.qs)");

    if(savePath.isEmpty())
        return;

    QFile file(savePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
        return;
    }
    //Записываем текст в файл
    QTextStream output(&file);
    output << m_scriptEdit->toPlainText();
    file.close();
}

void QtScriptNetworkEditor::slotSendScripts()
{
    const int chunkSize = 1022;//Размер одного пакета без индекса

    QString text = m_scriptEdit->toPlainText();
    QByteArray allData = text.toUtf8();
    QMap<int, QByteArray> chunks;
    int sizeData = allData.size();//Размер данных
    int offset = 0;
    int index = 0;
    //Проходимя по allData и делим на пакеты по 1022 байта и записываем в qmap
    while (offset < sizeData) {
        int size = std::min(chunkSize, sizeData - offset);
        chunks[index++] = allData.mid(offset, size);
        offset += size;
    }
    //Вначало каждого пакета вставляем номер пакета
    for(int i = 0; i < chunks.size(); i++){
        QByteArray &package = chunks[i];
        quint16 index = static_cast<quint16>(i);

        package.prepend(static_cast<char>((index >> 8) & 0xFF));
        package.prepend(static_cast<char>(index & 0xFF));
    }
    QHostAddress address(m_IP);

    //отправляем пакеты по очереди
    for(auto& chunk : chunks){
        qint64 sent = m_socket->writeDatagram(chunk, address, m_port);

        if (sent == -1)
            qWarning() << "Ошибка отправки:" << m_socket->errorString();
    }
}
