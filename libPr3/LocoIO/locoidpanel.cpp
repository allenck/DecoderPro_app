#include "locoidpanel.h"
#include <QPushButton>
#include <QComboBox>
#include "jtextarea.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QLabel>
#include "loconetsystemconnectionmemo.h"

LocoIdPanel::LocoIdPanel(QWidget *parent) :
  LnPanel(parent)
{
 // member declarations
 IDValues = QStringList() << "-" << "0"<< "1"<< "2"<< "3"<< "4"<< "5"<< "6" << "7";
}
/**
 * User interface for setting the LocoNet ID
 *
 * @author Bob Jacobsen Copyright (C) 2006, 2010
 * @version $Revision: 28746 $
 */
///*public*/ class LocoIdPanel extends jmri.jmrix.loconet.swing.LnPanel implements
//        LocoNetListener {

//    /**
//     *
//     */
//    private static final long serialVersionUID = 4377983464521092360L;
//    /*public*/ LocoIdPanel() {
//        super();
//    }

/*public*/ void LocoIdPanel::initComponents() /*throws Exception*/
{
//        ResourceBundle rb = ResourceBundle
//                .getBundle("jmri.jmrix.loconet.locoid.LocoId");

 // Create our UI elements, two buttons and a drop-down.
 setButton = new QPushButton(tr("Set"));
 readButton = new QPushButton(tr("Read"));
 idBox = new QComboBox(/*IDValues*/);
 idBox->addItems(IDValues);

 // Do our layout, two buttons side by side, drop down below.
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

 QWidget* p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout = new FlowLayout());
 pLayout->addWidget(readButton);
 pLayout->addWidget(setButton);

 thisLayout->addWidget(p);

 p = new QWidget();
 FlowLayout* pLayout2;

 p->setLayout(pLayout2 = new FlowLayout());
 pLayout2->addWidget(new QLabel(tr("Value")));
 pLayout2->addWidget(idBox);

 thisLayout->addWidget(p);

 // Set our callbacks
// setButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         setButtonActionPerformed();
//     }
// });
 connect(setButton, SIGNAL(clicked()), this, SLOT(setButtonActionPerformed()));
// readButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         readButtonActionPerformed();
//     }
// });
 connect(readButton, SIGNAL(clicked()), this, SLOT(readButtonActionPerformed()));
}

/*public*/ QString LocoIdPanel::getHelpTarget() {
    return "package.jmri.jmrix.loconet.locoid.LocoIdFrame";
}

/*public*/ QString LocoIdPanel::getTitle() {
    return LnPanel::getTitle(tr("Set ID"));
}

/*public*/ void LocoIdPanel::initComponents(LocoNetSystemConnectionMemo* memo)
{
    LnPanel::initComponents(memo);

    // connect to the LnTrafficController
    connectTc(memo->getLnTrafficController());

    // press the Read button for the user, so we populate the current value
    readButtonActionPerformed();
}

/**
 * Callback when someone presses the Set button
 */
/*public*/ void LocoIdPanel::setButtonActionPerformed() {
    QString value = idBox->currentText();

    if (value != "-") {
        memo->getLnTrafficController()->sendLocoNetMessage(
                createSetPacket(value));
    }
}

/**
 * Callback when someone presses the Read button
 */
/*public*/ void LocoIdPanel::readButtonActionPerformed() {
    // We set the display to "-" until the callback gets the value from the
    // Loconet
    idBox->setCurrentIndex(0);
    memo->getLnTrafficController()->sendLocoNetMessage(createReadPacket());
}

/**
 * Process the incoming message, see if it is a panel response, and if so
 * parse the LocoNet ID. Use that value to set the ID box.
 *
 * This is the callback called by the LnTrafficController
 *
 * @param m Inbound LocoNet message to check.
 */
/*public*/ void LocoIdPanel::message(LocoNetMessage* m) {

    // The message is 6 bytes long.
    if (m->getNumDataElements() != 6) {
        return;
    }

    int b1 = m->getElement(0) & 0xFF;
    int b2 = m->getElement(1) & 0xFF;
    int b3 = m->getElement(2) & 0xFF;
    int b4 = m->getElement(3) & 0x07; // UR-92's set bit 4 for duplex

    // Response code is D7 {12, 17, 1F} 00 <value>
    if ((b1 == 0xD7)
            && ((b2 == 0x12) || (b2 == 0x17) || (b2 == 0x1F))
            && (b3 == 0x00)) {
        // We start with "-", so index + 1
        idBox->setCurrentIndex(b4 + 1);
    }
}

/**
 * Create a LocoNet packet to Query panels for the LocoNet ID
 *
 * @return The packet, with contents filled-in
 */
LocoNetMessage* LocoIdPanel::createReadPacket() {
    LocoNetMessage* m = new LocoNetMessage(6);
    m->setElement(0, 0xDF);
    m->setElement(1, 0x00);
    m->setElement(2, 0x00);
    m->setElement(3, 0x00);
    m->setElement(4, 0x00);

    return m;
}

/**
 * Create a LocoNet packet to set the LocoNet ID.
 *
 * @param s The desired value as a string in decimal
 * @return The packet, with contents filled-in
 */
LocoNetMessage* LocoIdPanel::createSetPacket(QString s) {
    // convert to int value
    int data = (s).toInt();
    // format packet
    LocoNetMessage* m = new LocoNetMessage(6);
    m->setElement(0, 0xDF);
    m->setElement(1, 0x40);
    m->setElement(2, 0x1F);
    m->setElement(3, data);
    m->setElement(4, 0x00);
    return m;
}

/**
 * Tell the LocoNet controller we want to hear messages, which will
 * automatically call our "message"
 *
 * @param t LocoNet instance to connect to
 */
/*public*/ void LocoIdPanel::connectTc(LnTrafficController* t)
{
 //t.addLocoNetListener(~0, this);
 connect(t, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
}

/*public*/ void LocoIdPanel::dispose() {
    //memo->getLnTrafficController()->removeLocoNetListener(~0, this);
 disconnect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));

 LnPanel::dispose();
}
