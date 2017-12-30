#ifndef TRIGGERROUTEMODEL_H
#define TRIGGERROUTEMODEL_H
#include "abstractstartupmodel.h"
#include "../libPr3/route.h"
#include "../libPr3/routemanager.h"

class Logger;
class TriggerRouteModel : public AbstractStartupModel
{
public:
 TriggerRouteModel();
 /*public*/ QString getUserName();
 /*public*/ void setUserName(QString name);
 /*public*/ Route* getRoute();
 /*public*/ void performAction() throw (JmriException);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TriggerRouteModel.class);

};

#endif // TRIGGERROUTEMODEL_H
