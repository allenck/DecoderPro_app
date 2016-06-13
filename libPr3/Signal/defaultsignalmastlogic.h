#ifndef DEFAULTSIGNALMASTLOGIC_H
#define DEFAULTSIGNALMASTLOGIC_H
#include <QHash>
#include "logger.h"
#include "signalmastlogic.h"
#include "signalmast.h"
#include <QThread>
#include <QMutex>
#include <QMap>
#include "namedbeanhandle.h"
#include "sensor.h"
#include "turnout.h"
#include "block.h"

class SignalMastLogic;
class SignalMast;
class LayoutEditor;
class LayoutBlock;
class DestinationMast;
class PropertyChangeSupport;
class PropertyDestinationMastListener;
class PropertySourceMastListener;
class NamedBeanSetting;
class PropertySensorListener;
class PropertyTurnoutListener;
class PropertyBlockListener;
class PropertySignalMastListener;
class SignalSpeedMap;

class LIBPR3SHARED_EXPORT DefaultSignalMastLogic : public SignalMastLogic
{
    Q_OBJECT
public:
    //explicit DefaultSignalMastLogic(QObject *parent = 0);
    /*public*/ DefaultSignalMastLogic (SignalMast* source, QObject *parent = 0);
    /*public*/ void setFacingBlock(LayoutBlock* facing);
    /*public*/ void setProtectingBlock(LayoutBlock* protecting);
    /*public*/ LayoutBlock* getFacingBlock();
    /*public*/ LayoutBlock* getProtectingBlock();
    /*public*/ SignalMast* getSourceMast();
    /*public*/ void replaceSourceMast(SignalMast* oldMast, SignalMast* newMast);
    /*public*/ void replaceDestinationMast(SignalMast* oldMast, SignalMast* newMast);
    /*public*/ void setDestinationMast(SignalMast* dest);
    /*public*/ bool isDestinationValid(SignalMast* dest);
    /*public*/ QList<SignalMast*> getDestinationList();
    /*public*/ QString getComment(SignalMast* dest);
    /*public*/ void setComment(QString comment,SignalMast* dest);
    /*public*/ void setStore(int store, SignalMast* destination);
    /*public*/ int getStoreState(SignalMast* destination);
    /*public*/ void setEnabled(SignalMast* dest);
    /*public*/ void setDisabled(SignalMast* dest) ;
    /*public*/ bool isEnabled(SignalMast* dest);
    /*public*/ bool isActive(SignalMast* dest);
    /*public*/ bool removeDestination(SignalMast* dest);
    /*public*/ void disableLayoutEditorUse();
    /*public*/ void useLayoutEditor(bool boo, SignalMast* destination) throw (JmriException);
    /*public*/ bool useLayoutEditor(SignalMast* destination);
    /*public*/ void useLayoutEditorDetails(bool turnouts, bool blocks, SignalMast* destination) throw (JmriException);
    /*public*/ bool useLayoutEditorTurnouts(SignalMast* destination);
    /*public*/ bool useLayoutEditorBlocks(SignalMast* destination);
    /*public*/ bool allowAutoMaticSignalMastGeneration(SignalMast* destination);
    /*public*/ void allowAutoMaticSignalMastGeneration(bool allow, SignalMast* destination);
    /*public*/ void allowTurnoutLock(bool lock, SignalMast* destination);
    /*public*/ bool isTurnoutLockAllowed(SignalMast* destination);
    /*public*/ virtual void setTurnouts(QHash<NamedBeanHandle<Turnout*>*, int> turnouts, SignalMast* destination);
    /*public*/ void setAutoTurnouts(QHash<Turnout*, int> turnouts, SignalMast* destination);
    /*public*/ void setBlocks(QHash<Block*, int> blocks, SignalMast* destination);
    /*public*/ virtual void setAutoBlocks(QMap<Block*, int> blocks, SignalMast* destination);
    /*public*/ void setMasts(QHash<SignalMast*, QString> masts, SignalMast* destination);
    /*public*/ void setAutoMasts(QHash<SignalMast*, QString> masts, SignalMast* destination);
    /*public*/ virtual void setSensors(QHash<NamedBeanHandle<Sensor*>*, int> sensors, SignalMast* destination);
    /*public*/ void addSensor(QString sensorName, int state, SignalMast* destination);
    /*public*/ void removeSensor(QString sensorName, SignalMast* destination);
    /*public*/ QList<Block*> getBlocks(SignalMast* destination);
    /*public*/ QList<Block*> getAutoBlocks(SignalMast* destination);
    /*public*/ QList<Block*> getAutoBlocksBetweenMasts(SignalMast* destination);
    /*public*/ QList<Turnout*> getTurnouts(SignalMast* destination);
    /*public*/ QList<NamedBeanHandle<Turnout*>* > getNamedTurnouts(SignalMast* destination);
    /*public*/ QList<Turnout*> getAutoTurnouts(SignalMast* destination);
    /*public*/ QList<Sensor*> getSensors(SignalMast* destination);
    /*public*/ QList<NamedBeanHandle<Sensor*>* > getNamedSensors(SignalMast* destination);
    /*public*/ QList<SignalMast*> getSignalMasts(SignalMast* destination);
    /*public*/ QList<SignalMast*> getAutoMasts(SignalMast* destination);
    /*general method to initialise all*/
    /*public*/ void initialise();
    /*public*/ void initialise(SignalMast* destination);
    /*public*/ void setupLayoutEditorDetails();
    bool checkStates();
    /*public*/ bool areBlocksIncluded(QList<Block*> blks);
    /*public*/ int getBlockState(Block* block, SignalMast* destination);
    /*public*/ bool isBlockIncluded(Block* block, SignalMast* destination);
    /*public*/ bool isTurnoutIncluded(Turnout* turnout, SignalMast* destination);
    /*public*/ bool isSensorIncluded(Sensor* sensor, SignalMast* destination);
    /*public*/ bool isSignalMastIncluded(SignalMast* signal, SignalMast* destination);
    /*public*/ int getAutoBlockState(Block* block, SignalMast* destination);
    /*public*/ int getSensorState(Sensor* sensor, SignalMast* destination);
    /*public*/ int getTurnoutState(Turnout* turnout, SignalMast* destination);
    /*public*/ int getAutoTurnoutState(Turnout* turnout, SignalMast* destination);
    /*public*/ QString getSignalMastState(SignalMast* mast, SignalMast* destination);
    /*public*/ QString getAutoSignalMastState(SignalMast* mast, SignalMast* destination);
    /*public*/ float getMaximumSpeed(SignalMast* destination);
    void setMastAppearance();
    /*public*/ void setConflictingLogic(SignalMast* sm, LevelXing* lx);
    /*public*/ void removeConflictingLogic(SignalMast* sm, LevelXing* lx);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ int getNumPropertyChangeListeners();
    /*public*/ void dispose();

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
private:
    SignalMast* source;
    SignalMast* destination;
    QString stopAspect;

