#ifndef HOLD_H
#define HOLD_H

#include "abstractdigitalexpression.h"
#include "femalesocketlistener.h"

class FemaleDigitalExpressionSocket;
class Hold : public AbstractDigitalExpression, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  Hold(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate() /*throws JmriException */override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  QString getTriggerExpressionSocketSystemName();
  /*public*/  void setTriggerExpressionSocketSystemName(QString systemName);
  /*public*/  QString getHoldActionSocketSystemName();
  /*public*/  void setHoldActionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override{return (QObject*)this;
                           }
 private:
  static Logger* log;
  /*private*/ QString _triggerExpressionSocketSystemName;
  /*private*/ QString _holdExpressionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _triggerExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _holdExpressionSocket;
  /*private*/ bool _isActive = false;

};

#endif // HOLD_H
