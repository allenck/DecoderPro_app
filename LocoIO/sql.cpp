#include "sql.h"
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>
#include <QMessageBox>

Sql::Sql(LocoIOData* data, QObject *parent) :
    QObject(parent)
{
 this->data = data;
 QStringList drivers = QSqlDatabase::drivers();
 QString sDrivers = "Available drivers: ";
 foreach (QString s, drivers) {
     sDrivers.append(s);
     sDrivers.append(" ");
  }

 if(!QSqlDatabase::isDriverAvailable("QSQLITE"))
 {
  qDebug()<< "QSQLITE driver not available";
  //std::cout << "QSQLITE driver not available";
  QMessageBox::warning(nullptr,"Warning","QSQLITE driver not available. \n"+ sDrivers);
 }
 dbFileName = QDir::homePath() + QDir::separator() + "LocoNetMonitor.db";
 std::cout << dbFileName.toLatin1().constData();
 db = QSqlDatabase::addDatabase("QSQLITE");
 db.setDatabaseName(dbFileName);
 db.addDatabase("QSQLITE", "LocoNetMonitor");
 if(!db.open())
 {
  qDebug() << QString("Error opening database: %1 ").arg(db.lastError().text());
  emit error(QString("Error opening database: %1 ").arg(db.lastError().text()));
 }
 else
 {
  QString CommandString;
  QSqlQuery query(db);
  CommandString = "create table if not exists `comments` (id INTEGER PRIMARY KEY, unitAddress integer NOT NUll, unitSubAddress integer NOT NULL, port integer NOT NULL, type text, mode text, title text, description text, address integer, opCode integer, isOutput integer, CONSTRAINT index1 UNIQUE (unitAddress, unitSubAddress, port)) ";
  if(!query.exec(CommandString))
  {
   qDebug() << QString("Table create error: %1").arg(query.lastError().text());
  }
  // Create rfid table if not exists
  CommandString = "create table if not exists `rfid` (id INTEGER PRIMARY KEY, `serial` text NOT NULL, `block` int, `description` text, CONSTRAINT index1 UNIQUE (serial))";
  if(!query.exec(CommandString))
  {
   qDebug() << QString("Table create error: %1").arg(query.lastError().text());
  }
 }
}
void Sql::setData(LocoIOData *data)
{
 this->data = data;
}
bool Sql::isOpen()
{
 return db.isOpen();
}
bool Sql::isValid() { return db.isValid();}

bool Sql::updateComment(int port, QString type, QString title, QString description)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "insert or replace into comments (unitAddress, unitSubAddress, port, type, mode, title, description, address, opCode, isOutput) VALUES(:unitAddress, :unitSubAddress, :port, :type, :mode, :title, :description, :address, :opCode, :isOutput) ";
 query.prepare(CommandString);
 query.bindValue(":unitAddress", data->getUnitAddress());
 query.bindValue(":unitSubAddress", data->getUnitSubAddress());
 query.bindValue(":port", port);
 query.bindValue(":type", type);
 query.bindValue(":mode", data->getMode(port-1));
 query.bindValue(":title", title);
 query.bindValue(":description", description);
 query.bindValue(":address", data->getAddr(port-1));
 int opCode = 0;
 int isOutput=0;
 LocoIOMode* lim = data->getLIM(port-1);
 if(lim != nullptr)
 {
  opCode = lim->getOpcode();
  isOutput = lim->getOutput();
 }
 query.bindValue(":opCode", opCode);
 query.bindValue("isOutput", isOutput);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error updating comments record for port %1: ").arg(port).arg(query.lastError().text()));
  return false;
 }
 return true;
}
bool Sql::updateBasicComments(int port, QString type)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "insert or replace into comments (unitAddress, unitSubAddress, port, type, mode,  address, opCode, isOutput) VALUES(:unitAddress, :unitSubAddress, :port, :type, :mode,  :address, :opCode, :isOutput) ";
 query.prepare(CommandString);
 query.bindValue(":unitAddress", data->getUnitAddress());
 query.bindValue(":unitSubAddress", data->getUnitSubAddress());
 query.bindValue(":port", port);
 query.bindValue(":type", type);
 query.bindValue(":mode", data->getMode(port-1));
 query.bindValue(":address", data->getAddr(port-1));
 int opCode = 0;
 int isOutput=0;
 LocoIOMode* lim = data->getLIM(port-1);
 if(lim != nullptr)
 {
  opCode = lim->getOpcode();
  isOutput = lim->getOutput();
 }
 query.bindValue(":opCode", opCode);
 query.bindValue("isOutput", isOutput);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error updating basic comments record for port %1: ").arg(port).arg(query.lastError().text()));
  return false;
 }
 return true;
}

