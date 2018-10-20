#ifndef SQL_H
#define SQL_H

#include <QObject>
#include "locoiodata.h"
#include <QSqlDatabase>
#include <QSqlRecord>
#include "locoio_global.h"

class LOCOIOSHARED_EXPORT Sql : public QObject
{
 Q_OBJECT
public:
 explicit Sql(LocoIOData* data, QObject *parent = nullptr);
 void setData(LocoIOData* data);
 bool isOpen();
 bool isValid();
 bool updateComment(int port, QString type, QString title, QString description);
 bool updateBasicComments(int port, QString type);
 bool deleteComment(int port);
 bool commentRecordExists(int port);
 QSqlRecord getComments(int port);
 bool changeAddress(int oldUnitAddress, int oldUnitSubAddress, int newUnitAddress, int newUnitSubAddress);
 bool rfidPortExists(QString serial);
 bool updateRfidPort(QString serial, int block,  QString description);
 bool deleteRfidPort(QString serial);
 QSqlRecord getRfidPort(QString serial);

signals:
 void error(QString str);
public slots:

private:
 LocoIOData* data;
 QString dbFileName;
 QSqlDatabase db;
};

#endif // SQL_H
