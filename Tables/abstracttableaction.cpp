#include "abstracttableaction.h"
#include "instancemanager.h"
#include "jmriuserpreferencesmanager.h"
#include "abstracttabletabaction.h"
#include <QSortFilterProxyModel>
#include "jtable.h"
#include <qheaderview.h>
#include <QPushButton>
#include "beantabledatamodel.h"
#include "mysortfilterproxymodel.h"
#include <QRegExp>
#include "systemconnectionmemomanager.h"
#include "loggerfactory.h"
#include "managercombobox.h"
#include "actionlistener.h"
#include "proxyturnoutmanager.h"
#include "proxylightmanager.h"

AbstractTableAction::AbstractTableAction(QObject *parent) :
    AbstractAction(parent)
{
}
/**
 * Swing action to create and register a
 * SignalHeadTable GUI
 *
 * @author	Bob Jacobsen    Copyright (C) 2003
 * @version     $Revision: 28013 $
 */

// /*abstract*/ /*public*/ class AbstractTableAction extends AbstractAction {

    /**
     *
     */
// /*private*/ static final long serialVersionUID = -7910901479004827844L;

/*public*/ AbstractTableAction::AbstractTableAction(QString actionName,QObject *parent) :
    AbstractAction(actionName, parent)
{
 //super(actionName);
}

///*public*/ AbstractTableAction(QString actionName, QObject option, QObject *parent) :
//    QObject(parent)
//{
// super(actionName);
//}


///*public*/ static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");
///*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");

/**
 * Create the JTable DataModel, along with the changes
 * for the specific NamedBean type
 */

// /*protected*/ /*abstract*/ void AbstractTableAction::createModel() {}

/**
 * Include the correct title
 */

/*protected*/ /*abstract*/ void AbstractTableAction::setTitle() {}


/*public*/ void AbstractTableAction::actionPerformed(JActionEvent * /*e*/)
{
 // create the JTable model, with changes for specific NamedBean
 createModel();
// if(m != NULL)
// {
 //TableSorter sorter = new TableSorter(m);
 MySortFilterProxyModel* sorter = new MySortFilterProxyModel(m);
 //sorter->setSourceModel((QAbstractItemModel*)m);
 JTable *dataTable = m->makeJTable(m->getMasterClassName(), m, sorter);
 dataTable->setSortingEnabled(true);
 //sorter.setTableHeader(dataTable.getTableHeader());

 // allow reordering of the columns
 //dataTable.getTableHeader().setReorderingAllowed(true);

 // create the frame
//    f = new BeanTableFrame(m, helpTarget(), dataTable){
//    /**
//     *
//     */
//    private static final long serialVersionUID = 1123302534258100353L;

//    /**
//     * Include an "add" button
//     */
//    void extras() {
//        if(includeAddButton){
//            JButton addButton = new JButton(this.tr("ButtonAdd"));
//            addToBottomBox(addButton, this.getClass().getName());
//            addButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    addPressed(e);
//                }
//            });
//        }
//        }
//    };
  f = new ATABeanTableFrame(m, helpTarget(), dataTable, this);
// }
// else
// {
//  f= new ATABeanTableFrame(this);
// }
 //buildMenus(f);
 setMenuBar(f); // comes after the Help menu is added by f = new
                // BeanTableFrame(etc.) in stand alone application
 configureTable(dataTable);
 setTitle();
 addToFrame(f);
 f->adjustSize();
 f->setVisible(true);
}

/**
 * Notification that column visibility for the JTable has updated.
 * <p>
 * This is overridden by classes which have column visibility Checkboxes on bottom bar.
 * <p>
 *
 * Called on table startup and whenever a column goes hidden / visible.
 *
 * @param colsVisible   array of ALL table columns and their visibility
 *                      status in order of main Table Model, NOT XTableColumnModel.
 */
/*protected*/ void AbstractTableAction::columnsVisibleUpdated(QVector<bool> colsVisible){
    log->debug(tr("columns updated %1").arg(colsVisible.count()));
}

ATABeanTableFrame::ATABeanTableFrame(AbstractTableAction *act)
{
 this->act = act;
}

ATABeanTableFrame::ATABeanTableFrame(BeanTableDataModel *m, QString helpTarget, JTable *table, AbstractTableAction *act) : BeanTableFrame(m, helpTarget,table)
{
 this->act = act;
}

