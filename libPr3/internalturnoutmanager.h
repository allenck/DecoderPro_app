#ifndef INTERNALTURNOUTMANAGER_H
#define INTERNALTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"
#include "abstractturnout.h"

class InternalSystemConnectionMemo;
class InternalTurnoutManager : public AbstractTurnoutManager
{
 Q_OBJECT
public:
 QT_DEPRECATED InternalTurnoutManager(QObject* parent = nullptr);
 QT_DEPRECATED /*public*/ InternalTurnoutManager(QString prefix, QObject* parent = nullptr);
 /*public*/ InternalTurnoutManager(InternalSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ SystemConnectionMemo* getMemo();
 /*public*/ bool allowMultipleAdditions(QString systemName);
 /*public*/ QString createSystemName(QString curAddress, QString prefix) const throw (JmriException);
 /*public*/ QStringList getValidOperationTypes();
 /*public*/ QString getEntryToolTip();

protected:
/*protected*/ Turnout* createNewTurnout(QString systemName, QString userName) const;
/*protected*/ QString prefix; // = "I";

};
class AbstractTurnoutO1 : public AbstractTurnout
{
 Q_OBJECT
public:
 AbstractTurnoutO1(QString systemName, QString userName) : AbstractTurnout(systemName, userName) {}
protected:
 //@Override
 /*protected*/ void forwardCommandChangeToLayout(int /*s*/) {
 }

 //@Override
 /*protected*/ void turnoutPushbuttonLockout(bool /*b*/) {
 }

protected:
};
#endif // INTERNALTURNOUTMANAGER_H
