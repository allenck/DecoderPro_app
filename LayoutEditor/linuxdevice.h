#ifndef LINUXDEVICE_H
#define LINUXDEVICE_H
#include <QObject>
#include "exceptions.h"

/*interface*/class  LinuxDevice  : public QObject
{
 Q_OBJECT
public:
 LinuxDevice(QObject* parent = 0) : QObject(parent) {}
    /*public*/ virtual void close() throw (IOException) {}
};

#endif // LINUXDEVICE_H
