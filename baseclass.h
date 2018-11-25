#ifndef BASECLASS_H
#define BASECLASS_H
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QProgressDialog>
#include <QDialog>
#include "pixel.h"
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
typedef std::vector<std::pair<int, int> > VP;
class BaseClass
{
public:
    BaseClass(QString fn);
    virtual void fillPixels();
   // int modeValue(std::vector<int> *eng, int size);
    pixelall pixel[385][385];
    void getSize(VP *p);
    virtual ~BaseClass();


private:
    QString f_dir;
    QProgressDialog *prog;
};

#endif // BASECLASS_H
