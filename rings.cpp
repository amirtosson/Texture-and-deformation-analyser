#include "rings.h"

Rings::Rings(QString fn, float maxen, float minen): BaseClass(fn),eng_max(maxen),eng_min(minen),f_dir(fn)
{

}

void Rings::fillPixels()
{
    QFile f(f_dir);
  QTextStream filen(&f);
     if(f.open(QIODevice::ReadOnly | QIODevice::Text)){

    int num1, num2, num3;
     do {

       filen>>num1>>num2>>num3;
        if((num1!=0||num2!=0)&& (num3<eng_max)&&(num3>eng_min)){
        pixel[num1][num2].counts++;
     pixel[num1][num2].hits_amp.push_back(num3);
 }

    }while(!filen.atEnd());
     f.close();

     }
}
