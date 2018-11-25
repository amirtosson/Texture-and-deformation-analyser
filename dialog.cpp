#include "dialog.h"
#include "ui_dialog.h"
#include <stdlib.h>





Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->img, SIGNAL(mouseMove(QMouseEvent*)) ,SLOT(Mouse_current_pos(QMouseEvent *)));
    connect(ui->img_sub, SIGNAL(mouseMove(QMouseEvent*)) ,SLOT(Mouse_current_pos_sub(QMouseEvent *)));
    connect(ui->img, SIGNAL(mousePress(QMouseEvent*)),SLOT(Mouse_Pressed(QMouseEvent *))    );
    connect(ui->img_sub, SIGNAL(mousePress(QMouseEvent*)),SLOT(Mouse_Pressed_sub(QMouseEvent *))    );
    ui->img->axisRect()->setupFullAxesBox(false);
    ui->img->xAxis->setVisible(false);
    ui->img->yAxis->setVisible(false);
    ui->img_sub->xAxis->setVisible(false);
    ui->img_sub->yAxis->setVisible(false);
    ui->img->axisRect()->setAutoMargins(QCP::msNone);
    ui->img->axisRect()->setMargins(QMargins(0,0,0,0));
    colorMap = new QCPColorMap(ui->img->xAxis, ui->img->yAxis);
    colorsub_map=new QCPColorMap(ui->img_sub->xAxis,ui->img_sub->yAxis);

    line = new QCPItemLine(ui->img_sub);
    pts.reserve(7);



}

Dialog::~Dialog()
{
    delete ui;
    delete colorMap;

    delete colorsub_map;
    delete line;
    delete _base_class;
    delete _ring_class;
    pts.clear();
}


inline float lineMM(int pt[4]){
    return static_cast<float>(pt[1]-pt[3])/(pt[0]-pt[2]);
}
inline float lineBB(int pt[4],float ml){
        return pt[1]-(ml*pt[0]);
}
void Dialog::Mouse_current_pos(QMouseEvent *evv)
{
    QPoint pp=evv->pos();
    ui->mouse->setText(QString("X=%1 ,Y=%2").arg(pp.x()).arg(384-pp.y()));}

void Dialog::Mouse_current_pos_sub(QMouseEvent *evv)
{//ui->img_sub->xAxis->pixelToCoord(pp.x())
    QPoint pp=evv->pos();
    ui->mouse_2->setText(QString("X=%1 ,Y=%2").arg(ui->img_sub->xAxis->pixelToCoord(pp.x())).arg(ui->img_sub->yAxis->pixelToCoord(pp.y())));
}

void Dialog::Mouse_Pressed(QMouseEvent *evv2)
{
int point,px,py;
QPoint po=evv2->pos();
px=po.x();
py=384-po.y();


if(ui->r1->isChecked()){point=1;}
else if(ui->r2->isChecked()){point=2;}
else if(ui->r3->isChecked()){point=3;}
else if(ui->r4->isChecked()){point=4;}
else{point=0;}

switch (point) {
       case 1:ui->X1->setText(QString::number(px));
              ui->Y1->setText(QString::number(py));
              pts[0]=std::make_pair(px,py);
              ui->r2->setChecked(true);
                break;
       case 2:ui->X2->setText(QString::number(px));
              ui->Y2->setText(QString::number(py));
              pts[1]=std::make_pair(px,py);
              ui->r3->setChecked(true);
                 break;
       case 3:ui->X3->setText(QString::number(px));
              ui->Y3->setText(QString::number(py));
              pts[2]=std::make_pair(px,py);
              ui->r4->setChecked(true);
                 break;
       case 4:ui->X4->setText(QString::number(px));
              ui->Y4->setText(QString::number(py));
              pts[3]=std::make_pair(px,py);
}}

void Dialog::Mouse_Pressed_sub(QMouseEvent *evv2)
{
    int point,px,py;
    QPoint po=evv2->pos();
    px=ui->img_sub->xAxis->pixelToCoord(po.x());

    py=ui->img_sub->yAxis->pixelToCoord(po.y());



    if(ui->r1_2->isChecked()){point=1;}
    else if(ui->r2_2->isChecked()){point=2;}
    else{point=0;}
    switch (point) {
           case 1:ui->X1_2->setText(QString::number(px));
                  ui->Y1_2->setText(QString::number(py));
                  line_points[0]=px;
                  line_points[1]=py;
                  ui->r2_2->setChecked(true);
                    break;
           case 2:ui->X2_2->setText(QString::number(px));
                  ui->Y2_2->setText(QString::number(py));
                  line_points[2]=px;
                  line_points[3]=py;

    }



}
void Dialog::on_open_clicked()
{
    filename=QFileDialog::getOpenFileName(
                this,
               tr("Open data file"),
               "/home/tosson/Desktop",
               "All files (*);;Text Files (*.txt)"
                );
    if(filename!=0){QMessageBox::information(this, tr("File Name"), filename);
    ui->draw->setEnabled(true);
    ui->ring->setEnabled(true);
    }
    else{QMessageBox::warning(this, tr("Warning"), "Invalid file name");}
}

