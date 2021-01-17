#ifndef METERMANAGER_H
#define METERMANAGER_H
#include "abstractmanager.h"

class MeterManager : public AbstractManager
{
  Q_OBJECT
 public:
  MeterManager(QObject* parent = nullptr) : AbstractManager(parent) {}
  MeterManager(SystemConnectionMemo*memo, QObject *parent = 0) : AbstractManager(memo, parent) {}
  //  QString getNamedBeanClass() const override {return "jmri.MeterManager";}
//  int getXMLOrder() const {return Manager::METERS;}
  //virtual QObject* self() =0;
  /*public*/ virtual NamedBean *getBySystemName(QString name) const =0;
  /*public*/ virtual NamedBean* getByUserName(QString key) const =0;

};
//Q_DECLARE_INTERFACE(MeterManager, "MeterManager")
#endif // METERMANAGER_H
