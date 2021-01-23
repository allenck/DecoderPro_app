#ifndef LNCVDEVICES_H
#define LNCVDEVICES_H

#include <QObject>
#include "lncvdevice.h"
#include "propertychangesupport.h"

class Logger;
class LncvDevices : public QObject
{
  Q_OBJECT
 public:
  explicit LncvDevices(QObject *parent = nullptr);
  /*public*/ void addDevice(LncvDevice* d);
  /*public*/ void removeAllDevices();
  /*public*/ int isDeviceExistant(LncvDevice* deviceToBeFound);
  /*public*/ bool deviceExists(LncvDevice* d);
  /*public*/ LncvDevice* getDevice(int index);
  /*public*/ QVector<LncvDevice*> getDevices();
  /*public*/ int size();
  /*public*/ void addPropertyChangeListener(PropertyChangeListener*l);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ /*final*/ QList<LncvDevice*> deviceList;
  PropertyChangeSupport* pcs = new PropertyChangeSupport(this);
};

#endif // LNCVDEVICES_H