    QHash<SignalMast*, DestinationMast*> destList;// =  QHash<SignalMast*, DestinationMast*>();
    LayoutEditor* editor;

    bool useAutoGenBlock;// = true;
    bool useAutoGenTurnouts;// = true;

    LayoutBlock* facingBlock;// = NULL;
    LayoutBlock* protectingBlock;// = NULL;

    bool disposing;// = false;
    Logger*log;
    PropertyChangeSupport* pcs;// = new jPropertyChangeSupport(this);
    /*volatile*/ bool inWait;// = false;
    QThread* thr;// = NULL;
    /*synchronized*/ void setSignalAppearance();
    QMutex mutex;
protected:
    /*protected*/ PropertyDestinationMastListener*  propertyDestinationMastListener;// = new PropertyDestinationMastListener();
    /*protected*/ PropertySourceMastListener* propertySourceMastListener;// = new PropertySourceMastListener();
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

friend class PropertyDestinationMastListener;
friend class PropertySourceMastListener;
friend class PropertySignalMastListener;
friend class PropertyTurnoutListener;
friend class PropertySensorListener;
friend class PropertyBlockListener;
friend class RunnableThis;
friend class DestinationMast;
friend class SignalMastLogicWidget;
};
//This is the listener on the destination signalMast
class PropertyDestinationMastListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertyDestinationMastListener(DefaultSignalMastLogic* parent)
    {
     this->parent = parent;
    }
    DefaultSignalMastLogic* parent;
    void propertyChange(PropertyChangeEvent *e)
    {
        SignalMast* mast = (SignalMast*) e->getSource();
        if (mast==parent->destination)
        {
            if(parent->log->isDebugEnabled())
                parent->log->debug("destination mast change " +mast->getDisplayName());
            parent->setSignalAppearance();
        }
    }
};

