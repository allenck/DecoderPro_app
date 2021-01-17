#ifndef LAYOUTBLOCKMANAGER_H
#define LAYOUTBLOCKMANAGER_H
#include "abstractmanager.h"
#include "layoutblock.h"
//#include "signalhead.h"
#include "runnable.h"

class SignalHead;
class SignalMast;
class LayoutBlockConnectivityTools;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutBlockManager : public AbstractManager
{
 Q_OBJECT
public:
 explicit LayoutBlockManager(QObject *parent = 0);
 ~LayoutBlockManager() {}
 LayoutBlockManager(const LayoutBlockManager&) : AbstractManager() {}
 /*public*/ int getXMLOrder() const override;
 /*public*/ char typeLetter() const override{ return 'B'; }
/**
 * Method to create a new LayoutBlock if the LayoutBlock does not exist
 *   Returns null if a LayoutBlock with the same systemName or userName
 *       already exists, or if there is trouble creating a new LayoutBlock.
 *   Note that since the userName is used to address LayoutBlocks, the
 *       user name must be present.  If the user name is not present,
 *       the new LayoutBlock is not created, and null is returned.
 */
/*public*/ LayoutBlock* createNewLayoutBlock(QString systemName, QString userName);
/*public*/ LayoutBlock* createNewLayoutBlock();
/**
 * Remove an existing LayoutBlock.
 */
/*public*/ void deleteLayoutBlock(LayoutBlock* block);
/**
 * Method to get an existing LayoutBlock.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ LayoutBlock* getLayoutBlock(QString name);
/*public*/ LayoutBlock* getLayoutBlock(Block* block);
/*public*/ LayoutBlock* getBlockWithMemoryAssigned(Memory* m);
/*public*/ void initializeLayoutBlockPaths();
/*public*/ void addBadBeanError();
/*public*/ SignalHead* getFacingSignalHead (Block* facingBlock, Block* protectedBlock);
/*public*/ LayoutBlock* getProtectedBlock(QString signalName, LayoutEditor* panel);
/*public*/ LayoutBlock* getFacingBlock(QString signalName, LayoutEditor* panel);
/*public*/ NamedBean* getNamedBeanAtEndBumper(Block* facingBlock, LayoutEditor* panel);
/*public*/ SignalMast* getSignalMastAtEndBumper(Block* facingBlock, LayoutEditor* panel);
/*public*/ LayoutBlock* getFacingBlockByMast(SignalMast *signalMast, LayoutEditor* panel);
/*public*/ LayoutBlock* getProtectedBlockByMast(SignalMast* signalMast, LayoutEditor* panel);
/*public*/ LayoutBlockConnectivityTools* getLayoutBlockConnectivityTools();
/*public*/ QList<LayoutBlock*> getProtectingBlocksByNamedBean( /*@Nullable*/ NamedBean* nb, /*@Nullable*/ LayoutEditor* panel);
/*private*/ QList<LayoutBlock*> getProtectingBlocksByBean(/*@Nullable*/ NamedBean* bean, /*@Nullable*/ LayoutEditor* panel);

/**
* returns true if advanced layout block routing has been enabled.
*/
/*public*/ bool isAdvancedRoutingEnabled();
/**
* Enables the advanced layout block routing protocol
* <p>
* The block routing protocol enables each layout block to build up a list of
* all reachable blocks, along with how far away they are, which direction they
* are in and which of the connected blocks they are reachable from.
*/
/*public*/ void enableAdvancedRouting(bool boo);

/**
 * Method to find a LayoutBlock with a specified Sensor assigned as its
 *    occupancy sensor.  Returns the block or NULL if no existing LayoutBlock
 *    has the Sensor assigned.
 */
 /*public*/ LayoutBlock* getBlockWithSensorAssigned(Sensor* s);
 void setLastRoutingChange();
 /*public*/ void setStabilisedSensor(QString pName) throw (JmriException);
 /*public*/ Sensor* getStabilisedSensor();
 /*public*/ NamedBeanHandle <Sensor*>* getNamedStabilisedSensor();
 /*public*/ bool routingStablised();
 /*public*/ long getLastRoutingChange();
 /*public*/ Sensor* getSensorAtEndBumper(Block* facingBlock, LayoutEditor* panel);
 /*public*/ LayoutBlock* getFacingBlockByNamedBean(NamedBean* nb, LayoutEditor* panel);
 /*public*/ LayoutBlock* getProtectedBlockByNamedBean(NamedBean* nb, LayoutEditor* panel);
 /*public*/ LayoutBlock* getFacingBlock(SignalHead* signalHead, LayoutEditor* panel);
 /*public*/ LayoutBlock* getFacingBlockBySensor(Sensor* sensor, LayoutEditor* panel);
 /*public*/ LayoutBlock* getFacingBlockBySensor(QString sensorName, LayoutEditor* panel);
 /*public*/ LayoutBlock* getProtectedBlock(SignalHead* signalHead, LayoutEditor* panel);
 /*public*/ bool warn();
 /*public*/ void turnOffWarning();
 /*public*/ LayoutBlock* getProtectedBlockBySensor(Sensor* sensor, LayoutEditor* panel);
 /*public*/ LayoutBlock* getProtectedBlockBySensor(QString sensorName, LayoutEditor* panel);
 /*public*/ QList<LayoutBlock*> getProtectingBlocksBySensor(/*@CheckForNull*/ Sensor* sensor, /*@CheckForNull*/ LayoutEditor* panel);
 /*public*/ QList<LayoutBlock*> getProtectingBlocksBySensorOld(/*@CheckForNull*/ Sensor* sensor, /*@Nonnull*/ LayoutEditor* panel);
 /*public*/ NamedBean* getFacingNamedBean(Block* facingBlock, Block* protectedBlock, LayoutEditor* panel);
 /*public*/ SignalMast* getFacingSignalMast(Block* facingBlock, Block* protectedBlock);
 /*public*/ SignalMast* getFacingSignalMast(Block* facingBlock, Block* protectedBlock, LayoutEditor* panel);
 /*public*/ Sensor* getFacingSensor (Block* facingBlock, Block* protectedBlock, LayoutEditor* panel);
 /*public*/ QObject* getFacingSignalObject(Block* facingBlock, Block* protectedBlock);
 QCompleter* getCompleter(QString text, bool bIncludeUserNames = false);
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ QString getNamedBeanClass()const override {
     return "LayoutBlock";
 }
 /*public*/ QString getBeanTypeHandled(bool plural)const override;
 /*public*/ LayoutBlock *getBySystemName(QString name) const;
 /*public*/ LayoutBlock *getByUserName(QString key)const ;


signals:
 void propertyChange(PropertyChangeEvent *e);

public slots:
 void passPropertyChange(PropertyChangeEvent*);

private:
 /*private*/ int blkNum;// = 1;
 /*private*/ void initializeLayoutBlockRouting();
/*private*/ long lastRoutingChange;
/*private*/ void setRoutingStabilised();
 /*private*/ bool warnConnectivity;// = true;


Logger log;
/*private*/ bool initialized;// = false;
/*private*/ int badBeanErrors;// = 0;
bool checking;// = false;
bool stabilised;// = false;
QThread* thr;// = NULL;

/*private*/ NamedBeanHandle<Sensor*>* namedStabilisedIndicator = nullptr;
///*private*/ LayoutTurnout* getLayoutTurnoutFromTurnoutName(QString turnoutName,LayoutEditor* panel);
LayoutBlockConnectivityTools* lbct;// = new LayoutBlockConnectivityTools();
/*private*/ QList<LayoutBlock*> getProtectingBlocksByBeanByPanel(/*@Nullable*/ NamedBean* bean,/*@Nullable*/ LayoutEditor* panel);
/*private*/ LayoutBlock* getFacingBlockByBean(
        /*@Nonnull*/ NamedBean* bean,
        LayoutEditor* panel);
/*private*/ LayoutBlock* getFacingBlockByBeanByPanel(
        /*@Nonnull*/ NamedBean* bean,
        /*@Nonnull */LayoutEditor* panel);

protected:
/*protected*/ bool _enableAdvancedRouting;// = false;
friend class MyRunnable;
};
Q_DECLARE_METATYPE(LayoutBlockManager)

class MyRunnable : public Runnable
{
 Q_OBJECT
    LayoutBlockManager* self;
public:
    MyRunnable(QObject* as, LayoutBlockManager* self);
  public slots:
  /*public*/ void run();
signals:
    void propertyChange(PropertyChangeEvent*);
    void finished();
private:
 Logger* log;
};
#endif // LAYOUTBLOCKMANAGER_H
