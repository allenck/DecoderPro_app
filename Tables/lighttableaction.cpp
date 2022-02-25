#include "lighttableaction.h"
#include "propertychangeevent.h"
#include "jtextfield.h"
#include "lightcontrol.h"
#include "light.h"
#include "userpreferencesmanager.h"
#include "connectionnamefromsystemname.h"
#include <QComboBox>
#include <QLabel>
#include <jtextfield.h>
#include <qcheckbox.h>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "flowlayout.h"
#include <QGroupBox>
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "pushbuttondelegate.h"
#include "abstractlight.h"
#include "abstractlightmanager.h"
#include "colorutil.h"
#include "joptionpane.h"
#include "proxylightmanager.h"
#include "guilafpreferencesmanager.h"
#include "imageio.h"
#include "bufferedimage.h"
#include "loggerfactory.h"
#include "file.h"
#include "fileutil.h"
#include "lighttabledatamodel.h"
#include "lightintensitypane.h"
#include "borderfactory.h"
#include "namedbean.h"
#include "defaultlightcontrol.h"
#include "borderfactory.h"
#include "abstractproxymanager.h"
/**
 * Swing action to create and register a LightTable GUI.
 * <P>
 * Based on SignalHeadTableAction.java
 *
 * @author	Dave Duchamp Copyright (C) 2004
 */
///*public*/ class LightTableAction extends AbstractTableAction {

/*public*/ /*static*/ QString LightTableAction::lightControlTitle =tr("Light Control");


/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param s title of the action
 */
/*public*/ LightTableAction::LightTableAction(QString s, QObject* parent) : AbstractTableAction(s, parent) {
    //super(s);
    common();
    // disable ourself if there is no primary Light manager available
    if (lightManager == nullptr) {
        setEnabled(false);
    }
}

/*public*/ LightTableAction::LightTableAction(QObject* parent) : AbstractTableAction(tr("Light Table"), parent) {
    //this(tr("TitleLightTable"));
    common();
}

void LightTableAction::common()
{
 setObjectName("LightTableAction");
 oneDigit = new DecimalFormat("0");
 oneDotTwoDigit = new DecimalFormat("0.00");
 addFrame = nullptr;
 curLight = nullptr;
 lightCreatedOrUpdated = false;
 noWarn = false;
 inEditMode = false;
 lightControlChanged = false;
 log = new Logger("LightTableAction");
 gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";


 // items of add frame
 systemSelectionCombo = QString(this->metaObject()->className()) + ".SystemSelected";
 panel1a = nullptr;
 varPanel = nullptr;
 systemNameLabel = new QLabel(tr("System Name") + " ");
 fixedSystemName = new QLabel("xxxxxxxxxxx");
 userName = new JTextField(10);
 userNameLabel = new QLabel(tr("User Name") + " ");
 lightControlTableModel = nullptr;
 create = nullptr;
 update = nullptr;
 cancel = nullptr;
 addControl = nullptr;

 controlList = QList<LightControl*>();
 sensorControl = tr("By Sensor");
 fastClockControl = tr("By Fast Clock");
 turnoutStatusControl = tr("By Turnout Status");
 timedOnControl = tr("By Timed ON");
 twoSensorControl = tr("By Two Sensors");
 noControl = tr("None");

 status1 = new JLabel(tr("Select or enter data, then press Create for a new Light, or press Cancel."));
 status2 = new JLabel("");

 // parts for supporting variable intensity, transition
 labelMinIntensity = new QLabel(tr("Minimum Intensity") + "  ");
 fieldMinIntensity = new JTextField(3);
 labelMinIntensityTail = new QLabel(" %   ");
 labelMaxIntensity = new QLabel(tr("Maximum Intensity") + "  ");
 fieldMaxIntensity = new JTextField(3);
 labelMaxIntensityTail = new QLabel(" %   ");
 labelTransitionTime = new QLabel(tr("Transition Time") + "  ");
 fieldTransitionTime = new JTextField(5);

 // items for add/edit Light Control window
 addControlFrame = nullptr;
 typeBox = nullptr;
 typeBoxLabel = new QLabel(tr("Control Type"));
 defaultControlIndex = 0;
 inEditControlMode = false;
 lc = nullptr;
 field1a = new JTextField(10);  // Sensor
 field1a2 = new JTextField(10);  // Sensor 2
 field1b = new JTextField(8);  // Fast Clock
 field1c = new JTextField(10);  // Turnout
 field1d = new JTextField(10);  // Timed ON
 f1Label = new QLabel(tr("Sensor"));
 field2a = new JTextField(8);  // Fast Clock
 field2b = new JTextField(8); // Timed ON
 f2Label = new QLabel(tr("Sense for ON"));
}

/*public*/ void LightTableAction::setManager(Manager* man) {
    if(qobject_cast<LightManager*>(man->mself()))
     lightManager = qobject_cast<LightManager*>(man->mself());
}

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Lights
 */
/*protected*/ void LightTableAction::createModel()
{
 // load graphic state column display preference
 //_graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();

 m = new LightTableDataModel(lightManager);
}

/*protected*/ void LightTableAction::setTitle() {
    f->setTitle(tr("Light Table"));
}

/*protected*/ QString LightTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.LightTable";
}


/*protected*/ void LightTableAction::addPressed(ActionEvent* /*e*/)
{
    if (inEditMode) {
        // cancel Edit and reactivate the edited light
        cancelPressed(nullptr);
    }
    if (addFrame == nullptr) {
        addFrame = new JmriJFrameX(tr("Add Light"), false, true);
        addFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
        addFrame->addHelpMenu("package.jmri.jmrit.beantable.LightAddEdit", true);
        addFrame->setLocation(100, 30);
        QWidget* contentPane = addFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout); //BoxLayout(contentPane, BoxLayout.Y_AXIS));
        QWidget* panel1 = new QWidget();
        FlowLayout* panel1Layout;
        panel1->setLayout(panel1Layout = new FlowLayout());
        configureManagerComboBox(prefixBox, lightManager, "LightManager");
        connectionChoice = prefixBox->getSelectedItem();
        hardwareAddressTextField->setValidator(validator = new LTAValidator(hardwareAddressTextField, this));
        panel1Layout->addWidget(systemLabel);
        panel1Layout->addWidget(prefixBox);
        panel1Layout->addWidget(new QLabel("   "));
        panel1Layout->addWidget(addRangeBox);
        addRangeBox->setToolTip(tr("LightAddRangeHint"));
//        addRangeBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addRangeChanged();
//            }
//        });
        connect(addRangeBox, SIGNAL(clicked()), this, SLOT(addRangeChanged()));
        panel1Layout->addWidget(systemNameLabel);
        systemNameLabel->setVisible(false);
        panel1Layout->addWidget(fixedSystemName);
        fixedSystemName->setVisible(false);
        prefixBox->setToolTip(tr("Select a system connection for the new Light"));
//        prefixBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(prefixBox, &ManagerComboBox::currentIndexChanged,[=]{
                prefixChanged();
//            }
        });
        contentPane->layout()->addWidget(panel1);
        panel1a = new QWidget();
        FlowLayout* panel1aLayout;
        panel1a->setLayout(panel1aLayout = new FlowLayout());
        panel1aLayout->addWidget(new QLabel(tr("Hardware Address")));
        panel1aLayout->addWidget(hardwareAddressTextField);
        hardwareAddressTextField->setValidator(validator = new LTAValidator(hardwareAddressTextField, this));
        hardwareAddressTextField->setText("");
        hardwareAddressTextField->setToolTip(tr("Enter an integer as the hardware address for the (first) new Light, e.g. '13'"));
        hardwareAddressTextField->setName("hwAddressTextField"); // for GUI test NOI18N
        hardwareAddressTextField->setBackground(QColor(Qt::yellow)); // reset after possible error notificationpanel1aLayout->addWidget(labelNumToAdd);

        if (hardwareAddressValidator==nullptr){
            hardwareAddressValidator = new SystemNameValidator(hardwareAddressTextField, /*Objects.requireNonNull*/(prefixBox->getSelectedItem()), true);
        } else {
            hardwareAddressValidator->setManager(prefixBox->getSelectedItem());
        }

        hardwareAddressTextField->setInputVerifier(hardwareAddressValidator);

        //prefixBox.addActionListener((evt) -> hardwareAddressValidator.setManager(prefixBox.getSelectedItem()));
        connect(prefixBox, &ManagerComboBox::currentIndexChanged, [=]{hardwareAddressValidator->setManager(prefixBox->getSelectedItem());});
