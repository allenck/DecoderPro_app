#ifndef ABSTRACTNAMEDBEANHANDLEMANAGER_H
#define ABSTRACTNAMEDBEANHANDLEMANAGER_H
#include "abstractmanager.h"

class AbstractNamedBeanHandleManager : public AbstractManager
{
  Q_OBJECT
 public:
  AbstractNamedBeanHandleManager(QObject* parent = nullptr);
  /*public*/ NamedBean* getBySystemName(QString name) const;
  /*public*/ NamedBean* getByUserName(QString key) const;
};

#endif // ABSTRACTNAMEDBEANHANDLEMANAGER_H
