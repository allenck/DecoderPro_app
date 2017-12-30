#include "tabbedpreferences.h"
#include <QList>
#include <QTabWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QListWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QIcon>
#include "fileutil.h"
#include <QMetaObject>
#include "jseparator.h"
#include "preferencessubpanel.h"
#include "propertychangeevent.h"
#include <QStackedWidget>
#include <QMetaType>
#include "connectionspreferencespanel.h"
#include "programmerconfigpane.h"
//#include "createbuttonpanel.h"
//#include "performactionpanel.h"
#include "createbuttonmodel.h"
#include "performactionmodel.h"
#include "managerdefaultsconfigpane.h"
#include "filelocationpane.h"
#include "guilafconfigpane.h"
#include "throttlespreferencespane.h"
#include "usermessagepreferencespane.h"
#include <performfilepanel.h>
#include "rosterconfigpane.h"
#include "guilocalepreferencespanel.h"
#include "railroadnamepreferencespanel.h"
#include "profilepreferencespanel.h"
#include "signalheadtableaction.h"
#include "turnouttableaction.h"
#include "metatypes.h"
#include "loggerfactory.h"

//TabbedPreferences::TabbedPreferences(QObject *parent) :
//    AppConfigBase(parent)
//{
//}
/**
 * Provide access to preferences via a tabbed pane.
 *
 * Preferences panels listed in the PreferencesPanel property of the
 * apps.AppsStructureBundle ResourceBundle will be automatically loaded if they
 * implement the {@link jmri.swing.PreferencesPanel} interface.
 *
 * Other Preferences Panels will need to be manually added to this file in a
 * manner similar to the WiThrottlePrefsPanel.
 *
 * @author Bob Jacobsen Copyright 2010
 * @author Randall Wood 2012
 * @version $Revision: 28419 $
 */
// /*public*/ class TabbedPreferences extends AppConfigBase {

//@Override
/*public*/ QString TabbedPreferences::getHelpTarget() {
    return "package.apps.TabbedPreferences";
}

//@Override
/*public*/ QString TabbedPreferences::getTitle() {
    return tr("Preferences");
}

//@Override
/*public*/ bool TabbedPreferences::isMultipleInstances() {
    return false;
}

// only one of these!
/*public*/ /*static*/ /*final*/ QString TabbedPreferences::INITIALIZATION = "PROP_INITIALIZATION";


/*public*/ TabbedPreferences::TabbedPreferences(QWidget *parent)
    : AppConfigBase(parent)
{
 preferencesElements =  QList<QDomElement>();
 //preferencesPanels = QMap<QString, PreferencesPanel*>();
 detailpanel = new QStackedWidget();
 detailpanel->resize(300, 400);
 preferencesArray = QList<PreferencesCatItems*>();
 initialisationState = 0x00;
 log->setDebugEnabled(true);

 /*
  * Adds the place holders for the menu items so that any items add by
  * third party code is added to the end
  */
  preferencesArray.append(new PreferencesCatItems("CONNECTIONS", tr("Connections")));

  preferencesArray.append(new PreferencesCatItems("DEFAULTS", tr("Defaults")));

  preferencesArray.append(new PreferencesCatItems("FILELOCATIONS", tr("File Location")));

  preferencesArray.append(new PreferencesCatItems("STARTUP", tr("StartUp")));

  preferencesArray.append(new PreferencesCatItems("DISPLAY", tr("Display")));

  preferencesArray.append(new PreferencesCatItems("MESSAGES", tr("Messages")));

  preferencesArray.append(new PreferencesCatItems("ROSTER", tr("Roster")));

  preferencesArray.append(new PreferencesCatItems("THROTTLE", tr("Throttle")));

  preferencesArray.append(new PreferencesCatItems("WITHROTTLE",tr("WiThrottle")));
  new Metatypes();
}