#if 0
        hardwareAddressValidator->SwingPropertyChangeSupport::addPropertyChangeListener("validation", /*(evt) ->*/&SystemNameValidator::prop
        { // NOI18N
            Validation* validation = hardwareAddressValidator->getValidation();
            Validation::Type type = validation.getType();
            create.setEnabled(type != Validation.Type.WARNING && type != Validation.Type.DANGER);
            QString message = validation->getMessage();
            if (message == "") {
                status1->setText("");
            } else {
                message = message.trimmed();
                if (message.startsWith("<html>") && message.contains("<br>")) {
                    message = message.mid(0, message.indexOf("<br>"));
                    if (!message.endsWith("</html>")) {
                        message = message + "</html>";
                    }
                }
                status1->setText(message);
            }
        });
#endif
        hardwareAddressValidator->addPropertyChangeListener("validation", new HAVPropertyChangeListener(this));
        panel1aLayout->addWidget(numberToAdd);
        numberToAdd->setToolTip(tr("Set the number of sequential address Lights to add (Max. 50)"));
        contentPane->layout()->addWidget(panel1a);
        QWidget* panel2 = new QWidget();
        FlowLayout* panel2Layout;
        panel2->setLayout(panel2Layout = new FlowLayout());
        panel2Layout->addWidget(userNameLabel);
        panel2Layout->addWidget(userName);
        userName->setToolTip(tr("LightUserNameHint"));
        contentPane->layout()->addWidget(panel2);
        lightIntensityPanel = new LightIntensityPane(false);
        Border* varPanelTitled = BorderFactory::createTitledBorder(BorderFactory::createEtchedBorder(),
            tr("Variable Intensity"));
        lightIntensityPanel->setBorder(varPanelTitled);
        contentPane->layout()->addWidget(lightIntensityPanel);
        // light control table
        lightControlPanel = new LightControlPane();
        Border* panel3Titled = BorderFactory::createTitledBorder(BorderFactory::createEtchedBorder(),
            tr("Light Controllers"));
        lightControlPanel->setBorder(panel3Titled);
        contentPane->layout()->addWidget(lightControlPanel);
        // message items
        QGroupBox* panel4 = new QGroupBox();
        QVBoxLayout* panel4Layout = new QVBoxLayout(panel4);
        //panel4->setLayout(new BoxLayout(panel4, BoxLayout.Y_AXIS));
        QWidget* panel41 = new QWidget();
        FlowLayout* panel41Layout;
        panel41->setLayout(panel41Layout =new FlowLayout());
        panel41Layout->addWidget(status1);
        status1->setText(tr("Select or enter data, then press Create for a new Light, or press Cancel."));
        QWidget* panel42 = new QWidget();
        FlowLayout* panel42Layout;
        panel42->setLayout(panel42Layout = new FlowLayout());
        panel42Layout->addWidget(status2);
        status2->setText("");
        status2->setVisible(false);
        panel4Layout->addWidget(panel41);
        panel4Layout->addWidget(panel42);
//        Border panel4Border = BorderFactory.createEtchedBorder();
//        panel4->setBorder(panel4Border);
        panel4->setStyleSheet(gbStyleSheet);
        contentPane->layout()->addWidget(panel4);
        // buttons at bottom of window
        QWidget* panel5 = new QWidget();
        FlowLayout* panel5Layout;
        panel5->setLayout(panel5Layout=new FlowLayout); //(FlowLayout.TRAILING));
        panel5Layout->addWidget(cancel = new QPushButton(tr("Cancel")));
//        cancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelPressed(e);
//            }
//        });
        connect(cancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));
        cancel->setToolTip(tr("Press Cancel to leave unchanged"));
        panel5Layout->addWidget(create = new QPushButton(tr("Create")));
//        create.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                createPressed(e);
//            }
//        });
        connect(create, SIGNAL(clicked()), this, SLOT(createPressed()));
        create->setToolTip(tr("Press Create to create a new Light"));
        panel5Layout->addWidget(update = new QPushButton(tr("Update")));
//        update.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updatePressed(e);
//            }
//        });
        connect(update, SIGNAL(clicked()), this, SLOT(updatePressed()));
        update->setToolTip(tr("Press Update to change the Light"));
        cancel->setVisible(true);
        create->setVisible(true);
        update->setVisible(false);
        contentPane->layout()->addWidget(panel5);
    }
    prefixChanged();

//    addFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            cancelPressed(NULL);
//        }
//    });
    addFrame->addWindowListener(new LTAWindowListener(this));
    addFrame->adjustSize();
    addFrame->setVisible(true);
}

/*public*/ void LightTableAction::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
    QString property = propertyChangeEvent->getPropertyName();
    if ("background" == (property)) {
        if ( propertyChangeEvent->getNewValue().value<QColor>() == QColor(Qt::white)) { // valid entry
            create->setEnabled(true);
        } else { // invalid
            create->setEnabled(false);
        }
    }
}

LTAWindowListener::LTAWindowListener(LightTableAction *lta)
{
 this->lta = lta;
}

void LTAWindowListener::windowClosing(QCloseEvent *e)
{
 lta->cancelPressed();
}

/*protected*/ void LightTableAction::prefixChanged() {
 if (prefixBox->getSelectedItem() != nullptr) {
     lightIntensityPanel->setVisible(supportsVariableLights());
     // behaves like the AddNewHardwareDevice pane (dim if not available, do not hide)
     addRangeBox->setEnabled(canAddRange());
     addRangeBox->setSelected(false);
     numberToAdd->setValue(1);
     numberToAdd->setEnabled(false);
     labelNumToAdd->setEnabled(false);
     // show tooltip for selected system connection
     connectionChoice = prefixBox->getSelectedItem(); // store in Field for CheckedTextField
     // Update tooltip in the Add Light pane to match system connection selected from combobox.
     log->debug(tr("Connection choice = [%1]").arg(connectionChoice->getBeanTypeHandled()));
     // get tooltip from ProxyLightManager
     QString systemPrefix = connectionChoice->getSystemPrefix();
     addEntryToolTip = connectionChoice->getEntryToolTip();
     addRangeBox->setEnabled(((AbstractLightManager*) connectionChoice->mself())->allowMultipleAdditions(systemPrefix));
     log->debug(tr("DefaultLightManager tip: %1").arg(addEntryToolTip));
     // show Hardware address field tooltip in the Add Light pane to match system connection selected from combobox
     if (addEntryToolTip != "") {
         hardwareAddressTextField->setToolTip(
                 tr("<html>%1 %2 use one of these patterns:<br>%3</html>").arg(
                         connectionChoice->getMemo()->getUserName(),
                         tr("Lights"),
                         addEntryToolTip));
//         hardwareAddressValidator->setToolTip(hardwareAddressTextField->toolTip());
         hardwareAddressValidator->verify(hardwareAddressTextField);
     }
     create->setEnabled(true); // too severe to start as disabled (false) until we fully support validation
     addFrame->pack();
     addFrame->setVisible(true);
 }
}

