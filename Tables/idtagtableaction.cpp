#include "idtagtableaction.h"
#include "idtagmanager.h"
#include "idtag.h"
#include "instancemanager.h"
#include <QPushButton>
#include "userpreferencesmanager.h"
#include "jtextfield.h"
#include <QCheckBox>
#include "reporter.h"
#include "joptionpane.h"
#include "abstracttabletabaction.h"
#include <QBoxLayout>
#include "addnewdevicepanel.h"
#include "rfid/proxyidtagmanager.h"

//IdTagTableAction::IdTagTableAction()
//{

//}
/**
 * Swing action to create and register a IdTagTable GUI.
 *
 * @author  Bob Jacobsen Copyright (C) 2003
 * @author  Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class IdTagTableAction extends AbstractTableAction {

/**
* Create an action with a specific title.
* <P>
* Note that the argument is the Action title, not the title of the
* resulting frame. Perhaps this should be changed?
*
* @param actionName title of the action
*/
//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ IdTagTableAction::IdTagTableAction(QString actionName, QObject* parent) :
    AbstractTableAction(actionName, parent)
{
 //super(actionName);
 log = new Logger("IdTagTableAction");
 addFrame = NULL;
 sysName = new JTextField(12);
 userName = new JTextField(15);
 isStateStored = new QCheckBox(tr("Store State"));
 isFastClockUsed = new QCheckBox(tr("Use Fast Clock"));

    // disable ourself if there is no primary IdTag manager available
    if (((IdTagManager*)InstanceManager::getDefault("IdTagManager")) == NULL) {
        setEnabled(false);
    }

}

/*public*/ IdTagTableAction::IdTagTableAction(QObject* parent) : AbstractTableAction(tr("IdTag Table"), parent)
{
//this(tr("TitleIdTagTable"));
}

/**
* Create the JTable DataModel, along with the changes for the specific case
* of IdTag objects
*/
//@Override
/*protected*/ void IdTagTableAction::createModel()
{
 m = new IdTagBeanTableDataModel(this);
}

IdTagBeanTableDataModel::IdTagBeanTableDataModel(IdTagTableAction *act)
{
 this->act = act;
 log = new Logger("IdTagBeanTableDataModel");
 init();
}

//@Override
/*public*/ QString IdTagBeanTableDataModel::getValue(QString name) const
{
    DefaultIdTag* tag =(DefaultIdTag*)((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getBySystemName(name);
    if (tag == NULL) {
        return "?";
    }
    QVariant t = tag->getTagID();
    if (!t.isNull()) {
        return t.toString();
    } else {
        return "";
    }
}

//@Override
/*public*/ AbstractManager* IdTagBeanTableDataModel::getManager() {
    IdTagManager* m = (IdTagManager*)InstanceManager::getDefault("IdTagManager");
    if (!m->isInitialised()) {
        m->init();
    }
    return m;
}

//@Override
/*public*/ NamedBean* IdTagBeanTableDataModel::getBySystemName(QString name) const
{
    return ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getBySystemName(name);
}

//@Override
/*public*/ NamedBean* IdTagBeanTableDataModel::getByUserName(QString name) {
    return ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getByUserName(name);
}
/*public int getDisplayDeleteMsg() { return InstanceManager::getDefault("UserPreferencesManager")->getWarnMemoryInUse(); }
 public void setDisplayDeleteMsg(int boo) { InstanceManager::getDefault(jmri.UserPreferencesManager.class).setWarnMemoryInUse(boo); }*/

//@Override
/*public*/ void IdTagBeanTableDataModel::clickOn(NamedBean* t) {
    // don't do anything on click; not used in this class, because
    // we override setValueAt
}

//@Override
/*public*/ bool IdTagBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::DisplayRole)
 {
  int col = index.column();
  int row = index.row();
    if (col == CLEARCOL) {
        IdTag* t = (IdTag*) getBySystemName(sysNameList.at(row));
        if (log->isDebugEnabled()) {
            log->debug("Clear where & when last seen for " + ((NamedBean*)t->self())->getSystemName());
        }
        t->setWhereLastSeen(NULL);
        fireTableRowsUpdated(row, row);
    }
 }
 return BeanTableDataModel:: setData(index, value, role);
}

//@Override
/*public*/ int IdTagBeanTableDataModel::columnCount(const QModelIndex &parent) const
{
    return CLEARCOL + 1;
}

//@Override
/*public*/ QVariant IdTagBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 int col = section;
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (col) {
        case VALUECOL:
            return tr("IdTagID");
        case WHERECOL:
            return tr("IdWhere");
        case WHENCOL:
            return tr("IdWhen");
        case CLEARCOL:
            return "";
        default:
        break;
    }
  }
 return BeanTableDataModel::headerData(section, orientation, role);
}