void Dialog::on_draw_clicked()
{
    if(_base_class!=NULL){
      delete _base_class;
    }

  _base_class=new BaseClass(filename);
  ui->accept->setEnabled(true);
  _base_class->fillPixels();
 colorMap->data()->setSize(384,384);
 colorMap->data()->setRange(QCPRange(0, 384), QCPRange(0, 384));
 double x2, y2, z2;
 int xIndex,yIndex;
 for (xIndex=0; xIndex<384; ++xIndex)  {
      for (yIndex=0; yIndex<384; ++yIndex){
       colorMap->data()->cellToCoord(xIndex, yIndex, &x2, &y2);
       z2 = _base_class->pixel[xIndex][yIndex].counts;
       colorMap->data()->setCell(xIndex, yIndex, z2);
      }
   }

 colorMap->setGradient(QCPColorGradient::gpSpectrum);
 colorMap->selectable();

 colorMap->rescaleDataRange();
 colorMap->setInterpolate(false);
 colorMap->setTightBoundary(false);
 colorMap->rescaleDataRange();
 ui->img->rescaleAxes();
 ui->img->replot();
}

void Dialog::on_ring_clicked()
{
    int max,min;
 ui->accept->setEnabled(true);
    if(!ui->eng_min->isModified()&& !ui->eng_max->isModified()){
      QMessageBox::warning(this, tr("Warning"), "Enter the energy limits");
    }
    else{
        QString mx=ui->eng_max->text();
        max =mx.split(" ")[0].toInt(); 
        QString mn=ui->eng_min->text();
        min =mn.split(" ")[0].toInt();

    if((max<16000)&&(min>100)){_ring_class = new Rings(filename,max,min);
        _ring_class->fillPixels();
        colorMap->data()->setSize(384,384);
        colorMap->data()->setRange(QCPRange(0, 384), QCPRange(0, 384));
        double x2, y2, z2;
        int xIndex,yIndex;
        for (xIndex=0; xIndex<384; ++xIndex)  {
             for (yIndex=0; yIndex<384; ++yIndex){
              colorMap->data()->cellToCoord(xIndex, yIndex, &x2, &y2);
              z2 = _ring_class->pixel[xIndex][yIndex].counts;
              colorMap->data()->setCell(xIndex, yIndex, z2);
             }
          }
        colorMap->setGradient(QCPColorGradient::gpSpectrum);
        colorMap->setInterpolate(true);
        colorMap->setTightBoundary(false);
        ui->img->axisRect()->setRangeZoomFactor(5,5);
        colorMap->rescaleDataRange();
        ui->img->axisRect(0);
        ui->img->rescaleAxes();
        ui->img->replot();
    }
    else {QMessageBox::warning(this, tr("Warning"), "Invalid enteries, please check the energy limits");}
    }
}


void Dialog::on_accept_clicked()
{
_base_class->getSize(&pts);
ui->setline->setEnabled(true);
colorsub_map->data()->setSize(pts[6].first,pts[6].second);
colorsub_map->data()->setRange(QCPRange(pts[4].second, pts[4].first), QCPRange(pts[5].second, pts[5].first));
double x2, y2, z2;
int xIndex,yIndex,xx=0,yy=0;
for (xIndex=pts[4].second; xIndex<pts[4].first; ++xIndex)  {
    yy=0;
     for (yIndex=pts[5].second; yIndex< pts[5].first; ++yIndex){
      colorsub_map->data()->cellToCoord(xIndex,  yIndex, &x2, &y2);
      z2 = _base_class->pixel[xIndex][yIndex].counts;

     colorsub_map->data()->setCell(xx, yy, z2);
     ++yy;
    }
     ++xx;
  }
colorsub_map->setGradient(QCPColorGradient::gpSpectrum);
colorsub_map->setInterpolate(false);
colorsub_map->setTightBoundary(false);
colorsub_map->rescaleDataRange();
ui->img_sub->xAxis->setRange(QCPRange(pts[4].second, pts[4].first));
ui->img_sub->yAxis->setRange(pts[5].second, pts[5].first);
ui->img_sub->rescaleAxes();
ui->img_sub->replot();

}


void Dialog::on_setline_clicked()
{
    line->setPen(QPen(Qt::red));
    line->start->setCoords(line_points[0],line_points[1]);
    line->end->setCoords(line_points[2],line_points[3]);
    ui->img_sub->rescaleAxes();
    ui->img_sub->replot();
    lineM= lineMM(line_points);
    lineb= lineBB(line_points,lineM);
 unsigned int pix_num= std::sqrt(pow((line_points[0]-line_points[2]),2)+pow((line_points[1]-line_points[3]),2));
     QVector <double> yy(pix_num),xx(pix_num),eng(pix_num);
    for (int i=0; i<pix_num; i++)
    {
      xx[i] = i;
      yy[i] = _base_class->pixel[i+line_points[0]][static_cast<int>((lineM*(i+line_points[0]))+lineb)].counts;
      eng[i]= _base_class->pixel[i+line_points[0]][static_cast<int>((lineM*(i+line_points[0]))+lineb)].eng_mode;
    }
    ui->plot->addGraph();
    ui->plot_eng->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::black));
    ui->plot_eng->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setData(xx,yy);
    ui->plot_eng->graph(0)->setData(xx,eng);
    ui->plot->xAxis->setLabel("Pixels");
    ui->plot->yAxis->setLabel("Intensity");
    ui->plot->xAxis->setLabel("Pixels");
    ui->plot_eng->yAxis->setLabel("Energy");
    ui->plot->graph(0)->rescaleAxes(true);
     ui->plot_eng->graph(0)->rescaleAxes(true);
    ui->plot->replot();
    ui->plot_eng->replot();
   ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
   ui->plot_eng->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}