/*protected*/ void LightTableAction::addRangeChanged() {
    if (addRangeBox->isChecked()) {
        numberToAdd->setEnabled(true);
        labelNumToAdd->setEnabled(true);
    } else {
        numberToAdd->setEnabled(false);
        labelNumToAdd->setEnabled(false);
    }
}

/*private*/ bool LightTableAction::canAddRange() {
    QString testSysName = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()) + "L11";
    return ((ProxyLightManager*)InstanceManager::lightManagerInstance())->allowMultipleAdditions(testSysName);
}

/**
 * Set up panel for Variable Options
 */
void LightTableAction::setupVariableDisplay(bool showIntensity, bool showTransition) {
    labelMinIntensity->setVisible(showIntensity);
    fieldMinIntensity->setVisible(showIntensity);
    labelMinIntensityTail->setVisible(showIntensity);
    labelMaxIntensity->setVisible(showIntensity);
    fieldMaxIntensity->setVisible(showIntensity);
    labelMaxIntensityTail->setVisible(showIntensity);
    labelTransitionTime->setVisible(showTransition);
    fieldTransitionTime->setVisible(showTransition);
    if (showIntensity || showTransition) {
        varPanel->setVisible(true);
    } else {
        varPanel->setVisible(false);
    }
}

/**
 * Returns true if system can support variable lights
 */
bool LightTableAction::supportsVariableLights() {
    QString testSysName = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()) + "L11";
    return ((ProxyLightManager*)InstanceManager::lightManagerInstance())->supportsVariableLights(testSysName);
}

/**
 * Responds to the Create button
 */
void LightTableAction::createPressed(ActionEvent* /*e*/) {
    //ConnectionNameFromSystemName::getPrefixFromName((String) prefixBox.getSelectedItem())
    QString lightPrefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()) + "L";
    QString turnoutPrefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText()) + "T";
    QString curAddress = hardwareAddressTextField->text();
    if (curAddress.length() < 1) {
        log->warn("Hardware Address was not entered");
        status1->setText(tr("Error: No Hardware Address was entered."));
        status2->setVisible(false);
        hardwareAddressTextField->setBackground(Qt::red);
        addFrame->adjustSize();
        addFrame->setVisible(true);
        return;
    }
    QString suName = lightPrefix + curAddress;
    QString uName = userName->text();
    if (uName==("")) {
        uName = "";   // a blank field means no user name
    }
    // Does System Name have a valid format
    if (qobject_cast<AbstractProxyManager*>(InstanceManager::getDefault("LightManager"))->validSystemNameFormat(suName)!= Manager::NameValidity::VALID) {
        // Invalid System Name format
        log->warn("Invalid Light system name format entered: " + suName);
        status1->setText(tr("Error: System Name has an invalid format."));
        status2->setText(tr("Please revise System Name and try again."));
        status2->setVisible(true);
        hardwareAddressTextField->setBackground(Qt::red);
        addFrame->adjustSize();
        addFrame->setVisible(true);
        return;
    }
    // Format is valid, normalize it
    ProxyLightManager* mgr= static_cast<ProxyLightManager*> (InstanceManager::getDefault("LightManager"));
    QString sName = mgr->AbstractProxyManager::normalizeSystemName(suName);
    // check if a Light with this name already exists
    Light* g = (Light*)mgr->AbstractProxyManager::getBySystemName(sName)->self();
    if (g != NULL) {
        // Light already exists
        status1->setText(tr("Error: an element with this System Name already exists."));
        status1->setForeground(Qt::red);
        status2->setText(tr("Press Edit to see User Name and Control information."));
        status2->setVisible(true);
        addFrame->adjustSize();
        addFrame->setVisible(true);
        return;
    }
    // check if Light exists under an alternate name if an alternate name exists
    QString altName = mgr->convertSystemNameToAlternate(suName);
    if (altName != ("")) {
        g = (Light*)InstanceManager::lightManagerInstance()->getBySystemName(altName)->self();
        if (g != NULL) {
            // Light already exists
            status1->setText(tr("Error: Light") + " '" + altName + "' "
                    + tr("exists and is the same address."));
            status1->setForeground(Qt::red);
            status2->setVisible(false);
            hardwareAddressTextField->setBackground(Qt::red);
            addFrame->adjustSize();
            addFrame->setVisible(true);
            return;
        }
    }
    // check if a Light with the same user name exists
    if (uName != NULL && uName != ("")) {
        g = (Light*)mgr->getByUserName(uName)->self();
        if (g != NULL) {
            // Light with this user name already exists
            status1->setText(tr("Error: an element with this User Name already exists."));
            status1->setForeground(Qt::red);
            status2->setText(tr("Please revise User Name and try again."));
            status2->setVisible(true);
            addFrame->adjustSize();
            addFrame->setVisible(true);
            return;
        }
    }
    // check if System Name corresponds to configured hardware
    if (!mgr->validSystemNameConfig(suName)) {
        // System Name not in configured hardware
        status1->setText(tr("Error: System Name doesn't refer to configured hardware."));
        status2->setText(tr("Please revise System Name and try again."));
        status2->setVisible(true);
        addFrame->adjustSize();
        addFrame->setVisible(true);
        return;
    }
    // check if requested Light uses the same address as a Turnout
    QString testSN = turnoutPrefix + curAddress;
    Turnout* testT = (Turnout*)((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
            AbstractProxyManager::getBySystemName(testSN)->self();
    if (testT != nullptr) {
        // Address is already used as a Turnout
         log->warn("Requested Light " + sName + " uses same address as Turnout " + testT->getDisplayName());
        if (!noWarn) {
            int selectedValue = JOptionPane::showOptionDialog(addFrame,
                    tr("Warning - Requested Light") + " " + sName + " " + tr("uses same address as Turnout") + " "
                    + testSN + ".\n   " + tr("LightWarn7"), tr("WarningTitle"),
                    JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                    QVariantList{tr("Yes"), tr("No"),
                        tr("Yes - Stop Warnings")}, tr("No"));
            if (selectedValue == 1) {
                return;   // return without creating if "No" response
            }
            if(selectedValue == 2){
                // Suppress future warnings, and continue
                noWarn = true;
            }
        }
        // Light with this system name already exists as a turnout
        status2->setText(tr("Warning: New Light refers to address already used by") + " " + testSN + ".");
        status2->setVisible(true);
    }
    // Check multiple Light creation request, if supported
    int numberOfLights = 1;
    int startingAddress = 0;
    if (mgr->allowMultipleAdditions(sName)
            && addRangeBox->isChecked() && (numberToAdd->text().length() > 0)) {
        // get number requested
        bool bok;
            numberOfLights = (numberToAdd->text().toInt(&bok));
        if(!bok)
        {
            status1->setText(tr("Error: Bad 'Number to Add' entry."));
            status2->setVisible(false);
            addFrame->adjustSize();
            addFrame->setVisible(true);
             log->error("Unable to convert " + numberToAdd->text() + " to a number - Number to add");
            return;
        }
        // convert numerical hardware address

            startingAddress = hardwareAddressTextField->text().toInt(&bok);
        if(!bok) {
            status1->setText(tr("Error: Entered hardware address does not convert to a number."));
            status2->setVisible(false);
            addFrame->adjustSize();
            addFrame->setVisible(true);
             log->error("Unable to convert " + hardwareAddressTextField->text() + " to a number.");
            return;
        }
        // check that requested address range is available
        int add = startingAddress;
        QString testAdd = "";
        for (int i = 0; i < numberOfLights; i++) {
            testAdd = lightPrefix + add;
            if (mgr->AbstractProxyManager::getBySystemName(testAdd) != NULL) {
                status1->setText(tr("Error: Requested range of hardware addresses is not free."));
                status1->setForeground(Qt::red);
                status2->setVisible(true);
                addFrame->adjustSize();
                addFrame->setVisible(true);
                 log->error("Range not available - " + testAdd + " already exists.");
                return;
            }
            testAdd = turnoutPrefix + add;
            if (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->AbstractProxyManager::getBySystemName(testAdd) != NULL) {
                status1->setText(tr("Error: Requested range of hardware addresses is not free."));
                status1->setForeground(Qt::red);
                status2->setVisible(true);
                addFrame->adjustSize();
                addFrame->setVisible(true);
                 log->error("Range not available - " + testAdd + " already exists.");
                return;
            }
            add++;
        }
    }

    // Create a single new Light, or the first Light of a range
    try {
        g = mgr->newLight(suName, uName);
    } catch (IllegalArgumentException* ex) {
        // user input no good
        handleCreateException(ex, sName);
        return; // without creating
    }
    lightControlPanel->setLightFromControlTable(g);
    if (qobject_cast<VariableLight*>(g->self())) {
         lightIntensityPanel->setLightFromPane((VariableLight*)g->self());
     }
     g->activateLight();
     lightCreatedOrUpdated = true;

     status2->setText("");
     status2->setVisible(false);

    // provide feedback to user
    QString feedback = tr("New Light(s) added:") + " " + ((AbstractNamedBean*)g->self())->getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME);
    // create additional lights if requested
    if (numberOfLights > 1) {
        QString sxName = "";
        QString uxName = "";
        if (uName == NULL) {
            uxName = "";
        }
        for (int i = 1; i < numberOfLights; i++) {
            sxName = lightPrefix + (startingAddress + i);
            if (uName != NULL) {
                uxName = uName + "+" + i;
            }
            try {
                g = InstanceManager::lightManagerInstance()->newLight(sxName, uxName);
            } catch (IllegalArgumentException* ex) {
                // user input no good
// TODO:                handleCreateException(ex, sName);
                return; // without creating any more Lights
            }
        }
        feedback = feedback + " - " + sxName + ", " + uxName;
    }
    status1->setText(feedback);
    status1->setForeground(Qt::gray);
    status2->setText("");
    status2->setVisible(false);
    addFrame->adjustSize();
    addFrame->setVisible(true);
}
#if 0
/**
 * Responds to the Edit button in the light table, window has already been
 * created
 */
