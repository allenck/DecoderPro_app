#ifndef TABBEDPREFERENCES_H
#define TABBEDPREFERENCES_H
#include "appconfigbase.h"
#include <QtXml>
#include "libpref_global.h"
#include "preferencessubpanel.h"
#include "jtabbedpane.h"

class QSplitter;
class TabDetails;
//class QStackedWidget;
class PropertyChangeEvent;
class QListWidget;
class QTabWidget;
class QScrollArea;
class QPushButton;
class PreferencesCatItems;
class LIBPREFSHARED_EXPORT TabbedPreferences : public AppConfigBase
{
    Q_OBJECT
 //Q_INTERFACES(PreferencesPanel PreferencesSubPanel)

public:
    explicit TabbedPreferences(QWidget *parent = 0);
    enum STATES
    {
     UNINITIALISED = 0x00,
     INITIALISING = 0x01,
     INITIALISED = 0x02
    };
    /*public*/ static /*final*/ QString INITIALIZATION;// = "PROP_INITIALIZATION";
    virtual
    /*public*/ QString getHelpTarget();
    virtual
    /*public*/ QString getTitle();
    virtual
    /*public*/ bool isMultipleInstances();
    /*public*/ /*synchronized*/ int init();
    //int startInit();
    /*public*/ int getInitialisationState();
    /*public*/ bool isInitialised();
//    /*public*/ void setUIFontSize(float size);
//    /*public*/ void setUIFont(FontUIResource f);
    /*public*/ void addPreferencesPanel(PreferencesPanel* panel);
    /* Method allows for the preference to goto a specific list item */
    /*public*/ void gotoPreferenceItem(QString selection, QString subCategory);
    /*public*/ QStringList getPreferenceMenuList();
    /*public*/ QStringList getPreferenceSubCategory(QString category);
    /*public*/ void disablePreferenceItem(QString selection, QString subCategory);
    /*public*/ void setUIFontSize(float size);
    /*public*/ bool isPreferencesValid();


//    /*static*/ class PreferencesCatItems : public QObject
//    {
//     /**
//      *
//      */
//     //private static final long serialVersionUID = 5928584215129175250L;
//     /*
//      * This contains details of all list items to be displayed in the
//      * preferences
//      */
//     QString itemText;
//     QString prefItem;
//     QTabWidget* tabbedPane;// = new QTabWidget();
//     QStringList disableItemsList;// = new ArrayList<>();
//     /*static*/ class TabDetails : public QObject
//     {
//      /**
//       *
//       */
//      //private static final long serialVersionUID = -7077354592762639878L;
//      /* This contains all the JPanels that make up a preferences menus */
//      QWidget* tabItem;
//      QString tabTooltip;
//      QString tabTitle;
//      QWidget* tabPanel;// = new JPanel();
//      //bool store;
//     public:
//      TabDetails(QString labelkey, QString tabTit, QWidget* item,
//                QString tooltip);
//      QString getToolTip() ;
//      QString getTitle();
//      QWidget* getPanel() ;
//      QWidget* getItem();
//     }; // end TabDetails class
//    QList<TabDetails*> TabDetailsArray;// = new ArrayList<>();
//    public:
//      PreferencesCatItems(QString pref, QString title, int sortOrder) ;
//      void addPreferenceItem(QString title, QString labelkey, QWidget* item, QString tooltip) ;
//      QString getPrefItem() ;
//      QString getItemString();
//      QStringList getSubCategoriesList();
//      QWidget* getPanel() ;
//      void gotoSubCategory(QString sub);
//      void disableSubCategory(QString sub);
//    }; // end PreferencesCatItem class
signals:
 void propertyChange(PropertyChangeEvent*);
public slots:
    void On_save_clicked();
    void On_list_selection(int);
private:
    QList<QDomElement> preferencesElements;// = new ArrayList<>();
    //QMap<QString, PreferencesPanel*> preferencesPanels;// = QMap<QString, PreferencesPanel*>();

//    QStackedWidget* detailpanel;// = new JPanel();

    QList<PreferencesCatItems*> preferencesArray;// = QList<PreferencesCatItems*>();
    QWidget* buttonpanel;
    QListWidget* list;
    QPushButton* save;
    QSplitter* splitter;
    int initialisationState;// = 0x00;
    int currSplitterWidget = 1;
    ///*private*/ static final long serialVersionUID = -6266891995866315885L;
    /*private*/ void setInitalisationState(int state);
    /*private*/ bool invokeSaveOptions();
    void selection(QString view);
    /*private*/ void addItem(QString prefItem, QString itemText, QString tabtitle, QString labelKey, PreferencesPanel* item, QString tooltip, int sortOrder, QString className);
    int getCategoryIndexFromString(QString category);
    void updateJList();
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("TabbedPreferences");
    bool isDirty();
    QMap<QString, int> widgetIndexes;

protected:
    /*protected*/ QStringList getChoices();
friend class TabbedPreferencesFrame;
friend class EditConnectionPreferences;
};

/*static*/ class PreferencesCatItems : public QObject
{
 Q_OBJECT
 //Q_INTERFACES(PreferencesPanel PreferencesSubPanel)
    /**
     *
     */
    //private static final long serialVersionUID = 5928584215129175250L;
    /*
     * This contains details of all list managedPreferences to be displayed in the
     * preferences
     */
    QString itemText;
    QString prefItem;
    int sortOrder;// = Integer.MAX_VALUE;
    JTabbedPane* tabbedPane;// = new JTabbedPane();
    //QWidget* nonTabbedPane = nullptr;
    QList<QString> disableItemsList;// = new QList<>();

    QList<TabDetails*> tabDetailsArray;// = new ArrayList<>();
    TabbedPreferences* tabbedPreferences;

public:

    PreferencesCatItems(QString pref, QString title, int sortOrder, TabbedPreferences* tabbedPreferences);
    void addPreferenceItem(QString title, QString labelkey, QWidget* item,
            QString tooltip, int sortOrder, QString className) ;
    QString getPrefItem();
    QString getItemString();
    QList<QString> getSubCategoriesList();
    QWidget* getPanel();
    void gotoSubCategory(QString sub);
    void disableSubCategory(QString sub);
    int getSortOrder();
    void setSortOrder(int sortOrder);
 friend class EditConnectionPreferences;
};

/*static*/ class TabDetails : public QObject
{
Q_OBJECT
 //Q_INTERFACES(PreferencesPanel PreferencesSubPanel)
    /**
     *
     */
   //private static final long serialVersionUID = -7077354592762639878L;
    /* This contains all the JPanels that make up a preferences menus */
    QWidget* tabItem;
    QString tabTooltip;
    QString tabTitle;
    QWidget* tabPanel;// = new JPanel();
    //boolean store;
    int sortOrder = 0;
    QString _className;
public:
    TabDetails(QString labelkey, QString tabTit, QWidget* item,
            QString tooltip, int sortOrder, QString className) ;
    QString getToolTip();
    QString getTitle();
    QWidget* getPanel();
    QWidget* getItem() ;
    void setSortOrder(int sortOrder);
    int getSortOrder();
    QString className();
};
#endif // TABBEDPREFERENCES_H
