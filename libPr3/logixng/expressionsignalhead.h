#ifndef EXPRESSIONSIGNALHEAD_H
#define EXPRESSIONSIGNALHEAD_H

#include "abstractdigitalexpression.h"
#include "propertychangelistener.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "namedbeanhandle.h"
#include "signalhead.h"
#include "expressionnode.h"

class QueryType;
class ExpressionSignalHead : public AbstractDigitalExpression, public PropertyChangeListener, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener VetoableChangeListener)
 public:
  ExpressionSignalHead(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  class QueryType {
//      Appearance(Bundle.getMessage("SignalHeadQueryType_Appearance")),
//      NotAppearance(Bundle.getMessage("SignalHeadQueryType_NotAppearance")),
//      Lit(Bundle.getMessage("SignalHeadQueryType_Lit")),
//      NotLit(Bundle.getMessage("SignalHeadQueryType_NotLit")),
//      Held(Bundle.getMessage("SignalHeadQueryType_Held")),
//      NotHeld(Bundle.getMessage("SignalHeadQueryType_NotHeld"));
   public:
    enum TYPE {Appearance, NotAppearance, Lit, NotLit, Held, NotHeld};
    /*public*/  static QList<TYPE> values()
    {
     return QList<TYPE>{Appearance, NotAppearance, Lit, NotLit, Held, NotHeld};
    }

//      /*private*/ final String _text;

//      /*private*/ QueryType(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/  static QString toString(TYPE t) {
       switch (t) {
       case Appearance: return tr("has appearance");
       case NotAppearance: return tr("has not appearence");
       case Lit: return tr("is lit");
       case NotLit: return tr("is not lit");
       case Held: return tr("is held");
        case NotHeld: return tr("is not held");
       }
       throw new IllegalArgumentException();
      }
    /*public*/ static TYPE valueOf(QString s)
    {
     if(s ==tr("has appearance") ) return Appearance;
     if(s ==tr("has not appearence")) return NotAppearance;
     if(s == tr("is lit")) return Lit;
     if(s ==tr("is not lit")) return NotLit;
     if(s ==tr("is held")) return Held;
     if(s ==tr("is not held")) return NotHeld;
     throw new IllegalArgumentException();
    }

  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setSignalHead(/*@Nonnull*/ QString signalHeadName);
  /*public*/  void setSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle) ;
  /*public*/  void setSignalHead(/*@Nonnull*/ SignalHead* signalHead);
  /*public*/  void removeSignalHead();
  /*public*/  NamedBeanHandle<SignalHead*>* getSignalHead();
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ QString signalHeadName);
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ NamedBeanHandle<SignalHead*>* handle);
  /*public*/  void setExampleSignalHead(/*@Nonnull*/ SignalHead* signalHead) ;
  /*public*/  void removeExampleSignalHead();
  /*public*/  NamedBeanHandle<SignalHead*>* getExampleSignalHead();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing() ;
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference() ;
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable() ;
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula();
  /*public*/  void setQueryAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getQueryAddressing() ;
  /*public*/  void setQueryType(QueryType::TYPE queryType) ;
  /*public*/  QueryType::TYPE getQueryType() ;
  /*public*/  void setQueryReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getQueryReference();
  /*public*/  void setQueryLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getQueryLocalVariable();
  /*public*/  void setQueryFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getQueryFormula();
  /*public*/  void setAppearanceAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAppearanceAddressing();
  /*public*/  void setAppearance(int appearance);
  /*public*/  int getAppearance();
  /*public*/  void setAppearanceReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getAppearanceReference();
  /*public*/  void setAppearanceLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getAppearanceLocalVariable();
  /*public*/  void setAppearanceFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getAppearanceFormula();
  /*public*/  Category getCategory() override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override;

  QObject* bself() override {return (QObject*)this;}
  QObject* pself() override {return (QObject*)this;}
  /*public*/ virtual void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
   AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
  }
  /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                    QString name, QString listenerRef) override {
   AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
  }
  /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
  ///*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
  /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
  /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
  /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
  /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
   return AbstractNamedBean::getPropertyChangeListenersByReference(name);
  }
  void addPropertyChangeListener(PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(l);}


 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<SignalHead*>* _signalHeadHandle = nullptr;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;

  /*private*/ NamedBeanAddressing::TYPE _queryAddressing = NamedBeanAddressing::Direct;
  /*private*/ QueryType::TYPE _queryType = QueryType::Appearance;
  /*private*/ QString _queryReference = "";
  /*private*/ QString _queryLocalVariable = "";
  /*private*/ QString _queryFormula = "";
  /*private*/ ExpressionNode* _queryExpressionNode;

  /*private*/ NamedBeanAddressing::TYPE _appearanceAddressing = NamedBeanAddressing::Direct;
  /*private*/ int _signalHeadAppearance = SignalHead::DARK;
  /*private*/ QString _appearanceReference = "";
  /*private*/ QString _appearanceLocalVariable = "";
  /*private*/ QString _appearanceFormula = "";
  /*private*/ ExpressionNode* _appearanceExpressionNode;

  /*private*/ NamedBeanHandle<SignalHead*>* _exampleSignalHeadHandle = nullptr;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseQueryFormula() /*throws ParserException*/ ;
  /*private*/ void parseAppearanceFormula() /*throws ParserException*/;
  /*private*/ int getAppearanceFromName(QString name);
  /*private*/ int getNewAppearance() /*throws JmriException*/ ;
  /*private*/ QueryType::TYPE getQuery() /*throws JmriException*/;


};

#endif // EXPRESSIONSIGNALHEAD_H
