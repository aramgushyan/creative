#include "basa.h"
#include "ui_basa.h"
#include"zametki.h"
#include <mainwindow.h>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include<QTextEdit>
basa::basa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basa)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("Таблица");


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open())
    {
    qDebug("open");
    }
    else{
        qDebug("no open");
    }

    rostvlg = new srav(this); // инициализируем и открываем
    connect(this, &basa::signaliz, rostvlg, &srav::prinat); // подключение к окну сравнения для передачи данных и приёма в нём
    connect(rostvlg,&srav::vernut,this,&basa::slotprindb); // обратный коннект

    otprav= new zametki(this); //открытие заметок
    connect(this,&basa::sendSignal, otprav, &zametki::slot);


    quary = new QSqlQuery(db);

    quary->exec("CREATE TABLE Plants(Название TEXT, Полив TEXT, Свет TEXT, Удобрения TEXT, Влажность почвы TEXT, Средний рост TEXT);");

    model = new QSqlTableModel(this, db);

    model->setTable("Plants");

    model->select();

    model->setHeaderData(0, Qt::Horizontal, "Название", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Полив", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Свет", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "Удобрения", Qt::DisplayRole);
    model->setHeaderData(4, Qt::Horizontal, "Влажность почвы", Qt::DisplayRole);
    model->setHeaderData(5, Qt::Horizontal, "Средний рост", Qt::DisplayRole);

    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);



    // для удобного взаимодействия с таблицей
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSortingEnabled(true); // сортировка по столбцам

}

basa::~basa()
{
    db.close(); // при закрытии формы закрывается подключение к базе
    delete ui;
}

void basa::on_pushButton_clicked() // добавление строки
{
    model->insertRow(model->rowCount());
}


void basa::on_pushButton_2_clicked() // удаление строки
{
    model->removeRow(row);
    model->select();
}


void basa::on_tableView_clicked(const QModelIndex &index)
{
    rowData="";
    row = index.row();
    if (hran != 10) {
        if (hran == row){
    }
        else {
             ui->textEdit->clear();
        }
    }
    int id = index.row(); // Получаем номер строки
     hran = id;
        // Получаем данные из каждой ячейки текущей строки
    for (int column = 0; column < model->columnCount(); ++column) {
        QModelIndex cellIndex = index.sibling(row, column); // Получаем индекс для каждой ячейки
        QString cellData = cellIndex.data().toString(); // Получаем данные из текущей ячейки
        if (column == 5) {
            rostiztablisa = cellData; // Получение значения роста из таблицы и сохранение его в переменной
                }
       if(column == 4){
           vlagaistablisa = cellData; // Получение значения влажности почвы из таблицы и сохранение его в переменной
       }
        // Добавляем соответствующий префикс в зависимости от значения столбца
        switch(column) {
            case 0:
                rowData += "   Название: " + cellData + "\n";
                break;
            case 1:
                rowData += "   Полив: " + cellData + "\n";
                break;
            case 2:
                rowData += "   Свет: " + cellData + "\n";
                break;
            case 3:
                rowData += "   Удобрения: " + cellData + "\n";
                break;
            case 4:
                rowData += "   Влажность почвы: " + cellData + "\n";
                break;
            case 5:
                rowData += "   Рост: " + cellData + "\n";
                break;
            default:
                rowData += cellData + "\n";
        }
    }

        qDebug() << id; // Выводим всю информацию из строки в консоль
        qDebug() << "ПЕРЕМЕННАЯ = "<<rostiztablisa;
}



void basa::on_pushButton_4_clicked()
{
    hide();
    MainWindow* fwindow;
    fwindow = new MainWindow;
    fwindow->show();
    this->close();
}



void basa::on_dobavit_clicked()
{

    // Получаем текст из QTextEdit и добавляем к нему строку rowData
    QString text = ui->textEdit->toPlainText();
    text += rowData;

    // Устанавливаем новый текст в QTextEdit
    ui->textEdit->setText(text);

    // Отправляем сигнал со значением текста из QTextEdit
    emit sendSignal(ui->textEdit->toPlainText());

    // Обнуляем переменные text и rowData
    text = "";
    rowData = "";

    // Показываем окно otprav
    otprav->show();
}

void basa::on_detalldata_clicked()
{
    rostvlg->show();
    emit signaliz(rostiztablisa,vlagaistablisa);
}

void basa::slotprindb(QString vernutvivod)
{

    // Получаем текст из QTextEdit и добавляем к нему строку rowData
    QString text = ui->textEdit->toPlainText();
    text += vernutvivod;

    // Устанавливаем новый текст в QTextEdit
    ui->textEdit->setText(text);

    // Обнуляем переменные text и rowData
    text = "";
    vernutvivod = "";
}

