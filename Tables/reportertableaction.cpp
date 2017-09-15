#include "reportertableaction.h"
#include "reportermanager.h"
#include "jmrijframe.h"
#include "jtextfield.h"
#include <QCheckBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "instancemanager.h"
#include "connectionnamefromsystemname.h"
#include "userpreferencesmanager.h"
#include "addnewhardwaredevicepanel.h"
#include <QMessageBox>
#include "proxyreportermanager.h"

//ReporterTableAction::ReporterTableAction()
//{

//}
/**
 * Swing action to create and register a ReporterTable GUI.
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 */
///*public*/ class ReporterTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param actionName title of the action
 */
/*public*/ ReporterTableAction::ReporterTableAction(QString actionName, QObject* parent)
    : AbstractTableAction(actionName, parent)
{
    //super(actionName);
    common();

    // disable ourself if there is no primary Reporter manager available
    if (reportManager == NULL) {
        setEnabled(false);
    }
}


/*public*/ void ReporterTableAction::setManager(ReporterManager* man) {
    reportManager = man;
}

/*public*/ ReporterTableAction::ReporterTableAction(QObject* parent) : AbstractTableAction(tr("TitleReporterTable"), parent)
{
    //this(tr("TitleReporterTable"));

}
void ReporterTableAction::common()
{
 reportManager = InstanceManager::reporterManagerInstance();
 log = new Logger("ReporterTableAction");

 addFrame = NULL;
 sysName = new JTextField(10);
 userName = new JTextField(20);
 prefixBox = new QComboBox();
 numberToAdd = new JTextField(10);
 range = new QCheckBox(tr("AddRangeBox"));
 sysNameLabel = new QLabel("Hardware Address");
 userNameLabel = new QLabel(tr("User Name"));
 systemSelectionCombo = QString(metaObject()->className()) + ".SystemSelected";
 userNameError = QString(this->metaObject()->className()) + ".DuplicateUserName";
}

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Reporters
 */
/*protected*/ void ReporterTableAction::createModel()
{
 m = new RtBeanTableDataModel(this);
}

RtBeanTableDataModel::RtBeanTableDataModel(ReporterTableAction* act)
{
    this->act = act;
    log = new Logger("RtBeanTableDataModel");
    init();
}
/*public*/ /*static*/ /*final*/ int RtBeanTableDataModel::LASTREPORTCOL = RtBeanTableDataModel::NUMCOLUMN;

/*public*/ QString RtBeanTableDataModel::getValue(QString name) const
{
    QVariant value;
    return (value = act->reportManager->getBySystemName(name)->getCurrentReport()) == QVariant() ? "" : value.toString();
}

/*public*/ Manager* RtBeanTableDataModel::getManager() {
    return act->reportManager;
}

/*public*/ NamedBean* RtBeanTableDataModel::getBySystemName(QString name)  const
{
    return ((ProxyReporterManager*)act->reportManager)->getBySystemName(name);
}

/*public*/ NamedBean* RtBeanTableDataModel::getByUserName(QString name) {
    return act->reportManager->getByUserName(name);
}
/*public int getDisplayDeleteMsg() { return InstanceManager.getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
 public void setDisplayDeleteMsg(int boo) { InstanceManager.getDefault(jmri.UserPreferencesManager.class).setMultipleChoiceOption(getClassName(), "delete", boo); }*/

/*protected*/ QString RtBeanTableDataModel::getMasterClassName() {
    return act->getClassName();
}

/*public*/ void RtBeanTableDataModel::clickOn(NamedBean* t) {
    // don't do anything on click; not used in this class, because
    // we override setValueAt
}

/*public*/ bool RtBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int col = index.column();
    int row = index.row();

  if(role == Qt::EditRole)
  {

    if (col == VALUECOL) {
        Reporter* t = (Reporter*) getBySystemName(sysNameList.at(row));
        t->setReport(value);
        fireTableRowsUpdated(row, row);
    }
    if (col == LASTREPORTCOL) {
        // do nothing
    }
  }
  BeanTableDataModel::setData(index, value,role);
}

/*public*/ int RtBeanTableDataModel::columnCount(const QModelIndex &parent) const
{
    return LASTREPORTCOL + 1;
}

