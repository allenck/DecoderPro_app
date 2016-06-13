#ifndef ABSTRACTAUDIOTHREAD_H
#define ABSTRACTAUDIOTHREAD_H
#include "audiothread.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractAudioThread : public AudioThread
{
 Q_OBJECT
public:
 explicit AbstractAudioThread(QObject *parent = 0);
 /*public*/ bool alive();
 /*public*/ void die();

signals:

public slots:
private:
 /**
  * True while the thread is running
  */
 /*private*/ bool _alive;// = true;

 /**
  * True when thread should die
  */
 /*private*/ bool _die;// = false;

 /**
  * Simple counter to ensure that each created thread has a unique name
  */
 /*private*/ static long counter;
 /*private*/ /*synchronized*/ bool die(bool action, bool value);
 /*private*/ /*synchronized*/ bool alive(bool action, bool  value);

protected:
 /*protected*/ void cleanup();
 /*protected*/ bool dying();
 /*protected*/ static void snooze(long ms);
 friend class AbstractAudioFactory;
};

#endif // ABSTRACTAUDIOTHREAD_H
