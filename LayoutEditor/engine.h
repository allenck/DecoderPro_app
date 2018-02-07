#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include "measurement.h"
#include "propertychangeevent.h"
#include "loggerfactory.h"

namespace RPS
{
class Transmitter;
class Receiver;
class Engine : public QObject
{
 Q_OBJECT
public:
 explicit Engine(QObject *parent = nullptr);
 static /*public*/ Engine* instance();
 /*public*/ void dispose();
 /*public*/ void setVSound(double v);
 /*public*/ double getVSound();
 /*public*/ void setOffset(int offset) ;
 /*public*/ int getOffset();
 /*public*/ Transmitter* getTransmitter(int i);
 /*public*/ int getNumTransmitters();
 /*public*/ void setMaxReceiverNumber(int n);
 /*public*/ int getMaxReceiverNumber();
 /*public*/ QVector3D getReceiverPosition(int i);

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
 /*public*/ void notify(Reading* r);

private:
 void loadValues();
 QString algorithm;// = "Ash 2.1";  // default value, configured separately
 /*private*/ double vsound;// = 0.013544;  // 0.013544 inches/usec, .000345 m/usec,
 /*private*/ int offset;// = 0;
 Measurement* lastPoint = NULL;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("Engine");

 QVector<Receiver*>* receivers;
 QThread* pollThread;
 bool pollOutstanding;
 void saveLastMeasurement(QString id, Measurement* m);
 QList<Transmitter*>* transmitters;

protected:
 static /*volatile*/ /*protected*/ Engine* _instance;// = NULL;


};
}
#endif // ENGINE_H