/*public*/ QVariant RtBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 int col = section;
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (col == VALUECOL) {
        return tr("Report");
    }
    if (col == LASTREPORTCOL) {
        return tr("Last Report");
    }
 }
    return BeanTableDataModel::headerData(section, orientation, role);
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == VALUECOL) {
//        return String.class;
//    }
//    if (col == LASTREPORTCOL) {
//        return String.class;
//    }
//    return super.getColumnClass(col);
//}

/*public*/ Qt::ItemFlags RtBeanTableDataModel::flags(const QModelIndex &index) const
{
 int col = index.column();
    if (col == LASTREPORTCOL) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return BeanTableDataModel::flags(index);
}

/*public*/ QVariant RtBeanTableDataModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int col = index.column();
  int row = index.row();
    if (col == LASTREPORTCOL) {
        Reporter* t = (Reporter*) getBySystemName(sysNameList.at(row));
        return t->getLastReport();
    }
 }
    return BeanTableDataModel::data(index, role);
}

/*public*/ int RtBeanTableDataModel::getPreferredWidth(int col) {
    if (col == LASTREPORTCOL) {
        return BeanTableDataModel::getPreferredWidth(VALUECOL);
    }
    return BeanTableDataModel::getPreferredWidth(col);
}

/*public*/ void RtBeanTableDataModel::configValueColumn(JTable* table) {
    // value column isn't button, so config is NULL
}

/*protected*/ bool RtBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    return true;
    // return (e.getPropertyName().indexOf("Report")>=0);
}

/*public*/ QPushButton* RtBeanTableDataModel::configureButton() {
    log->error("configureButton should not have been called");
    return NULL;
}

/*protected*/ QString RtBeanTableDataModel::getBeanType() {
    return tr("Reporter");
}

/*protected*/ void ReporterTableAction::setTitle() {
    f->setTitle(tr("TitleReporterTable"));
}

/*protected*/ QString ReporterTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.ReporterTable";
}

/*protected*/ void ReporterTableAction::addPressed(ActionEvent* /*e*/) {
    pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if (addFrame == NULL) {
        addFrame = new JmriJFrame(tr("Add Reporter"), false, true);
        QWidget* centralWidget = new QWidget(addFrame);
        addFrameLayout = new QVBoxLayout(centralWidget);
        addFrame->setCentralWidget(centralWidget);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.ReporterAddEdit", true);
        OkActionListener* okListener = new OkActionListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                okPressed(e);
//            }
//        };
        CancelActionListener* cancelListener = new CancelActionListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) { cancelPressed(e); }
//        };
        ReporterRangeListener* rangeListener = new ReporterRangeListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                canAddRange(e);
//            }
//        };
        if (QString(reportManager->metaObject()->className()).contains("ProxyReporterManager"))
        {
            ProxyReporterManager* proxy = (ProxyReporterManager*) reportManager;
            QList<Manager*> managerList = proxy->getManagerList();
            for (int x = 0; x < managerList.size(); x++) {
                QString manuName = ConnectionNameFromSystemName::getConnectionName(managerList.at(x)->getSystemPrefix());
                bool addToPrefix = true;
                //Simple test not to add a system with a duplicate System prefix
                for (int i = 0; i < prefixBox->count(); i++) {
                    if ((prefixBox->itemText(i)) == (manuName)) {
                        addToPrefix = false;
                    }
                }
                if (addToPrefix) {
                    prefixBox->addItem(manuName);
                }
            }
            if (pref->getComboBoxLastSelection(systemSelectionCombo) != NULL) {
                prefixBox->setCurrentIndex(prefixBox->findText(pref->getComboBoxLastSelection(systemSelectionCombo)));
            }
        } else {
            prefixBox->addItem(ConnectionNameFromSystemName::getConnectionName(reportManager->getSystemPrefix()));
        }
        sysName->setObjectName("sysName");
        userName->setObjectName("userName");
        prefixBox->setObjectName("prefixBox");
        addFrameLayout->addWidget(new AddNewHardwareDevicePanel(sysName, userName, prefixBox, numberToAdd, range, "OK", okListener, cancelListener, rangeListener));
        canAddRange(NULL);
    }
    addFrame->adjustSize();
    addFrame->setVisible(true);
}
OkActionListener::OkActionListener(ReporterTableAction* act) { this->act = act;}
/*public*/ void OkActionListener::actionPerformed(ActionEvent* /*e*/) {
    act->okPressed();
}
CancelActionListener::CancelActionListener(ReporterTableAction *act) { this->act = act;}
/*public*/ void CancelActionListener::actionPerformed(ActionEvent* /*e*/) { act->cancelPressed(); }

