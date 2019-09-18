#ifndef INTERNALTURNOUTMANAGER_H
#define INTERNALTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"

class InternalSystemConnectionMemo;
class InternalTurnoutManager : public AbstractTurnoutManager
{
 Q_OBJECT
public:
 QT_DEPRECATED InternalTurnoutManager(QObject* parent = nullptr);
 QT_DEPRECATED /*public*/ InternalTurnoutManager(QString prefix, QObject* parent = nullptr);
 /*public*/ InternalTurnoutManager(InternalSystemConnectionMemo* memo, QObject* parent = nullptr);

 /*public*/ QString getSystemPrefix();
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
 /*public*/ QStringList getValidOperationTypes();
protected:
/*protected*/ Turnout* createNewTurnout(QString systemName, QString userName);
/*protected*/ QString prefix; // = "I";

};

#endif // INTERNALTURNOUTMANAGER_H
