#ifndef ENTRYEXITPAIRS_H
#define ENTRYEXITPAIRS_H
#include "manager.h"
#include "logger.h"
#include <QMutex>
#include "exceptions.h"
#include "sensor.h"
#include <QColor>
#include "libPr3_global.h"

class SignalMastLogicManager;
class LayoutBlock;
class LayoutEditor;
class Source;
class PointDetails;
class LIBPR3SHARED_EXPORT EntryExitPairs : public Manager
{
    Q_OBJECT
public:
    explicit EntryExitPairs(QObject *parent = 0);
    /*public*/ int routingMethod;// = LayoutBlockConnectivityTools.METRIC;
    //Method to get delay between issuing Turnout commands
    /*public*/ int turnoutSetDelay;// = 0;

    /*final*/ static int HOPCOUNT;// = LayoutBlockConnectivityTools.HOPCOUNT;
    /*final*/ static int METRIC;// = LayoutBlockConnectivityTools.METRIC;

//    /*public*/ /*final*/ static int NXBUTTONSELECTED;// = 0x08;
//    /*public*/ /*final*/ static int NXBUTTONACTIVE;// = Sensor.ACTIVE;
//    /*public*/ /*final*/ static int NXBUTTONINACTIVE;// = Sensor.INACTIVE;
    enum NXSTATE
    {
     NXBUTTONSELECTED = 0x08,
     NXBUTTONACTIVE = Sensor::ACTIVE,
     NXBUTTONINACTIVE = Sensor::INACTIVE
    };

    /**
    * Constant value to represent that the entryExit will only set up the
    * turnouts between two different points
    */
    /*public*/ /*final*/ static int SETUPTURNOUTSONLY;// = 0x00;

    /**
    * Constant value to represent that the entryExit will set up the
    * turnouts between two different points and configure the signalmast logic
    * to use the correct blocks.
    */
    /*public*/ /*final*/ static int SETUPSIGNALMASTLOGIC;// = 0x01;

   /**
    * Constant value to represent that the entryExit will do full interlocking
    * it will set the turnouts and "reserve" the blocks.
    */
    /*public*/ /*final*/ static int FULLINTERLOCK;// = 0x02;
    enum ACTIONS
    {
     PROMPTUSER = 0x00,
     AUTOCLEAR = 0x01,
     AUTOCANCEL = 0x02
    };

