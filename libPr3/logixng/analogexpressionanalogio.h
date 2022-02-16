#ifndef ANALOGEXPRESSIONANALOGIO_H
#define ANALOGEXPRESSIONANALOGIO_H
#include "abstractanalogexpression.h"
#include "propertychangelistener.h"
#include "vetoablechangelistener.h"
#include "namedbeanhandle.h"
#include "category.h"

class Logger;
class AnalogIO;
class AnalogExpressionAnalogIO : public AbstractAnalogExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  AnalogExpressionAnalogIO(QString sys, QString user, QObject* parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/override;
  /*public*/  Category::TYPE getCategory()override ;
  /*public*/  void setAnalogIO(/*@Nonnull*/ QString analogIOName) ;
  /*public*/  void setAnalogIO(/*@Nonnull*/ NamedBeanHandle<AnalogIO*>* handle);
  /*public*/  void setAnalogIO(/*@Nonnull*/ AnalogIO* analogIO);
  /*public*/  void removeAnalogIO();
  /*public*/  NamedBeanHandle<AnalogIO*>* getAnalogIO();
  /*public*/  double evaluate()override;
  /*public*/  FemaleSocket* getChild(int index)
          /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override;
  QObject* self() override{return (QObject*)this;}
  QString getUserName()const override {return AbstractBase::getUserName();}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt) override;

 private:
  /*private*/ NamedBeanHandle<AnalogIO*>* _analogIOHandle;
 static Logger* log;
 protected:
};

#endif // ANALOGEXPRESSIONANALOGIO_H