void LightTableAction::editPressed() {
    // check if a Light with this name already exists
    QString suName = fixedSystemName->text();
    QString sName = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->normalizeSystemName(suName);
    if (sName == ("")) {
        // Entered system name has invalid format
        status1->setText(tr("Error: System Name has an invalid format."));
        status2->setText(tr("Please revise System Name and try again."));
        status2->setVisible(true);
        addFrame->adjustSize();
        addFrame->setVisible(true);
        return;
    }
    Light* g = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(sName);
    if (g == NULL) {
        // check if Light exists under an alternate name if an alternate name exists
        QString altName = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->convertSystemNameToAlternate(sName);
        if (altName != ("")) {
            g = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(altName);
            if (g != NULL) {
                sName = altName;
            }
        }
        if (g == NULL) {
            // Light does not exist, so cannot be edited
            status1->setText(tr("Error: Light with entered System Name doesn't exist."));
            status2->setText(tr("Please revise System Name and try again."));
            status2->setVisible(true);
            addFrame->adjustSize();
            addFrame->setVisible(true);
            return;
        }
    }
    // Light was found, make its system name not changeable
    curLight = g;
    fixedSystemName->setText(sName);
    fixedSystemName->setVisible(true);
    prefixBox->setVisible(false);
    systemNameLabel->setVisible(true);
    systemLabel->setVisible(false);
    panel1a->setVisible(false);
    addRangeBox->setVisible(false);
    // deactivate this light
    curLight->deactivateLight();
    inEditMode = true;
    // get information for this Light
    userName->setText(g->getUserName());
    clearLightControls();
    controlList = curLight->getLightControlList();
    // variable intensity
    if (g->isIntensityVariable()) {
        fieldMinIntensity->setText(oneDigit->format(g->getMinIntensity() * 100) + "  ");
        fieldMaxIntensity->setText(oneDigit->format(g->getMaxIntensity() * 100) + "  ");
        if (g->isTransitionAvailable()) {
            fieldTransitionTime->setText(oneDotTwoDigit->format(g->getTransitionTime()) + "    ");
        }
    }
    setupVariableDisplay(g->isIntensityVariable(), g->isTransitionAvailable());

    update->setVisible(true);
    create->setVisible(false);
    status1->setText(tr("Change data and press Update, or press Cancel."));
    status2->setText("");
    status2->setVisible(false);
    addFrame->adjustSize();
    addFrame->setVisible(true);
    lightControlTableModel->fireTableDataChanged();
}
#endif
void LightTableAction::handleCreateException(Exception ex, QString sysName) {
    JOptionPane::showMessageDialog(addFrame,
                   tr("Could not create light \"%1\" to add it.").arg(
                    sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

/**
 * Responds to the Update button
 */
void LightTableAction::updatePressed(ActionEvent* /*e*/) {
    Light* g = curLight;
    // Check if the User Name has been changed
    QString uName = userName->text();
    if (uName == ("")) {
        uName = "";   // a blank field means no user name
    }
    QString prevUName = ((AbstractNamedBean*)g->self())->getUserName();
    if ((uName != NULL) && !(uName == (prevUName))) {
        // user name has changed - check if already in use
        Light* p = (Light*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getByUserName(uName)->self();
        if (p != NULL) {
            // Light with this user name already exists
            status1->setText(tr("Error: an element with this User Name already exists."));
            status2->setText(tr("Please revise User Name and try again."));
            status2->setVisible(true);
            return;
        }
        // user name is unique, change it
        ((AbstractNamedBean*)g->self())->setUserName(uName);
    } else if ((uName == NULL) && (prevUName != NULL)) {
        // user name has been cleared
        ((AbstractNamedBean*)g->self())->setUserName(NULL);
    }
    setLightControlInformation(g);
    // Variable intensity, transitions
    if (g->isIntensityVariable()) {
        g->setMinIntensity(fieldMinIntensity->text().toDouble() / 100);
        g->setMaxIntensity(fieldMaxIntensity->text().toDouble() / 100);
        if (g->isTransitionAvailable()) {
            g->setTransitionTime(fieldTransitionTime->text().toDouble());
        }
    }
    g->activateLight();
    lightCreatedOrUpdated = true;
    cancelPressed(NULL);
}

/*private*/ void LightTableAction::setLightControlInformation(Light* g) {
    if (inEditMode && !lightControlChanged) {
        return;
    }
    g->clearLightControls();
    for (int i = 0; i < controlList.size(); i++) {
        LightControl* lc = controlList.at(i);
        lc->setParentLight((AbstractLight*)g->self());
        g->addLightControl(lc);
    }
}

/**
 * Responds to the Cancel button
 */
void LightTableAction::cancelPressed(ActionEvent* /*e*/) {
 if (addFrame != nullptr) {
     addFrame->setVisible(false); // hide first for cleaner display
 }

 // remind to save, if Light was created or edited
 if (lightCreatedOrUpdated) {
     ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage(
             tr("Reminder"), tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(
                     tr("Lights")),
                     getClassName(),
                     "remindSaveLight"); // NOI18N
 }
 lightCreatedOrUpdated = false;
 // finally, get rid of the add/edit Frame
 if (addFrame != nullptr) {

     lightControlPanel->dispose(); // closes any popup windows

     removePrefixBoxListener(prefixBox);
     addFrame->dispose();
     addFrame = nullptr;
     //create->removePropertyChangeListener(colorChangeListener);

 }
}

/**
 * Reacts to a control type change
 */
void LightTableAction::controlTypeChanged() {
    setUpControlType( typeBox->currentText());
}

/**
 * Sets the Control Information according to control type
 */
void LightTableAction::setUpControlType(QString ctype) {
    if (sensorControl == (ctype)) {
        // set up window for sensor control
        f1Label->setText(tr("Sensor"));
        field1a->setToolTip(tr("Enter name of Sensor controlling this Light"));
        f2Label->setText(tr("Sense for ON"));
        stateBox->clear();
        stateBox->addItem(tr("Active"));
        sensorActiveIndex = 0;
        stateBox->addItem(tr("Inactive"));
        sensorInactiveIndex = 1;
        stateBox->setToolTip(tr("Select Sensor state corresponding to Light ON"));
        f2Label->setVisible(true);
        field1a->setVisible(true);
        field1a2->setVisible(false);
        field1a->setToolTip(tr("Enter name of Sensor controlling this Light"));
        field1b->setVisible(false);
        field1c->setVisible(false);
        field1d->setVisible(false);
        field2a->setVisible(false);
        field2b->setVisible(false);
        stateBox->setVisible(true);
        defaultControlIndex = sensorControlIndex;
    } else if (fastClockControl == (ctype)) {
        // set up window for fast clock control
        f1Label->setText(tr("Time On (hh:mm)"));
        field1b->setToolTip(tr("Enter time as hh:mm for a 24-hour clock"));
        f2Label->setText(tr("Time Off (hh:mm)"));
        field2a->setToolTip(tr("Enter time as hh:mm for a 24-hour clock"));
        f2Label->setVisible(true);
        field1a->setVisible(false);
        field1a2->setVisible(false);
        field1b->setVisible(true);
        field1c->setVisible(false);
        field1d->setVisible(false);
        field2a->setVisible(true);
        field2b->setVisible(false);
        stateBox->setVisible(false);
        defaultControlIndex = fastClockControlIndex;
    } else if (turnoutStatusControl == (ctype)) {
        // set up window for turnout status control
        f1Label->setText(tr("Turnout Name"));
        field1c->setToolTip(tr("Enter name of Turnout whose status is shown in new Light"));
        f2Label->setText(tr("Status for ON"));
        stateBox->clear();
        stateBox->addItem(InstanceManager::turnoutManagerInstance()->getClosedText());
        turnoutClosedIndex = 0;
        stateBox->addItem(InstanceManager::turnoutManagerInstance()->getThrownText());
        turnoutThrownIndex = 1;
        stateBox->setToolTip(tr("Select Turnout state corresponding to Light ON"));
        f2Label->setVisible(true);
        field1a->setVisible(false);
        field1a2->setVisible(false);
        field1b->setVisible(false);
        field1c->setVisible(true);
        field1d->setVisible(false);
        field2a->setVisible(false);
        field2b->setVisible(false);
        stateBox->setVisible(true);
        defaultControlIndex = turnoutStatusControlIndex;
    } else if (timedOnControl == (ctype)) {
        // set up window for sensor control
        f1Label->setText(tr("Trigger Sensor Name"));
        field1d->setToolTip(tr("Enter name of Sensor triggering Timed ON"));
        f2Label->setText(tr("Duration ON (msec)"));
        field2b->setToolTip(tr("Enter duration of Timed ON in milliseconds"));
        f2Label->setVisible(true);
        field1a->setVisible(false);
        field1a2->setVisible(false);
        field1b->setVisible(false);
        field1c->setVisible(false);
        field1d->setVisible(true);
        field2a->setVisible(false);
        field2b->setVisible(true);
        stateBox->setVisible(false);
        defaultControlIndex = timedOnControlIndex;
    } else if (twoSensorControl == (ctype)) {
        // set up window for two sensor control
        f1Label->setText(tr("Sensor Name"));
        field1a->setToolTip(tr("Enter name of Sensor controlling this Light"));
        f2Label->setText(tr("Sense for ON"));
        stateBox->clear();
        stateBox->addItem(tr("Active"));
        sensorActiveIndex = 0;
        stateBox->addItem(tr("Inactive"));
        sensorInactiveIndex = 1;
        stateBox->setToolTip(tr("Select Sensor state corresponding to Light ON"));
        f2Label->setVisible(true);
        field1a->setVisible(true);
        field1a2->setVisible(true);
        field1a->setToolTip(tr("Enter name of both Sensors controlling this Light"));
        field1b->setVisible(false);
        field1c->setVisible(false);
        field1d->setVisible(false);
        field2a->setVisible(false);
        field2b->setVisible(false);
        stateBox->setVisible(true);
        defaultControlIndex = twoSensorControlIndex;
    } else if (noControl == (ctype)) {
        // set up window for no control
        f1Label->setText(tr("No Automated Control Selected"));
        f2Label->setVisible(false);
        field1a->setVisible(false);
        field1a2->setVisible(false);
        field1b->setVisible(false);
        field1c->setVisible(false);
        field1d->setVisible(false);
        field2a->setVisible(false);
        field2b->setVisible(false);
        stateBox->setVisible(false);
        defaultControlIndex = noControlIndex;
    } else {
         log->error("Unexpected control type in controlTypeChanged: " + ctype);
    }
    addControlFrame->adjustSize();
    addControlFrame->setVisible(true);
}
#if 0
/*protected*/ void LightTableAction::createControlPressed(ActionEvent* e) {
    if (typeBox->currentText() == (noControl)) {
        return;
    }
    lc = new LightControl();
    if (setControlInformation(lc)) {
        controlList.append(lc);
        lightControlChanged = true;
        lightControlTableModel->fireTableDataChanged();
        cancelControlPressed(e);
    } else {
        addFrame->adjustSize();
        addControlFrame->setVisible(true);
    }
}
#endif
#if 0
/*protected*/ void LightTableAction::updateControlPressed(ActionEvent* e) {
    if (setControlInformation(lc)) {
        lightControlChanged = true;
        lightControlTableModel->fireTableDataChanged();
        cancelControlPressed(e);
    } else {
        addFrame->adjustSize();
        addControlFrame->setVisible(true);
    }
}

/*protected*/ void LightTableAction::cancelControlPressed(ActionEvent* /*e*/) {
    if (inEditControlMode) {
        inEditControlMode = false;
    }
    if (inEditMode) {
        status1->setText(tr("Change data and press Update, or press Cancel."));
    } else {
        status1->setText(tr("Select or enter data, then press Create for a new Light, or press Cancel."));
    }
    status2->setText("");
    status2->setVisible(false);
    addFrame->adjustSize();
    addFrame->setVisible(true);
    addControlFrame->setVisible(false);
    addControlFrame->dispose();
    addControlFrame = NULL;
}

/**
 * Retrieve control information from window and update Light Control Returns
 * 'true' if no errors or warnings.
 */
/*private*/ bool LightTableAction::setControlInformation(LightControl* g) {
    // Get control information
    if (sensorControl == (typeBox->currentText())) {
        // Set type of control
        g->setControlType(Light::SENSOR_CONTROL);
        // Get sensor control information
        QString sensorName = field1a->text().trimmed();
        Sensor* s = NULL;
        if (sensorName.length() < 1) {
            // no sensor name entered
            g->setControlType(Light::NO_CONTROL);
        } else {
            // name was entered, check for user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensorName);
            if (s == NULL) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensorName);
                if (s != NULL) {
                    // update sensor system name in case it changed
                    sensorName = s->getSystemName();
                    field1a->setText(sensorName);
                }
            }
        }
        int sState = Sensor::ACTIVE;
        if (stateBox->currentText() == (tr("Inactive"))) {
            sState = Sensor::INACTIVE;
        }
        g->setControlSensorName(sensorName);
        g->setControlSensorSense(sState);
        if (s == NULL) {
            status1->setText(tr("Error: Sensor could not be provided. Light Control not created."));
            return (false);
        }
    } else if (fastClockControl == (typeBox->currentText())) {
        // Set type of control
        g->setControlType(Light::FAST_CLOCK_CONTROL);
        // read and parse the hours and minutes in the two fields
        bool error = false;
        int onHour = 0;
        int onMin = 0;
        int offHour = 0;
        int offMin = 0;
        QString s = field1b->text();
        if ((s.length() != 5) || (s.at(2) != ':')) {
            status1->setText(tr("Format error in time entry, please reenter as hh:mm."));
            error = true;
        }
        if (!error) {
            try {
                onHour = s.mid(0, 2).toInt();
                if ((onHour < 0) || (onHour > 24)) {
                    status1->setText(tr("Number out of range in time entry, please reenter as hh:mm."));
                    error = true;
                }
            } catch (NumberFormatException* e) {
                status1->setText(tr("Bad character in time field, please reenter as hh:mm."));
                error = true;
            }
        }
        if (!error) {
            try {
                onMin = s.mid(3, 5).toInt();
                if ((onMin < 0) || (onMin > 59)) {
                    status1->setText(tr("Number out of range in time entry, please reenter as hh:mm."));
                    error = true;
                }
            } catch (Exception* e) {
                status1->setText(tr("Bad character in time field, please reenter as hh:mm."));
                error = true;
            }
        }
        s = field2a->text();
        if ((s.length() != 5) || (s.at(2) != ':')) {
            status1->setText(tr("Format error in time entry, please reenter as hh:mm."));
            error = true;
        }
        if (!error) {
            try {
                offHour = s.mid(0, 2).toInt();
                if ((offHour < 0) || (offHour > 24)) {
                    status1->setText(tr("Number out of range in time entry, please reenter as hh:mm."));
                    error = true;
                }
            } catch (Exception* e) {
                status1->setText(tr("Bad character in time field, please reenter as hh:mm."));
                error = true;
            }
        }
        if (!error) {
            try {
                offMin = s.mid(3, 5).toInt();
                if ((offMin < 0) || (offMin > 59)) {
                    status1->setText(tr("Number out of range in time entry, please reenter as hh:mm."));
                    error = true;
                }
            } catch (Exception* e) {
                status1->setText(tr("Bad character in time field, please reenter as hh:mm."));
                error = true;
            }
        }

        if (error) {
            return (false);
        }
        g->setFastClockControlSchedule(onHour, onMin, offHour, offMin);
    } else if (turnoutStatusControl == (typeBox->currentText())) {
        bool error = false;
        Turnout* t = NULL;
        // Set type of control
        g->setControlType(Light::TURNOUT_STATUS_CONTROL);
        // Get turnout control information
        QString turnoutName = field1c->text().trimmed();
        if (turnoutName.length() < 1) {
            // valid turnout system name was not entered
            g->setControlType(Light::NO_CONTROL);
        } else {
            // Ensure that this Turnout is not already a Light
            if (turnoutName.at(1) == 'T') {
                // must be a standard format name (not just a number)
                QString testSN = turnoutName.mid(0, 1) + "L"
                        + turnoutName.mid(2, turnoutName.length());
                Light* testLight = (Light*)InstanceManager::lightManagerInstance()->
                        getBySystemName(testSN);
                if (testLight != NULL) {
                    // Requested turnout bit is already assigned to a Light
                    status2->setText(tr("Warning: Requested Turnout uses the same address as Light:") + " " + testSN + ".");
                    status2->setVisible(true);
                    error = true;
                }
            }
            if (!error) {
                // Requested turnout bit is not assigned to a Light
                t =(Turnout*) InstanceManager::turnoutManagerInstance()->
                        getByUserName(turnoutName);
                if (t == NULL) {
                    // not user name, try system name
                    t = (Turnout*)InstanceManager::turnoutManagerInstance()->
                            getBySystemName(turnoutName.toUpper());
                    if (t != NULL) {
                        // update turnout system name in case it changed
                        turnoutName = t->getSystemName();
                        field1c->setText(turnoutName);
                    }
                }
            }
        }
        // Initialize the requested Turnout State
        int tState = Turnout::CLOSED;
        if (stateBox->currentText() == (InstanceManager::
                turnoutManagerInstance()->getThrownText())) {
            tState = Turnout::THROWN;
        }
        g->setControlTurnout(turnoutName);
        g->setControlTurnoutState(tState);
        if (t == NULL) {
            status1->setText(tr("Error: Turnout could not be provided. Light Control not created."));
            return (false);
        }
    } else if (timedOnControl == (typeBox->currentText())) {
        // Set type of control
        g->setControlType(Light::TIMED_ON_CONTROL);
        // Get trigger sensor control information
        Sensor* s = NULL;
        QString triggerSensorName = field1d->text();
        if (triggerSensorName.length() < 1) {
            // Trigger sensor not entered, or invalidly entered
            g->setControlType(Light::NO_CONTROL);
        } else {
            // name entered, try user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(triggerSensorName);
            if (s == NULL) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(triggerSensorName);
                if (s != NULL) {
                    // update sensor system name in case it changed
                    triggerSensorName = s->getSystemName();
                    field1d->setText(triggerSensorName);
                }
            }
        }
        g->setControlTimedOnSensorName(triggerSensorName);
        int dur = 0;
        bool bok;
            dur = field2b->text().toInt(&bok);
        if(!bok){
            if (s != NULL) {
                status1->setText(tr("Error: Duration entry had invalid format. Light Control not created."));
                return (false);
            }
        }
        g->setTimedOnDuration(dur);
        if (s == NULL) {
            status1->setText(tr("Error: Trigger Sensor has invalid name. Light Control not created."));
            return (false);
        }
    } else if (twoSensorControl == (typeBox->currentText())) {
        // Set type of control
        g->setControlType(Light::TWO_SENSOR_CONTROL);
        // Get sensor control information
        QString sensorName = field1a->text().trimmed();
        Sensor* s = NULL;
        QString sensor2Name = field1a2->text().trimmed();
        Sensor* s2 = NULL;
        if ((sensorName.length() < 1) || (sensor2Name.length() < 1)) {
            // no sensor name entered
            g->setControlType(Light::NO_CONTROL);
        } else {
            // name was entered, check for user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensorName);
            if (s == NULL) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensorName);
                if (s != NULL) {
                    // update sensor system name in case it changed
                    sensorName = s->getSystemName();
                    field1a->setText(sensorName);
                }
            }
            s2 = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensor2Name);
            if (s2 == NULL) {
                // not user name, try system name
                s2 = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensor2Name);
                if (s2 != NULL) {
                    // update sensor system name in case it changed
                    sensor2Name = s2->getSystemName();
                    field1a2->setText(sensor2Name);
                }
            }
        }
        int sState = Sensor::ACTIVE;
        if (stateBox->currentText() == (tr("Inactive"))) {
            sState = Sensor::INACTIVE;
        }
        g->setControlSensorName(sensorName);
        g->setControlSensor2Name(sensor2Name);
        g->setControlSensorSense(sState);
        if (s == NULL) {
            status1->setText(tr("Error: Sensor could not be provided. Light Control not created."));
            return (false);
        }
    } else if (noControl == (typeBox->currentText())) {
        // Set type of control
        g->setControlType(Light::NO_CONTROL);
    } else {
         log->error("Unexpected control type: " + typeBox->currentText());
    }
    return (true);
}
#endif
#if 0
/**
 * Formats time to hh:mm given integer hour and minute
 */
