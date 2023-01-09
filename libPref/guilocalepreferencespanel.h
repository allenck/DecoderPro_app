#ifndef GUILOCALEPREFERENCESPANEL_H
#define GUILOCALEPREFERENCESPANEL_H
#include "preferencessubpanel.h"
#include "libpref_global.h"

class GuiLafConfigPane;
class LIBPREFSHARED_EXPORT GuiLocalePreferencesPanel : public QWidget, public PreferencesSubPanel,
  public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(PreferencesSubPanel  InstanceManagerAutoDefault)

public:
    Q_INVOKABLE explicit GuiLocalePreferencesPanel(QWidget *parent = 0);
    ~GuiLocalePreferencesPanel() {}
    GuiLocalePreferencesPanel(const GuiLocalePreferencesPanel&) : QWidget() {}
    /*public*/ QString getParentClassName()  override ;
    /*public*/ void setParent(PreferencesPanel* parent) override ;
    /*public*/ PreferencesPanel* getParent() override ;
    /*public*/ QString getPreferencesItem() override ;
    /*public*/ QString getPreferencesItemText() override ;
    /*public*/ QString getTabbedPreferencesTitle() override ;
    /*public*/ QString getLabelKey() override  ;
    /*public*/ QWidget* getPreferencesComponent() override ;
    /*public*/ bool isPersistant() override ;
    /*public*/ QString getPreferencesTooltip() override ;
    /*public*/ void savePreferences() override ;
    /*public*/ bool isDirty() override ;
    /*public*/ bool isRestartRequired() override ;
    /*public*/ bool isPreferencesValid() override ;
    /*public*/ QString className() override ;

    /*public*/ QObject* ppself() override  {return this;}
    /*public*/ QObject* self() override {return this;}

signals:

public slots:
private:
    GuiLafConfigPane* parent = nullptr;
};
Q_DECLARE_METATYPE(GuiLocalePreferencesPanel)
#endif // GUILOCALEPREFERENCESPANEL_H
