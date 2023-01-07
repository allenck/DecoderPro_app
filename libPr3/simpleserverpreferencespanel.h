#ifndef SIMPLESERVERPREFERENCESPANEL_H
#define SIMPLESERVERPREFERENCESPANEL_H

#include <jpanel.h>
#include "preferencespanel.h"

class JFrame;
class JSpinner;
class SimpleServerPreferences;
class SimpleServerPreferencesPanel : public JPanel, public PreferencesPanel
{
  Q_OBJECT
  Q_INTERFACES(PreferencesPanel)
 public:
  SimpleServerPreferencesPanel(JPanel* parent = nullptr);
  /*public*/  SimpleServerPreferencesPanel(JFrame* f = nullptr);
  /*public*/  QString getPreferencesItem() override;
  /*public*/  QString getPreferencesItemText() override;
  /*public*/  QString getTabbedPreferencesTitle()override;
  /*public*/  QString getLabelKey() override;
  /*public*/  QWidget* getPreferencesComponent() override;
  /*public*/  bool isPersistant() override;
  /*public*/  QString getPreferencesTooltip() override;
  /*public*/  void savePreferences() override;
  /*public*/  bool isDirty() override;
  /*public*/  bool isRestartRequired() override;
  /*public*/  bool isPreferencesValid() override;
  /*public*/  QString className() override;

  QObject* ppself() override {return (QObject*)this;}

 private:
  /*private*/ JSpinner* port;
  /*private*/ SimpleServerPreferences* preferences;
  /*private*/ JFrame* parentFrame = nullptr;
  void common();
  /*private*/ void initGUI();
  /*private*/ void setGUI();
  /*private*/ bool setValues();
  /*private*/ JPanel* portPanel();

 protected:
  /*protected*/ void applyValues();
  /*protected*/ void cancelValues();

};

#endif // SIMPLESERVERPREFERENCESPANEL_H
