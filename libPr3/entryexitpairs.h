#ifndef ENTRYEXITPAIRS_H
#define ENTRYEXITPAIRS_H
#include "manager.h"
#include "logger.h"
#include <QMutex>
#include "exceptions.h"
#include "sensor.h"
#include <QColor>
#include "libPr3_global.h"
#include <QTimer>
#include "source.h"
#include "jpanel.h"
#include "instancemanagerautodefault.h"
#include "vetoablechangesupport.h"
#include "propertychangelistener.h"

class DeletePair;
class JDialog;
class StackNXPanel;
class DestinationPoints;
class SignalMastLogicManager;
class LayoutBlock;
class LayoutEditor;
class Source;
class PointDetails;
/*static*/ class StackDetails {
public:
        DestinationPoints* dp;
        bool reverse;

        StackDetails(DestinationPoints* dp, bool reverse) {
            this->dp = dp;
            this->reverse = reverse;
        }

        bool getReverse() {
            return reverse;
        }

        DestinationPoints* getDestinationPoint() {
            return dp;
        }
    };
/**
 * Class to store NX sets consisting of a source point, a destination point,
 * a direction and a reference.
 */
/*static*/ class SourceToDest {
public:
    Source* s = nullptr;
    DestinationPoints* dp = nullptr;
    bool direction = false;
    int ref = -1;

    /**
     * Constructor for a SourceToDest element.
     * @param s a source point
     * @param dp a destination point
     * @param dir a direction
     * @param ref Integer used as reference
     */
    SourceToDest(Source* s, DestinationPoints* dp, bool dir, int ref) {
        this->s = s;
        this->dp = dp;
        this->direction = dir;
        this->ref = ref;
    }
};

class /*LIBPR3SHARED_EXPORT*/ EntryExitPairs : public VetoableChangeSupport, public Manager, public InstanceManagerAutoDefault, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(Manager InstanceManagerAutoDefault PropertyChangeListener)
public:
    explicit EntryExitPairs(QObject *parent = 0);
 ~EntryExitPairs() {}
 EntryExitPairs(const EntryExitPairs&) : VetoableChangeSupport(this) {}
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
     AUTOCANCEL = 0x02,
     AUTOSTACK = 0x03
    };

    static QWidget* glassPane;// = new QWidget();
    /*public*/ void setDispatcherIntegration(bool boo);
    /*public*/ bool getDispatcherIntegration();
    /*public*/ QWidget* getGlassPane();
    /*public*/ void addNXSourcePoint(LayoutBlock* facing, QList<LayoutBlock *> protecting, NamedBean* loc, LayoutEditor* panel);
    /*public*/ void addNXSourcePoint(NamedBean* source);
    /*public*/ void addNXSourcePoint(NamedBean* source, LayoutEditor* panel);
    /*public*/ QObject* getEndPointLocation(NamedBean* source, LayoutEditor* panel);
    /*public*/ int getXMLOrder() const override;
    /*public*/ NamedBean *getBySystemName(QString systemName) const;
    /*public*/ NamedBean* getByUserName(QString systemName) const ;
//    /*public*/ NamedBean* getBeanBySystemName(QString systemName) const override;
//    /*public*/ NamedBean* getBeanByUserName(QString userName)const override;
    /*public*/ NamedBean* getNamedBean(QString name) const override;
//    /*public*/ char systemLetter() const;
    /*public*/ SystemConnectionMemo* getMemo() const override;
    /*public*/ QString getSystemPrefix()const override;
    /*public*/ char typeLetter() const override;
    /*public*/ QString makeSystemName(QString s)const override;
    /*public*/ int getObjectCount() override;
