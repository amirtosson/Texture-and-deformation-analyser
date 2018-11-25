#ifndef MY_Q_H
#define MY_Q_H

#include <QWidget>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include <QLabel>
#include <QPixmap>


class my_q : public QLabel
{
     Q_OBJECT
public:
    explicit my_q(QWidget *parent = 0);
        void mouseMoveEvent(QMouseEvent *ev);
        void mousePressEvent(QMouseEvent *ev);
         int x,y;
signals:
        void Mouse_Pressed2();
        void Mouse_Pos();
public slots:
};
#endif // MY_Q_H
