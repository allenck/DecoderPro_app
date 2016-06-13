#ifndef QUADOUTPUTSIGNALHEAD_H
#define QUADOUTPUTSIGNALHEAD_H

#include "tripleturnoutsignalhead.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT QuadOutputSignalHead : public TripleTurnoutSignalHead
{
    Q_OBJECT
public:
    //explicit QuadOutputSignalHead(QObject *parent = 0);
    /*public*/ QuadOutputSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, NamedBeanHandle<Turnout*> *lunar, QObject *parent = 0) ;
    /*public*/ QuadOutputSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, NamedBeanHandle<Turnout*>* lunar, QObject *parent = 0);
    /*public*/ void dispose();
    /*public*/ NamedBeanHandle<Turnout*>* getLunar() ;
    /*public*/ void setLunar(NamedBeanHandle<Turnout*>* t);
    /*public*/ QVector<int> getValidStates() ;
    /*public*/ QVector<QString> getValidStateNames();

signals:

public slots:
private:
    NamedBeanHandle<Turnout*>* mLunar;
    /*final*/ static /*private*/QVector<int> validStates;
    /*final*/ static /*private*/ QVector<QString> validStateNames ;

protected:
    /*protected*/ void updateOutput();

};

#endif // QUADOUTPUTSIGNALHEAD_H
