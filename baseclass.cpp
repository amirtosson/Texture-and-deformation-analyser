#include "baseclass.h"
#include<bits/stdc++.h>

BaseClass::BaseClass(QString fn):f_dir(fn)
{
prog =new QProgressDialog();

}
BaseClass:: ~BaseClass(){
    delete prog;
}
void BaseClass::fillPixels()
{


    QFile f(f_dir);
  QTextStream filen(&f);
     if(f.open(QIODevice::ReadOnly | QIODevice::Text)){

int count=0;
    int num1, num2, num3;
   // prog->setWindowTitle("nanana");

     do {
//prog->show();
       filen>>num1>>num2>>num3;
      count++;
        if(num1!=0||num2!=0){
        pixel[num1][num2].counts++;
     pixel[num1][num2].hits_amp.push_back(num3);
     if(pixel[num1][num2].hits_amp.size()>2){
       pixel[num1][num2].eng_mode=*std::max_element(pixel[num1][num2].hits_amp.begin(),pixel[num1][num2].hits_amp.end());
     }
    else {pixel[num1][num2].eng_mode=0;}
 }

    }while(!filen.atEnd());
   // prog->close();
     f.close();
     QMessageBox msgBox;
     msgBox.setWindowTitle("Information");
     msgBox.setText(QString("You have %1 events with average %2 event per pixel").arg(count).arg((count/(384*384))));
     msgBox.exec();

     }












}


void BaseClass::getSize(VP *p)
{
    int x_size,y_size,p2,p1;
  std::sort(p->begin(),p->begin()+4,[](const std::pair<int,int> &a,const std::pair<int,int> &b){
                return a.first<b.first;
            });
  VP::iterator it=p->begin();
  VP::iterator it2=p->begin()+3;
  p1=(*it2).first;
  p2=(*it).first;
  x_size=p1-p2;
  it=p->begin()+4;
  *it=std::make_pair(p1,p2);

  std::sort(p->begin(),p->begin()+4,[](const std::pair<int,int> &a,const std::pair<int,int> &b){
                return a.second<b.second;
            });
  it=p->begin();
  it2=p->begin()+3;
  p1=(*it2).second;
  p2=(*it).second;
  y_size=p1-p2;
  it=p->begin()+5;
  *it=std::make_pair(p1,p2);
  it=p->begin()+6;
  *it=std::make_pair(x_size,y_size);

}
