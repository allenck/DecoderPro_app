#ifndef RAILROADNAMEPREFERENCESPANEL_H
#define RAILROADNAMEPREFERENCESPANEL_H

#include "preferencespanel.h"
#include "libpref_global.h"

class WebServerPreferences;
class JFrame;
class QPushButton;
class JTextField;
class LIBPREFSHARED_EXPORT RailroadNamePreferencesPanel : public PreferencesPanel
{
    Q_OBJECT
public:
    explicit RailroadNamePreferencesPanel(QWidget *parent = 0);
    ~RailroadNamePreferencesPanel() {}
    RailroadNamePreferencesPanel(const RailroadNamePreferencesPanel&) : PreferencesPanel() {}
    /*public*/ void enableSave();
    /*public*/ void storeValues();
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText() ;
    /*public*/ QString getTabbedPreferencesTitle() ;
    /*public*/ QString getLabelKey();
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ bool isDirty();
    /*public*/ bool isRestartRequired();
    /*public*/ QWidget* getTopLevelAncestor();

signals:

public slots:
private:
//    Border lineBorder;
    JTextField* railroadName;
    QPushButton* saveB;
    QPushButton* cancelB;
    WebServerPreferences* preferences;
    JFrame* parentFrame;// = null;
    /*private*/ void initGUI();
    /*private*/ void setGUI();
    /*private*/ bool setValues();
    /*private*/ QWidget* rrNamePanel();
protected:
    /*protected*/ void applyValues();
    /*protected*/ void cancelValues();

};

#endif // RAILROADNAMEPREFERENCESPANEL_H
