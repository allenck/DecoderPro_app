#ifndef DEFAULTDIGITALACTIONMANAGER_H
#define DEFAULTDIGITALACTIONMANAGER_H

#include "abstractbasemanager.h"
#include <QObject>
#include "digitalactionmanager.h"
#include "category.h"
#include "abstractmalesocket.h"

class DefaultDigitalActionManager : public AbstractBaseManager, public DigitalActionManager
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionManager)
 public:
  explicit DefaultDigitalActionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  AbstractMaleSocket *getLastRegisteredMaleSocket()override;
  /*public*/  AbstractMaleSocket *registerBean(/*MaleDigitalActionSocket*/AbstractMaleSocket *maleSocket) override;
  /*public*/  MaleDigitalActionSocket* registerAction(/*@Nonnull*/ NamedBean* action)
          /*throws IllegalArgumentException*/ override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleDigitalActionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getActionClasses() override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteDigitalAction(MaleDigitalActionSocket* x)override;
  static /*public*/  DefaultDigitalActionManager* instance();
  /*public*/  /*Class<MaleDigitalActionSocket>*/QString getNamedBeanClass() const override;
  QString getClassName() override {return "jmri.jmrit.logixng.implementation.DefaultDigitalActionManager";}

  QObject* pself() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}

  QString getAutoSystemName() override {return AbstractManager::getAutoSystemName();}
  void addPropertyChangeListener(PropertyChangeListener* l) override {PropertyChangeSupport::addPropertyChangeListener(l);}

 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category, QList</*Class<? extends Base>*/QString>> actionClassList = QHash<Category, QList</*Class<? extends Base>*/QString>>();
  /*private*/ AbstractMaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultDigitalActionManager* _instance;// = null;

 protected:
  /*protected*/ MaleDigitalActionSocket* createMaleActionSocket(DigitalActionBean* action);
  /*protected*/ MaleDigitalActionSocket* castBean(MaleSocket* maleSocket)override;

};

#endif // DEFAULTDIGITALACTIONMANAGER_H
