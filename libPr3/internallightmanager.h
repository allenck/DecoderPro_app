#ifndef INTERNALLIGHTMANAGER_H
#define INTERNALLIGHTMANAGER_H
#include "abstractlightmanager.h"
#include "abstractvariablelight.h"


class LIBPR3SHARED_EXPORT InternalLightManager : public AbstractLightManager
{
    Q_OBJECT
public:
 explicit InternalLightManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ bool validSystemNameConfig(QString systemName);
    /*public*/ bool supportsVariableLights(QString systemName);
    /*public*/ bool allowMultipleAdditions(QString systemName);
    /*public*/ SystemConnectionMemo* getMemo();
    /*public*/ QString getEntryToolTip();


signals:

public slots:
protected:
 /*protected*/ Light* createNewLight(QString systemName, QString userName);

};

class AbstractVariableLightO1 : public  AbstractVariableLight
{
 Q_OBJECT
public:
 AbstractVariableLightO1(QString systemName, QString userName)
  : AbstractVariableLight(systemName, userName) {}
    //protected void forwardCommandChangeToLayout(int s) {}
 protected:
    //@Override
    /*protected*/ void sendIntensity(double /*intensity*/) {
    }

    //@Override
    /*protected*/ void sendOnOffCommand(int /*newState*/) {
    }

    //@Override
    /*protected*/ int getNumberOfSteps() {
        return 100;
    }
};

#endif // INTERNALLIGHTMANAGER_H
