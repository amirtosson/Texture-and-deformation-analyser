#include "my_q.h"

my_q::my_q(QWidget *parent) : QLabel(parent){}
void my_q::mouseMoveEvent(QMouseEvent *ev)
{this->x = ev->x();
 this->y = 384-ev->y();
 emit Mouse_Pos();}

void my_q::mousePressEvent(QMouseEvent *ev)
{//emit Mouse_Pressed();
}


