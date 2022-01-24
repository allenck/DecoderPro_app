#ifndef HTMLCONDUCTOR_H
#define HTMLCONDUCTOR_H
#include "htmltraincommon.h"

namespace Operations {


class HtmlConductor : public HtmlTrainCommon
{
public:
 /*public*/ HtmlConductor(QLocale locale, Operations::Train* train, QObject* parent = 0) /*throw (IOException)*/;
 /*public*/ QString getLocation() /*throw (IOException)*/;
 /*private*/ QString getCurrentAndNextLocation();
 /*private*/ QString getMoveButton();
 // needed for location comments, not yet in formatter
 /*private*/ QString getEngineChanges(RouteLocation* location);
 /*private*/ QString getLocationComments() ;
 /*private*/ QString performWork(bool pickup, bool local);
private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("HtmlConductor");
 /*private*/ QString pickupCars();
 /*private*/ QString dropCars(bool local);

};
}
#endif // HTMLCONDUCTOR_H