QString LightTableAction::formatTime(int hour, int minute) {
    QString s = "";
    QString t = QString::number(hour);
    if (t.length() == 2) {
        s = t + ":";
    } else if (t.length() == 1) {
        s = "0" + t + ":";
    }
    t = QString::number(minute);
    if (t.length() == 2) {
        s = s + t;
    } else if (t.length() == 1) {
        s = s + "0" + t;
    }
    if (s.length() != 5) {
        // input error
        s = "00:00";
    }
    return s;
}

/**
 * Returns text showing the type of Light Control
 */
/*public*/ QString LightTableAction::getControlTypeText(int type) {
    switch (type) {
        case Light::SENSOR_CONTROL:
            return sensorControl;
        case Light::FAST_CLOCK_CONTROL:
            return fastClockControl;
        case Light::TURNOUT_STATUS_CONTROL:
            return turnoutStatusControl;
        case Light::TIMED_ON_CONTROL:
            return timedOnControl;
        case Light::TWO_SENSOR_CONTROL:
            return twoSensorControl;
        case Light::NO_CONTROL:
            return noControl;
        default:
            return noControl;
    }
}
#endif
/**
 * Returns text showing the type of Light Control
 */
/*public*/ /*static*/ QString LightTableAction::getDescriptionText(LightControl* lc, int type) {
    switch (type) {
        case Light::SENSOR_CONTROL:
            return tr("ON when %1 is %2.").arg(lc->getControlSensorName(), getControlSensorSenseText(lc));
        case Light::FAST_CLOCK_CONTROL:
            return tr("ON at %1, OFF at %2.").arg(tr("%1:%2").arg(lc->getFastClockOnHour()).arg(lc->getFastClockOnMin()).arg(
                        tr("%1:%2").arg(lc->getFastClockOffHour()).arg(lc->getFastClockOffMin())));
        case Light::TURNOUT_STATUS_CONTROL:
            return tr("ON when %1 is %2.").arg(
                    lc->getControlTurnoutName()).arg(LightTableAction::getControlTurnoutStateText(lc));
        case Light::TIMED_ON_CONTROL:
            return tr("ON for %1 msec. when %2 goes %3.").arg(
                    "" + lc->getTimedOnDuration()).arg( lc->getControlTimedOnSensorName()).arg(
                        LightTableAction::getControlSensorSenseText(lc));
        case Light::TWO_SENSOR_CONTROL:
            return tr("ON when either %1} or %2 is %3}.").arg(
                    lc->getControlSensorName()).arg(lc->getControlSensor2Name(),
                        LightTableAction::getControlSensorSenseText(lc));
        default:
            return "";
    }
}

