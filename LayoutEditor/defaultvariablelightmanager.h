#ifndef DEFAULTVARIABLELIGHTMANAGER_H
#define DEFAULTVARIABLELIGHTMANAGER_H

#include <abstractlightmanager.h>
#include "variablelightmanager.h"

class DefaultVariableLightManager : public AbstractManager, public VariableLightManager
{
  Q_OBJECT
  Q_INTERFACES(VariableLightManager)
 public:
  DefaultVariableLightManager(SystemConnectionMemo* memo, QObject* parent=nullptr);
  ~DefaultVariableLightManager() {}
  DefaultVariableLightManager(const DefaultVariableLightManager& other) : AbstractManager(other.memo) {}
  /*public*/ DefaultVariableLightManager* init();
  /*public*/ void dispose() override;
  /*public*/ int getXMLOrder()const override;
  /*public*/ QChar typeLetter() const override;
  /*public*/ QString getBeanTypeHandled(bool plural)const override;
  /*public*/ /*Class<VariableLight>*/ QString getNamedBeanClass()const override;
  /*public*/ void Register(/*@Nonnull*/ NamedBean* s) override;
  /*public*/ void deregister(/*@Nonnull*/ NamedBean* s)override;
  /*public*/ void deleteBean(/*@Nonnull*/ NamedBean* n, /*@Nonnull*/ QString property) override;

  QObject* self() override {return this;}
  QObject* vself() override {return (QObject*)this;}

  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString s) const override {return AbstractManager::getBeanByUserName(s);}
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString s) const override {return AbstractManager::getBeanBySystemName(s);}
  /*public*/ SystemConnectionMemo* getMemo()  override {return AbstractManager::getMemo();}
 public slots:
  //@Override
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

};

#endif // DEFAULTVARIABLELIGHTMANAGER_H
