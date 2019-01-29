#ifndef POINTDETAILS_H
#define POINTDETAILS_H

#include <QObject>
#include <QHash>
#include <QMutex>
#include "logger.h"
#include "exceptions.h"
#include "runnable.h"
#include "entryexitpairs.h"

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
    /*public*/ PointDetails(LayoutBlock* facing, LayoutBlock* protecting, QObject *parent = 0);
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
//    /*public*/ int hashCode();
    void setSignalMast(SignalMast* mast);
    void setSource(Source* src);
    void setDestination(DestinationPoints* srcdp, Source* src);
    void removeDestination(DestinationPoints* srcdp);
    void removeSource(Source* src);
    void setButtonState(int state);
    /*synchronized*/ /*public*/ void setNXButtonState(int state);

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
    /*public*/ void nxButtonListener(PropertyChangeEvent* e);

private:
    LayoutEditor* panel;// = null;
    LayoutBlock* facing;
    QList<LayoutBlock*> protectingBlocks;
    /*private*/ NamedBean* refObj;
    /*private*/ QObject* refLoc;
    /*private*/ Sensor* sensor;
    /*private*/ SignalMast* signalmast;
    /*private*/ SignalHead* signalhead;
    static int nxButtonTimeout;// = 10;

    Source* sourceRoute;
    /*transient*/ QHash<DestinationPoints*, Source*>* destinations;// = new QHash<DestinationPoints, Source>(5);
    bool routeToSet;// = false;
    bool routeFromSet;// = false;
    /*private*/ int nxButtonState;// = EntryExitPairs.NXBUTTONINACTIVE;
    /*transient*/ QThread* nxButtonTimeOutThr;

    void nxButtonTimeOut();
    void cancelNXButtonTimeOut();
    bool extendedtime;// = false;
    /*public*/ void flashSensor();
    /*public*/ void stopFlashSensor();
    QMutex mutex;
    Logger* log;
    friend class ButtonTimeOut;
    friend class DestinationPoints;
    friend class DPRunnable;
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

#endif // POINTDETAILS_H
