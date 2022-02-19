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
 /*public*/ SystemConnectionMemo* getMemo() override;
 /*public*/ bool allowMultipleAdditions(QString systemName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix)  /*throw (JmriException)*/ override;
 /*public*/ QStringList getValidOperationTypes() override;
 /*public*/ QString getEntryToolTip() override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Turnout";
 }
 /*public*/ QString toString() {return "InternalTurnoutManager";}
  QObject* self() override {return (QObject*)this;}
  QObject* vself() override { return (QObject*)this;}

protected:
/*protected*/ Turnout* createNewTurnout(QString systemName, QString userName) ;
/*protected*/ QString prefix; // = "I";

};
class AbstractTurnoutO1 : public AbstractTurnout
{
 Q_OBJECT
public:
 AbstractTurnoutO1(QString systemName, QString userName) : AbstractTurnout(systemName, userName) {}
protected:
 //@Override
 /*protected*/ void forwardCommandChangeToLayout(int /*s*/)  override{
 }

 //@Override
 /*protected*/ void turnoutPushbuttonLockout(bool /*b*/) override {
 }

protected:
};
#endif // INTERNALTURNOUTMANAGER_H
