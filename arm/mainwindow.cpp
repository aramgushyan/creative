#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"basa.h"
#include "zametki.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Меню");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() // открытие рабочего окна
{
    hide();
    basa window;
    window.setModal(true);
    window.exec();
}




void MainWindow::on_pushButton_3_clicked() // открытие рабочего окна
{
    hide();
    zametki window;
    window.setModal(true);
    window.exec();
}

