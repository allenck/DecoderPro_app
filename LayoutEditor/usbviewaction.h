#ifndef USBVIEWACTION_H
#define USBVIEWACTION_H
#include "abstractaction.h"

class Logger;
class UsbViewAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ UsbViewAction(QObject* parent);
 UsbViewAction(QString s, QObject* parent);

public slots:
 /*public*/ void actionPerformed();

private:
 static Logger* log;
};

#endif // USBVIEWACTION_H