//    /*public*/ QStringList getSystemNameArray() override;
    /*public*/ QStringList getSystemNameList() override;
    /*public*/ void Register(NamedBean* n)const override;
    /*public*/ void deregister(NamedBean* n)const override;
    /*public*/ void setClearDownOption(int i);
    /*public*/ int getClearDownOption();
    /*public*/ void setOverlapOption(int i);
    /*public*/ int getOverlapOption();
    /*public*/ void setMemoryOption(QString memoryName);
    /*public*/ QString getMemoryOption();
    /*public*/ void setMemoryClearDelay(int secs) ;
    /*public*/ int getMemoryClearDelay();
    /*public*/ void dispose() override;
    /*public*/ QObjectList* getSourceList(LayoutEditor* panel);
    /*public*/ Source* getSourceForPoint(PointDetails* pd);
    /*public*/ void setSingleSegmentRoute(QString nxPair);
    /*public*/ void setMultiPointRoute(PointDetails* requestpd, LayoutEditor* panel);
    /*public*/ int getNxPairNumbers(LayoutEditor* panel);
    /*public*/ QObjectList getNxSource(LayoutEditor* panel);
    /*public*/ QObjectList getNxDestination();
    /*public*/ QList<LayoutEditor*> getSourcePanelList();
    /*public*/ void addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel);
    /*public*/ void addNXDestination(NamedBean* source, NamedBean* destination, LayoutEditor* panel, QString id);
    /*public*/ QObjectList* getDestinationList(NamedBean *obj, LayoutEditor* panel);
    /*public*/ void removeNXSensor(Sensor* sensor);
    /*public*/ bool deleteNxPair(NamedBean* sensor);
    /*public*/ bool deleteNxPair(NamedBean* source, NamedBean* exitSensor, LayoutEditor* panel);
    /*public*/ bool isDestinationValid(NamedBean *source, NamedBean* dest, LayoutEditor* panel);
    /*public*/ bool isUniDirection(NamedBean *source, LayoutEditor* panel, NamedBean *dest);
    /*public*/ void setUniDirection(NamedBean *source, LayoutEditor* panel, NamedBean *dest, bool set);
    /*public*/ bool canBeBiDirectional(NamedBean *source, LayoutEditor* panel, NamedBean *dest);
    /*public*/ bool isEnabled(NamedBean *source, LayoutEditor* panel, NamedBean *dest);
    /*public*/ void setEnabled(NamedBean *source, LayoutEditor* panel, NamedBean *dest, bool set);
    /*public*/ void setEntryExitType(NamedBean *source, LayoutEditor* panel, NamedBean *dest, int set);
    /*public*/ int getEntryExitType(NamedBean* source, LayoutEditor* panel, NamedBean* dest);
    /*public*/ QString getUniqueId(NamedBean *source, LayoutEditor* panel, NamedBean *dest);
    /*public*/ QStringList getEntryExitList();
    /*public*/ bool isPathActive(NamedBean* sourceObj, NamedBean* destObj, LayoutEditor* panel);
    /*public*/ void cancelInterlock(NamedBean *source, LayoutEditor* panel, NamedBean *dest);

    /*public*/ /*final*/ static int CANCELROUTE;// = 0;
    /*public*/ /*final*/ static int CLEARROUTE;// = 1;
    /*public*/ /*final*/ static int EXITROUTE;// = 2;
    /*public*/ /*final*/ static int STACKROUTE;// = 4;
    /*/*public*/ static void flashSensor(PointDetails* pd);
    /*public*/ static void stopFlashSensor(PointDetails* pd);
    /*synchronized*/ /*public*/ void setNXButtonState(PointDetails* nxPoint, int state);
    /*public*/ PointDetails* getPointDetails(NamedBean *obj, LayoutEditor* panel);
    PointDetails* getPointDetails(LayoutBlock* source, QList<LayoutBlock *> destination, LayoutEditor* panel);
    //No point in have multiple copies of what is the same thing.
    /*public*/ QString getPointAsString(NamedBean* obj, LayoutEditor* panel);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* list, NamedBean* obj, LayoutEditor* panel);
//    java.beans.PropertyChangeSupport pcs = new java.beans.PropertyChangeSupport(this);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) ;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) ;
    /*public*/ void automaticallyDiscoverEntryExitPairs(LayoutEditor* editor, int interlockType) /*throw (JmriException)*/;
    /*public*/ int getSettingTimer();
    /*public*/ void setSettingTimer(int i);
    /*public*/ bool useDifferentColorWhenSetting();
    /*public*/ QColor getSettingRouteColor();
    /*public*/ void setSettingRouteColor(QColor col);
    /*public*/ bool isAssignableFromType() {return true;}
    /*public*/ QSet<NamedBean*> getNamedBeanSet() override;
    /*synchronized*/ /*public*/ void stackNXRoute(DestinationPoints* dp, bool reverse);
    /*public*/ QList<DestinationPoints*> getStackedInterlocks();
    /*public*/ bool isRouteStacked(DestinationPoints* dp, bool reverse);
    /*synchronized*/ /*public*/ void cancelStackedRoute(DestinationPoints* dp, bool reverse);
    /*public*/ QList<QString> layoutBlockSensors(/*@Nonnull*/ LayoutBlock* layoutBlock);
    /*public*/ /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) ;
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners() override;
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override;
    /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
    /*public*/ void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener)override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners() override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners(QString propertyName) override;
    /*public*/ void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener)override;
    /*public*/ void deleteBean(DestinationPoints* bean, QString property) throw (PropertyVetoException);
    /*public*/ QString getBeanTypeHandled(bool plural)const override;
    /*public*/ void addDataListener(/*ManagerDataListener*/QObject *e) override;
    /*public*/ void removeDataListener(QObject *e) override;
    /*public*/ QString getNamedBeanClass()const override;

    QObject* self() override {return (QObject*)this;}

