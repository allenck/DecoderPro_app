#ifndef STARTUPPAUSEMODEL_H
#define STARTUPPAUSEMODEL_H
#include "abstractstartupmodel.h"

class Logger;
class StartupPauseModel : public AbstractStartupModel
{
public:
 StartupPauseModel();
 /*public*/ static /*final*/ int DEFAULT_DELAY;// = 10;
 /*public*/ QString getName();
 /*public*/ bool isValid();
 /*public*/ int getDelay();
 /*public*/ void setDelay(int delay);
 /*public*/ void performAction() throw (JmriException);

private:
 /*private*/ int delay;// = -1; // default to invalid duration
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("StartupPauseModel");

};

#endif // STARTUPPAUSEMODEL_H
