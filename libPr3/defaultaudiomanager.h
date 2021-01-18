#ifndef DEFAULTAUDIOMANAGER_H
#define DEFAULTAUDIOMANAGER_H
#include "abstractaudiomanager.h"
#include "quietshutdowntask.h"
#include "libPr3_global.h"
#include "namedbean.h"
#include <QSet>

class QStringList;
class AudioFactory;
class ShutDownTask;
class LIBPR3SHARED_EXPORT DefaultAudioManager : public AbstractAudioManager
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit DefaultAudioManager(QObject *parent = 0);
 ~DefaultAudioManager() {}
 DefaultAudioManager(const DefaultAudioManager&) : AbstractAudioManager() {}
 /*public*/ int getXMLOrder()const override;
 /*public*/ QString getSystemPrefix()const override;
 /*public*/ static DefaultAudioManager* instance();
 /*public*/ QT_DEPRECATED QStringList getSystemNameList(int subType);
 /*public*/ QSet<NamedBean*> getNamedBeanSet(QChar subType);
 /*public*/ QT_DEPRECATED QStringList getSystemNameList(QChar subType)override;
 /*public*/ /*synchronized*/ void init()override;
 /*public*/ void deregister(NamedBean* s)const override;
 /*public*/ void cleanUp();
 /*public*/ AudioFactory* getActiveAudioFactory()override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Audio";
 }

signals:

public slots:
private:
 /*private*/ static int countListeners;// = 0;
 /*private*/ static int countSources;// = 0;
 /*private*/ static int countBuffers;// = 0;
 /*private*/ /*final*/ QSet<NamedBean*> listeners;// = new TreeSet<>(new jmri.util.NamedBeanComparator<>());
 /*private*/ /*final*/ QSet<NamedBean*> buffers;// = new TreeSet<>(new jmri.util.NamedBeanComparator<>());
 /*private*/ /*final*/ QSet<NamedBean*> sources;// = new TreeSet<>(new jmri.util.NamedBeanComparator<>());
 /**
  * Reference to the currently active AudioFactory
  */
 /*private*/ static AudioFactory* activeAudioFactory;// = null;

 /*private*/ static bool _initialised;// = false;

 ShutDownTask* audioShutDownTask;
 Logger* log;

protected:
 /*protected*/ Audio* createNewAudio(QString systemName, QString userName) /*throws AudioException*/ override;

};
class AudioShutDownTask : public QuietShutDownTask
{
 Q_OBJECT
public:
 AudioShutDownTask(QString);
 bool doAction()override;
};
Q_DECLARE_METATYPE(DefaultAudioManager)
#endif // DEFAULTAUDIOMANAGER_H
