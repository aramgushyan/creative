#include "grafik.h"
#include "ui_grafik.h"
#include<QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QGraphicsTextItem>//Подключить!!!
grafik::grafik(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grafik)
{
   ui->setupUi(this);

   this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
   this->setWindowTitle("График");

}

grafik::~grafik()
{
    delete ui;
}

void grafik::on_pushButton_2_clicked()
{
    // построение графика
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setPlainText("График Влажности почвы в %.");
    text->setFont(QFont("Arial", 12));
    text->setPos(120, 190); // Установите координаты x и y, где хотите разместить текст
    scene->addItem(text);

    QGraphicsView *view = new QGraphicsView(scene);
       QVector<int> vlaga;
    QFile file("vlag.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream writeStream(&file);
        while (!file.atEnd())
        {
                QString e =file.readLine() ;
                vlaga.append(e.toInt());
        }
               file.close();
    }
    view->setSceneRect(0, 0, 500, 200); // устанавливаем размер сцены

    QPen pen(Qt::black);
    pen.setWidth(2);
    scene->addLine(0, 180, 500, 180, pen); // горизонтальная линия (x)
    scene->addLine(0, 0, 0, 180, pen); // вертикальная линия (y)

   QPen xxx(Qt::red); // для отрисовки рисок на линии x
   xxx.setWidth(3);

   QPen yyy(Qt::red); // для отрисовки рисок на линии y
   yyy.setWidth(3);

   QPen lin(Qt::green); // для отрисовки графика
   lin.setWidth(2);


   int x = 0; // Начальная координата X
   int y0 = 180; // Начальная координата Y для первого значения
   int z = 180;

   for (int j = 0; j <= 10; ++j) {
       scene->addLine(-5, z, 5, z, yyy); // риски на линии y

       // Добавление цифры от 0 до 10 рядом с каждой риской y
       QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(j*10));
       text->setPos(-30, z - 5); // Позиция цифры рядом с риской
       // Настройка шрифта цифры
       QFont font = text->font();
       font.setPointSize(10);
       text->setFont(font);

       z = z - 18;
   }

   for (int i = 0; i < vlaga.size(); i++) {
       int y = 180 - vlaga[i]-30; // Рассчитываем координату Y для текущего значения
       scene->addLine(x, y0, x + 40, y, lin); // Добавляем отрезок на сцену

       scene->addLine(x, 185, x, 175, xxx); // риски на линии x
       x += 40; // Увеличиваем X для следующего значения
       y0 = y; // Запоминаем координату Y для следующей линии

       if(i==11)
       {
           y = 180 - vlaga[i];
           x += 0; // Увеличиваем X для следующего значения
           scene->addLine(x, 185, x, 175, xxx); // риски на линии x


       }
   }

   ui->graphicsView->setScene(scene);
}


void grafik::on_pushButton_clicked()
{
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setPlainText("График Роста растения в см.");
    text->setFont(QFont("Arial", 12));
    text->setPos(-10, 190); // Установите координаты x и y, где хотите разместить текст
    scene->addItem(text);

    // передача массива из одного окна в другое, для построения графика, через файл
    QGraphicsView *view = new QGraphicsView(scene);
    QVector<int> rost; // массив
    QFile file("rost.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream writeStream(&file);
        while (!file.atEnd())
        {
                QString e =file.readLine() ;
                rost.append(e.toInt());
        }
               file.close();
    }

    view->setSceneRect(0, 0, 500, 200); // устанавливаем размер сцены

    // настройка линий для отрисовки рисок x и y
    QPen xxx(Qt::red); // x
    xxx.setWidth(3);

    QPen yyy(Qt::red); // y
    yyy.setWidth(3);

    QPen lin(Qt::green); // настройка толщины линии графика
    lin.setWidth(2);

    QPen pen(Qt::black); // настройка линии осей координат
    pen.setWidth(2);
    scene->addLine(0, 180, 180, 180, pen); // горизонтальная линия (x)
    scene->addLine(0, 0, 0, 180, pen); // вертикальная линия (y)

    int x = 0; // Начальная координата X
    int y0 = 180; // Начальная координата Y для первого значения

    int z = 180;
    for (int j = 0; j <= 10; ++j) {
        scene->addLine(-5, z, 5, z, yyy); // риски на линии y

        // Добавление цифры от 0 до 10 рядом с каждой риской y
        QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(j*10)); // 10 , 20 , 30 ... 100
        text->setPos(-30, z - 5); // Позиция цифры рядом с риской
        QFont font = text->font();// Настройка шрифта цифры
        font.setPointSize(10);
        text->setFont(font);

        z = z - 18;
    }
    for (int i = 0; i < rost.size(); i++) {
        int y = 180 - rost[i]; // Рассчитываем координату Y для текущего значения

        scene->addLine(x, y0, x + 15, y, lin); // Добавляем отрезок на сцену
        scene->addLine(x, 185, x, 175, xxx); // риски на линии x

        x += 15; // Увеличиваем X для следующего значения
        y0 = y; // Запоминаем координату Y для следующей линии

        if(i==11)
        {
            y = 180 - rost[i];
            x += 0; // Увеличиваем X для следующего значения
            scene->addLine(x, 185, x, 175, xxx); // риски на линии x


        }
    }
    ui->graphicsView->setScene(scene);
}

void grafik::on_close_clicked()
{
    this->close();
}

