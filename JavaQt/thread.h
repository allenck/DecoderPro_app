#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
  Q_OBJECT
 public:
  Thread(QObject* runnable, QString name = "", QObject* parent = nullptr);
  void setName(QString name) {setObjectName(name);}
 signals:
  void finished();
};

#endif // THREAD_H
