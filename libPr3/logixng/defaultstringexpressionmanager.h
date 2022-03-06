#ifndef DEFAULTSTRINGEXPRESSIONMANAGER_H
#define DEFAULTSTRINGEXPRESSIONMANAGER_H

#include "abstractbasemanager.h"
#include "malestringexpressionsocket.h"
#include "stringexpressionmanager.h"
#include "instancemanagerautodefault.h"


class DefaultStringExpressionManager : public AbstractBaseManager, public StringExpressionManager, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(StringExpressionManager InstanceManagerAutoDefault)
 public:
  explicit DefaultStringExpressionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleSocket* registerBean(/*MaleStringExpressionSocket*/MaleSocket* maleSocket)override;
  /*public*/  MaleStringExpressionSocket* registerExpression(/*@Nonnull*/ StringExpressionBean* expression)
          /*throws IllegalArgumentException*/override;
  /*public*/  int getXMLOrder()  const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleStringExpressionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getExpressionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteStringExpression(MaleStringExpressionSocket* x)override;
  static /*public*/  DefaultStringExpressionManager* instance();
  /*public*/  /*Class<MaleStringExpressionSocket>*/QString getNamedBeanClass()const override;

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}


 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> expressionClassList = QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultStringExpressionManager* _instance;// = null;


 protected:
  /*protected*/ MaleStringExpressionSocket* castBean(MaleSocket* maleSocket)override;
  /*protected*/ MaleStringExpressionSocket* createMaleStringExpressionSocket(StringExpressionBean* expression);

};

#endif // DEFAULTSTRINGEXPRESSIONMANAGER_H
