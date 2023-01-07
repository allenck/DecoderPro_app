#ifndef MANAGINGPREFERENCESPANEL_H
#define MANAGINGPREFERENCESPANEL_H
#include "preferencespanel.h"

/**
 * A {@link jmri.swing.PreferencesPanel} that manages other PreferencesPanels
 * within its own panel.
 *
 * @author Randall Wood 2015
 */
/*public*/ /*interface*/class  ManagingPreferencesPanel : public PreferencesPanel {
 public:
    /*public*/ /*abstract*/virtual QList<PreferencesPanel*> getPreferencesPanels() =0;
};

Q_DECLARE_INTERFACE(ManagingPreferencesPanel, "ManagingPreferencesPanel")
#endif // MANAGINGPREFERENCESPANEL_H
