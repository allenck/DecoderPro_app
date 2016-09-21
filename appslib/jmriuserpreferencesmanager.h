#ifndef JMRIUSERPREFERENCESMANAGER_H
#define JMRIUSERPREFERENCESMANAGER_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QPoint>
#include <QSize>
#include "bean.h"
#include <QtXml>
#include"sortorder.h"

//class PreferenceList;
//class MultipleChoice;
class WindowLocations;
//class ClassPreferences;
//class TableColumnPreferences;
class File;
class ComboBoxLastSelection;
class UserPreferencesManager;
class Logger;
class JmriUserPreferencesManager : public Bean
{
    Q_OBJECT
protected:
 class ClassPreferences;
public:

    explicit JmriUserPreferencesManager(QObject *parent = 0);
    /*public*/ static UserPreferencesManager* getInstance();
    /*public*/ static UserPreferencesManager* getDefault();
 /*public*/ /*synchronized*/ virtual void allowSave();
 /*public*/ /*synchronized*/ virtual void disallowSave();
 /*public*/ virtual QSize getScreen();
 /*public*/ virtual void setSimplePreferenceState(QString name, bool state);
 /*public*/ virtual bool getSimplePreferenceState(QString name);
 /*public*/ virtual QStringList getSimplePreferenceStateList();
 /*public*/ virtual void setPreferenceState(QString strClass, QString item, bool state);
 /*public*/ virtual bool getPreferenceState(QString strClass, QString item);
 /*public*/ /*final*/ virtual void preferenceItemDetails(QString strClass, QString item, QString description);
 /*public*/ virtual QStringList getPreferenceList(QString strClass);
 /*public*/ void setClassDescription(QString strClass);
 /*public*/ /*final*/ void readUserPreferences();
 /*public*/ void displayRememberMsg();
 /*public*/ virtual void setWindowLocation(QString strClass, QPoint location);
 /*public*/ virtual void setWindowSize(QString strClass, QSize dim);
 /*public*/ virtual QStringList getWindowList();
 /*public*/ virtual void setProperty(QString strClass, QString key, QVariant value);
 /*public*/ virtual QVariant getProperty(QString strClass, QString key) ;
 /*public*/ virtual QSet<QString> getPropertyKeys(QString strClass);
 /*public*/ virtual bool isWindowPositionSaved(QString strClass);
 /*public*/ virtual QString getClassDescription(QString strClass);
 /*public*/ virtual QStringList getPreferencesClasses();
 /*public*/ virtual void setSessionPreferenceState(QString name, bool state);
 /*public*/ virtual bool getSessionPreferenceState(QString name);
 /*public*/ virtual void showInfoMessage(QString title, QString message, QString strClass, QString item);
 /*public*/ virtual void showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ virtual void showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ virtual void showWarningMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
 /*public*/ /*synchronized*/ void setChangeMade(bool fireUpdate);
 /*public*/ /*synchronized*/ virtual void resetChangeMade();
 /*public*/ virtual void setLoading();
 /*public*/ virtual void finishLoading();
 /*public*/ int getComboBoxSelectionSize();
 /*public*/ virtual void setMultipleChoiceOption(QString strClass, QString choice, QString value);
 /*public*/ virtual void setTableColumnPreferences(QString table, QString column, int order, int width, int sort, bool hidden);

signals:

public slots:
private:
 /*private*/ /*static*/ class ComboBoxLastSelection {

     QString comboBoxName;// = NULL;
     QString lastValue;// = NULL;
public:
     ComboBoxLastSelection(QString comboBoxName, QString lastValue);
     QString getLastValue();
     void setLastValue(QString lastValue);
     QString getComboBoxName();

 };

 /*static*/ class WindowLocations {

     QPoint xyLocation;// = new Point(0, 0);
     QSize size;// = new Dimension(0, 0);
     bool saveSize;// = false;
     bool saveLocation;// = false;

     WindowLocations();
     QPoint getLocation();
     QSize getSize();
     void setSaveSize(bool b);
     void setSaveLocation(bool b);
     bool getSaveSize();
     bool getSaveLocation();
     void setLocation(QPoint xyLocation) ;
     void setSize(QSize size);
     void setProperty(QString key, QVariant value);
     QVariant getProperty(QString key);
     QSet<QString> getPropertyKeys();
 private:
     /*final*/ QMap<QString, QVariant> parameters;// = new HashMap<>();
     friend class JmriUserPreferencesManager;
 };

 /*static*/ class TableColumnPreferences {

 public:
     /**
      * SortOrder is an enumeration of the possible sort orderings.
      *
      * @see RowSorter
      * @since 1.6
      */
     /*public*/ enum SortOrder {
         /**
          * Enumeration value indicating the items are sorted in increasing order.
          * For example, the set <code>1, 4, 0</code> sorted in
          * <code>ASCENDING</code> order is <code>0, 1, 4</code>.
          */
         ASCENDING,

         /**
          * Enumeration value indicating the items are sorted in decreasing order.
          * For example, the set <code>1, 4, 0</code> sorted in
          * <code>DESCENDING</code> order is <code>4, 1, 0</code>.
          */
         DESCENDING,

         /**
          * Enumeration value indicating the items are unordered.
          * For example, the set <code>1, 4, 0</code> in
          * <code>UNSORTED</code> order is <code>1, 4, 0</code>.
          */
         UNSORTED
     };
     TableColumnPreferences(int order, int width, int sort, bool hidden) ;
     int getOrder();
     int getWidth();
     int getSort() ;
     bool getHidden();
 private:
     int order;
     int width;
     int sort;
     bool hidden;
 };


