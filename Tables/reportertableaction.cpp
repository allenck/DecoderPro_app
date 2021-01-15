#include "reportertableaction.h"
#include "jmrijframe.h"
#include <QCheckBox>
#include <QBoxLayout>
#include "connectionnamefromsystemname.h"
#include "userpreferencesmanager.h"
#include "addnewhardwaredevicepanel.h"
#include "joptionpane.h"
#include "proxyreportermanager.h"
#include <reportable.h>
#include "vptr.h"
#include "rfid/reportervariant.h"

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
    if (reporterManager == nullptr) {
        setEnabled(false);
    }
}


/*public*/ void ReporterTableAction::setManager(ReporterManager* man) {
    reporterManager = man;
}

/*public*/ ReporterTableAction::ReporterTableAction(QObject* parent) : AbstractTableAction(tr("TitleReporterTable"), parent)
{
    //this(tr("TitleReporterTable"));

}
void ReporterTableAction::common()
{
 reporterManager = (ReporterManager*)InstanceManager::getDefault("ReporterManager");
 log = new Logger("ReporterTableAction");

 addFrame = NULL;
 sysNameLabel = new JLabel("Hardware Address");
 userNameLabel = new JLabel(tr("User Name"));
 systemSelectionCombo = QString(metaObject()->className()) + ".SystemSelected";
 userNameError = QString(this->metaObject()->className()) + ".DuplicateUserName";
 connectionChoice = "";
 statusBarLabel = new JLabel(tr("Enter a Hardware Address and (optional) User Name.")/*, JLabel.LEADING*/);
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
   Reporter* r = (Reporter*)act->reporterManager->getBySystemName(name);
   if (r == nullptr) {
       return "";
   }
   value = r->getCurrentReport();
   if(value == QVariant()) {
      return "";
   }
   //else if(value instanceof jmri.Reportable)
   //if(value.canConvert<Reportable*>())
   QObject* obj = VPtr<QObject>::asPtr(value);
   if(obj)
   {
      //return ((jmri.Reportable)value).toReportString();
       //return value.convert<Reportable>();
       return VPtr<Reportable>::asPtr(value)->toReportString();
   } else {
      return value.toString();
   }
}

/*public*/ Manager* RtBeanTableDataModel::getManager() {
    return act->reporterManager;
}

/*public*/ NamedBean* RtBeanTableDataModel::getBySystemName(QString name)  const
{
    return ((ProxyReporterManager*)act->reporterManager)->getBySystemName(name);
}

/*public*/ NamedBean* RtBeanTableDataModel::getByUserName(QString name) {
    return act->reporterManager->getByUserName(name);
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
#if 1
    pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if (addFrame == NULL) {
        addFrame = new JmriJFrameX(tr("Add Reporter"), false, true);
        addFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
        QWidget* centralWidget = new QWidget(addFrame);
        addFrameLayout = new QVBoxLayout(centralWidget);
        addFrame->setCentralWidget(centralWidget);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.ReporterAddEdit", true);
        RTACreateListener* createListener = new RTACreateListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                okPressed(e);
//            }
//        };
        RTACancelActionListener* cancelListener = new RTACancelActionListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) { cancelPressed(e); }
//        };
        ReporterRangeListener* rangeListener = new ReporterRangeListener(this);
//        {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                canAddRange(e);
//            }
//        };
        configureManagerComboBox(prefixBox, reporterManager, "ReporterManager");
        userNameTextField->setObjectName("userName");
        prefixBox->setName("prefixBox");
        addButton = new JButton(tr("Create"));
        //addButton.addActionListener(createListener);
        connect(addButton, &JButton::clicked, [=]{createListener->actionPerformed();});
        hardwareAddressValidator = new SystemNameValidator(hardwareAddressTextField, prefixBox->getSelectedItem(), true);
        // create panel
        addFrameLayout->addWidget(new AddNewHardwareDevicePanel(hardwareAddressTextField, hardwareAddressValidator, userNameTextField, prefixBox,
                                                                numberToAddSpinner, rangeCheckBox, addButton, cancelListener, rangeListener, statusBarLabel));

        canAddRange(NULL);
    }
    hardwareAddressTextField->setObjectName("hwAddressTextField"); // for GUI test NOI18N
    //hardwareAddressTextField->setBackground(Color.yellow);
    hardwareAddressTextField->setBackground(QColor(Qt::yellow));
    //addButton.addActionListener(createListener);
    // reset statusBar text
    statusBarLabel->setText(tr("Enter a Hardware Address and (optional) User Name."));
    statusBarLabel->setStyleSheet("QEditLine {color: gray}");

    addFrame->pack();
    addFrame->setVisible(true);
