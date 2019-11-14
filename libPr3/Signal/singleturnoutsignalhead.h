#ifndef SINGLETURNOUTSIGNALHEAD_H
#define SINGLETURNOUTSIGNALHEAD_H
#include "defaultsignalhead.h"
#include "namedbeanhandle.h"

class Turnout;
class LIBPR3SHARED_EXPORT SingleTurnoutSignalHead : public DefaultSignalHead
{
    Q_OBJECT
public:
    //explicit SingleTurnoutSignalHead(QObject *parent = 0);
    /*public*/ SingleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* lit, int on, int off, QObject *parent = 0);
    /*public*/ SingleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* lit, int on, int off, QObject *parent = 0);
    ~SingleTurnoutSignalHead() {dispose();}
    /*public*/ void dispose() ;
    /*public*/ int getOnAppearance();
    /*public*/ int getOffAppearance();
    /*public*/ void setOnAppearance(int on);
    /*public*/ void setOffAppearance(int off);
    /*public*/ NamedBeanHandle<Turnout*>* getOutput();
    /*public*/ void setOutput(NamedBeanHandle<Turnout*>* t);
    /*public*/ QVector<int> getValidStates() ;
    /*public*/ QVector<QString> getValidStateNames();
    /*protected*/ void updateOutput(); // needs to be Public for flash to work


signals:

public slots:
private:
    /*private*/ QString getSignalColour(int mAppearance);
    int mOnAppearance;// = DARK;
    int mOffAppearance;// = LUNAR;
    NamedBeanHandle<Turnout*>* mOutput;
    Logger* log;
//friend class DefaultSignalHead;
};

#endif // SINGLETURNOUTSIGNALHEAD_H
