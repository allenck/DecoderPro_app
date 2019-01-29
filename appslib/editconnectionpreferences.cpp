#include "editconnectionpreferences.h"
#include "loggerfactory.h"
#include "editconnectionpreferencesdialog.h"
#include <QScrollArea>
#include <QBoxLayout>
#include "jlist.h"
#include <QPushButton>
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include <QLabel>
#include "flowlayout.h"
#include "jseparator.h"
#include "fileutil.h"
#include "preferencespanel.h"
#include <QFormLayout>
#include "joptionpane.h"
#include "imageicon.h"
#include "tabbedpreferences.h"
#include <QStackedWidget>

/**
 * Provide access to preferences via a tabbed pane.
 *
 * Preferences panels provided by a {@link java.util.ServiceLoader} will be
 * automatically loaded if they implement the
 * {@link jmri.swing.PreferencesPanel} interface.
 * <p>
 * State is maintained as a bound property with name INITIALIZATION (see value
 * below)
 * <p>
 * JMRI apps (generally) create one object of this type on the main thread as
 * part of initialization, then create a separate "initialize preferences"
 * thread to handle the init() call and adding all the tabs. Finally, the result
 * is displayed on the Swing thread.
 *
 * @author Bob Jacobsen Copyright 2010
 * @author Randall Wood 2012, 2016
 */
//public class EditConnectionPreferences extends AppConfigBase {

//@Override
/*public*/ QString EditConnectionPreferences::getHelpTarget() {
    return "package.apps.TabbedPreferences";
}

//@Override
/*public*/ QString EditConnectionPreferences::getTitle() {
    return tr("Preferences");
}
// Preferences Window Title

//@Override
/*public*/ bool EditConnectionPreferences::isMultipleInstances() {
    return false;
} // only one of these!


//QWidget* detailpanel = new QWidget();
//{
//    // The default panel needs to have a CardLayout (Qt QFormLayout!)
//    detailpanel.setLayout(new CardLayout());
//}



/*public*/ EditConnectionPreferences::EditConnectionPreferences(EditConnectionPreferencesDialog* dialog, QWidget *parent) : AppConfigBase(parent)
{
 detailpanel = new QWidget();
 preferencesArray = QList<PreferencesCatItems*>();
    this->dialog = dialog;

    /*
     * Adds the place holders for the menu managedPreferences so that any managedPreferences add by
     * third party code is added to the end
     */
    preferencesArray.append(new PreferencesCatItems(QString("CONNECTIONS"), tr("Connections"), 100, nullptr));
}

/*public*/ void EditConnectionPreferences::init() {
    list = new JList();
//    listScroller = new JScrollPane(list);
//    listScroller.setPreferredSize(new Dimension(100, 100));

    buttonpanel = new QWidget();
    //buttonpanel.setLayout(new BoxLayout(buttonpanel, BoxLayout.Y_AXIS));
    buttonPanelLayout = new QHBoxLayout(buttonpanel);
    //buttonpanel.setBorder(BorderFactory.createEmptyBorder(6, 6, 6, 3));

    detailpanel = new JPanel();
    //detailpanel.setLayout(new CardLayout());
    QFormLayout* detailpanelLayout = new QFormLayout(detailpanel);
    //detailpanel.setBorder(BorderFactory.createEmptyBorder(6, 3, 6, 6));

    save = new QPushButton(
            QIcon(FileUtil::findURL("program:resources/icons/misc/gui3/SaveIcon.png").toLocalFile()), tr("Save"));
#if 0
    save.addActionListener((ActionEvent e) -> {
        dialog.restartProgram = true;
        savePressed(invokeSaveOptions());
    });
#endif
    quit = new QPushButton(
            tr("Quit"));
//                new ImageIcon(FileUtil.findURL("program:resources/icons/misc/gui3/SaveIcon.png", FileUtil.Location.INSTALLED)));
#if 0
    quit.addActionListener((ActionEvent e) -> {
        if (dialog != null) {
            dialog.restartProgram = false;
            dialog.dispose();
        }
    });
#endif
    QHBoxLayout* thisLayout;
    setLayout(thisLayout = new QHBoxLayout(this)); //this, BoxLayout.X_AXIS));
    //getTabbedPreferences()->preferencesArray.stream().forEach((preferences) -> {

    foreach (PreferencesCatItems* preferences , getTabbedPreferences()->preferencesArray)
    {
        //detailpanel.add(preferences.getPanel(), preferences->getPrefItem());
     detailpanelLayout->addRow(preferences->getPrefItem(), preferences->getPanel());
    }//);

    QWidget* panel = new QWidget();
    FlowLayout* panelLayout = new FlowLayout(panel);
    panelLayout->addWidget(new QPushButton("Test"));
    detailpanelLayout->addRow( "DANIEL", panel);

    updateJList();
    thisLayout->addWidget(buttonpanel);
    thisLayout->addWidget(new JSeparator(JSeparator::VERTICAL));
    thisLayout->addWidget(detailpanel);

    list->setCurrentIndex(list->model()->index(0,0));
    selection(preferencesArray.at(0)->getPrefItem());
}