/*private*/ /*static*/ QString LightTableAction::getControlSensorSenseText(LightControl* lc) {
    int s = lc->getControlSensorSense();
    if (s == Sensor::ACTIVE) {
        return tr("Active");
    }
    return tr("Inactive");
}

/*private*/ /*static*/ QString LightTableAction::getControlTurnoutStateText(LightControl* lc) {
    int s = lc->getControlTurnoutState();
    if (s == Turnout::CLOSED) {
        return InstanceManager::turnoutManagerInstance()->getClosedText();
    }
    return InstanceManager::turnoutManagerInstance()->getThrownText();
}
#if 0
/**
 * Responds to Edit button on row in the Light Control Table
 */
/*protected*/ void LightTableAction::editControlAction(int row) {
    lc = controlList.at(row);
    if (lc == NULL) {
         log->error("Invalid light control edit specified");
        return;
    }
    inEditControlMode = true;
    addEditControlWindow();
    int ctType = lc->getControlType();
    switch (ctType) {
        case Light::SENSOR_CONTROL:
            setUpControlType(sensorControl);
            typeBox->setCurrentIndex(sensorControlIndex);
            field1a->setText(lc->getControlSensorName());
            stateBox->setCurrentIndex(sensorActiveIndex);
            if (lc->getControlSensorSense() == Sensor::INACTIVE) {
                stateBox->setCurrentIndex(sensorInactiveIndex);
            }
            break;
        case Light::FAST_CLOCK_CONTROL:
    {
            setUpControlType(fastClockControl);
            typeBox->setCurrentIndex(fastClockControlIndex);
            int onHour = lc->getFastClockOnHour();
            int onMin = lc->getFastClockOnMin();
            int offHour = lc->getFastClockOffHour();
            int offMin = lc->getFastClockOffMin();
            field1b->setText(formatTime(onHour, onMin));
            field2a->setText(formatTime(offHour, offMin));
            break;
    }
        case Light::TURNOUT_STATUS_CONTROL:
            setUpControlType(turnoutStatusControl);
            typeBox->setCurrentIndex(turnoutStatusControlIndex);
            field1c->setText(lc->getControlTurnoutName());
            stateBox->setCurrentIndex(turnoutClosedIndex);
            if (lc->getControlTurnoutState() == Turnout::THROWN) {
                stateBox->setCurrentIndex(turnoutThrownIndex);
            }
            break;
        case Light::TIMED_ON_CONTROL:
    {
            setUpControlType(timedOnControl);
            typeBox->setCurrentIndex(timedOnControlIndex);
            int duration = lc->getTimedOnDuration();
            field1d->setText(lc->getControlTimedOnSensorName());
            field2b->setText(QString::number(duration));
            break;
    }
        case Light::TWO_SENSOR_CONTROL:
            setUpControlType(twoSensorControl);
            typeBox->setCurrentIndex(twoSensorControlIndex);
            field1a->setText(lc->getControlSensorName());
            field1a2->setText(lc->getControlSensor2Name());
            stateBox->setCurrentIndex(sensorActiveIndex);
            if (lc->getControlSensorSense() == Sensor::INACTIVE) {
                stateBox->setCurrentIndex(sensorInactiveIndex);
            }
            break;
        case Light::NO_CONTROL:
            // Set up as "None"
            setUpControlType(noControl);
            typeBox->setCurrentIndex(noControlIndex);
            field1a->setText("");
            stateBox->setCurrentIndex(sensorActiveIndex);
            break;
    }
    updateControl->setVisible(true);
    createControl->setVisible(false);
    addControlFrame->adjustSize();
    addControlFrame->setVisible(true);
}

