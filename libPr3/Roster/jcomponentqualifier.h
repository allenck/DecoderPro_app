#ifndef JCOMPONENTQUALIFIER_H
#define JCOMPONENTQUALIFIER_H
#include "arithmeticqualifier.h"

class JComponentQualifier : public ArithmeticQualifier
{
    Q_OBJECT
public:
    //explicit JComponentQualifier(QObject *parent = 0);
    /*public*/ JComponentQualifier(QWidget* component, VariableValue* watchedVal, int value, QString relation, QObject *parent = 0);
    /*public*/ void setWatchedAvailable(bool enable);

signals:

public slots:
private:
    QWidget* component;
protected:
    /*protected*/ bool currentAvailableState();

};

#endif // JCOMPONENTQUALIFIER_H
