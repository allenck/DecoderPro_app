#ifndef PROJECTSCOMMONSUBS_H
#define PROJECTSCOMMONSUBS_H

#include <QObject>

class Logger;
class ProjectsCommonSubs : public QObject
{
  Q_OBJECT
 public:
  explicit ProjectsCommonSubs(QObject *parent = nullptr);
  static /*final*/ /*public*/ char SSV_SEPARATOR;// = ';';
  static /*public*/ QList<QString> getArrayListFromCSV(QString csvString);// { return helper1(csvString, CSVFormat.DEFAULT.getDelimiter());}
  static /*public*/ QList<QString> getArrayListFromSSV(QString ssvString);// { return helper1(ssvString, SSV_SEPARATOR); }
  static /*private*/ QList<QString> helper1(QString ssvString, char separator);

  /*public*/ static bool isNullOrEmptyString(QString aString);

 signals:

 public slots:

 private:
  static Logger* log;
};

#endif // PROJECTSCOMMONSUBS_H
