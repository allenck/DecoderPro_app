#include "signaleditframe.h"
#include "loggerfactory.h"
#include "portalmanager.h"
#include "portal.h"
#include "spinnernumbermodel.h"
#include "jspinner.h"
#include "jtextfield.h"
#include <QButtonGroup>
#include "box.h"
#include "oblock.h"
#include "signalhead.h"

/**
 * Defines a GUI for editing OBlock - Signal objects in the tabbed Table interface.
 * Adapted from AudioSourceFrame.
 * Compare to CPE CircuitBuilder Signal Config frame {@link jmri.jmrit.display.controlPanelEditor.EditSignalFrame}
 *
 * @author Matthew Harris copyright (c) 2009
 * @author Egbert Broerse (C) 2020
 */
///*public*/ class SignalEditFrame extends JmriJFrame {


    //@SuppressWarnings("OverridableMethodCallInConstructor")
    /*public*/ SignalEditFrame::SignalEditFrame(/*@Nonnull*/ QString title,
                           /*@CheckForNull*/ NamedBean* signal,
                           /*@CheckForNull*/ SignalTableModel::SignalRow* sr,
                           /*@CheckForNull*/ SignalTableModel* model, QWidget* parent) : JmriJFrame(title, true, true, parent) {
        //super(title, true, true);
        this->model = model;
        this->signal = signal;
        if (signal == nullptr) {
            _newSignal = true;
        }
        log->debug(tr("SR == %1").arg((sr == nullptr ? "null" : "not null")));
        obm = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
        pm = (PortalManager*)InstanceManager::getDefault("PortalManager");
        for (Portal* pi : pm->getPortalSet()) {
            portalComboBox->addItem(pi->getName());
        }
        layoutFrame();
        if (sr != nullptr) {
            _sr = sr;
            _portal = sr->getPortal();
            populateFrame(_sr);
        } else {
            resetFrame();
        }
        addCloseListener(this);
    }

    /*public*/ void SignalEditFrame::layoutFrame() {
        frame->addHelpMenu("package.jmri.jmrit.beantable.OBlockTable", true);
        frame->getContentPane()->setLayout(new QVBoxLayout());//frame->getContentPane(), BoxLayout.PAGE_AXIS));
        frame->resize(300, 200);
        main->setLayout(new QVBoxLayout());//main, BoxLayout.PAGE_AXIS));

        JPanel* configGrid = new JPanel();
        QGridLayout* layout = new QGridLayout();//4, 2, 10, 0); // (int rows, int cols, int hgap, int vgap)
        configGrid->setLayout(layout);

        JPanel* p = new JPanel();
        p->setLayout(new QVBoxLayout());//p, BoxLayout.PAGE_AXIS));

        // row 1
        JPanel* p1 = new JPanel(new FlowLayout());
        p1->layout()->addWidget(signalMastLabel);
        p1->layout()->addWidget(sigMastComboBox);
        sigMastComboBox->setAllowNull(true);
        p1->layout()->addWidget(mastName);
        configGrid->layout()->addWidget(p1);

        p1 = new JPanel();
        p1->layout()->addWidget(signalHeadLabel);
        p1->layout()->addWidget(sigHeadComboBox);
        sigHeadComboBox->setAllowNull(true);
        p1->layout()->addWidget(headName);
        configGrid->layout()->addWidget(p1);
//        sigMastComboBox->addActionListener(e -> {
        connect(sigMastComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
            if ((sigMastComboBox->getSelectedIndex() > 0) && (sigHeadComboBox->getItemCount() > 0)) {
                sigHeadComboBox->setSelectedIndex(0); // either one
                model->checkDuplicateSignal(sigMastComboBox->getSelectedItem());
            }
        });
