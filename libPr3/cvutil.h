#ifndef CVUTIL_H
#define CVUTIL_H

#include <QObject>

class Logger;
class CvUtil : public QObject
{
  Q_OBJECT
 public:
  explicit CvUtil(QObject *parent = nullptr);
  /*public*/ static QList<QString> expandCvList(QString cvString);
  /*public*/ static QString addCvDescription(QString toolTip, QString cvDescription, QString mask);
  /*public*/ static QString getMaskDescription(QString mask);

 signals:

 public slots:
 private:
  static Logger* log;
};

#endif // CVUTIL_H