//@SuppressWarnings("rawtypes")
/*public*/ /*synchronized*/ int TabbedPreferences::init()
{
 if (initialisationState == INITIALISED)
 {
  return INITIALISED;
 }
 if (initialisationState != UNINITIALISED)
 {
  return initialisationState;
 }
 return UNINITIALISED;
}
int TabbedPreferences::startInit()
{
 this->setInitalisationState(INITIALISING);
 setWindowTitle(getTitle());

 list = new QListWidget();
//    listScroller = new JScrollPane(list);
//    listScroller.setPreferredSize(new Dimension(100, 100));

 buttonpanel = new QWidget();
 QVBoxLayout* buttonPanelLayout;
 buttonpanel->setLayout(buttonPanelLayout = new QVBoxLayout); //(buttonpanel, BoxLayout.Y_AXIS));
//    buttonpanel.setBorder(BorderFactory.createEmptyBorder(6, 6, 6, 3));

// detailpanel = new QWidget();
// QFormLayout* detailPanelLayout;
// detailpanel->setLayout(detailPanelLayout = new QFormLayout); //CardLayout());
    //detailpanel.setBorder(BorderFactory.createEmptyBorder(6, 3, 6, 6));

//    save = new QPushButton(
//            tr("ButtonSave"),
//            new ImageIcon(
//                    FileUtil::findExternalFilename("program:resources/icons/misc/gui3/SaveIcon.png")));
 save = new QPushButton( QIcon(FileUtil::getExternalFilename("program:resources/icons/misc/gui3/SaveIcon.png")),tr("Save"));
//    save.addActionListener((ActionEvent e) -> {
//        savePressed(invokeSaveOptions());
//    });
 connect(save, SIGNAL(clicked()), this, SLOT(On_save_clicked()));
 QHBoxLayout* thisLayout;
 setMinimumSize(400, 300);
 setLayout(thisLayout = new QHBoxLayout); //(this, BoxLayout.X_AXIS));

//    try
//    {
//      QStringList classNames = (new ObjectMapper()).readValue(
//                ResourceBundle.getBundle("apps.AppsStructureBundle").getString("PreferencesPanels"),
//                new TypeReference<List<String>>() {
//                });
#if 0
 [ "jmri.jmrix.swing.ConnectionsPreferencesPanel", "apps.ManagerDefaultsConfigPane", "apps.FileLocationPane", "apps.PerformActionPanel", /*"apps.CreateButtonPanel",*/ "apps.PerformFilePanel", "apps.PerformScriptPanel", "apps.GuiLafConfigPane", "apps.GuiLocalePreferencesPanel", "apps.SystemConsoleConfigPanel", "jmri.jmrit.beantable.usermessagepreferences.UserMessagePreferencesPane", "jmri.jmrit.symbolicprog.ProgrammerConfigPane", "jmri.jmrit.roster.RosterConfigPane", "jmri.jmrit.throttle.ThrottlesPreferencesPane", "jmri.jmrit.withrottle.WiThrottlePrefsPanel", "jmri.profile.ProfilePreferencesPanel", "jmri.jmris.json.JsonServerPreferencesPanel", "jmri.web.server.RailroadNamePreferencesPanel", "jmri.web.server.WebServerPreferencesPanel", "jmri.jmrit.logix.WarrantPreferencesPanel" ]
#endif
 QStringList classNames = QStringList()
  << QString("ConnectionsPreferencesPanel") << QString( "ManagerDefaultsConfigPane") << QString( "FileLocationPane" ) /*<< QString( "PerformActionPanel")*/ /*<< QString("CreateButtonPanel")*/ << QString( "PerformFilePanel") << QString("GuiLafConfigPane") << QString("GuiLocalePreferencesPanel") << QString( "SystemConsoleConfigPanel") << QString("UserMessagePreferencesPane") << QString( "ProgrammerConfigPane") << QString("RosterConfigPane") << QString( "ThrottlesPreferencesPane") << QString("WiThrottlePrefsPanel") << QString( "ProfilePreferencesPanel") << QString("JsonServerPreferencesPanel") << QString( "RailroadNamePreferencesPanel") << QString("WebServerPreferencesPanel") << QString("WarrantPreferencesPanel") <<
     QString("StartupActionsPreferencesPanel");
 foreach (QString className,classNames)
 {
//      try
//      {
  PreferencesPanel* panel = NULL;

  //PreferencesPanel panel = (PreferencesPanel) Class.forName(className).newInstance();
  int id = QMetaType::type(className.toLocal8Bit());
  if(id != 0)
  {
#if QT_VERSION < 0x050000
   panel = (PreferencesPanel*)QMetaType::construct(id);
#else
   panel = (PreferencesPanel*)QMetaType::create(id);
#endif

  //if (panel instanceof PreferencesSubPanel)
  if(qobject_cast<PreferencesSubPanel*>(panel)!=NULL)
  {
   className = ((PreferencesSubPanel*) panel)->getParentClassName();
   if (!this->getPreferencesPanels()->contains(className))
   {
    int id = QMetaType::type(className.toLocal8Bit());
    if(id > 0)
    {
#if QT_VERSION < 0x050000
     this->addPreferencesPanel((PreferencesPanel*) QMetaType::construct(id));
#else
     this->addPreferencesPanel((PreferencesPanel*) QMetaType::create(id));
#endif
    }
    else
     log->error("Unable to add preferences class (" + className + ")"/*, e*/);
   }
   PreferencesPanel* parentPanel = this->getPreferencesPanels()->value(className);
   ((PreferencesSubPanel*) panel)->setParent(parentPanel);
  }
  this->addPreferencesPanel(panel);
 }
 //catch (ClassNotFoundException | InstantiationException | IllegalAccessException e) {
 else
  log->error("Unable to add preferences class (" + className + ")"/*, e*/);
 }
//}
//   } catch (Exception e) {
//        log->error("Unable to parse PreferencePanels property", e);
//    }
 foreach (PreferencesCatItems* preferences, preferencesArray)
 {
  detailpanel->addWidget(preferences->getPanel());
  //detailpanel->addWidget(preferences->getPrefItem());
  detailpanel->setWindowTitle(preferences->getPrefItem());
 }

 updateJList();
 thisLayout->addWidget(buttonpanel);
 thisLayout->addWidget(new JSeparator(JSeparator::VERTICAL));
 thisLayout->addWidget(detailpanel);

 list->setCurrentRow(0);
// selection(preferencesArray.get(0).getPrefItem());
 this->setInitalisationState(INITIALISED);
 return initialisationState;
}

