#include "thread.h"
#include "exceptions.h"

Thread::Thread(QObject *runnable, QString name, QObject* parent) : QThread(parent)
{
 setObjectName(name);
 runnable->moveToThread(this);
 if(qobject_cast<Runnable*>(runnable))
  connect(this, SIGNAL(started()), runnable, SLOT(run()));
 else
 {
  if(runnable->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("process()")) == -1)
   throw new NoSuchMethodException(tr("worker %1 thread missing 'process' method."));
  connect(this, SIGNAL(started()), runnable, SLOT(process()));
 }
 connect(runnable, SIGNAL(finished()), this, SLOT(quit()));
 connect(runnable, SIGNAL(finished()), runnable, SLOT(deleteLater()));
 connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
 this->runnable = runnable;
}
