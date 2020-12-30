#include "blockpatheditframe.h"
#include "loggerfactory.h"
#include "portal.h"
#include "oblock.h"
#include "userpreferencesmanager.h"
#include "pathturnouttablemodel.h"
#include "blockpathtablemodel.h"
#include "opath.h"
#include "joptionpane.h"
#include "spinnernumbermodel.h"
#include <QButtonGroup>
#include "borderlayout.h"
#include "borderfactory.h"
#include "box.h"
#include "jbutton.h"

/**
 * Defines a GUI for editing OBlock - OPath objects in the _tabbed OBlock Table interface.
 * Based on {@link jmri.jmrit.audio.swing.AudioSourceFrame} and
 * {@link jmri.jmrit.beantable.routetable.AbstractRouteAddEditFrame}
 *
 * @author Matthew Harris copyright (c) 2009
 * @author Egbert Broerse (C) 2020
 */
///*public*/ class BlockPathEditFrame extends JmriJFrame {



//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ BlockPathEditFrame::BlockPathEditFrame(QString title, OBlock* block, OPath* path,
                          TableFrames::PathTurnoutJPanel* turnouttable, BlockPathTableModel* pathmodel, TableFrames* parent) :JmriJFrameX(title, true, true) {
    //super(title, true, true);
    _block = block;
    _turnoutTablePane = turnouttable;
    _pathmodel = pathmodel;
    _core = parent;
    if (path == nullptr || turnouttable == nullptr) {
        _newPath = true;
    } else {
        _path = path;
        _tomodel = turnouttable->getModel();
        if (_tomodel != nullptr) { // test uses a plain JTable without getRowCount()
            log->debug(tr("TurnoutModel.size = %1").arg(_tomodel->getRowCount()));
        }
    }
    // fill Portals combo
    pm = (PortalManager*)InstanceManager::getDefault("PortalManager");
    for (Portal* pi : pm->getPortalSet()) {
        fromPortalComboBox->addItem(pi->getName());
        toPortalComboBox->addItem(pi->getName());
    }

    layoutFrame();
    blockName->setText(_block->getDisplayName());
    if (_newPath) {
        resetFrame();
    } else {
        populateFrame(path);
    }

    addCloseListener(this);

}

