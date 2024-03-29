#ifndef USERPREFERENCESMANAGER_H
#define USERPREFERENCESMANAGER_H
#include <QObject>
#include <QHash>
#include <QPoint>
#include <QSize>
#include <QStringList>
#include "level.h"
#include <QMap>
#include <QVariant>
#include <QSet>
#include "javaqt_global.h"
#include "bean.h"

/**
 * Interface for the User Preferences Manager.
 * <P>
 * The User Message Preference Manager keeps track of the options that a user
 * has selected in messages where they have selected "Remember this setting for next time"
 *
 * @see jmri.managers.DefaultUserMessagePreferences
 *
 * @author      Kevin Dickerson Copyright (C) 2010
 * @version	$Revision: 20527 $
 */
class PropertyChangeListener;
/*public interface*/ class JAVAQTSHARED_EXPORT UserPreferencesManager : public Bean
{
 Q_OBJECT
private slots:
 virtual void initAfter() {}
public:
    UserPreferencesManager(QObject* parent = nullptr) : Bean(parent) {}
    ~UserPreferencesManager() {}
    UserPreferencesManager(const UserPreferencesManager&) : Bean() {}
    /*public*/ virtual void setLoading() =0;
    /*public*/ virtual void finishLoading() =0;
    /*public*/ static /*final*/ QString PREFERENCES_UPDATED;// = "PreferencesUpdated"; // NOI18N

    /**
     * Enquire as to the state of a user preference.
     * <p>
     * Preferences that have not been set will be
     * considered to be false.
     *<p>
     * The name is free-form, but to avoid ambiguity it should
     * start with the package name (package.Class) for the
     * primary using class.
     */
    virtual bool getSimplePreferenceState(QString /*name*/) =0;

    /**
     * This is used to remember the last selected state of a checkBox and thus
     * allow that checkBox to be set to a true state when it is next initialised.
     * This can also be used anywhere else that a simple yes/no, true/false type
     * preference needs to be stored.
     *
     * It should not be used for remembering if a user wants to suppress a message
     * as there is no means in the GUI for the user to reset the flag.
     * setPreferenceState() should be used in this instance
     * The name is free-form, but to avoid ambiguity it should
     * start with the package name (package.Class) for the
     * primary using class.
     * @param name A unique name to identify the state being stored
     * @param state simple bool.
     */
    virtual void setSimplePreferenceState(QString /*name*/, bool /*state*/) =0;

    /**
     * Enquire as to the state of a user preference.
     * <p>
     * Preferences that have not been set will be considered to be defaultState.
     * <p>
     * The name is free-form, but to avoid ambiguity it should start with the
     * package name (package.Class) for the primary using class.
     *
     * @param name the name of the preference
     * @param defaultState the default state if not set
     * @return the state or defaultState if never set
     */
    virtual bool getCheckboxPreferenceState(QString name, bool defaultState)=0;
    /**
     * This is used to remember the last selected state of a checkBox and thus
     * allow that checkBox to be set to a true state when it is next
     * initialized. This can also be used anywhere else that a simple yes/no,
     * true/false type preference needs to be stored.
     * <p>
     * It should not be used for remembering if a user wants to suppress a
     * message as there is no means in the GUI for the user to reset the flag.
     * setPreferenceState() should be used in this instance The name is
     * free-form, but to avoid ambiguity it should start with the package name
     * (package.Class) for the primary using class.
     *
     * @param name  A unique name to identify the state being stored
     * @param state simple boolean
     */
    virtual void setCheckboxPreferenceState(QString name, bool state)=0;


    /**
     *  Returns an ArrayList of the checkbox states set as true.
     */
    /*public*/ virtual QStringList getSimplePreferenceStateList() =0;

    /**
     * Used to save the state of checkboxes which can suppress messages from being
     * displayed.
     * This method should be used by the initiating code in conjunction with the
     * preferenceItemDetails.
     * Here the items are stored against a specific class and access to change
     * them is made available via the GUI, in the preference manager.
     * <p>
     * The strClass parameter does not have to be the exact class name of the
     * initiating code, but can be one where the information is related and therefore
     * can be grouped together with.
     * <p>
     * Both the strClass and item although free form, should make up a unique reference.
     * @param strClass The class that this preference should be stored or grouped with.
     * @param item The specific item that is to be stored
     * @param state Boolean state of the item.
     */
    /*public*/ virtual void setPreferenceState(QString /*strClass*/, QString /*item*/, bool /*state*/) =0;

    /**
    * Returns the state of a given item registered against a specific class or item.
    */
    /*public*/ virtual bool getPreferenceState(QString /*strClass*/, QString /*item*/) =0;

    /**
     * Register details about a particular preference, so that it can be
     * displayed in the GUI and provide a meaning full description when
     * presented to the user.
     *
     * @param strClass    A string form of the class that the preference is
     *                    stored or grouped with
     * @param item        The specific item that is being stored
     * @param description A meaningful description of the item that the user
     *                    will understand
     */
    /*public*/ virtual void setPreferenceItemDetails(QString /*strClass*/, QString /*item*/, QString /*description*/) =0;
    /**
     * Returns a list of preferences that are registered against a specific class.
     */
    /*public*/ virtual QStringList getPreferenceList(QString /*strClass*/) =0;

    /**
     * Returns the itemName of the n preference in the given class
     */
    /*public*/ virtual QString getPreferenceItemName(QString /*strClass*/, int /*n*/) =0;

    /**
     * Returns the description of the given item preference in the given class
     */
    /*public*/ virtual QString getPreferenceItemDescription(QString /*strClass*/, QString /*item*/) =0;


    /**
     * Enquire as to the state of a user preference for the current session.
     * <p>
     * Preferences that have not been set will be
     * considered to be false.
     *<p>
     * The name is free-form, but to avoid ambiguity it should
     * start with the package name (package.Class) for the
     * primary using class.
     */
    /*public*/ virtual bool getSessionPreferenceState(QString /*name*/) =0;

    /**
    * Used to surpress messages for the current session, the information is not
    * stored, can not be changed via the GUI.
    * <p>
    * This can be used to help prevent over loading the user with repetitive error
    * messages such as turnout not found while loading a panel file due to a connection failing.
    * The name is free-form, but to avoid ambiguity it should
    * start with the package name (package.Class) for the
    * primary using class.
    * @param name A unique identifer for preference.
    * @param state
    */
    /*public*/ virtual void setSessionPreferenceState(QString /*name*/, bool /*state*/) =0;

     // The reset is used after the preferences have been loaded for the first time
    /*public*/ virtual void resetChangeMade() {}

    /**
     * Show an error message ("don't forget ...") with a given dialog title and
     * user message. Use a given preference name to determine whether to show it
     * in the future. added flag to indicate that the message should be
     * suppressed JMRI session only. The classString & item parameters should
     * form a unique value
     *
     * @param title Message Box title
     * @param message Message to be displayed
     * @param classString String value of the calling class
     * @param item String value of the specific item this is used for
     * @param sessionOnly Means this message will be suppressed in this JMRI
     * session and not be remembered
     * @param alwaysRemember Means that the suppression of the message will be
     * saved
     */
    /*public*/ virtual void showErrorMessage(QString /*title*/, QString /*message*/, QString /*classString*/, QString /*item*/, bool /*sessionOnly*/, bool /*alwaysRemember*/) =0;

    /**
     * Show an info message ("don't forget ...")
     * with a given dialog title and
     * user message.
     * Use a given preference name to determine whether
     * to show it in the future.
     * The classQString & item parameters should form a unique value
     * @param title Message Box title
     * @param message Message to be displayed
     * @param classQString QString value of the calling class
     * @param item QString value of the specific item this is used for
     */
    /*public*/ virtual void showInfoMessage(QString /*title*/, QString /*message*/, QString /*classQString*/, QString /*item*/) =0;


    /**
     * Show an info message ("don't forget ...")
     * with a given dialog title and
     * user message.
     * Use a given preference name to determine whether
     * to show it in the future.
     * added flag to indicate that the message should be suppressed
     * JMRI session only.
     * The classQString & item parameters should form a unique value
     * @param title Message Box title
     * @param message Message to be displayed
     * @param classQString QString value of the calling class
     * @param item QString value of the specific item this is used for
     * @param sessionOnly Means this message will be suppressed in this JMRI session and not be remembered
     * @param alwaysRemember Means that the suppression of the message will be saved
     * @param level Used to determine the type of messagebox that will be used.
     */
    /*public*/ virtual void showInfoMessage(QString /*title*/, QString /*message*/, QString /*classString*/, QString /*item*/, bool /*sessionOnly*/, bool /*alwaysRemember*/) =0;
    /**
    * returns the last selected value in a given combobox
    *
    **/
    /*public*/ virtual QString getComboBoxLastSelection(QString /*comboBoxName*/) =0;
    /**
    * sets the last selected value in a given combobox
    *
    **/
    /*public*/ virtual void setComboBoxLastSelection(QString /*comboBoxName*/, QString /*lastValue*/) =0;

    /**
    * returns the number of comboBox options saved
    *
    **/
    // /*public*/ virtual int getComboBoxSelectionSize() {return 0;}

    /**
    * returns the ComboBox Name at position n
    *
    **/
    // /*public*/ virtual QString getComboBoxName(int /*n*/) {return "";}

    /**
    * returns the ComboBox Value at position n
    *
    **/
    // /*public*/ virtual QString getComboBoxLastSelection(int /*n*/) {return "";}

    /*public*/ virtual QSize getScreen() =0;

//    QT_DEPRECATED /*public*/ virtual void allowSave() {}
//    QT_DEPRECATED /*public*/ virtual void disallowSave() {}

    /**
    * Returns the description of a class/group registered with the preferences.
    */
    /*public*/ virtual QString getClassDescription(QString /*strClass*/) =0;

    /**
    * Returns a list of the classes registered with the preference manager.
    */
    /*public*/ virtual QStringList getPreferencesClasses() =0;

    /**
     * Given that we know the class as a string, we will try and attempt to gather
     * details about the preferences that has been added, so that we can make better
     * sense of the details in the preferences window.
     * <p>
     * This looks for specific methods within the class called "getClassDescription"
     * and "setMessagePreferenceDetails".  If found it will invoke the methods,
     * this will then trigger the class to send details about its preferences back
     * to this code.
     */
    /*public*/ virtual void setClassDescription(QString /*strClass*/) =0;


    /**
     * Add descriptive details about a specific message box, so that if it needs
     * to be reset in the preferences, then it is easily identifiable. displayed
     * to the user in the preferences GUI.
     *
     * @param strClass      String value of the calling class/group
     * @param item          String value of the specific item this is used for.
     * @param description   A meaningful description that can be used in a label
     *                      to describe the item
     * @param options       A map of the integer value of the option against a
     *                      meaningful description.
     * @param defaultOption The default option for the given item.
     */
    /*public*/ virtual void setMessageItemDetails(QString /*strClass*/, QString /*item*/, QString /*description*/, QMap<int, QString>* /*options*/, int /*defaultOption*/) =0;

    /**
    * Returns a map of the value against description of the different items in a
    * given class.  This information can then be used to build a Combo box.
    * @param strClass Class or group of the given item
    * @param item the item which we wish to return the details about.
    */
    /*public*/ virtual QMap<int, QString>* getChoiceOptions(QString /*strClass*/, QString /*item*/) =0;

    /**
    * Returns the number of Mulitple Choice items registered with a given class.
    */
    /*public*/ virtual int getMultipleChoiceSize(QString /*strClass*/) =0;

    /**
    * Returns a list of all the multiple choice items registered with a given class.
    */
    /*public*/ virtual QStringList getMultipleChoiceList(QString /*strClass*/) =0;

    /**
    * Returns the nth item name in a given class
    */
    /*public*/ virtual QString getChoiceName(QString /*strClass*/, int /*n*/) =0;

    /**
    * Returns the a meaningful description of a given item in a given class or group.
    */
    /*public*/ virtual QString getChoiceDescription(QString /*strClass*/, QString /*item*/) =0;

    /**
    * Returns the current value of a given item in a given class
    */
    /*public*/ virtual int getMultipleChoiceOption (QString /*strClass*/, QString /*item*/) =0;

    /**
    * Returns the default value of a given item in a given class
    */
    /*public*/ virtual int getMultipleChoiceDefaultOption (QString /*strClass*/, QString /*choice*/) =0;

    /**
    * Sets the value of a given item in a given class, by its string description
    */
    /*public*/ virtual void setMultipleChoiceOption (QString /*strClass*/, QString /*choice*/, QString /*value*/) =0;

    /**
    * Sets the value of a given item in a given class, by its integer value
    */
    /*public*/ virtual void setMultipleChoiceOption (QString /*strClass*/, QString /*choice*/, int /*value*/) =0;

    /**
    * returns the combined size of both types of items registered.
    */
    /*public*/ virtual int getPreferencesSize(QString /*strClass*/) =0;

    /**
     * Saves the last location of a given component on the screen.
     * <p>
     * The jmri.util.JmriJFrame, will automatically use the class name of the frame
     * if the class name returned is equal to jmri.util.JmriJFrame, the location is not stored
     * @param strClass This is a unique identifier for window location being saved
     * @param location The x,y location of the window given in a Point
     */
    /*public*/ virtual void setWindowLocation(QString /*strClass*/, QPoint /*location*/) =0;

    /**
     * Saves the last size of a given component on the screen
     * <p>
     * The jmri.util.JmriJFrame, will automatically use the class name of the frame
     * if the class name returned is equal to jmri.util.JmriJFrame, the size is not stored
     * @param strClass This is a unique identifier for window size being saved
     * @param dim The width, height size of the window given in a Dimension
     */
    /*public*/ virtual void setWindowSize(QString /*strClass*/, QSize /*dim*/) =0;

    /**
    * Returns the x,y location of a given Window
    */
    /*public*/ virtual QPoint getWindowLocation(QString /*strClass*/) {return QPoint();}
    /**
    * Returns the width, height size of a given Window
    */
    /*public*/ virtual QSize getWindowSize(QString /*strClass*/) =0;



    /*public*/ virtual QStringList getWindowList() =0;

    /**
     * Do we have a saved window position for the class
     * @param strClass
     * @return true if the window position details are stored, false if not.
     */
//    QT_DEPRECATED /*public*/ virtual bool isWindowPositionSaved(QString strClass)
//    {
//     return this->hasProperties(strClass);
//    }
    /**
     * Check if there are properties for the given class
     *
     * @param strClass class to check
     * @return true if properties for strClass are maintained; false otherwise
     */
    /*public*/ virtual bool hasProperties(QString /*strClass*/) =0;

    /*public*/ virtual bool getSaveWindowSize(QString /*strClass*/) =0;

    /*public*/ virtual bool getSaveWindowLocation(QString /*strClass*/) =0;

    /*public*/ virtual void setSaveWindowSize(QString /*strClass*/, bool /*b*/) {}

    /*public*/ virtual void setSaveWindowLocation(QString /*strClass*/, bool /*b*/) {}

    /**
     * Attach a key/value pair to the
     * given class, which can be retrieved later.
     * These are not bound properties as yet,
     * and don't throw events on modification.
     * Key must not be null.
     */
    /*public*/ virtual void setProperty(QString /*strClass*/, QString /*key*/, QVariant /*value*/) =0;

    /**
     * Retrieve the value associated with a key in a given class
     * If no value has been set for that key, returns null.
     */
    /*public*/ virtual QVariant getProperty(QString /*strClass*/, QString /*key*/) =0;

    /**
     * Retrieve the complete current set of keys for a given class.
     */
    /*public*/ virtual QSet<QString> getPropertyKeys(QString /*strClass*/) =0;

    /**
     * Stores the details of a tables column, so that it can be saved and re-applied
     * when jmri is re-started
     * @param table The reference for the table
     * @param column The column name
     * @param order The position that the column appears in the header
     * @param width The width of the column
     * @param sort The sort order of the column
     * @param hidden Should the column be hidden
     */
//    QT_DEPRECATED /*public*/ virtual void setTableColumnPreferences(QString /*table*/, QString /*column*/, int /*order*/, int /*width*/, int /*sort*/, bool /*hidden*/) {}

    /**
     * Get the stored position of the column for a given table
     * @param table The reference for the table
     * @param column The column name
     * @return -1 if not found
     */
//    QT_DEPRECATED /*public*/ virtual int getTableColumnOrder(QString /*table*/, QString /*column*/) {return 0;}

    /**
     * Get the stored column width for a given table
     * @param table The reference for the table
     * @param column The column name
     * @return -1 if not found
     */
//    QT_DEPRECATED /*public*/ virtual int getTableColumnWidth(QString /*table*/, QString /*column*/) {return 0;}

    /**
     * Get the stored column sort order for a given table
     * @param table The reference for the table
     * @param column The column name
     * @return 0 if not found
     */
//    QT_DEPRECATED /*public*/ virtual int getTableColumnSort(QString /*table*/, QString /*column*/) {return 0;}

    /**
     * Get the stored column hidden state for a given table
     * @param table The reference for the table
     * @param column The column name
     * @return 0 if not found
     */
//    QT_DEPRECATED /*public*/ virtual bool getTableColumnHidden(QString /*table*/, QString /*column*/) {return false;}

    /**
     * Get a name for a column at index i
     * @param table The reference for the table
     * @param i The column index
     * returns null if not found, otherwise the column name
     */
//    QT_DEPRECATED /*public*/ virtual QString getTableColumnAtNum(QString /*table*/, int /*i*/) {return "";}

    /**
     * Get a list of all the table preferences stored
     * @return a List of all the tables, if no tables exist then an empty list is returned
     */
//    QT_DEPRECATED /*public*/ virtual QStringList getTablesList() {return QStringList();}

    /**
     * Get a list of all the column settings for a specific table
     * @param table
     * @return a List of all the columns in a table, if the table is not valid an empty list is returned
     */
//    QT_DEPRECATED /*public*/ virtual QStringList getTablesColumnList(QString /*table*/) {return QStringList();}
    /*
        Example informational message dialog box.

        final UserPreferencesManager p;
        p = jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class);
        if (p.getRouteSaveMsg()){
            final JDialog dialog = new JDialog();
            dialog.setTitle("Reminder");
            dialog.setLocationRelativeTo(null);
            dialog.setDefaultCloseOperation(javax.swing.JFrame.DISPOSE_ON_CLOSE);
            JPanel container = new JPanel();
            container.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
            container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));

            JLabel question = new JLabel("Remember to save your Route information.", JLabel.CENTER);
            question.setAlignmentX(Component.CENTER_ALIGNMENT);
            container.add(question);

            JButton okButton = new JButton("Okay");
            JPanel button = new JPanel();
            button.setAlignmentX(Component.CENTER_ALIGNMENT);
            button.add(okButton);
            container.add(button);

            final JCheckBox remember = new JCheckBox("Do not remind me again?");
            remember.setAlignmentX(Component.CENTER_ALIGNMENT);
            remember.setFont(remember.getFont().deriveFont(10f));
            container.add(remember);

            okButton.addActionListener(new ActionListener(){
                public virtual void actionPerformed(ActionEvent e) {
                    if(remember.isSelected()){
                        p.setRouteSaveMsg(false);
                    }
                    dialog.dispose();
                }
            });


            dialog.getContentPane().add(container);
            dialog.pack();
            dialog.setModal(true);
            dialog.setVisible(true);
        }

*/

/*
        Example question message dialog box.

        final DefaultUserMessagePreferences p;
        p = jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class);
        if (p.getQuitAfterSave()==0x00){
            final JDialog dialog = new JDialog();
            dialog.setTitle(rb.getQString("MessageShortQuitWarning"));
            dialog.setLocationRelativeTo(null);
            dialog.setDefaultCloseOperation(javax.swing.JFrame.DISPOSE_ON_CLOSE);
            JPanel container = new JPanel();
            container.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
            container.setLayout(new BoxLayout(container, BoxLayout.Y_AXIS));

            JLabel question = new JLabel(rb.getQString("MessageLongQuitWarning"));
            question.setAlignmentX(Component.CENTER_ALIGNMENT);
            container.add(question);

            final JCheckBox remember = new JCheckBox("Remember this setting for next time?");
            remember.setFont(remember.getFont().deriveFont(10f));
            remember.setAlignmentX(Component.CENTER_ALIGNMENT);

            JButton yesButton = new JButton("Yes");
            JButton noButton = new JButton("No");
            JPanel button = new JPanel();
            button.setAlignmentX(Component.CENTER_ALIGNMENT);
            button.add(yesButton);
            button.add(noButton);
            container.add(button);

            noButton.addActionListener(new ActionListener(){
                public  void actionPerformed(ActionEvent e) {
                    if(remember.isSelected()){
                        p.setQuitAfterSave(0x01);
                    }
                    dialog.dispose();
                }
            });

            yesButton.addActionListener(new ActionListener(){
                public  void actionPerformed(ActionEvent e) {
                    if(remember.isSelected()) {
                        p.setQuitAfterSave(0x02);
                    }
                    dialog.dispose();
                }
            });
            container.add(remember);
            container.setAlignmentX(Component.CENTER_ALIGNMENT);
            container.setAlignmentY(Component.CENTER_ALIGNMENT);
            dialog.getContentPane().add(container);
            dialog.pack();
            dialog.setModal(true);
            dialog.setVisible(true);
        }
        */
    /**
     * Check if saving preferences is allowed.
     *
     * @return true if saving is allowed; false otherwise
     */
    virtual /*public*/ bool isSaveAllowed() =0;
    /**
     * Set if saving preferences is allowed. When setting true, preferences will
     * be saved immediately if needed.
     * <p>
     * <strong>Note</strong> only set false if a number of preferences will be
     * set together to avoid excessive disk I/O while setting preferences.
     * <p>
     * <strong>Note</strong> remember to allow saving as soon as blocking saving
     * is no longer needed.
     *
     * @param saveAllowed true to allow saving; false to block saving
     */
    virtual /*public*/ void setSaveAllowed(bool /*saveAllowed*/) =0;

    virtual /*public*/ void removePropertyChangeListener(PropertyChangeListener* /*l*/)  {}

    virtual /*public*/ void addPropertyChangeListener(PropertyChangeListener* /*l*/) {}
};
//Q_DECLARE_METATYPE(UserPreferencesManager)
#endif // USERPREFERENCESMANAGER_H
