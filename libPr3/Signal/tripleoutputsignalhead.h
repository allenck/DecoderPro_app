#ifndef TRIPLEOUTPUTSIGNALHEAD_H
#define TRIPLEOUTPUTSIGNALHEAD_H
#include "doubleturnoutsignalhead.h"

class TripleOutputSignalHead : public DoubleTurnoutSignalHead
{
public:
 /*public*/ TripleOutputSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* blue, NamedBeanHandle<Turnout*>* red, QObject* parent = nullptr);
 /*public*/ TripleOutputSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* blue, NamedBeanHandle<Turnout*>* red, QObject* parent = nullptr);
 /*public*/ void dispose();
 /*public*/ NamedBeanHandle<Turnout*>* getBlue();
 /*public*/ void setBlue(NamedBeanHandle<Turnout*>* t);
 /*public*/ QVector<int> getValidStates();
 /*public*/ QVector<QString> getValidStateNames();

private:
 static Logger* log;
 NamedBeanHandle<Turnout*>* mBlue;
 /*final*/ static /*private*/ QVector<int> validStates;
 /*final*/ static /*private*/ QVector<QString> validStateNames;
 bool isTurnoutUsed(Turnout* t);
 void readOutput();


protected:
 /*protected*/ void updateOutput();

};

#endif // TRIPLEOUTPUTSIGNALHEAD_H