#endif
}
RTACreateListener::RTACreateListener(ReporterTableAction* act) { this->act = act;}
/*public*/ void RTACreateListener::actionPerformed(JActionEvent* /*e*/) {
    act->createPressed();
}
RTACancelActionListener::RTACancelActionListener(ReporterTableAction *act) { this->act = act;}
/*public*/ void RTACancelActionListener::actionPerformed(JActionEvent* /*e*/) { act->cancelPressed(); }

ReporterRangeListener::ReporterRangeListener(ReporterTableAction *act) { this->act = act;}
/*public*/ void ReporterRangeListener::actionPerformed(JActionEvent* /*e*/) {
    act->canAddRange();
}


void ReporterTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = nullptr;
}

void ReporterTableAction::createPressed(ActionEvent* /*e*/)
{
 int numberOfReporters = 1;

 if (rangeCheckBox->isChecked()) {
  numberOfReporters = numberToAddSpinner->value();

 }
 if (numberOfReporters >= 65) {
        if (JOptionPane::showConfirmDialog(addFrame,
                tr("You are about to add %1 Reporters into the configuration\nAre you sure?").arg(numberOfReporters),
                tr("Warning"),
                JOptionPane::YES_NO_OPTION) == 1) {
      return;
  }
 }

 QString rName = "";
 QString reporterPrefix = ConnectionNameFromSystemName::getPrefixFromName((QString) prefixBox->currentText());
 QString curAddress = hardwareAddressTextField->text();
// initial check for empty entry
 if (curAddress.length() < 1)
 {
   statusBarLabel->setText(tr("You must provide a Hardware Address to start."));
   statusBarLabel->setStyleSheet("QLabel {color: red}");
   hardwareAddressTextField->setBackground(QColor(Qt::red));
   return;
  }
 else {
      hardwareAddressTextField->setBackground(QColor(Qt::white));
  }
 // Add some entry pattern checking, before assembling sName and handing it to the ReporterManager
 QString statusMessage = tr("New %1(s) added:").arg(tr("Reporter"));
 QString errorMessage = "";
 for (int x = 0; x < numberOfReporters; x++)
 {
  curAddress = ((ProxyReporterManager*)reporterManager)->getNextValidAddress(curAddress, reporterPrefix);
  if (curAddress == "") {
   log->debug("Error converting HW or getNextValidAddress");
   errorMessage = (tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip)."));
   statusBarLabel->setStyleSheet("QEditLine {color: red}");
   // The next address returned an error, therefore we stop this attempt and go to the next address.
  }

  // Compose the proposed system name from parts:
  rName = reporterPrefix + reporterManager->typeLetter() + curAddress;
  Reporter* r = nullptr;
  //try {
      r = ((ProxyReporterManager*)reporterManager)->provideReporter(rName);
  if(r == nullptr)
  {
      // user input no good
   handleCreateException(rName); // displays message dialog to the user
   // add to statusBar as well
   errorMessage = tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip).");
   statusBarLabel->setText(errorMessage);
   statusBarLabel->setStyleSheet("QLabel {color: red}");
      return; // without creating
  }
  if (r != nullptr)
  {
      QString user = userNameTextField->text().trimmed();
      if ((x != 0) && user != "" && user != ("")) {
          user = userNameTextField->text() + ":" + x;
      }
      if (user != "" && user != ("") && (reporterManager->getByUserName(user) == nullptr)) {
          r->setUserName(user);
      } else if (((ProxyReporterManager*)reporterManager)->getByUserName(user) != nullptr && !pref->getPreferenceState(getClassName(), userNameError))
      {
          pref->showErrorMessage("Duplicate UserName", "The username " + user + " specified is already in use and therefore will not be set", userNameError, "", false, true);
      }
      // add first and last names to statusMessage user feedback string
      if (x == 0 || x == numberOfReporters - 1) {
          statusMessage = statusMessage + " " + rName + " (" + user + ")";
      }
      if (x == numberOfReporters - 2) {
          statusMessage = statusMessage + " " + tr("up to") + " ";
      }
      // only mention first and last of range added

      // end of for loop creating range of Reporters
  }
 }
 // provide feedback to user
 if (errorMessage == "") {
     statusBarLabel->setText(statusMessage);
     statusBarLabel->setStyleSheet("QLabel {color: gray}");
 } else {
     statusBarLabel->setText(errorMessage);
     // statusBar.setForeground(Color.red); // handled when errorMassage is set to differentiate urgency
 }

 pref->setComboBoxLastSelection(systemSelectionCombo, prefixBox->currentText());
 addFrame->setVisible(false);
 addFrame->dispose();
 addFrame = nullptr;
}

