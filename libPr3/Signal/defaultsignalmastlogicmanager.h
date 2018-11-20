#ifndef DEFAULTSIGNALMASTLOGICMANAGER_H
#define DEFAULTSIGNALMASTLOGICMANAGER_H
#include <QList>
#include "exceptions.h"
#include "signalmastlogicmanager.h"
#include <QMutex>
#include "logger.h"
#include "signalmastlogic.h"


class SignalSpeedMap;
class SignalMastLogic;
class SignalMast;
class PropertyChangeSupport;
class PropertyChangeListener;
class PropertyBlockManagerListener;
class LIBPR3SHARED_EXPORT DefaultSignalMastLogicManager : public SignalMastLogicManager
{
    Q_OBJECT
public:
    explicit DefaultSignalMastLogicManager(QObject *parent = 0);
    ~DefaultSignalMastLogicManager() {}
    DefaultSignalMastLogicManager(const DefaultSignalMastLogicManager&) : SignalMastLogicManager() {}
    /*public*/ int getXMLOrder();
    /*public*/ /*final*/ static SignalSpeedMap* getSpeedMap();
    /*public*/ SignalMastLogic* getSignalMastLogic(SignalMast* source);
    /*public*/ SignalMastLogic* newSignalMastLogic(SignalMast* source);
    /*public*/ void replaceSignalMast(SignalMast* oldMast, SignalMast* newMast);
    /*public*/ void swapSignalMasts(SignalMast* mastA, SignalMast* mastB);
    /*public*/ QList<SignalMastLogic*> getLogicsByDestination(SignalMast* destination);
    /*public*/ QList<SignalMastLogic*> getSignalMastLogicList();
    /*public*/ bool isSignalMastUsed(SignalMast* mast);
    /*public*/ void removeSignalMastLogic(SignalMastLogic* sml, SignalMast* dest);
    /*public*/ void removeSignalMastLogic(SignalMastLogic* sml);
    /*public*/ void removeSignalMast(SignalMast* mast);
    /*public*/ void disableLayoutEditorUse(SignalMast* mast);
    /*public*/ void dispose() ;
    /*public*/ void initialise();
    /*public*/ NamedBean* getBeanBySystemName(QString systemName);
    /*public*/ NamedBean* getBeanByUserName(QString userName);
    /*public*/ NamedBean* getNamedBean(QString name);
    /*public*/ QString getSystemPrefix() ;
    /*public*/ char typeLetter();
    /*public*/ QString makeSystemName(QString s) ;
    /*public*/ QStringList getSystemNameArray() ;
    /*public*/ QStringList getSystemNameList();
    /*public*/ QSet<NamedBean*> getNamedBeanSet();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ void Register(NamedBean* n) ;
    /*public*/ void deregister(NamedBean* n);
    /*public*/ long getSignalLogicDelay();
    /*public*/ void setSignalLogicDelay(long l);
    /*public*/ void discoverSignallingDest(SignalMast* source, LayoutEditor* layout) throw (JmriException);
    /*public*/ void automaticallyDiscoverSignallingPairs() throw (JmriException);
    /*public*/ void generateSection();


signals:
    void on_newSignalMastLogicCreated(SignalMastLogic*);
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
    Logger* log;
    /*private*/ static SignalSpeedMap* _speedMap;// = SignalSpeedMap.getMap();
    QList<SignalMastLogic*> signalMastLogic;// = new QList<SignalMastLogic*>();
    //PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    long signalLogicDelay;// = 500L;
    bool runWhenStablised;// = false;
    QMutex mutex;

protected:
    /*protected*/ void registerSelf();
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    /*protected*/ PropertyBlockManagerListener* propertyBlockManagerListener;// = new PropertyBlockManagerListener();
 friend class PropertyBlockManagerListener;
};
Q_DECLARE_METATYPE(DefaultSignalMastLogicManager)

class PropertyBlockManagerListener : public PropertyChangeListener
{
public:
 PropertyBlockManagerListener(DefaultSignalMastLogicManager* dsmlm)
 {
  this->dsmlm = dsmlm;
 }
 /*public*/ void propertyChange(PropertyChangeEvent* e)
 {
  if(e->getPropertyName()==("topology"))
  {
   //boolean newValue = new Boolean.parseBoolean(String.valueOf(e.getNewValue()));
   bool newValue = e->getNewValue().toBool();
   if(newValue)
   {
    for(int i = 0; i <dsmlm->signalMastLogic.size(); i++)
    {
     dsmlm->signalMastLogic.at(i)->setupLayoutEditorDetails();
    }
    if(dsmlm->runWhenStablised)
    {
     try
     {
            dsmlm->automaticallyDiscoverSignallingPairs();
     } catch (JmriException je)
     {
         //Considered normal if routing not enabled
     }
    }
   }
  }
 }
private:
 DefaultSignalMastLogicManager* dsmlm;
};
#endif // DEFAULTSIGNALMASTLOGICMANAGER_H