/*public*/ void BlockPathEditFrame::layoutFrame() {
    frame->addHelpMenu("package.jmri.jmrit.beantable.OBlockTable", true);
    frame->getContentPane()->setLayout(new QVBoxLayout());//frame.getContentPane(), BoxLayout.Y_AXIS));
    frame->resize(400, 500);

    JPanel* p = new JPanel();
    p->setLayout(new QVBoxLayout());//p, BoxLayout.PAGE_AXIS));

    JPanel* configGrid = new JPanel();
    QGridLayout* layout = new QGridLayout(/*5, 2, 10, 0*/); // (int rows, int cols, int hgap, int vgap)
    configGrid->setLayout(layout);

    // row 1
    layout->addWidget(blockLabel, 0, 0);
    layout->addWidget(blockName, 0,1);

    // row 2
    layout->addWidget(pathLabel, 1,0);
    JPanel* p1 = new JPanel();
    p1->layout()->addWidget(pathUserName);
    layout->addWidget(p1, 1, 1);

    // row 3
    layout->addWidget(fromPortalLabel, 2,0);
//    fromPortalComboBox.addActionListener(e -> {
    connect(fromPortalComboBox, &JComboBox::currentIndexChanged, [=]{

        if ((fromPortalComboBox->getItemCount() > 0) && (fromPortalComboBox->getSelectedItem() != "") &&
                (toPortalComboBox->getSelectedItem() != "")
                && (fromPortalComboBox->getSelectedItem() == (toPortalComboBox->getSelectedItem()))) {
            log->debug("resetting ToPortal");
            toPortalComboBox->setSelectedIndex(0); // clear the other one
        }
    });
    layout->addWidget(fromPortalComboBox, 2,1);

    // row 4
    layout->addWidget(toPortalLabel, 3,0);
//    toPortalComboBox.addActionListener(e -> {
    connect(fromPortalComboBox, &JComboBox::currentIndexChanged, [=]{
        if ((toPortalComboBox->getItemCount() > 0) && (fromPortalComboBox->getSelectedItem() != "") &&
                (toPortalComboBox->getSelectedItem() != "")
                && (fromPortalComboBox->getSelectedItem() == (toPortalComboBox->getSelectedItem()))) {
            log->debug("resetting ToPortal");
            fromPortalComboBox->setSelectedIndex(0); // clear the other one
        }
    });
    layout->addWidget(toPortalComboBox, 3, 1);

    // row 5
//        JPanel p3 = new JPanel();
//        p3.setLayout(new BoxLayout(p3, BoxLayout.LINE_AXIS));
//        p3.add(Box.createHorizontalGlue());
    // copied from beanedit, also in BlockPathEditFrame
    lengthSpinner->setModel(
            new SpinnerNumberModel((0.), (0.), (1000.), (0.01)));
//    lengthSpinner->setEditor(new JSpinner::NumberEditor(lengthSpinner, "###0.00"));
    lengthSpinner->resize( JTextField(8).sizeHint());
    lengthSpinner->setValue(0.); // reset from possible previous use

    QButtonGroup* bg = new QButtonGroup(this);
    bg->addButton(inch);
    bg->addButton(cm);

    p1 = new JPanel(new FlowLayout());
    p1->layout()->addWidget(inch);
    p1->layout()->addWidget(cm);
    //p1->setLayout(new QVBoxLayout());//p1, BoxLayout.PAGE_AXIS));
    inch->setChecked(true);
//    inch.addActionListener(e -> {
    connect(inch, &QRadioButton::clicked, [=]{
        cm->setChecked(!inch->isChecked());
        updateLength();
    });
//    cm.addActionListener(e -> {
    connect(cm, &QRadioButton::clicked, [=]{
        inch->setChecked(!cm->isChecked());
        updateLength();
    });
    layout->addWidget(p1);

    JPanel* p2 = new JPanel(new FlowLayout);
    p2->layout()->addWidget(lengthSpinner);
    lengthSpinner->setToolTip( tr("LengthToolTip %1").arg(tr("Path")));
    layout->addWidget(p2);

    p->layout()->addWidget(configGrid);

    JPanel* totbl = new JPanel();
    totbl->setLayout(new BorderLayout(/*10, 10*/));
    totbl->setBorder(BorderFactory::createLineBorder(Qt::black));
    ((BorderLayout*)totbl->layout())->addWidget(_turnoutTablePane, BorderLayout::Center);
    p->layout()->addWidget(totbl);

    p2 = new JPanel();
    QFont f = statusBar->font();
    f.setPointSize(0.9f * blockName->font().pointSizeF());
    statusBar->setFont(f); // a bit smaller
    statusBar->setForeground(Qt::gray);
    p2->layout()->addWidget(statusBar);
    p->layout()->addWidget(p2);

    p->layout()->addWidget(Box::createVerticalGlue());

    p2 = new JPanel();
    p2->setLayout(new QHBoxLayout());//p2, BoxLayout.LINE_AXIS));
    JButton* cancel;
    p2->layout()->addWidget(cancel = new JButton( tr("Cancel")));
    //cancel.addActionListener((ActionEvent e) -> closeFrame());
    connect(cancel, &JButton::clicked, [=]{closeFrame();});
    JButton* ok;
    p2->layout()->addWidget(ok = new JButton( tr("OK")));
    //ok.addActionListener(this::createPressed);
    connect(ok, &JButton::clicked, [=]{createPressed();});
    ((BorderLayout*)p->layout())->addWidget(p2, BorderLayout::South);

    frame->getContentPane()->layout()->addWidget(p);
}

/**
 * Populate the Edit OBlock frame with default values.
 */
/*public*/ void BlockPathEditFrame::resetFrame() {
    pathUserName->setText("");
    if (toPortalComboBox->getItemCount() < 2) {
        status( tr("To set up a Path, define at least 2 Portals."), true);
    } else {
        status( tr("To create a new %1, enter its definition, then click [%2].").arg(tr("Path")).arg(tr("Create")),
                false); // I18N to include original button name in help string
    }
    lengthSpinner->setValue(0.0);
    _newPath = true;
}