void TabbedPreferences::On_save_clicked()
{
 savePressed(invokeSaveOptions());
}

/*private*/ void TabbedPreferences::setInitalisationState(int state)
{
    int old = this->initialisationState;
    this->initialisationState = state;
    //this->firePropertyChange(INITIALIZATION, old, state);
    emit propertyChange(new PropertyChangeEvent(this,INITIALIZATION, old, state));
}

/*public*/ int TabbedPreferences::getInitialisationState() {
    return this->initialisationState;
}

/*public*/ bool TabbedPreferences::isInitialised() {
    return (this->getInitialisationState() == INITIALISED);
}

// package only - for TabbedPreferencesFrame
bool TabbedPreferences::isDirty()
{
 foreach (PreferencesPanel* panel, this->getPreferencesPanels()->values())
 {
  if (log->isDebugEnabled())
  {
   log->debug(tr("PreferencesPanel %1 (%2) is %3.").arg(
           panel->metaObject()->className()).arg(
           (panel->getTabbedPreferencesTitle() != "") ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
           (panel->isDirty() ? "dirty" : "clean")));
  }
  if (panel->isDirty()) {
      return true;
  }
 }
 return false;
}

/*private*/ bool TabbedPreferences::invokeSaveOptions()
{
 bool restartRequired = false;
 foreach (PreferencesPanel* panel, this->preferencesPanels->values())
 {
  if (log->isDebugEnabled())
  {
   log->debug(QString("PreferencesPanel %1 (%2) is %3.").arg(
                    panel->metaObject()->className()).arg(
                    (panel->getTabbedPreferencesTitle() != "") ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
                    (panel->isDirty())? "dirty" : "clean"));
  }
  panel->savePreferences();
  if (log->isDebugEnabled())
  {
   log->debug(QString("PreferencesPanel %1 (%2) restart is %3 required.").arg(
                    panel->metaObject()->className()).arg(
                    (panel->getTabbedPreferencesTitle() != "") ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
                    (panel->isRestartRequired()) ? "" : "not "));
  }
  if (!restartRequired)
  {
   restartRequired = panel->isRestartRequired();
  }
 }
 return restartRequired;
}

