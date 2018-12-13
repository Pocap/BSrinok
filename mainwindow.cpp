#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rinok.h"
#include "QString"
#include "result.h"
Rinok GLOBoRinok;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

   GLOBoRinok.N=ui->leN->text().toInt();
   GLOBoRinok.S0=ui->leS0->text().toInt();
   GLOBoRinok.B0=ui->leB0->text().toInt();
   GLOBoRinok.K=ui->leK->text().toInt();
   GLOBoRinok.a=ui->le_a->text().toDouble();
   GLOBoRinok.b=ui->le_b->text().toDouble();
   GLOBoRinok.r=ui->le_r->text().toDouble();
   GLOBoRinok.Count_pzv();

   Result *res = new Result;
   res->show();
}
