#ifndef TIMESINCEMIDNIGHT_H
#define TIMESINCEMIDNIGHT_H

#include "abstractanalogexpression.h"
#include "timebase.h"
#include "timertask.h"

class TimeSinceMidnight : public AbstractAnalogExpression, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  class Type
  {

   public:
    enum TYPE {FastClock, SystemClock};
    static QString toString(TYPE t)
    {
     if(t == FastClock) return tr("Fast Clock");
     return tr("System Clock");
    }
    static QList<TYPE> values;// {FastClock, SystemClock};
    static TYPE getType(QString s)
    {
     if(s == tr("Fast Clock")) return FastClock;
     return SystemClock;
    }
  };

  explicit TimeSinceMidnight(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  Category getCategory()override;
  /*public*/  void setType(Type::TYPE type);
  /*public*/  Type::TYPE getType();
  /*public*/  double evaluate()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}
  QObject* self() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;


 private:
  static Logger* log;
  /*private*/ Type::TYPE _type = Type::FastClock;
  /*private*/ Timebase* _fastClock;

  TimerTask* timerTask = nullptr;
  /*private*/ /*final*/ int millisInAMinute = 60000;
  /*private*/ void scheduleTimer();

};

#endif // TIMESINCEMIDNIGHT_H