void ATABeanTableFrame::extras()
{
 if(act->includeAddButton())
 {
  QPushButton* addButton = new QPushButton(tr("Add"));
  addToBottomBox(addButton, "this.getClass().getName()");
//  addButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
  connect(addButton, &QPushButton::clicked, [=]{
        act->addPressed(/*e*/);
//    }
  });
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
  addButton->setSizePolicy(sizePolicy);
 }
}
/*public*/ QString ATABeanTableFrame::getClassName()
{
 return "jmri.jmrit.beantable.BeanTableFrame";
}


/*public*/ BeanTableDataModel* AbstractTableAction::getTableDataModel()
{
 createModel();
 return m;
}

/*public*/ void AbstractTableAction::setFrame(BeanTableFrame* frame){
    f=frame;
}

/**
 * Allow subclasses to add to the frame
 * without have to actually subclass the BeanTableDataFrame
 */
/*public*/ void AbstractTableAction::addToFrame(BeanTableFrame* /*f*/) {
}

/**
 * If the subClass is being included in a greater tabbed frame, then this
 * method is used to add the details to the tabbed frame
 */
 /*public*/ void AbstractTableAction::addToPanel(AbstractTableTabAction* f) { }

/**
 * If the subClass is being included in a greater tabbed frame, then this
 * is used to specify which manager the subclass should be using.
 */
/*protected*/ void AbstractTableAction::setManager(Manager* /*man*/) { }
/**
 * Get the Bean Manager in use by the TableAction.
 * @return Bean Manager, could be Proxy or normal Manager, may be null.
 */
//@CheckForNull
/*protected*/ Manager/*<E>*/* AbstractTableAction::getManager(){
    return nullptr;
}
/**
 * Allow subclasses to add alter the frames Menubar
 * without have to actually subclass the BeanTableDataFrame
 */
/*public*/ void AbstractTableAction::setMenuBar(BeanTableFrame* /*f*/){
}

/*public*/ QWidget* AbstractTableAction::getPanel(){
    return NULL;
}

/**
 * Perform configuration of the JTable as required by a specific TableAction.
 * @param table The table to configure.
 */
/*protected*/ void AbstractTableAction::configureTable(JTable* /*table*/){
}

/*public*/ void AbstractTableAction::dispose() {
    if (m!=NULL){
        m->dispose();
    }
}

/**
 * Increments trailing digits of a system/user name (string) I.E. "Geo7"
 * returns "Geo8" Note: preserves leading zeros: "Geo007" returns "Geo008"
 * Also, if no trailing digits, appends "1": "Geo" returns "Geo1"
 *
 * @param name the system or user name string
 * @return the same name with trailing digits incremented by one
 */
/*protected*/ /*@Nonnull*/ QString AbstractTableAction::nextName(/*@Nonnull*/ QString name) {
    QStringList parts = name.split(QRegExp("(?=\\d+$)")/*, 2*/);
    QString numString = "0";
    if (parts.length() == 2) {
        numString = parts[1];
    }
    /*final*/ int numStringLength = numString.length();
    /*final*/ int num = numString.toInt() + 1;
    //return parts[0] + String.format("%0" + numStringLength + "d", num);
    return parts.at(0) + QStringLiteral("%1").arg(num, numStringLength, 10, QLatin1Char('0'));
}

/**
 * Specify the JavaHelp target for this specific panel
 */
/*protected*/ QString AbstractTableAction::helpTarget() {
    return "index";  // by default, go to the top
}

/*public*/ QString AbstractTableAction::getClassDescription() { return "Abstract Table Action"; }

/*public*/ void AbstractTableAction::setMessagePreferencesDetails()
{
 QMap< int,QString>* options =  new QMap< int,QString>();
 options->insert(0x00, tr("Always Ask"));
 options->insert(0x01, tr("Never Delete"));
 options->insert(0x02, tr("Delete Without Prompting"));
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setMessageItemDetails(getClassName(), "deleteInUse", tr("When Deleting an iten that is in use"), options, 0x00);

}

/*protected*/ /*abstract*/ QString AbstractTableAction::getClassName() {return "";}

/*public*/ bool AbstractTableAction::includeAddButton()
{ return _includeAddButton; }


