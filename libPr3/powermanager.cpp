#include "powermanager.h"

PowerManager::PowerManager(QObject *parent) :
    QObject(parent)
{
}
const int PowerManager::UNKNOWN = 0;
const int PowerManager::ON      = 2;
const int PowerManager::OFF     = 4;

