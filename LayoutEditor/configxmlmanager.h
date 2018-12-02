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
    /*public*/ void registerConfig(QObject* o);
    /*public*/ void registerPref(QObject* o) ;
    void confirmAdapterAvailable(QObject* o);
    /*public*/ void removePrefItems();
    /*public*/ QObject* findInstance(/*Class<?> */QString c, int index) ;
    /*public*/ QObjectList getInstanceList(/*Class<?> */QString c);
    /*public*/ void registerConfig(QObject* o, int x);
    /*public*/ void registerTool(QObject* o);
    /*public*/ void registerUser(QObject* o);
    /*public*/ void registerUserPrefs(QObject* o);
    /*public*/ void deregister(QObject* o);
    /*public*/ static QString adapterName(QObject* o);
    void locateClassFailed(Throwable ex, QString adapterName, QObject* o);
    /*public*/ bool storeAll(File* file) const;
    /*public*/ void storePrefs() ;
    /*public*/ void storePrefs(File* file) ;
    /*public*/ void storeUserPrefs(File* file);
    /*public*/ void setPrefsLocation(File* prefsFile);
    /*public*/ bool storeConfig(File* file);
    /*public*/ bool storeUser(File* file) ;
    /*public*/ bool makeBackup(File* file) const;
    static /*public*/ QDomElement elementFromObject(QObject* o);
    static /*public*/ QDomElement elementFromObject(QObject* object, bool shared);
    /*public*/ bool load(File* fi) throw (JmriException) ;
    /*public*/ bool load(QUrl url) throw (JmriException);
    /*public*/ bool load(File* fi, bool registerDeferred) throw (JmriException) ;
    /*public*/ bool load(QUrl url, bool registerDeferred) throw (JmriException) ;
    /*public*/ bool loadDeferred(File* fi) throw (JmriException);
    /*public*/ bool loadDeferred(QUrl url) throw (JmriException);
    /*public*/ QUrl find(QString f);
    void locateFileFailed(QString f);
    static /*public*/ void creationErrorEncountered(
            XmlAdapter* adapter,
            QString operation,
            QString description,
            QString systemName,
            QString userName,
            Throwable exception);
    static /*public*/ void storingErrorEncountered(
            XmlAdapter* adapter,
            QString operation,
            Level* level,
            QString description,
            QString systemName,
            QString userName,
            Throwable exception
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
};

#endif // CONFIGXMLMANAGER_H
