#ifndef SPINNERNUMBERMODEL_H
#define SPINNERNUMBERMODEL_H
#include "abstractspinnermodel.h"
//#include "comparable.h"
//#include "number.h"
#include <QVariant>
#include "javaqt_global.h"


class JAVAQTSHARED_EXPORT SpinnerNumberModel : public AbstractSpinnerModel
{
    Q_OBJECT
public:
    explicit SpinnerNumberModel(QObject *parent = 0);
/*public*/ SpinnerNumberModel(QVariant value, QVariant minimum, QVariant maximum, QVariant stepSize, QObject *parent = 0);
/*public*/ SpinnerNumberModel(int value, int minimum, int maximum, int stepSize, QObject *parent = 0);
/*public*/ void setMinimum(QVariant minimum);
/*public*/ QVariant getMinimum();
/*public*/ void setMaximum(QVariant maximum);
/*public*/ QVariant getMaximum();
/*public*/ void setStepSize(QVariant stepSize);
/*public*/ QVariant getStepSize();
/*public*/ QVariant getNextValue();
/*public*/ QVariant getPreviousValue();
/*public*/ QVariant getNumber();
/*public*/ QVariant getValue() ;
/*public*/ void setValue(QVariant value);

signals:

public slots:
private:
    /*private*/ QVariant stepSize, value;
    /*private*/ QVariant minimum, maximum;
/*private*/ QVariant incrValue(int dir);


};

#endif // SPINNERNUMBERMODEL_H
