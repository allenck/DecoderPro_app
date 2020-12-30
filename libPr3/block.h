#ifndef BLOCK_H
#define BLOCK_H
#include "logger.h"
#include "abstractnamedbean.h"
#include "sensor.h"
#include "namedbeanhandle.h"
#include "exceptions.h"
#include "physicallocationreporter.h"


class Path;
class LIBPR3SHARED_EXPORT Block : public AbstractNamedBean /*, public PhysicalLocationReporter*/
{
    Q_OBJECT
public:
    /*public*/ Block(QString systemName, QString userName="",QObject* parent =0);
//    static const int OCCUPIED = Sensor::ACTIVE;
//    static const int UNOCCUPIED;// = 0x04;// Sensor::INACTIVE;
 /*public*/ QString toDebugString();

    enum STATE
    {
     OCCUPIED = 0x02, // Sensor::Active,
     UNOCCUPIED = 0x04,
     UNDETECTED = 0x100
    };
    Q_ENUM(STATE)
    // Curvature attributes
    static /*const*/ int NONE;// = 0x00;
    static /*const*/ int GRADUAL;// = 0x01;
    static /*const*/ int TIGHT;// = 0x02;
    static /*const*/ int SEVERE;// = 0x04;

    /*public*/ virtual bool setSensor(QString pName);
    /*public*/ virtual void setNamedSensor(NamedBeanHandle<Sensor*>* s);
    /*public*/ Sensor* getSensor();
    /*public*/ NamedBeanHandle <Sensor*>* getNamedSensor();
    /**
     * Set the Reporter that should provide the data value for this block.
     *
     * @see Reporter
     * @param reporter Reporter object to link, or NULL to clear
     */
    /*public*/ void setReporter(Reporter* reporter);
    /**
     * Retrieve the Reporter that is linked to this Block
     *
     * @see Reporter
     * @return linked Reporter object, or NULL if not linked
     */
    /*public*/ Reporter* getReporter();
    /**
     * Define if the Block's value should be populated from the
     * {@link Reporter#getCurrentReport() current report}
     * or from the {@link Reporter#getLastReport() last report}.
     *
     * @see Reporter
     * @param reportingCurrent
     */
    /*public*/ void setReportingCurrent(bool reportingCurrent);
    /**
     * Determine if the Block's value is being populated from the
     * {@link Reporter#getCurrentReport() current report}
     * or from the {@link Reporter#getLastReport() last report}.
     *
     * @see Reporter
     * @return true if populated by {@link Reporter#getCurrentReport() current report};
     * false if from {@link Reporter#getLastReport() last report}.
     */
    /*public*/ bool isReportingCurrent();
    /*public*/ int getState() override;
    QString getStateString();
    /*public*/ virtual void addPath(Path* p);
    /*public*/ virtual void removePath(Path* p);
    /*public*/ bool hasPath(Path* p);

    /**
     * Get a copy of the list of Paths
     */
    /*public*/ QVector<Path*>* getPaths();
    /**
     * Provide a general method for updating the report.
     */
    /*public*/ void setState(int v) override;
    /**
     * Set the value retained by this Block.
     * Also used when the Block itself gathers a value from an
     * adjacent Block.  This can be overridden in a subclass if
     * e.g. you want to keep track of Blocks elsewhere, but make
     * sure you also eventually invoke the super.setValue() here.
     * <p>
     * @param value The new Object resident in this block, or NULL if none.
     */
    /*public*/ virtual void setValue(QVariant value);
    /*public*/ QVariant getValue();
    /*public*/ void setDirection(int direction);
    /*public*/ int getDirection();
    /**
    * The block deny list, is used by higher level code, to determine if
    * traffic/trains should be allowed to enter from an attached block,
    * the list only deals with blocks that access should be denied from.
    * If we want to prevent traffic from following from this block to another
    * then this block must be added to the deny list of the other block.
    * By default no block is barred, so traffic flow is bi-directional.
    */
    /*public*/ void addBlockDenyList(QString pName);
    /*public*/ void addBlockDenyList(Block* blk);
    /*public*/ void removeBlockDenyList(QString blk);
    /*public*/ void removeBlockDenyList(Block* blk);
    /*public*/ QList<QString> *getDeniedBlocks();
    /*public*/ bool isBlockDenied(QString deny);
    /*public*/ bool isBlockDenied(Block* deny);
    /*public*/ bool getPermissiveWorking();
    /*public*/ void setPermissiveWorking(bool w);
    /*public*/ float getSpeedLimit();
    /*public*/ QString getBlockSpeed();
    /*public*/ void setBlockSpeed(QString s) throw (JmriException);
    /*public*/ void setCurvature(int c);
    /*public*/ int getCurvature();
    /*public*/ void setLength(float l);  // l must be in millimeters
    /*public*/ float getLengthMm(); // return length in millimeters
    /*public*/ float getLengthCm();  // return length in centimeters
    /*public*/ float getLengthIn();  // return length in inches
    /*public*/ bool equals(QObject* obj)override;

//    /** Handle change in sensor state.
//     * <P>
//     * Defers real work to goingActive, goingInactive methods
//     */
//    void handleSensorChange(PropertyChangeEvent* e);
//    /**
//     * Handle change in Reporter value.
//     *
//     * @param e PropertyChangeEvent
//     */
//    void handleReporterChange(PropertyChangeEvent* e);
    /**
     * Handles Block sensor going INACTIVE: this block is empty
     */
    /*public*/ virtual void goingInactive();
    /**
     * Handles Block sensor going ACTIVE: this block is now occupied,
     * figure out from who and copy their value.
     */
    /*public*/ virtual void goingActive();
    /**
     * Find which path this Block became Active, without actually
     * modifying the state of this block.
     *
     * (this is largely a copy of the 'Search' part of the logic
     * from goingActive())
     */
    /*public*/ Path* findFromPath();

