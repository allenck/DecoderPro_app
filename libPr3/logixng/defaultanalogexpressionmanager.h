#ifndef DEFAULTANALOGEXPRESSIONMANAGER_H
#define DEFAULTANALOGEXPRESSIONMANAGER_H

#include "abstractbasemanager.h"
#include "instancemanagerautodefault.h"
#include "Analogexpressionbean.h"
#include "defaultmaleanalogexpressionsocket.h"
#include "analogexpressionmanager.h"

class MaleAnalogExpressionSocketFactory;
class AnalogExpressionAnalogIO;
class AnalogExpressionFactory;
class FemaleSocketListener;
class FemaleAnalogExpressionSocket;
class Base;
class Category;
class DefaultAnalogExpressionManager : public AbstractBaseManager, public AnalogExpressionManager, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(AnalogExpressionManager InstanceManagerAutoDefault)
 public:
  explicit DefaultAnalogExpressionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleSocket* registerBean(/*MaleAnalogExpressionSocket**/MaleSocket* maleSocket)override;
  /*public*/  MaleAnalogExpressionSocket* registerExpression(/*@Nonnull*/ AnalogExpressionBean* expression)override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QString getBeanTypeHandled() const override;
  /*public*/  void deleteAnalogExpression(MaleAnalogExpressionSocket *x)override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  NameValidity validSystemNameFormat(QString systemName) override;
  /*public*/  FemaleAnalogExpressionSocket* createFemaleSocket(
    Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getExpressionClasses()override;
  /*public*/  QString getBeanTypeHandled(bool plural)const override;
  static /*public*/  DefaultAnalogExpressionManager* instance();
  /*public*/  /*Class<MaleAnalogExpressionSocket>*/QString getNamedBeanClass()const override;
  /*public*/ QString getClassName() {return "jmri.jmrit.logixng.implementation.DefaultAnalogExpressionManager";}

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  /*public*/ QString getAutoSystemName()override;

 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base*/QString>> expressionClassList = QHash<Category*, QList</*Class<? extends Base*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultAnalogExpressionManager* _instance;// = nullptr;
protected:
  /*protected*/ MaleAnalogExpressionSocket* createMaleAnalogExpressionSocket(AnalogExpressionBean* expression);
  /*protected*/ MaleAnalogExpressionSocket* castBean(MaleSocket* maleSocket)override;

};

#endif // DEFAULTANALOGEXPRESSIONMANAGER_H
