#ifndef DEFAULTANALOGEXPRESSIONMANAGER_H
#define DEFAULTANALOGEXPRESSIONMANAGER_H

#include "abstractbasemanager.h"
#include "instancemanagerautodefault.h"
#include "Analogexpressionbean.h"
#include "maleanalogexpressionsocket.h"

class MaleAnalogExpressionSocketFactory;
class AnalogExpressionAnalogIO;
class AnalogExpressionFactory;
class FemaleSocketListener;
class FemaleAnalogExpressionSocket;
class Base;
class Category;
class DefaultAnalogExpressionManager : public AbstractBaseManager, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  explicit DefaultAnalogExpressionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass();
  /*public*/  MaleSocket* getLastRegisteredMaleSocket()override;
  /*public*/  MaleAnalogExpressionSocket* registerBean(MaleAnalogExpressionSocket* maleSocket);
  /*public*/  MaleAnalogExpressionSocket* registerExpression(/*@Nonnull*/ AnalogExpressionBean* expression);
  /*public*/  int getXMLOrder() const override;
  /*public*/  QString getBeanTypeHandled() const override;
  /*public*/  void deleteAnalogExpression(MaleAnalogExpressionSocket* x);
  /*public*/  QChar typeLetter() const override;
  /*public*/  NameValidity validSystemNameFormat(QString systemName) override;
  /*public*/  FemaleAnalogExpressionSocket* createFemaleSocket(
    Base* parent, FemaleSocketListener* listener, QString socketName);
  /*public*/  QMap<Category*, QList</*Class<? extends Base>*/Base*>> getExpressionClasses();
  /*public*/  QString getBeanTypeHandled(bool plural);
  static /*public*/  DefaultAnalogExpressionManager* instance();
  /*public*/  /*Class<MaleAnalogExpressionSocket>*/QString getNamedBeanClass();

 private:
  static Logger* log;
  /*private*/ /*final*/ QMap<Category*, QList</*Class<? extends Base*/Base*>> expressionClassList = QMap<Category*, QList</*Class<? extends Base*/Base*>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultAnalogExpressionManager* _instance;// = nullptr;
  QList<QString> aList; //list of classes derived from AnalogExpressionFactory*
//                                       = {new AnalogExpressionAnalogIO(),
//                                          new AnalogExpressionConstant(),
//                                          new AnalogExpressionMemory(),
//                                          new AnalogFormula(),
//                                          new TimeSinceMidnight()};
  QList<MaleAnalogExpressionSocketFactory*> bList; //DebuggerMaleAnalogExpressionSocketFactory
protected:
  /*protected*/ MaleAnalogExpressionSocket* createMaleAnalogExpressionSocket(AnalogExpressionBean* expression);
  /*protected*/ MaleAnalogExpressionSocket* castBean(MaleSocket* maleSocket)override;

};

#endif // DEFAULTANALOGEXPRESSIONMANAGER_H