    /*public*/ void setAllocated(bool boo);

    /** Parse a given string and return the LocoAddress value that is presumed stored
     * within it based on this object's protocol.
     * The Class Block implementationd defers to its associated Reporter, if it exists.
     *
     * @param rep String to be parsed
     * @return LocoAddress address parsed from string, or NULL if this Block isn't associated
     *         with a Reporter, or is associated with a Reporter that is not also a
     *         PhysicalLocationReporter
     */
    /*public*/ LocoAddress* getLocoAddress(QString rep);
    /** Parses out a (possibly old) LnReporter-generated report string to extract the direction from
     * within it based on this object's protocol.
     * The Class Block implementationd defers to its associated Reporter, if it exists.
     *
     * @param rep String to be parsed
     * @return PhysicalLocationReporter.Direction direction parsed from string, or NULL if
     *         this Block isn't associated with a Reporter, or is associated with a Reporter
     *         that is not also a PhysicalLocationReporter
     */
    /*public*/ PhysicalLocationReporter::Direction getDirection(QString rep);
    /** Return this Block's physical location, if it exists.
     * Defers actual work to the helper methods in class PhysicalLocation
     *
     * @return PhysicalLocation : this Block's location.
     */
    /*public*/ PhysicalLocation* getPhysicalLocation() ;
    /** Return this Block's physical location, if it exists.
     * Does not use the parameter s
     * Defers actual work to the helper methods in class PhysicalLocation
     *
     * @param s (this parameter is ignored)
     * @return PhysicalLocation : this Block's location.
     */
    /*public*/ PhysicalLocation* getPhysicalLocation(QString s);
    /*public*/ void setBlockSpeedName(QString s);
    virtual /*public*/ void goingUnknown();
    virtual /*public*/ void goingInconsistent();

signals:

public slots:
    /** Handle change in sensor state.
     * <P>
     * Defers real work to goingActive, goingInactive methods
     */
    void handleSensorChange(PropertyChangeEvent* e);
    void handleSensorChange(QString propertyName, int o, int n);
    /**
     * Handle change in Reporter value.
     *
     * @param e PropertyChangeEvent
     */
    void handleReporterChange(PropertyChangeEvent* e);

private:
    Logger* log;
    // internal data members
    /*private*/ int _current;// = UNOCCUPIED; // state
    /*private*/ Sensor* _sensor = nullptr;
    /*private*/ NamedBeanHandle<Sensor*>* _namedSensor = nullptr;
    /*private*/ PropertyChangeListener* _sensorListener = nullptr;
    /*private*/ QVariant _value;
    /*private*/ int _direction;
    /*private*/ int _curvature;// = NONE;
    /*private*/ float _length = 0.0f;  // always stored in millimeters
    /*private*/ Reporter* _reporter = nullptr;
    /*private*/ PropertyChangeListener* _reporterListener = nullptr;
    /*private*/ bool _reportingCurrent;// = false;
    QVector<Path*>* paths;// = new QVector<Path*>();
    //Deny traffic entering from this block
    QVector<NamedBeanHandle<Block*>* > blockDenyList;// = new QVector<NamedBeanHandle<Block*>>(1);
    /*private*/ bool _permissiveWorking=false;
    /*private*/ QString _blockSpeed;// = "";
    /*private*/ int maxInfoMessages = 5;
    /*private*/ int infoMessageCount = 0;
};

class BlockSensorListener : public PropertyChangeListener
{
 Q_OBJECT
 Block* block;
public:
 BlockSensorListener(Block* block) {this->block = block;}
public slots:
 void propertyChange(PropertyChangeEvent*);
};
#endif // BLOCK_H
