#include "portaleditframe.h"
#include "loggerfactory.h"
#include "portal.h"
#include "box.h"
#include "jbutton.h"
#include "joptionpane.h"

/**
 * Defines a GUI for editing OBlocks - Portal objects in the _tabbed OBlock Table interface.
 * Based on AudioSourceFrame.
 *
 * @author Matthew Harris copyright (c) 2009
 * @author Egbert Broerse (C) 2020
 */
///*public*/ class PortalEditFrame extends JmriJFrame {


///*private*/ /*final*/ JScrollPane scroll = new JScrollPane(main, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);

///*private*/ /*final*/ Object lock = new Object();


//@SuppressWarnings("OverridableMethodCallInConstructor")
/*public*/ PortalEditFrame::PortalEditFrame(/*@Nonnull*/ QString title, Portal* portal, PortalTableModel* model, QWidget* parent)
 : JmriJFrame(title, true, true, parent)
{
    //super(title, true, true);
    this->model = model;
    pm = (PortalManager*)InstanceManager::getDefault("PortalManager");
    layoutFrame();
    if (portal == nullptr) {
        resetFrame();
        setTitle(tr("Add Portal"));
        _newPortal = true;
    } else {
        _portal = portal;
        populateFrame(portal);
    }
}

/*public*/ void PortalEditFrame::layoutFrame() {
    frame->addHelpMenu("package.jmri.jmrit.beantable.OBlockTable", true);
    frame->getContentPane()->setLayout(new QVBoxLayout());//frame.getContentPane(), BoxLayout.PAGE_AXIS));
    frame->resize(425, 225);

    JPanel* p = new JPanel();
    p->setLayout(new QVBoxLayout());//p, BoxLayout.PAGE_AXIS));

    JPanel* configGrid = new JPanel();
    QGridLayout* layout = new QGridLayout();//3, 2, 10, 0); // (int rows, int cols, int hgap, int vgap)
    configGrid->setLayout(layout);

    // row 1
    configGrid->layout()->addWidget(portalLabel);
    JPanel* p1 = new JPanel(new QVBoxLayout);
    ((QVBoxLayout*)p1->layout())->addWidget(portalUserName, 0, Qt::AlignCenter);
    configGrid->layout()->addWidget(p1);
    // row 2
    //fromBlockComboBox->addActionListener(e -> {
    connect(fromBlockComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
        if ((toBlockComboBox->getItemCount() > 0) && (fromBlockComboBox->getSelectedItem() != nullptr) &&
                (toBlockComboBox->getSelectedItem() != nullptr) &&
                (toBlockComboBox->getSelectedItem() == fromBlockComboBox->getSelectedItem())) {
            log->debug("resetting ToBlock");
            toBlockComboBox->setSelectedIndex(0); // clear the other one
        }
    });
    configGrid->layout()->addWidget(fromBlockLabel);
    configGrid->layout()->addWidget(fromBlockComboBox);
    fromBlockComboBox->setAllowNull(true);
    // row 3
//    toBlockComboBox->addActionListener(e -> {
    connect(toBlockComboBox, &NamedBeanComboBox::currentIndexChanged, [=]{
        if ((toBlockComboBox->getItemCount() > 0) && (fromBlockComboBox->getSelectedItem() != nullptr) &&
                (toBlockComboBox->getSelectedItem() != nullptr) &&
                (toBlockComboBox->getSelectedItem() ==(fromBlockComboBox->getSelectedItem()))) {
            log->debug("resetting FromBlock");
            fromBlockComboBox->setSelectedIndex(0); // clear the other one
        }
    });
    configGrid->layout()->addWidget(toBlockLabel);
    configGrid->layout()->addWidget(toBlockComboBox);
    toBlockComboBox->setAllowNull(true);

    p->layout()->addWidget(configGrid);
    p->layout()->addWidget(Box::createVerticalGlue());

    p1 = new JPanel();
//    statusBar.setFont(statusBar.getFont().deriveFont(0.9f * portalUserName.getFont().getSize())); // a bit smaller
    statusBar->setForeground(Qt::gray);
    p1->layout()->addWidget(statusBar);
    p1->layout()->addWidget(p1);

    // put buttons at the bottom
    JPanel* p2 = new JPanel();
    JButton* cancel;
    p2->layout()->addWidget(cancel = new JButton(tr("Cancel")));
    //cancel.addActionListener((ActionEvent e) -> frame.dispose());
    connect(cancel, &JButton::clicked, [=]{
     frame->dispose();
    });

    JButton* ok;
    p2->layout()->addWidget(ok = new JButton(tr("OK")));
    //ok.addActionListener((ActionEvent e) -> {
    connect(ok, &JButton::clicked, [=]{
        applyPressed(/*e*/);
    });
    p->layout()->addWidget(p2);//, BorderLayout.SOUTH);

    main->layout()->addWidget(p);
    frame->getContentPane()->layout()->addWidget(main);
}