/**
 * Responds to Delete button on row in the Light Control Table
 */
/*protected*/ void LightTableAction::deleteControlAction(int row) {
    controlList.removeAt(row);
    lightControlTableModel->fireTableDataChanged();
    lightControlChanged = true;
}

/**
 * Table model for Light Controls in the Add/Edit Light window
 */
///*public*/ class LightControlTableModel extends javax.swing.table.AbstractTableModel implements
//        java.beans.PropertyChangeListener {

//    /*public*/ static final int TYPE_COLUMN = 0;
//    /*public*/ static final int DESCRIPTION_COLUMN = 1;
//    /*public*/ static final int EDIT_COLUMN = 2;
//    /*public*/ static final int REMOVE_COLUMN = 3;

    /*public*/ LightControlTableModel::LightControlTableModel(LightTableAction* lta, QObject* parent)
                : AbstractTableModel(parent)
    {
        //super();
     this->lta = lta;
     setObjectName("LightControlTableModel");
    }

    /*public*/ void LightControlTableModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == ("length")) {
            // a new LightControl item is available in the manager
            fireTableDataChanged();
        }
    }

//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == TYPE_COLUMN) {
//            return String.class;
//        }
//        if (c == DESCRIPTION_COLUMN) {
//            return String.class;
//        }
//        if (c == EDIT_COLUMN) {
//            return JButton.class;
//        }
//        if (c == REMOVE_COLUMN) {
//            return JButton.class;
//        }
//        return String.class;
//    }

    /*public*/ int LightControlTableModel::columnCount(const QModelIndex &parent) const
    {
        return REMOVE_COLUMN + 1;
    }

    /*public*/ int LightControlTableModel::rowCount(const QModelIndex &parent) const
    {
        return (lta->controlList.size());
    }

    /*public*/ Qt::ItemFlags LightControlTableModel::flags(const QModelIndex &index) const
    {
     int c = index.column();
        if (c == TYPE_COLUMN) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        if (c == DESCRIPTION_COLUMN) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        if (c == EDIT_COLUMN) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        }
        if (c == REMOVE_COLUMN) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        }
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    /*public*/ QVariant LightControlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        if (section == TYPE_COLUMN) {
            return tr("Control Type");
        } else if (section == DESCRIPTION_COLUMN) {
            return tr("Control Description");
        }
     }
        return QVariant();
    }

    /*public*/ int LightControlTableModel::getPreferredWidth(int col) {
        switch (col) {
            case TYPE_COLUMN:
                return JTextField(20).sizeHint().width();
            case DESCRIPTION_COLUMN:
                return  JTextField(70).sizeHint().width();
            case EDIT_COLUMN:
                return  JTextField(8).sizeHint().width();
            case REMOVE_COLUMN:
                return  JTextField(8).sizeHint().width();
        }
        return  JTextField(8).sizeHint().width();
    }

    /*public*/ QVariant LightControlTableModel::data(const QModelIndex &index, int role) const
    {
      if(role == Qt::DisplayRole)
      {
        int rx = index.row();
        if (rx > lta->controlList.size()) {
            return QVariant();
        }
        LightControl* lc = lta->controlList.at(rx);
        int c = index.column();
        switch (c) {
            case TYPE_COLUMN:
                return (lta->getControlTypeText(lc->getControlType()));
            case DESCRIPTION_COLUMN:
                return (lta->getDescriptionText(lc, lc->getControlType()));
            case EDIT_COLUMN:
                return tr("Edit");
            case REMOVE_COLUMN:
                return tr("Delete");
            default:
                break;
        }
      }
      if(lta->_graphicState &&  role == Qt::DecorationRole)
      {
       int c = index.column();

      }
      return QVariant();
    }

    /*public*/ bool LightControlTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
      if(role == Qt::EditRole)
      {
       int row = index.row();
       int col = index.column();
        if (col == EDIT_COLUMN) {
            // set up to edit. Use separate Runnable so window is created on top
//            class WindowMaker implements Runnable {

//                WindowMaker(int _row) {
//                    row = _row;
//                }
//                int row;

//                /*public*/ void run() {
                    lta->editControlAction(row);
//                }
//            }
//            WindowMaker t = new WindowMaker(row);
//            javax.swing.SwingUtilities.invokeLater(t);
        }
        if (col == REMOVE_COLUMN) {
            lta->deleteControlAction(row);
        }
        return true;
    }
      return false;
}
#endif
/*public*/ QString LightTableAction::getClassDescription() {
    return tr("Light Table");
}

