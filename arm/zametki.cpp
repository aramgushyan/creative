#include "zametki.h"
#include "ui_zametki.h"
#include <mainwindow.h>
#include <QDebug>
#include <QSettings>


zametki::zametki(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zametki)

{
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfcodec);

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("Заметки");


    QFile file("fila.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        savetext = file.readAll();
        file.close();
    }
     ui->textEdit->setText(savetext);
}

zametki::~zametki()
{
    delete ui;
}

void zametki::on_pushButton_clicked() // переход в главное меню
{
    hide();
    MainWindow* fwindow;
    fwindow = new MainWindow;
    fwindow->show();
    this->close();
}

void zametki::on_pushButton_2_clicked() // запись в файл
{
   savetext=ui->textEdit->toPlainText();
   QFile file("fila.txt");
   if (file.open(QIODevice::WriteOnly))
   {
       qDebug() << "File is open";
       QTextStream writeStream(&file);
              writeStream <<savetext ;
              file.close();
   }
}


void zametki::on_pushButton_3_clicked() // сохранение и возможность выбора места для сохранения
{
    savetext=ui->textEdit->toPlainText();
    QFile file("otchet.txt");
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
        }
    }
    if (file.open(QIODevice::WriteOnly))
    {
        qDebug() << "File is open";
        QTextStream writeStream(&file);
               writeStream <<savetext ;
               file.close();
    }
}

void zametki::slot(QString a) // получение сигнала и перенос его в текстовое поле
{
    ui->textEdit->setText(a);

}

void zametki::on_close_clicked() // закрыть
{
    this->close();
}

