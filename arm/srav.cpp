#include "srav.h"
#include "ui_srav.h"
#include "mainwindow.h"
#include"grafik.h"
#include<QSqlTableModel>
#include<QDebug>
#include <QRandomGenerator> // для произвольного значения в ячейке
#include <QFile>
srav::srav(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::srav)
{
ui->setupUi(this);

this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
this->setWindowTitle("Дополнительные данные");


ui->tableWidget->setRowCount(2); // задаём кол-во строк для таблицы
ui->tableWidget->setColumnCount(12); // задаём кол-во столбцов для таблицы

ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Сентябрь"<<"Октябрь"<<"Ноябрь"<<"Декабрь"<<"Январь"<<"Февраль"<<"Март"<<"Апрель"<<"Май"<<"Июнь"<<"Июль"<<"Август"); // названия стоблцов
ui->tableWidget->setVerticalHeaderLabels(QStringList()<<"Рост"<<"Влажность почвы в %");

// заполнение таблицы по умолчанию, при открытии окна
int rost=0;
int vs=0;
int prrost=0;
int infor;
int rs =1;
for(int i=0;i<ui->tableWidget->rowCount();++i) // идёт заполнение строки
{
    for(int j=0;j<ui->tableWidget->columnCount();++j)// идёт заполнение столбцов
    {
        if(i>=1){
            rs = QRandomGenerator::global()->bounded(50,100);} // при заполнении первой строки, следующие значения принимают значения влажность
        else {
            rs += QRandomGenerator::global()->bounded(0,5); // для заполнения роста
        }
        QTableWidgetItem*tbl = new QTableWidgetItem(QString::number(rs)); // заполнение элементов
        ui->tableWidget->setItem(i,j,tbl);

        infor = ui->tableWidget->item(i, j)->text().toInt(); // получение знаечния из ячейки таблицы
        if(i>=1){
            vs += infor;
        }
        else
        {
            rost += infor - prrost; // собираем сюда значния новый рост - старый
            prrost=infor; // сохраняем новый рост
        }
        rs++;
    }
}
vs=vs/12; // среднее значение влажности
rost=rost/12; // среднее значение роста

ui->Rost->setText(QString::number(rost)); // вывод данных в texeLine - рост
ui->Vlag->setText(QString::number(vs)); // вывод данных в texeLine - влажность
}

srav::~srav()
{
    delete ui;
}

void srav::on_pushButton_2_clicked()
{
    int rost=0;
    int vs=0;
    int prrost=0;
    int infor;
    int rs =1;
    for(int i=0;i<ui->tableWidget->rowCount();++i) // идёт заполнение строки
    {
        for(int j=0;j<ui->tableWidget->columnCount();++j)// идёт заполнение столбцов
        {
            if(i>=1){
                rs = QRandomGenerator::global()->bounded(50,100);} // при заполнении первой строки, следующие значения принимают значения влажность
            else {
                rs += QRandomGenerator::global()->bounded(0,5); // для заполнения роста
            }
            QTableWidgetItem*tbl = new QTableWidgetItem(QString::number(rs)); // заполнение элементов
            ui->tableWidget->setItem(i,j,tbl);

            infor = ui->tableWidget->item(i, j)->text().toInt(); // получение знаечния из ячейки таблицы
            if(i>=1){
                vs += infor;
            }
            else
            {
                rost += infor - prrost; // собираем сюда значния новый рост - старый
                prrost=infor; // сохраняем новый рост
            }
            rs++;
            qDebug()<<rost<<" ";
        }
    }
    vs=vs/12; // среднее значение влажности
    rost=rost/12; // среднее значение роста
    qDebug()<<"Средний прирост роста за год = "<<rost<<" ";
    qDebug()<<"Средняя Влажность почвы за год = "<<vs<<" ";

    ui->Rost->setText(QString::number(rost)); // вывод данных в texeLine - рост
    ui->Vlag->setText(QString::number(vs)); // вывод данных в texeLine - влажность

}
void srav::on_pushButton_3_clicked()
{
    QVector<int> vlagnost;  // Объявление массива для хранения значений влажности
    QVector<int> rosttt; // Объявление массива для хранения значений роста

    for(int i = 0; i < ui->tableWidget->rowCount(); ++i) // идем по строкам
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); ++j) // идем по столбцам
        {
            int value = ui->tableWidget->item(i, j)->text().toInt(); // получаем значение из ячейки

            if(i>=1){
                vlagnost.append(value);// Записываем значение в массив
            }
            else
            {
                 rosttt.append(value);// Записываем значение в массив
            }
        }
    }

    //перенос данных для постоения графика
    QFile file("vlag.txt");
    if (file.open(QIODevice::WriteOnly))
    {

        QTextStream writeStream(&file);
        int x = vlagnost.size();
        for (int i=0;i<x;++i){
               writeStream <<QString::number(vlagnost[i])<<endl ;
        }
               file.close();
    }
    QFile file1("rost.txt");
    if (file1.open(QIODevice::WriteOnly))
    {

        QTextStream writeStream(&file1);
        int a = rosttt.size();
        for (int i=0;i<a;++i){
               writeStream <<QString::number(rosttt[i])<< endl ;
        }
               file1.close();
    }
    grafik oknograf;
    oknograf.setModal(true);
    oknograf.exec();

}

