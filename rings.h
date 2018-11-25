#ifndef RINGS_H
#define RINGS_H
#include "baseclass.h"

class Rings: public BaseClass
{
public:
    Rings(QString fn, float maxen, float minen);
    void fillPixels();

private:
    volatile float eng_min,eng_max;
QString f_dir;
};

#endif // RINGS_H
