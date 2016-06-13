#ifndef DECIMALFORMAT_H
#define DECIMALFORMAT_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DecimalFormat //: public QObject
{
    //Q_OBJECT
public:
    explicit DecimalFormat(QString tmplt/*, QObject *parent = 0*/);
    QString format(int num);
    QString format(double num);

signals:

public slots:
private:
 QString tmplt;
 //QObject* parent;

};

#endif // DECIMALFORMAT_H