/*private*/ void ReporterTableAction::canAddRange(ActionEvent* /*e*/)
{
 rangeCheckBox->setEnabled(false);
 rangeCheckBox->setChecked(false);
 connectionChoice =  prefixBox->currentText(); // store in Field for CheckedTextField
 if (connectionChoice == "") {
     // Tab All or first time opening, default tooltip
     connectionChoice = "TBD";
 }
 if (QString(reporterManager->metaObject()->className()).contains("ProxyReporterManager"))
 {
  ProxyReporterManager* proxy = (ProxyReporterManager*) reporterManager;
  QList<Manager*> managerList = proxy->getManagerList();
  QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName(connectionChoice);
  for (int x = 0; x < managerList.size(); x++) {
      ReporterManager* mgr = (ReporterManager*) managerList.at(x);
      QString sp = mgr->getSystemPrefix();
      bool bam = mgr->allowMultipleAdditions(systemPrefix);
      if (mgr->getSystemPrefix() == (systemPrefix) && mgr->allowMultipleAdditions(systemPrefix)) {
          rangeCheckBox->setEnabled(true);
          addEntryToolTip = mgr->getEntryToolTip();
          log->debug("R add box set");
          break;
      }
  }
 } else if (reporterManager->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()))) {
     rangeCheckBox->setEnabled(true);
     log->debug("R add box enabled2");
     // get tooltip from sensor manager
     addEntryToolTip = reporterManager->getEntryToolTip();
     log->debug("ReporterManager tip");
 }
 // show hwAddressTextField field tooltip in the Add Reporter pane that matches system connection selected from combobox
 hardwareAddressTextField->setToolTip("<html>"
         + tr("For %1 %2 use one of these patterns:").arg(connectionChoice).arg(tr("Sensors"))
         + "<br>" + addEntryToolTip + "</html>");
 hardwareAddressTextField->setStyleSheet("QEditLine { background-color: yellow};"); // reset
}

