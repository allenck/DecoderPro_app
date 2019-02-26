#ifndef READING_H
#define READING_H

#include <QObject>
#include <QVariant>

class Reading : public QObject
{
 Q_OBJECT
public:
 /*public*/ Reading(QString id, QVector<double>* values, QObject *parent = nullptr);
 /*public*/ Reading(QString id,QVector<double>* values, QString raw, QObject *parent = nullptr);
 /*public*/ Reading(QString id, QVector<double>* values, int time);
 /*public*/ Reading(Reading* r);
 /*public*/ int getTime();
 /*public*/ QString getID();
 /*public*/ int getNValues();
 /*public*/ double getValue(int i);
 /*public*/ QVector<double>* getValues();
 /*public*/ QString toString();
 /*public*/ QVariant getRawData();


signals:

public slots:

private:
 /*final*/ QVariant rawData;
 /*final*/ QString id;
 /*final*/ QVector<double>* values;
 /*final*/ int time; // in msec since epoch

};

#endif // READING_H
