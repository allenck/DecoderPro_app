#ifndef EXPRESSIONSIGNALMASTSWING_H
#define EXPRESSIONSIGNALMASTSWING_H

#include "abstractdigitalexpressionswing.h"

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
    /*private*/ JTabbedPane* _tabbedPaneSignalMast;
    /*private*/ BeanSelectPanel/*<SignalMast>*/* _signalMastBeanPanel;
    /*private*/ JPanel* _panelSignalMastDirect;
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

};
Q_DECLARE_METATYPE(ExpressionSignalMastSwing)
#endif // EXPRESSIONSIGNALMASTSWING_H
