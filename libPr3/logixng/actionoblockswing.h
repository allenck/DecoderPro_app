#ifndef ACTIONOBLOCKSWING_H
#define ACTIONOBLOCKSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class BeanSelectPanel;
class JTabbedPane;
class ActionOBlockSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionOBlockSwing(QObject *parent = nullptr);
    ~ActionOBlockSwing() {}
    ActionOBlockSwing(const ActionOBlockSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString() override;
    /*public*/ void dispose()override;

    QObject* sself() override{return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneOBlock;
    /*private*/ BeanSelectPanel/*<OBlock*>*/* _oblockBeanPanel;
    /*private*/ JPanel* _panelOBlockDirect;
    /*private*/ JPanel* _panelOBlockReference;
    /*private*/ JPanel* _panelOBlockLocalVariable;
    /*private*/ JPanel* _panelOBlockFormula;
    /*private*/ JTextField* _oblockReferenceTextField;
    /*private*/ JTextField* _oblockLocalVariableTextField;
    /*private*/ JTextField* _oblockFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperation;
    /*private*/ JComboBox/*<DirectOperation>*/* _stateComboBox;
    /*private*/ JPanel* _panelOperationDirect;
    /*private*/ JPanel* _panelOperationReference;
    /*private*/ JPanel* _panelOperationLocalVariable;
    /*private*/ JPanel* _panelOperationFormula;
    /*private*/ JTextField* _oblockOperReferenceTextField;
    /*private*/ JTextField* _oblockOperLocalVariableTextField;
    /*private*/ JTextField* _oblockOperFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneData;
    /*private*/ JPanel* _panelDataDirect;
    /*private*/ JPanel* _panelDataReference;
    /*private*/ JPanel* _panelDataLocalVariable;
    /*private*/ JPanel* _panelDataFormula;
    /*private*/ JTextField* _oblockDataDirectTextField;
    /*private*/ JTextField* _oblockDataReferenceTextField;
    /*private*/ JTextField* _oblockDataLocalVariableTextField;
    /*private*/ JTextField* _oblockDataFormulaTextField;
    /*private*/ void setDataPanelState();
    /*private*/ void validateBlockSection(QList<QString>* errorMessages);
    /*private*/ void validateOperationSection(QList<QString>* errorMessages) ;
    /*private*/ void validateDataSection(QList<QString>* errorMessages);

protected:
    /*protected*/ void createPanel(/*@CheckForNulll*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionOBlockSwing)
#endif // ACTIONOBLOCKSWING_H
