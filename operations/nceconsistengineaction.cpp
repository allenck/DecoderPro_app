#include "nceconsistengineaction.h"

namespace Operations {

 /**
  * Starts the NceConsistEngine thread
  *
  * @author Dan Boudreau Copyright (C) 2008
  */
 // public class NceConsistEngineAction extends AbstractAction {


     /*public*/ NceConsistEngineAction::NceConsistEngineAction(QObject *parent) : AbstractAction(tr("Nce s"), parent){
         //super(Bundle.getMessage("Synchronize with NCE Consists "), parent);
         // only enable if connected to an NCE system
         setEnabled(false);
#if 0
         // disable if NCE USB selected
         // get NceTrafficContoller if there's one
         QList<NceSystemConnectionMemo> memos = InstanceManager.getList(NceSystemConnectionMemo.class);

         // find NceConnection that is serial
         for (NceSystemConnectionMemo memo : memos) {
             if (memo.getNceUsbSystem() == NceTrafficController.USB_SYSTEM_NONE) {
                 tc = memo.getNceTrafficController();
                 if (!memo.getDisabled()) {
                     setEnabled(true);
                 }
             }
         }
#endif
     }

     //@Override
     /*public*/ void NceConsistEngineAction::actionPerformed(JActionEvent* /*ae*/) {
#if 0
         Thread mb = new NceConsistEngines(tc);
         mb.setName("Nce Consist Sync Engines"); // NOI18N
         mb.start();
#endif
     }


} // namespace Operations
