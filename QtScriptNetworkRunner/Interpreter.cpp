#include "Interpreter.h"

Interpreter::Interpreter()
{

}

bool Interpreter::parseString(QString &comm)
{
    Figure figure;
    QStringList commands = comm.split(" "); //Список слов
    int size = commands.size();

    if(size <=0)
        return false;

    //Для залитого или пустого круга
    if(commands[0] == "fillCircle" || commands[0] == "strokeCircle"){
        if(size != 5)//Если не 5 параметров, выходим
            return false;

        //Заполняем тип фигуры
        if(commands[0] == "fillCircle")
            figure.type = TypeFigure::fillCircle;
        else if(commands[0] == "strokeCircle")
            figure.type = TypeFigure::strokeCircle;

        bool okX;
        bool okY;
        bool okR;
        //Пытаемся привести int в безнаковому числу
        quint16 x = commands[1].toUShort(&okX);
        quint16 y = commands[2].toUShort(&okY);
        quint16 r = commands[3].toUShort(&okR);

        //Если из параметров хотя бы одна не цифра, то ошибка
        if(!okX || !okY || !okR)
            return false;
        //Если успех, кладём все точки
        figure.points.append(QPointF(x,y));
        figure.radius = r;//радиус

        QColor c(commands[4]);//Если цвет корректен, то также кладём
        if(!c.isValid())
            return false;

        figure.color = c;
    }
    else if(commands[0] == "fillTriangle" || commands[0] == "strokeTriangle"){
        if(size != 8)
            return false;

        if(commands[0] == "fillTriangle")
            figure.type = TypeFigure::fillTriangle;
        else if(commands[0] == "strokeTriangle")
            figure.type = TypeFigure::strokeTriangle;
        bool okX1;
        bool okY1;
        bool okX2;
        bool okY2;
        bool okX3;
        bool okY3;
        quint16 x1 = commands[1].toUShort(&okX1);
        quint16 y1 = commands[2].toUShort(&okY1);
        quint16 x2 = commands[3].toUShort(&okX2);
        quint16 y2 = commands[4].toUShort(&okY2);
        quint16 x3 = commands[5].toUShort(&okX3);
        quint16 y3 = commands[6].toUShort(&okY3);
        if(!okX1 || !okY1 || !okX2 || !okY2 || !okX3 || !okY3)
            return false;

        figure.points.append(QPointF(x1,y1));
        figure.points.append(QPointF(x2,y2));
        figure.points.append(QPointF(x3,y3));

        QColor c(commands[7]);
        if(!c.isValid())
            return false;

        figure.color = c;
    }
    else if(commands[0] == "fillRectangle" || commands[0] == "strokeRectangle"){
        if(size != 6)
            return false;

        if(commands[0] == "fillRectangle")
            figure.type = TypeFigure::fillRectangle;
        else if(commands[0] == "strokeRectangle")
            figure.type = TypeFigure::strokeRectangle;

        bool okX1;
        bool okY1;
        bool okX2;
        bool okY2;


        quint16 x1 = commands[1].toUShort(&okX1);
        quint16 y1 = commands[2].toUShort(&okY1);
        quint16 x2 = commands[3].toUShort(&okX2);
        quint16 y2 = commands[4].toUShort(&okY2);


        if(!okX1 || !okY1 || !okX2 || !okY2)
            return false;

        figure.points.append(QPointF(x1,y1));
        figure.points.append(QPointF(x2,y2));

        QColor c(commands[5]);
        if(!c.isValid())
            return false;

        figure.color = c;
    }
    else if(commands[0] == "line"){
        if(size != 6)
            return false;

        figure.type = TypeFigure::line;

        bool okX1;
        bool okY1;
        bool okX2;
        bool okY2;

        quint16 x1 = commands[1].toUShort(&okX1);
        quint16 y1 = commands[2].toUShort(&okY1);
        quint16 x2 = commands[3].toUShort(&okX2);
        quint16 y2 = commands[4].toUShort(&okY2);

        if(!okX1 || !okY1 || !okX2 || !okY2 )
            return false;

        figure.points.append(QPointF(x1,y1));
        figure.points.append(QPointF(x2,y2));

        QColor c(commands[5]);
        if(!c.isValid())
            return false;

        figure.color = c;
    }
    else{//Если не вошли ни в какое условие - значит команда некорректна
        return false;
    }
    m_figures.push_back(figure);
    return true;
}

int Interpreter::parseStrings(QStringList strings)
{
    //В цикле парсим каждую строку и команду
    int counter = 0;
    for(auto &string : strings){
        counter++;
        bool isPainted = parseString(string);
        if(!isPainted){ //Если строка некорректная, то вернём номер
            return counter;
        }
    }
    return 0;//Иначе вернём 0 в случае успеха
}

QVector<Figure> Interpreter::getFigures()
{
    return m_figures;
}
