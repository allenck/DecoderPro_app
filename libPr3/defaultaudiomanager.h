#ifndef DEFAULTAUDIOMANAGER_H
#define DEFAULTAUDIOMANAGER_H
#include "abstractaudiomanager.h"
#include "quietshutdowntask.h"
#include "libPr3_global.h"

class QStringList;
class AudioFactory;
class ShutDownTask;
class LIBPR3SHARED_EXPORT DefaultAudioManager : public AbstractAudioManager
{
 Q_OBJECT
public:
 explicit DefaultAudioManager(QObject *parent = 0);
 ~DefaultAudioManager() {}
 DefaultAudioManager(const DefaultAudioManager&) : AbstractAudioManager() {}
 /*public*/ int getXMLOrder();
 /*public*/ QString getSystemPrefix();
 /*public*/ static DefaultAudioManager* instance();
 /*public*/ Q_DECL_DEPRECATED QStringList getSystemNameList(int subType);
 /*public*/ QStringList getSystemNameList(QChar subType);
 /*public*/ /*synchronized*/ void init();
 /*public*/ void deregister(NamedBean* s);
 /*public*/ void cleanUp();
 /*public*/ AudioFactory* getActiveAudioFactory();

signals:

public slots:
private:
 /*private*/ static int countListeners;// = 0;
 /*private*/ static int countSources;// = 0;
 /*private*/ static int countBuffers;// = 0;

 /**
  * Reference to the currently active AudioFactory
  */
 /*private*/ static AudioFactory* activeAudioFactory;// = null;

 /*private*/ static bool _initialised;// = false;

 ShutDownTask* audioShutDownTask;
/*private*/ /*volatile*/ static DefaultAudioManager* _instance;
 Logger* log;

protected:
 /*protected*/ Audio* createNewAudio(QString systemName, QString userName) /*throws AudioException*/ ;

};
class AudioShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
public:
 AudioShutDownTask(QString);
 bool doAction();
};
Q_DECLARE_METATYPE(DefaultAudioManager)
#endif // DEFAULTAUDIOMANAGER_H
