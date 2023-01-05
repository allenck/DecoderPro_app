#ifndef WEBSERVERPREFERENCESPANEL_H
#define WEBSERVERPREFERENCESPANEL_H
#include "preferencespanel.h"
#include "itemlistener.h"
#include "jpanel.h"

class QLabel;
class QSpinBox;
class QCheckBox;
class ItemListener;
class BindingGroup;
class WebServerPreferences;
class WebServerPreferencesPanel : public JPanel, public PreferencesPanel
{
 Q_OBJECT
 Q_INTERFACES(PreferencesPanel)

public:
 Q_INVOKABLE WebServerPreferencesPanel(QWidget* parent = 0);
 ~WebServerPreferencesPanel(){}
 WebServerPreferencesPanel(const WebServerPreferencesPanel&) : JPanel() {}
 /*public*/ QString getPreferencesItem() ;
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey() ;
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant() ;
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired() ;
 /*public*/ bool isPreferencesValid();
 /*public*/ int getSortOrder();
 /*public*/ QString className();
 /*public*/ QObject* self() {return (QObject*)this;}


public slots:
 void on_readonlyPower_checked(bool);
 void on_webSeverStartupOption( bool checked);


private:
 /*private*/ QSpinBox* port;
 /*private*/ QCheckBox* readonlyPower;
 /*private*/ QLabel* portLabel;
 /*private*/ /*final*/ WebServerPreferences* preferences;
 /*private*/ QCheckBox* startup;
 /*private*/ ItemListener* startupItemListener;
 /*private*/ int startupActionPosition;// = -1;
 /*private*/ BindingGroup* bindingGroup;
 /*private*/ void initComponents();
  /*private*/ bool isStartupAction();

};

Q_DECLARE_METATYPE(WebServerPreferencesPanel)
#endif // WEBSERVERPREFERENCESPANEL_H
