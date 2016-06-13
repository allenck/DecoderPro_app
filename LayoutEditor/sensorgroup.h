#ifndef SENSORGROUP_H
#define SENSORGROUP_H

#include <QObject>
#include <QStringList>

class Logger;
class SensorGroup : public QObject
{
 Q_OBJECT
public:
 //explicit SensorGroup(QObject *parent = 0);
 SensorGroup(QString name,QObject *parent= 0);

signals:

public slots:
 void addPressed();

private:
 /*private*/ /*final*/ static QString namePrefix;// = "SENSOR GROUP:";  // should be upper case
 /*private*/ /*final*/ static QString nameDivider;// = ":";

 QString name;
 QStringList sensorList;
 Logger* log;
};

#endif // SENSORGROUP_H
