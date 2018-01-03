#ifndef USBVIEWACTION_H
#define USBVIEWACTION_H
#include "abstractaction.h"

class Logger;
class UsbViewAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ UsbViewAction(QObject* parent = 0);
 UsbViewAction(QString s, QObject* parent);
 ~UsbViewAction() {}
 UsbViewAction(const UsbViewAction&) : AbstractAction() {}

public slots:
 /*public*/ void actionPerformed();

private:
 static Logger* log;
};
Q_DECLARE_METATYPE(UsbViewAction)
#endif // USBVIEWACTION_H