ReporterRangeListener::ReporterRangeListener(ReporterTableAction *act) { this->act = act;}
/*public*/ void ReporterRangeListener::actionPerformed(ActionEvent* /*e*/) {
    act->canAddRange();
}


void ReporterTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void ReporterTableAction::okPressed(ActionEvent* /*e*/) {
    int numberOfReporters = 1;

    if (range->isChecked()) {
        bool bOk;
            numberOfReporters = numberToAdd->text().toInt(&bOk);
        if(!bOk)
        {
             log->error("Unable to convert " + numberToAdd->text() + " to a number");
            ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                    showErrorMessage("Error", "Number to Reporters to Add must be a number!", "" , "", true, false);
            return;
        }
    }
    if (numberOfReporters >= 65) {
//        if (JOptionPane.showConfirmDialog(addFrame,
//                "You are about to add " + numberOfReporters + " Reporters into the configuration\nAre you sure?", "Warning",
//                JOptionPane.YES_NO_OPTION) == 1) {
        if(QMessageBox::question(addFrame, tr("Warning"), tr("You are about to add %1 Reporters into the configuration\nAre you sure?").arg(numberOfReporters), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            return;
        }
    }
    QString reporterPrefix = ConnectionNameFromSystemName::getPrefixFromName((QString) prefixBox->currentText());

    QString rName = NULL;
    QString curAddress = sysName->text();

    for (int x = 0; x < numberOfReporters; x++)
    {
        curAddress = ((ProxyReporterManager*)reportManager)->getNextValidAddress(curAddress, reporterPrefix);
        if (curAddress == NULL) {
            //The next address is already in use, therefore we stop.
            break;
        }
        //We have found another turnout with the same address, therefore we need to go onto the next address.
        rName = reporterPrefix + reportManager->typeLetter() + curAddress;
        Reporter* r = NULL;
        //try {
            r = ((ProxyReporterManager*)reportManager)->provideReporter(rName);
        if(r == NULL) {
            // user input no good
            handleCreateException(rName);
            return; // without creating
        }
        if (r != NULL) {
            QString user = userName->text();
            if ((x != 0) && user != NULL && user != ("")) {
                user = userName->text() + ":" + x;
            }
            if (user != NULL && user != ("") && (reportManager->getByUserName(user) == NULL)) {
                r->setUserName(user);
            } else if (((ProxyReporterManager*)reportManager)->getByUserName(user) != NULL && !pref->getPreferenceState(getClassName(), userNameError)) {
                pref->showErrorMessage("Duplicate UserName", "The username " + user + " specified is already in use and therefore will not be set", userNameError, "", false, true);
            }
        }
    }
    pref->addComboBoxLastSelection(systemSelectionCombo, (QString) prefixBox->currentText());
}

/*private*/ void ReporterTableAction::canAddRange(ActionEvent* /*e*/)
{
    range->setEnabled(false);
    range->setChecked(false);
    if (QString(reportManager->metaObject()->className()).contains("ProxyReporterManager"))
    {
        ProxyReporterManager* proxy = (ProxyReporterManager*) reportManager;
        QList<Manager*> managerList = proxy->getManagerList();
        QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName(prefixBox->currentText());
        for (int x = 0; x < managerList.size(); x++) {
            ReporterManager* mgr = (ReporterManager*) managerList.at(x);
            QString sp = mgr->getSystemPrefix();
            bool bam = mgr->allowMultipleAdditions(systemPrefix);
            if (mgr->getSystemPrefix() == (systemPrefix) && mgr->allowMultipleAdditions(systemPrefix)) {
                range->setEnabled(true);
                return;
            }
        }
    } else if (reportManager->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()))) {
        range->setEnabled(true);
    }
}

void ReporterTableAction::handleCreateException(QString sysName) {
//    javax.swing.JOptionPane.showMessageDialog(addFrame,
//            java.text.MessageFormat.format(
//                    tr("ErrorReporterAddFailed"),
//                    new Object[]{sysName}),
//            tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(addFrame, tr("Error"),tr("Could not create Reporter %1 to add it. Check that number/name is OK.").arg(sysName));
}

/*protected*/ QString ReporterTableAction::getClassName() {
    return "ReporterTableAction";
}

/*public*/ QString  ReporterTableAction::getClassDescription() {
    return tr("TitleReporterTable");
}

