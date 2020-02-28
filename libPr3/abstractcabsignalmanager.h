#ifndef ABSTRACTCABSIGNALMANAGER_H
#define ABSTRACTCABSIGNALMANAGER_H
#include "cabsignalmanager.h"

class CabSignalListListener;
class AbstractCabSignalManager : public QObject, public CabSignalManager
{
 Q_OBJECT
 Q_INTERFACES(CabSignalManager)
public:
 AbstractCabSignalManager(QObject *parent =0);
 /*public*/ CabSignal* getCabSignal(LocoAddress* address) override;
 /*public*/ void delCabSignal(LocoAddress* address)override;
 /*public*/ QSet<LocoAddress*> getCabSignalList()override;
 /*public*/ QVector<CabSignal*> getCabSignalArray()override;
 /*public*/ void addCabSignalListListener(CabSignalListListener* listener)override;
 /*public*/ void removeCabSignalListListener(CabSignalListListener* listener)override;
 /*public*/ void notifyCabSignalListChanged()override;

private:
 static Logger* log;
 // keep a list of listeners for block objects.
 /*private*/ QList<PropertyChangeListener*> mBlockListeners;
 /*private*/ bool blockInit = false;
 /*private*/ void initBlocks();
 /*private*/ void handleBlockChange(PropertyChangeEvent* e);

protected:
 /*protected*/ QHash<LocoAddress*, CabSignal*> signalList;
 /*protected*/ QList<CabSignalListListener*> listListeners;
 /*abstract*/ /*protected*/ virtual CabSignal* createCabSignal(LocoAddress* address) {return nullptr;}
 friend class ACMPropertyChangeListener;
};

class ACMPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 AbstractCabSignalManager* acm;
public:
 ACMPropertyChangeListener(AbstractCabSignalManager* acm) {this->acm = acm;}
public slots:
 void propertyChange(PropertyChangeEvent* e) override
 {
  acm->handleBlockChange(e);
 }
};
#endif // ABSTRACTCABSIGNALMANAGER_H