//        sigHeadComboBox->addActionListener(e -> {
            connect(sigHeadComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
            if ((sigHeadComboBox->getSelectedIndex() > 0) && (sigMastComboBox->getItemCount() > 0)) {
                sigMastComboBox->setSelectedIndex(0); // either one
                model->checkDuplicateSignal(sigHeadComboBox->getSelectedItem());
            }
        });

        // row 2
        p1 = new JPanel();
        p1->layout()->addWidget(portalLabel);
        p1->layout()->addWidget(portalComboBox); // combo has a blank first item
//        portalComboBox->addActionListener(e -> {
        connect(portalComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
            if (portalComboBox->getSelectedIndex() > 0) {
                fromBlock->setText(pm->getPortal( portalComboBox->getSelectedItem())->getFromBlockName());
                toBlock->setText(pm->getPortal( portalComboBox->getSelectedItem())->getToBlockName());
            }
        });
        configGrid->layout()->addWidget(p1);
//        flipButton.addActionListener(e -> {
        connect(flipButton, &JButton::clicked, [=]{
            QString left = fromBlock->text();
            fromBlock->setText(toBlock->text());
            toBlock->setText(left);
        });
        p1 = new JPanel();
        p1->layout()->addWidget(flipButton);
        flipButton->setToolTip(tr("<html>Invert the From and To (Protected) Blocks.<br>To assign a different Block to this Portal, edit it in the Portal Table</html>"));
        configGrid->layout()->addWidget(p1);

        // row 3
        p1 = new JPanel();
        p1->layout()->addWidget(fromBlockLabel);
        p1->layout()->addWidget(fromBlock);
//        fromBlockComboBox->setAllowNull(true);
//        fromBlockComboBox.addActionListener(e -> {
//            if (fromBlockComboBox->getSelectedIndex() == toBlockComboBox->getSelectedIndex()) {
//                toBlockComboBox->setSelectedIndex(0);
//            }
//        });
        configGrid->layout()->addWidget(p1);

        p1 = new JPanel();
        p1->layout()->addWidget(toBlockLabel);
        p1->layout()->addWidget(toBlock);
//        toBlockComboBox->setAllowNull(true);
//        toBlockComboBox.addActionListener(e -> {
//            if (fromBlockComboBox->getSelectedIndex() == toBlockComboBox->getSelectedIndex()) {
//                fromBlockComboBox->setSelectedIndex(0);
//            }
//        });
        configGrid->layout()->addWidget(p1);

        // row 4
        // copied from beanedit, also in BlockPathEditFrame
        p1 = new JPanel();
        p1->layout()->addWidget(new JLabel(tr("%1").arg(tr("Offset"))));
        lengthSpinner->setModel(
                new SpinnerNumberModel((0), (-2000), (2000), (0.01)));
//        lengthSpinner->setEditor(new JSpinner::NumberEditor(lengthSpinner, "###0.00"));
        lengthSpinner->resize( JTextField(8).getPreferredSize());
        lengthSpinner->setValue(0); // reset from possible previous use
        lengthSpinner->setToolTip(tr("<html>Distance from Signal to speed change point.<br>It is added to (- subtracted from) the calculation of the ramp distance<br>when a Warrant must slow the train in response to the Aspect or Appearance of the Signal.</html>"));
        p1->layout()->addWidget(lengthSpinner);
        configGrid->layout()->addWidget(p1);

        QButtonGroup* bg = new QButtonGroup(this);
        bg->addButton(inch);
        bg->addButton(cm);

        p1 = new JPanel();
        p1->layout()->addWidget(inch);
        p1->layout()->addWidget(cm);
        p1->setLayout(new QVBoxLayout());//p1, BoxLayout.PAGE_AXIS));
        inch->setChecked(true);
//        inch.addActionListener(e -> {
        connect(inch, &QRadioButton::clicked, [=]{
            cm->setChecked(!inch->isChecked());
            updateLength();
        });
