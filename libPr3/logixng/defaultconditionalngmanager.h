#ifndef DEFAULTCONDITIONALNGMANAGER_H
#define DEFAULTCONDITIONALNGMANAGER_H

#include <abstractmanager.h>
#include "conditionalng_manager.h"
#include "conditionalng.h"

class LogixNG;
class DefaultConditionalNGManager : public AbstractManager, public ConditionalNG_Manager
{
  Q_OBJECT
  Q_INTERFACES(ConditionalNG_Manager)
 public:
  DefaultConditionalNGManager(QObject* parent = nullptr);
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  NameValidity validSystemNameFormat(QString systemName)override;
  /*public*/  DefaultConditionalNG *createConditionalNG(LogixNG* logixNG, QString systemName, QString userName)
          /*throws IllegalArgumentException*/override;
  /*public*/  DefaultConditionalNG *createConditionalNG(
          LogixNG* logixNG, QString systemName, QString userName, int threadID)
          /*throws IllegalArgumentException*/override;
  /*public*/  ConditionalNG* createConditionalNG(LogixNG* logixNG, QString userName) /*throws IllegalArgumentException*/ override;
  /*public*/  ConditionalNG* createConditionalNG(LogixNG* logixNG, QString userName, int threadID) /*throws IllegalArgumentException*/override;
  /*public*/  ConditionalNG* getConditionalNG(LogixNG* logixNG, QString name) override;
  /*public*/  LogixNG* getParentLogixNG(QString systemName)override;
  /*public*/  DefaultConditionalNG *getByUserName(LogixNG* logixNG, QString name) override;
  /*public*/  NamedBean* getByUserName(QString name) override
  {
   return  AbstractManager::getByUserName(name);
  }
  /*public*/  ConditionalNG *getBySystemName(QString name)override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteConditionalNG(ConditionalNG* x)override;
  /*public*/  void setLoadDisabled(bool s)override;
  /*public*/  void setRunOnGUIDelayed(bool value)override;
  static /*public*/  DefaultConditionalNGManager* instance() ;
  /*public*/  /*Class<ConditionalNG>*/QString getNamedBeanClass() const override;
  /*public*/  void fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/;
  /*public*/  /*final*/ void deleteBean(/*@Nonnull*/ /*ConditionalNG**/NamedBean* conditionalNG, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/override;
  QString getClassName() {return "jmri.jmrit.logixng.implementation.DefaultConditionalNGManager";}
  QObject* self() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}


 private:
  static Logger* log;
  static /*volatile*/ DefaultConditionalNGManager* _instance;// = nullptr;

};

#endif // DEFAULTCONDITIONALNGMANAGER_H