// package only - for EditConnectionPreferencesDialog
bool EditConnectionPreferences::isDirty() {
    // if not for the debug statements, this method could be the one line:
    // return this.getPreferencesPanels().values.stream().anyMatch((panel) -> (panel.isDirty()));
    //return this.getPreferencesPanels().values().stream().map((panel) ->
    QMap<QString, PreferencesPanel*>* map = this->getPreferencesPanels();
    foreach(PreferencesPanel* panel, map->values())
    {
     if(panel->isDirty())

        // wrapped in isDebugEnabled test to prevent overhead of assembling message
        if (log->isDebugEnabled()) {
//            log->debug(tr("PreferencesPanel %1 (%2) is %3.").arg(
//                    QString(panel->objectName())).arg(
//                    (panel->getTabbedPreferencesTitle() != nullptr) ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
//                    (panel->isDirty()) ? "dirty" : "clean"));
        }
//     }
//     return panel;
    }//).anyMatch((panel) -> (panel.isDirty()));
}

// package only - for EditConnectionPreferencesDialog
bool EditConnectionPreferences::invokeSaveOptions() {
    bool restartRequired = false;
    for (PreferencesPanel* panel : this->getPreferencesPanels()->values()) {
        // wrapped in isDebugEnabled test to prevent overhead of assembling message
        if (log->isDebugEnabled()) {
//            log->debug(tr("PreferencesPanel %1 (%2) is %3.").arg(
//                    QString(panel->metaObject()->className()).arg(
//                    (panel->getTabbedPreferencesTitle() != nullptr) ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
//                    (panel->isDirty()) ? "dirty" : "clean")));
        }
        panel->savePreferences();
        // wrapped in isDebugEnabled test to prevent overhead of assembling message
        if (log->isDebugEnabled()) {
//            log->debug(tr("PreferencesPanel %1 (%2) restart is %3 required.").arg(
//                    QString(panel->metaObject()->className()).arg(
//                    (panel->getTabbedPreferencesTitle() != nullptr) ? panel->getTabbedPreferencesTitle() : panel->getPreferencesItemText()).arg(
//                    (panel->isRestartRequired()) ? "" : "not ")));
        }
        if (!restartRequired) {
            restartRequired = panel->isRestartRequired();
        }
    }
    return restartRequired;
}

void EditConnectionPreferences::selection(QString view) {
    QFormLayout* cl = (QFormLayout*) (detailpanel->layout());
//??    cl.show(detailpanel, view);
}

/*public*/ void EditConnectionPreferences::addPreferencesPanel(PreferencesPanel* panel) {
    this->getPreferencesPanels()->insert(QString(panel->className()), panel);
    addItem(panel->getPreferencesItem(),
            panel->getPreferencesItemText(),
            panel->getTabbedPreferencesTitle(),
            panel->getLabelKey(),
            panel,
            panel->getPreferencesTooltip(),
            panel->getSortOrder()
    );
}