void srav::on_pushButton_clicked() // закрытие окна и очистка текстового поля
{
    ui->rezultatsrav->clear();
    this->close();
}

void srav::prinat(QString rostiztablisa,QString vlagaistablisa) // получение сигнала и занесение данных
{
    ui->Optrost->setText(rostiztablisa);
    ui->Optvlg->setText(vlagaistablisa);
}

void srav::on_vtrnut_clicked()
{
   emit vernut(vernutvivod); // Эмитируем сигнал vernut с переданным значением
}


void srav::on_sravnit_clicked() // сравнение значений роста и влажности
{
    // считывание значений из lineEdit
    vernutvivod="";
    QString textoptrost = ui->Optrost->text();
    QString textoptvlg = ui->Optvlg->text();
    QString textrost= ui->Rost->text();
    QString textvlg=ui->Vlag->text();

    // перевод в числовой тип данных для сравнения
    int sravoptrost = textoptrost.toInt();
    int sravoptvlg = textoptvlg.toInt();
    int sravrost = textrost.toInt();
    int sravvlg = textvlg.toInt();

    // сравнение и вывод в textEdit
    if (sravoptvlg<sravvlg){
        vernutvivod+="   \nСредний процент влажности почвы превышает оптимальные показатели.\n";
        if(sravoptrost<sravrost){
            vernutvivod+="   \nОднако, благодаря правильному уходу, ваше растение развивается в хорошем темпе.\n";
        }
        else{
            vernutvivod+="   \nПереизбыток влаги замедлил темп развития вашего растения.\n";
        }
    }
    else{
        if(sravoptvlg == sravvlg)
        {
            vernutvivod+="   \nСредний процент влажности почвы удавлетворяет оптимальным показателям.\n";
            if(sravoptrost<sravrost){
                vernutvivod+="   \nБлагодаря правильному уходу, ваше растение развивается в хорошем темпе.\n";
            }
            else{
                vernutvivod+="   \nОднако недостаточный уход замедлил темп развития вашего растения.\n";
            }
        }
        else {
            vernutvivod+="   \nСредний процент влажности почвы неудовлетворяет оптимальным показателям.\n";
            if(sravoptrost<sravrost){
                vernutvivod+="   \nОднако, благодаря правильному уходу, ваше растение развивается в хорошем темпе.\n";
            }
            else{
                vernutvivod+="   \nНедостаток влаги замедлил темп развития вашего растения, вам следует пересмотреть график полива.\n";
            }
        }
    }
    ui->rezultatsrav->setText(vernutvivod);

}

