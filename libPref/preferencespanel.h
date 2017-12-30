#ifndef PREFERENCESPANEL_H
#define PREFERENCESPANEL_H
#include <QTabWidget>
#include "jframe.h"
#include "libpref_global.h"
/**
 * An interface to define methods that the Preferences Window can and should
 * expect Preferences panels to implement.
 *
 * This class allows the Preferences Window become less formally aware of all
 * possible preferences settings in JMRI, and to instead interrogate a
 * PreferencesPanel for most of the information that the Preferences window
 * requires to add the PreferencesPanel to the window.
 *
 * @author Randall Wood (C) 2012, 2014
 */
/*public*/ /*interface*/ class LIBPREFSHARED_EXPORT PreferencesPanel : public QWidget
{
 Q_OBJECT
public:
 PreferencesPanel(QWidget* parent = 0) : QWidget(parent) {}
 ~PreferencesPanel() {}
 PreferencesPanel(const PreferencesPanel&) : QWidget() {}
    /**
     * Get the Preferences Item identifier.
     *
     * Multiple PreferencePanels can be displayed as tabs in a single item.
     * Preferences items are listed in the menu on the left of the preferences
     * window.
     *
     * @return the preferences item identifier.
     */
    virtual /*public abstract*/ QString getPreferencesItem() {return "";}

    /**
     * Get the text for the Preferences Item in the preferences window list of
     * preferences categories.
     *
     * Multiple PreferencePanels can be displayed as tabs in a single item.
     * Preferences items are listed in the menu on the left of the preferences
     * window.
     *
     * @return the text for the preferences item.
     */
    virtual /*public abstract*/ QString getPreferencesItemText() {return "";}

    /**
     * Get the title for the tab containing this preferences item.
     *
     * @return a tab title
     */
    virtual /*public abstract*/ QString getTabbedPreferencesTitle() {return "";}

    /**
     * Text displayed above the preferences panel
     *
     * This label is only displayed if the preferences panel is in a tabbed set
     * of preferences. This label can contain multiple lines.
     *
     * @return label text
     */
    virtual /*public abstract*/ QString getLabelKey() {return "";}

    /**
     * Get the preferences component for display
     *
     * @return the preferences panel
     */
    virtual /*public abstract*/ QWidget* getPreferencesComponent() {return NULL;}

    /**
     * Indicates that this PrefernecesPanel should be stored across application
     * starts by the PreferencesManager
     *
     * This should be true if the implementing class relies on the
     * {@link jmri.ConfigureManager} stores and retrieves the preferences
     * managed by the implementing class on behalf of the implementing class.
     *
     * @return false if the implementing class stores its own preferences
     */
    virtual /*public abstract*/ bool isPersistant() {return false;}

    /**
     * The tooltip to display for a tabbed preferences panel
     *
     * @return tooltip text
     */
    virtual /*public abstract*/ QString getPreferencesTooltip() {return "";}

    /**
     * Save any changes to preferences.
     *
     * This method is called for every instance of a PreferencesPanel that is
     * loaded by {@link apps.gui3.TabbedPreferences} if {@link #isPersistant()}
     * is false.
     */
    virtual /*public abstract*/ void savePreferences() {}

    /**
     * Indicate that preferences need to be saved.
     *
     * @return true if preferences need to be saved, false otherwise
     */
    virtual /*public abstract*/ bool isDirty() {return true;}

    /**
     * Indicate that the preferences will not take effect until restarted.
     *
     * @return true if the application needs to restart
     */
    virtual /*public abstract*/ bool isRestartRequired() {return false;}
 /**
  * Returns the top-level ancestor of this component (either the
  * containing <code>Window</code> or <code>Applet</code>),
  * or <code>null</code> if this component has not
  * been added to any container.
  *
  * @return the top-level <code>Container</code> that this component is in,
  *          or <code>null</code> if not in any container
  */
 /*public*/ QWidget* getTopLevelAncestor()
 {
  for(QObject* p = this; p != NULL; p = p->parent())
  {
   //if(p instanceof Window || p instanceof Applet)
      if(qobject_cast<JFrame*>(p)!=NULL)
   {
    return (QWidget*)p;
   }
  }
  return NULL;
 }
};
Q_DECLARE_METATYPE(PreferencesPanel)
#endif // PREFERENCESPANEL_H
