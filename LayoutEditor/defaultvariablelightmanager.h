#ifndef DEFAULTVARIABLELIGHTMANAGER_H
#define DEFAULTVARIABLELIGHTMANAGER_H

#include <abstractlightmanager.h>
#include "variablelightmanager.h"

class DefaultVariableLightManager : public AbstractLightManager, public VariableLightManager
{
  Q_OBJECT
  Q_INTERFACES(VariableLightManager)
 public:
  DefaultVariableLightManager(SystemConnectionMemo* memo, QObject* parent=nullptr);
  ~DefaultVariableLightManager() {}
  DefaultVariableLightManager(const DefaultVariableLightManager& other) : AbstractLightManager(other.memo) {}
  /*public*/ DefaultVariableLightManager* init();
  /*public*/ void dispose() override;
  /*public*/ int getXMLOrder()const override;
  /*public*/ char typeLetter() const override;
  /*public*/ QString getBeanTypeHandled(bool plural)const override;
  /*public*/ /*Class<VariableLight>*/ QString getNamedBeanClass()const override;
  /*public*/ void Register(/*@Nonnull*/ VariableLight* s);
  /*public*/ void deregister(/*@Nonnull*/ NamedBean* s)const override;
  /*public*/ void deleteBean(/*@Nonnull*/ VariableLight* n, /*@Nonnull*/ QString property) ;

  QObject* self() override {return this;}
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString s) const override;
  /*public*/ VariableLight* getBySystemName(/*@Nonnull*/ QString s);
  /*public*/ SystemConnectionMemo* getMemo() const override;
 public slots:
  //@Override
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

};

#endif // DEFAULTVARIABLELIGHTMANAGER_H
