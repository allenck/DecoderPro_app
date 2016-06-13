#include "slotmonpane.h"
#include "loconetsystemconnectionmemo.h"
#include "slotmondatamodel.h"
#include "jtable.h"
#include <QCheckBox>
#include <QPushButton>
#include <QBoxLayout>
#include "flowlayout.h"

SlotMonPane::SlotMonPane(QWidget *parent) :
  LnPanel(parent)
{
 log = new Logger("SlotMonPane");
 showAllCheckBox = new QCheckBox();
 showSystemCheckBox = new QCheckBox();
 estopAllButton = new QPushButton(tr("Estop All"));
 clearAllButton = new QPushButton(tr("Clear All Non-InUse Slots"));
}
/**
 * Frame provinging a command station slot manager.
 * <P>
 * Slots 102 through 127 are normally not used for loco control, so are shown
 * separately.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version	$Revision: 28878 $
 */
// /*public*/ class SlotMonPane extends jmri.jmrix.loconet.swing.LnPanel {

    /**
     *
     */
//    private static final long serialVersionUID = 5149412620444668985L;

///*public*/ SlotMonPane() {
//    super();
//}

/*public*/ void SlotMonPane::initComponents(LocoNetSystemConnectionMemo* memo) {
    LnPanel::initComponents(memo);

    slotModel = new SlotMonDataModel(128, 16, memo);
    //slotTable = JTableUtil.sortableDataModel(slotModel);
    slotTable = new JTable(slotModel);
    //slotScroll = new JScrollPane(slotTable);

    // configure items for GUI
    showAllCheckBox->setText(tr("Show unused slots"));
    showAllCheckBox->setVisible(true);
    showAllCheckBox->setChecked(false);
    showAllCheckBox->setToolTip(tr("TooltipSlotMonShowUnused"));

    showSystemCheckBox->setText(tr("Show system slots"));
    showSystemCheckBox->setVisible(true);
    showSystemCheckBox->setChecked(false);
    showSystemCheckBox->setToolTip(tr("if checked, slots reserved for system use will be shown"));

    slotModel->configureTable(slotTable);

    // add listener object so checkboxes function
//    showAllCheckBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            slotModel.showAllSlots(showAllCheckBox.isSelected());
//            slotModel.fireTableDataChanged();
//        }
//    });
    connect(showAllCheckBox, SIGNAL(clicked()), this, SLOT(On_showAllCheckBox_clicked()));
//    showSystemCheckBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            slotModel.showSystemSlots(showSystemCheckBox.isSelected());
//            slotModel.fireTableDataChanged();
//        }
//    });
    connect(showSystemCheckBox, SIGNAL(clicked()), this, SLOT(On_showSystemCheckBox_clicked()));
    // add listener object so stop all button functions
//    estopAllButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            slotModel.estopAll();
//        }
//    });
    connect(estopAllButton, SIGNAL(clicked()), slotModel, SLOT(estopAll()));
#if 0
    estopAllButton.addMouseListener(new MouseListener() {
        /*public*/ void mousePressed(MouseEvent e) {
            slotModel.estopAll();
        }

        /*public*/ void mouseExited(MouseEvent e) {
        }

        /*public*/ void mouseEntered(MouseEvent e) {
        }

        /*public*/ void mouseReleased(MouseEvent e) {
        }

        /*public*/ void mouseClicked(MouseEvent e) {
        }
    });
#endif
    //Jeffrey 6/29/2013
//    clearAllButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            slotModel.clearAllSlots();
//        }
//    });
    connect(clearAllButton, SIGNAL(clicked()), slotModel, SLOT(clearAllSlots()));
    // adjust model to default settings
    slotModel->showAllSlots(showAllCheckBox->isChecked());
    slotModel->showSystemSlots(showSystemCheckBox->isChecked());

    // general GUI config
    QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

    // install items in GUI
    QWidget* pane1 = new QWidget();
    FlowLayout* panelLayout;
    pane1->setLayout(panelLayout = new FlowLayout());

    panelLayout->addWidget(showAllCheckBox);
    panelLayout->addWidget(showSystemCheckBox);
    panelLayout->addWidget(estopAllButton);
    panelLayout->addWidget(clearAllButton);

    thisLayout->addWidget(pane1);
    thisLayout->addWidget(/*slotScroll*/slotTable);

    // set scroll size
    //pane1->setMaximumSize(new java.awt.Dimension(100,300));
    if (pane1->maximumSize().height() > 0 && pane1->maximumSize().width() > 0) {
        pane1->setMaximumSize(pane1->sizeHint());
    }
}

void SlotMonPane::On_showAllCheckBox_clicked()
{
 slotModel->showAllSlots(showAllCheckBox->isChecked());
 slotModel->fireTableDataChanged();

}
void SlotMonPane::On_showSystemCheckBox_clicked()
{
 slotModel->showSystemSlots(showSystemCheckBox->isChecked());
 slotModel->fireTableDataChanged();

}

/*public*/ QString SlotMonPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.slotmon.SlotMonFrame";
}

/*public*/ QString SlotMonPane::getTitle() {
    return LnPanel::getTitle(tr("Monitor Slots"));
}

/*public*/ void SlotMonPane::dispose() {
    slotModel->dispose();
    slotModel = NULL;
    slotTable = NULL;
    //slotScroll = NULL;
    LnPanel::dispose();
}
#if 0
/**
 * Nested class to create one of these using old-style defaults
 */
static /*public*/ class Default extends jmri.jmrix.loconet.swing.LnNamedPaneAction {

    /**
     *
     */
    private static final long serialVersionUID = 8377346674021280925L;

    /*public*/ Default() {
        super(tr("MenuItemSlotMonitor"),
                new jmri.util.swing.sdi.JmriJFrameInterface(),
                SlotMonPane.class.getName(),
                jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
    }
};
#endif