//@Override
///*public*/ Class<?> getColumnClass(int col) {
//    switch (col) {
//        case VALUECOL:
//        case WHERECOL:
//        case WHENCOL:
//            return String.class;
//        case CLEARCOL:
//            return JButton.class;
//        default:
//            return super.getColumnClass(col);
//    }
//}

//@Override
/*public*/ Qt::ItemFlags IdTagBeanTableDataModel::flags(const QModelIndex &index) const
{
    int col = index.column();
    switch (col) {
        case VALUECOL:
        case WHERECOL:
        case WHENCOL:
            return Qt::ItemIsEnabled;
        case CLEARCOL:
            return Qt::ItemIsEnabled | Qt::ItemIsEditable;
        default:
        break;
    }
  return BeanTableDataModel::flags(index);

}

//@Override
/*public*/ QVariant IdTagBeanTableDataModel::data(const QModelIndex &index, int role) const
{
    DefaultIdTag* t;
    int col = index.column();
    int row = index.row();
    if(role == Qt::DisplayRole)
    {
    switch (col)
    {
     case WHERECOL:
        Reporter* r;
        t = (DefaultIdTag*) getBySystemName(sysNameList.at(row));
        return (t != NULL) ? (((r = t->getWhereLastSeen()) != NULL) ? r->getSystemName() : QVariant()) : QVariant();
     case WHENCOL:
     {
        QDateTime d;
        t = (DefaultIdTag*) getBySystemName(sysNameList.at(row));
        return (t != NULL) ? (((d = t->getWhenLastSeen()) != QDateTime())
                ? /*DateFormat.getDateTimeInstance(DateFormat.SHORT*/ QDateTime::currentDateTime().toString(), /*DateFormat.MEDIUM).format(d)*/d.toString() : QVariant()) : QVariant();
     }
     case CLEARCOL:
            return tr("Clear");
        default:
            break;
    }
 }
  return BeanTableDataModel::data(index, role);
}

//@Override
/*public*/ int IdTagBeanTableDataModel::getPreferredWidth(int col) {
    switch (col) {
        case SYSNAMECOL:
        case WHERECOL:
        case WHENCOL:
            return  JTextField(12).sizeHint().width();;
        case VALUECOL:
            return  JTextField(10).sizeHint().width();;
        case CLEARCOL:
            return  QPushButton(tr("Clear")).sizeHint().width(); + 4;
        default:
            return BeanTableDataModel::getPreferredWidth(col);
    }
}

//@Override
/*public*/ void IdTagBeanTableDataModel::configValueColumn(JTable* table) {
    // value column isn't button, so config is NULL
}
void IdTagBeanTableDataModel::configureTable(JTable *table)
{
 setColumnToHoldButton(table,CLEARCOL);
}

//@Override
/*protected*/ bool IdTagBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    return true;
    // return (e.getPropertyName().indexOf("alue")>=0);
}

//@Override
/*public*/ QPushButton* IdTagBeanTableDataModel::configureButton() {
    log->error("configureButton should not have been called");
    return NULL;
}

//@Override
/*protected*/ QString IdTagBeanTableDataModel::getMasterClassName() {
    return /*act->getClassName();*/ "jmri.jmrit.beantable.IdTagTableAction";
}

//@Override
/*protected*/ QString IdTagBeanTableDataModel::getBeanType() {
    return "ID Tag";
}

//@Override
/*protected*/ void IdTagTableAction::setTitle() {
    f->setTitle(tr("TitleIdTagTable"));
}

//@Override
/*protected*/ QString IdTagTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.IdTagTable";
}


//@Override
/*protected*/ void IdTagTableAction::addPressed(/*ActionEvent* e*/) {
    if (addFrame == NULL) {
        addFrame = new JmriJFrameX(tr("Add Id Tag"), false, true);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.IdTagAddEdit", true);
        QVBoxLayout* thisLayout;
        addFrame->getContentPane()->setLayout(thisLayout = new QVBoxLayout()); //, BoxLayout.Y_AXIS));

//        ActionListener okListener = (ActionEvent ev) -> {
//            okPressed(ev);
//        };
        IdTagOkListener* okListener = new IdTagOkListener(this);

//        ActionListener cancelListener = (ActionEvent ev) -> {
//            cancelPressed(ev);
//        };
        CancelListener* cancelListener = new CancelListener(this);

        thisLayout->addWidget(new AddNewDevicePanel(sysName, userName, "OK", okListener, cancelListener));
    }
    addFrame->adjustSize();
    addFrame->setVisible(true);
}

void IdTagTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void IdTagTableAction::okPressed(ActionEvent* /*e*/) {
    QString user = userName->text();
    if (user==("")) {
        user = "";
    }
//        String tag = tagID.getText();
//        if (tag.equals("")) tag=NULL;
    QString sName = sysName->text();
    //try {
        if(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->newIdTag(sName, user)== NULL)
//      ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->newIdTag(sName, user);
//    } catch (IllegalArgumentException ex) {
        {
        // user input no good
        handleCreateException(sName);
    }
    addFrame->close();
}
//private boolean noWarn = false;
IdTagOkListener::IdTagOkListener(IdTagTableAction *act)
{
    this->act = act;
}
void IdTagOkListener::actionPerformed(JActionEvent *)
{
  act->okPressed();
}
CancelListener::CancelListener(IdTagTableAction *act)
{ this->act = act; }
void CancelListener::actionPerformed(JActionEvent */*e*/)
{
    act->cancelPressed();
}

void IdTagTableAction::handleCreateException(QString sysName) {
    JOptionPane::showMessageDialog(addFrame,
            tr("Could not create ID tag \"%1\" to add it. Check that number/name is OK.").arg(sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

//@Override
/*public*/ QString IdTagTableAction::getClassDescription() {
    return tr("IdTag Table");
}

//@Override
/*public*/ void IdTagTableAction::addToFrame(BeanTableFrame* f) {
    f->addToBottomBox(isStateStored, this->metaObject()->className());
    IdTagManager* mgr = (IdTagManager*)InstanceManager::getDefault("IdTagManager");
    isStateStored->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isStateStored());
//    isStateStored->addActionListener((ActionEvent e) -> {
//        ((IdTagManager*)InstanceManager::getDefault("IdTagManager")).setStateStored(isStateStored.isSelected());
//    });
    StateStoredActionListener* stateStoredActionListener = new StateStoredActionListener(this);
    //connect(isStateStored, SIGNAL(toggled(bool)), stateStoredActionListener->self(), SLOT(actionPerformed()));
    connect(isStateStored, &QCheckBox::clicked, [=]{stateStoredActionListener->actionPerformed();});
    f->addToBottomBox(isFastClockUsed, this->metaObject()->className());
    isFastClockUsed->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isFastClockUsed());
//    isFastClockUsed.addActionListener((ActionEvent e) -> {
//        ((IdTagManager*)InstanceManager::getDefault("IdTagManager")).setFastClockUsed(isFastClockUsed.isSelected());
//    });
    FastClockUsedActionListener* fastClockUsedActionListener = new FastClockUsedActionListener(this);
    //connect(isFastClockUsed, SIGNAL(toggled(bool)), fastClockUsedActionListener->self(), SLOT(actionPerformed()));
    connect(isFastClockUsed, &QCheckBox::clicked, [=]{fastClockUsedActionListener->actionPerformed();});
    log->debug("Added CheckBox in addToFrame method");
}
StateStoredActionListener::StateStoredActionListener(IdTagTableAction* act)
{
  this->act = act;
}
void StateStoredActionListener::actionPerformed(JActionEvent *)
{
 ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setStateStored(act->isStateStored->isChecked());

}
FastClockUsedActionListener::FastClockUsedActionListener(IdTagTableAction *act)
{
    this->act = act;
}
void FastClockUsedActionListener::actionPerformed(JActionEvent *)
{
    ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->setFastClockUsed(act->isFastClockUsed->isChecked());
}

//@Override
/*public*/ void IdTagTableAction::addToPanel(AbstractTableTabAction* f) {
    QString connectionName = tagManager->getMemo()->getUserName();
    if (qobject_cast<ProxyIdTagManager*>(tagManager)) {
        connectionName = "All";
    }
//    else if (connectionName == nullptr && (tagManager instanceof DefaultRailComManager)) {
//        connectionName = "RailCom"; // NOI18N (proper name).
//    }
    f->addToBottomBox(isStateStored, this->metaObject()->className());
    isStateStored->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isStateStored());
//    isStateStored.addActionListener((ActionEvent e) -> {
//        ((IdTagManager*)InstanceManager::getDefault("IdTagManager")).setStateStored(isStateStored.isSelected());
//    });
    StateStoredActionListener* stateStoredActionListener = new StateStoredActionListener(this);
    connect(isStateStored, SIGNAL(toggled(bool)), stateStoredActionListener->self(), SLOT(actionPerformed()));
    f->addToBottomBox(isFastClockUsed, this->metaObject()->className());
    isFastClockUsed->setChecked(((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->isFastClockUsed());
//    isFastClockUsed.addActionListener((ActionEvent e) -> {
//        ((IdTagManager*)InstanceManager::getDefault("IdTagManager")).setFastClockUsed(isFastClockUsed.isSelected());
//    });
    FastClockUsedActionListener* fastClockUsedActionListener = new FastClockUsedActionListener(this);
    connect(isFastClockUsed, SIGNAL(toggled(bool)), fastClockUsedActionListener->self(), SLOT(actionPerformed()));
    log->debug("Added CheckBox in addToPanel method");
}

//@Override
/*protected*/ QString IdTagTableAction::getClassName() {
    return "jmri.jmrit.beantable.IdTagTableAction";
}
