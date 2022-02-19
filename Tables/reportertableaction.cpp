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
#include "reportertabledatamodel.h"
#include "loggerfactory.h"

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


/*public*/ void ReporterTableAction::setManager(Manager* man) {
 if(qobject_cast<ReporterManager*>(man->self()))
    reporterManager = qobject_cast<ReporterManager*>(man->self());
}

/*public*/ ReporterTableAction::ReporterTableAction(QObject* parent) : AbstractTableAction(tr("TitleReporterTable"), parent)
{
    //this(tr("TitleReporterTable"));
 common();
}

void ReporterTableAction::common()
{

 addFrame = NULL;
 userNameLabel = new JLabel(tr("User Name"));
 systemSelectionCombo = QString(metaObject()->className()) + ".SystemSelected";
 userNameError = QString(this->metaObject()->className()) + ".DuplicateUserName";
 statusBarLabel = new JLabel(tr("Enter a Hardware Address and (optional) User Name.")/*, JLabel.LEADING*/);
}

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Reporters
 */
//@Override
/*protected*/ void ReporterTableAction::createModel()
{
 m = new ReporterTableDataModel(reporterManager);
 //m->setManager(reporterManager);
}

/*protected*/ void ReporterTableAction::setTitle() {
    f->setTitle(tr("TitleReporterTable"));
}

/*protected*/ QString ReporterTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.ReporterTable";
}

/*protected*/ void ReporterTableAction::addPressed(JActionEvent* /*e*/) {
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

        if (hardwareAddressValidator==nullptr){
            hardwareAddressValidator = new SystemNameValidator(hardwareAddressTextField, /*java.util.Objects.requireNonNull*/(prefixBox->getSelectedItem()), true);
        } else {
            hardwareAddressValidator->setManager(prefixBox->getSelectedItem());
        }

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
          JOptionPane::YES_NO_OPTION) == 1)
  {
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
 QString uName = userNameTextField->text();
 for (int x = 0; x < numberOfReporters; x++)
 {
  try {
  curAddress = ((ProxyReporterManager*)reporterManager->self())->getNextValidAddress(curAddress, reporterPrefix, false);
  }
  catch (Exception* ex) {
    displayHwError(curAddress, ex);
    // directly add to statusBarLabel (but never called?)
    statusBarLabel->setText(tr("Unable to convert \"%1\" to a valid Hardware Address.").arg(curAddress));
    statusBarLabel->setForeground(Qt::red);
    return;
  }

  // Compose the proposed system name from parts:
  rName = reporterPrefix + ((ProxyReporterManager*)reporterManager->self())->AbstractProxyManager::typeLetter() + curAddress;
  Reporter* r = nullptr;
  try {
      r = ((ProxyReporterManager*)reporterManager->self())->provideReporter(rName);
  } catch (IllegalArgumentException* ex) {
   // user input no good
   handleCreateException(ex, rName); // displays message dialog to the user
   return; // without creating
  }
  if (!uName.isEmpty()) {
      if ((reporterManager->getByUserName(uName) == nullptr)) {
          ((AbstractNamedBean*)r->self())->setUserName(uName);
      } else {
          pref->showErrorMessage(tr("Error"),
          tr("The specified user name \"%1\" is already in use and therefore will not be set.").arg(uName), userNameError, "", false, true);
      }

      // add first and last names to statusMessage user feedback string
                  // only mention first and last of rangeCheckBox added
      if (x == 0 || x == numberOfReporters - 1) {
          statusMessage = statusMessage + " " + rName + " (" + uName + ")";
      }
      if (x == numberOfReporters - 2) {
          statusMessage = statusMessage + " " + tr("up to") + " ";
      }

      // bump user name
      if (!uName.isEmpty()) {
          uName = nextName(uName);
      }

      // end of for loop creating rangeCheckBox of Reporters
  }
 }
 // provide success feedback to uName
 statusBarLabel->setText(statusMessage);
 statusBarLabel->setForeground(Qt::gray);

 pref->setComboBoxLastSelection(systemSelectionCombo, prefixBox->currentText());
 addFrame->setVisible(false);
 addFrame->dispose();
 addFrame = nullptr;
}

/*private*/ void ReporterTableAction::canAddRange(ActionEvent* /*e*/)
{
 rangeCheckBox->setEnabled(false);
 rangeCheckBox->setChecked(false);
 if (prefixBox->getSelectedIndex() == -1) {
     prefixBox->setSelectedIndex(0);
 }
 connectionChoice = prefixBox->getSelectedItem(); // store in Field for CheckedTextField
 QString systemPrefix = connectionChoice->getSystemPrefix();
 rangeCheckBox->setEnabled(((ReporterManager*) connectionChoice->self())->allowMultipleAdditions(systemPrefix));
 addEntryToolTip = connectionChoice->getEntryToolTip();
 // show hwAddressTextField field tooltip in the Add Reporter pane that matches system connection selected from combobox
 hardwareAddressTextField->setToolTip(
         tr("<html>%1 %2 use one of these patterns:<br>%3</html>").arg(
                 connectionChoice->getMemo()->getUserName(),
                 tr("Reporters"),
                 addEntryToolTip));
 //hardwareAddressValidator->setToolTip(hardwareAddressTextField->toolTip());
 hardwareAddressValidator->verify(hardwareAddressTextField);
}

void ReporterTableAction::handleCreateException(Exception* ex, QString sysName) {
 statusBarLabel->setText(ex->getLocalizedMessage());
 statusBarLabel->setForeground(Qt::red);
// QString err = Bundle.getMessage("ErrorBeanCreateFailed",
//     InstanceManager.getDefault(ReporterManager.class).getBeanTypeHandled(),sysName);
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
 prefix = ConnectionNameFromSystemName::getPrefixFromName(act->prefixBox->currentText());
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
         validFormat = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->validSystemNameFormat(prefix + "R" + value) == Manager::NameValidity::VALID;
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

/*private*/ /*final*/ /*static*/ Logger* ReporterTableAction::log = LoggerFactory::getLogger("ReporterTableAction");
