#ifndef DECIMALFORMAT_H
#define DECIMALFORMAT_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DecimalFormat //: public QObject
{
 //Q_OBJECT
public:
    explicit DecimalFormat(QString tmplt/*, QObject *parent = nullptr*/);
    QString format(int num) const;
    QString format(double num)const;

private:
 QString tmplt;

};

#endif // DECIMALFORMAT_H
