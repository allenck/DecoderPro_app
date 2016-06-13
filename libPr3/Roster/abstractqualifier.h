#ifndef ABSTRACTQUALIFIER_H
#define ABSTRACTQUALIFIER_H
#include "qualifier.h"
#include "variablevalue.h"

class LIBPR3SHARED_EXPORT AbstractQualifier : public Qualifier
{
    //Q_OBJECT
public:
    //explicit AbstractQualifier(QObject *parent = 0);
    /*public*/ AbstractQualifier( VariableValue* watchedVal, QObject *parent = 0);
    void processValueChangeEvent(PropertyChangeEvent* e);
//    /*public*/ void update(int value);
    /*abstract*/ /*public*/ virtual bool currentDesiredState();
signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    VariableValue* watchedVal;
protected:
    /*protected*/ bool availableStateFromEvent(PropertyChangeEvent* e);
    virtual bool availableStateFromValue(int );

    /*protected*/ void setWatchedAvailable(bool enable);
    /*abstract*/ /*protected*/ virtual bool currentAvailableState();

friend class QualifierCombiner;
friend class ArithmeticQualifier;
};

#endif // ABSTRACTQUALIFIER_H
