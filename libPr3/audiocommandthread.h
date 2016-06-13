#ifndef AUDIOCOMMANDTHREAD_H
#define AUDIOCOMMANDTHREAD_H
#include "abstractaudiothread.h"
#include "libPr3_global.h"

class AudioCommand;
class AudioFactory;
class Logger;
class LIBPR3SHARED_EXPORT AudioCommandThread : public AbstractAudioThread
{
 Q_OBJECT
public:
 //explicit AudioCommandThread(QObject *parent = 0);
 /*public*/ AudioCommandThread(AudioFactory* activeAudioFactory,QObject *parent = 0);
 /*public*/ void run();

signals:
 void executeCommand();

public slots:
 void command_queued();

private:
 Logger* log;
 /**
  * Reference to active audio factory
  */
 /*private*/ AudioFactory* activeAudioFactory;
protected:
 /*protected*/ void cleanup();

};

#endif // AUDIOCOMMANDTHREAD_H
