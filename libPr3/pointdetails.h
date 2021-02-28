#ifndef POINTDETAILS_H
#define POINTDETAILS_H

#include <QObject>
#include <QHash>
#include <QMutex>
#include "logger.h"
#include "exceptions.h"
#include "runnable.h"
#include "entryexitpairs.h"
#include "layoutblock.h"

class ButtonTimeOut;
class EntryExitPairs;
class Runnable;
class PropertyChangeEvent;
class DestinationPoints;
class Source;
class SignalMast;
class SignalHead;
class Sensor;
class NamedBean;
class LayoutBlock;
class LayoutEditor;
class PointDetails : public QObject
{
    Q_OBJECT
public:
    //explicit PointDetails(QObject *parent = 0);
    /*public*/ PointDetails(LayoutBlock* facing, QList<LayoutBlock*> protecting, QObject *parent = 0);
    LayoutBlock* getFacing();
    QList<LayoutBlock*> getProtecting();
    void setRouteTo(bool boo);
    void setRouteFrom(bool boo);
    /*public*/ void setPanel(LayoutEditor* panel);
    /*public*/ LayoutEditor* getPanel();
    /*public*/ void setRefObject(NamedBean* refObs);
    /*public*/ NamedBean* getRefObject();
    /*public*/ QObject* getRefLocation();
    Sensor* getSensor();
    bool isRouteToPointSet();
    bool isRouteFromPointSet();
    /*public*/ QString getDisplayName();
    void setNXState(int state);
    int getNXState();
    SignalMast* getSignalMast();
    void setSignalHead(SignalHead* head);
    SignalHead* getSignalHead();
    void setSensor(Sensor* sen);
    void addSensorList();
    void removeSensorList();
    NamedBean* getSignal();
    /*public*/ bool equals(QObject* obj);
    /*public*/ uint hashCode();
    void setSignalMast(SignalMast* mast);
    void setSource(Source* src);
    void setDestination(DestinationPoints* srcdp, Source* src);
    void removeDestination(DestinationPoints* srcdp);
    void removeSource(Source* src);
    void setButtonState(int state);
    /*synchronized*/ /*public*/ void setNXButtonState(int state);
    /*public*/ void setRefObjectByPanel(NamedBean* refObs, LayoutEditor* pnl);
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) ;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:

private:
    LayoutEditor* panel = nullptr;
    LayoutBlock* facing = nullptr;
    QList<LayoutBlock*> protectingBlocks;
    /*private*/ NamedBean* refObj = nullptr;
    /*private*/ QObject* refLoc = nullptr;
    /*private*/ Sensor* sensor = nullptr;
    /*private*/ SignalMast* signalmast = nullptr;
    /*private*/ SignalHead* signalhead = nullptr;
    static int nxButtonTimeout;// = 10;
#if 1
    inline bool operator==(const PointDetails &e2)
    {
        return facing == e2.facing
               && protectingBlocks == e2.protectingBlocks;
    }

    inline uint qHash(const PointDetails &key, uint seed)
    {
        return /*qHash(key.facing, seed)*/ key.facing->hashCode();
    }
#endif
    Source* sourceRoute;
    /*transient*/ QHash<DestinationPoints*, Source*>* destinations;// = new QHash<DestinationPoints, Source>(5);
    bool routeToSet = false;
    bool routeFromSet = false;
    /*private*/ int nxButtonState;// = EntryExitPairs.NXBUTTONINACTIVE;
    /*transient*/ QThread* nxButtonTimeOutThr = nullptr;

    void nxButtonTimeOut();
    void cancelNXButtonTimeOut();
    bool extendedtime = false;
    /*public*/ void flashSensor();
    /*public*/ void stopFlashSensor();
    QMutex mutex;
    Logger* log;
    /*private*/ void nxButtonStateChange(PropertyChangeEvent* e);


protected:
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    /*protected*/ PropertyChangeListener* nxButtonListener;// = new PropertyChangeListener() {


    friend class ButtonTimeOut;
    friend class DestinationPoints;
    friend class DPRunnable;
    friend class NxButtonListener;
};

class ButtonTimeOut :public  Runnable
{
 Q_OBJECT
    PointDetails* self;
public:

    ButtonTimeOut(PointDetails* self){
        this->self = self;
    }
    /*public*/ void run() {
        try {
            //Stage one default timer for the button if no other button has been pressed
            QThread::msleep(self->nxButtonTimeout*1000);
            //Stage two if an extended time out has been requested
            if(self->extendedtime){
                QThread::msleep(60000);  //timeout after a minute waiting for the sml to set.
            }
        } catch (InterruptedException ex) {
            self->log->debug("Flash timer cancelled");
        }
        self->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
    }
};

class NxButtonListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 PointDetails* pd;
public:
 NxButtonListener(PointDetails* pd) {this->pd = pd;}
 void propertyChange(PropertyChangeEvent* e) override
 {
  pd->nxButtonStateChange(e);
 }
 QObject* self() override{return (QObject*)this;}
};
#endif // POINTDETAILS_H
