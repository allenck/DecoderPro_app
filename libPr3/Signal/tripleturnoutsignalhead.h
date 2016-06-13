#ifndef TRIPLETURNOUTSIGNALHEAD_H
#define TRIPLETURNOUTSIGNALHEAD_H

#include "doubleturnoutsignalhead.h"
#include "namedbeanhandle.h"
#include "libPr3_global.h"

class Turnout;
class LIBPR3SHARED_EXPORT TripleTurnoutSignalHead : public DoubleTurnoutSignalHead
{
    Q_OBJECT
public:
    //explicit TripleTurnoutSignalHead(QObject *parent = 0);
    /*public*/ TripleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, QObject *parent = 0);
    /*public*/ TripleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, QObject *parent = 0);
    /*public*/ void dispose();
    /*public*/ NamedBeanHandle<Turnout*>* getYellow();
    /*public*/ void setYellow(NamedBeanHandle<Turnout*>* t);

signals:

public slots:
private:
    NamedBeanHandle<Turnout*>* mYellow;

protected:
    /*protected*/ void updateOutput();
friend class QuadOutputSignalHead;
};

#endif // TRIPLETURNOUTSIGNALHEAD_H
