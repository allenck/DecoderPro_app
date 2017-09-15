#ifndef SENDPACKETACTION_H
#define SENDPACKETACTION_H
#include "abstractaction.h"
#include "liblayouteditor_global.h"

class ActionEvent;
class LIBLAYOUTEDITORSHARED_EXPORT SendPacketAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit SendPacketAction(QObject *parent = 0);
 /*public*/ SendPacketAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* /*e*/);
private:
 void common();

};

#endif // SENDPACKETACTION_H
