#ifndef ACTIONPOSITIONABLE_H
#define ACTIONPOSITIONABLE_H

#include "abstractdigitalaction.h"
#include "editor.h"
#include "namedbeanaddressing.h"
#include "expressionnode.h"
#include "threadingutil.h"


class ActionPositionable : public AbstractDigitalAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit ActionPositionable( QObject *parent = nullptr) : AbstractDigitalAction(parent) {}
  ActionPositionable(QString sys, QString user, QObject *parent = nullptr);
  ~ActionPositionable(){}
  ActionPositionable(const ActionPositionable&) : AbstractDigitalAction() {}
  class Operation
  {
    //Q_OBJECT
   public:
    enum TYPE {Disable, Enable, Hide, Show, None};
    static QString toString(TYPE t){
     switch(t)
     {
      case Disable: return "Disable";
      case Enable: return "Enable";
      case Hide: return "Hide";
      case Show: return "Show";
    }
    return tr("None");
   }
    static TYPE valueOf(QString s)
    {
     if(s == "Disable") return Disable;
     if(s == "Enable") return Enable;
     if(s == "Hide") return Hide;
     if(s == "Show") return Show;
     return None;
    }
   static QList<QString> values () {return QList<QString> {"Disable", "Enable", "Hide", "Show"}; }
  };
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws ParserException*/override;
  /*public*/  void setEditor(/*@CheckForNull*/ QString editorName);
  /*public*/  QString getEditorName();
  /*public*/  void setPositionable(/*@CheckForNull*/ QString positionableName);
  /*public*/  QString getPositionableName();
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getLocalVariable();
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */;
  /*public*/  QString getFormula();
  /*public*/  void setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ ;
  /*public*/  NamedBeanAddressing::TYPE getStateAddressing();
  /*public*/  void setOperation(Operation::TYPE isControlling);
  /*public*/  Operation::TYPE getOperation();
  /*public*/  void setStateReference(/*@Nonnull*/ QString reference);
  /*public*/  QString getStateReference() ;
  /*public*/  void setStateLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getStateLocalVariable();
  /*public*/  void setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ ;
  /*public*/  QString getStateFormula();
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException */override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute()/* throws JmriException*/ override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}
  QObject* self() override {return (QObject*)this;}

//  void addPropertyChangeListener(PropertyChangeListener* l) override {Base::addPropertyChangeListener(l);}
//  void addPropertyChangeListener(QString propertyName, PropertyChangeListener* l) override {AbstractNamedBean::addPropertyChangeListener(propertyName, l);}

 private:
  static Logger* log;
  /*private*/ QString _editorName;
  /*private*/ Editor* _editor;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
//    /*private*/ NamedBeanHandle<Turnout> _turnoutHandle;
  /*private*/ QString _positionableName;
  /*private*/ Positionable* _positionable;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ Operation::TYPE _operation = Operation::Enable;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ void parseFormula() /*throws ParserException*/;
  /*private*/ void parseStateFormula() /*throws ParserException override*/;
  /*private*/ QString getNewState() /*throws JmriException */;

};
class MyThreadAction : public ThreadAction
{
  Q_OBJECT
  ActionPositionable* ap;
  ActionPositionable::Operation::TYPE operation;
  Positionable* positionable;
 public:
  MyThreadAction(ActionPositionable::Operation::TYPE operation, Positionable* positionablem, ActionPositionable* ap) {
   this->operation = operation;
   this->positionable = positionable;
   this->ap = ap;
  }
  void run();
};

#endif // ACTIONPOSITIONABLE_H
