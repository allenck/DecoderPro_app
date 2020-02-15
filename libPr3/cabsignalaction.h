#ifndef CABSIGNALACTION_H
#define CABSIGNALACTION_H
#include "jmriabstractaction.h"

class CabSignalAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 CabSignalAction(QObject* parent);
 /*public*/ CabSignalAction(QString s, WindowInterface* wi);
 /*public*/ CabSignalAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ CabSignalAction(QString s, QObject *parent);


public slots:
 /*public*/ JmriPanel* makePanel();

};

#endif // CABSIGNALACTION_H
