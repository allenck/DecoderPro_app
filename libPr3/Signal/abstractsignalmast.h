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
    /*public*/ void setAspect(QString aspect) override;
    /*public*/ QString getAspect()  override;
    /*public*/ QString getSpeed() ;
    /*public*/ int getState() override;
    /*public*/ void setState(int i) override;
    /*public*/ bool getLit() override;
    /*public*/ bool getHeld() override ;
    /*public*/ void setLit(bool newLit) override;
    /*public*/ void setHeld(bool newHeld) override;
    void configureSignalSystemDefinition(QString name);
    void configureAspectTable(QString signalSystemName, QString aspectMapName);
    /*public*/ SignalSystem* getSignalSystem() override;
    /*public*/ SignalAppearanceMap* getAppearanceMap() override;
    /*public*/ QVector<QString> getValidAspects() override;
    /*public*/ QVector<QString> getAllKnownAspects();
    /*public*/ void setAspectDisabled(QString aspect);
    /*public*/ void setAspectEnabled(QString aspect);
    /*public*/QStringList* getDisabledAspects();
    /*public*/ bool isAspectDisabled(QString aspect) override;
    /*public*/ void setAllowUnLit(bool boo);
    /*public*/ bool allowUnLit();
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) override;
    /*public*/ QString getBeanType() override;
    /*public*/ QString getMastType() override;
    /*public*/ void setMastType(/*@Nonnull*/ QString type) override;

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
    bool _allowUnLit = false;
    QString mastType;

protected:
    /*protected*/ QString aspect;// = NULL;
    /*protected*/ QString speed;// = NULL;

friend class SignalHeadSignalMast;
friend class TurnoutSignalMast;
friend class VirtualSignalMast;
friend class MatrixSignalMast;
};

#endif // ABSTRACTSIGNALMAST_H