/**
* Used with the Tabbed instances of table action, so that the print option
* is handled via that on the appropriate tab.
*/
/*public*/ void AbstractTableAction::print(JTable::PrintMode /*mode*/, QString /*headerFormat*/, QString /*footerFormat*/){ log->error("Caught here");}

/*protected*/ /*abstract*/ void AbstractTableAction::addPressed(JActionEvent*) {}

/**
 * Configure the combo box listing managers.
 * Can be placed on Add New pane to select a connection for the new item.
 *
 * @param comboBox     the combo box to configure
 * @param manager      the current manager
 * @param managerClass the implemented manager class for the current
 *                     manager; this is the class used by
 *                     {@link InstanceManager#getDefault(Class)} to get the
 *                     default manager, which may or may not be the current
 *                     manager
 */
/*protected*/ void AbstractTableAction::configureManagerComboBox(ManagerComboBox/*<E>*/* comboBox, Manager/*<E>*/* manager,
        /*Class<? extends Manager<E>>*/QString managerClass) {
    Manager/*<E>*/* defaultManager = (AbstractManager*)InstanceManager::getDefault(managerClass);
    // populate comboBox
    if(qobject_cast<ProxyManager*>(defaultManager->self())) {
        comboBox->setManagers(defaultManager);
    } else {
        comboBox->setManagers(manager);
    }
    // set current selection
    if (qobject_cast<ProxyManager*>(defaultManager->self())) {
        UserPreferencesManager* upm = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
        QString systemSelectionCombo = /*this.getClass().getName()*/QString("jmri.jmrit.beantable.")+metaObject()->className() + ".SystemSelected";
        if (upm->getComboBoxLastSelection(systemSelectionCombo) != "") {
            SystemConnectionMemo* memo = SystemConnectionMemoManager::getDefault()
                    ->getSystemConnectionMemoForUserName(upm->getComboBoxLastSelection(systemSelectionCombo));
            comboBox->setSelectedItem(/*memo->get*/(managerClass));
        } else {
            //ProxyManager/*<E>*/* proxy = (ProxyManager/*<E>*/*) manager;
            if(qobject_cast<ProxyTurnoutManager*>(manager->self()))
             comboBox->setSelectedItem(((ProxyTurnoutManager*)manager->self())->getDefaultManager()->toString());
            if(qobject_cast<ProxySensorManager*>(manager->self()))
             comboBox->setSelectedItem(((ProxySensorManager*)manager->self())->getDefaultManager()->toString());
            if(qobject_cast<ProxyLightManager*>(manager->self()))
             comboBox->setSelectedItem(((ProxyLightManager*)manager->self())->getDefaultManager()->toString());
            if(qobject_cast<ProxyReporterManager*>(manager->self()))
             comboBox->setSelectedItem(((ProxyReporterManager*)manager->self())->getDefaultManager()->toString());
        }
    } else {
        comboBox->setSelectedItem(manager->toString());
    }
}

/**
 * Remove the Add panel prefixBox listener before disposal.
 * The listener is created when the Add panel is defined.  It persists after the
 * the Add panel has been disposed.  When the next Add is created, AbstractTableAction
 * sets the default connection as the current selection.  This triggers validation before
 * the new Add panel is created.
 * <p>
 * The listener is removed by the controlling table action before disposing of the Add
 * panel after Close or Create.
 * @param prefixBox The prefix combobox that might contain the listener.
 */
/*protected*/ void AbstractTableAction::removePrefixBoxListener(ManagerComboBox/*<E>*/* prefixBox) {
    //Arrays.asList(prefixBox.getActionListeners()).forEach((l) ->
//    foreach(ActionListener* l, prefixBox->getActionListeners)
//    {
//        prefixBox->removeActionListener(l);
//    }//);
}

/**
 * Display a warning to user about invalid entry. Needed as entry validation
 * does not disable the Create button when full system name eg "LT1" is entered.
 *
 * @param curAddress address as entered in Add new... pane address field
 * @param ex the exception that occurred
 */
/*protected*/ void AbstractTableAction::displayHwError(QString curAddress, Exception* ex) {
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            showErrorMessage(tr("Error"),
                    tr("Unable to convert \"%1\" to a valid Hardware Address.").arg(curAddress),"" + ex->getMessage(),"",
                    true,false);
}

/*private*/ /*static*/ /*final*/ Logger* AbstractTableAction::log = LoggerFactory::getLogger("AbstractTableAction");
