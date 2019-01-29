#ifndef LNTCPPREFERENCESPANEL_H
#define LNTCPPREFERENCESPANEL_H
#include "preferencespanel.h"
#include "QSpinBox"
#include <QLabel>
#include "../libPr3/loconet/LnOverTcp/lntcppreferences.h"
#include <QCheckBox>
#include "itemlistener.h"


class LnTcpPreferencesPanel : public QWidget, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
 Q_INVOKABLE LnTcpPreferencesPanel(QWidget* parent = nullptr);
 ~LnTcpPreferencesPanel() {}
 LnTcpPreferencesPanel(const LnTcpPreferencesPanel&) : QWidget() {}
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey() ;
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant();
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired() ;
 /*public*/ virtual bool isPreferencesValid();
 /*public*/ QString className();


public slots:
 void on_startup_clicked();

private:
 /*private*/ QSpinBox* port;
 /*private*/ QLabel* portLabel;
 /*private*/ /*final*/ LnTcpPreferences* preferences;
 /*private*/ QCheckBox* startup;
 /*private*/ ItemListener* startupItemListener;
 /*private*/ int startupActionPosition = -1;
// /*private*/ BindingGroup bindingGroup;
 /*private*/ void initComponents();
 /*private*/ bool isStartupAction();

};
Q_DECLARE_METATYPE(LnTcpPreferencesPanel)

class LnTcpStartupItemListener : public ItemListener
{
 Q_OBJECT
 LnTcpPreferencesPanel* panel;

};
#endif // LNTCPPREFERENCESPANEL_H
