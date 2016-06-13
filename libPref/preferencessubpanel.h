#ifndef PREFERENCESSUBPANEL_H
#define PREFERENCESSUBPANEL_H

#include "preferencespanel.h"
#include "libpref_global.h"

class  PropertyChangeEvent;
/*public*/ class LIBPREFSHARED_EXPORT PreferencesSubPanel : public PreferencesPanel
{
    Q_OBJECT
public:
    PreferencesSubPanel(QWidget* parent = 0);
~PreferencesSubPanel() {}
//    PreferencesSubPanel(const PreferencesSubPanel&) {}
    /*public*/ /*abstract*/ virtual QString getParentClassName() {return "";}

    /*public*/ /*abstract*/ virtual void setParent(PreferencesPanel* /*parent*/) {}

    /*public*/ /*abstract*/ virtual PreferencesPanel* getParent() {return NULL;}
 signals:
  void propertyChange(PropertyChangeEvent*);
 public slots:
  void On_propertyChange(PropertyChangeEvent*);
};

#endif // PREFERENCESSUBPANEL_H
