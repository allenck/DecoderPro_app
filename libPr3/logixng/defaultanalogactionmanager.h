#ifndef DEFAULTANALOGACTIONMANAGER_H
#define DEFAULTANALOGACTIONMANAGER_H

#include "abstractbasemanager.h"
#include "analogactionmanager.h"

class DefaultAnalogActionManager : public AbstractBaseManager, public AnalogActionManager
{
  Q_OBJECT
  Q_INTERFACES(AnalogActionManager)
 public:
  explicit DefaultAnalogActionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleSocket* registerBean(/*MaleAnalogActionSocket*/MaleSocket *maleSocket)override;
  /*public*/  MaleAnalogActionSocket* registerAction(/*@Nonnull*/ AnalogActionBean* action)
          /*throws IllegalArgumentException*/override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QString getBeanTypeHandled() const override;
  /*public*/  void deleteAnalogAction(MaleAnalogActionSocket* x)override;
  /*public*/  QChar typeLetter() const override;
//  /*public*/  Manager::NameValidity validSystemNameFormat(QString systemName)override;
  /*public*/  FemaleAnalogActionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getActionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  static /*public*/  DefaultAnalogActionManager* instance();
  /*public*/  /*Class<MaleAnalogActionSocket>*/QString getNamedBeanClass() const override;
  QString getClassName() override {return ".jmri.jmrit.logixng.implementation.DefaultAnalogActionManager";}

  QObject* self() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}

  QString getAutoSystemName() override {return AbstractManager::getAutoSystemName();}
 private:
  static Logger* log;
  static /*volatile*/ DefaultAnalogActionManager* _instance;// = null;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> actionClassList =  QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;

 protected:
  /*protected*/ MaleAnalogActionSocket* castBean(MaleSocket* maleSocket)override;
  /*protected*/ MaleAnalogActionSocket* createMaleActionSocket(AnalogActionBean* action);

};

#endif // DEFAULTANALOGACTIONMANAGER_H
