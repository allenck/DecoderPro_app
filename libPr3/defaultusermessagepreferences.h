#ifndef DEFAULTUSERMESSAGEPREFERENCES_H
#define DEFAULTUSERMESSAGEPREFERENCES_H
#include "userpreferencesmanager.h"
#include "logger.h"
#include <QMutex>
#include <QFile>
#include <QStringList>
#include "propertychangelistener.h"
#include <QVector>
#include "quietshutdowntask.h"
#include "exceptions.h"
//#include "indexoutofboundsexception.h"
#include <QSet>
#include "libPr3_global.h"

class DefaultUserMessagePreferences;
class LIBPR3SHARED_EXPORT UserPreferencesShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
  public:
    explicit UserPreferencesShutDownTask(QString name, DefaultUserMessagePreferences *parent);
    /*public*/  /*public*/ bool doAction();
private:
    Logger* log;
    DefaultUserMessagePreferences *parent;
};
/*static*/ class MultipleChoice{

    QMap<int, QString> options;
    QString optionDescription;
    QString item;
    int value;// = -1;
    int defaultOption;// = -1;
public:
    MultipleChoice(QString description, QString item, QMap<int, QString> options, int defaultOption)
    {
     init();
     this->item = item;
     setMessageItems(description, options, defaultOption);
    }

    MultipleChoice(QString item, int value)
    {
     init();
     this->item = item;
     this->value = value;
    }

    void init()
    {
     value = -1;
     defaultOption = -1;
    }

    void setValue(int value)
    {
     this->value = value;
    }

    void setValue(QString value)
    {
     foreach(QVariant o, options.keys())
     {
      if(options.value(o.toInt())==(value))
      {
       this->value = o.toInt();
      }
     }
    }

    void setMessageItems(QString description, QMap<int, QString> options, int defaultOption)
    {
     optionDescription = description;
     this->options = options;
     this->defaultOption = defaultOption;
     if (value==-1)
      value = defaultOption;
    }

    int getValue() { return value; }

    int getDefaultValue() { return defaultOption; }

    QString getItem(){ return item; }

    QString getOptionDescription() { return optionDescription; }

    QMap<int, QString> getOptions() { return options; }

};

/*static*/ class PreferenceList{
    // need to fill this with bits to get a meaning full description.
    bool set;// = false;
    QString item;// = "";
    QString description;// = "";
public:
    PreferenceList(QString item)
    {
     this->item = item;
     set = false;
     description = "";
    }

    PreferenceList(QString item, bool state)
    {
     this->item = item;
     set = false;
     description = "";
     set=state;
    }

    PreferenceList(QString item, QString description)
    {
     this->description = description;
     this->item = item;
    }

    void setDescription(QString desc)
    {
     description = desc;
    }

    QString getDescription()
    {
     return description;
    }

    bool getState()
    {
     return set;
    }

    void setState(bool state)
    {
     this->set=state;
    }

    QString getItem()
    {
     return item;
    }

};

/**
 * Holds details about the specific class.
 */
/*static*/ class ClassPreferences
{
    QString classDescription;

    QList<MultipleChoice*>* multipleChoiceList;// = new QList<MultipleChoice*>();
    QList<PreferenceList*>* preferenceList;// = new QList<PreferenceList*>();
public:
    ClassPreferences()
    {
     multipleChoiceList =  new QList<MultipleChoice*>();
     preferenceList =  new QList<PreferenceList*>();
    }

    ClassPreferences(QString classDescription)
    {
     multipleChoiceList =  new QList<MultipleChoice*>();
     preferenceList =  new QList<PreferenceList*>();
     this->classDescription = classDescription;
    }

    QString getDescription ()
    {
     return classDescription;
    }

    void setDescription (QString description)
    {
     classDescription = description;
    }

    QList<PreferenceList*>* getPreferenceList()
    {
     return preferenceList;
    }

    int getPreferenceListSize() { return preferenceList->size(); }

    QList<MultipleChoice*>* getMultipleChoiceList()
    {
     return multipleChoiceList;
    }

    int getPreferencesSize()
    {
     return multipleChoiceList->size()+preferenceList->size();
    }

    /*public*/ QString getPreferenceName(int n)
    {
     try
     {
      return preferenceList->value(n)->getItem();
     }
     catch (IndexOutOfBoundsException ioob)
     {
      return NULL;
     }
    }

    int getMultipleChoiceListSize() { return multipleChoiceList->size(); }

    /*public*/ QString getChoiceName(int n)
    {
        try{
            return multipleChoiceList->value(n)->getItem();
        } catch (IndexOutOfBoundsException ioob) {
            return NULL;
        }
    }
};



