#ifndef STRINGACTIONMEMORY_H
#define STRINGACTIONMEMORY_H

#include "abstractstringaction.h"
#include <QObject>
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "namedbeanhandlemanager.h"
#include "memory.h"

class StringActionMemory : public AbstractStringAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit StringActionMemory(QString sys, QString user, QObject *parent = nullptr);

  /*public*/  void setValue(QString value)override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<Memory*>* _memoryHandle;

};

#endif // STRINGACTIONMEMORY_H
