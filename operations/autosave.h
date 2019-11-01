#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include <QObject>

class Logger;
namespace Operations
{
 class Worker;
 class AutoSave : public QObject
 {
  Q_OBJECT
 public:
  explicit AutoSave(QObject *parent = 0);


 signals:

 public slots:
 private:
  static QThread* autoSave;// = null;
  /*private*/ /*synchronized*/ void saveFiles();
  Logger* log;
 friend class Worker;
 };

 class Worker : public QObject
 {
  Q_OBJECT
 public:
  Worker(AutoSave* autoSave);
  ~Worker() {}
 public slots:
  void process();
 signals:
  void finished();
  void error(QString err);
 private:
  AutoSave* autoSave;
 };
}
#endif // AUTOSAVE_H
