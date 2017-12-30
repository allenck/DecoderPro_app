#include "memorytableaction.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include <QLabel>
#include <QCheckBox>
#include "addnewbeanpanel.h"
#include <QMessageBox>
#include <QBoxLayout>
#include "userpreferencesmanager.h"

//MemoryTableAction::MemoryTableAction()
//{

//}
/**
 * Swing action to create and register a MemoryTable GUI.
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 */
///*public*/ class MemoryTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param actionName title of the action
 */
/*public*/ MemoryTableAction::MemoryTableAction(QString actionName, QObject* parent)
    : AbstractTableAction(actionName, parent)
{
    //super(actionName);
    common();

    // disable ourself if there is no primary Memory manager available
    if (InstanceManager::memoryManagerInstance() == NULL) {
        setEnabled(false);
    }

}
void MemoryTableAction::common()
{
 addFrame = NULL;
 sysName = new JTextField(5);
 userName = new JTextField(5);
 sysNameLabel = new QLabel(tr("System Name:"));
 userNameLabel = new QLabel(tr("User Name:"));

 numberToAdd = new JTextField(10);
 range = new QCheckBox(tr("Add Range Box"));
 autoSystemName = new QCheckBox(tr("Auto Sys Name"));
 systemNameAuto = QString(this->metaObject()->className()) + ".AutoSystemName";

 log = new Logger("MemoryTableAction");
}

/*public*/ MemoryTableAction::MemoryTableAction(QObject* parent) : AbstractTableAction(tr("Memory Table"), parent)
{
    //this(tr("TitleMemoryTable"));
    common();
}

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Memory objects
 */
/*protected*/ void MemoryTableAction::createModel()
{
 m = new MtBeanTableDataModel(this);
}
MtBeanTableDataModel::MtBeanTableDataModel(MemoryTableAction* mt)
{
    this->act = mt;
    log = new Logger("MtBeanTableDataModel");
    //sysNameList = getManager()->getSystemNameList();
    init();
}
/*public*/ QString MtBeanTableDataModel::getValue(QString name) const
{
    Memory* mem = InstanceManager::memoryManagerInstance()->getBySystemName(name);
    if (mem == NULL) {
        return "?";
    }
    QVariant m = mem->getValue();
    if (!m.isNull()) {
        return m.toString();
    } else {
        return "";
    }
}

/*public*/ Manager* MtBeanTableDataModel::getManager() {
    return InstanceManager::memoryManagerInstance();
}

/*public*/ NamedBean* MtBeanTableDataModel::getBySystemName(QString name)  const
{
    return InstanceManager::memoryManagerInstance()->getBySystemName(name);
}

/*public*/ NamedBean* MtBeanTableDataModel::getByUserName(QString name) {
    return InstanceManager::memoryManagerInstance()->getByUserName(name);
}
/*public int getDisplayDeleteMsg() { return InstanceManager.getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
 public void setDisplayDeleteMsg(int boo) { InstanceManager.getDefault(jmri.UserPreferencesManager.class).setMultipleChoiceOption(getClassName(), "delete", boo); }*/

/*protected*/ QString MtBeanTableDataModel::getMasterClassName() {
    return act->getClassName();
}

/*public*/ void MtBeanTableDataModel::clickOn(NamedBean* t) {
    // don't do anything on click; not used in this class, because
    // we override setValueAt
}

/*public*/ bool MtBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int col = index.column();
  int row = index.column();

    if (col == VALUECOL)
    {
        Memory* t = (Memory*) getBySystemName(sysNameList.at(row));
        t->setValue(value);
        fireTableRowsUpdated(row, row);
        return true;
    }
 }
 return BeanTableDataModel::setData(index, value, role);
}

/*public*/ QVariant MtBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
      int col = section;

    if (col == VALUECOL) {
        return tr("Value");
    }
  }
  return BeanTableDataModel::headerData(section, orientation, role);
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == VALUECOL) {
//        return String.class;
//    } else {
//        return super.getColumnClass(col);
//    }
//}

/*public*/ void MtBeanTableDataModel::configValueColumn(JTable* table) {
    // value column isn't button, so config is NULL
}

/*protected*/ bool MtBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    return true;
    // return (e.getPropertyName().indexOf("alue")>=0);
}

/*public*/ QPushButton* MtBeanTableDataModel::configureButton() {
    log->error("configureButton should not have been called");
    return NULL;
}

/*protected*/ QString MtBeanTableDataModel::getBeanType() {
    return tr("Memory");
}