//This is the listener on the source signalMast
class PropertySourceMastListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertySourceMastListener(DefaultSignalMastLogic* parent)
    {
     this->parent = parent;
    }
    DefaultSignalMastLogic* parent;
    void propertyChange(PropertyChangeEvent *e)
    {
        SignalMast* mast = (SignalMast*) e->getSource();
        if ((mast==parent->source) && (e->getPropertyName()==("Held")))
        {
            if(parent->log->isDebugEnabled())
                parent->log->debug("source mast change " +mast->getDisplayName() + " " + e->getPropertyName());
            parent->setSignalAppearance();
        }
    }
};

class DestinationMast : public QObject
{
 Q_OBJECT
 public:
    DestinationMast(SignalMast* destination, DefaultSignalMastLogic* dsml);

    DefaultSignalMastLogic* dsml;
    void updateDestinationMast(SignalMast* newMast);
      QString getComment();
      void setComment(QString comment);
      bool isActive();
      float getMinimumSpeed();
      void setEnabled();
      void setDisabled() ;
      bool isEnabled();
      int store;// = STOREALL;;
      void setStore(int store);
      int getStoreState();
      bool isTurnoutLockAllowed();
      void allowTurnoutLock(bool lock);
      void setTurnouts(QHash<NamedBeanHandle<Turnout*>*, int> turnouts);
      void setAutoTurnouts(QHash<Turnout*, int> turnouts);
      void setBlocks(QHash<Block*, int> blocks);
      /*public*/ void setAutoBlocks(QMap<Block*, int> blocks);
      void setMasts(QHash<SignalMast*, QString> masts);
      void setAutoMasts(QHash<SignalMast*, QString> newAutoMasts, bool overright);
      void setSensors(QHash<NamedBeanHandle<Sensor*>*, int> sensors);
      void addSensor(NamedBeanHandle<Sensor*>* sen, int state);
      void removeSensor(NamedBeanHandle<Sensor*>* sen);

      QList<Block*> getBlocks();
      QList<Block*> getAutoBlocks();
      QList<Turnout*> getTurnouts();
      QList<NamedBeanHandle<Turnout*>* > getNamedTurnouts();
      QList<Turnout*> getAutoTurnouts();
      QList<SignalMast*> getSignalMasts();
      QList<SignalMast*> getAutoSignalMasts();
      QList<Sensor*> getSensors();
      QList<NamedBeanHandle<Sensor*>* > getNamedSensors();
      bool isBlockIncluded(Block* block);
      bool isAutoBlockIncluded(LayoutBlock* block);
      bool isAutoBlockIncluded(Block* block);
      bool isBlockIncluded(LayoutBlock* block);
      bool isTurnoutIncluded(Turnout* turnout);
      bool isSensorIncluded(Sensor* sensor);
      bool isSignalMastIncluded(SignalMast* signal);
      int getAutoBlockState(Block* block);
      int getBlockState(Block* block);
      int getSensorState(Sensor* sensor);
      int getTurnoutState(Turnout* turnout);
      int getAutoTurnoutState(Turnout* turnout);
      QString getSignalMastState(SignalMast* mast);
      QString getAutoSignalMastState(SignalMast* mast);
      void checkState();
      void checkStateDetails();
      void initialise();
      void useLayoutEditor(bool boo) throw (JmriException) ;
      void useLayoutEditorDetails(bool turnouts, bool blocks) throw (JmriException);
      void setupLayoutEditorDetails() throw (JmriException);
      void setupAutoSignalMast(SignalMastLogic* sml, bool overright);
      void addAutoSignalMast(SignalMast* mast);
      void removeAutoSignalMast(SignalMast* mast);
      bool useLayoutEditor();
      bool useLayoutEditorBlocks();
      bool useLayoutEditorTurnouts();
      bool allowAutoSignalMastGeneration;// = false;
      bool allowAutoSignalMastGen();
      void allowAutoSignalMastGen(bool gen) ;
      void dispose();
      void lockTurnouts();
      void clearTurnoutLock();

