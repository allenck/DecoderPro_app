#ifndef PROXYANALOGIOMANAGER_H
#define PROXYANALOGIOMANAGER_H

#include <abstractproxymanager.h>
#include "analogiomanager.h"

class AnalogIO;
class InternalAnalogIOManager;
class ProxyAnalogIOManager : public AbstractProxyManager, public AnalogIOManager
{
  Q_OBJECT
  Q_INTERFACES(AnalogIOManager)
 public:
  explicit ProxyAnalogIOManager(QObject *parent = nullptr);
  /*public*/  ProxyAnalogIOManager* init();
  /*public*/  int getXMLOrder() const override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  /*Class<AnalogIO>*/QString getNamedBeanClass() const override;
  /*public*/  /*AnalogIO*/ NamedBean* getBySystemName(/*@Nonnull*/ QString systemName)const override;
  /*public*/  NamedBean* getByUserName(/*@Nonnull*/ QString userName)const override;
  /*public*/  void dispose()override;
  /*public*/  void addBeanType(/*Class<? extends AnalogIO>*/QString clazz, Manager/*<? extends NamedBean>*/* manager);
  /*public*/  void removeBeanType(/*Class<? extends AnalogIO>*/QString clazz, Manager/*<? extends NamedBean>*/* manager);

  QObject* pself() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}


 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* e)override;

 private:
  /*private*/ /*final*/ InternalAnalogIOManager* internalAnalogIOManager;
  /*private*/ bool muteUpdates = false;
  /*private*/ /*final*/ QList</*Class<? extends AnalogIO>*/QString> registerBeans = QList</*Class<? extends AnalogIO>*/QString>();
  /*private*/ /*final*/ QList<Manager/*<? extends NamedBean>*/*> registerBeanManagers = QList<Manager/*<? extends NamedBean>*/*>();

 protected:
  /*protected*/ AbstractManager/*<AnalogIO>*/* makeInternalManager() const override;

};

#endif // PROXYANALOGIOMANAGER_H