/*private*/ void EditConnectionPreferences::addItem(QString prefItem, QString itemText, QString tabTitle,
        QString labelKey, PreferencesPanel* item, QString tooltip, int sortOrder) {
    PreferencesCatItems* itemBeingAdded = nullptr;
    for (PreferencesCatItems* preferences : preferencesArray) {
        if (preferences->getPrefItem() == (prefItem)) {
            itemBeingAdded = preferences;
            // the lowest sort order of any panel sets the sort order for
            // the preferences category
            if (sortOrder < preferences->sortOrder) {
                preferences->sortOrder = sortOrder;
            }
            break;
        }
    }
    if (itemBeingAdded == nullptr) {
        itemBeingAdded = new PreferencesCatItems(prefItem, itemText, sortOrder, nullptr);
        preferencesArray.append(itemBeingAdded);
        // As this is a new item in the selection list, we need to update
        // the JList.
        updateJList();
    }
    if (tabTitle == nullptr) {
        tabTitle = itemText;
    }
    itemBeingAdded->addPreferenceItem(tabTitle, labelKey, item->getPreferencesComponent(), tooltip, sortOrder);
}

/* Method allows for the preference to goto a specific list item */
/*public*/ void EditConnectionPreferences::gotoPreferenceItem(QString _selection, QString subCategory) {

    selection(_selection);
#if 0
    list->setCurrentIndex(getCategoryIndexFromString(_selection));
#endif
    if (subCategory == nullptr || subCategory.isEmpty()) {
        return;
    }
    preferencesArray.value(getCategoryIndexFromString(_selection))
            ->gotoSubCategory(subCategory);
}

/*
 * Returns a List of existing Preference Categories.
 */
/*public*/ QStringList EditConnectionPreferences::getPreferenceMenuList() {
    QStringList choices = QStringList();
    for (PreferencesCatItems* preferences : preferencesArray) {
        choices.append(preferences->getPrefItem());
    }
    return choices;
}

int EditConnectionPreferences::getCategoryIndexFromString(QString category) {
    for (int x = 0; x < preferencesArray.size(); x++) {
        if (preferencesArray.at(x)->getPrefItem() == (category)) {
            return (x);
        }
    }
    return -1;
}

/*protected*/ QStringList EditConnectionPreferences::getChoices() {
    QStringList choices = QStringList();
    for (PreferencesCatItems* preferences : preferencesArray) {
        choices.append(preferences->getItemString());
    }
    return choices;
}

void EditConnectionPreferences::updateJList() {
    //buttonpanel.removeAll();
    while ( QWidget* w = buttonpanel->findChild<QWidget*>() )
        delete w;
#if 0
    if (list->getListSelectionListeners().length > 0) {
        list->removeListSelectionListener(list->getListSelectionListeners()[0]);
    }
#endif
    QStringList choices = this->getChoices();
    list = new JList(choices);
//    listScroller = new JScrollPane(list);
//    listScroller.setPreferredSize(new Dimension(100, 100));
#if 0
    list->setSelectionMode(ListSelectionModel::SINGLE_INTERVAL_SELECTION);
    list->setLayoutOrientation(JList::VERTICAL);
    list->addListSelectionListener((ListSelectionEvent e) -> {
        PreferencesCatItems item = preferencesArray.get(list.getSelectedIndex());
        selection(item.getPrefItem());
    });
#endif
    buttonPanelLayout->addWidget(list);
    buttonPanelLayout->addWidget(save);

    if (quit != nullptr) {
        buttonPanelLayout->addWidget(quit);
    }
}

