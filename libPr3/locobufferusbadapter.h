#ifndef LOCOBUFFERUSBADAPTER_H
#define LOCOBUFFERUSBADAPTER_H
#include "locobufferadapter.h"

class LocoBufferAdapter;
class LnTrafficController;
class LnPortController;
class LIBPR3SHARED_EXPORT LocoBufferUsbAdapter : public LocoBufferAdapter
{
    Q_OBJECT
public:
  LocoBufferUsbAdapter(QObject *parent = 0);
  ~LocoBufferUsbAdapter(){}
  void configure();
 /**
  * Get an array of valid baud rates.
  */
 /*public*/ QStringList validBaudRates();
    /**
     * Get an array of valid baud rates as integers. This allows subclasses
     * to change the arrays of speeds.
     */
    /*public*/ QVector<int> validBaudNumbers();
  /*public*/ void  dispose();

signals:
    
public slots:
 private:
  Logger log;
    
protected:
// /*protected*/ void setSerialPort(SerialPort activeSerialPort); // throws gnu.io.UnsupportedCommOperationException {

};

#endif // LOCOBUFFERUSBADAPTER_H