 private:
    LayoutBlock* destinationBlock;// = NULL;
    LayoutBlock* protectingBlock;

    //QHash<NamedBeanHandle<Turnout>, Integer> turnouts = new QHash<NamedBeanHandle<Turnout>, Integer>(0);
    QList<NamedBeanSetting*> userSetTurnouts;// =  QList<NamedBeanSetting*>(0);
    QHash<Turnout*, int> autoTurnouts;// = new QHash<Turnout, Integer>(0);
    //QHash<Turnout, Boolean> turnoutThroats = new QHash<Turnout, Boolean>(0);
    //QHash<Turnout, Boolean> autoTurnoutThroats = new QHash<Turnout, Boolean>(0);

    QList<NamedBeanSetting*> userSetMasts;// = new QList<NamedBeanSetting>(0);
    QHash<SignalMast*, QString> autoMasts;// = new QHash<SignalMast, QString>(0);
    QList<NamedBeanSetting*> userSetSensors;// = new QList<NamedBeanSetting>(0);
    QList<NamedBeanSetting*> userSetBlocks;// = new QList<NamedBeanSetting>(0);
    bool turnoutThrown;// = false;
    bool permissiveBlock;// = false;
    bool disposed;// = false;

    QList<LevelXing*> blockInXings;// = new QList<LevelXing>();

    //autoBlocks are for those automatically generated by the system.
    QMap<Block*, int> autoBlocks;// = new LinkedHashMap<Block, Integer>(0);

    QList<Block*> xingAutoBlocks;// = new QList<Block>(0);
    //SignalMast* source;
    SignalMast* destination;
    bool active;// = false;
    bool destMastInit;// = false;

    float minimumBlockSpeed;// = 0.0f;

    bool _useLayoutEditor;// = false;
    bool _useLayoutEditorTurnouts;// = false;
    bool _useLayoutEditorBlocks;// = false;
    bool _lockTurnouts;// = false;
    QString comment;
    bool enable;// = true;
    Logger* log;
    bool inWait;// = false;
    QThread* thr;// = NULL;


    protected:
    /*protected*/ void calculateSpeed();
    /*protected*/ PropertySensorListener* propertySensorListener;// = new PropertySensorListener(this) ;
    /*protected*/ PropertyTurnoutListener* propertyTurnoutListener;// = new PropertyTurnoutListener(this) ;
    /*protected*/ PropertyBlockListener* propertyBlockListener;// = new PropertyBlockListener();
    /*protected*/ PropertySignalMastListener* propertySignalMastListener;// = new PropertySignalMastListener() ;
    PropertyDestinationMastListener* propertyDestinationMastListener;
    /*protected*/ bool IsSensorIncluded(Sensor* sen);
    friend class PropertySensorListener;
    friend class PropertyTurnoutListener;
    friend class PropertyBlockListener;
    friend class PropertySignalMastListener;
 friend class DefaultSignalMastLogic;
};

class NamedBeanSetting
{
public:
      NamedBeanHandle<NamedBean*>* namedBean;
      int setting;
      QString strSetting;
      NamedBeanSetting(NamedBeanHandle<NamedBean*>* namedBean, int setting)
      {
          this->namedBean = namedBean;
          this->setting = setting;
      }

      NamedBeanSetting (NamedBeanHandle<NamedBean*>* namedBean, QString setting){
          this->namedBean = namedBean;
          strSetting = setting;
      }

      NamedBean* getBean(){
          return (NamedBean*)namedBean->getBean();
      }

      NamedBeanHandle<NamedBean*>* getNamedBean(){
          return namedBean;
      }
      int getSetting(){
          return setting;
      }

      QString getStringSetting(){
          return strSetting;
      }

      QString getBeanName(){
          return namedBean->getName();
      }
  };

class PropertySensorListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertySensorListener(DestinationMast* parent)
    {
     this->parent = parent;
    }
    DestinationMast* parent;
