#ifndef LOGIXNG_ANALOGINSTANCEINITIALIZER_H
#define LOGIXNG_ANALOGINSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class LogixNG_AnalogInstanceInitializer : public AbstractInstanceInitializer
{
  Q_OBJECT
 public:
  explicit LogixNG_AnalogInstanceInitializer(QObject *parent = nullptr) : AbstractInstanceInitializer(parent) {}
  /*public*/  /*<T>*/ QObject* getDefault(QString  type) const override;
  /*public*/  QSet</*Class<?>*/QString>* getInitalizes()override;

};

#endif // LOGIXNG_ANALOGINSTANCEINITIALIZER_H