    static QWidget* glassPane;// = new QWidget();
    /*public*/ void setDispatcherIntegration(bool boo);
    /*public*/ bool getDispatcherIntegration();
    /*public*/ QWidget* getGlassPane();
    /*public*/ void addNXSourcePoint(LayoutBlock* facing, LayoutBlock* protecting, NamedBean* loc, LayoutEditor* panel);
    /*public*/ void addNXSourcePoint(NamedBean* source);
    /*public*/ void addNXSourcePoint(NamedBean* source, LayoutEditor* panel);
    /*public*/ QObject* getEndPointLocation(NamedBean* source, LayoutEditor* panel);
    /*public*/ int getXMLOrder();
    /*public*/ NamedBean* getBySystemName(QString systemName);
    /*public*/ NamedBean* getBeanBySystemName(QString systemName);
    /*public*/ NamedBean* getBeanByUserName(QString userName);
    /*public*/ NamedBean* getNamedBean(QString name);
    /*public*/ char systemLetter();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ QString makeSystemName(QString s);
    /*public*/ QStringList getSystemNameArray();
    /*public*/ QStringList getSystemNameList();
    /*public*/ void Register(NamedBean* n);
    /*public*/ void deregister(NamedBean* n);
    /*public*/ void setClearDownOption(int i);
    /*public*/ int getClearDownOption();
    /*public*/ void dispose();
    /*public*/ QObjectList* getSourceList(LayoutEditor* panel);
    /*public*/ int getNxPairNumbers(LayoutEditor* panel);
    /*public*/ QObjectList* getNxSource(LayoutEditor* panel);
    /*public*/ QObjectList* getNxDestination();
    /*public*/ QList<LayoutEditor*> getSourcePanelList();
    /*public*/ void addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel);
    /*public*/ void addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel, QString id);
    /*public*/ QObjectList* getDestinationList(QObject* obj, LayoutEditor* panel);
    /*public*/ void deleteNxPair(NamedBean* source, NamedBean* destination, LayoutEditor* panel);
    /*public*/ bool isDestinationValid(QObject* source, QObject* dest, LayoutEditor* panel);
    /*public*/ bool isUniDirection(QObject* source, LayoutEditor* panel, QObject* dest);
    /*public*/ void setUniDirection(QObject* source, LayoutEditor* panel, QObject* dest, bool set);
    /*public*/ bool canBeBiDirectional(QObject* source, LayoutEditor* panel, QObject* dest);
    /*public*/ bool isEnabled(QObject* source, LayoutEditor* panel, QObject* dest);
    /*public*/ void setEnabled(QObject* source, LayoutEditor* panel, QObject* dest, bool set);
    /*public*/ void setEntryExitType(QObject* source, LayoutEditor* panel, QObject* dest, int set);
    /*public*/ int getEntryExitType(QObject* source, LayoutEditor* panel, QObject* dest);
    /*public*/ QString getUniqueId(QObject* source, LayoutEditor* panel, QObject* dest);
    /*public*/ QStringList getEntryExitList();
    /*public*/ bool isPathActive(QObject* sourceObj, QObject* destObj, LayoutEditor* panel);
    /*public*/ void cancelInterlock(QObject* source, LayoutEditor* panel, QObject* dest);

    /*public*/ /*final*/ static int CANCELROUTE;// = 0;
    /*public*/ /*final*/ static int CLEARROUTE;// = 1;
    /*public*/ /*final*/ static int EXITROUTE;// = 2;
    /*/*public*/ static void flashSensor(PointDetails* pd);
    /*public*/ static void stopFlashSensor(PointDetails* pd);
    /*synchronized*/ /*public*/ void setNXButtonState(PointDetails* nxPoint, int state);
    /*public*/ PointDetails* getPointDetails(QObject* obj, LayoutEditor* panel);
    PointDetails* getPointDetails(LayoutBlock* source, LayoutBlock* destination, LayoutEditor* panel);
    //No point in have multiple copies of what is the same thing.
    static QList<PointDetails*>* pointDetails;// = new ArrayList<PointDetails>();
    /*public*/ QString getPointAsString(NamedBean* obj, LayoutEditor* panel);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* list, NamedBean* obj, LayoutEditor* panel);
//    java.beans.PropertyChangeSupport pcs = new java.beans.PropertyChangeSupport(this);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n) ;
    /*public*/ void automaticallyDiscoverEntryExitPairs(LayoutEditor* editor, int interlockType) throw (JmriException);
    /*public*/ int getSettingTimer();
    /*public*/ void setSettingTimer(int i);
    /*public*/ bool useDifferentColorWhenSetting();
    /*public*/ QColor getSettingRouteColor();
    /*public*/ void setSettingRouteColor(QColor col);

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
    void on_propertyChange(PropertyChangeEvent*);
private:
    int routeClearOption;// = PROMPTUSER;
    QMap<PointDetails*, Source*>* nxpair;// = new QMap<PointDetails*, Source*>();
    /*private*/ PointDetails* providePoint(NamedBean* source, LayoutEditor* panel);
    Logger* log;
    QObjectList* destinationList;// = new ArrayList<Object>();
    /*private*/ PointDetails* providePoint(LayoutBlock* source, LayoutBlock* protecting, LayoutEditor* panel);
    bool runWhenStablised;// = false;
    LayoutEditor* toUseWhenStable;
    int interlockTypeToUseWhenStable;
    SignalMastLogicManager* smlm;
    QMutex mutex;
    /*private*/ int settingTimer;// = 2000;
    /*private*/ QColor settingRouteColor;// = null;
    bool allocateToDispatcher;// = false;

};

#endif // ENTRYEXITPAIRS_H