/*public*/ void TabbedPreferences::setUIFontSize(float size) {
#if 0
    Enumeration<Object> keys = UIManager.getDefaults().keys();
    Font f;
    while (keys.hasMoreElements()) {
        Object key = keys.nextElement();
        Object value = UIManager.get(key);

        if (value instanceof FontUIResource) {
            f = UIManager.getFont(key).deriveFont(((Font) value).getStyle(), size);
            UIManager.put(key, f);
        }
    }
#endif
}
#if 0
/*public*/ void TabbedPreferences::setUIFont(FontUIResource f) {
    Enumeration<Object> keys = UIManager.getDefaults().keys();
    while (keys.hasMoreElements()) {
        Object key = keys.nextElement();
        Object value = UIManager.get(key);
        if (value instanceof FontUIResource) {
            UIManager.put(key, f);
        }
    }
}
#endif
void TabbedPreferences::selection(QString View)
{
//    CardLayout cl = (CardLayout) (detailpanel.getLayout());
//    cl.show(detailpanel, View);
 for(int i=0; i < detailpanel->count(); i++)
 {
  if(preferencesArray.at(i)->getPrefItem() == View)
  {
   detailpanel->setCurrentIndex(i);
   return;
  }
 }
}

/*public*/ void TabbedPreferences::addPreferencesPanel(PreferencesPanel* panel)
{
 this->preferencesPanels->insert(panel->metaObject()->className(), panel);

 QString preferenceItem = panel->getPreferencesItem();
 QString preferencesItemText = panel->getPreferencesItemText();
 QString tabbedPreferencesTitle = panel->getTabbedPreferencesTitle();
 QString labelKey = panel ->getLabelKey();
 bool bPersistent = panel->isPersistant();
 QString toolTip = panel->getPreferencesTooltip();

 addItem(panel->getPreferencesItem(),
            panel->getPreferencesItemText(),
            panel->getTabbedPreferencesTitle(),
            panel->getLabelKey(),
            panel,
            panel->isPersistant(),
            panel->getPreferencesTooltip()
 );
}

/*private*/ void TabbedPreferences::addItem(QString prefItem, QString itemText, QString tabtitle, QString labelKey, PreferencesPanel* item, bool store, QString tooltip)
{
 PreferencesCatItems* itemBeingAdded = NULL;
 foreach (PreferencesCatItems* preferences, preferencesArray)
 {
  if (preferences->getPrefItem()==(prefItem))
  {
   itemBeingAdded = preferences;
   break;
  }
 }
 if (itemBeingAdded == NULL)
 {
  itemBeingAdded = new PreferencesCatItems(prefItem, itemText);
  preferencesArray.append(itemBeingAdded);
  // As this is a new item in the selection list, we need to update
  // the JList.
  if (initialisationState == INITIALISED)
  {
   updateJList();
  }
 }
 if (tabtitle == NULL)
 {
     tabtitle = itemText;
 }
 itemBeingAdded->addPreferenceItem(tabtitle, labelKey, item->getPreferencesComponent(), tooltip);
}