signals:
    //void propertyChange(PropertyChangeEvent*);
public slots:
    void propertyChange(PropertyChangeEvent*)override;
    /*public*/ void propertyDestinationPropertyChange(PropertyChangeEvent* e);
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException);

private:
    int routeClearOption;// = PROMPTUSER;
    int routeOverlapOption = PROMPTUSER;
    QString memoryOption = "";     // Optional memory variable to receive allocation messages
    int memoryClearDelay = 0;     // Delay before clearing memory, 0 for clearing disabled
    /*private*/ PointDetails* providePoint(NamedBean* source, LayoutEditor* panel);
    Logger* log;
    QObjectList destinationList;// = new ArrayList<Object>();
    /*private*/ PointDetails* providePoint(LayoutBlock* source, QList<LayoutBlock *> protecting, LayoutEditor* panel);
    bool runWhenStablised = false;
    LayoutEditor* toUseWhenStable;
    int interlockTypeToUseWhenStable;
    SignalMastLogicManager* smlm;
    QMutex mutex;
    /*private*/ int settingTimer;// = 2000;
    /*private*/ QColor settingRouteColor;// = null;
    bool allocateToDispatcher;// = false;
    /*private*/ void setMultiPointRoute(PointDetails* fromPd, PointDetails* toPd);
    int refCounter = 0;
    /**
     * List holding SourceToDest sets of routes between two points.
     */
    QList<SourceToDest*> routesToSet;// = new ArrayList<>();
    int currentDealing = 0;
    /*synchronized*/ void processRoutesToSet();
    /*synchronized*/ void removeRemainingRoute();
    QList<StackDetails*> stackList;// = new ArrayList<>();
    QTimer* checkTimer;
    StackNXPanel* stackPanel = nullptr;
    JDialog* stackDialog = nullptr;
    /**
     * List of NX pairs that are scheduled for deletion.
     * @since 4.11.2
     */
    QList<DeletePair*> deletePairList;// = new ArrayList<>();
    /*private*/ bool checkNxPairs();
    /*private*/ bool confirmDeletePairs();
    /*private*/ void deleteNxPairs();
    QHash<PointDetails*, Source*> nxpair;// = new HashMap<>();
    void createDeletePairList(NamedBean* sensor);
    VetoableChangeSupport* vcs;// = new VetoableChangeSupport(this);
    /*final*/ QVector</*ManagerDataListener*/QObject*> listeners;// = new QVector<ManagerDataListener</*DestinationPoints*/NamedBean*>*>();
    static QList<PointDetails*>* pointDetails;// = new ArrayList<PointDetails>();
    //PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    SystemConnectionMemo* memo = nullptr;

private slots:
    /*synchronized*/ void checkRoute();
protected:
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n) ;

 friend class DeletePair;
 friend class PickListModel;
 friend class EntryExitTestTools;
 friend class AddEntryExitPairPanel;
 friend class AEPTableModel;
};
Q_DECLARE_METATYPE(EntryExitPairs)

/**
 * Class to store NX pair components.
 * @since 4.11.2
 */
class DeletePair {
public:
    NamedBean* src = nullptr;
    NamedBean* dest = nullptr;
    LayoutEditor* pnl = nullptr;
    DestinationPoints* dp = nullptr;
    EntryExitPairs* pairs;

    /**
     * Constructor for a DeletePair row.
     * @param src Source sensor bean
     * @param dest Ddestination sensor bean
     * @param pnl The LayoutEditor panel for the source bean
     */
    DeletePair(NamedBean* src, NamedBean* dest, LayoutEditor* pnl, EntryExitPairs* pairs) {
        this->src = src;
        this->dest = dest;
        this->pnl = pnl;
     this->pairs = pairs;

        // Get the actual destination point, if any.
        PointDetails* sourcePoint = pairs->getPointDetails(src, pnl);
        PointDetails* destPoint = pairs->getPointDetails(dest, pnl);
        if (sourcePoint != nullptr && destPoint != nullptr) {
            if (pairs->nxpair.contains(sourcePoint)) {
                this->dp = pairs->nxpair.value(sourcePoint)->getDestForPoint(destPoint);
            }
        }
    }
};

#endif // ENTRYEXITPAIRS_H
