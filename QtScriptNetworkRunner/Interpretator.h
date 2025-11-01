#pragma once

#include <QVector>
#include <QColor>
#include <QPointF>

enum class TypeFigure{ //Типы объектов для рисования
    fillCircle, strokeCircle, fillTriangle,strokeTriangle, fillRectangle, strokeRectangle, line
};
struct Figure{//структура для отрисовки
    TypeFigure type = TypeFigure::fillCircle;//Тип фигуры
    QVector<QPointF> points;//Точки построения
    QColor color = QColor(Qt::black);//Цвет
    double radius = 0;//Радиус если есть
};


class Interpretator
{
public:
    Interpretator();
    bool parseString(QString &string);//Читаем строку
    int parseStrings(QStringList strings);//Читаем строки
    QVector<Figure> getFigures();//Метод для получения список фигур
private:
    QVector<Figure> m_figures;
};