/**
 * Populate the Edit Path frame with current values.
 *
 * @param p existing OPath to copy the attributes from
 */
/*public*/ void BlockPathEditFrame::populateFrame(OPath* p) {
    if (p == nullptr) {
        throw  IllegalArgumentException("Null OPath object");
    }
    pathUserName->setText(p->getName());
    if (p->getFromPortal() != nullptr) {
        log->debug(tr("BPEF FROMPORTAL name = %1").arg(p->getFromPortal()->getName()));
        fromPortalComboBox->setSelectedItem(p->getFromPortal()->getName());
    }
    if (p->getToPortal() != nullptr) {
        log->debug(tr("BPEF TOPORTAL name = %1").arg(p->getToPortal()->getName()));
        toPortalComboBox->setSelectedItem(p->getToPortal()->getName());
    }
    if (_block->isMetric()) {
        cm->setChecked(true);
        lengthSpinner->setValue(_path->getLengthCm());
    } else {
        inch->setChecked(true); // set first while length = 0 to prevent recalc
        lengthSpinner->setValue(_path->getLengthIn());
    }
    status( tr("To change this %1, make changes above, then click [%2].").arg(tr("Path")).arg(tr("OK")), false);
    _newPath = false;
}

/*private*/ void BlockPathEditFrame::createPressed(/*JActionEvent e*/) {
    QString user = pathUserName->text().trimmed();
    if (user == ("") || (_newPath && _block->getPathByName(user) != nullptr)) { // check existing names before creating
        status(user == ("") ?  tr("System Name field can not be left blank.") :  tr("Duplicate name. Path \"%1\" has already been defined.").arg(user), true);
        pathUserName->setBackground(Qt::red);
        return;
    }
    if (_newPath) {
        Portal* fromPortal = _block->getPortalByName( fromPortalComboBox->getSelectedItem());
        Portal* toPortal = _block->getPortalByName( toPortalComboBox->getSelectedItem());
        if (fromPortal != nullptr || toPortal != nullptr) {
            _path = new OPath(user, _block, fromPortal, toPortal, QList<BeanSetting*>());
            if (!_block->addPath(_path)) {
                status( tr("Failed to add Path on Portal %1").arg(user), true);
            } else {
                _pathmodel->initTempRow();
                _core->updateOBlockTablesMenu();
                _pathmodel->fireTableDataChanged();
                closeFrame(); // success
            }
        }
    } else if (_path->getName() != (user)) {
        _path->setName(user); // name change on existing path
    }
    try { // adapted from BlockPathTableModel setValue
        if (fromPortalComboBox->getSelectedIndex() <= 0) {
            // 0 = empty choice, need at least 1 Portal
            if (toPortalComboBox->getSelectedIndex() > 0) {
                _path->setFromPortal(nullptr); // portal can be removed from path by setting to null but we want at least 1
            } else {
                status( tr("A Path in a Block requires at least 1 Portal"), true);
                return;
            }
        } else {
            QString fromP =  fromPortalComboBox->getSelectedItem();
            log->debug(tr("looking for FromPortal %1").arg(fromP));
            Portal* fromPortal = _block->getPortalByName(fromP);
            if (fromPortal == nullptr || pm->getPortal(fromP) == nullptr) {
                int val = _core->verifyWarning( tr("No Portal named \"%1\" is found in Block \"%2\". Do you want to\ncreate a new portal called \"%1\" for Block \"%2\"?").arg(fromP).arg(_block->getDisplayName()));
                if (val == 2) {
                    return; // abort
                }
                fromPortal = pm->providePortal(fromP);
                if (!fromPortal->setFromBlock(_block, false)) {
                    val = _core->verifyWarning( tr("If you make this change, please verify path connections in blocks %1 and %2.").arg(fromP).arg(fromPortal->getFromBlockName()));
                    if (val == 2) {
                        return;
                    }
                }
                fromPortal->setFromBlock(_block, true);
            }
            _path->setFromPortal(fromPortal);
            if (!fromPortal->addPath(_path)) {
                status( tr("Failed to add Path on Portal %1").arg(fromP), true);
                return;
            }
        }

        if (toPortalComboBox->getSelectedIndex() <= 0) {
            // 0 = empty choice, need at least 1 Portal
            if (fromPortalComboBox->getSelectedIndex() > 0) {
                _path->setToPortal(nullptr); // portal can be removed from path by setting to null
            } else {
                status( tr("A Path in a Block requires at least 1 Portal"), true);
                return;
            }
        } else {
            QString toP =  toPortalComboBox->getSelectedItem();
            log->debug(tr("looking for ToPortal %1").arg(toP));
            Portal* toPortal = _block->getPortalByName(toP);
            if (toPortal == nullptr || pm->getPortal(toP) == nullptr) {
                int val = _core->verifyWarning( tr("No Portal named \"%1\" is found in Block \"%2\". Do you want to\ncreate a new portal called \"%1\" for Block  \"%2\"?").arg(toP).arg(_block->getDisplayName()));
                if (val == 2) {
                    return; // abort
                }
                toPortal = pm->providePortal(toP);
                if (!toPortal->setFromBlock(_block, false)) {
                    val = _core->verifyWarning( tr("If you make this change, please verify path connections in blocks {0} %1and %2.").arg(toP).arg(toPortal->getFromBlockName()));
                    if (val == 2) {
                        return;
                    }
                }
                toPortal->setToBlock(_block, true);
                _path->setToPortal(toPortal);
                if (!toPortal->addPath(_path)) {
                    status( tr("Failed to add Path on Portal %1").arg(toP), true);
                    return;
                }
            }
        }

        _path->setLength((float) lengthSpinner->getValue() * (cm->isChecked() ? 10.0f : 25.4f)); // stored in mm
        _block->setMetricUnits(cm->isChecked());
    } catch (IllegalArgumentException ex) {
        JOptionPane::showMessageDialog(this, ex.getMessage(),  tr("Path Create Error"), JOptionPane::ERROR_MESSAGE);
        status( tr("Failed to add Path on Portal %1").arg(user), true);
        return;
    }
    // Notify changes
    if (_pathmodel != nullptr) {
        _pathmodel->fireTableDataChanged();
    }
    _core->setPathEdit(false);
    log->debug("BlockPathEditFrame.createPressed pathEdit=False");
    closeFrame();
}

