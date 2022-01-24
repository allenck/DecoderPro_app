#ifndef PROJECTSCOMMONSUBS_H
#define PROJECTSCOMMONSUBS_H

#include <QObject>
#include <QButtonGroup>

class NBHSignal;
class Logger;
class ProjectsCommonSubs : public QObject
{
  Q_OBJECT
 public:
  explicit ProjectsCommonSubs(QObject *parent = nullptr);
  static /*final*/ /*public*/ char SSV_SEPARATOR;// = ';';
  static /*public*/ QList<QString> getArrayListOfSignalNames(QList<NBHSignal*>* array);
  static /*public*/ QList<NBHSignal*>* getArrayListOfSignals(QList<QString> signalNames);
  static /*public*/ QList<QString> getArrayListFromCSV(QString csvString);// { return helper1(csvString, CSVFormat.DEFAULT.getDelimiter());}
  static /*public*/ QList<QString> getArrayListFromSSV(QString ssvString);// { return helper1(ssvString, SSV_SEPARATOR); }
  static /*private*/ QList<QString> helper1(QString ssvString, char separator);

  static /*public*/ QList<QString> getFixedArrayListSizeFromCSV(QString csvString, int returnArrayListSize);
  static /*public*/ int getIntFromStringNoThrow(QString aString, int defaultValueIfProblem);
  /*public*/ static bool isNullOrEmptyString(QString aString);
  /*public*/ static int getButtonSelectedInt(QButtonGroup* buttonGroup);
  /*public*/ static QString getButtonSelectedString(QButtonGroup* buttonGroup);

 signals:

 public slots:

 private:
  static Logger* log;

  friend class FrmMainForm;
};

#endif // PROJECTSCOMMONSUBS_H
