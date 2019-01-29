#ifndef PREFERENCESSUBPANEL_H
#define PREFERENCESSUBPANEL_H

#include "preferencespanel.h"
#include "libpref_global.h"

class  PropertyChangeEvent;
/*public*/ class LIBPREFSHARED_EXPORT PreferencesSubPanel {
public:
//    PreferencesSubPanel(const PreferencesSubPanel&) {}
    /*public*/ /*abstract*/ virtual QString getParentClassName() {return "";}

    /*public*/ /*abstract*/ virtual void setParent(PreferencesPanel* /*parent*/) {}

    /*public*/ /*abstract*/ virtual PreferencesPanel* getParent() {return NULL;}
};
Q_DECLARE_INTERFACE(PreferencesSubPanel, "PreferencesSubPanel")
#endif // PREFERENCESSUBPANEL_H
