#include "triggerroutemodelfactory.h"
#include "loggerfactory.h"
#include "triggerroutemodel.h"
#include "instancemanager.h"
#include "joptionpane.h"
#include "startupactionsmanager.h"
#include "../libPr3/route.h"
#include "../libPr3/routemanager.h"
#include "defaultroute.h"

TriggerRouteModelFactory::TriggerRouteModelFactory()
{
 setObjectName("TriggerRouteModelFactory");
}
/**
 * Factory to create {@link apps.startup.TriggerRouteModel} objects.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class TriggerRouteModelFactory implements StartupModelFactory {

/*private*/ /*final*/ /*static*/ Logger* TriggerRouteModelFactory::log = LoggerFactory::getLogger("TriggerRouteModelFactory");

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString TriggerRouteModelFactory::getModelClass() {
    return "TriggerRouteModel";
}

//@Override
/*public*/ QString TriggerRouteModelFactory::getDescription() {
    //return Bundle.getMessage(this->getModelClass().getCanonicalName());
 return tr("Set route");
}

//@Override
/*public*/ QString TriggerRouteModelFactory::getActionText() {
    return tr("%1...").arg(this->getDescription()); // NOI18N
}

//@Override
/*public*/ StartupModel* TriggerRouteModelFactory::newModel() {
    return (StartupModel*)new TriggerRouteModel();
}

//@Override
/*public*/ void TriggerRouteModelFactory::editModel(StartupModel* model, QWidget* parent)
{
#if 1
 //if (this->getModelClass().isInstance(model))
 if(Class::forName(this->getModelClass())->isInstance(model))
 {
  QList<QString> userNames = QStringList();
  //((RouteManager*)InstanceManager::getDefault("RouteManager")).getSystemNameList().stream().forEach((systemName) ->
  foreach(QString systemName, ((RouteManager*)InstanceManager::getDefault("RouteManager"))->getSystemNameList())
  {
      Route* r = (Route*)((RouteManager*)InstanceManager::getDefault("RouteManager"))->getBySystemName(systemName);
      if (r != NULL) {
          QString userName = ((DefaultRoute*)r)->getUserName();
          if (userName != NULL && !userName.isEmpty()) {
              userNames.append(userName);
          }
      } else {
          log->error(tr("Failed to get route %1").arg(systemName));
      }
  }//);
//  userNames.sort(NULL);
  QList<QVariant> vl = QList<QVariant>();
  foreach (QString sn, userNames) {
   vl.append(QVariant(sn));
  }
  QVariant name = JOptionPane::showInputDialog(parent, tr("<html><strong>Select a route to set when the application starts.</strong><br><br>Ensure the panel containing the route is loaded before the route is set.<br>Only routes with user names can be automatically set.</html>"), // NOI18N
          this->getDescription(),
          JOptionPane::PLAIN_MESSAGE,
          QIcon(),
          vl, //userNames.toArray(new String[userNames.size()]),
          model->getName());
  if (name.toString() != "" && name.toString() != (model->getName())) {
      model->setName(name.toString());
      ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->setRestartRequired();
  }
 }
#endif
}

//@Override
/*public*/ void TriggerRouteModelFactory::initialize() {
    // nothing to do
}
