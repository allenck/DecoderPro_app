#ifndef ABSTRACTSECTIONMANAGER_H
#define ABSTRACTSECTIONMANAGER_H
#include "abstractmanager.h"
#include "internalsystemconnectionmemo.h"
#include "section.h"

class AbstractSectionManager : public AbstractManager
{
  Q_OBJECT
 public:
  AbstractSectionManager(InternalSystemConnectionMemo* memo = nullptr, QObject* parent = nullptr);
  /*public*/ Section* getBySystemName(QString name) const;
  /*public*/ Section* getByUserName(QString key) const;
};

#endif // ABSTRACTSECTIONMANAGER_H
