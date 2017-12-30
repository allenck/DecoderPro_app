#ifndef JMRIUSERPREFERENCESMANAGER_H
#define JMRIUSERPREFERENCESMANAGER_H
#include "userpreferencesmanager.h"
#include "bean.h"
#include <QtXml>
#include "sortorder.h"

class Logger;
class QDomDocument;
class QDomElement;

class File;
class WindowLocations;
class ClassPreferences;
class MultipleChoice;
class PreferenceList;
class JmriUserPreferencesManager : public UserPreferencesManager
{
public:
 /*public*/ /*final*/ static QString SAVE_ALLOWED;// = "saveAllowed";

 JmriUserPreferencesManager();
 ~JmriUserPreferencesManager() {}
 JmriUserPreferencesManager(const JmriUserPreferencesManager&) : UserPreferencesManager() {}
 /*public*/ static UserPreferencesManager* getInstance();
 /*public*/ static UserPreferencesManager* getDefault();
 /*public*/ /*synchronized*/ void setSaveAllowed(bool saveAllowed);
 /*public*/ bool isSaveAllowed() ;
 /*public*/ QSize getScreen();
 /*public*/ void setSimplePreferenceState(QString name, bool state);
 /*public*/ bool getSimplePreferenceState(QString name);
 /*public*/ QStringList getSimplePreferenceStateList() ;
 /*public*/ void setPreferenceState(QString strClass, QString item, bool state);
 /*public*/ bool getPreferenceState(QString strClass, QString item);
 /*public*/ /*final*/ void setPreferenceItemDetails(QString strClass, QString item, QString description);
 /*public*/ QStringList getPreferenceList(QString strClass);
 /*public*/ QString getPreferenceItemName(QString strClass, int n) ;
 /*public*/ QString getPreferenceItemDescription(QString strClass, QString item);
 /*public*/ void setSessionPreferenceState(QString name, bool state);
 /*public*/ bool getSessionPreferenceState(QString name);
 /*public*/ void showInfoMessage(QString title, QString message, QString strClass, QString item);
 /*public*/ void showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ void showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ void showWarningMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ QString getComboBoxLastSelection(QString comboBoxName);
 /*public*/ void setComboBoxLastSelection(QString comboBoxName, QString lastValue);
 /*public*/ /*synchronized*/ bool getChangeMade();
 /*public*/ /*synchronized*/ void setChangeMade(bool fireUpdate);
 /*public*/ /*synchronized*/ void resetChangeMade();
 /*public*/ void setLoading();
 /*public*/ void finishLoading();
 /*public*/ void displayRememberMsg() ;
 /*public*/ QPoint getWindowLocation(QString strClass);
 /*public*/ QSize getWindowSize(QString strClass);
 /*public*/ bool getSaveWindowSize(QString strClass);
 /*public*/ bool getSaveWindowLocation(QString strClass);
 /*public*/ void setSaveWindowSize(QString strClass, bool b);
 /*public*/ void setSaveWindowLocation(QString strClass, bool b) ;
 /*public*/ void setWindowLocation(QString strClass, QPoint location);
 /*public*/ void setWindowSize(QString strClass, QSize dim) ;
 /*public*/ QStringList getWindowList();
 /*public*/ void setProperty(QString strClass, QString key, QVariant value);
 /*public*/ QVariant getProperty(QString strClass, QString key);
 /*public*/ QSet<QString> getPropertyKeys(QString strClass);
 /*public*/ bool hasProperties(QString strClass);
 /*public*/ QString getClassDescription(QString strClass);
 /*public*/ QStringList getPreferencesClasses();
 /*public*/ void setClassDescription(QString strClass);
 /*public*/ void setMessageItemDetails(QString strClass, QString item, QString description, QMap<int, QString> options, int defaultOption);
 /*public*/ QMap<int, QString> getChoiceOptions(QString strClass, QString item);
 /*public*/ int getMultipleChoiceSize(QString strClass);
 /*public*/ QStringList getMultipleChoiceList(QString strClass);
 /*public*/ QString getChoiceName(QString strClass, int n);
 /*public*/ QString getChoiceDescription(QString strClass, QString item);
 /*public*/ int getMultipleChoiceOption(QString strClass, QString item);
 /*public*/ int getMultipleChoiceDefaultOption(QString strClass, QString choice);
 /*public*/ void setMultipleChoiceOption(QString strClass, QString choice, QString value);
 /*public*/ void setMultipleChoiceOption(QString strClass,QString choice, int value);
 /*public*/ void setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden);
 /*public*/ int getTableColumnOrder(QString table, QString column);
 /*public*/ int getTableColumnWidth(QString table, QString column);
 /*public*/ int getTableColumnSort(QString table, QString column);
 /*public*/ bool getTableColumnHidden(QString table, QString column) ;
 /*public*/ QString getTableColumnAtNum(QString table, int i);
 /*public*/ QStringList getTablesList();
 /*public*/ QStringList getTablesColumnList(QString table);
 /*public*/ QString getClassDescription();
 /*public*/ int getPreferencesSize(QString strClass);
 /*public*/ /*final*/ void readUserPreferences();

