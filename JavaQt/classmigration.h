#ifndef CLASSMIGRATION_H
#define CLASSMIGRATION_H
#include <QMap>

class Logger;
class ClassMigration
{
 public:
  /*public*/ static QString migrateName(QString);
 private:
  static QMap<QString, QString> map;
  static Logger* log;
 protected:
  ClassMigration();

};

#endif // CLASSMIGRATION_H
