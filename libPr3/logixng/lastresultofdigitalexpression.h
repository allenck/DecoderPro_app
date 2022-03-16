#ifndef LASTRESULTOFDIGITALEXPRESSION_H
#define LASTRESULTOFDIGITALEXPRESSION_H

#include "abstractdigitalexpression.h"
#include "namedbeanhandle.h"
#include "vetoablechangelistener.h"

class LastResultOfDigitalExpression : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  explicit LastResultOfDigitalExpression(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)override;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ QString digitalExpressionName) ;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ NamedBeanHandle<DigitalExpressionBean*>* handle) ;
  /*public*/  void setDigitalExpression(/*@Nonnull*/ DigitalExpressionBean* digitalExpression);
  /*public*/  void removeDigitalExpression() ;
  /*public*/  NamedBeanHandle<DigitalExpressionBean*>* getDigitalExpression();
  /*public*/  Category* getCategory()override;
  /*public*/  bool evaluate() override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ override;

 private:
  static Logger* log;
  /*private*/ NamedBeanHandle<DigitalExpressionBean*>* _digitalExpressionHandle = nullptr;

};

#endif // LASTRESULTOFDIGITALEXPRESSION_H