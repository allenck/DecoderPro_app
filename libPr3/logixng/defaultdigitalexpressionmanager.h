#ifndef DEFAULTDIGITALEXPRESSIONMANAGER_H
#define DEFAULTDIGITALEXPRESSIONMANAGER_H

#include "abstractbasemanager.h"
#include "category.h"
#include "digitalexpressionmanager.h"

class MaleDigitalExpressionSocket;
class DefaultDigitalExpressionManager : public AbstractBaseManager, public DigitalExpressionManager
{
 public:
  explicit DefaultDigitalExpressionManager(QObject *parent = nullptr);
  /*public*/  /*Class<? extends MaleSocket>*/QString getMaleSocketClass()override;
  /*public*/  MaleSocket* getLastRegisteredMaleSocket() override;
  /*public*/  MaleSocket* registerBean(/*MaleDigitalExpressionSocket*/MaleSocket* maleSocket)override;
  /*public*/  MaleDigitalExpressionSocket* registerExpression(/*@Nonnull*/DigitalExpressionBean* expression)
          /*throws IllegalArgumentException */override;
  /*public*/  int getXMLOrder() const override;
  /*public*/  QChar typeLetter() const override;
  /*public*/  FemaleDigitalExpressionSocket* createFemaleSocket(
          Base* parent, FemaleSocketListener* listener, QString socketName)override;
  /*public*/  QHash<Category *, QList<QString> > getExpressionClasses() override;
  /*public*/  QString getBeanTypeHandled(bool plural) const override;
  /*public*/  void deleteDigitalExpression(MaleDigitalExpressionSocket* x)override;
  static /*public*/  DefaultDigitalExpressionManager* instance();
  /*public*/  /*Class<MaleDigitalExpressionSocket>*/QString getNamedBeanClass() const override;

  QObject* vself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ /*final*/ QHash<Category*, QList</*Class<? extends Base>*/QString>> expressionClassList = QHash<Category*, QList</*Class<? extends Base>*/QString>>();
  /*private*/ MaleSocket* _lastRegisteredBean;
  static /*volatile*/ DefaultDigitalExpressionManager* _instance;// = null;

 protected:
  /*protected*/ MaleDigitalExpressionSocket* castBean(MaleSocket* maleSocket);
  /*protected*/ MaleDigitalExpressionSocket* createMaleExpressionSocket(DigitalExpressionBean* expression);

};

#endif // DEFAULTDIGITALEXPRESSIONMANAGER_H