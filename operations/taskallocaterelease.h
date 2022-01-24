#ifndef TASKALLOCATERELEASE_H
#define TASKALLOCATERELEASE_H

#include <QObject>

class AllocatedSection;
class TaskAllocateRelease : public QObject
{
  Q_OBJECT
 public:
  /*public*/ enum TaskAction {
      SCAN_REQUESTS,
      RELEASE_RESERVED,
      RELEASE_ONE,
      AUTO_RELEASE,
      ABORT
  };
  explicit TaskAllocateRelease(TaskAction action, QObject *parent = nullptr);
  TaskAllocateRelease(TaskAction action, QString trainName, QObject *parent = nullptr);
  TaskAllocateRelease(TaskAction action, AllocatedSection* aSection, bool termTrain, QObject *parent = nullptr);
  /*public*/ TaskAction getAction();
  /*public*/ QString getTrainName();
  /*public*/ AllocatedSection* getAllocatedSection();
  /*public*/ bool getTerminatingTrain();
 signals:

 public slots:

 private:
  /*private*/ TaskAction act;
  /*private*/ QString trainName = nullptr;
  /*private*/ AllocatedSection* allocatedSection = nullptr;
  /*private*/ bool terminateingTrain = false;

};

#endif // TASKALLOCATERELEASE_H
