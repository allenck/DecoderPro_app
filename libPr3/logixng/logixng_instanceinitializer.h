#ifndef LOGIXNG_INSTANCEINITIALIZER_H
#define LOGIXNG_INSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class LogixNG_InstanceInitializer : public AbstractInstanceInitializer
{
 Q_OBJECT
 public:
  LogixNG_InstanceInitializer();
  /*public*/  /*<T>*/ QObject* getDefault(QString type)override;
  /*public*/  QSet<QString> getInitalizes()override;

};

#endif // LOGIXNG_INSTANCEINITIALIZER_H