public slots:
    void propertyChange(PropertyChangeEvent *e)
    {
     Sensor* sen = (Sensor*) e->getSource();
     parent->log->debug(parent->dsml->source->getDisplayName() + " to " + parent->destination->getDisplayName() + " destination sensor "+ sen->getDisplayName() + "trigger " + e->getPropertyName());
     if (e->getPropertyName()==("KnownState"))
     {
      int now = e->getNewValue().toInt();
      parent->log->debug("current value " + QString::number(now) + " value we want " + QString::number(parent->getSensorState(sen)));
      if (parent->IsSensorIncluded(sen) && parent->getSensorState(sen)!=now)
      {
       //if(log.isDebugEnabled())
       parent->log->debug("Sensor " + sen->getDisplayName() + " caused the signalmast to be set to danger");
       //getSourceMast().setAspect(stopAspect);
       if (parent->active==true)
       {
        parent->active=false;
        parent->dsml->setSignalAppearance();
       }
      }
      else if (parent->getSensorState(sen)==now)
      {
       //if(log.isDebugEnabled())
       parent->log->debug(parent->destination->getDisplayName() + " sensor " + sen->getDisplayName() + " triggers a calculation of change");
       parent->checkState();
      }
     }
    }
};
class PropertyTurnoutListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertyTurnoutListener(DestinationMast* parent)
    {
     this->parent = parent;
    }
    DestinationMast* parent;
    void propertyChange(PropertyChangeEvent *e)
    {
     Turnout* turn = (Turnout*) e->getSource();
     //   log.debug(destination.getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger");
     if (e->getPropertyName()==("KnownState"))
     {
      //Need to check this against the manual list vs auto list
      //The manual list should over-ride the auto list
      int now =  e->getNewValue().toInt();
      if(parent->isTurnoutIncluded(turn))
      {
       if (parent->getTurnoutState(turn)!=now)
       {
        if(parent->log->isDebugEnabled())
        {
         parent->log->debug("Turnout " + turn->getDisplayName() + " caused the signalmast to be set");
         parent->log->debug("From " + parent->dsml->getSourceMast()->getDisplayName() + " to " + parent->destination->getDisplayName() + " Turnout " + turn->getDisplayName() + " caused the signalmast to be set to danger");
        }
        if (parent->active==true)
        {
         parent->active=false;
         parent->dsml->setSignalAppearance();
        }
       }
       else
       {
        if(parent->log->isDebugEnabled())
         parent->log->debug(parent->destination->getDisplayName() + " turnout " + turn->getDisplayName() + " triggers a calculation of change");
        parent->checkState();
       }
      }
      else if(parent->autoTurnouts.contains(turn))
      {
       if (parent->getAutoTurnoutState(turn)!=now)
       {
        if(parent->log->isDebugEnabled())
        {
         parent->log->debug("Turnout " + turn->getDisplayName() + " auto caused the signalmast to be set");
         parent->log->debug("From " + parent->dsml->getSourceMast()->getDisplayName() + " to" + parent->destination->getDisplayName() + " Auto Turnout " + turn->getDisplayName() + " auto caused the signalmast to be set to danger");
        }
        if (parent->active==true)
        {
         parent->active=false;
         parent->dsml->setSignalAppearance();
        }
       }
       else
       {
        if(parent->log->isDebugEnabled())
         parent->log->debug("From " + parent->dsml->getSourceMast()->getDisplayName() + " to " + parent->destination->getDisplayName() + " turnout " + turn->getDisplayName() + " triggers a calculation of change");
        parent->checkState();
       }
      }
    }
    else if ((e->getPropertyName()==("TurnoutStraightSpeedChange")) || (e->getPropertyName()==("TurnoutDivergingSpeedChange")))
     {
      parent->calculateSpeed();
     }
    }
};
class PropertyBlockListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertyBlockListener(DestinationMast* parent)
    {
     this->parent = parent;
    }
    DestinationMast* parent;
    void propertyChange(PropertyChangeEvent *e)
    {
     Block* block = (Block*) e->getSource();
     if(parent->log->isDebugEnabled())
      parent->log->debug(parent->destination->getDisplayName() + " destination block "+ block->getDisplayName() + " trigger " +e->getPropertyName() + " " + e->getNewValue().toString());
        if (e->getPropertyName()==("state"))
        {
            int now = e->getNewValue().toInt();
            if(parent->log->isDebugEnabled())
            {
                parent->log->debug(QString("%1").arg(parent->isBlockIncluded(block)?"true":"false"));
                parent->log->debug(QString("%1").arg(parent->autoBlocks.contains(block)?"true":"false"));
            }
            if (parent->isBlockIncluded(block)){
                if(parent->log->isDebugEnabled()){
                    parent->log->debug(parent->destination->getDisplayName() + " in manual block");
                    parent->log->debug(parent->getBlockState(block) + "  " + QString::number(now));
                }
                /*if (getBlockState(block) != now){
                    if(parent->log->isDebugEnabled()){
                        parent->log->debug("Block " + block.getDisplayName() + " caused the signalmast to be set");
                        parent->log->debug(destination.getDisplayName() + " Block " + block.getDisplayName() + " caused the signalmast to be set");
                    }
                    if (active==true){
                        active=false;
                        setSignalAppearance();
                    }
                } else {
                    if(parent->log->isDebugEnabled())
                        parent->log->debug(destination.getDisplayName() + " block " + block.getDisplayName() + " triggers a calculation of change");
                    checkState();
                }*/
                parent->checkState();
            } else if (parent->autoBlocks.contains(block)){
                if(parent->log->isDebugEnabled()){
                    parent->log->debug(parent->destination->getDisplayName() + " in auto block");
                    parent->log->debug(parent->getAutoBlockState(block) + "  " + QString::number(now));
                }
                /*if (getAutoBlockState(block) != now){
                    if(parent->log->isDebugEnabled()){
                        parent->log->debug("Block " + block.getDisplayName() + " caused the signalmast to be set");
                        parent->log->debug(destination.getDisplayName() + " auto Block " + block.getDisplayName() + " caused the signalmast to be set");
                    }
                    if (active==true){
                        active=false;
                        setSignalAppearance();

                    }
                } else {
                    if(parent->log->isDebugEnabled())
                        parent->log->debug(destination.getDisplayName() + " auto block " + block.getDisplayName() + " triggers a calculation of change");
                    checkState();
                }*/
                parent->checkState();
            } else if(parent->log->isDebugEnabled()) {
                parent->log->debug(parent->destination->getDisplayName() + " Not found");
            }
        } else if (e->getPropertyName()==("BlockSpeedChange")) {
            parent->calculateSpeed();
        }
    }
};
class PropertySignalMastListener : public PropertyChangeListener
{
 Q_OBJECT
public:
    PropertySignalMastListener(DestinationMast* parent)
    {
     this->parent = parent;
    }
    DestinationMast* parent;
    void propertyChange(PropertyChangeEvent *e)
    {
     SignalMast* mast = (SignalMast*) e->getSource();
     if(parent->log->isDebugEnabled())
       parent->log->debug(parent->destination->getDisplayName() + " signalmast change " + mast->getDisplayName() + " " + e->getPropertyName());
     //   parent->log->debug(destination.getDisplayName() + " destination sensor "+ sen.getDisplayName() + "trigger");
        if (e->getPropertyName()==("Aspect")) {

            QString now = ((QString) e->getNewValue().toString());
            if(parent->log->isDebugEnabled())
                parent->log->debug(parent->destination->getDisplayName() + " match property " + now);
            if(parent->isSignalMastIncluded(mast)){
                if (now!=(parent->getSignalMastState(mast)))
                {
                    if(parent->log->isDebugEnabled()) {
                        parent->log->debug(parent->destination->getDisplayName() + " in mast list SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
                        parent->log->debug("SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
                    }
                    if (parent->active){
                        parent->active=false;
                        parent->dsml->setSignalAppearance();
                    }
                } else {
                    if(parent->log->isDebugEnabled())
                        parent->log->debug(parent->destination->getDisplayName() + " in mast list signalmast change");
                    parent->checkState();
                }
            } else if (parent->autoMasts.contains(mast)){
                if (now!=(parent->getAutoSignalMastState(mast))){
                    if(parent->log->isDebugEnabled()){
                        parent->log->debug("SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
                        parent->log->debug(parent->destination->getDisplayName() + " in auto mast list SignalMast* " + mast->getDisplayName() + " caused the signalmast to be set");
                    }
                    if (parent->active){
                        parent->active=false;
                        parent->dsml->setSignalAppearance();
                    }
                } else {
                    if(parent->log->isDebugEnabled())
                        parent->log->debug(parent->destination->getDisplayName() + " in auto mast list signalmast change");
                    parent->checkState();
                }
            }
        }
    }
};

#endif // DEFAULTSIGNALMASTLOGIC_H
