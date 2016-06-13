#ifndef QUALIFIERCOMBINER_H
#define QUALIFIERCOMBINER_H
#include "qualifier.h"
#include "libPr3_global.h"

class VariableValue;
class ValueQualifier;
class PropertyChangeEvent;
class LIBPR3SHARED_EXPORT QualifierCombiner : public Qualifier
{
 Q_OBJECT
public:
    //explicit QualifierCombiner();
    /*public*/ QualifierCombiner(QList<Qualifier*>* qualifiers);


signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
 //VariableValue* qualifiedVal;
 QList<Qualifier*>* qualifiers;
protected:
 /*protected*/ void setWatchedAvailable(bool enable);
 /*protected*/ bool availableCombinedState();


};

#endif // QUALIFIERCOMBINER_H
