#ifndef EXPRESSIONSIGNALMASTSWING_H
#define EXPRESSIONSIGNALMASTSWING_H

#include "abstractdigitalexpressionswing.h"
#include "threadingutil.h"

class ExpressionSignalMast;
class JComboBox;
class BeanSelectPanel;
class JTabbedPane;
class ExpressionSignalMastSwing : public AbstractDigitalExpressionSwing
{
    Q_OBJECT
public:
     Q_INVOKABLE explicit ExpressionSignalMastSwing(QObject *parent = nullptr);
    ~ExpressionSignalMastSwing() {}
    ExpressionSignalMastSwing(const ExpressionSignalMastSwing&) : AbstractDigitalExpressionSwing() {}
    /*public*/ static /*final*/ int NUM_COLUMNS_TEXT_FIELDS;// = 20;
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

    QObject* sself() override{return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneSignalMast = nullptr;
    /*private*/ BeanSelectPanel/*<SignalMast>*/* _signalMastBeanPanel = nullptr;
    /*private*/ JPanel* _panelSignalMastDirect = nullptr;
    /*private*/ JPanel* _panelSignalMastReference;
    /*private*/ JPanel* _panelSignalMastLocalVariable;
    /*private*/ JPanel* _panelSignalMastFormula;
    /*private*/ JTextField* _signalMastReferenceTextField;
    /*private*/ JTextField* _signalMastLocalVariableTextField;
    /*private*/ JTextField* _signalMastFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneQueryType;
    /*private*/ JPanel* _panelQueryTypeDirect;
    /*private*/ JPanel* _panelQueryTypeReference;
    /*private*/ JPanel* _panelQueryTypeLocalVariable;
    /*private*/ JPanel* _panelQueryTypeFormula;

    /*private*/ JComboBox/*<ExpressionSignalMast.QueryType>*/* _operationComboBox;
    /*private*/ JTextField* _signalMastQueryReferenceTextField;
    /*private*/ JTextField* _signalMastQueryLocalVariableTextField;
    /*private*/ JTextField* _signalMastQueryFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneAspectType;
    /*private*/ JPanel* _panelAspectTypeDirect;
    /*private*/ JPanel* _panelAspectTypeReference;
    /*private*/ JPanel* _panelAspectTypeLocalVariable;
    /*private*/ JPanel* _panelAspectTypeFormula;

    /*private*/ JComboBox* _signalMastAspectComboBox;
    /*private*/ JTextField* _signalMastAspectReferenceTextField;
    /*private*/ JTextField* _signalMastAspectLocalVariableTextField;
    /*private*/ JTextField* _signalMastAspectFormulaTextField;

    /*private*/ BeanSelectPanel/*<SignalMast>*/* _exampleSignalMastBeanPanel;
    /*private*/ void setGuiEnabledStates();
    /*private*/ void setAspectComboBox(ExpressionSignalMast* expression);

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

    friend class ESMS_ThreadingUtil;
};
Q_DECLARE_METATYPE(ExpressionSignalMastSwing)

class ESMS_ThreadingUtil : public ThreadAction
{
  Q_OBJECT
  ExpressionSignalMast* expression;
  ExpressionSignalMastSwing* esms;
 public:
  ESMS_ThreadingUtil(ExpressionSignalMast* expression, ExpressionSignalMastSwing* esms){
   this->expression = expression;
   this->esms = esms;
  }
  void run()
  {
   esms->setAspectComboBox(expression);
  }
};
#endif // EXPRESSIONSIGNALMASTSWING_H