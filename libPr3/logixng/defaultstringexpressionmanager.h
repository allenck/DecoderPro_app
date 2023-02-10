#ifndef DEFAULTSTRINGEXPRESSIONMANAGER_H
#define DEFAULTSTRINGEXPRESSIONMANAGER_H

#include "abstractbasemanager.h"
#include "stringexpressionmanager.h"
#include "instancemanagerautodefault.h"
#include "defaultmalestringexpressionsocket.h"

class DefaultMaleStringExpressionSocket;
class DefaultStringExpressionManager : public AbstractBaseManager, public StringExpressionManager, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(StringExpressionManager InstanceManagerAutoDefault)
 public:
  explicit DefaultStringExpressionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  AbstractMaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  AbstractMaleSocket *registerBean(/*MaleStringExpressionSocket*/AbstractMaleSocket *maleSocket)override;
  /*public*/  DefaultMaleStringExpressionSocket* registerExpression(/*@Nonnull*/ StringExpressionBean* expression)
          /*throws IllegalArgumentException*/override;
  /*public*/  int getXMLOrder()  const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleStringExpressionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getExpressionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteStringExpression(DefaultMaleStringExpressionSocket *x)override;
  static /*public*/  DefaultStringExpressionManager* instance();
  /*public*/  /*Class<MaleStringExpressionSocket>*/QString getNamedBeanClass()const override;
  QString getClassName() override {return ".jmri.jmrit.logixng.implementation.DefaultStringExpressionManager";}

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

  QString getAutoSystemName() override {return AbstractManager::getAutoSystemName();}


 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category, QList</*Class<? extends Base>*/QString>> expressionClassList = QHash<Category, QList</*Class<? extends Base>*/QString>>();
  /*private*/ AbstractMaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultStringExpressionManager* _instance;// = null;


 protected:
  /*protected*/ MaleStringExpressionSocket* castBean(MaleSocket* maleSocket)override;
  /*protected*/ DefaultMaleStringExpressionSocket *createMaleStringExpressionSocket(StringExpressionBean* expression);

};

#endif // DEFAULTSTRINGEXPRESSIONMANAGER_H
