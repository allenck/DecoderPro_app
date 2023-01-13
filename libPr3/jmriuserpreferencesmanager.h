#ifndef JMRIUSERPREFERENCESMANAGER_H
#define JMRIUSERPREFERENCESMANAGER_H
#include "userpreferencesmanager.h"
#include "bean.h"
#include <QtXml>
#include "sortorder.h"
#include "instancemanagerautoinitialize.h"
#include "abstractinstanceinitializer.h"

class Logger;
class QDomDocument;
class QDomElement;

class File;
class WindowLocations;
class ClassPreferences;
class MultipleChoice;
class PreferenceList;
class JmriUserPreferencesManager : public UserPreferencesManager, public InstanceManagerAutoInitialize
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoInitialize)
public:
 /*public*/ /*final*/ static QString SAVE_ALLOWED;// = "saveAllowed";

 Q_INVOKABLE JmriUserPreferencesManager(QObject* parent = nullptr);
 ~JmriUserPreferencesManager() {}
 JmriUserPreferencesManager(const JmriUserPreferencesManager&) : UserPreferencesManager() {}
// /*public*/ static UserPreferencesManager* getInstance();
// /*public*/ static UserPreferencesManager* getDefault();
 /*public*/ /*synchronized*/ void setSaveAllowed(bool saveAllowed) override;
 /*public*/ bool isSaveAllowed() override ;
 /*public*/ QSize getScreen() override;
 /*public*/ void setSimplePreferenceState(QString name, bool state) override;
 /*public*/ bool getSimplePreferenceState(QString name) override;
 /*public*/ QStringList getSimplePreferenceStateList()  override;
 /*public*/ void setPreferenceState(QString strClass, QString item, bool state) override;
 /*public*/ bool getPreferenceState(QString strClass, QString item) override;
 /*public*/ /*final*/ void setPreferenceItemDetails(QString strClass, QString item, QString description) override;
 /*public*/ QStringList getPreferenceList(QString strClass) override;
 /*public*/ QString getPreferenceItemName(QString strClass, int n) override ;
 /*public*/ QString getPreferenceItemDescription(QString strClass, QString item) override;
 /*public*/ void setSessionPreferenceState(QString name, bool state) override;
 /*public*/ bool getSessionPreferenceState(QString name) override;
 /*public*/ void showInfoMessage(QString title, QString message, QString strClass, QString item) override;
 /*public*/ void showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) override;
 /*public*/ void showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember) override;
 /*public*/ void showWarningMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ QString getComboBoxLastSelection(QString comboBoxName) override;
 /*public*/ void setComboBoxLastSelection(QString comboBoxName, QString lastValue) override;
 /*public*/ bool getCheckboxPreferenceState(QString name, bool defaultState)override;
 /*public*/ void setCheckboxPreferenceState(QString name, bool state)override;
 /*public*/ /*synchronized*/ bool getChangeMade();
 /*public*/ /*synchronized*/ void setChangeMade(bool fireUpdate);
 /*public*/ /*synchronized*/ void resetChangeMade() override;
 /*public*/ void setLoading() override;
 /*public*/ void finishLoading() override;
 /*public*/ void displayRememberMsg() ;
 /*public*/ QPoint getWindowLocation(QString strClass) override;
 /*public*/ QSize getWindowSize(QString strClass) override;
 /*public*/ bool getSaveWindowSize(QString strClass) override;
 /*public*/ bool getSaveWindowLocation(QString strClass) override;
 /*public*/ void setSaveWindowSize(QString strClass, bool b) override;
 /*public*/ void setSaveWindowLocation(QString strClass, bool b) override ;
 /*public*/ void setWindowLocation(QString strClass, QPoint location) override;
 /*public*/ void setWindowSize(QString strClass, QSize dim) override ;
 /*public*/ QStringList getWindowList() override;
 /*public*/ void setProperty(QString strClass, QString key, QVariant value) override;
 /*public*/ QVariant getProperty(QString strClass, QString key) override;
 /*public*/ QSet<QString> getPropertyKeys(QString strClass) override;
 /*public*/ bool hasProperties(QString strClass) override;
 /*public*/ QString getClassDescription(QString strClass) override;
 /*public*/ QStringList getPreferencesClasses() override;
 /*public*/ void setClassDescription(QString strClass) override;
 /*public*/ void setMessageItemDetails(QString strClass, QString item, QString description, QMap<int, QString> *options, int defaultOption) override;
 /*public*/ QMap<int, QString> *getChoiceOptions(QString strClass, QString item) override;
 /*public*/ int getMultipleChoiceSize(QString strClass) override;
 /*public*/ QStringList getMultipleChoiceList(QString strClass) override;
 /*public*/ QString getChoiceName(QString strClass, int n) override;
 /*public*/ QString getChoiceDescription(QString strClass, QString item) override;
 /*public*/ int getMultipleChoiceOption(QString strClass, QString item) override;
 /*public*/ int getMultipleChoiceDefaultOption(QString strClass, QString choice) override;
 /*public*/ void setMultipleChoiceOption(QString strClass, QString choice, QString value) override;
 /*public*/ void setMultipleChoiceOption(QString strClass,QString choice, int value) override;
 /*public*/ void setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden);
 /*public*/ int getTableColumnOrder(QString table, QString column);
 /*public*/ int getTableColumnWidth(QString table, QString column);
 /*public*/ int getTableColumnSort(QString table, QString column);
 /*public*/ bool getTableColumnHidden(QString table, QString column) ;
 /*public*/ QString getTableColumnAtNum(QString table, int i);
 /*public*/ QStringList getTablesList();
 /*public*/ QStringList getTablesColumnList(QString table);
 /*public*/ QString getClassDescription();
 /*public*/ int getPreferencesSize(QString strClass) override;
 /*public*/ /*final*/ void readUserPreferences();
 Q_INVOKABLE /*public*/ void initialize() override;
 //@ServiceProvider(service = InstanceInitializer.class)
 /*public*/ /*static*/ class Initializer : public AbstractInstanceInitializer {

   //Q_INTERFACES(InstanceInitializer)
     //@Override
     /*public*/ /*<T>*/ QObject* getDefault(/*Class<T>*/QString type) const override{
         if (type == "UserPreferencesManager") {
             return new JmriUserPreferencesManager();
         }
         return AbstractInstanceInitializer::getDefault(type);
     }

     //@Override
     /*public*/ QSet</*Class<?>*/QString>* getInitalizes() override{
         QSet</*Class<?>*/QString>* set = AbstractInstanceInitializer::getInitalizes();
         set->insert("UserPreferencesManager");
         return set;
     }
 };