bool Sql::deleteComment(int port)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "delete from comments where unitAddress = :unitAddress and unitSubAddress = :unitSubAddress and port = :port";
 query.prepare(CommandString);
 query.bindValue(":unitAddress", data->getUnitAddress());
 query.bindValue(":unitSubAddress", data->getUnitSubAddress());
 query.bindValue(":port", port);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error retrieving record for port %1: ").arg(port).arg(query.lastError().text()));
  return false;
 }
 return true;
}
QSqlRecord Sql::getComments(int port)
{
 QString CommandString;

 QSqlQuery query(db);
 CommandString = "select * from comments where unitAddress = :unitAddress and unitSubAddress = :unitSubAddress and port = :port";
 query.prepare(CommandString);
 query.bindValue(":unitAddress", data->getUnitAddress());
 query.bindValue(":unitSubAddress", data->getUnitSubAddress());
 query.bindValue(":port", port);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error retrieving record for port %1: ").arg(port).arg(query.lastError().text()));
  emit error(QString(tr("Error retrieving record for port %1: ").arg(port).arg(query.lastError().text())));
  return QSqlRecord();
 }
 //qDebug()<< QString("Query returned %1 ").arg(query.lastError().text());
 query.next();
 return query.record();
}
bool Sql::commentRecordExists(int port)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "select count(*) from comments where unitAddress = :unitAddress and unitSubAddress = :unitSubAddress and port = :port";
 query.prepare(CommandString);
 query.bindValue(":unitAddress", data->getUnitAddress());
 query.bindValue(":unitSubAddress", data->getUnitSubAddress());
 query.bindValue(":port", port);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error retrieving record for port %1: ").arg(port).arg(query.lastError().text()));
  emit(QString(tr("Error retrieving record for port %1: ").arg(port).arg(query.lastError().text())));
  return false;
 }
 int count;
 if(query.next())
  count = query.value(0).toInt();
 return (count !=0);
}
bool Sql::changeAddress(int oldUnitAddress, int oldUnitSubAddress, int newUnitAddress, int newUnitSubAddress)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "update comments set unitAddress = :newUnitAddress, unitSubAddress = :newUnitSubAddress where unitAddress = :oldUnitAddress and unitSubAddress = :oldUnitSubAddress";
 query.prepare(CommandString);
 query.bindValue(":newUnitAddress", newUnitAddress);
 query.bindValue(":newUnitSubAddress", newUnitSubAddress);
 query.bindValue(":oldUnitAddress", oldUnitAddress);
 query.bindValue(":oldUnitSubAddress", oldUnitSubAddress);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error changing address %1: ").arg(query.lastError().text()));
  return false;
 }
 return true;
}
bool Sql::rfidPortExists(QString serial)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "select count(*) from `rfid` where serial = :serial";
    query.prepare(CommandString);
    query.bindValue(":serial", serial);
    if(!query.exec())
    {
     qDebug()<< QString(tr("Error retrieving record for rfidport %1: ").arg(serial).arg(query.lastError().text()));
     emit(QString(tr("Error retrieving record for rfidport %1: ").arg(serial).arg(query.lastError().text())));
     return false;
    }
    int count;
    if(query.next())
     count = query.value(0).toInt();
    return (count !=0);
}
bool Sql::updateRfidPort(QString serial, int block,  QString description)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "insert or replace into `rfid` (serial, block, description) VALUES(:serial, :block, :description) ";
 query.prepare(CommandString);
 query.bindValue(":serial", serial);
 query.bindValue(":block", block);
 query.bindValue(":description", description);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error updating rfid record for port %1: ").arg(serial).arg(query.lastError().text()));
  return false;
 }
 return true;
}
bool Sql::deleteRfidPort(QString serial)
{
 QString CommandString;
 QSqlQuery query(db);
 CommandString = "delete from `rfid` where serial = :serial";
 query.prepare(CommandString);
 query.bindValue(":serial", serial);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error retrieving record for port %1: ").arg(serial).arg(query.lastError().text()));
  return false;
 }
 return true;
}
QSqlRecord Sql::getRfidPort(QString serial)
{
 QString CommandString;

 QSqlQuery query(db);
 CommandString = "select * from `rfid` where serial = :serial";
 query.prepare(CommandString);
 query.bindValue(":serial", serial);
 if(!query.exec())
 {
  qDebug()<< QString(tr("Error retrieving record for rfid port %1: ").arg(serial).arg(query.lastError().text()));
  emit error(QString(tr("Error retrieving record for rfid port %1: ").arg(serial).arg(query.lastError().text())));
  return QSqlRecord();
 }
 //qDebug()<< QString("Query returned %1 ").arg(query.lastError().text());
 query.next();
 return query.record();
}