/**
 * Populate the Edit OBlock frame with default values.
 */
/*public*/ void PortalEditFrame::resetFrame() {
    portalUserName->setText("");
    portalUserName->setBackground(Qt::white);
    if (fromBlockComboBox->getItemCount() > 0) {
        fromBlockComboBox->setSelectedIndex(0);
        toBlockComboBox->setSelectedIndex(0); // the combos use the same list so 1 check is sufficient
    }
    // reset statusBar text
    if (fromBlockComboBox->getItemCount() < 2) {
        status(tr("To set up a Portal, define at least 2 OBlocks."), true);
    } else {
        status(tr("Enter a unique Name"), false);
    }
    _newPortal = true;
}

/**
 * Populate the Edit Portal frame with current values.
 *
 * @param p existing Portal to copy the attributes from
 */
/*public*/ void PortalEditFrame::populateFrame(Portal* p) {
    if (p == nullptr) {
        throw IllegalArgumentException("Null OBlock object");
    }
    portalUserName->setText(p->getName());
    if (p->getFromBlockName() != nullptr) {
        fromBlockComboBox->setSelectedItemByName(p->getFromBlockName());
    }
    if (p->getToBlockName() != nullptr) {
        toBlockComboBox->setSelectedItemByName(p->getToBlockName());
    }
    _newPortal = false;
}

/*private*/ void PortalEditFrame::applyPressed(JActionEvent* e) {
    QString user = portalUserName->text().trimmed();
    if (user ==("")) {
        // warn/help bar red
        status(tr("WarningSysNameEmpty"), true);
        portalUserName->setBackground(Qt::red);
        return;
    }
    portalUserName->setBackground(Qt::white);
    status(tr("AddPortalStatusEnter"), false);
    if (fromBlockComboBox->getSelectedIndex() == -1 || toBlockComboBox->getSelectedIndex() == -1) {
        status(tr("Portal \"%1\" needs to have a Block specified on each side.").arg(user), true);
        return;
    }
    if (_newPortal) {
        _portal = pm->createNewPortal(user);
        if (_portal == nullptr) { // pm found an existing portal by the same name
            // warn/help bar red
            status(tr("WarningSysNameInUse"), true);
            portalUserName->setBackground(Qt::red);
            return;
        }
    } else {
        QString msg = _portal->setName(user); // will check for duplicates
        if (msg != "") {
            status(msg, true);
            return;
        }
    }
    try {
        OBlock* block = (OBlock*)fromBlockComboBox->getSelectedItem();
        if (block != nullptr) { // could have been deleted in JMRI by now?
            // SametoFromBlock is prevented between comboboxes
            if (!_portal->setFromBlock(block, false)) {
                QString msg = tr("If you make this change, please verify path connections in blocks %1 and %2}.").arg(fromBlockComboBox->getSelectedItemDisplayName()).arg(_portal->getFromBlockName());
                int val = model->verifyWarning(msg);
                if (val == 2) {
                    status(msg, true);
                    return;
                } else {
                    status(tr("AddPortalStatusEnter"), false);
                }
            }
            _portal->setFromBlock(block, true);
        }
        block = (OBlock*)toBlockComboBox->getSelectedItem();
        if (block != nullptr) {
            if (!_portal->setToBlock(block, false)) {
                QString msg = tr("If you make this change, please verify path connections in blocks %1 and $2.").arg(fromBlockComboBox->getSelectedItemDisplayName()).arg(_portal->getFromBlockName());
                int val = model->verifyWarning(msg);
                if (val == 2) {
                    status(msg, true);
                    return;
                } else {
                    status(tr("AddPortalStatusEnter"), false);
                }
            }
            _portal->setToBlock(block, true);
        }
    } catch (IllegalArgumentException ex) {
        JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("PortalCreateErrorTitle"), JOptionPane::ERROR_MESSAGE);
        status(tr("Failed to add Portal %1").arg(user), true);
        return;
    }
    // Notify changes
    model->fireTableDataChanged();
    dispose();
}

void PortalEditFrame::status(QString message, bool warn){
    statusBar->setText(message);
    statusBar->setForeground(warn ? Qt::red : Qt::gray);
}

/*private*/ /*static*/ /*final*/ Logger* PortalEditFrame::log = LoggerFactory::getLogger("PortalEditFrame");
