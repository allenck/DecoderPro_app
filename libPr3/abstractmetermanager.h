#ifndef ABSTRACTMETERMANAGER_H
#define ABSTRACTMETERMANAGER_H
#include "abstractmanager.h"
#include "metermanager.h"

class AbstractMeterManager : /*public AbstractManager,*/  public MeterManager
{
  Q_OBJECT
  //Q_INTERFACES(MeterManager)
 public:
  AbstractMeterManager(SystemConnectionMemo* memo, QObject* parent = nullptr);
  /*public*/ int getXMLOrder() const override;
  /*public*/ char typeLetter() const override;
  /*public*/ QString getBeanTypeHandled(bool plural) const override;
  /*public*/ QString getNamedBeanClass() const override {return "jmri.managers.AbstractMeterManager";}
  /*public*/ NamedBean *getBySystemName(QString name) const override;
  /*public*/ NamedBean* getByUserName(QString key) const override;

};

#endif // ABSTRACTMETERMANAGER_H
