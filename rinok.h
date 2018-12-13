#ifndef RINOK_H
#define RINOK_H


class Rinok
{
private:

public:
    Rinok();
    int N;
    int S0;
    int SOld;
    int BOld;
    int B0;
    int K;
    double a;
    double b;
    double r;
    double pzv;
    void Count_pzv(){
        this->pzv=double(this->r-this->a)/double(this->b-this->a);
    }
    void ChangeS(double step);
    void ChangeB();
};

#endif // RINOK_H
