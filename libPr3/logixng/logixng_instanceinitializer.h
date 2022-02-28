#ifndef LOGIXNG_INSTANCEINITIALIZER_H
#define LOGIXNG_INSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class LogixNG_InstanceInitializer : public AbstractInstanceInitializer
{
 Q_OBJECT
 public:
  LogixNG_InstanceInitializer(QObject* parent = nullptr) : AbstractInstanceInitializer(parent) {}
  /*public*/  /*<T>*/ QObject* getDefault(QString type) const override;
  /*public*/  QSet<QString>* getInitalizes()override;

};

#endif // LOGIXNG_INSTANCEINITIALIZER_H
