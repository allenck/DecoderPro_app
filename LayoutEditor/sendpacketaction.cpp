#include "sendpacketaction.h"
#include "instancemanager.h"
#include "sendpacketframe.h"

//SendPacketAction::SendPacketAction(QObject *parent) :
//  AbstractAction(tr("Send Packet"), parent)
//{
// common();
//}
/**
 * Swing action to create and register a SendPacketFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2003
 * @version $Revision: 28746 $
 */
///*public*/ class SendPacketAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -3000436999151726193L;

/*public*/ SendPacketAction::SendPacketAction(QString s, QObject *parent) :
  AbstractAction(s, parent)
{
    //super(s);
common();
}
void SendPacketAction::common()
{
    // disable ourself if there is no command Station object available
    if (InstanceManager::getDefault("CommandStation") == nullptr) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SendPacketAction::SendPacketAction(QObject *parent) :
  AbstractAction(tr("Send DCC packet"), parent) {
    //this("Send DCC packet");
 common();
}

/*public*/ void SendPacketAction::actionPerformed(JActionEvent * /*e*/) {
    // create a SendPacketFrame
    SendPacketFrame* f = new SendPacketFrame();
    try {
        f->initComponents();
    } catch (Exception ex) {
        Logger::error("Exception: " /*+ ex.toString()*/);
    }
    f->setVisible(true);
}