private:
 /*private*/ void readComboBoxLastSelections();
 /*private*/ void saveComboBoxLastSelections();
 /*private*/ void readPreferencesState();
 /*private*/ void savePreferencesState();
 /*private*/ void readSimplePreferenceState();
 /*private*/ void saveSimplePreferenceState();
 /*private*/ void readWindowDetails();
 /*private*/ void saveWindowDetails();
 /*private*/ QDomElement readElement(/*@Nonnull*/ QString elementName, /*@Nonnull*/ QString _namespace);
 /*protected*/ void saveElement(/*@Nonnull*/ QDomElement element);
 /*private*/ void savePreferences();

private:
 /*private*/ /*final*/ static QString CLASSPREFS_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/class-preferences-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString CLASSPREFS_ELEMENT; // = "classPreferences"; // NOI18N
 /*private*/ /*final*/ static QString COMBOBOX_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/combobox-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString COMBOBOX_ELEMENT; // = "comboBoxLastValue"; // NOI18N
 /*private*/ /*final*/ static QString SETTINGS_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/settings-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString SETTINGS_ELEMENT; // = "settings"; // NOI18N
 /*private*/ /*final*/ static QString WINDOWS_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/window-details-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString WINDOWS_ELEMENT; // = "windowDetails"; // NOI18N
 /*private*/ bool dirty;// = false;
 /*private*/ bool loading;// = false;
 /*private*/ bool allowSave;
 /*private*/ QStringList* simplePreferenceList;// = new QStringList();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 /*private*/ QStringList* sessionPreferenceList;// = new QStringList();
 /*private*/ /*final*/ QHash<QString, WindowLocations*>* windowDetails;// = new QHash<QString, WindowLocations*>();
 /*private*/ QHash<QString, ClassPreferences*>* classPreferenceList;// = new QHash<QString, ClassPreferences*>();
 /*private*/ File* file;
 QDomDocument doc;
 Logger* log;
protected:
 /*protected*/ /*final*/ QHash<QString, QString>* comboBoxLastSelection;// = new QHash<QString, QString>();
 /*protected*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);
 /*protected*/ bool isLoading();
 /*protected*/ /*final*/ QString getClassName() ;
 /*protected*/ /*final*/ ClassPreferences* getClassPreferences(QString strClass) ;


};
/**
 * Holds details about the specific class.
 */
/*protected*/ /*final*/ /*static*/ class ClassPreferences
{
private:
    QString classDescription;

    QList<MultipleChoice*> multipleChoiceList;// = new ArrayList<>();
    QList<PreferenceList*>* preferenceList;// = new ArrayList<>();
public:
    ClassPreferences();
    ClassPreferences(QString classDescription);
    QString getDescription();
    void setDescription(QString description);
    QList<PreferenceList*>* getPreferenceList();
    int getPreferenceListSize();
    QList<MultipleChoice*> getMultipleChoiceList() ;
    int getPreferencesSize();
    /*public*/ QString getPreferenceName(int n);
    int getMultipleChoiceListSize();
    /*public*/ QString getChoiceName(int n);
    friend class JmriUserPreferencesManager;
};

/*protected*/ /*final*/ /*static*/ class MultipleChoice
{
private:
    QMap<int, QString> options;
    QString optionDescription;
    QString item;
    int value;// = -1;
    int defaultOption;// = -1;
public:
    MultipleChoice(QString description, QString item, QMap<int, QString> options, int defaultOption);
    MultipleChoice(QString item, int value);
    void setValue(int value) ;
    void setValue(QString value);
    void setMessageItems(QString description, QMap<int, QString> options, int defaultOption);
    int getValue();
    int getDefaultValue();
    QString getItem() ;
    QString getOptionDescription();
    QMap<int, QString> getOptions();
};

/*protected*/ /*final*/ /*static*/ class PreferenceList
{
private:
    // need to fill this with bits to get a meaning full description.
    bool set;// = false;
    QString item;// = "";
    QString description;// = "";
public:
    PreferenceList(QString item);
    PreferenceList(QString item, bool state);
    PreferenceList(QString item, QString description) ;
    void setDescription(QString desc);
    QString getDescription();
    bool getState();
    void setState(bool state);
    QString getItem();
};

/*protected*/ /*final*/ /*static*/ class WindowLocations
{
private:
    QPoint xyLocation;// = new Point(0, 0);
    QSize size;// = new Dimension(0, 0);
    bool saveSize;// = false;
    bool saveLocation;// = false;
public:
    WindowLocations() ;
    QPoint getLocation() ;
    QSize getSize();
    void setSaveSize(bool b) ;
    void setSaveLocation(bool b);
    bool getSaveSize() ;
    bool getSaveLocation() ;
    void setLocation(QPoint xyLocation);
    void setSize(QSize size);
    void setProperty(QString key, QVariant value);
    QVariant getProperty(QString key);
    QSet<QString> getPropertyKeys();
    /*final*/ QMap<QString, QVariant> parameters;// = new HashMap<>();
    friend class JmriUserPreferencesManager;
};
Q_DECLARE_METATYPE(JmriUserPreferencesManager)
#endif // JMRIUSERPREFERENCESMANAGER_H
