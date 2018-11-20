#ifndef EDITCONNECTIONPREFERENCES_H
#define EDITCONNECTIONPREFERENCES_H
#include "appconfigbase.h"
#include <QtXml>
#include <QTabWidget>
#if 0
/*static*/ class PreferencesCatItems_e  : QObject
{//implements java.io.Serializable {
Q_OBJECT
    /*
     * This contains details of all list managedPreferences to be displayed in the
     * preferences
     */
    QString itemText;
    QString prefItem;
    int sortOrder;// = Integer.MAX_VALUE;
    QTabWidget* tabbedPane;// = new JTabbedPane();
    QStringList disableItemsList; // = new ArrayList<>();
    /*static*/ class TabDetails_e  : public QObject //implements java.io.Serializable
    {

        /* This contains all the JPanels that make up a preferences menus */
        QWidget* tabItem;
        QString tabTooltip;
        QString tabTitle;
        QWidget* tabPanel;// = new JPanel();
        /*private*/ /*final*/ int sortOrder;
public:
        TabDetails_e(QString labelkey, QString tabTit, QWidget* item,
                QString tooltip, int sortOrder);
        QString getToolTip() ;
        QString getTitle();
        QWidget* getPanel();
        QWidget* getItem();
        int getSortOrder();
    };

    /*private*/ /*final*/ QList<TabDetails_e*> tabDetailsArray;// = new ArrayList<>();
public:
    PreferencesCatItems_e(QString pref, QString title, int sortOrder);
    void addPreferenceItem(QString title, QString labelkey, QWidget* item,
            QString tooltip, int sortOrder);
    QString getPrefItem();
    QString getItemString();
    QWidget* getPanel();
    void gotoSubCategory(QString sub);
    friend class TabDetails_e;
    friend class EditConnectionPreferences;
};
#endif
class PreferencesCatItems;
class QHBoxLayout;
class TabbedPreferences;
class QPushButton;
class JList;
class EditConnectionPreferencesDialog;
class EditConnectionPreferences : public AppConfigBase
{
public:
 EditConnectionPreferences(EditConnectionPreferencesDialog *dialog, QWidget *parent = nullptr);
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ bool isMultipleInstances();
 /*public*/ void init();
 /*public*/ void addPreferencesPanel(PreferencesPanel* panel);
 /*public*/ void gotoPreferenceItem(QString selection, QString subCategory);
 /*public*/ QStringList getPreferenceMenuList();
 /*public*/ bool isPreferencesValid();
 /*public*/ void savePressed(bool restartRequired);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("EditConnectionPreferences");
 /**
  * The dialog that displays the preferences.
  * Used by the quit button to dispose the dialog.
  */
 /*final*/ EditConnectionPreferencesDialog* dialog;
 QDomNodeList preferencesElements;// = new ArrayList<>();
 QWidget* detailpanel;
 QList<PreferencesCatItems*> preferencesArray;// = new ArrayList<>();
 QWidget* buttonpanel;
 JList*  list;
 QPushButton* save;
 QPushButton* quit = nullptr;
 //QScrollArea* listScroller;
 /*private*/ TabbedPreferences* getTabbedPreferences();
 bool isDirty();
 bool invokeSaveOptions();
 void selection(QString view);
 /*private*/ void addItem(QString prefItem, QString itemText, QString tabTitle,
         QString labelKey, PreferencesPanel* item, QString tooltip, int sortOrder);
 int getCategoryIndexFromString(QString category);
 void updateJList();
 QHBoxLayout* buttonPanelLayout;

protected:
 /*protected*/ QStringList getChoices();
friend class EditConnectionPreferencesDialog;
};

#endif // EDITCONNECTIONPREFERENCES_H
