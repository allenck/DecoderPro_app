#include "lncvprogaction.h"
#include "jmrijframeinterface.h"
#include "instancemanager.h"

/**
 *
 * @author Egbert Broerse Copyright 2020
 */
///*public*/ class LncvProgAction extends LnNamedPaneAction {

/*public*/ LncvProgAction::LncvProgAction(QObject *parent)
 : LnNamedPaneAction(tr("Configure LNCV Modules"), new JmriJFrameInterface(),"LncvProgPane", (LocoNetSystemConnectionMemo*)InstanceManager::getDefault("LocoNetSystemConnectionMemo")/*, parent*/){
    //super(Bundle.getMessage("MenuItemLncvProg"),
//            new JmriJFrameInterface(),
//            LncvProgPane.class.getName(),
//            InstanceManager.getDefault(LocoNetSystemConnectionMemo.class));
}

//}
