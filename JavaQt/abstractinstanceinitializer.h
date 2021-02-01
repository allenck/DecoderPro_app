#ifndef ABSTRACTINSTANCEINITIALIZER_H
#define ABSTRACTINSTANCEINITIALIZER_H
#include "instanceinitializer.h"

class AbstractInstanceInitializer : public InstanceInitializer
{
public:
 AbstractInstanceInitializer();
 /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) const throw (IllegalArgumentException);
 /*public*/ QSet</*Class<?>*/QString> getInitalizes();

};

#endif // ABSTRACTINSTANCEINITIALIZER_H
