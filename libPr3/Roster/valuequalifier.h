#ifndef VALUEQUALIFIER_H
#define VALUEQUALIFIER_H
#include "variablevalue.h"
#include "arithmeticqualifier.h"


class LIBPR3SHARED_EXPORT ValueQualifier : public ArithmeticQualifier
{
 //Q_OBJECT
public:
    //explicit ValueQualifier(QObject *parent = 0);
    /*public*/ ValueQualifier(VariableValue* qualifiedVal, VariableValue* watchedVal, int value, QString relation);
    /*public*/ void setWatchedAvailable(bool enable);

signals:

public slots:
private:
    VariableValue* qualifiedVal;

protected:
    /*protected*/ bool currentAvailableState();

};

#endif // VALUEQUALIFIER_H
