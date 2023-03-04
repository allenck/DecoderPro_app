#ifndef ACTIONLIGHTINTENSITYSWING_H
#define ACTIONLIGHTINTENSITYSWING_H

#include "abstractdigitalactionswing.h"

class JTabbedPane;
class BeanSelectPanel;
class ActionLightIntensitySwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionLightIntensitySwing(QObject *parent = nullptr);
    ~ActionLightIntensitySwing() {}
    ActionLightIntensitySwing(const ActionLightIntensitySwing&) {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

private:
    /*private*/ JTabbedPane* _tabbedPaneLight;
    /*private*/ BeanSelectPanel/*<VariableLight>*/* lightBeanPanel;
    /*private*/ JPanel* _panelLightDirect;
    /*private*/ JPanel* _panelLightReference;
    /*private*/ JPanel* _panelLightLocalVariable;
    /*private*/ JPanel* _panelLightFormula;
    /*private*/ JTextField* _lightReferenceTextField;
    /*private*/ JTextField* _lightLocalVariableTextField;
    /*private*/ JTextField* _lightFormulaTextField;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(ActionLightIntensitySwing)
#endif // ACTIONLIGHTINTENSITYSWING_H
