#include "clockmonpane.h"
#include <QPushButton>
#include "jtextfield.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QLabel>
#include "loconetsystemconnectionmemo.h"
#include "slotmanager.h"

ClockMonPane::ClockMonPane(QWidget *parent) :
  LnPanel(parent)
{
 log = new Logger("ClockMonPane");
 days = new JTextField("00",2);
 hours = new JTextField("00",2);
 minutes = new JTextField("00",2);
 frac_mins = new JTextField("00",2);

 rate = new JTextField(4);

 readButton = new QPushButton("Read");

}
/**
 * Pane displaying a LocoNet clock monitor.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 * <P>
 * The original module has been converted to a clock monitor by removing all
 * active items (Dave Duchamp 2007-2008).
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2004, 2010
 * @version	$Revision: 28746 $
 */
///*public*/ class ClockMonPane extends LnPanel implements SlotListener {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 6741586521030027827L;

/*public*/ QString ClockMonPane::getHelpTarget() {
    return "package.jmri.jmrix.loconet.clockmon.ClockMonFrame";
}

/*public*/ QString ClockMonPane::getTitle() {
    return LnPanel::getTitle(tr("Monitor Clock"));
}

///*public*/ ClockMonPane() {
//    super();
//}

/*public*/ void ClockMonPane::initComponents(/*final*/ LocoNetSystemConnectionMemo* memo)
{
 LnPanel::initComponents(memo);

 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 // add GUI items
 QWidget* panel1 = new QWidget();
 FlowLayout* panel1Layout;
 panel1->setLayout(panel1Layout = new FlowLayout());
 panel1Layout->addWidget(new QLabel(" Day:"));
 panel1Layout->addWidget(days);
 panel1Layout->addWidget(new QLabel(" Time:"));
 panel1Layout->addWidget(hours);
 panel1Layout->addWidget(new QLabel(":"));
 panel1Layout->addWidget(minutes);
 panel1Layout->addWidget(new QLabel("."));
 panel1Layout->addWidget(frac_mins);
 thisLayout->addWidget(panel1);

 QWidget* panel2 = new QWidget();
 FlowLayout* panel2Layout;
 panel2->setLayout(panel2Layout = new FlowLayout());
 panel2Layout->addWidget(new QLabel(" Rate:"));
 panel2Layout->addWidget(rate);
 thisLayout->addWidget( panel2);

 QWidget* panel3 = new QWidget();
 FlowLayout* pane3Layout;
 panel3->setLayout(pane3Layout =new FlowLayout());
 pane3Layout->addWidget(readButton);
 thisLayout->addWidget(panel3);
 // Load GUI element contents with current slot contents
 notifyChangedSlot(memo->getSlotManager()->slot(LnConstants::FC_SLOT));

 // install "read" button handler
//    readButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            memo.getSlotManager().sendReadSlot(LnConstants.FC_SLOT);
//        }
//    }
//    );
 connect(readButton, SIGNAL(clicked()), this, SLOT(On_readButton_clicked()));
 // listen for updated slot contents
 if (memo->getSlotManager() != NULL)
 {
  //memo->getSlotManager()->addSlotListener(this);
  connect(memo->getSlotManager(), SIGNAL(changedSlot(LocoNetSlot*)), this, SLOT(notifyChangedSlot(LocoNetSlot*)));
 } else {
     log->error("No LocoNet connection available, can't function");
 }

}
 void ClockMonPane::On_readButton_clicked()
 {
  memo->getSlotManager()->sendReadSlot(LnConstants::FC_SLOT);
 }

/**
 * Handle changed slot contents, due to clock changes.
 *
 * @param s
 */
/*public*/ void ClockMonPane::notifyChangedSlot(LocoNetSlot* s) {
    if (s->getSlot() != LnConstants::FC_SLOT) {
        return; // only watch clock slot
    }
    if (log->isDebugEnabled()) {
        log->debug("slot update " + QString::number(s->getSlot()));
    }

    // update GUI from the new slot contents
    days->setText(QString::number(s->getFcDays()));
    hours->setText(QString::number(s->getFcHours()));
    minutes->setText(QString::number(s->getFcMinutes()));
    rate->setText(QString::number(s->getFcRate()));
    frac_mins->setText(QString::number(s->getFcFracMins()));
}

//@Override
/*public*/ void ClockMonPane::dispose() { 
    // Drop loconet connection
    if (memo->getSlotManager() != NULL) {
        //memo.getSlotManager().removeSlotListener(this);
     disconnect(memo->getSlotManager(), SIGNAL(changedSlot(LocoNetSlot*)), this, SLOT(notifyChangedSlot(LocoNetSlot*)));
    }

    // take apart the JFrame
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
    private static final long serialVersionUID = 2901473960804245354L;

    /*public*/ Default() {
        super(LocoNetBundle.bundle().getString("MenuItemClockMon"),
                new jmri.util.swing.sdi.JmriJFrameInterface(),
                ClockMonPane.class.getName(),
                jmri.InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
    }
}
#endif
