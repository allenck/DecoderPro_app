#include "simplelightctrlaction.h"
#include "instancemanager.h"
#include "lightmanager.h"
#include "simplelightctrlframe.h"

//SimpleLightControlAction::SimpleLightControlAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
///*public*/ class SimpleLightCtrlAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 4405267193635229462L;

/*public*/ SimpleLightCtrlAction::SimpleLightCtrlAction(QString s, QObject *parent) :
  AbstractAction(s, parent) {
    //super(s);
 common();
}

void SimpleLightCtrlAction::common()
{

    // disable ourself if there is no primary light manager available
    if (InstanceManager::lightManagerInstance() == NULL) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SimpleLightCtrlAction::SimpleLightCtrlAction(QObject *parent) :
  AbstractAction(tr("Lights"), parent){
    //this("Lights");
 common();
}

/*public*/ void SimpleLightCtrlAction::actionPerformed(JActionEvent * /*e*/) {

    SimpleLightCtrlFrame* f = new SimpleLightCtrlFrame();
    f->setVisible(true);

}
