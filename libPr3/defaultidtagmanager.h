#ifndef DEFAULTIDTAGMANAGER_H
#define DEFAULTIDTAGMANAGER_H
#include "idtagmanager.h"
#include "idtag.h"
#include "exceptions.h"
#include <QList>
#include "xmlfile.h"
#include <QMutex>
#include "logger.h"
#include <QFile>
#include "exceptions.h"
#include "instancemanager.h"
#include "abstractshutdowntask.h"
#include "abstractmanager.h"

class DefaultIdTag;
class DefaultIdTagManager : public IdTagManager
{
    Q_OBJECT
public:
    explicit DefaultIdTagManager(QObject *parent = 0);
    /*public*/ int getXMLOrder()const override;
    /*public*/ bool isInitialised()override;
    /*public*/ void init() const  override;
    /*public*/ char typeLetter()const override ;
    /*public*/ QString getSystemPrefix()const override;
    /*public*/ DefaultIdTag *provideIdTag(QString name)override;
    /*public*/ DefaultIdTag *getIdTag(QString name)override;
    /*public*/ NamedBean *getBySystemName(QString name)const override;
    /*public*/ NamedBean* getByUserName(QString key)const override;
    /*public*/ DefaultIdTag* getByTagID(QString tagID)override;
    /*public*/ virtual DefaultIdTag *newIdTag(QString systemName, QString userName)override;
    /*public*/ void Register(NamedBean* s) const override;
    /*public*/ void deregister(NamedBean* s)  const override;
    /*public*/ virtual void writeIdTagDetails() ;// throw (IOException);
    /*public*/ virtual void readIdTagDetails();
    /*public*/ void setStateStored(bool state)override;
    /*public*/ bool isStateStored()override;
    /*public*/ void setFastClockUsed(bool fastClock)override;
    /*public*/ bool isFastClockUsed()override;
    /*public*/ QList<IdTag*>* getTagsForReporter(Reporter* reporter, long threshold)override;
    /*public*/ DefaultIdTag *provide(QString name) throw (IllegalArgumentException)override;
 /*public*/ QString getNamedBeanClass()const override {
     return "IdTag";
 }

signals:
    void newIdTagCreated(DefaultIdTag* tag);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e)override;
private:
 Logger* log;
 /*private*/ static bool _initialised;// = false;
 /*private*/ static bool _loading;// = false;
 /*private*/ static bool _storeState;// = false;
 /*private*/ static bool _useFastClock;// = false;

 protected:
 /*protected*/ void registerSelf();
 /*protected*/ virtual NamedBean *createNewIdTag(QString systemName, QString userName);
 /*protected*/ bool dirty = false;
};

class IdTagManagerXml : XmlFile
{
 Q_OBJECT
public:
    /*public*/ static /*synchronized*/ IdTagManagerXml* instance();
    /*public*/ /*synchronized*/ void setDirty(bool dirty);
    /*public*/ QString getDefaultIdTagFileName();
    /*public*/ QString getIdTagDirectoryName();
    /*public*/ QString getIdTagFileName();
    /**
     * Absolute path to location of IdTag files.
     * @return path to location
     */
    /*public*/ static QString getFileLocation();

private:
    /**
     * Record the single instance
     */
    /*private*/ static IdTagManagerXml* _instance;// = NULL;

    /*private*/ static bool _loaded;// = false;

    /*private*/ bool _dirty;// = false;
    /*private*/ QFile* createFile(QString fileName, bool backup);
    /*private*/ void writeFile(QString fileName);// throw (FileNotFoundException);
    /*private*/ void readFile(QString fileName); //throw (JDOMException);
    /*private*/ static QString idTagDirectoryName;// = "idtags"; // NOI18N
    /*private*/ static QString idTagBaseFileName;// = "IdTags.xml"; // NOI18N
    /*private*/ static QString fileLocation;// = FileUtil.getUserFilesPath();


 QMutex mutex;
 Logger* log;
protected:
 /*protected*/ void load();
 /*protected*/ void store();

friend class DefaultIdTagManager;
};

class DefaultIdTagShutdownTask : public AbstractShutDownTask
{
  Q_OBJECT
 public:
    DefaultIdTagShutdownTask(QString name, QObject* parent = 0) : AbstractShutDownTask(name,parent)
    { }

    /*public*/ bool execute()
    {
     // Save IdTag details prior to exit, if necessary
     log.debug("Start writing IdTag details...");
//     try
//     {
//      ((DefaultIdTagManager*)InstanceManager::getDefault("IdTagManager"))->writeIdTagDetails();
      //new jmri.managers.DefaultIdTagManager().writeIdTagDetails();
//     }
//     catch (IOException ioe)
//     {
//      log.error("Exception writing IdTags: "+ioe.getMessage());
//     }

     // continue shutdown
     return true;
    }
 private:
 Logger log;
};

#endif // DEFAULTIDTAGMANAGER_H
