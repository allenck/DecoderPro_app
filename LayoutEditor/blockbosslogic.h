#ifndef BLOCKBOSSLOGIC_H
#define BLOCKBOSSLOGIC_H
#include "siglet.h"
#include "logger.h"
#include "namedbeanhandle.h"
#include "Signal/signalhead.h"
#include "liblayouteditor_global.h"

class Sensor;
class SignalHead;
class Turnout;
class NamedBeanHandleManager;
class LIBLAYOUTEDITORSHARED_EXPORT BlockBossLogic : public Siglet
{
    Q_OBJECT
public:
    //explicit BlockBossLogic(QObject *parent = 0);
    enum LOGIC
    {
    /*static*/ /*public*/ /*final*/ /*int*/ SINGLEBLOCK = 1,
    /*static*/ /*public*/ /*final*/ /*int*/ TRAILINGMAIN = 2,
    /*static*/ /*public*/ /*final*/ /*int*/ TRAILINGDIVERGING = 3,
    /*static*/ /*public*/ /*final*/ /*int*/ FACING = 4
    };
    /*public*/ BlockBossLogic(QObject *parent = 0);
    /*public*/ BlockBossLogic(QString name, QObject *parent=0);
    ~BlockBossLogic();
   /*public*/ QString getDrivenSignal();
    /*public*/ /*@Nonnull*/ NamedBeanHandle<SignalHead *> *getDrivenSignalNamedBean();
   /*public*/ void setSensor1(QString name);
   /*public*/ void setSensor2(QString name);
   /*public*/ void setSensor3(QString name);
   /*public*/ void setSensor4(QString name) ;
   /*public*/ void setSensor5(QString name);
   /*public*/ QString getSensor1();
   /*public*/ QString getSensor2();
   /*public*/ QString getSensor3();
   /*public*/ QString getSensor4();
   /*public*/ QString getSensor5();
   /*public*/ void setTurnout(QString name);
   /*public*/ QString getTurnout();
   /*public*/ void setMode(int mode);
   /*public*/ int getMode();
   /*public*/ void setComment(QString comment);
   /*public*/ QString getComment();
   /*public*/ void setWatchedSignal1(QString name, bool useFlash);
    /*public*/ void setWatchedSignal1Alt(QString name);
    /*public*/ QString getWatchedSignal1();
    /*public*/ QString getWatchedSignal1Alt();
    /*public*/ void setWatchedSignal2(QString name);
    /*public*/ QString getWatchedSignal2() ;
    /*public*/ void setWatchedSignal2Alt(QString name);
    /*public*/ QString getWatchedSignal2Alt();
    /*public*/ void setWatchedSensor1(QString name);
    /*public*/ QString getWatchedSensor1();
    /*public*/ void setWatchedSensor1Alt(QString name);
    /*public*/ QString getWatchedSensor1Alt();
    /*public*/ void setWatchedSensor2(QString name);
    /*public*/ QString getWatchedSensor2();
    /*public*/ void setWatchedSensor2Alt(QString name);
    /*public*/ QString getWatchedSensor2Alt();
    /*public*/ void setLimitSpeed1(bool d) ;
    /*public*/ bool getLimitSpeed1() ;
    /*public*/ void setLimitSpeed2(bool d);
    /*public*/ bool getLimitSpeed2();
    /*public*/ bool getUseFlash() ;
    /*public*/ void setDistantSignal(bool d);
    /*public*/ bool getDistantSignal();
    /*public*/ bool getHold() ;
    /*public*/ void setHold(bool m);
    /*public*/ void setApproachSensor1(QString name);
    /*public*/ QString getApproachSensor1();
    /*public*/ void defineIO() override;
    /*public*/ void setOutput() override;
    int fastestColor1();
    int fastestColor2();
    static int slowerOf(int a, int b);
    static int fasterOf(int a, int b);
    void doSingleBlock();
    void doTrailingMain();
    void doTrailingDiverging();
    void doFacing();
    void doApproach();
    /*public*/ static QListIterator<BlockBossLogic*> entries();
    /*public*/ void retain();
    /*public*/ static BlockBossLogic* getStoppedObject(QString signal);
    /*public*/ static BlockBossLogic* getExisting(QString signal);
    /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean);

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void sensorChange(PropertyChangeEvent*);
    void signalChange(PropertyChangeEvent*);
    void turnoutChange(PropertyChangeEvent*);
private:
    int mode;// = 0;
    Logger* log;
    QString comment;
    bool mHold;// = false;
    QString name;
    NamedBeanHandle<SignalHead*>* driveSignal = NULL;
    NamedBeanHandle<Sensor*>* watchSensor1 = NULL;
    NamedBeanHandle<Sensor*>*  watchSensor2 = NULL;
    NamedBeanHandle<Sensor*>*  watchSensor3 = NULL;
    NamedBeanHandle<Sensor*>*  watchSensor4 = NULL;
    NamedBeanHandle<Sensor*>*  watchSensor5 = NULL;
    NamedBeanHandle<Turnout*>* watchTurnout = NULL;
    NamedBeanHandle<SignalHead*>* watchedSignal1 = NULL;
    NamedBeanHandle<SignalHead*>* watchedSignal1Alt = NULL;
    NamedBeanHandle<SignalHead*>* watchedSignal2 = NULL;
    NamedBeanHandle<SignalHead*>* watchedSignal2Alt = NULL;
    NamedBeanHandle<Sensor*>*  watchedSensor1 = NULL;
    NamedBeanHandle<Sensor*>*  watchedSensor1Alt = NULL;
    NamedBeanHandle<Sensor*>*  watchedSensor2 = NULL;
    NamedBeanHandle<Sensor*>*  watchedSensor2Alt = NULL;
    NamedBeanHandle<Sensor*>*  approachSensor1 = NULL;

    bool limitSpeed1 = false;
    bool limitSpeed2 = false;
    bool protectWithFlashing = false;
    bool distantSignal = false;
    static QHash<QString,BlockBossLogic*>* umap;// = NULL;
    static QHash<QString,BlockBossLogic*>* smap;// = NULL;
    /*private*/ static void setup();

protected:
    /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);
//    /*protected*/ static final java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("jmri.jmrit.blockboss.BlockBossBundle");

 friend class BlockBossLogicProvider;
};
#endif // BLOCKBOSSLOGIC_H
