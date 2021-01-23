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
    /*public*/ int getXMLOrder() const override;
    /*public*/ /*final*/ static SignalSpeedMap* getSpeedMap();
    /*public*/ SignalMastLogic* getSignalMastLogic(SignalMast* source) override;
    /*public*/ SignalMastLogic* newSignalMastLogic(SignalMast* source) override;
    /*public*/ void replaceSignalMast(SignalMast* oldMast, SignalMast* newMast);
    /*public*/ void swapSignalMasts(SignalMast* mastA, SignalMast* mastB);
    /*public*/ QList<SignalMastLogic*> getLogicsByDestination(SignalMast* destination) override;
    /*public*/ QList<SignalMastLogic*> getSignalMastLogicList() override;
    /*public*/ bool isSignalMastUsed(SignalMast* mast) override;
    /*public*/ void removeSignalMastLogic(SignalMastLogic* sml, SignalMast* dest) override;
    /*public*/ void removeSignalMastLogic(SignalMastLogic* sml) override;
    /*public*/ void removeSignalMast(SignalMast* mast) override;
    /*public*/ void disableLayoutEditorUse(SignalMast* mast) override;
    /*public*/ void dispose() override ;
    /*public*/ void initialise() override;
    /*public*/ NamedBean* getBeanBySystemName(QString systemName)const override;
    /*public*/ NamedBean* getBeanByUserName(QString userName)const override;
    /*public*/ NamedBean* getNamedBean(QString name)const override;
    /*public*/ QString getSystemPrefix()const override ;
    /*public*/ char typeLetter() const override;
    /*public*/ QString makeSystemName(QString s)const override ;
    /*public*/ QStringList getSystemNameArray()  override;
    /*public*/ QStringList getSystemNameList() override;
//    /*public*/ QSet<NamedBean*> getNamedBeanSet() override;
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ void Register(NamedBean* n)const override ;
    /*public*/ void deregister(NamedBean* n)const override;
    /*public*/ long getSignalLogicDelay() override;
    /*public*/ void setSignalLogicDelay(long l)override;
    /*public*/ void discoverSignallingDest(SignalMast* source, LayoutEditor* layout) throw (JmriException) override;
    /*public*/ void automaticallyDiscoverSignallingPairs() throw (JmriException) override;
    /*public*/ void generateSection();
    QObject* self() {return (QObject*)this;}
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ /*Class<SignalMastLogic>*/QString getNamedBeanClass() const override;
    /*public*/ int setupSignalMastsDirectionSensors() override;
    /*public*/ void removeSignalMastsDirectionSensors() override;

signals:
    void on_newSignalMastLogicCreated(SignalMastLogic*);
    void propertyChange(PropertyChangeEvent*);

public slots:
private:
    Logger* log;
    /*private*/ static SignalSpeedMap* _speedMap;// = SignalSpeedMap.getMap();
    QList<SignalMastLogic*> signalMastLogic;// = new QList<SignalMastLogic*>();
    long signalLogicDelay;// = 500L;
    bool runWhenStablised;// = false;
    QMutex mutex;

protected:
    /*protected*/ void registerSelf();
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    /*protected*/ PropertyBlockManagerListener* propertyBlockManagerListener;// = new PropertyBlockManagerListener();
 friend class PropertyBlockManagerListener;
 friend class SignallingSourcePanel;
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
