#ifndef METERMANAGER_H
#define METERMANAGER_H
#include "abstractmanager.h"

class MeterManager : public AbstractManager
{
  Q_OBJECT
 public:
  MeterManager(QObject* parent = nullptr) : AbstractManager(parent) {}
};
#endif // METERMANAGER_H