/*protected*/ void MemoryTableAction::setTitle() {
  f->setTitle(tr("Memory Table"));
}

/*protected*/ QString MemoryTableAction::helpTarget() {
return "package.jmri.jmrit.beantable.MemoryTable";
}
#if 1


/*protected*/ void MemoryTableAction::addPressed(ActionEvent* /*e*/) {
    p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if (addFrame == NULL) {
        addFrame = new JmriJFrame(tr("Add Memory"), false, true);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.MemoryAddEdit", true);
        addFrame->getContentPane()->setLayout(new QVBoxLayout(addFrame->getContentPane()));//, BoxLayout.Y_AXIS));

//        ActionListener okListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                okPressed(e);
//            }
//        };
  MtOkListener* okListener = new MtOkListener(this);
//        ActionListener cancelListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) { cancelPressed(e); }
//        };
  MtCancelListener* cancelListener = new MtCancelListener(this);
  addFrame->getContentPane()->layout()->addWidget(new AddNewBeanPanel(sysName, userName, numberToAdd, range, autoSystemName, "OK", okListener, cancelListener));
    }
    if (p->getSimplePreferenceState(systemNameAuto)) {
        autoSystemName->setChecked(true);
    }
    addFrame->adjustSize();
    addFrame->setVisible(true);
}

MtOkListener::MtOkListener(MemoryTableAction *act) : ActionListener()
{
 this->act = act;
}
void MtOkListener::actionPerformed()
{
 act->okPressed();
}
MtCancelListener::MtCancelListener(MemoryTableAction *act) : ActionListener()
{
 this->act = act;
}
void MtCancelListener::actionPerformed()
{
 act->cancelPressed();
}


void MemoryTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void MemoryTableAction::okPressed(ActionEvent* /*e*/) {

    int numberOfMemory = 1;

    if (range->isChecked())
    {
        bool bOk;
            numberOfMemory = numberToAdd->text().toInt(&bOk);
        if(!bOk){
            log->error("Unable to convert " + numberToAdd->text() + " to a number");

            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showErrorMessage("Error", "Number to memory items to Add must be a number!", "" , "", true, false);
            return;
        }

    }

    if (numberOfMemory >= 65)
    {
//        if (JOptionPane.showConfirmDialog(addFrame,
//                "You are about to add " + numberOfMemory + " Memory Objects into the configuration\nAre you sure?", "Warning",
//                JOptionPane.YES_NO_OPTION) == 1) {
        if(QMessageBox::warning(addFrame, tr("Warning"), tr("You are about to add %1 Memory Objects into the configuration\nAre you sure?").arg(numberOfMemory),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            return;
        }
    }

    QString user = userName->text();
    if (user == ("")) {
        user = "";
    }
    QString sName = sysName->text();
    QString b;
    for (int x = 0; x < numberOfMemory; x++) {
        if (x != 0) {
            if (user != NULL) {
                b =  (userName->text());
                b.append(":");
                b.append(QString::number(x));
                user = b;
            }
            if (!autoSystemName->isChecked()) {
                b = sysName->text();
                b.append(":");
                b.append(QString::number(x));
                sName = b;
            }
        }
        //try {
            if (autoSystemName->isChecked()) {
                if(InstanceManager::memoryManagerInstance()->newMemory(user) == NULL)
                {
                    handleCreateException(sName);
                    return;
                }
            } else {
               if(InstanceManager::memoryManagerInstance()->newMemory(sName, user))
               {
                   handleCreateException(sName);
                   return;
               }
            }
//        } catch (IllegalArgumentException ex) {
//            // user input no good
//            handleCreateException(sName);
//            return; // without creating
//        }
    }
    p->setSimplePreferenceState(systemNameAuto, autoSystemName->isChecked());
}
//private bool noWarn = false;

void MemoryTableAction::handleCreateException(QString sysName) {
//    javax.swing.JOptionPane.showMessageDialog(addFrame,
//            java.text.MessageFormat.format(
//                    tr("ErrorMemoryAddFailed"),
//                    new Object[]{sysName}),
//            tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(addFrame, tr("Error"), tr("Could not create memory %1 to add it. Check that number/name is OK.").arg(sysName));
}

/*public*/ QString MemoryTableAction::getClassDescription() {
    return tr("Memory Table");
}
#endif
/*protected*/ QString MemoryTableAction::getClassName() {
    return "jmri.jmrit.beantable.MemoryTableAction";
}