private:
 /*private*/ void readComboBoxLastSelections();
 /*private*/ void saveComboBoxLastSelections();
 /*private*/ void readCheckBoxLastSelections();
 /*private*/ void saveCheckBoxLastSelections();
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
 /*private*/ static /*final*/ QString CHECKBOX_NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/checkbox-4-21-3.xsd"; // NOI18N
 /*private*/ static /*final*/ QString CHECKBOX_ELEMENT;// = "checkBoxLastValue"; // NOI18N
 /*private*/ /*final*/ static QString SETTINGS_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/settings-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString SETTINGS_ELEMENT; // = "settings"; // NOI18N
 /*private*/ /*final*/ static QString WINDOWS_NAMESPACE; // = "http://jmri.org/xml/schema/auxiliary-configuration/window-details-4-3-5.xsd"; // NOI18N
 /*private*/ /*final*/ static QString WINDOWS_ELEMENT; // = "windowDetails"; // NOI18N
 /*private*/ static /*final*/ QString REMINDER;// = "reminder";
 /*private*/ static /*final*/ QString JMRI_UTIL_JMRI_JFRAME;// = "jmri.util.JmriJFrame";
 /*private*/ static /*final*/ QString CLASS;// = "class";
 /*private*/ static /*final*/ QString VALUE;// = "value";
 /*private*/ static /*final*/ QString WIDTH;// = "width";
 /*private*/ static /*final*/ QString HEIGHT;// = "height";
 /*private*/ static /*final*/ QString PROPERTIES;// = "properties";
 /*private*/ bool dirty = false;
 /*private*/ bool loading = false;
 /*private*/ bool allowSave = true;
 /*private*/ QStringList* simplePreferenceList;// = new QStringList();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 /*private*/ QStringList* sessionPreferenceList;// = new QStringList();
 /*private*/ /*final*/ QHash<QString, WindowLocations*>* windowDetails;// = new QHash<QString, WindowLocations*>();
 /*private*/ QHash<QString, ClassPreferences*>* classPreferenceList;// = new QHash<QString, ClassPreferences*>();
 /*private*/ File* file;
 QDomDocument doc;
 static Logger* log;

private slots:
 void /*private*/ initAfter() override;

protected:
 /*protected*/ /*final*/ QHash<QString, QString>* comboBoxLastSelection;// = new QHash<QString, QString>();
 /*protected*/ /*final*/ QMap<QString, bool> checkBoxLastSelection = QMap<QString, bool>();
 virtual /*protected*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);
 virtual /*protected*/ bool isLoading();
 virtual /*protected*/ /*final*/ QString getClassName() ;
 /*protected*/ /*final*/ ClassPreferences* getClassPreferences(QString strClass) ;

 friend class JmriUserPreferencesManagerTest;
};
/**
 * Holds details about the specific class.
 */
/*protected*/ /*final*/ /*static*/ class ClassPreferences
{
private:
    QString classDescription;

    QList<MultipleChoice*>* multipleChoiceList = new QList<MultipleChoice*>();
    QList<PreferenceList*>* preferenceList = new QList<PreferenceList*>();
public:
    ClassPreferences();
    ClassPreferences(QString classDescription);
    QString getDescription();
    void setDescription(QString description);
    QList<PreferenceList*>* getPreferenceList();
    int getPreferenceListSize();
    QList<MultipleChoice*>* getMultipleChoiceList() ;
    int getPreferencesSize();
    /*public*/ QString getPreferenceName(int n);
    int getMultipleChoiceListSize();
    /*public*/ QString getChoiceName(int n);
    friend class JmriUserPreferencesManager;
};

/*protected*/ /*final*/ /*static*/ class MultipleChoice
{
private:
    QMap<int, QString>* options = nullptr;
    QString optionDescription;
    QString item;
    int value = -1;
    int defaultOption = -1;
public:
    MultipleChoice(QString description, QString item, QMap<int, QString>* options, int defaultOption);
    MultipleChoice(QString item, int value);
    void setValue(int value) ;
    void setValue(QString value);
    void setMessageItems(QString description, QMap<int, QString>* options, int defaultOption);
    int getValue();
    int getDefaultValue();
    QString getItem() ;
    QString getOptionDescription();
    QMap<int, QString> *getOptions();
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
