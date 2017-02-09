#ifndef TABBEDPREFERENCES_H
#define TABBEDPREFERENCES_H
#include "appconfigbase.h"
#include <QtXml>
#include "libpref_global.h"

class TabDetails;
class QStackedWidget;
class PropertyChangeEvent;
class QListWidget;
class QTabWidget;
class QScrollArea;
class QPushButton;
class PreferencesCatItems;
class LIBPREFSHARED_EXPORT TabbedPreferences : public AppConfigBase
{
    Q_OBJECT
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
    int startInit();
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

    /*static*/ class PreferencesCatItems : public QObject
    {
     /**
      *
      */
     //private static final long serialVersionUID = 5928584215129175250L;
     /*
      * This contains details of all list items to be displayed in the
      * preferences
      */
     QString itemText;
     QString prefItem;
     QTabWidget* tabbedPane;// = new QTabWidget();
     QStringList disableItemsList;// = new ArrayList<>();
     /*static*/ class TabDetails : public QObject
     {
      /**
       *
       */
      //private static final long serialVersionUID = -7077354592762639878L;
      /* This contains all the JPanels that make up a preferences menus */
      QWidget* tabItem;
      QString tabTooltip;
      QString tabTitle;
      QWidget* tabPanel;// = new JPanel();
      //bool store;
     public:
      TabDetails(QString labelkey, QString tabTit, QWidget* item,
                QString tooltip);
      QString getToolTip() ;
      QString getTitle();
      QWidget* getPanel() ;
      QWidget* getItem();
     }; // end TabDetails class
    QList<TabDetails*> TabDetailsArray;// = new ArrayList<>();
    public:
      PreferencesCatItems(QString pref, QString title) ;
      void addPreferenceItem(QString title, QString labelkey, QWidget* item, QString tooltip) ;
      QString getPrefItem() ;
      QString getItemString();
      QStringList getSubCategoriesList();
      QWidget* getPanel() ;
      void gotoSubCategory(QString sub);
      void disableSubCategory(QString sub);
    }; // end PreferencesCatItem class
signals:
 void propertyChange(PropertyChangeEvent*);
public slots:
    void On_save_clicked();
    void On_list_selection(int);
private:
    QList<QDomElement> preferencesElements;// = new ArrayList<>();
    //QMap<QString, PreferencesPanel*> preferencesPanels;// = QMap<QString, PreferencesPanel*>();

    QStackedWidget* detailpanel;// = new JPanel();

    QList<PreferencesCatItems*> preferencesArray;// = QList<PreferencesCatItems*>();
    QWidget* buttonpanel;
    QListWidget* list;
    QPushButton* save;
    //QScrollArea* listScroller;
    int initialisationState;// = 0x00;
    ///*private*/ static final long serialVersionUID = -6266891995866315885L;
    /*private*/ void setInitalisationState(int state);
    /*private*/ bool invokeSaveOptions();
    void selection(QString View);
    /*private*/ void addItem(QString prefItem, QString itemText, QString tabtitle, QString labelKey, PreferencesPanel* item, bool store, QString tooltip);
    int getCategoryIndexFromString(QString category);
    void updateJList();
Logger* log;
    bool isDirty();

protected:
    /*protected*/ QStringList getChoices();
friend class TabbedPreferencesFrame;
};
/*static*/ class PreferencesCatItems : QObject
{
 Q_OBJECT
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
        QTabWidget* tabbedPane;// = new JTabbedPane();
        QList<QString> disableItemsList;// = new QList<>();

        QList<TabDetails*> TabDetailsArray;// = new ArrayList<>();
        TabbedPreferences* tabbedPreferences;
public:

        PreferencesCatItems(QString pref, QString title, TabbedPreferences* tabbedPreferences);
        void addPreferenceItem(QString title, QString labelkey, QWidget* item,
                QString tooltip) ;
        QString getPrefItem();
        QString getItemString();
        QList<QString> getSubCategoriesList();
        QWidget* getPanel();
        void gotoSubCategory(QString sub);
        void disableSubCategory(QString sub);
        };

        /*static*/ class TabDetails : public QObject
{
Q_OBJECT
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
public:
            TabDetails(QString labelkey, QString tabTit, QWidget* item,
                    QString tooltip) ;
            QString getToolTip();
            QString getTitle();
            QWidget* getPanel();
            QWidget* getItem() ;
    };
#endif // TABBEDPREFERENCES_H
