#ifndef DEFAULTDIGITALACTIONMANAGER_H
#define DEFAULTDIGITALACTIONMANAGER_H

#include "abstractbasemanager.h"
#include <QObject>
#include "digitalactionmanager.h"
#include "category.h"

class DefaultDigitalActionManager : public AbstractBaseManager, public DigitalActionManager
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionManager)
 public:
  explicit DefaultDigitalActionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleDigitalActionSocket* registerBean(/*MaleDigitalActionSocket*/NamedBean* maleSocket)override;
  /*public*/  MaleDigitalActionSocket* registerAction(/*@Nonnull*/ DigitalActionBean* action)
          /*throws IllegalArgumentException*/ override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleDigitalActionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getActionClasses() override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteDigitalAction(MaleDigitalActionSocket* x)override;
  static /*public*/  DefaultDigitalActionManager* instance();
  /*public*/  /*Class<MaleDigitalActionSocket>*/QString getNamedBeanClass() const override;

  QObject* pself() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}


 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> actionClassList = QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultDigitalActionManager* _instance;// = null;

 protected:
  /*protected*/ MaleDigitalActionSocket* createMaleActionSocket(DigitalActionBean* action);
  /*protected*/ MaleDigitalActionSocket* castBean(MaleSocket* maleSocket)override;

};

#endif // DEFAULTDIGITALACTIONMANAGER_H
