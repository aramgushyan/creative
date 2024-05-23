#ifndef GRAFIK_H
#define GRAFIK_H

#include <QDialog>

namespace Ui {
class grafik;
}

class grafik : public QDialog
{
    Q_OBJECT

public:
    explicit grafik(QWidget *parent = nullptr);
    ~grafik();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_close_clicked();

private:
    Ui::grafik *ui;
};

#endif // GRAFIK_H