 /*private*/ /*final*/ static QString CLASSPREFS_NAMESPACE;// ="http://jmri.org/xml/schema/auxiliary-configuration/class-preferences-4-3-5.xsd"; // NOI18N
    /*private*/ /*final*/ static QString CLASSPREFS_ELEMENT;// ="classPreferences"; // NOI18N
    /*private*/ /*final*/ static QString COMBOBOX_NAMESPACE;// ="http://jmri.org/xml/schema/auxiliary-configuration/combobox-4-3-5.xsd"; // NOI18N
    /*private*/ /*final*/ static QString COMBOBOX_ELEMENT;// ="comboBoxLastValue"; // NOI18N
    /*private*/ /*final*/ static QString SETTINGS_NAMESPACE;// ="http://jmri.org/xml/schema/auxiliary-configuration/settings-4-3-5.xsd"; // NOI18N
    /*private*/ /*final*/ static QString SETTINGS_ELEMENT;// ="settings"; // NOI18N
    /*private*/ /*final*/ static QString TABLES_NAMESPACE;// ="http://jmri.org/xml/schema/auxiliary-configuration/table-details-4-3-5.xsd"; // NOI18N
    /*private*/ /*final*/ static QString TABLES_ELEMENT;// ="tableDetails"; // NOI18N
    /*private*/ /*final*/ static QString WINDOWS_NAMESPACE;// ="http://jmri.org/xml/schema/auxiliary-configuration/window-details-4-3-5.xsd"; // NOI18N
    /*private*/ /*final*/ static QString WINDOWS_ELEMENT;// ="windowDetails"; // NOI18N
    /*private*/ /*final*/ /*static*/ Logger* log;// = LoggerFactory.getLogger(JmriUserPreferencesManager.class);
 /*private*/ bool dirty;// = false;
 /*private*/ bool loading;// = false;
 /*private*/ bool _allowSave;
 /*private*/ QStringList simplePreferenceList;// = new ArrayList<>();
 //sessionList is used for messages to be suppressed for the current JMRI session only
 /*private*/ QStringList sessionPreferenceList;// = new ArrayList<>();
 /*private*/ QList<ComboBoxLastSelection*> _comboBoxLastSelection;// = new ArrayList<>();
 /*private*/ QMap<QString, WindowLocations*> windowDetails;// = new HashMap<>();
 /*private*/ QMap<QString, ClassPreferences*> classPreferenceList;// = new HashMap<>();
 /*private*/ QMap<QString, QMap<QString, TableColumnPreferences*> > tableColumnPrefs;// = new HashMap<>();
 /*private*/ File* file;
 /*private*/ void readComboBoxLastSelections();
 /*private*/ void readSimplePreferenceState();
 /*private*/ void saveSimplePreferenceState();
 /*private*/ void readTableColumnPreferences();
 /*private*/ void saveComboBoxLastSelections();
 /*private*/ void readPreferencesState();
 /*private*/ void savePreferencesState();
 /*private*/ void saveTableColumnPreferences();
 /*private*/ void readWindowDetails();
 QDomDocument doc;
 /*private*/ QDomElement readElement( QString elementName, QString _namespace);
 /*protected*/ void saveElement(/*@NonNULL */ QDomElement element);
 /*private*/ void savePreferences();
 /*private*/ void saveWindowDetails();

protected:
 /*protected*/ /*final*/ QString getClassName();
 /*protected*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);

 /*static*/ class MultipleChoice {

     QMap<int, QString> options;
     QString optionDescription;
     QString item;
     int value;// = -1;
     int defaultOption;// = -1;
 public:
     MultipleChoice(QString description, QString item, QMap<int, QString> options, int defaultOption);
     MultipleChoice(QString item, int value);
     void setValue(int value);
     void setValue(QString value);
     void setMessageItems(QString description, QMap<int, QString> options, int defaultOption);
     int getValue();
     int getDefaultValue();
     QString getItem();
     QString getOptionDescription();
     QMap<int, QString> getOptions();
 };

 /*static*/ class PreferenceList {

     // need to fill this with bits to get a meaning full description.
     bool set;// = false;
     QString item;// = "";
     QString description;// = "";
 public:
     PreferenceList(QString item);
     PreferenceList(QString item, bool state);
     PreferenceList(QString item, QString description);
     void setDescription(QString desc);
     QString getDescription();
     bool getState();
     void setState(bool state) ;
     QString getItem() ;
 };

 /**
  * Holds details about the speific class.
  */
 /*protected*/ /*static*/ class ClassPreferences
 {
    QString classDescription;

    QList<MultipleChoice*> multipleChoiceList;// = new ArrayList<MultipleChoice>();
    QList<PreferenceList*> preferenceList;// = new ArrayList<PreferenceList>();
 public:
    ClassPreferences() ;
    ClassPreferences(QString classDescription);
    QString getDescription();
    void setDescription(QString description);
    QList<PreferenceList*> getPreferenceList();
    QList<MultipleChoice*> getMultipleChoiceList();
    /*public*/ QString getPreferenceName(int n);
    /*public*/ QString getChoiceName(int n);
 private:
    void setDescription(const QString description) const;
    int getPreferenceListSize();
    int getPreferencesSize();
    int getMultipleChoiceListSize();


    friend class JmriUserPreferencesManager;

};





};
#endif // JMRIUSERPREFERENCESMANAGER_H
