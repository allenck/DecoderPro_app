#ifndef ABSTRACTSIGNALMAST_H
#define ABSTRACTSIGNALMAST_H
#include "signalmast.h"
#include "exceptions.h"

class DefaultSignalAppearanceMap;
class SignalSystem;
class SignalAppearanceMap;
class LIBPR3SHARED_EXPORT AbstractSignalMast : public SignalMast
{
    Q_OBJECT
public:
   // explicit AbstractSignalMast(QObject *parent = 0);
    /*public*/ AbstractSignalMast(QString systemName, QString userName, QObject *parent = 0);
 /*public*/ AbstractSignalMast(QString systemName, QObject *parent = 0);
    /*public*/ void setAspect(QString aspect) ;
    /*public*/ QString getAspect() ;
    /*public*/ QString getSpeed() ;
    /*public*/ int getState();
    /*public*/ void setState(int i);
    /*public*/ bool getLit();
    /*public*/ bool getHeld() ;
    /*public*/ void setLit(bool newLit);
    /*public*/ void setHeld(bool newHeld);
    void configureSignalSystemDefinition(QString name);
    void configureAspectTable(QString signalSystemName, QString aspectMapName);
    /*public*/ SignalSystem* getSignalSystem();
    /*public*/ SignalAppearanceMap* getAppearanceMap();
    /*public*/ QVector<QString> getValidAspects();
    /*public*/ QVector<QString> getAllKnownAspects();
    /*public*/ void setAspectDisabled(QString aspect);
    /*public*/ void setAspectEnabled(QString aspect);
    /*public*/QStringList* getDisabledAspects();
    /*public*/ bool isAspectDisabled(QString aspect);
    /*public*/ void setAllowUnLit(bool boo);
    /*public*/ bool allowUnLit();
    /*public*/ void vetoableChange(PropertyChangeEvent* evt); /*throws java.beans.PropertyVetoException*/
    /*public*/ QString getBeanType();
signals:

public slots:
private:
    /*private*/ bool mLit;// = true;
    Logger* log;
    /*private*/ bool mHeld;// = false;
    DefaultSignalAppearanceMap* map;
    SignalSystem* systemDefn;
    QStringList* disabledAspects;// = new QStringList(1);
    void common();
    bool _allowUnLit;
protected:
    /*protected*/ QString aspect;// = NULL;
    /*protected*/ QString speed;// = NULL;

friend class SignalHeadSignalMast;
friend class TurnoutSignalMast;
friend class VirtualSignalMast;
};

#endif // ABSTRACTSIGNALMAST_H
