#ifndef ENABLELOGIXSWING_H
#define ENABLELOGIXSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class BeanSelectPanel;
class JTabbedPane;
class EnableLogixSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit EnableLogixSwing(QObject *parent = nullptr);
    ~EnableLogixSwing() {}
    EnableLogixSwing(const EnableLogixSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString() override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}

private:
    /*private*/ JTabbedPane* _tabbedPaneLogix;
    /*private*/ BeanSelectPanel/*<Logix>*/* logixBeanPanel;
    /*private*/ JPanel* _panelLogixDirect;
    /*private*/ JPanel* _panelLogixReference;
    /*private*/ JPanel* _panelLogixLocalVariable;
    /*private*/ JPanel* _panelLogixFormula;
    /*private*/ JTextField* _logixReferenceTextField;
    /*private*/ JTextField* _logixLocalVariableTextField;
    /*private*/ JTextField* _logixFormulaTextField;

    /*private*/ JTabbedPane* _tabbedPaneOperation;
    /*private*/ JComboBox/*<Operation>*/* _stateComboBox;
    /*private*/ JPanel* _panelOperationDirect;
    /*private*/ JPanel* _panelOperationReference;
    /*private*/ JPanel* _panelOperationLocalVariable;
    /*private*/ JPanel* _panelOperationFormula;
    /*private*/ JTextField* _logixLockReferenceTextField;
    /*private*/ JTextField* _logixLockLocalVariableTextField;
    /*private*/ JTextField* _logixLockFormulaTextField;


protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(EnableLogixSwing)
#endif // ENABLELOGIXSWING_H
