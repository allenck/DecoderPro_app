#ifndef PREFERENCESSUBPANEL_H
#define PREFERENCESSUBPANEL_H

#include "preferencespanel.h"
#include "libpref_global.h"

class  PropertyChangeEvent;
/*public*/ class LIBPREFSHARED_EXPORT PreferencesSubPanel : public PreferencesPanel {
  Q_INTERFACES(PreferencesPanel)
public:
//    PreferencesSubPanel(const PreferencesSubPanel&) {}
    /*public*/ /*abstract*/ virtual QString getParentClassName() =0;

    /*public*/ /*abstract*/ virtual void setParent(PreferencesPanel* /*parent*/) =0;

    /*public*/ /*abstract*/ virtual PreferencesPanel* getParent() =0;

    /*public*/ virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(PreferencesSubPanel, "PreferencesSubPanel")
#endif // PREFERENCESSUBPANEL_H
