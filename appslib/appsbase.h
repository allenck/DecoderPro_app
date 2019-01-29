#ifndef APPSBASE_H
#define APPSBASE_H

#include <QObject>
#include "abstractshutdowntask.h"
#include <QMetaType>
#include "appslib_global.h"

class Logger;
class File;
class APPSLIBSHARED_EXPORT AppsBase : public QObject
{
    Q_OBJECT
public:
    explicit AppsBase(QObject *parent = 0);
    ~AppsBase() {}
    AppsBase(const AppsBase&) : QObject() {}
    static /*public*/ bool handleQuit();
    static /*public*/ bool handleRestart();
    static /*public*/ void preInit(QString applicationName);
    /*public*/ AppsBase(QString applicationName, QString configFileDef, QStringList args, QObject *parent = 0);
    static /*public*/ QString getConfigFileName();

signals:

public slots:
private:
    /*private*/ /*final*/ static QString configFilename;// = "/JmriConfig3.xml";
    static bool _preInit;// = false;
    Logger* log;
    /*private*/ bool doDeferredLoad(File* file);
protected slots:
    void init();
protected:
    /*protected*/ bool configOK = false;
    /*protected*/ bool configDeferredLoadOK = false;
    /*protected*/ bool preferenceFileExists = false;
    virtual /*protected*/ void configureProfile();
    /*protected*/ void installConfigurationManager();
    /*protected*/ void installManagers();
    /*protected*/ void setAndLoadPreferenceFile() ;
    /*protected*/ void installShutDownManager();
    /*protected*/ void addDefaultShutDownTasks();
    /*protected*/ void start() ;
    static /*protected*/ void setConfigFilename(QString def, QStringList args);
    static /*protected*/ void setJmriSystemProperty(QString key, QString value);

friend class Apps3;
friend class WriteBlocksShutDownTask;
};

class WriteBlocksShutDownTask : public AbstractShutDownTask
{
 Q_OBJECT
 AppsBase* base;
public:
 WriteBlocksShutDownTask(QString text, AppsBase* base);
 ~WriteBlocksShutDownTask() {}
 /*public*/ bool execute() ;
};
#endif // APPSBASE_H
