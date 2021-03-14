#include "tabbedpreferencesprofileaction.h"

/**
 * Tabbed Preferences Action for going direct to Profiles.
 *<p>
 * Most of the behavior comes from the {@link TabbedPreferencesAction} superclass;
 * this just adds a specific target.
 *
 * @author Bob Jacobsen (C) 2014, 2019
 */
//public class TabbedPreferencesProfileAction extends TabbedPreferencesAction {

    /*public*/ TabbedPreferencesProfileAction::TabbedPreferencesProfileAction(QObject* parent) : TabbedPreferencesAction(tr("TabbedPreferencesProfileAction"), parent){
        //super(Bundle.getMessage("MenuItemPreferencesProfile"));
        preferencesItem = "Profiles";
    }

//}
