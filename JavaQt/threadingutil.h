#ifndef THREADINGUTIL_H
#define THREADINGUTIL_H

#include <QObject>

class Logger;
class ThreadingUtil : public QObject
{
  Q_OBJECT
 public:
  explicit ThreadingUtil(QObject *parent = nullptr);

 signals:

 public slots:

 private:
  static Logger* log;
};

#endif // THREADINGUTIL_H
