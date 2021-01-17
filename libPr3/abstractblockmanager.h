#ifndef ABSTRACTBLOCKMANAGER_H
#define ABSTRACTBLOCKMANAGER_H
#include "abstractmanager.h"
#include "block.h"

class AbstractBlockManager : public AbstractManager
{
  Q_OBJECT
 public:
  AbstractBlockManager(QObject* parent = nullptr);
  /*public*/ Block* getBySystemName(QString name) const ;
  /*public*/ Block *getByUserName(QString key)const ;

};

#endif // ABSTRACTBLOCKMANAGER_H
