#include "mockcommandstation.h"

/**
 * Mock to provide a CommandStation object for tests
 *
 * @author	Bob Jacobsen Copyright 2018
 *
 */

// /*public*/ class MockCommandStation : public CommandStation {

    /*public*/ MockCommandStation::MockCommandStation(QObject* parent) : CommandStation(parent) {}
    /*public*/ MockCommandStation::MockCommandStation(QString name, QObject* parent) : CommandStation(parent)
{this->name = name;}

    //@Override
    /*public*/ bool MockCommandStation::sendPacket(QByteArray packet, int repeats) {
        lastPacket = packet;
        return true;
    }

    //@Override
    /*public*/ QString MockCommandStation::getUserName() {
        return name;
    }

    //@Override
    /*public*/ QString MockCommandStation::getSystemPrefix() {
        return name;
    }
