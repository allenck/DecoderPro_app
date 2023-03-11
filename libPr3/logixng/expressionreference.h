#ifndef EXPRESSIONREFERENCE_H
#define EXPRESSIONREFERENCE_H

#include "abstractdigitalexpression.h"
#include "propertychangelistener.h"
#include "is_isnot_enum.h"

class ExpressionReference : public AbstractDigitalExpression, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  Q_INVOKABLE explicit ExpressionReference(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/class PointsTo {
//      Nothing(Bundle.getMessage("ReferencePointsTo_Nothing")),
//      Audio(Bundle.getMessage("ReferencePointsTo_Audio")),
//      Light(Bundle.getMessage("ReferencePointsTo_Light")),
//      Memory(Bundle.getMessage("ReferencePointsTo_Memory")),
//      Sensor(Bundle.getMessage("ReferencePointsTo_Sensor")),
//      SignalHead(Bundle.getMessage("ReferencePointsTo_SignalHead")),
//      SignalMast(Bundle.getMessage("ReferencePointsTo_SignalMast")),
//      Turnout(Bundle.getMessage("ReferencePointsTo_Turnout")),
//      LogixNGTable(Bundle.getMessage("ReferencePointsTo_LogixNGTable"));
      public:
    enum TYPE {Nothing, Audio, Light, Memory, Sensor, SignalHead, SignalMast, Turnout, LogixNGTable};
    /*public*/ static QList<TYPE> values() {return QList<TYPE>{Nothing, Audio, Light, Memory, Sensor, SignalHead, SignalMast, Turnout, LogixNGTable};}
//      /*private*/ /*final*/ String _text;

//      /*private*/ PointsTo(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/ static QString toString(TYPE t) {
          switch(t)
          {
          case Nothing: return tr("Nothing");
          case Audio: return tr("Audio");
          case Light: return tr("Light");
          case Memory: return tr("Memory");
          case Sensor: return tr("Sensor");
          case SignalHead: return tr("SignalHead");
          case SignalMast: return tr("SignalMast");
          case Turnout: return tr("Turnout");
          case LogixNGTable: return tr("LogixNGTable");
          }
      }
      /*public*/ static TYPE valueOf(QString s)
      {
       if(s == tr("Nothing")) return Nothing;
       if(s == tr("Audio")) return Audio;
       if(s == tr("Light")) return Light;
       if(s == tr("Memory")) return Memory;
       if(s == tr("Sensor")) return Sensor;
       if(s == tr("SignalHead")) return SignalHead;
       if(s == tr("SignalMast")) return SignalMast;
       if(s == tr("Turnout")) return Turnout;
       if(s == tr("LogixNGTable")) return LogixNGTable;
       throw new IllegalArgumentException();
      }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException */override;
  /*public*/  void setReference(QString reference);
  /*public*/  QString getReference();
  /*public*/  void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
  /*public*/  Is_IsNot_Enum::VAL get_Is_IsNot() ;
  /*public*/  void setPointsTo(ExpressionReference::PointsTo::TYPE pointsTo);
  /*public*/  ExpressionReference::PointsTo::TYPE getPointsTo();
  /*public*/  Category getCategory()override;
  /*public*/  bool evaluate()override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  QObject* self() override {return (QObject*)this;}

  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}

 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ QString _reference;
  /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
  /*private*/ PointsTo::TYPE _pointsTo = PointsTo::Nothing;

};

#endif // EXPRESSIONREFERENCE_H
