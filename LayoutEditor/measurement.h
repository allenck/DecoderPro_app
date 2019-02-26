#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include "reading.h"

class Measurement : public QObject
{
 Q_OBJECT
public:
 /*public*/ Measurement(Reading* r, QObject *parent= nullptr);
 /*public*/ Measurement(Reading* r, double x, double y, double z, double vsound, int code, QString source, QObject *parent= nullptr);
 /*public*/ Reading* getReading();
 /*public*/ QString getID();
 /*public*/ double getX();
 /*public*/ double getY();
 /*public*/ double getZ();
 /*public*/ double getVSound();
 /*public*/ bool isValidPosition();
 /*public*/ void setValidPosition(bool val);
 /*public*/ int getCode();
 /*public*/ bool isOkPoint();
 /*public*/ QString textCode();
 /*public*/ QVector3D getPoint();
 /*public*/ QVector3D getVector();
 /*public*/ QString getSource();
 /*public*/ QString toString();


signals:

public slots:

private:
 double x, y, z, vsound;
 QString source;
 Reading* r;  // a Reading object is by definition immutable
 bool valid;// = true;
private:
 // provide a quick decimal truncation for formatting
 double truncate(double x);

protected:
 /*protected*/ int code;

};

#endif // MEASUREMENT_H
