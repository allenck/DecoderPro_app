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
#include "runnable.h"

class DefaultIdTag;
class DefaultIdTagManager : public AbstractManager, public IdTagManager
{
    Q_OBJECT
  Q_INTERFACES(IdTagManager)
public:
    explicit DefaultIdTagManager(QObject *parent = 0);
    /*public*/ int getXMLOrder()const override;
    /*public*/ bool isInitialised()  override;
    /*public*/ void init()   override;
    /*public*/ QChar typeLetter() const override ;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ DefaultIdTag *provideIdTag(QString name)override;
    /*public*/ DefaultIdTag *getIdTag(QString name)override;
    /*public*/ DefaultIdTag *getBySystemName(QString name) override;
    /*public*/ DefaultIdTag* getByUserName(QString key) override;
    /*public*/ DefaultIdTag* getByTagID(QString tagID)override;
    /*public*/ virtual DefaultIdTag *newIdTag(QString systemName, QString userName)override;
    /*public*/ void Register(NamedBean* s) override;
    /*public*/ void deregister(NamedBean* s)   override;
    /*public*/ virtual void writeIdTagDetails() ;// /*throw (IOException)*/;
    /*public*/ virtual void readIdTagDetails();
    /*public*/ void setStateStored(bool state)override;
    /*public*/ bool isStateStored()override;
    /*public*/ void setFastClockUsed(bool fastClock)override;
    /*public*/ bool isFastClockUsed()override;
    /*public*/ QList<IdTag*>* getTagsForReporter(Reporter* reporter, long threshold)override;
    /*public*/ DefaultIdTag *provide(QString name) /*throw (IllegalArgumentException)*/override;
    /*public*/ QString getNamedBeanClass()const override {
        return "IdTag";
    }
  /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
//  /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
//  /*public*/ IdTag* getBySystemName(QString name) override {return (IdTag*)AbstractManager::getBySystemName(name);}
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

  QObject* self() override {return (QObject*)this;}


signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e)override;
private:
 Logger* log;
 /*private*/ static bool _initialised;// = false;
 /*private*/ static bool _loading;// = false;
 /*private*/ static bool _storeState;// = false;
 /*private*/ static bool _useFastClock;// = false;
 /*private*/ Runnable* shutDownTask = nullptr;

 protected:
 /*protected*/ void registerSelf();
 /*protected*/ virtual NamedBean *createNewIdTag(QString systemName, QString userName);
 /*protected*/ bool dirty = false;
 /*protected*/ void initShutdownTask();
 friend class DefaultIdTagShutdownTask;
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
    /*private*/ bool initialised = false;
    /*private*/ bool loading = false;
    /*private*/ bool storeState = false;
    /*private*/ bool useFastClock = false;
    /*private*/ Runnable* shutDownTask = nullptr;
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

class DefaultIdTagShutdownTask : public Runnable
{
  Q_OBJECT
  DefaultIdTagManager* mgr;
 public:
    DefaultIdTagShutdownTask(DefaultIdTagManager* mgr)
    { this->mgr = mgr;}

    /*public*/ void run()
    {
     // Save IdTag details prior to exit, if necessary
     mgr->log->debug("Start writing IdTag details...");
     try {
         mgr->writeIdTagDetails();
     } catch (IOException* ioe) {
         mgr->log->error(tr("Exception writing IdTags: %1").arg( ioe->toString()));
     }
    }
 private:
 Logger log;
};

#endif // DEFAULTIDTAGMANAGER_H
