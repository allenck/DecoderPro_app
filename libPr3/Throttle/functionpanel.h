#ifndef FUNCTIONPANEL_H
#define FUNCTIONPANEL_H

#include <QDockWidget>
#include "logger.h"
#include "addresslistener.h"
namespace Ui {
class FunctionPanel;
}

class QDomElement;
class LocoAddress;
class PropertyChangeEvent;
class RosterEntry;
class DccThrottle;
class FunctionButton;
class AddressPanel;
class JToggleButton;
class FunctionPanel : public QDockWidget, public AddressListener
{
    Q_OBJECT
    Q_INTERFACES(AddressListener)
public:
    explicit FunctionPanel(QWidget *parent = 0);
    ~FunctionPanel();
    /*public*/ static /*final*/ int NUM_FUNCTION_BUTTONS;// = 29;
    /*public*/ static /*final*/ int NUM_FUNC_BUTTONS_INIT;// = 16;	//only show 16 function buttons at start
    /*public*/ void destroy();
    /*public*/ QList<FunctionButton*> getFunctionButtons();
    /*public*/ void setEnabled(bool isEnabled);
    /*public*/ void setEnabled();
    /*public*/ void setAddressPanel(AddressPanel* addressPanel);
    /*public*/ void saveFunctionButtonsToRoster (RosterEntry* rosterEntry);
    /*public*/ void resetFnButtons();
    /*public*/ void keyPressEvent(QKeyEvent* e);
    /*public*/ void keyReleaseEvent(QKeyEvent* e);
    /*public*/ QDomElement getXml();
    /*public*/ void setXml(QDomElement e);
    QObject* self() {return (QObject*)this;}

public slots:
    /*public*/ void notifyFunctionStateChanged(int functionNumber, bool isSet);
    /*public*/ void notifyFunctionLockableChanged(int functionNumber, bool isLockable);
    /*public*/ void buttonActionCmdPerformed();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
    /*public*/ void notifyAddressReleased(LocoAddress* la);
    /*public*/ void notifyAddressChosen(LocoAddress* l);
    /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
    /*public*/ void notifyConsistAddressReleased(int address, bool isLong) ;
    /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);

private:
    Ui::FunctionPanel *ui;
    /*private*/ DccThrottle* mThrottle;

    /*private*/	QWidget* mainPanel;
    /*private*/ QList<FunctionButton*> functionButton;
    /*private*/ JToggleButton* alt1Button;// = new JToggleButton();
    /*private*/ JToggleButton* alt2Button;// = new JToggleButton();

    /*private*/ AddressPanel* addressPanel;// = NULL; // to access roster infos
    Logger* log;
    /*private*/ void setFnButtons();
    /*private*/ bool keyReleased;// = true;
    /*private*/ void initGUI();

    friend class LearnFunctionPanel;
};

#endif // FUNCTIONPANEL_H
