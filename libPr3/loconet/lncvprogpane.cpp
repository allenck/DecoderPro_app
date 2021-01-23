#include "lncvprogpane.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "jtablepersistencemanager.h"
#include "borderfactory.h"
#include <QScrollArea>
#include "lncvmessagecontents.h"
#include "joptionpane.h"
#include "lncvdevicesmanager.h"
#include "lncvdevice.h"
#include "lncvdevices.h"

/**
 * Frame for discovery and display of LocoNet LNCV boards.
 * Derived from xbee node config. Verified with Digikeijs DR5033 hardware.
 *
 * Some of the message formats used in this class are Copyright Uhlenbrock.de
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Uhlenbrock.
 *
 * TODO add button in table rows to switch to DecoderPro ops mode programmer
 * @author Egbert Broerse Copyright (C) 2021
 */
// /*public*/ class LncvProgPane extends jmri.jmrix.loconet.swing.LnPanel implements LocoNetListener {


    ///*public*/ /*static*/ /*final*/ int LncvProgPane::ROW_HEIGHT = ( JButton("X").sizeHint().height())*9/10;


    /**
     * Constructor method
     */
    /*public*/ LncvProgPane::LncvProgPane(QWidget* parent) : LnPanel(parent){
        //super();

    }

    /**
     * {@inheritDoc}
     */
     //@Override
    /*public*/ QString LncvProgPane::getHelpTarget() {
        return "package.jmri.jmrix.loconet.swing.lncvprog.LncvProgPane"; // NOI18N
    }

     //@Override
    /*public*/ QString LncvProgPane::getTitle() {
        return tr("Configure LNCV Modules");
    }

    /**
     * Initialize the config window
     */
     //@Override
    /*public*/ void LncvProgPane::initComponents() {
        setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
        // buttons at top, like SE8c pane
        layout()->addWidget(initButtonPanel()); // requires presence of memo.
        layout()->addWidget(initStatusPanel()); // positioned after ButtonPanel so to keep it simple also delayed
        // creation of table must wait for memo + tc to be available, see initComponents(memo) next
    }

     //@Override
    /*public*/ /*synchronized*/ void LncvProgPane::initComponents(LocoNetSystemConnectionMemo* memo) {
        LnPanel::initComponents(memo);
        if(this->layout()== nullptr)
         setLayout(new QVBoxLayout);
        this->memo = memo;
        lncvdm = memo->getLncvDevicesManager();
        pm = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
        // connect to the LnTrafficController
        if (memo->getLnTrafficController() == nullptr) {
            log->error("No traffic controller is available");
        } else {
            // add listener
            memo->getLnTrafficController()->addLocoNetListener(~0, this);
        }

        // create the data model and its table
        moduleTableModel = new LncvProgTableModel(this, memo);
        moduleTable = new JTable(moduleTableModel);
        moduleTable->setRowSelectionAllowed(false);
        //moduleTable->setPreferredScrollableViewportSize(new Dimension(300, 200));
        resize(300, 200);
        moduleTable->setRowHeight((JButton("X").sizeHint().height())*9/10);
        moduleTable->setDefaultEditor("JButton", new ButtonEditor(new JButton()));
        moduleTable->setDefaultRenderer("JButton", new ButtonRenderer());
        moduleTable->setRowSelectionAllowed(true);
        //moduleTable->getSelectionModel().addListSelectionListener(new ListSelectionListener(){
        connect(moduleTable, &JTable::clicked, [=]{
//            /*public*/ void valueChanged(ListSelectionEvent event) {
                // print first column value from selected row
                copyEntry( moduleTable->getValueAt(moduleTable->getSelectedRow(), 1).toInt(),
                        (int) moduleTable->getValueAt(moduleTable->getSelectedRow(), 2).toInt());
//            }
        });
        // establish row sorting for the table
        sorter = new TableRowSorter/*<LncvProgTableModel*>*/(moduleTableModel);
        moduleTable->setRowSorter(sorter);
         // establish table physical characteristics persistence
        moduleTable->setName("LNCV Device Management"); // NOI18N
        // Reset and then persist the table's ui state
        JTablePersistenceManager* tpm;
        if( tpm =(JTablePersistenceManager*)InstanceManager::getOptionalDefault("JTablePersistenceManager"))//.ifPresent((tpm) ->
        {
            /*synchronized (this) */{
                tpm->resetState(moduleTable);
                tpm->persist(moduleTable/*, true*/);
            }
        }//);

        //JScrollPane tableScrollPane = new JScrollPane(moduleTable);
        tablePanel = new JPanel();
        Border* resultBorder = BorderFactory::createEtchedBorder();
        Border* resultTitled = BorderFactory::createTitledBorder(resultBorder, tr("LNCV Module Table"));
        tablePanel->setLayout(new QVBoxLayout());//tablePanel, BoxLayout.Y_AXIS));
        tablePanel->setBorder(resultTitled);
        tablePanel->layout()->addWidget(moduleTable);//tableScrollPane, BorderLayout.CENTER);

        layout()->addWidget(tablePanel);

        layout()->addWidget(initNotesPanel());
        rawCheckBox->setChecked(pm->getSimplePreferenceState(rawDataCheck));
    }

    /*
     * Initialize the Notes panel.
     */
    /*protected*/ JPanel* LncvProgPane::initNotesPanel() {
        // Set up the notes panel
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        JPanel* panel31 = new JPanel();
        panel31->setLayout(new QVBoxLayout());//panel31, BoxLayout.Y_AXIS));
        QScrollArea* resultScrollPane = new QScrollArea(/*result*/);
        resultScrollPane->setWidgetResizable(true);
        resultScrollPane->setWidget(result);
        panel31->layout()->addWidget(resultScrollPane);

        panel31->layout()->addWidget(rawCheckBox);
        rawCheckBox->setVisible(true);
        rawCheckBox->setToolTip(tr("f checked, show the raw traffic in hex"));
        panel3->layout()->addWidget(panel31);
        Border* panel3Border = BorderFactory::createEtchedBorder();
        Border* panel3Titled = BorderFactory::createTitledBorder(panel3Border, tr("LNCV Monitor"));
        panel3->setBorder(panel3Titled);
        return panel3;
    }

    /*
     * Initialize the Button panel. Requires presence of memo.
     */
    /*protected*/ JPanel* LncvProgPane::initButtonPanel() {
        // Set up buttons and entry fields
        JPanel* panel4 = new JPanel();
        panel4->setLayout(new FlowLayout());

        JPanel* panel41 = new JPanel();
        panel41->setLayout(new QVBoxLayout());//panel41, BoxLayout.PAGE_AXIS));
        allProgButton->setText(allProgRunning ?
                tr("ButtonStopAllProg") : tr("Start Broadcast Programming"));
        allProgButton->setToolTip(tr("A general 65535 command must be sent to allow access to a progbutton-activated LNCV article"));
        //allProgButton.addActionListener(e -> allProgButtonActionPerformed());
        connect(allProgButton, &JToggleButton::clicked, [=]{allProgButtonActionPerformed();});
        panel41->layout()->addWidget(allProgButton);

        modProgButton->setText((moduleProgRunning >= 0) ?
                tr("ButtonStopModProg") : tr("Start Module Programming"));
        modProgButton->setToolTip(tr("Enter the article number and address of the module"));
        //modProgButton.addActionListener(e -> modProgButtonActionPerformed());
        connect(modProgButton, &JToggleButton::clicked, [=]{modProgButtonActionPerformed();});
        panel41->layout()->addWidget(modProgButton);
        panel4->layout()->addWidget(panel41);

        JPanel* panel42 = new JPanel();
        panel42->setLayout(new QVBoxLayout());//panel42, BoxLayout.PAGE_AXIS));
        JPanel* panel421 = new JPanel(new FlowLayout());
        panel421->layout()->addWidget(articleFieldLabel);
        // entry field (decimal)
        articleField->setToolTip(tr("TipModuleArticleField"));
        panel421->layout()->addWidget(articleField);
        panel42->layout()->addWidget(panel421);

        JPanel* panel422 = new JPanel(new FlowLayout());
        panel422->layout()->addWidget(addressFieldLabel);
        // entry field (decimal) for Module Address
        addressField->setText("1");
        panel422->layout()->addWidget(addressField);
        panel42->layout()->addWidget(panel422);
        panel4->layout()->addWidget(panel42);

        JPanel* panel43 = new JPanel();
        Border* panel43Border = BorderFactory::createEtchedBorder();
        panel43->setBorder(panel43Border);
        panel43->setLayout(new QHBoxLayout());//panel43, BoxLayout.LINE_AXIS));

        JPanel* panel431 = new JPanel();
        panel431->setLayout(new QVBoxLayout());//panel431, BoxLayout.PAGE_AXIS));
        JPanel* panel4311 = new JPanel(new FlowLayout());
        panel4311->layout()->addWidget(cvFieldLabel);
        // entry field (decimal) for CV number to read/write
        //cvField->setToolTipText(tr("TipModuleCvField"));
        cvField->setText("0");
        panel4311->layout()->addWidget(cvField);
        panel431->layout()->addWidget(panel4311);

        JPanel* panel4312 = new JPanel(new FlowLayout());
        panel4312->layout()->addWidget(valueFieldLabel);
        // entry field (decimal) for CV value
        //valueField->setToolTipText(tr("TipModuleValueField"));
        valueField->setText("1");
        panel4312->layout()->addWidget(valueField);
        panel431->layout()->addWidget(panel4312);
        panel43->layout()->addWidget(panel431);

        JPanel* panel432 = new JPanel();
        panel432->setLayout(new QVBoxLayout());//panel432, BoxLayout.PAGE_AXIS));
        panel432->layout()->addWidget(readButton);
        readButton->setEnabled(false);
        //readButton->layout()->addActionListener(e -> readButtonActionPerformed());
        connect(readButton, &JButton::clicked, [=]{readButtonActionPerformed();});

        panel432->layout()->addWidget(writeButton);
        writeButton->setEnabled(false);
        //writeButton.addActionListener(e -> writeButtonActionPerformed());
        connect(writeButton, &JButton::clicked, [=]{writeButtonActionPerformed();});
        panel43->layout()->addWidget(panel432);
        panel4->layout()->addWidget(panel43);

        return panel4;
    }

    /*
     * Initialize the Status panel.
     */
    /*protected*/ JPanel* LncvProgPane::initStatusPanel() {
        // Set up module address and node type
        JPanel* panel2 = new JPanel();
        panel2->setLayout(new QVBoxLayout());//panel2, BoxLayout.PAGE_AXIS));
        JPanel* panel21 = new JPanel();
        panel21->setLayout(new FlowLayout());

        statusText1->setText("   ");
        statusText1->setHorizontalAlignment(JLabel::CENTER);
        panel21->layout()->addWidget(statusText1);
        panel2->layout()->addWidget(panel21);

        statusText2->setText("   ");
        statusText2->setHorizontalAlignment(JLabel::CENTER);
        panel2->layout()->addWidget(statusText2);
        return panel2;
    }

    /**
     * GENERALPROG button.
     */
    /*public*/ void LncvProgPane::allProgButtonActionPerformed() {
        if (moduleProgRunning >= 0) {
            statusText1->setText(tr("Warning: Module Programming running"));
            return;
        }
        // provide user feedback
        readButton->setEnabled(!allProgRunning);
        writeButton->setEnabled(!allProgRunning);
        log->debug(tr("AllProg pressed, allProgRunning=%1").arg((allProgRunning?"true":"false")));
        if (allProgRunning) {
            log->debug("Session was running, closing");
            // send LncvAllProgEnd command on LocoNet
            memo->getLnTrafficController()->sendLocoNetMessage(LncvMessageContents::createAllProgEndRequest(art));
            statusText1->setText(tr("LNCV General Programming closed"));
            allProgButton->setText(tr("Start Broadcast Programming"));
            articleField->setEnabled(true);
            addressField->setEnabled(true);
            allProgRunning = false;
            return;
        }
        articleField->setEnabled(false);
        addressField->setEnabled(false);
        art = -1;
        if (articleField->text() != ("")) {
            try {
                art = inDomain(articleField->text(), 9999);
            } catch (NumberFormatException e) {
                // fine, will do broadcast all
            }
        }
        // show dialog to protect unwanted ALL messages
        QVariantList dialogBoxButtonOptions = {
                tr("Proceed"),
                tr("Cancel")};
        int userReply = JOptionPane::showOptionDialog(this,
                tr("This in only intended for Uhlenbrock LNCV modules without an article number."),
                tr("Warning"),
                JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE,
                QIcon(), dialogBoxButtonOptions, dialogBoxButtonOptions[1]);
        if (userReply != 0) {
            return;
        }
        statusText1->setText(tr("LNCV General Programming running"));
        // send LncvProgSessionStart command on LocoNet
        LocoNetMessage* m = LncvMessageContents::createAllProgStartRequest(art);
        memo->getLnTrafficController()->sendLocoNetMessage(m);
        // stop and inform user
        statusText1->setText(tr("LNCV General Programming running"));
        allProgButton->setText(tr("Stop Broadcast Programming"));
        allProgRunning = true;
    }

    // MODULEPROG button
    /**
     * Handle Start/End Module Prog button.
     */
    /*public*/ void LncvProgPane::modProgButtonActionPerformed() {
        if (allProgRunning) {
            statusText1->setText(tr("Warning: General Programming running"));
            return;
        }
        if (articleField->text() == ("")) {
            statusText1->setText(tr("Enter an number in the Article Nr. field"));
            articleField->setBackground(Qt::red);
            modProgButton->setSelected(false);
            return;
        }
        if (addressField->text() == ("")) {
            statusText1->setText(tr("Enter a number in the Module Address field"));
            addressField->setBackground(Qt::red);
            modProgButton->setSelected(false);
            return;
        }
        // provide user feedback
        articleField->setBackground(Qt::white); // reset
        readButton->setEnabled(moduleProgRunning < 0);
        writeButton->setEnabled(moduleProgRunning < 0);
        if (moduleProgRunning >= 0) { // stop prog
            try {
                art = inDomain(articleField->text(), 9999);
                adr = moduleProgRunning; // use module address that was used to start Modprog
                memo->getLnTrafficController()->sendLocoNetMessage(LncvMessageContents::createModProgEndRequest(art, adr));
                statusText1->setText(tr("Ended Programming Module {%1").arg(adr));
                modProgButton->setText(tr("Start Module Programming"));
                moduleProgRunning = -1;
                articleField->setEnabled(true);
                addressField->setEnabled(true);
            } catch (NumberFormatException e) {
                statusText1->setText(tr("Enter an number in the Article Nr. field"));
                modProgButton->setSelected(true);
            }
            return;
        }
        if ((articleField->text() != ("")) && (addressField->text() != (""))) {
            try {
                art = inDomain(articleField->text(), 9999);
                adr = inDomain(addressField->text(), 65535); // goes in d5-d6 as module address
                memo->getLnTrafficController()->sendLocoNetMessage(LncvMessageContents::createModProgStartRequest(art, adr));
                statusText1->setText(tr("Started Programming Module %1").arg(adr));
                modProgButton->setText(tr("Stop Module Programming"));
                moduleProgRunning = adr; // store address during modProg, so next line is mostly as UI indication:
                articleField->setEnabled(false);
                addressField->setEnabled(false); // lock address field to prevent accidentally changing it

            } catch (NumberFormatException e) {
                log->error("invalid entry, must be number");
            }
        }
        // stop and inform user
    }

    // READCV button
    /**
     * Handle Read CV button, assemble LNCV read message. Requires presence of memo.
     */
    /*public*/ void LncvProgPane::readButtonActionPerformed() {
        QString sArt = "65535"; // LncvMessageContents.LNCV_ALL = broadcast
        if (moduleProgRunning >= 0) {
            sArt = articleField->text();
            articleField->setBackground(Qt::white); // reset
        }
        if ((sArt != "") && (addressField->text() != "") && (cvField->text() != "")) {
            try {
                art = inDomain(sArt, 9999); // limited according to Uhlenbrock info
                adr = inDomain(addressField->text(), 65535); // used as address for reply
                cv = inDomain(cvField->text(), 9999); // decimal entry
                memo->getLnTrafficController()->sendLocoNetMessage(LncvMessageContents::createCvReadRequest(art, adr, cv));
            } catch (NumberFormatException e) {
                log->error("invalid entry, must be number");
            }
        } else {
            statusText1->setText(tr("Enter an number in the Article Nr. field"));
            articleField->setBackground(Qt::red);
            return;
        }
        // stop and inform user
        statusText1->setText(tr("LNCV Read command sent"));
    }

    // WriteCV button
    /**
     * Handle Write button click, assemble LNCV write message. Requires presence of memo.
     */
    /*public*/ void LncvProgPane::writeButtonActionPerformed() {
        QString sArt = "65535"; // LncvMessageContents.LNCV_ALL;
        if (moduleProgRunning >= 0) {
            sArt = articleField->text();
        }
        if ((sArt != "") && (cvField->text() != "") && (valueField->text() != "")) {
            articleField->setBackground(Qt::white);
            try {
                art = inDomain(sArt, 9999);
                cv = inDomain(cvField->text(), 9999); // decimal entry
                val = inDomain(valueField->text(), 65535); // decimal entry
                if (cv == 0 && (val > 65534 || val < 1)) {
                    // reserved general module address, warn in status and abort
                    statusText1->setText(tr("FeedBackValidAddressRange"));
                    valueField->setBackground(Qt::red);
                    return;
                }
                writeConfirmed = false;
                memo->getLnTrafficController()->sendLocoNetMessage(LncvMessageContents::createCvWriteRequest(art, cv, val));
                valueField->setBackground(/*Qt::ORANGE*/QColor(255, 127,0));
            } catch (NumberFormatException e) {
                log->error("invalid entry, must be number");
            }
        } else {
            statusText1->setText(tr("Enter an number in the Article Nr. field"));
            articleField->setBackground(Qt::red);
            return;
        }
        // stop and inform user
        statusText1->setText(tr("LNCV Write command sent"));
        // wait for LACK reply
        //
        // if (received) {
        //      writeConfirmed = true;
        // }
    }

    /*private*/ int LncvProgPane::inDomain(QString entry, int max) {
        int n = -1;
        bool ok;
            n = entry.toInt(&ok);
        if(!ok) {
            log->error("invalid entry, must be number");
        }
        if ((0 <= n) && (n <= max)) {
            return n;
        } else {
            statusText1->setText(tr("Input outside valid number range, set to 0"));
            return 0;
        }
    }

    /*public*/ void LncvProgPane::copyEntry(int art, int mod) {
        if ((moduleProgRunning < 0) && !allProgRunning) { // protect locked fields while programming
            articleField->setText(QString::number(art));
            addressField->setText(QString::number(mod));
        }
    }

    /**
     * {@inheritDoc}
     * Compare to {@link LnOpsModeProgrammer#message(jmri.jmrix.loconet.LocoNetMessage)}
     *
     * @param l a message received and analysed for LNCV characteristics
     */
     //@Override
    /*public*/ /*synchronized*/ void LncvProgPane::message(LocoNetMessage* l) { // receive a LocoNet message and log it
        // got a LocoNet message, see if it's a LNCV response
        if (LncvMessageContents::isSupportedLncvMessage(l)) {
            // raw data, to display
            QString raw = (rawCheckBox->isChecked() ? ("[" + l->toString() + "] ") : "");
            // format the message text, expect it to provide consistent \n after each line
            QString formatted = l->toMonitorString(memo->getSystemPrefix());
            // copy the formatted data
            reply += raw + formatted;
        }
        // or LACK write confirmation response from module?
        if ((l->getOpCode() == LnConstants::OPC_LONG_ACK) &&
                (l->getElement(1) == 0x6D)) { // elem 1 = OPC (matches 0xED), elem 2 = ack1
            writeConfirmed = true;
            if (l->getElement(2) == 0x7f) {
                valueField->setBackground(Qt::green);
                reply += tr("(LNCV) WRITE confirmed by module %1").arg(moduleProgRunning) + "\n";
            } else if (l->getElement(2) == 1) {
                valueField->setBackground(Qt::red);
                reply += tr("(LNCV) WRITE to module %1 failed: CV%2 not present").arg(moduleProgRunning).arg(cv) + "\n";
            } else if (l->getElement(2) == 2) {
                valueField->setBackground(Qt::red);
                reply += tr("LNCVLNCV) WRITE to module %1 failed: CV{%2 is read only_WRITE_CV_READONLY").arg(moduleProgRunning).arg(cv) + "\n";
            } else if (l->getElement(2) == 3) {
                valueField->setBackground(Qt::red);
                reply += tr("(LNCV) WRITE to module %1 failed: Value {%2 outside allowed range").arg(moduleProgRunning).arg(val) + "\n";
            }
            return;
        }
        if (LncvMessageContents::extractMessageType(l)->equals( LncvCommand::map.value( LncvCommand::LNCV_WRITE))) {
            reply += tr("(LNCV) WRITE CV request to module %1 (currently in program mode)").arg((moduleProgRunning == -1 ? "ALL" : QString::number(moduleProgRunning))) + "\n";
        }
        if (LncvMessageContents::extractMessageType(l)->equals(LncvCommand::map.value(LncvCommand::LNCV_READ))) {
            reply += tr("(LNCV) READ CV request to module %1 (currently in program mode)").arg((moduleProgRunning == -1 ? "ALL" : QString::number(moduleProgRunning))) + "\n";
        }
        if (LncvMessageContents::extractMessageType(l)->equals(LncvCommand::map.value(LncvCommand::LNCV_READ_REPLY))) {
            // it's a LNCV ReadReply message, decode contents:
            LncvMessageContents* contents = new LncvMessageContents(l);
            int msgArt = contents->getLncvArticleNum();
            int msgAdr = moduleProgRunning;
            int msgCv = contents->getCvNum();
            int msgVal = contents->getCvValue();
            if ((msgCv == 0) || (msgArt == art)) { // trust last used address. to be sure, check against Article (hardware class) number
                msgAdr = msgVal; // if cvNum = 0, this is the LNCV module address
            }
            QString foundMod = "(LNCV) " + tr("Article Number:") +  QString::number(art) + " "
                    + tr("address:") + QString::number(msgAdr) + " "
                    + tr("cv:") + QString::number(msgCv) + " "
                    + tr("value:")+ QString::number(msgVal) + "\n";
            reply += foundMod;
            // store Module in list using write reply is handled by loconet.LncvDevicesManager

            // enter returned CV in CVnum field
            cvField->setText(msgCv + "");
            cvField->setBackground(Qt::white);
            // enter returned value in Value field
            valueField->setText(msgVal + "");
            valueField->setBackground(Qt::white);

            LncvDevice* dev = memo->getLncvDevicesManager()->getDevice(art, adr);
            if (dev != nullptr) {
                dev->setCvNum(msgCv);
                dev->setCvValue(msgVal);
            }
            memo->getLncvDevicesManager()->firePropertyChange("DeviceListChanged", true, false);
        }

        if (reply != "") {
            allProgFinished("");
        }
    }

    /*
     * AllProg Session callback.
     */
    /*public*/ void LncvProgPane::allProgFinished(QString error) {
        if (error != "") {
             log->error(tr("LNCV process finished with error: %1").arg(error));
             statusText2->setText(tr("FeedBackDiscoverFail"));
        } else {
            log->debug("LNCV process completed successfully.");
            /*synchronized (this) */{
                statusText2->setText(tr("%1 Modules discovered").arg(lncvdm->getDeviceCount()));
                result->setText(reply);
            }
        }
    }

    /**
     * {@inheritDoc}
     */
     //@Override
    /*public*/ void LncvProgPane::dispose() {
        if (memo != nullptr && memo->getLnTrafficController() != nullptr) {
            // disconnect from the LnTrafficController, normally attached/detached after Discovery completed
            memo->getLnTrafficController()->removeLocoNetListener(~0, this);
        }
        // and unwind swing
        if (pm != nullptr) {
            pm->setSimplePreferenceState(rawDataCheck, rawCheckBox->isChecked());
        }
        if (moduleProgRunning >= 0) {
            modProgButtonActionPerformed();
        }
        if (allProgRunning) {
            allProgButtonActionPerformed();
        }
        LnPanel::setVisible(false);

        JTablePersistenceManager* tpm = (JTablePersistenceManager*)InstanceManager::getOptionalDefault("JTablePersistenceManager"); //.ifPresent((tpm)
        if(tpm) {
            /*synchronized (this)*/ {
                tpm->stopPersisting(moduleTable);
            }
        }//);

        LnPanel::dispose();
    }

    /**
     * Testing methods.
     *
     * @return text currently in Article field
     */
    /*protected*/ QString LncvProgPane::getArticleEntry() {
        if (!articleField->isEnabled()) {
            return "locked";
        } else {
            return articleField->text();
        }
    }

    /*protected*/ QString LncvProgPane::getAddressEntry() {
        if (!addressField->isEnabled()) {
            return "locked";
        } else {
            return addressField->text();
        }
    }

    /*protected*/ QString LncvProgPane::getMonitorContents(){
            return reply;
    }

    /*protected*/ void LncvProgPane::setCvFields(int cvNum, int cvVal) {
        cvField->setText(""+cvNum);
        if (cvVal > -1) {
            valueField->setText("" + cvVal);
        } else {
            valueField->setText("");
        }
    }

    /*protected*/ /*synchronized*/ LncvDevice* LncvProgPane::getModule(int i) {
        if (lncvdm == nullptr) {
            lncvdm = memo->getLncvDevicesManager();
        }
        log->debug(tr("lncvdm.getDeviceCount()=%1").arg(lncvdm->getDeviceCount()));
        if (i > -1 && i < lncvdm->getDeviceCount()) {
            return lncvdm->getDeviceList()->getDevice(i);
        } else {
            log->debug(tr("getModule(%1) failed").arg(i));
            return nullptr;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LncvProgPane::log = LoggerFactory::getLogger("LncvProgPane");
