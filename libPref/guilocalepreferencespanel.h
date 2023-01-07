#ifndef GUILOCALEPREFERENCESPANEL_H
#define GUILOCALEPREFERENCESPANEL_H
#include "preferencessubpanel.h"
#include "libpref_global.h"

class GuiLafConfigPane;
class LIBPREFSHARED_EXPORT GuiLocalePreferencesPanel : public QWidget, public PreferencesSubPanel,
  public PreferencesPanel, public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(PreferencesPanel PreferencesSubPanel InstanceManagerAutoDefault)

public:
    Q_INVOKABLE explicit GuiLocalePreferencesPanel(QWidget *parent = 0);
    ~GuiLocalePreferencesPanel() {}
    GuiLocalePreferencesPanel(const GuiLocalePreferencesPanel&) : QWidget() {}
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
    /*public*/ bool isPreferencesValid();
    /*public*/ QString className();
    /*public*/ QObject* ppself() {return (QObject*)this;}
    /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
private:
    GuiLafConfigPane* parent = nullptr;
};

#endif // GUILOCALEPREFERENCESPANEL_H
