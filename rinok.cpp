#include "rinok.h"

Rinok::Rinok()
{

}
void Rinok::ChangeS(double step){
    SOld=S0;
    S0=S0*(1+step);
}
void Rinok::ChangeB(){
    BOld=B0;
    B0=B0*(1+r);
}
