#include "result.h"
#include "ui_result.h"
#include "math.h"
#include"QDebug"

extern Rinok GLOBoRinok;
int factorial(int i)
{
  if (i==0) return 1;
  else return i*factorial(i-1);
}

double CountFna(int i){
    double temp=0;
for(int k=0; k<=i ;k++){
        double tA = factorial(i)/(factorial(i-k)*factorial(k));
        double tB = pow(GLOBoRinok.pzv,k)*pow(1-GLOBoRinok.pzv,i-k);
        double tC = std::max(0.0,GLOBoRinok.S0*(1+GLOBoRinok.a)*pow((1+GLOBoRinok.b)/(1+GLOBoRinok.a),k)*pow(1+GLOBoRinok.a,i)-GLOBoRinok.K);
        temp += tA*tB*tC;
    }
return temp;
}
double CountFnb(int i){
    double temp=0;
for(int k=0; k<=i ;k++){
    double tA = factorial(i)/(factorial(i-k)*factorial(k));
    double tB = pow(GLOBoRinok.pzv,k)*pow(1-GLOBoRinok.pzv,i-k);
    double tC = std::max(0.0,GLOBoRinok.S0*(1+GLOBoRinok.b)*pow((1+GLOBoRinok.b)/(1+GLOBoRinok.a),k)*pow(1+GLOBoRinok.a,i)-GLOBoRinok.K);
        temp += tA*tB*tC;
    }
return temp;
}



double CountCn(){
    double Cn=0;

        double temp=0;
        for(int k=0; k<=GLOBoRinok.N ;k++){
            int i = GLOBoRinok.N-k;
                double tA = factorial(GLOBoRinok.N)/(factorial(i)*factorial(k));
                double tB = pow(GLOBoRinok.pzv,k)*pow(1-GLOBoRinok.pzv,i);
                double tC = std::max(0.0,(GLOBoRinok.S0*pow(1+GLOBoRinok.b,k)*pow(1+GLOBoRinok.a,i)-GLOBoRinok.K));
                temp += tA*tB*tC;
            }
       Cn=temp/pow(1+GLOBoRinok.r,1*GLOBoRinok.N);
       return Cn;

}


double Result::CountGamma(int i){
    double gamma;
    double Fna=CountFna(GLOBoRinok.N-i);
    double Fnb=CountFnb(GLOBoRinok.N-i);

    gamma=pow(1+GLOBoRinok.r,-1*(GLOBoRinok.N-i))*((Fnb-Fna)/(GLOBoRinok.S0*(GLOBoRinok.b-GLOBoRinok.a)));
    this->Gamma=gamma;
    return gamma;

}
void Result::CountX(){
    this->X=this->Beta*GLOBoRinok.B0+this->Gamma*GLOBoRinok.S0;
}

double Result::CountBeta(int i){
    double beta;

    beta=(this->X-CountGamma(i)*GLOBoRinok.S0)/GLOBoRinok.B0;
    this->Beta=beta;
    return beta;

}

Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    this->iteration=1;
    this->Cn=CountCn();
    ui->Survived->setText("Day "+QString::number(iteration,'g',9));
    ui->lbl_Cn->setText("Cn = " + QString::number(this->Cn,'g',9));
    this->X=this->Cn;
    ui->lbl_B->setText("B = "+QString::number(GLOBoRinok.B0,'g',9));
    ui->lbl_S->setText("S = "+QString::number(GLOBoRinok.S0,'g',9));
    ui->lbl_gamma->setText("Gamma = "+QString::number(CountGamma(iteration),'g',9));
    ui->lbl_beta->setText("Beta = "+QString::number(CountBeta(iteration),'g',9));

    if(iteration==GLOBoRinok.N+1){
        double f=std::max(0,GLOBoRinok.S0-GLOBoRinok.K);
        ui->lblFinish->setText("f = "+ QString::number(f));
        ui->pbUp->setEnabled(false);
        ui->pbDown->setEnabled(false);
    }
}

Result::~Result()
{
    delete ui;
}

void Result::on_pbUp_clicked()
{
    iteration++;
    GLOBoRinok.ChangeS(GLOBoRinok.b);
    GLOBoRinok.ChangeB();
    CountX();
    if(iteration==GLOBoRinok.N+1){
        double f=std::max(0,GLOBoRinok.S0-GLOBoRinok.K);
        ui->lblFinish->setText("f = "+ QString::number(f));
        ui->pbUp->setEnabled(false);
        ui->pbDown->setEnabled(false);
        ui->lblDept->setText("Долг = "+QString::number(GLOBoRinok.S0*this->Gamma-f));
    }
    ui->Survived->setText("Day "+QString::number(iteration,'g',9));
    ui->lbl_Cn->setText("X = " + QString::number(this->X,'g',9));
    ui->lbl_B->setText("B = "+QString::number(GLOBoRinok.B0,'g',9));
    ui->lbl_S->setText("S = "+QString::number(GLOBoRinok.S0,'g',9));
    ui->lbl_gamma->setText("Gamma = "+QString::number(CountGamma(iteration),'g',9));
    ui->lbl_beta->setText("Beta = "+QString::number(CountBeta(iteration),'g',9));


}

void Result::on_pbDown_clicked()
{
    iteration++;
    GLOBoRinok.ChangeS(GLOBoRinok.a);
    GLOBoRinok.ChangeB();
    CountX();
    if((iteration==GLOBoRinok.N+1)||(CountBeta(iteration)==0)||(CountGamma(iteration)==0)){
        double f=std::max(0,GLOBoRinok.S0-GLOBoRinok.K);
        ui->lblFinish->setText("f = "+ QString::number(f));
        ui->pbUp->setEnabled(false);
        ui->pbDown->setEnabled(false);
        ui->lblDept->setText("Долг = "+QString::number(GLOBoRinok.S0*this->Gamma-f));
    }
    ui->Survived->setText("Day "+QString::number(iteration,'g',9));
    ui->lbl_Cn->setText("X = " + QString::number(this->X,'g',9));
    ui->lbl_B->setText("B = "+QString::number(GLOBoRinok.B0,'g',9));
    ui->lbl_S->setText("S = "+QString::number(GLOBoRinok.S0,'g',9));
    ui->lbl_gamma->setText("Gamma = "+QString::number(CountGamma(iteration),'g',9));
    ui->lbl_beta->setText("Beta = "+QString::number(CountBeta(iteration),'g',9));



}