//        cm.addActionListener(e -> {
        connect(cm, &QRadioButton::clicked, [=]{
            inch->setChecked(!cm->isChecked());
            updateLength();
        });
        configGrid->layout()->addWidget(p1);
        p->layout()->addWidget(configGrid);

        p->layout()->addWidget(Box::createHorizontalGlue());

        JPanel* p2 = new JPanel();
        //statusBar->setFont(statusBar->getFont().deriveFont(0.9f * signalMastLabel->getFont()->getSize())); // a bit smaller
        QFont f = statusBar->font();
        f.setPointSizeF(signalMastLabel->getFont().pointSizeF()*.9);
        statusBar->setFont(f);
        statusBar->setForeground(Qt::gray);
        p2->layout()->addWidget(statusBar);
        p->layout()->addWidget(p2);

        p2 = new JPanel();
        p2->setLayout(new QHBoxLayout());//p2, BoxLayout.LINE_AXIS));
        JButton* cancel;
        p2->layout()->addWidget(cancel = new JButton(tr("Cancel")));
//        cancel.addActionListener((ActionEvent e) -> closeFrame());
        connect(cancel, &JButton::clicked, [=]{
         closeFrame();
        });
        JButton* ok;
        p2->layout()->addWidget(ok = new JButton(tr("OK")));
        //ok.addActionListener(this::applyPressed);
        p->layout()->addWidget(p2);
        connect(ok, &JButton::clicked, [=]{
         applyPressed();
        });

        //main.add(p);
        frame->getContentPane()->layout()->addWidget(p);
        //frame.add(scroll);
        frame->pack();
    }

    /**
     * Reset the Edit Signal frame with default values.
     */
    /*public*/ void SignalEditFrame::resetFrame() {
        if (sigMastComboBox->getItemCount() > 0) {
            sigMastComboBox->setSelectedIndex(0);
        }
        if (sigHeadComboBox->getItemCount() > 0) {
            sigHeadComboBox->setSelectedIndex(0);
        }
        if (portalComboBox->getItemCount() > 0) {
            portalComboBox->setSelectedIndex(0);
        }
        lengthSpinner->setValue(0);
        // reset statusBar text
        if ((sigMastComboBox->getItemCount() == 0) && (sigHeadComboBox->getItemCount() == 0)) {
            status(tr("Define Signals in JMRI before using them with OBlocks"), true);
        } else if (portalComboBox->getItemCount() > 1) {
            status(tr("To create a new %1, enter its definition, then click [%2].").arg(
                    (tr("SignalMast")+"/"+tr("SignalHead"))).arg(
                    tr("OK")), false); // I18N to include original button name in help string
        } else {
            status(tr("To set up a Signal, define at least 1 Portal with 2 Blocks in the Portal Table."), true);
        }
        mastName->setVisible(false);
        headName->setVisible(false);
        sigMastComboBox->setVisible(true);
        sigHeadComboBox->setVisible(true);
        frame->pack();
    }

    /**
     * Populate the Edit Signal frame with current values from a SignalRow in the SignalTable.
     *
     * @param sr existing SignalRow to copy the attributes from
     */
    /*public*/ void SignalEditFrame::populateFrame(SignalTableModel::SignalRow* sr) {
        if (sr == nullptr) {
            throw IllegalArgumentException("Null Signal object");
        }
        status(tr("To change this %1, make changes above, then click [%2].").arg(sr->getSignal()->getDisplayName()).arg(
                tr("OK")), false);
        fromBlock->setText(sr->getFromBlock()->getDisplayName());
        toBlock->setText(sr->getToBlock()->getDisplayName());
        if (qobject_cast<SignalMast*>(signal)) {
            mastName->setText(sr->getSignal()->getDisplayName());
            headName->setText("-");
            //sigMastComboBox->setSelectedItemByName(sr->getSignal()->getDisplayName()); // combo hidden for Edits
        } else if (qobject_cast<SignalHead*>(signal)) {
            mastName->setText("-");
            headName->setText(sr->getSignal()->getDisplayName());
            //sigHeadComboBox->setSelectedItemByName(sr->getSignal()->getDisplayName()); // combo hidden for Edits
        }
        portalComboBox->setSelectedItem(_portal->getName());
        cm->setChecked(sr->_isMetric); // before filling in value in spinner prevent recalc
        if (sr->isMetric()) {
            lengthSpinner->setValue(sr->getLength()/10);
        } else {
            lengthSpinner->setValue(sr->getLength()/25.4f);
        }
        mastName->setVisible(true);
        headName->setVisible(true);
        sigMastComboBox->setVisible(false);
        sigHeadComboBox->setVisible(false);
        frame->pack();
        _newSignal = false;
    }

    /*private*/ void SignalEditFrame::applyPressed(/*ActionEvent e*/) {
        if (_newSignal) { // can't change an existing mast, easy to delete and recreate
            if (sigMastComboBox->getSelectedIndex() > 0) {
                signal = sigMastComboBox->getSelectedItem();
            } else if (sigHeadComboBox->getSelectedIndex() > 0) {
                signal = sigHeadComboBox->getSelectedItem();
            } else {
                status(tr("WarnNoSignal"), true);
                return;
            }
            QString msg = model->checkDuplicateSignal(signal);
            if (msg != "") {
                status(msg, true);
                return;
            }
        }
        _portal = pm->getPortal( portalComboBox->getSelectedItem());
        if (_portal == nullptr || portalComboBox->getSelectedIndex() < 1) {
            status(tr("WarnNoPortal"), true);
            return;
        }
        if (!_newSignal) {
            model->deleteSignal(_sr);    // delete old in Portal if it was set
            _sr->setPortal(_portal);
        }
        // fetch physical details
        float length;
        if (cm->isChecked()) {
            length = (float) lengthSpinner->getValue()*10.0f;
        } else {
            length = (float) lengthSpinner->getValue()*25.4f;
        }

        if (_portal->setProtectSignal(signal, length, obm->getOBlock(toBlock->getText()))) {
            if ((fromBlock->getText() == "") && (toBlock->getText() != "")) { // could be read from old panels?
                _portal->setFromBlock(_portal->getOpposingBlock(obm->getOBlock(/*Objects.requireNonNull*/(toBlock->getText()))), true);
            }
        }
        // update Metric choice in /*protected*/Block
        if (toBlock->getText() != nullptr) {
            /*Objects.requireNonNull*/(obm->getOBlock(toBlock->getText()))->setMetricUnits(cm->isChecked());
        }
        // Notify changes
        model->fireTableDataChanged();

        closeFrame();
    }

    /*protected*/ void SignalEditFrame::closeFrame(){
        // remind to save, if Turnout was created or edited
        //        if (isDirty) {
        //            showReminderMessage();
        //            isDirty = false;
        //        }
        // hide frame
        setVisible(false);

        model->setEditMode(false);
        log->debug("SignalEditFrame.closeFrame signalEdit=False");
        frame->dispose();
    }

    // copied from beanedit, also in BlockPathEditFrame
    /*private*/ void SignalEditFrame::updateLength() {
        float len = (float) lengthSpinner->getValue();
        if (inch->isChecked()) {
            lengthSpinner->setValue(len/2.54f);
        } else {
            lengthSpinner->setValue(len*2.54f);
        }
    }

    void SignalEditFrame::status(QString message, bool warn){
        statusBar->setText(message);
        statusBar->setForeground(warn ? Qt::red : Qt::gray);
    }

    // listen for frame closing
    void SignalEditFrame::addCloseListener(JmriJFrame* frame) {
        frame->addWindowListener(new SEFWindowListener(this));
//        {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                model->setEditMode(false);
//                log.debug("SignalEditFrame.closeFrame signalEdit=False");
//                frame->dispose();
//            }
//        });
    }

    /*private*/ /*static*/ /*final*/ Logger* SignalEditFrame::log = LoggerFactory::getLogger("SignalEditFrame");