/* Method allows for the preference to goto a specific list item */
/*public*/ void TabbedPreferences::gotoPreferenceItem(QString _selection, QString subCategory)
{
 selection(_selection);
 //list->setSelectedIndex(getCategoryIndexFromString(_selection));
 list->setCurrentRow(getCategoryIndexFromString(_selection));
 if (subCategory == "" || subCategory==(""))
 {
  return;
 }
 preferencesArray.value(getCategoryIndexFromString(_selection))
            ->gotoSubCategory(subCategory);
}

/*
 * Returns a List of existing Preference Categories.
 */
/*public*/ QStringList TabbedPreferences::getPreferenceMenuList()
{
 QStringList choices =  QStringList();
 foreach (PreferencesCatItems* preferences, preferencesArray)
 {
  choices.append(preferences->getPrefItem());
 }
 return choices;
}

/*
 * Returns a list of Sub Category Items for a give category
 */
/*public*/ QStringList TabbedPreferences::getPreferenceSubCategory(QString category) {
 int index = getCategoryIndexFromString(category);
 return preferencesArray.value(index)->getSubCategoriesList();
}

int TabbedPreferences::getCategoryIndexFromString(QString category)
{
 for (int x = 0; x < preferencesArray.size(); x++)
 {
  if (preferencesArray.at(x)->getPrefItem()==(category))
  {
   return (x);
  }
 }
 return -1;
}

/*public*/ void TabbedPreferences::disablePreferenceItem(QString selection, QString subCategory)
{
 if (subCategory == "" || subCategory==(""))
 {
  // need to do something here like just disable the item

 }
 else
 {
  preferencesArray.at(getCategoryIndexFromString(selection))->disableSubCategory(subCategory);
 }
}

/*protected*/ QStringList TabbedPreferences::getChoices()
{
 QStringList choices = QStringList();
 foreach (PreferencesCatItems* preferences, preferencesArray)
 {
  choices.append(preferences->getItemString());
 }
 return choices;
}

void TabbedPreferences::updateJList()
{
 //buttonpanel.removeAll();
 QObjectList oList = buttonpanel->children();
 foreach(QObject* o, oList)
 {
  if(qobject_cast<QWidget*>(o) != NULL)
  {
   buttonpanel->layout()->removeWidget((QWidget*)o);
   o->deleteLater();
  }
 }
// if (list->getListSelectionListeners().length() > 0)
// {
//  list->removeListSelectionListener(list->getListSelectionListeners()[0]);
// }
 list =  new QListWidget(); //new Vector<String>(getChoices()));
 //list->append(getChoices());
 list->addItems(getChoices());

//    listScroller = new QScrollArea(list);
//    listScroller->resize( QSize(100, 100));
 list->setSelectionMode(/*ListSelectionModel::SINGLE_INTERVAL_SELECTION*/QAbstractItemView::SingleSelection);
// list->setLayoutOrientation(JList.VERTICAL);
//    list.addListSelectionListener((ListSelectionEvent e) -> {
//        PreferencesCatItems item = preferencesArray.get(list.getSelectedIndex());
//        selection(item.getPrefItem());
//    });
 connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(On_list_selection(int)));
 buttonpanel->layout()->addWidget(list);
 buttonpanel->layout()->addWidget(save);
}
void TabbedPreferences::On_list_selection(int row)
{
 if(row < 0)
  return;
 PreferencesCatItems* item = preferencesArray.at(/*list.getSelectedIndex()*/row);
 selection(item->getPrefItem());

}

//static class PreferencesCatItems implements java.io.Serializable {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 5928584215129175250L;
//    /*
//     * This contains details of all list items to be displayed in the
//     * preferences
//     */
//    String itemText;
//    String prefItem;
//    JTabbedPane tabbedPane = new JTabbedPane();
//    ArrayList<String> disableItemsList = new ArrayList<>();

//    ArrayList<TabDetails> TabDetailsArray = new ArrayList<>();

TabbedPreferences::PreferencesCatItems::PreferencesCatItems(QString pref, QString title)
{
 tabbedPane = new QTabWidget();
 tabbedPane->setMinimumSize(400,400);
 tabbedPane->setObjectName("tabbedPane");
 disableItemsList =  QStringList();

 TabDetailsArray =  QList<TabDetails*>();

 prefItem = pref;
 itemText = title;
}

