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
 /*public*/ CabSignal* getCabSignal(LocoAddress* address);
 /*public*/ void delCabSignal(LocoAddress* address);
 /*public*/ QSet<LocoAddress*> getCabSignalList();
 /*public*/ QVector<CabSignal*> getCabSignalArray();
 /*public*/ void addCabSignalListListener(CabSignalListListener* listener);
 /*public*/ void removeCabSignalListListener(CabSignalListListener* listener);
 /*public*/ void notifyCabSignalListChanged();

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
 /*abstract*/ /*protected*/ virtual CabSignal* createCabSignal(LocoAddress* address) = 0;
 friend class ACMPropertyChangeListener;
};

class ACMPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 AbstractCabSignalManager* acm;
public:
 ACMPropertyChangeListener(AbstractCabSignalManager* acm) {this->acm = acm;}
public slots:
 void propertyChange(PropertyChangeEvent* e)
 {
  acm->handleBlockChange(e);
 }
};
#endif // ABSTRACTCABSIGNALMANAGER_H
