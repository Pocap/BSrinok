#ifndef RESULT_H
#define RESULT_H

#include <QWidget>
#include "rinok.h"

namespace Ui {
class Result;
}

class Result : public QWidget
{
    Q_OBJECT

public:
    Result(QWidget *parent = 0);
    ~Result();
    Rinok oRinok;
    double Cn;
    double CountBeta(int i);
    int iteration;
    double X;
    void CountX();
    double CountGamma(int i);
private slots:
    void on_pbUp_clicked();

    void on_pbDown_clicked();

private:
    Ui::Result *ui;
    double Beta;
    double Gamma;
};

#endif // RESULT_H
