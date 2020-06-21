#ifndef CONFIGXMLMANAGER_H
#define CONFIGXMLMANAGER_H

#include "xmlfile.h"
#include <QUrl>
#include "xmladapter.h"

#include "level.h"
#include "configuremanager.h"
#include "liblayouteditor_global.h"

class File;
class XmlAdapter;
class ErrorHandler;
class LIBLAYOUTEDITORSHARED_EXPORT ConfigXmlManager : public ConfigureManager
{
    Q_OBJECT
public:
    explicit ConfigXmlManager(QObject *parent = nullptr);
    ~ConfigXmlManager();
    /**
     * Define the current DTD version string for the layout-config DTD.
     * See the <A HREF="package-summary.html#DTD">DTD versioning discussion</a>
     */
    static /*final*/const  /*public*/ QString schemaVersion;// = "-2-9-6";
    /*public*/ void registerConfig(QObject* o) override;
    /*public*/ void registerPref(QObject* o)  override;
    void confirmAdapterAvailable(QObject* o);
    static /*public*/ QString currentClassName(QString name);
    /*public*/ void removePrefItems() override;
    /*public*/ QObject* findInstance(/*Class<?> */QString c, int index)  override;
    /*public*/ QObjectList getInstanceList(/*Class<?> */QString c) override;
    /*public*/ void registerConfig(QObject* o, int x) override;
    /*public*/ void registerTool(QObject* o) override;
    /*public*/ void registerUser(QObject* o) override;
    /*public*/ void registerUserPrefs(QObject* o) override;
    /*public*/ void deregister(QObject* o) override;
    /*public*/ static QString adapterName(QObject* o);
    void locateClassFailed(Throwable ex, QString adapterName, QObject* o);
    /*public*/ bool storeAll(File* file) const override;
    /*public*/ void storePrefs()  override;
    /*public*/ void storePrefs(File* file)  override;
    /*public*/ void storeUserPrefs(File* file) override;
    /*public*/ void setPrefsLocation(File* prefsFile);
    /*public*/ bool storeConfig(File* file) override;
    /*public*/ bool storeUser(File* file)  override;
    /*public*/ bool makeBackup(File* file) const override;
    static /*public*/ QDomElement elementFromObject(QObject* o);
    /*public*/ bool load(File* fi) throw (JmriException)  override;
    /*public*/ bool load(QUrl url) throw (JmriConfigureXmlException) override;
    /*public*/ bool load(File* fi, bool registerDeferred) throw (JmriException)  override;
    /*public*/ bool load(QUrl url, bool registerDeferred) throw (JmriConfigureXmlException)  override;
    /*public*/ bool loadDeferred(File* fi) throw (JmriException) override;
    /*public*/ bool loadDeferred(QUrl url) throw (JmriConfigureXmlException) override;
    /*public*/ QUrl find(QString f) override;
    virtual void locateFileFailed(QString f) ;
    static /*public*/ void creationErrorEncountered(XmlAdapter* adapter,
            QString operation,
            QString description,
            QString systemName,
            QString userName,
            Throwable *exception);
    static /*public*/ void storingErrorEncountered(XmlAdapter* adapter,
            QString operation,
            Level* level,
            QString description,
            QString systemName,
            QString userName,
            Throwable *exception
            );
    /*static*/ /*public*/ void setErrorHandler(ErrorHandler handler);

signals:

public slots:
private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConfigXmlManager");
    QList<QObject*>  plist;// = new QList<QObject*> ();
    //Hashtable<Object, Integer> clist = new Hashtable<Object, Integer>();
    //QHash<QObject*, int> clist;// = Collections.synchronizedMap(new LinkedHashMap<Object, Integer>());
    QMap<int, QObject*> clist;
    QList<QObject*>  tlist;// = new QList<QObject*> ();
    QList<QObject*>  ulist;// = new QList<QObject*> ();
    QList<QObject*>  uplist;// = new QList<QObject*> ();
    QMap<int, QDomElement> loadDeferredList;// = new QList<QDomElement>();
    File* prefsFile;
    QString defaultBackupDirectory;// = FileUtil.getUserFilesPath()+"backupPanels";
    /*private*/ void storeVersion(QDomElement root) const;
    /*private*/ static /*final*/ QString fileLocation;// = "layout"+File.separator;
    static ErrorHandler* handler;// = new ErrorHandler();
    static /*public*/ void setErrorHandler(ErrorHandler* handler);
    QMap<QString, QString> configXmlMap;
//    /*private*/ void loadVersion(QDomElement root, XmlAdapter* adapter) ;

protected:

    /*protected*/ QDomElement initStore() const;
    /*protected*/ void addPrefsStore(QDomElement root) ;
    /*protected*/ bool addConfigStore(QDomElement root) const;
    /*protected*/ bool addToolsStore(QDomElement root) const;
    /*protected*/ bool addUserStore(QDomElement root) const;
    /*protected*/ void addUserPrefsStore(QDomElement root) const;
    /*protected*/ void includeHistory(QDomElement root) const;
    /*protected*/ bool finalStore(QDomElement root, File* file) const;
    /*protected*/ QList<QDomElement> getLoadDeferredList();

friend class Apps;
friend class AppsBase;
friend class ErrorHandlerO1;
friend class ConfigXmlManagerTest;
};

#endif // CONFIGXMLMANAGER_H