void TabbedPreferences::PreferencesCatItems::addPreferenceItem(QString title, QString labelkey, QWidget* item, QString tooltip)
{
 foreach (TabDetails* tabDetails, TabDetailsArray)
 {
  if (tabDetails->getTitle()==(title))
  {
   // If we have a match then we do not need to add it back in.
   return;
  }
 }
 TabDetails* tab = new TabDetails(labelkey, title, item, tooltip);
 TabDetailsArray.append(tab);
 //tabbedPane.addTab(tab.getTitle(), null, tab.getPanel(),
//                tab->getToolTip());
 int tabIndex = tabbedPane->addTab(tab->getItem(), tab->getTitle());
 tabbedPane->setTabToolTip(tabIndex,tab->getToolTip());
 tabbedPane->setTabEnabled(tabIndex, true);

 foreach (QString disableItem,disableItemsList)
 {
  if (item->metaObject()->className()==(disableItem))
  {
   for(int i = 0; i < tabbedPane->count(); i++)
   {
    if(tabbedPane->tabText(i) == tab->getTitle())
    {
     tabbedPane->setCurrentIndex(i);
     break;
    }
   }
   //tabbedPane->setEnabledAt(tabbedPane->indexOfTab(tab->getTitle()), false);
   tabbedPane->setTabEnabled(tabIndex, false);
   return;
  }
 }
}

QString TabbedPreferences::PreferencesCatItems::getPrefItem() {
    return prefItem;
}

QString TabbedPreferences::PreferencesCatItems::getItemString() {
    return itemText;
}

QStringList TabbedPreferences::PreferencesCatItems::getSubCategoriesList()
{
 QStringList choices =  QStringList();
 foreach (TabDetails* tabDetails, TabDetailsArray)
 {
  choices.append(tabDetails->getTitle());
 }
 return choices;
}

/*
 * This returns a JPanel if only one item is configured for a menu item
 * or it returns a JTabbedFrame if there are multiple items for the menu
 */
QWidget* TabbedPreferences::PreferencesCatItems::getPanel()
{
 if(TabDetailsArray.isEmpty()) return new QWidget();
 if (TabDetailsArray.size() == 1)
 {
  return TabDetailsArray.at(0)->getItem();
 }
 else
 {
  return tabbedPane;
 }
}

void TabbedPreferences::PreferencesCatItems::gotoSubCategory(QString sub)
{
 if (TabDetailsArray.size() == 1)
 {
  return;
 }
 for (int i = 0; i < TabDetailsArray.size(); i++)
 {
  if (TabDetailsArray.at(i)->getTitle()==(sub))
  {
   tabbedPane->setCurrentIndex(i);
   return;
  }
 }
}

void TabbedPreferences::PreferencesCatItems::disableSubCategory(QString sub)
{
 if (TabDetailsArray.isEmpty())
 {
  // So the tab preferences might not have been initialised when
  // the call to disable an item is called therefore store it for
  // later on
  disableItemsList.append(sub);
  return;
 }
 for (int i = 0; i < TabDetailsArray.size(); i++)
 {
  if ((TabDetailsArray.at(i)->getItem())->metaObject()->className() == (sub))
  {
   tabbedPane->setTabEnabled(i, false);
   return;
  }
 }
}

//    static class TabDetails implements java.io.Serializable {

//        /**
//         *
//         */
//        private static final long serialVersionUID = -7077354592762639878L;
//        /* This contains all the JPanels that make up a preferences menus */
//        JComponent tabItem;
//        String tabTooltip;
//        String tabTitle;
//        JPanel tabPanel = new JPanel();
//        //bool store;

