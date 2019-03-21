#ifndef PACKETGENACTION_H
#define PACKETGENACTION_H
#include "abstractaction.h"

class Logger;
class JMRIClientSystemConnectionMemo;
class PacketGenAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ PacketGenAction(QString s, JMRIClientSystemConnectionMemo* memo, QObject* parent);
 /*public*/ PacketGenAction(JMRIClientSystemConnectionMemo* memo, QWidget *parent);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
 JMRIClientSystemConnectionMemo* _memo = nullptr;
 static Logger* log;

};

#endif // PACKETGENACTION_H
