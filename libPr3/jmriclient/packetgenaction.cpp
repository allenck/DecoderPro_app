#include "packetgenaction.h"
#include "jmriclientsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "packetgenframe.h"
/**
 * Swing action to create and register a PacketGenFrame object
 *
 * @author Bob Jacobsen Copyright (C) 2008
 */
// /*public*/ class PacketGenAction extends AbstractAction {


/*public*/ PacketGenAction::PacketGenAction(QString s, JMRIClientSystemConnectionMemo* memo, QObject* parent)
 : AbstractAction(s,parent) {
   // super(s);
    _memo = memo;
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ PacketGenAction::PacketGenAction(JMRIClientSystemConnectionMemo* memo, QWidget* parent)
 : AbstractAction("Generate JMRI Client message",  parent)
{
   // this("Generate JMRI Client message", memo);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

//@Override
/*public*/ void PacketGenAction::actionPerformed(/*ActionEvent e*/) {
    PacketGenFrame* f = new PacketGenFrame();
    try {
        f->initComponents();
    } catch (Exception* ex) {
        log->error("Exception: " + ex->getMessage());
    }

    // connect to the traffic controller
    f->_connect(_memo->getJMRIClientTrafficController());
    f->setVisible(true);
}
/*private*/ /*final*/ /*static*/ Logger* PacketGenAction::log = LoggerFactory::getLogger("PacketGenAction");