TabbedPreferences::PreferencesCatItems::TabDetails::TabDetails(QString labelkey, QString tabTit, QWidget* item,
        QString tooltip)
{
 tabPanel = new QWidget();
 //tabPanel->setMinimumSize(400, 300);
 tabItem = item;
 tabTitle = tabTit;
 tabTooltip = tooltip;

 QWidget* p = new QWidget();
 QVBoxLayout* pLayout= new QVBoxLayout;
 //p->setLayout(pLayout = new QVBoxLayout); //BorderLayout());
 if (labelkey != "")
 {
  // insert label at top
  // As this can be multi-line, embed the text within <html>
  // tags and replace newlines with <br> tag
  QLabel* t = new QLabel("<html>"
                + labelkey.replace(('\n'), "<br>")
                + "</html>");
        //t.setHorizontalAlignment(JLabel.CENTER);
  t->setWordWrap(true);
  t->setAlignment(Qt::AlignCenter);
//                t.setAlignmentX(0.5f);
//                t.setPreferredSize(t->getMinimumSize());
//                t.setMaximumSize(t.getMinimumSize());
//                t.setOpaque(false);
  pLayout->addWidget(t, 0, Qt::AlignTop /*BorderLayout.NORTH*/);
 }
 pLayout->addWidget(item, 0, Qt::AlignCenter /*BorderLayout.CENTER*/);
 item->setMinimumSize(400,300);
 QVBoxLayout* tabPanelLayout;
 tabPanel->setLayout(tabPanelLayout = new QVBoxLayout); //BorderLayout());
 tabPanelLayout->addWidget(p); //,0, Qt::AlignCenter /*BorderLayout.CENTER*/);
}

QString TabbedPreferences::PreferencesCatItems::TabDetails::getToolTip() {
    return tabTooltip;
}

QString TabbedPreferences::PreferencesCatItems::TabDetails::getTitle() {
    return tabTitle;
}

QWidget* TabbedPreferences::PreferencesCatItems::TabDetails::getPanel() {
    return tabPanel;
}

QWidget* TabbedPreferences::PreferencesCatItems::TabDetails::getItem() {
    return tabItem;
}

//static class PreferencesCatItems implements java.io.Serializable {

//        /**
//         *
//         */
//        private static final long serialVersionUID = 5928584215129175250L;
//        /*
//         * This contains details of all list managedPreferences to be displayed in the
//         * preferences
//         */
//        String itemText;
//        String prefItem;
//        JTabbedPane tabbedPane = new JTabbedPane();
//        ArrayList<String> disableItemsList = new ArrayList<>();

