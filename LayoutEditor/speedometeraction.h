#ifndef SPEEDOMETERACTION_H
#define SPEEDOMETERACTION_H
#include "jmriabstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SpeedometerAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 //explicit SpeeometerAction(QObject *parent = 0);
 /*public*/ SpeedometerAction(QString s, WindowInterface* wi);
 /*public*/ SpeedometerAction(QString s, QIcon i, WindowInterface* wi) ;
 /*public*/ SpeedometerAction(QString s, QObject *parent);
 /*public*/ SpeedometerAction(QObject *parent);
 /*public*/ JmriPanel* makePanel();

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0) override;
 
private: 
 void common();
};

#endif // SPEEDOMETERACTION_H
