#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "runnable.h"

class Thread : public QThread
{
  Q_OBJECT
  QObject* runnable;
 public:
  Thread(QObject* runnable, QString name = "", QObject* parent = nullptr);
  void setName(QString name) {setObjectName(name);}
 public slots:
//  void run()
//  {
//   //((Runnable*)this->runnable)->run();
//  }
 signals:
  void finished();
};

#endif // THREAD_H
