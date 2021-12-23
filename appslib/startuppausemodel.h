#ifndef STARTUPPAUSEMODEL_H
#define STARTUPPAUSEMODEL_H
#include "abstractstartupmodel.h"

class Logger;
class StartupPauseModel : public AbstractStartupModel
{
 Q_OBJECT
public:
 StartupPauseModel(QObject* parent = 0);
 ~StartupPauseModel() {}
 StartupPauseModel(const StartupPauseModel&) :AbstractStartupModel() {}
 /*public*/ static /*final*/ int DEFAULT_DELAY;// = 10;
 /*public*/ QString getName();
 /*public*/ bool isValid();
 /*public*/ int getDelay();
 /*public*/ void setDelay(int delay);
 /*public*/ void performAction(QString) /*throw (JmriException)*/;

private:
 /*private*/ int delay;// = -1; // default to invalid duration
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("StartupPauseModel");

};
Q_DECLARE_METATYPE(StartupPauseModel)
#endif // STARTUPPAUSEMODEL_H
