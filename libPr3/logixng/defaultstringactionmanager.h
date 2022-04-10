#ifndef DEFAULTSTRINGACTIONMANAGER_H
#define DEFAULTSTRINGACTIONMANAGER_H

#include "abstractbasemanager.h"
#include "stringactionmanager.h"
#include "malestringactionsocket.h"
class DefaultStringActionManager : public AbstractBaseManager, public StringActionManager
{
  Q_OBJECT
  Q_INTERFACES(StringActionManager)
 public:
  explicit DefaultStringActionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass() override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket() override;
  /*public*/  MaleSocket* registerBean(/*MaleStringActionSocket*/MaleSocket* maleSocket)override;
  /*public*/  MaleStringActionSocket* registerAction(/*@Nonnull*/ StringActionBean* action)
          /*throws IllegalArgumentException*/ override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleStringActionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getActionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteStringAction(MaleStringActionSocket* x)override;
  static /*public*/  DefaultStringActionManager* instance();
  /*public*/  /*Class<MaleStringActionSocket>*/QString getNamedBeanClass() const override;
QString getClassName() override {return ".jmri.jmrit.logixng.implementation.DefaultStringActionManager";}

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> actionClassList = QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultStringActionManager* _instance;// = null;

 protected:
  /*protected*/ MaleStringActionSocket* castBean(MaleSocket* maleSocket)override;
  /*protected*/ MaleStringActionSocket* createMaleActionSocket(StringActionBean* action);

};

#endif // DEFAULTSTRINGACTIONMANAGER_H
