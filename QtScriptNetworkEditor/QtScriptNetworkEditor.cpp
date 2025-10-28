#include "QtScriptNetworkEditor.h"

QtScriptNetworkEditor::QtScriptNetworkEditor(QWidget *parent): QMainWindow(parent)
{
    setUI();
}

QtScriptNetworkEditor::~QtScriptNetworkEditor()
{

}

void QtScriptNetworkEditor::setUI()
{
    resize(1280, 720);
    setWindowTitle("Редактор скриптов");

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
    m_openButton->setMinimumWidth(100);
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

    //Установка центрального виджета
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    centralLayout->addWidget(m_splitter);
    setCentralWidget(centralWidget);
}

void QtScriptNetworkEditor::slotLoadScripts()
{

}

void QtScriptNetworkEditor::slotSaveScripts()
{

}

void QtScriptNetworkEditor::slotSendScripts()
{

}
