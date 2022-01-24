#include "lnmessageserveraction.h"
#include "loggerfactory.h"

LnMessageServerAction::LnMessageServerAction()
{

}
/**
 * Start a LnMessageServer that will listen for clients wanting to use the
 * LocoNet connection on this machine. Copyright: Copyright (c) 2002
 *
 * @author Alex Shepherd
 */
///*public*/ class LnMessageServerAction extends AbstractAction {

/*public*/ LnMessageServerAction::LnMessageServerAction(QString s, QWidget* parent)
: AbstractAction(s, parent){
    //super(s);
}

/*public*/ LnMessageServerAction::LnMessageServerAction(QWidget* parent) : AbstractAction(tr("Start LocoNet server"), parent){
    //super("Start LocoNet server");
}

//@Override
/*public*/ void LnMessageServerAction::actionPerformed(/*ActionEvent e*/) {
#if 0 // TODO:
    try {
        // start server
        LnMessageServer server = LnMessageServer.getInstance();
        server.enable();
        // advertise under zeroconf
        ZeroConfService.create("_jmri-locormi._tcp.local.", 1099).publish();
        // disable action, as already run
        setEnabled(false);
    } catch (RemoteException ex) {
        log.warn("LnMessageServerAction Exception: {}", ex->getMessage()); // NOI18N
    }
#endif
}

/*private*/ /*final*/ /*static*/ Logger* LnMessageServerAction::log = LoggerFactory::getLogger("LnMessageServerAction");