/*public*/ bool EditConnectionPreferences::isPreferencesValid() {
    //return this->getPreferencesPanels().values().stream().allMatch((panel) -> (panel.isPreferencesValid()));
 foreach(PreferencesPanel* panel, getPreferencesPanels()->values())
 {
  if(!panel->isPreferencesValid()) return false;
 }
 return true;
}

//@Override
/*public*/ void EditConnectionPreferences::savePressed(bool restartRequired) {
    ShutDownManager* sdm = static_cast<ShutDownManager*>(InstanceManager::getNullableDefault("ShutDownManager"));
    if (!this->isPreferencesValid() && (sdm == nullptr || !sdm->isShuttingDown())) {
        for (PreferencesPanel* panel : this->getPreferencesPanels()->values()) {
            if (!panel->isPreferencesValid()) {
                switch (JOptionPane::showConfirmDialog(this,
                        tr("<html><b>The %1 preferences are invalid.</b><br>Do you want to correct them?</html>").arg(panel->getTabbedPreferencesTitle()),
                        tr("Invalid Preferences"),
                        JOptionPane::YES_NO_OPTION,
                        JOptionPane::ERROR_MESSAGE)) {
                    case JOptionPane::YES_OPTION:
                        // abort save and return to broken preferences
                        this->gotoPreferenceItem(panel->getPreferencesItem(), panel->getTabbedPreferencesTitle());
                        return;
                    default:
                        // do nothing
                        break;
                }
            }
        }
    }
    AppConfigBase::savePressed(restartRequired);
}
#if 0 // see TabbedPreferences
//static class PreferencesCatItems implements java.io.Serializable {

//    /*
//     * This contains details of all list managedPreferences to be displayed in the
//     * preferences
//     */
//    String itemText;
//    String prefItem;
//    int sortOrder = Integer.MAX_VALUE;
//    JTabbedPane tabbedPane = new JTabbedPane();
//    ArrayList<String> disableItemsList = new ArrayList<>();

//    private final ArrayList<TabDetails> tabDetailsArray = new ArrayList<>();

    PreferencesCatItems::PreferencesCatItems(QString pref, QString title, int sortOrder) {
     tabbedPane = new QTabWidget();
     disableItemsList = QStringList();

        prefItem = pref;
        itemText = title;
        this->sortOrder = sortOrder;
    }

    void PreferencesCatItems::addPreferenceItem(QString title, QString labelkey, QWidget* item,
            QString tooltip, int sortOrder) {
        for (TabDetails* tabDetails : tabDetailsArray) {
            if (tabDetails->getTitle() == (title)) {
                // If we have a match then we do not need to add it back in.
                return;
            }
        }
        TabDetails* tab = new TabDetails(labelkey, title, item, tooltip, sortOrder);
        tabDetailsArray.append(tab);
//        tabDetailsArray.sort((TabDetails o1, TabDetails o2) -> {
//            int comparison = Integer.compare(o1.sortOrder, o2.sortOrder);
//            return (comparison != 0) ? comparison : o1.tabTitle.compareTo(o2.tabTitle);
//        });
        qSort(tabDetailsArray.begin(), tabDetailsArray.end());
#if 0
        QScrollArea* scroller = new JScrollPane(tab.getPanel());
        scroller.setBorder(BorderFactory.createEmptyBorder());
        ThreadingUtil.runOnGUI(() -> {

            tabbedPane.addTab(tab.getTitle(), null, scroller, tab.getToolTip());

            for (QString disableItem : disableItemsList) {
                if (item.getClass().getName().equals(disableItem)) {
                    tabbedPane.setEnabledAt(tabbedPane.indexOfTab(tab.getTitle()), false);
                    return;
                }
            }
        });
#endif
    }

    QString PreferencesCatItems::getPrefItem() {
        return prefItem;
    }

    QString PreferencesCatItems::getItemString() {
        return itemText;
    }

    /*
     * This returns a JPanel if only one item is configured for a menu item
     * or it returns a JTabbedFrame if there are multiple managedPreferences for the menu
     */
    QWidget* PreferencesCatItems::getPanel() {
        if (tabDetailsArray.size() == 1) {
            return tabDetailsArray.at(0)->getPanel();
        } else {
            if (tabbedPane->count() == 0) {
                for (TabDetails* tab : tabDetailsArray) {
#if 0
                    ThreadingUtil.runOnGUI(() -> {
                        JScrollPane scroller = new JScrollPane(tab.getPanel());
                        scroller.setBorder(BorderFactory.createEmptyBorder());

                        tabbedPane.addTab(tab.getTitle(), null, scroller, tab.getToolTip());

                        for (String disableItem : disableItemsList) {
                            if (tab.getItem().getClass().getName().equals(disableItem)) {
                                tabbedPane.setEnabledAt(tabbedPane.indexOfTab(tab.getTitle()), false);
                                return;
                            }
                        }
                    });
#endif
                }
            }
            return tabbedPane;
        }
    }

    void PreferencesCatItems::gotoSubCategory(QString sub) {
        if (tabDetailsArray.size() == 1) {
            return;
        }
        for (int i = 0; i < tabDetailsArray.size(); i++) {
            if (tabDetailsArray.at(i)->getTitle() == (sub)) {
                tabbedPane->setCurrentIndex(i);
                return;
            }
        }
    }