/*protected*/ void BlockPathEditFrame::closeFrame(){
    // remind to save, if Path was created or edited
    if (isDirty) {
        showReminderMessage();
        isDirty = false;
    }
    // hide addFrame
    setVisible(false);

    if (_tomodel != nullptr) {
        _tomodel->dispose();
    }
    _core->setPathEdit(false);
    log->debug("BlockPathEditFrame.closeFrame pathEdit=False");
    this->dispose();
}

/*protected*/ void BlockPathEditFrame::showReminderMessage() {
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            showInfoMessage(tr("Reminder"),  // NOI18N
                    tr("<html>Remember to save your %1 information in your Configuration.<br>(choose Store &gt; Store Configuration... from the File menu)</html>").arg(tr("MenuItemOBlockTable")),  // NOI18N
                    "BlockPathEditFrame", "remindSaveOBlock"); // NOI18N
}

// copied from beanedit, also used in BlockPathEditFrame
/*private*/ void BlockPathEditFrame::updateLength() {
    float len = (float) lengthSpinner->getValue();
    if (inch->isChecked()) {
        lengthSpinner->setValue(len/2.54f);
    } else {
        lengthSpinner->setValue(len*2.54f);
    }
}

void BlockPathEditFrame::status(QString message, bool warn){
    statusBar->setText(message);
    statusBar->setForeground(warn ? Qt::red : Qt::gray);
}

// listen for frame closing
void BlockPathEditFrame::addCloseListener(JmriJFrame* frame) {
//    frame.addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            _core.setPathEdit(false);
//            log.debug("BlockPathEditFrame.closeFrame pathEdit=False");
//            frame.dispose();
//        }
//    });
 frame->addWindowListener(new BPEFCloseListener(this));
}

/*private*/ /*static*/ /*final*/ Logger* BlockPathEditFrame::log = LoggerFactory::getLogger("BlockPathEditFrame");
