#ifndef IFTHENELSE_H
#define IFTHENELSE_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"

class FemaleDigitalExpressionSocket;
class FemaleDigitalActionSocket;
class IfThenElse : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  /*private*/ /*static*/ enum TriState {
      Unknown,
      False,
      True

//      /*public*/  static TriState getValue(bool value) {
//          return value ? True : False;
//      }
  };
 public:
  /**
   * The type of Action. If the type is changed, the action is aborted if it
   * is currently running.
   */
  /*public*/ class Type {
   public:
    enum ETYPE {
      /**
       * The "then" or "else" action is executed when the expression changes
       * its result. If the expression has returned "false", but now returns
       * "true", the "then" action is executed. If the expression has
       * returned "true", but now returns "false", the "else" action is executed.
       */
      ExecuteOnChange/*(Bundle.getMessage("IfThenElse_ExecuteOnChange"))*/,

      /**
       * The "then" or "else" action is always executed when this action is
       * executed. If the expression returns "true", the "then" action is
       * executed. If the expression returns "false", the "else" action is
       * executed.
       */
      AlwaysExecute/*(Bundle.getMessage("IfThenElse_AlwaysExecute"));*/
    };
//      private final String _text;

//      private Type(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/ static QString toString(ETYPE t) {
          switch(t)
          {
          case ExecuteOnChange:
          return tr("Execute on change");
          case AlwaysExecute:
           return tr("Always execute");
          default:
           break;
          }
          return "?";
      }
     static QList<ETYPE> values()
    {
     return QList<ETYPE> {ExecuteOnChange, AlwaysExecute};
    }
    /*public*/ static ETYPE valueOf(QString s)
     {
      if(s== tr("Execute on change"))return ExecuteOnChange;
      if(s==tr("Always execute")) return AlwaysExecute;
      throw new IllegalArgumentException();
     }

    friend class IfThenElse;
  };
  explicit IfThenElse(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException */override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  Type::ETYPE getType();
  /*public*/  void setType(Type::ETYPE type);
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount() override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalExpressionSocket* getIfExpressionSocket();
  /*public*/  QString getIfExpressionSocketSystemName();
  /*public*/  void setIfExpressionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalActionSocket* getThenActionSocket();
  /*public*/  QString getThenActionSocketSystemName();
  /*public*/  void setThenActionSocketSystemName(QString systemName);
  /*public*/  FemaleDigitalActionSocket* getElseActionSocket();
  /*public*/  QString getElseActionSocketSystemName() ;
  /*public*/  void setElseActionSocketSystemName(QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override{return(QObject*)this;}
  QObject* bself() override{return(QObject*)this;}



 private:
  static Logger* log;
  /*private*/ Type::ETYPE _type = Type::ETYPE::ExecuteOnChange;
  /*private*/ TriState _lastExpressionResult = TriState::Unknown;
  /*private*/ QString _ifExpressionSocketSystemName;
  /*private*/ QString _thenActionSocketSystemName;
  /*private*/ QString _elseActionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _ifExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _thenActionSocket;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _elseActionSocket;

};

#endif // IFTHENELSE_H
