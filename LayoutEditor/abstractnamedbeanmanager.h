#ifndef ABSTRACTNAMEDBEANMANAGER_H
#define ABSTRACTNAMEDBEANMANAGER_H
#include "manager.h"
#include <QObject>

class AbstractNamedBeanManager : public QObject, public Manager
{
  Q_OBJECT
  Q_INTERFACES(Manager)
 public:
  AbstractNamedBeanManager();
  QObject* self() {return (QObject*)this;}

};

#endif // ABSTRACTNAMEDBEANMANAGER_H
