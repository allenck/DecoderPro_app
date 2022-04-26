#ifndef SHUTDOWNMANAGERINITIALIZER_H
#define SHUTDOWNMANAGERINITIALIZER_H

#include <abstractinstanceinitializer.h>

class Logger;
class ShutDownManagerInitializer : public AbstractInstanceInitializer
{
  Q_OBJECT
 public:
  explicit ShutDownManagerInitializer(QObject *parent = nullptr);
  /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) const override;
  /*public*/ QSet</*Class<?>*/QString>* getInitalizes()override;

 private:
  static Logger* log;
};

#endif // SHUTDOWNMANAGERINITIALIZER_H
