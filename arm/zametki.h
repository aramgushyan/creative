#ifndef ZAMETKI_H
#define ZAMETKI_H

#include <QDialog>
#include<QDebug>
#include <mainwindow.h>
#include <QtWidgets>
#include<QSqlTableModel>
namespace Ui {
class zametki;
}

class zametki : public QDialog
{
    Q_OBJECT

public:
    explicit zametki(QWidget *parent = nullptr);
    ~zametki();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_close_clicked();

private:
    Ui::zametki *ui;
    QSqlDatabase db2; // вторая база данных
    QString savetext; // для сохранения текста

public slots:
    void slot(QString a); // для получения сигнала
};

#endif // ZAMETKI_H
