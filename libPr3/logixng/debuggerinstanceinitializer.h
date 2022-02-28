#ifndef DEBUGGERINSTANCEINITIALIZER_H
#define DEBUGGERINSTANCEINITIALIZER_H

#include <abstractinstanceinitializer.h>

class DebuggerInstanceInitializer : public AbstractInstanceInitializer
{
 public:
  explicit DebuggerInstanceInitializer(QObject *parent = nullptr) : AbstractInstanceInitializer(parent) {}
  /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type)const override;
  /*public*/ QSet</*Class<?>*/QString>* getInitalizes() override;

};

#endif // DEBUGGERINSTANCEINITIALIZER_H
