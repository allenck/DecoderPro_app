#ifndef LOGIXNG_INSTANCEINITIALIZER_H
#define LOGIXNG_INSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class LogixNG_InstanceInitializer : public AbstractInstanceInitializer
{
 public:
  LogixNG_InstanceInitializer();
  /*public*/  /*<T>*/ QObject* getDefault(QString type)override;
  /*public*/  QSet<QString> getInitalizes();

};

#endif // LOGIXNG_INSTANCEINITIALIZER_H