//    static class TabDetails implements java.io.Serializable {

//        /* This contains all the JPanels that make up a preferences menus */
//        JComponent tabItem;
//        String tabTooltip;
//        String tabTitle;
//        JPanel tabPanel = new JPanel();
//        private final int sortOrder;

        TabDetails::TabDetails(QString labelkey, QString tabTit, QWidget* item,
                QString tooltip, int sortOrder) {
         tabPanel = new QWidget();
            tabItem = item;
            tabTitle = tabTit;
            tabTooltip = tooltip;
            this->sortOrder = sortOrder;

            QWidget* p = new QWidget();
            //p.setLayout(new BorderLayout());
            QHBoxLayout* pLayout = new QHBoxLayout(p);
            if (labelkey != nullptr) {
                // insert label at top
                // As this can be multi-line, embed the text within <html>
                // tags and replace newlines with <br> tag
                QLabel* t = new QLabel("<html>"
                        + labelkey.replace("\n", "<br>")
                        + "</html>");
//                t.setHorizontalAlignment(JLabel.CENTER);
//                t.setAlignmentX(0.5f);
//                t.setPreferredSize(t.getMinimumSize());
//                t.setMaximumSize(t.getMinimumSize());
//                t.setOpaque(false);
                pLayout->addWidget(t, /*BorderLayout.NORTH*/ 0, Qt::AlignTop);
            }
            pLayout->addWidget(item, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
#if 0
            ThreadingUtil.runOnGUI(() -> {
                tabPanel.setLayout(new BorderLayout());
                tabPanel.add(p, BorderLayout.CENTER);
            });
#endif
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

        int TabDetails::getSortOrder() {
            return sortOrder;
        }
//    }
//}
#endif
/**
 * Ensure a TabbedPreferences instance is always available.
 *
 * @return the default TabbedPreferences instance, creating it if needed
 */
/*private*/ TabbedPreferences* EditConnectionPreferences::getTabbedPreferences() {
//    return InstanceManager::getOptionalDefault(TabbedPreferences.class).orElseGet(() -> {
//        return InstanceManager.setDefault(TabbedPreferences.class, new TabbedPreferences());
//    });
    TabbedPreferences* tabbedPreferences = static_cast<TabbedPreferences*>(InstanceManager::getDefault("TabbedPreferences"));
    if(tabbedPreferences != nullptr)
     return tabbedPreferences;
    else
     return (TabbedPreferences*)InstanceManager::setDefault("TabbedPreferences", (QObject*)new TabbedPreferences());
}

/*private*/ /*final*/ /*static*/ Logger* EditConnectionPreferences::log = LoggerFactory::getLogger("EditConnectionPreferences");

