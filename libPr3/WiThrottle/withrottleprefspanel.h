#ifndef WITHROTTLEPREFSPANEL_H
#define WITHROTTLEPREFSPANEL_H
#include "preferencespanel.h"

class ItemListener;
class WiThrottlePreferences;
class QSpinBox;
class QRadioButton;
class QCheckBox;
class WiThrottlePrefsPanel : public PreferencesPanel
{
public:
 WiThrottlePrefsPanel(QWidget* parent = 0);
 ~WiThrottlePrefsPanel() {}
 WiThrottlePrefsPanel(const WiThrottlePrefsPanel&) : PreferencesPanel() {}
 /*public*/ WiThrottlePrefsPanel(JFrame* f, QWidget* parent = 0);
 /*public*/ void initGUI();
 /*public*/ void storeValues();
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey();
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant();
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired() ;
 /*public*/ bool isPreferencesValid();


private:
 void common();
 QCheckBox* eStopCB;
 QSpinBox* delaySpinner;

 QCheckBox* momF2CB;

 QSpinBox* port;

 QCheckBox* powerCB;
 QCheckBox* turnoutCB;
 QCheckBox* routeCB;
 QCheckBox* consistCB;
 QCheckBox* startupCB;
 ItemListener* startupItemListener;
 int startupActionPosition;// = -1;
 QRadioButton* wifiRB;
 QRadioButton* dccRB;

 WiThrottlePreferences* localPrefs;
 JFrame* parentFrame;// = NULL;
 /*private*/ void setGUI();
 /*private*/ bool setValues();
 /*private*/ QWidget* eStopDelayPanel();
 /*private*/ QWidget* functionsPanel();
 /*private*/ QWidget* socketPortPanel();
 /*private*/ QWidget* allowedControllers();
 /*private*/ bool isStartUpAction();

protected:
 /*protected*/ void cancelValues();

};
Q_DECLARE_METATYPE(WiThrottlePrefsPanel)
#endif // WITHROTTLEPREFSPANEL_H
