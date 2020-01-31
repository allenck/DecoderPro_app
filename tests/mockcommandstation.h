#ifndef MOCKCOMMANDSTATION_H
#define MOCKCOMMANDSTATION_H
#include "commandstation.h"

class MockCommandStation : public QObject, public CommandStation
{
 Q_OBJECT
 Q_INTERFACES(CommandStation)
public:
 MockCommandStation(QObject *parent = nullptr);
 /*public*/ MockCommandStation(QString name, QObject *parent = nullptr);
 /*public*/ bool sendPacket(QByteArray packet, int repeats);
 /*public*/ QString getUserName();
 /*public*/ QString getSystemPrefix();
 /*public*/ QByteArray lastPacket;

private:
 QString name = "I";

};

#endif // MOCKCOMMANDSTATION_H
