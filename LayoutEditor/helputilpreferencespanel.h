#ifndef HELPUTILPREFERENCESPANEL_H
#define HELPUTILPREFERENCESPANEL_H

#include <jpanel.h>
#include "preferencespanel.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "helputilpreferences.h"

class HelpUtilPreferencesPanel : public JPanel, public PreferencesPanel, public InstanceManagerAutoDefault
{
  Q_OBJECT
  Q_INTERFACES(PreferencesPanel InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE HelpUtilPreferencesPanel(QWidget *parent = nullptr);
  ~HelpUtilPreferencesPanel() {}
  HelpUtilPreferencesPanel(const HelpUtilPreferencesPanel&) : JPanel() {}
  /*public*/ QString getPreferencesItem() override;
  /*public*/ QString getPreferencesItemText() override;
  /*public*/ QString getTabbedPreferencesTitle() override;
  /*public*/ QString getLabelKey() override;
  /*public*/ QWidget* getPreferencesComponent() override; //JComponent
  /*public*/ bool isPersistant() override;
  /*public*/ QString getPreferencesTooltip() override;
  /*public*/ void savePreferences() override;
  /*public*/ bool isDirty() override;
  /*public*/ bool isRestartRequired() override;
  /*public*/ bool isPreferencesValid() override;
  QObject* ppself() override {return (QObject*)this;}
  QString className()  override {return "jmrit.util.HelpUtilPreferencesPanel";}
 private:
  /*private*/ /*final*/ HelpUtilPreferences* _preferences;

  QRadioButton* _openHelpOnFileRadioButton;
  QRadioButton* _openHelpOnlineRadioButton;
  QRadioButton* _openHelpOnJMRIWebServerRadioButton;
  QButtonGroup* _openHelpButtonGroup;
  /*private*/ void initGUI();
  /*private*/ bool setValues();
  /*private*/ JPanel* getHelpPanel();

};
Q_DECLARE_METATYPE(HelpUtilPreferencesPanel)
#endif // HELPUTILPREFERENCESPANEL_H
