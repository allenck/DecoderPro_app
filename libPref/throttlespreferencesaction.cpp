#include "throttlespreferencesaction.h"
#include "instancemanager.h"
#include "throttleframemanager.h"

ThrottlesPreferencesAction::ThrottlesPreferencesAction(QObject *parent) :
    QAction("Throttles preferences", parent)
{
}
// /*public*/ class ThrottlesPreferencesAction extends AbstractAction {
/**
 * Constructor
 * @param s Name for the action.
 */
/*public*/ ThrottlesPreferencesAction::ThrottlesPreferencesAction(QString s, QObject *parent) : QAction(s, parent){
 //   super(s);
// disable the ourselves if there is no throttle Manager
 if (InstanceManager::throttleManagerInstance()==NULL)
 {
  setEnabled(false);
 }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

///*public*/ ThrottlesPreferencesAction() {
//  this("Throttles preferences");
//}

/*public*/ void ThrottlesPreferencesAction::actionPerformed(ActionEvent* /*e*/) {
    ((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->showThrottlesPreferences();
}
