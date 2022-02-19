#ifndef INTERNALLIGHTMANAGER_H
#define INTERNALLIGHTMANAGER_H
#include "abstractlightmanager.h"
#include "abstractvariablelight.h"
#include "preferNumericComparator.h"

class LIBPR3SHARED_EXPORT InternalLightManager : public AbstractLightManager
{
    Q_OBJECT
public:
 explicit InternalLightManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ bool validSystemNameConfig(QString systemName) override;
    /*public*/ bool supportsVariableLights(QString systemName) override;
    /*public*/ bool allowMultipleAdditions(QString systemName) override;
    /*public*/ SystemConnectionMemo* getMemo() override;
    /*public*/ QString getEntryToolTip() override;
    /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }
  /*public*/ QString toString() override {return "InternalLightManager";}
  QObject* vself() override { return (QObject*)this;}

signals:

public slots:
protected:
 /*protected*/ Light* createNewLight(QString systemName, QString userName) override;

};

class AbstractVariableLightO1 : public  AbstractVariableLight
{
 Q_OBJECT
public:
 AbstractVariableLightO1(QString systemName, QString userName)
  : AbstractVariableLight(systemName, userName) {}
//    /*public*/ QString getSystemName() const override {
//     return getSystemName();
//    }
    //QObject* self() override {return this;}
    //@Override
    /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, NamedBean* n) override{
        return (new PreferNumericComparator())->compare(suffix1, suffix2);
    }
 protected:
    //@Override
    /*protected*/ void sendIntensity(double /*intensity*/) override{
    }

    //@Override
    /*protected*/ void sendOnOffCommand(int /*newState*/) override{
    }

    //@Override
    /*protected*/ int getNumberOfSteps() override{
        return 100;
    }
};

#endif // INTERNALLIGHTMANAGER_H
