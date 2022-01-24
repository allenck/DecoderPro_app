#ifndef ABSTRACTSIGNALHEAD_H
#define ABSTRACTSIGNALHEAD_H
#include "abstractnamedbean.h"
#include "../Signal/signalhead.h"
#include <QVector>

class Turnout;
class LIBPR3SHARED_EXPORT AbstractSignalHead :  public SignalHead
{
    Q_OBJECT
public:
    //explicit AbstractSignalHead(QObject *parent = 0);
    /*public*/ AbstractSignalHead(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ AbstractSignalHead(QString systemName, QObject *parent = 0);
    /*public*/ QString getAppearanceName(int appearance)override;
    /*public*/ QString getAppearanceName()override;
    /*public*/ int getAppearance()override;
    /*public*/ bool isCleared()override;
    /*public*/ bool isShowingRestricting()override;
    /*public*/ bool isAtStop()override;
    /*public*/ bool getLit()override;
    /*public*/ bool getHeld()override;
    /*public*/ void setState(int s)override;
    /*public*/ int getState()override;
    /*public*/ static QVector<int> getDefaultValidStates();
    /*public*/ static const QVector<QString> getDefaultValidStateNames();
    /*public*/ static const QString getDefaultStateName(int appearance);
    /*public*/ QVector<int> getValidStates()override;
    /*public*/ QVector<QString> getValidStateNames()override;
    /*public*/ QString getBeanType()override;

signals:
    //void propertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
    //void propertyChange(PropertyChangeEvent *);
public slots:
 /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ override;

private:
    /*private*/ static const  QVector<int> validStates;// = new int[]{
//        DARK,
//        RED,
//        YELLOW,
//        GREEN,
//        LUNAR,
//        FLASHRED,
//        FLASHYELLOW,
//        FLASHGREEN,
//        FLASHLUNAR
//    };
    /*private*/ static const QVector<QString> validStateNames;
 virtual bool isTurnoutUsed(Turnout* /*t*/) {return false;}
protected:
    /*protected*/ int mAppearance;// = DARK;
    /**
     * By default, signals are lit.
     */
    /*protected*/ bool mLit;// = true;
    /**
     * By default, signals are not held.
     */
    /*protected*/ bool mHeld;// = false;

};

#endif // ABSTRACTSIGNALHEAD_H
