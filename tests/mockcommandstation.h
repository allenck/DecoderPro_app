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
 /*public*/ bool sendPacket(QByteArray packet, int repeats)override;
 /*public*/ QString getUserName()override;
 /*public*/ QString getSystemPrefix()override;
 /*public*/ QByteArray lastPacket;
 /*public*/ QObject* self() override{return (QObject*)this;}

private:
 QString name = "I";

};

#endif // MOCKCOMMANDSTATION_H