void ReporterTableAction::handleCreateException(QString sysName) {
    JOptionPane::showMessageDialog(addFrame,
                    tr("Could not create Reporter %1 to add it. Check that number/name is OK.").arg(sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

/*protected*/ QString ReporterTableAction::getClassName() {
    return "jmri.jmrit.beantable.ReporterTableAction";
}

/*public*/ QString  ReporterTableAction::getClassDescription() {
    return tr("Reporter Table");
}
#if 0
/**
 * Private class used in conjunction with CheckedTextField to provide
 * the mechanisms required to validate the text field data upon loss of
 * focus, and colorize the text field in case of validation failure.
 */
///*private*/ class MyVerifier : public InputVerifier //implements java.awt.event.ActionListener
//{
//Q_OBJECT

//    // set default background color for invalid field data
//    QColor mark = ColorUtil::stringToColor("orange");
//public:
    /** {@inheritDoc} */
    //@Override
    /*public*/ bool MyVerifier::shouldYieldFocus(QWidget* input) {
        //if (input.getClass() == CheckedTextField.class)
     if(qobject_cast<CheckedTextField*>(input))
        {

            bool inputOK = verify(input);
            if (inputOK) {
                //input.setBackground(Color.white);
             input->setStyleSheet("QEditLine { background-color: white};");
                return true;
            } else {
                //input.setBackground(mark);
             input->setStyleSheet(tr("QEditLine { background-color: rgb(%1,%2,%3,%4)};").arg(mark.red()).arg(mark.green()).arg(mark.blue()).arg(mark.alpha()));
                ((QLineEdit*) input)->selectAll();
                return false;
            }
        } else {
            return false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool MyVerifier::verify(QWidget* input) {
        //if (input.getClass() == CheckedTextField.class)
     if(qobject_cast<CheckedTextField*>(input))
        {
            return ((CheckedTextField*) input)->isValid();
        } else {
            return false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void MyVerifier::actionPerformed(ActionEvent* e) {
        JTextField* source = (JTextField*) e->getSource();
        shouldYieldFocus(source); //ignore return value
        source->selectAll();
    }
//};

/**
 * Extends JTextField to provide a data validation function.
 *
 * @author Egbert Broerse 2017, based on
 * jmri.jmrit.util.swing.ValidatedTextField by B. Milhaupt
 */
///*public*/ class CheckedTextField : public JTextField
//{
//Q_OBJECT
//    CheckedTextField* fld;
//    bool allow0Length = false; // for Add new bean item, a value that is zero-length is considered invalid.
//    /*private*/ MyVerifier* verifier; // internal mechanism used for verifying field data before focus is lost
//    ReporterTableAction* rta;
//public:
    /**
     * Text entry field with an active key event checker.
     *
     * @param len field length
     */
    /*public*/ CheckedTextField::CheckedTextField(int len, ReporterTableAction* rta) : JTextField("", len){
        //super("", len);
     this->rta = rta;
        fld = this;

        // configure InputVerifier
        verifier = new MyVerifier();
        fld = this;
        fld->setInputVerifier(verifier);
#if 0
        fld.addFocusListener(new FocusListener() {
            @Override
            public void focusGained(FocusEvent e) {
                setEditable(true);
            }

            @Override
            public void focusLost(FocusEvent e) {
                setEditable(true);
            }
        });
#endif
    }

    /**
     * Validate the field information. Does not make any GUI changes.
     * <p>
     * During validation, logging is capped at the Error level to keep the Console clean from repeated validation.
     * This is reset to default level afterwards.
     *
     * @return 'true' if current field entry is valid according to the
     *         system manager; otherwise 'false'
     */
    //@Override
    /*public*/ bool CheckedTextField::isValid() {
        QString value;
        QString prefix = ConnectionNameFromSystemName::getPrefixFromName(rta->connectionChoice); // connectionChoice is set by canAddRange()

        if (fld == nullptr) {
            return false;
        }
        value = text().trimmed();
        if ((value.length() < 1) && (allow0Length == false)) {
            return QValidator::Invalid;
        } else if ((allow0Length == true) && (value.length() == 0)) {
            return QValidator::Acceptable;
        } else {
            bool validFormat = false;
                // try {
                validFormat = static_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->validSystemNameFormat(prefix + "R" + value) == Manager::NameValidity::VALID;
                // } catch (jmri.JmriException e) {
                // use it for the status bar?
                // }
            if (validFormat) {
                rta->addButton->setEnabled(true); // directly update Create button
                return true;
            } else {
                rta->addButton->setEnabled(false); // directly update Create button
                return false;
            }
        }
    }
//};
#endif
RTAValidator::RTAValidator(JTextField *fld, ReporterTableAction *act)
{
 this->fld = fld;
 this->act = act;
 connect(act->prefixBox, SIGNAL(currentTextChanged(QString)), this, SLOT(prefixBoxChanged(QString)));
 prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
 mark = ColorUtil::stringToColor("orange");
}

QValidator::State RTAValidator::validate(QString &s, int &pos) const
{
 QString value = s.trimmed();
 if ((value.length() < 1) && (allow0Length == false)) {
     return QValidator::Invalid;
 }
 else if ((allow0Length == true) && (value.length() == 0))
 {
     return QValidator::Acceptable;
 }
 else {
     bool validFormat = false;
         // try {
         validFormat = static_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->validSystemNameFormat(prefix + "R" + value) == Manager::NameValidity::VALID;
         // } catch (jmri.JmriException e) {
         // use it for the status bar?
         // }
     if (validFormat) {
         fld->setBackground(QColor(Qt::white));
         return QValidator::Acceptable;
     } else {
         fld->setBackground(QColor(mark));
         if(value.length() > -1 && value.toInt()>0)
         {
          return QValidator::Intermediate;
         }
         return QValidator::Invalid;
     }
 }
}

void RTAValidator::prefixBoxChanged(QString txt)
{
 prefix = ConnectionNameFromSystemName::getPrefixFromName(txt);
}
