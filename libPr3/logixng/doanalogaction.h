#ifndef DOANALOGACTION_H
#define DOANALOGACTION_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"

class FemaleAnalogExpressionSocket;
class FemaleAnalogActionSocket;
class DoAnalogAction : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit DoAnalogAction(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException */override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() /*throws JmriException*/ override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleAnalogActionSocket* getAnalogActionSocket();
  /*public*/  QString getAnalogActionSocketSystemName();
  /*public*/  void setAnalogActionSocketSystemName(QString systemName);
  /*public*/  FemaleAnalogExpressionSocket* getAnalogExpressionSocket() ;
  /*public*/  QString getAnalogExpressionSocketSystemName() ;
  /*public*/  void setAnalogExpressionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ QString _analogExpressionSocketSystemName;
  /*private*/ QString _analogActionSocketSystemName;
  /*private*/ /*final*/ FemaleAnalogExpressionSocket* _analogExpressionSocket;
  /*private*/ /*final*/ FemaleAnalogActionSocket* _analogActionSocket;

};

#endif // DOANALOGACTION_H
