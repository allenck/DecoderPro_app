#ifndef TABBEDPREFERENCESPROFILEACTION_H
#define TABBEDPREFERENCESPROFILEACTION_H

#include "tabbedpreferencesaction.h"

class TabbedPreferencesProfileAction : public TabbedPreferencesAction
{
    Q_OBJECT
public:
    TabbedPreferencesProfileAction(QObject* parent = nullptr);
    ~TabbedPreferencesProfileAction() {}
    TabbedPreferencesProfileAction(const TabbedPreferencesProfileAction&) : TabbedPreferencesAction() {}
};
Q_DECLARE_METATYPE(TabbedPreferencesProfileAction)
#endif // TABBEDPREFERENCESPROFILEACTION_H
