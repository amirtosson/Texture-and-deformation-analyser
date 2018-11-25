#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "qcustomplot.h"
#include "pixel.h"
#include "baseclass.h"
#include "rings.h"
#include <exception>
#include <vector>
#include <utility>
#include <algorithm>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString filename;

private slots:
    void Mouse_current_pos(QMouseEvent *evv);
    void Mouse_current_pos_sub(QMouseEvent *evv);
    void Mouse_Pressed(QMouseEvent *evv2);
    void Mouse_Pressed_sub(QMouseEvent *evv2);
    void on_open_clicked();

    void on_draw_clicked();

    void on_ring_clicked();

    void on_accept_clicked();

    void on_setline_clicked();

private:
    Ui::Dialog *ui;
    QCPColorMap *colorMap;
    QCPColorMap *colorsub_map;
    QCPItemLine *line;
    BaseClass *_base_class;
    Rings *_ring_class;
    std::vector<std::pair<int,int> >pts;
    int line_points[4];
    float lineM,lineb;

};

#endif // DIALOG_H
