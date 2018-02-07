#ifndef DISTRIBUTOR_H
#define DISTRIBUTOR_H

#include <QObject>
#include "reading.h"
#include "measurement.h"

class Logger;
class Reporter;
class Distributor : public QObject
{
 Q_OBJECT
public:
 explicit Distributor(QObject *parent = nullptr);
 /*public*/ static Distributor* instance();
 // /*public*/ void addMeasurementListener(/*MeasurementListener*/Reporter* l);
 /*public*/ void submitReading(Reading* s);
 /*public*/ void submitMeasurement(Measurement* s);

signals:
 void newReading(Reading*);
 void newMeasurement(Measurement*);

public slots:
private:
 static /*volatile*/ /*private*/ Distributor* _instance;// = null;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("Distributor");

};

#endif // DISTRIBUTOR_H
