#include "receiver.h"

using namespace RPS;

/**
 * Holds all the state information for a single receiver.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
  */
///*public*/ class Receiver {

/*public*/ Receiver::Receiver(QVector3D position, QObject *parent) : QObject(parent) {
active = false;
max = 99999;
min = 0;
last = -1;

    this->position = position;
}

/*public*/ void Receiver::setPosition(QVector3D position) {
    this->position = position;
}

/*public*/ QVector3D Receiver::getPosition() {
    return position;
}

/*public*/ bool Receiver::isActive() {
    return active;
}

/*public*/ void Receiver::setActive(bool active) {
    this->active = active;
}

/*public*/ int Receiver::getLastTime() {
    return last;
}

/*public*/ void Receiver::setLastTime(int m) {
    last = m;
}


/*public*/ int Receiver::getMinTime() {
    return min;
}

/*public*/ void Receiver::setMinTime(int m) {
    min = m;
}

/*public*/ int Receiver::getMaxTime() {
    return max;
}

/*public*/ void Receiver::setMaxTime(int m) {
    max = m;
}
