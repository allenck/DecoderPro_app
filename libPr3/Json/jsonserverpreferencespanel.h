#ifndef JSONSERVERPREFERENCESPANEL_H
#define JSONSERVERPREFERENCESPANEL_H
#include "preferencespanel.h"

class QSpinBox;
class QPushButton;
class JsonServerPreferences;
class JsonServerPreferencesPanel : public PreferencesPanel
{
 Q_OBJECT
public:
 JsonServerPreferencesPanel(QWidget* parent = 0);
 /*public*/ static /*final*/ int MAX_HEARTBEAT_INTERVAL;// = 3600;
 /*public*/ static /*final*/ int MIN_HEARTBEAT_INTERVAL;// = 1;
 /*public*/ JsonServerPreferencesPanel(JFrame* f, QWidget* parent = 0);
 /*public*/ void enableSave();
 /*public*/ QString getPreferencesItem();
 /*public*/ QString getPreferencesItemText();
 /*public*/ QString getTabbedPreferencesTitle();
 /*public*/ QString getLabelKey();
 /*public*/ QWidget* getPreferencesComponent();
 /*public*/ bool isPersistant();
 /*public*/ QString getPreferencesTooltip();
 /*public*/ void savePreferences();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();
 /*public*/ bool isPreferencesValid();


private:
 /*private*/ QSpinBox* heartbeatIntervalSpinner;
 /*private*/ QSpinBox* port;
 /*private*/ QPushButton* btnSave;
 /*private*/ QPushButton* btnCancel;
 /*private*/ JsonServerPreferences* preferences;
 /*private*/ JFrame* parentFrame;// = NULL;
 /*private*/ void initGUI();
 /*private*/ void setGUI();
 /*private*/ QWidget* heartbeatPanel();
 /*private*/ QWidget* portPanel();

private slots:
 /*private*/ bool setValues();

protected:
 /*protected*/ void applyValues() ;
 /*protected*/ void cancelValues();

};

#endif // JSONSERVERPREFERENCESPANEL_H
