#ifndef GUILOCALEPREFERENCESPANEL_H
#define GUILOCALEPREFERENCESPANEL_H
#include "preferencessubpanel.h"
#include "libpref_global.h"

class GuiLafConfigPane;
class LIBPREFSHARED_EXPORT GuiLocalePreferencesPanel : public PreferencesSubPanel
{
    Q_OBJECT
public:
    explicit GuiLocalePreferencesPanel(QWidget *parent = 0);
    ~GuiLocalePreferencesPanel() {}
//    GuiLocalePreferencesPanel(const GuiLocalePreferencesPanel&) : PreferencesSubPanel(0) {}
    /*public*/ QString getParentClassName() ;
    /*public*/ void setParent(PreferencesPanel* parent);
    /*public*/ PreferencesPanel* getParent();
    /*public*/ QString getPreferencesItem();
    /*public*/ QString getPreferencesItemText();
    /*public*/ QString getTabbedPreferencesTitle();
    /*public*/ QString getLabelKey() ;
    /*public*/ QWidget* getPreferencesComponent();
    /*public*/ bool isPersistant();
    /*public*/ QString getPreferencesTooltip();
    /*public*/ void savePreferences();
    /*public*/ bool isDirty();
    /*public*/ bool isRestartRequired();

signals:

public slots:
private:
    GuiLafConfigPane* parent;// = NULL;
};

#endif // GUILOCALEPREFERENCESPANEL_H
