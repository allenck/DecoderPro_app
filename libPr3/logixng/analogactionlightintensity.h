#ifndef ANALOGACTIONLIGHTINTENSITY_H
#define ANALOGACTIONLIGHTINTENSITY_H

#include "abstractanalogaction.h"
#include "vetoablechangelistener.h"
#include "namedbeanaddressing.h"
#include "variablelight.h"
#include "expressionnode.h"
class AnalogActionLightIntensity : public AbstractAnalogAction, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  explicit AnalogActionLightIntensity(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  static /*final*/ int INTENSITY_SOCKET;// = 0;
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  void setLight(/*@Nonnull*/ QString lightName) ;
  /*public*/  void setLight(/*@Nonnull*/ NamedBeanHandle<VariableLight*>* handle);
  /*public*/  void setLight(/*@Nonnull*/ VariableLight* light) ;
  /*public*/  void removeLight();
  /*public*/  NamedBeanHandle<VariableLight*>* getLight() ;
  /*public*/  void setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getAddressing();
  /*public*/  void setReference(/*@Nonnull*/ QString reference) ;
  /*public*/  QString getReference();
  /*public*/  void setLocalVariable(/*@Nonnull*/ QString localVariable) ;
  /*public*/  QString getLocalVariable() ;
  /*public*/  void setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getFormula() ;
  /*public*/  Category* getCategory()override;
  /*public*/  void setValue(double value) /*throws JmriException*/ override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount() override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}

 public slots:
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/override;

 private:
  static Logger* log;
  /*private*/ NamedBeanAddressing::TYPE _addressing = NamedBeanAddressing::Direct;
  /*private*/ NamedBeanHandle<VariableLight*>* _lightHandle;
  /*private*/ QString _reference = "";
  /*private*/ QString _localVariable = "";
  /*private*/ QString _formula = "";
  /*private*/ ExpressionNode* _expressionNode;
  /*private*/ void parseFormula() /*throws ParserException*/;


 protected:

};

#endif // ANALOGACTIONLIGHTINTENSITY_H
