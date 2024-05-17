#ifndef SRAV_H
#define SRAV_H
#include <QDialog>
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include <QDialog>

namespace Ui {
class srav;
}

class srav : public QDialog
{
    Q_OBJECT

public:
explicit srav(QWidget *parent = nullptr);
    ~srav();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_clicked();
    void on_vtrnut_clicked();

    void on_sravnit_clicked();

private:
    Ui::srav *ui;
    QSqlQuery *quary1;
    QString vernutvivod; // строка для хранения вывода и передачи через сигнал в в окно базы

public slots:
    void prinat(QString rostiztablisa,QString vlagaistablisa);// слот для приёма

signals:
    void vernut(QString vernutvivod); // сигнал для отпарвки в окно база

};

#endif // SRAV_H
