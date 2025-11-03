# QtScriptNetwork

Два приложения на Qt: редактор скриптов и исполнитель скриптов, взаимодействующие между собой через протокол UDP. 
Редактор скриптов позволяет писать строки кода на простом скриптовом языке для рисования графических фигур, таких как линии, круги, прямоугольники и треугольники. В редакторе предусмотрена возможность открытия и сохранения скриптов в локальные файлы. После написания скрипта редактор отправляет команды на исполнение через UDP в приложение-исполнитель.
Исполнитель скриптов принимает скрипт от редактора, разбирает команды и рисует соответствующие фигуры в графическом окне. Он поддерживает как заполненные фигуры, так и контурные, управляет цветом, размерами и координатами объектов.

---

# Структура проекта

- **ConnectionDialog** — окно для ввода IP и порта сервера. Позволяет пользователю указать адрес и порт для подключения, проверяет корректность введённых данных.  
- **QtScriptNetworkEditor** — главное окно редактора скриптов. Позволяет создавать, открывать, редактировать и сохранять скрипты, а также отправлять их по UDP на указанный IP и порт.  
- **Interpreter** — класс для парсинга скриптов. Преобразует строки команд в объекты фигур (круги, треугольники, прямоугольники, линии) и хранит список построенных фигур.  
- **QtScriptNetworkRunner** — главное окно приёмника скриптов. Получает UDP-пакеты, собирает их в текст, отображает скрипт и визуализирует фигуры на сцене.

---

# Команды скриптов

## Круги
- `fillCircle X Y R COLOR` — заполненный круг с центром `(X,Y)`, радиусом `R` и цветом заливки `COLOR`.  
- `strokeCircle X Y R COLOR` — контур круга с центром `(X,Y)`, радиусом `R` и цветом линии `COLOR`.  

## Треугольники
- `fillTriangle X1 Y1 X2 Y2 X3 Y3 COLOR` — заполненный треугольник с вершинами `(X1,Y1)`, `(X2,Y2)`, `(X3,Y3)` и цветом заливки `COLOR`.  
- `strokeTriangle X1 Y1 X2 Y2 X3 Y3 COLOR` — контур треугольника с теми же параметрами, цвет линии `COLOR`.  

## Прямоугольники
- `fillRectangle X1 Y1 X2 Y2 COLOR` — заполненный прямоугольник с углами `(X1,Y1)` и `(X2,Y2)`, цвет заливки `COLOR`.  
- `strokeRectangle X1 Y1 X2 Y2 COLOR` — контур прямоугольника с теми же параметрами, цвет линии `COLOR`.  

## Линии
- `line X1 Y1 X2 Y2 COLOR` — линия от точки `(X1,Y1)` до `(X2,Y2)` с цветом `COLOR`.  

## Поддерживаемые цвета:
black, white, red, green, blue, yellow, cyan, magenta, gray, orange, purple, darkGray, lightGray, darkRed, darkGreen, darkBlue, darkCyan, darkMagenta, darkYellow, darkOrange, darkPurple, lightRed, lightGreen, lightBlue, lightCyan, lightMagenta, lightYellow


## Пример скрипта
```text
# Круги
fillCircle 100 100 50 blue
strokeCircle 250 100 40 cyan

# Треугольники
fillTriangle 50 250 150 250 100 350 red
strokeTriangle 200 250 300 250 250 350 green

# Прямоугольники
fillRectangle 350 50 450 150 yellow
strokeRectangle 500 50 600 150 blue

# Линии
line 10 400 100 400 black
```
# Сборка, деплой и запуск Qt-проектов на Windows
Эта инструкция описывает процесс сборки, деплоя и запуска проектов **QtScriptNetworkEditor** и **QtScriptNetworkRunner** с использованием **Qt 5.15.2** и **MSVC2019 64-bit**.

---

## Требования

- **Qt 5.15.2** (MSVC2019 64-bit)  
- **Visual Studio 2019** (или другой MSVC 64-bit компилятор)  
- **CMake 3.16**

---

## Сборка проекта

### Подготовка среды сборки

1. Откройте главный `CMakeLists.txt` в папке проекта **LumiQt** через Qt Creator.  
2. Выберите конфигурацию **Release** и соберите оба проекта:
   - `QtScriptNetworkEditor`  
   - `QtScriptNetworkRunner`  

Исполняемые файлы будут созданы в папках `build-.../Release`.

---

## Деплой приложений с помощью `windeployqt`

### Деплой QtScriptNetworkEditor
```bat
C:\Path\To\Qt\bin\windeployqt.exe ^
    --dir C:\Path\To\Deploy\QtScriptNetworkEditor ^
    C:\Path\To\Build\Release\QtScriptNetworkEditor\QtScriptNetworkEditor.exe

# Копирование самого .exe в папку деплоя
copy /Y C:\Path\To\Build\Release\QtScriptNetworkEditor\QtScriptNetworkEditor.exe ^
    C:\Path\To\Deploy\QtScriptNetworkEditor\
```

### Деплой QtScriptNetworkRunner
```bat
C:\Path\To\Qt\bin\windeployqt.exe ^
    --dir C:\Path\To\Deploy\QtScriptNetworkRunner ^
    C:\Path\To\Build\Release\QtScriptNetworkRunner\QtScriptNetworkRunner.exe

# Копирование самого .exe в папку деплоя
copy /Y C:\Path\To\Build\Release\QtScriptNetworkRunner\QtScriptNetworkRunner.exe ^
    C:\Path\To\Deploy\QtScriptNetworkRunner\
```
## Настройка запуска (Editor ↔ Runner)

### Работа на одной машине
Можно использовать IP и порт по умолчанию для Editor и Runner.

### Работа на двух машинах
1. На машине с **Runner** выполните команду:
```bat
ipconfig
```
Используйте IPv4-адрес машины Runner в обоих приложениях.

## Пошаговый запуск
### Машина 1 — Editor
1. Запустите `QtScriptNetworkEditor.exe`.
2. Введите IP и порт Runner (или оставьте по умолчанию).
3. Нажмите **Сохранить**.
4. Напишите скрипт и нажмите **Отправить**.
5. При необходимости можно **сохранять скрипт в файл** и загружать его из файла.

### Машина 2 — Runner
1. Запустите `QtScriptNetworkRunner.exe`.
2. Введите текущий IP Editor и порт.
3. Нажмите **Сохранить**.
4. Скрипт, присланный с Editor, отобразится в текстовом виде.
5. Пользователь может **стереть скрипт** или **запустить его**.

### Ошибки при передаче скрипта

Если скрипт не доходит до машины **Runner**, выполните следующие действия:

1. С машины **Editor** проверьте соединение с машиной **Runner** с помощью команды `ping`:

```bat
ping <IP_адрес_машины_Runner>
```
Если пинг не проходит, временно отключите брендмауэр Windows на обеих машинах и повторите проверку соединения.
