#ifndef INTERNALTURNOUTMANAGER_H
#define INTERNALTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"

class InternalTurnoutManager : public AbstractTurnoutManager
{
 Q_OBJECT
public:
 InternalTurnoutManager();
 /*public*/ QString getSystemPrefix();
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
 /*public*/ QStringList getValidOperationTypes();
protected:
/*protected*/ Turnout* createNewTurnout(QString systemName, QString userName);
/*protected*/ QString prefix; // = "I";

};

#endif // INTERNALTURNOUTMANAGER_H
