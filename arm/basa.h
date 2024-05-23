#ifndef BASA_H
#define BASA_H
#include "mainwindow.h"
#include <QDialog>
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QTextEdit>
#include <mainwindow.h>
#include<zametki.h>
#include<srav.h>
namespace Ui {
class basa;
}

class basa : public QDialog
{
    Q_OBJECT

public:
    explicit basa(QWidget *parent = nullptr);
    ~basa();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_dobavit_clicked();

    void on_detalldata_clicked();

private:
    Ui::basa *ui;
    QSqlDatabase db; // переменная для базы данных
    QSqlQuery *quary;
    QTextEdit*text; // текст
    QSqlTableModel *model; // для таблицы
    QString s1,s2,s3,s4; // файл
    QString rowData; // Строка для хранения информации из всей строки
    QString rostiztablisa; // Переменная для хранения роста из таблицы бд
    QString vlagaistablisa; // Переменная для хранения влажности почвы из таблицы бд
    int row; // номер удаляемой строки
    zametki*otprav; // для отправки сигнала в заметки
    int hran = 10;

    srav *rostvlg; // создаём объект для дальнейшего взаимодействия с окном

signals:
    void sendSignal(QString a);
    void signaliz(QString rostiztablisa, QString vlagaistablisa); // сигнал для отправки данных в сравнение

public slots:
    void slotprindb(QString vernutvivod); // слот для приёма данных
};

#endif // BASA_H
