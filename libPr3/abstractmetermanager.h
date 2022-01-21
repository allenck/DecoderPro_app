#ifndef ABSTRACTMETERMANAGER_H
#define ABSTRACTMETERMANAGER_H
#include "abstractmanager.h"
#include "metermanager.h"

class AbstractMeterManager : public AbstractManager,  public MeterManager
{
  Q_OBJECT
  Q_INTERFACES(MeterManager)
 public:
  AbstractMeterManager(SystemConnectionMemo* memo, QObject* parent = nullptr);
  /*public*/ int getXMLOrder() const override;
  /*public*/ QChar typeLetter()  override;
  /*public*/ QString getBeanTypeHandled(bool plural) const override;
  /*public*/ QString getNamedBeanClass() const override {return "jmri.managers.AbstractMeterManager";}
//  /*public*/ NamedBean *getBySystemName(QString name)  override;
//  /*public*/ NamedBean* getByUserName(QString key) override;

  QObject* self() override {return (QObject*)this;}
  /*public*/ NamedBean* getBySystemName(QString name) override{return AbstractManager::getBySystemName(name);}
  /*public*/ NamedBean* getByUserName(QString name) override{return AbstractManager::getByUserName(name);}

  /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}

};

#endif // ABSTRACTMETERMANAGER_H