//        ArrayList<TabDetails> TabDetailsArray = new ArrayList<>();

        PreferencesCatItems::PreferencesCatItems(QString pref, QString title, TabbedPreferences *tabbedPreferences)
        {
            prefItem = pref;
            itemText = title;
            this->tabbedPreferences = tabbedPreferences;
        }

        void PreferencesCatItems::addPreferenceItem(QString title, QString labelkey, QWidget* item,
                QString tooltip)
        {
            foreach (TabDetails* tabDetails, TabDetailsArray)
            {
                if (tabDetails->getTitle()==(title))
                {
                    // If we have a match then we do not need to add it back in.
                    return;
                }
            }
            TabDetails* tab = new TabDetails(labelkey, title, item, tooltip);
            TabDetailsArray.append(tab);
            QScrollArea* scroller = new QScrollArea(tab->getPanel());
            //scroller.setBorder(BorderFactory.createEmptyBorder());
            //tabbedPane.addTab(tab.getTitle(), null, scroller, tab.getToolTip());
            int iTab = tabbedPane->addTab(scroller, tab->getTitle());
            tabbedPane->setTabToolTip(iTab, tab->getToolTip());

            foreach (QString disableItem, disableItemsList)
            {
                if (QString(item->metaObject()->className()) == disableItem)
                {
                    //tabbedPane->setEnabledAt(tabbedPane->indexOfTab(tab->getPanel()), false);
                 tabbedPane->setTabEnabled(tabbedPane->indexOf(tab->getPanel()),false);
                    return;
                }
            }
        }

        QString PreferencesCatItems::getPrefItem() {
            return prefItem;
        }

        QString PreferencesCatItems::getItemString() {
            return itemText;
        }

        QList<QString> PreferencesCatItems::getSubCategoriesList() {
         QList<QString> choices =  QList<QString>();
            foreach (TabDetails* tabDetails, TabDetailsArray) {
                choices.append(tabDetails->getTitle());
            }
            return choices;
        }

        /*
         * This returns a JPanel if only one item is configured for a menu item
         * or it returns a JTabbedFrame if there are multiple managedPreferences for the menu
         */
        QWidget* PreferencesCatItems::getPanel() {
            if (TabDetailsArray.size() == 1) {
                return TabDetailsArray.at(0)->getPanel();
            } else {
                return tabbedPane;
            }
        }

        void PreferencesCatItems::gotoSubCategory(QString sub) {
            if (TabDetailsArray.size() == 1) {
                return;
            }
            for (int i = 0; i < TabDetailsArray.size(); i++) {
                if (TabDetailsArray.at(i)->getTitle()==(sub)) {
                    tabbedPane->setCurrentIndex(i);
                    return;
                }
            }
        }

        void PreferencesCatItems::disableSubCategory(QString sub) {
            if (TabDetailsArray.isEmpty()) {
                // So the tab preferences might not have been initialised when
                // the call to disable an item is called therefore store it for
                // later on
                disableItemsList.append(sub);
                return;
            }
            for (int i = 0; i < TabDetailsArray.size(); i++) {
                if ((TabDetailsArray.at(i)->getItem())->metaObject()->className()
                        == (sub)) {
                    tabbedPane->setTabEnabled(i, false);
                    return;
                }
            }
        }

//        static class TabDetails implements java.io.Serializable {

//            /**
//             *
//             */
//            private static final long serialVersionUID = -7077354592762639878L;
//            /* This contains all the JPanels that make up a preferences menus */
//            JComponent tabItem;
//            String tabTooltip;
//            String tabTitle;
//            JPanel tabPanel = new JPanel();
//            //boolean store;

            TabDetails::TabDetails(QString labelkey, QString tabTit, QWidget* item,
                    QString tooltip)
            {
                tabItem = item;
                tabTitle = tabTit;
                tabTooltip = tooltip;
                tabPanel = new QWidget;

                QWidget* p = new QWidget();
                //p.setLayout(new BorderLayout());
                QVBoxLayout* pLayout = new QVBoxLayout(p);
                if (labelkey != NULL)
                {
                    // insert label at top
                    // As this can be multi-line, embed the text within <html>
                    // tags and replace newlines with <br> tag
                    QLabel* t = new QLabel("<html>"
                            + labelkey.replace(('\n'), "<br>")
                            + "</html>");
                    //t.setHorizontalAlignment(JLabel.CENTER);
                    t->setAlignment(Qt::AlignHCenter);
                    //t.setAlignmentX(0.5f);
                    t->resize(t->sizeHint());
                    t->setMaximumSize(t->sizeHint());
//                    t->setOpaque(false);
                    pLayout->addWidget(t, /*BorderLayout.NORTH*/0,Qt::AlignTop);
                }
                pLayout->addWidget(item, /*BorderLayout.CENTER*/0, Qt::AlignVCenter);
                //tabPanel.setLayout(new BorderLayout());
                QVBoxLayout* tabPanelLayout = new QVBoxLayout(tabPanel);
                tabPanelLayout->addWidget(p, /*BorderLayout.CENTER*/0, Qt::AlignVCenter);
            }

            QString TabDetails::getToolTip() {
                return tabTooltip;
            }

            QString TabDetails::getTitle() {
                return tabTitle;
            }

            QWidget* TabDetails::getPanel() {
                return tabPanel;
            }

            QWidget* TabDetails::getItem() {
                return tabItem;
            }

//        }
//    }
/*private*/ /*final*/ /*static*/ Logger* TabbedPreferences::log = LoggerFactory::getLogger("TabbedPreferences");
