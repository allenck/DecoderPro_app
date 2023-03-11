#ifndef ACTIONWARRANTSWING_H
#define ACTIONWARRANTSWING_H

#include "abstractdigitalactionswing.h"

class BeanSelectPanel;
class JTabbedPane;
class JComboBox;
class ActionWarrantSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionWarrantSwing(QObject *parent = nullptr);
    ~ActionWarrantSwing() {}
    ActionWarrantSwing(const ActionWarrantSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

private:
    /*private*/ JTabbedPane* _tabbedPaneWarrant;
    /*private*/ BeanSelectPanel/*<Warrant>*/* _warrantBeanPanel;
    /*private*/ JPanel* _panelWarrantDirect;
    /*private*/ JPanel* _panelWarrantReference;
    /*private*/ JPanel* _panelWarrantLocalVariable;
    /*private*/ JPanel* _panelWarrantFormula;
    /*private*/ JTextField* _warrantReferenceTextField;
    /*private*/ JTextField* _warrantLocalVariableTextField;
    /*private*/ JTextField* _warrantFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperation;
    /*private*/ JComboBox/*<DirectOperation>*/* _stateComboBox;
    /*private*/ JPanel* _panelOperationDirect;
    /*private*/ JPanel* _panelOperationReference;
    /*private*/ JPanel* _panelOperationLocalVariable;
    /*private*/ JPanel* _panelOperationFormula;
    /*private*/ JTextField* _warrantOperReferenceTextField;
    /*private*/ JTextField* _warrantOperLocalVariableTextField;
    /*private*/ JTextField* _warrantOperFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneData;
    /*private*/ JPanel* _panelDataDirect;
    /*private*/ JPanel* _panelDataReference;
    /*private*/ JPanel* _panelDataLocalVariable;
    /*private*/ JPanel* _panelDataFormula;
    /*private*/ JTextField* _warrantDataReferenceTextField;
    /*private*/ JTextField* _warrantDataLocalVariableTextField;
    /*private*/ JTextField* _warrantDataFormulaTextField;

    /*private*/ JPanel* _panelControlTrainCombo;
    /*private*/ JTextField* _trainIdNameTextField;
    /*private*/ JComboBox/*<ControlAutoTrain>*/* _controlTrainComboBox;
    /*private*/ void setDataPanelState();
    /*private*/ void validateWarrantSection(QList<QString>* errorMessages);
    /*private*/ void validateOperationSection(QList<QString>* errorMessages) ;
    /*private*/ void validateDataSection(QList<QString>* errorMessages) ;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionWarrantSwing)
#endif // ACTIONWARRANTSWING_H