/*static*/ class WindowLocations{
    QPoint xyLocation;// = new QPoint(0,0);
    QSize size;// = QSize (0,0);
    bool saveSize;// = false;
    bool saveLocation;// = false;
public:
    WindowLocations()
    {
     xyLocation =  QPoint(0,0);
     size = QSize (0,0);
     saveSize = false;
     saveLocation = false;
    }

    QPoint getLocation(){
    return xyLocation; }

    QSize getSize() { return size; }

    void setSaveSize(bool b){
        saveSize = b;
    }

    void setSaveLocation(bool b){
        saveLocation = b;
    }

    bool getSaveSize(){
        return saveSize;
    }

    bool getSaveLocation(){
        return saveLocation;
    }

    void setLocation(QPoint xyLocation) {
        this->xyLocation = xyLocation;
        saveLocation = true;
    }

    void setSize(QSize size) {
        this->size = size;
        saveSize=true;
    }

    void setProperty(QString key, QVariant value)
    {
     if (parameters.isEmpty())
      parameters =  QHash<QString, QVariant>();
     parameters.insert(key, value);
    }

    QVariant getProperty(QString key)
    {
     if (parameters.isEmpty()) return QVariant();
      return parameters.value(key);
    }

    QSet<QString> getPropertyKeys()
    {
     if (parameters.isEmpty()) return QSet<QString>();
     return parameters.keys().toSet();
    }

    QHash<QString, QVariant> parameters;// = NULL;

};

/*static*/ class TableColumnPreferences{

    int order;
    int width;
    int sort;
    bool hidden;
public:
    TableColumnPreferences(int order, int width, int sort, bool hidden){
        this->order = order;
        this->width = width;
        this->sort = sort;
        this->hidden = hidden;
    }

    int getOrder(){
        return order;
    }

    int getWidth(){
        return width;
    }

    int getSort(){
        return sort;
    }
    bool getHidden(){
        return hidden;
    }
};
class ShutDownTask;
//class QuietShutDownTask;
class ComboBoxLastSelection;
class PropertyChangeListener;
//class WindowLocations;
//class ClassPreferences;
class MultipleChoice;
class TableColumnPreferences;
class LIBPR3SHARED_EXPORT DefaultUserMessagePreferences : public UserPreferencesManager
{
    Q_OBJECT
public:
    explicit DefaultUserMessagePreferences(QObject *parent = 0);
 ~DefaultUserMessagePreferences() {}
 DefaultUserMessagePreferences(const DefaultUserMessagePreferences&) {}
    /*public*/ static DefaultUserMessagePreferences* getInstance();
    /*public*/ /*synchronized*/ void allowSave() ;
    /*public*/ /*synchronized*/ void disallowSave() ;
    /*public*/ QSize getScreen();
    /*public*/ void setSimplePreferenceState(QString name, bool state);
    /*public*/ QStringList getSimplePreferenceStateList();
    /*public*/ bool getSimplePreferenceState(QString name);
    /*public*/ void setPreferenceState(QString strClass, QString item, bool state);
    /*public*/ bool getPreferenceState(QString strClass, QString item);
    /*public*/ void preferenceItemDetails(QString strClass, QString item, QString description);
    /*public*/ QStringList getPreferenceList(QString strClass);
    /*public*/ QString getPreferenceItemName(QString strClass, int n);
    /*public*/ QString getPreferenceItemDescription(QString strClass, QString item);
    /*public*/ void setSessionPreferenceState(QString name, bool state) ;
    /*public*/ bool getSessionPreferenceState(QString name);
    /*public*/ void showInfoMessage(QString title, QString message, QString strClass, QString item);
    /*public*/ void showInfoMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, Level* level);
    /*public*/ void showErrorMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember);
    /*public*/ void addComboBoxLastSelection(QString comboBoxName, QString lastValue);
    /*public*/ QString getComboBoxLastSelection(QString comboBoxName);
    /*public*/ void setComboBoxLastSelection(QString comboBoxName, QString lastValue);
    /*public*/ int getComboBoxSelectionSize();
    /*public*/ QString getComboBoxName(int n);
    /*public*/ QString getComboBoxLastSelection(int n);
    /*public*/ /*synchronized*/ bool getChangeMade();
    /*public*/ /*synchronized*/ void setChangeMade(bool fireUpdate);
    /*public*/ /*synchronized*/ void resetChangeMade();
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void setLoading();
    /*public*/ void finishLoading();
    /*public*/ void displayRememberMsg();
    /*public*/ QPoint getWindowLocation(QString strClass);
    /*public*/ QSize getWindowSize(QString strClass);
    /*public*/ bool getSaveWindowSize(QString strClass);
    /*public*/ bool getSaveWindowLocation(QString strClass);
    /*public*/ void setSaveWindowSize(QString strClass, bool b);
    /*public*/ void setSaveWindowLocation(QString strClass, bool b);
    /*public*/ void setWindowLocation(QString strClass, QPoint location);
    /*public*/ void setWindowSize(QString strClass, QSize dim);
    /*public*/ QStringList getWindowList();
    /*public*/ void setProperty(QString strClass, QString key, QVariant value) ;
    /*public*/ QVariant getProperty(QString strClass, QString key);
    /*public*/ QSet<QString> getPropertyKeys(QString strClass);
    /*public*/ bool isWindowPositionSaved(QString strClass);
    /*public*/ QString getClassDescription(QString strClass);
    /*public*/ QStringList getPreferencesClasses();
    /*public*/ void setClassDescription(QString strClass);
    /*public*/ void messageItemDetails(QString strClass, QString item, QString description, QStringList msgOption, QList<int> msgNumber, int defaultOption);
    /*public*/ void messageItemDetails(QString strClass, QString item, QString description, QMap<int, QString> options, int defaultOption);
    /*public*/ QMap<int, QString> getChoiceOptions(QString strClass, QString item);
    /*public*/ int getMultipleChoiceSize(QString strClass);
    /*public*/ QStringList getMultipleChoiceList(QString strClass);
    /*public*/ QString getChoiceName(QString strClass, int n);
    /*public*/ QString getChoiceDescription(QString strClass, QString item);
    /*public*/ int getMultipleChoiceOption (QString strClass, QString item);
    /*public*/ int getMultipleChoiceDefaultOption (QString strClass, QString choice);
    /*public*/ void setMultipleChoiceOption (QString strClass, QString choice, QString value);
    /*public*/ void setMultipleChoiceOption (QString strClass, QString choice, int value);
    /*public*/ void setTableColumnPreferences(QString table, QString column, int order, int width, int sort, bool hidden);
    /*public*/ int getTableColumnOrder(QString table, QString column);
    /*public*/ int getTableColumnWidth(QString table, QString column);
    /*public*/ int getTableColumnSort(QString table, QString column);
    /*public*/ bool getTableColumnHidden(QString table, QString column);
    /*public*/ QString getTableColumnAtNum(QString table, int i);
    /*public*/ QStringList getTablesList();
    /*public*/ QStringList getTablesColumnList(QString table);
    /*public*/ QString getClassDescription();
    /*public*/ int getPreferencesSize(QString strClass);
    /*public*/ void readUserPreferences();
    ShutDownTask* getShutDownTask();
signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
 /*private*/ bool _allowSave;// = true;
  Logger* log;
  QMutex mutex;
  QStringList simplePreferenceList;// =  QStringLIst();
  //sessionList is used for messages to be suppressed for the current JMRI session only
  QStringList sessionPreferenceList;// =  QStringList();
  ShutDownTask* userPreferencesShutDownTask;// = NULL;
  QList <ComboBoxLastSelection*> _comboBoxLastSelection;// = new ArrayList<ComboBoxLastSelection>();
  /*private*/ static /*volatile*/ bool _changeMade;// = false;
  // data members to hold contact with the property listeners
  /*final*/ /*private*/ QVector<PropertyChangeListener*>* listeners;// = new QVector<PropertyChangeListener*>();
  /*private*/ static /*volatile*/ bool _loading;// = false;
  QHash<QString, WindowLocations*> windowDetails;// = new QHash<String, WindowLocations>();
  QHash<QString, ClassPreferences*> classPreferenceList;// = new QHash<String, ClassPreferences*>();
  QHash<QString, QHash<QString, TableColumnPreferences*> > tableColumnPrefs;// =  QHash<QString, QHash<QString,TableColumnPreferences*>*>();
  QFile* file;
  /*private*/ void showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item, /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type);

protected:
  /*protected*/ void notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue);
  /*protected*/ QString getClassName();
friend class UserPreferencesShutDownTask;
};

Q_DECLARE_METATYPE(DefaultUserMessagePreferences)
/*private*/ /*static*/ class ComboBoxLastSelection
{
    QString comboBoxName;// = NULL;
    QString lastValue;// = NULL;
public:
    ComboBoxLastSelection(QString comboBoxName, QString lastValue)
    {
     this->comboBoxName = comboBoxName;
     this->lastValue = lastValue;
    }

    QString getLastValue(){ return lastValue; }

    void setLastValue(QString lastValue){ this->lastValue = lastValue; }

    QString getComboBoxName() {return comboBoxName; }

};


#endif // DEFAULTUSERMESSAGEPREFERENCES_H
