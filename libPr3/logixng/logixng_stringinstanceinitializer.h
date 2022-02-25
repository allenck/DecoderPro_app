#ifndef LOGIXNG_STRINGINSTANCEINITIALIZER_H
#define LOGIXNG_STRINGINSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class LogixNG_StringInstanceInitializer : public AbstractInstanceInitializer
{
  Q_OBJECT
 public:
  explicit LogixNG_StringInstanceInitializer(QObject *parent = nullptr);
  /*public*/  /*<T>*/  QObject* getDefault(/*Class<T>*/QString type)const override;
  /*public*/  QSet</*Class<?>*/QString> getInitalizes()override;

};

#endif // LOGIXNG_STRINGINSTANCEINITIALIZER_H