/*protected*/ QString LightTableAction::getClassName() {
    return "jmri.jmrit.beantable.LightTableAction";
}
#if 0
/**
* Read and buffer graphics. Only called once for this table.
*
* @see #getTableCellEditorComponent(JTable, Object, boolean,
* int, int)
*/
/*protected*/ void LTBeanTableDataModel::loadIcons() {
 try
 {
  onImage = ImageIO::read(new File(onIconPath));
  offImage = ImageIO::read(new File(offIconPath));
 } catch (IOException* ex) {
     log->error(tr("error reading image from %1 or %2").arg(onIconPath).arg(offIconPath), ex);
 }
 log->debug("Success reading images");
 int imageWidth = onImage->width();
 int imageHeight = onImage->height();
 // scale icons 50% to fit in table rows
 QImage smallOnImage = onImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0); //, Image.SCALE_DEFAULT);
 QImage smallOffImage = offImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0); //, Image.SCALE_DEFAULT);
 onIcon = QPixmap::fromImage(smallOnImage);
 offIcon =  QPixmap::fromImage(smallOffImage);
 iconHeight = onIcon.height();
}

Logger* LTBeanTableDataModel::log = LoggerFactory::getLogger("LTBeanTableDataModel");
#endif
LTAValidator::LTAValidator(JTextField *fld, LightTableAction *act)
{
 this->fld = fld;
 this->act = act;
 connect(act->prefixBox, SIGNAL(currentTextChanged(QString)), this, SLOT(prefixBoxChanged(QString)));
 prefix = act->connectionChoice->getMemo()->getSystemPrefix();
 mark = ColorUtil::stringToColor("orange");
}

QValidator::State LTAValidator::validate(QString &s, int &pos) const
{
 QString value = s.trimmed();
 if ((value.length() < 1) && (allow0Length == false)) {
     return QValidator::Invalid;
 } else if ((allow0Length == true) && (value.length() == 0)) {
     return QValidator::Acceptable;
 } else {
     bool validFormat = false;
         // try {
         validFormat = qobject_cast<LightManager*>(InstanceManager::getDefault("LightManager"))->validSystemNameFormat(prefix + "L" + value) == Manager::NameValidity::VALID;
         // } catch (jmri.JmriException e) {
         // use it for the status bar?
         // }
     if (validFormat) {
         act->create->setEnabled(true); // directly update Create button
         fld->setBackground(QColor(Qt::white));
         return QValidator::Acceptable;
     } else {
         act->create->setEnabled(false); // directly update Create button
         fld->setBackground(QColor(mark));
         return QValidator::Invalid;
     }
 }
}

void LTAValidator::prefixBoxChanged(QString txt)
{
 prefix = ConnectionNameFromSystemName::getPrefixFromName(txt);
}

/*public*/ void LightTableAction::setMessagePreferencesDetails()
{
 AbstractTableAction::setMessagePreferencesDetails();
}
