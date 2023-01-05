#include "throttleslistaction.h"
#include "instancemanager.h"
#include "throttleframemanager.h"

//ThrottlesListAction::ThrottlesListAction(QObject *parent) :
//  QAction(parent)
//{
//}
// /*public*/ class ThrottlesListAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 6318756102854541505L;

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ ThrottlesListAction::ThrottlesListAction(QString s, QObject *parent) :
  QAction(s, parent)
{
 //super(s);
 common();
}

void ThrottlesListAction::common()
{
 // disable the ourselves if there is no throttle Manager
 if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr)
 {
  setEnabled(false);
 }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ ThrottlesListAction::ThrottlesListAction(QObject *parent) :
  QAction(tr("Throttles list"), parent)
{
 //this("Throttles list");
 common();
}

/*public*/ void ThrottlesListAction::actionPerformed(ActionEvent* /*e*/) {
    ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->showThrottlesList();
}
