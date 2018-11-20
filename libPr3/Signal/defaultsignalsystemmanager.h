#ifndef DEFAULTSIGNALSYSTEMMANAGER_H
#define DEFAULTSIGNALSYSTEMMANAGER_H
#include "signalsystemmanager.h"
#include "xmlfile.h"
#include "libPr3_global.h"

class XmlFile;
class SignalSystem;
class QDomElement;
class DefaultSignalSystem;
class LIBPR3SHARED_EXPORT DefaultSignalSystemManager : public SignalSystemManager
{
    Q_OBJECT
public:
    //explicit DefaultSignalSystemManager(QObject *parent = 0);
    /*public*/ DefaultSignalSystemManager(QObject *parent = 0);
    ~DefaultSignalSystemManager() {}
    DefaultSignalSystemManager(const DefaultSignalSystemManager&) : SignalSystemManager() {}
    /*public*/ int getXMLOrder();
    QString getSystemPrefix() ;
    /*public*/ char typeLetter() ;
    /*public*/ SignalSystem* getSystem(QString name) ;
    /*public*/ SignalSystem* getBySystemName(QString key) ;
    /*public*/ SignalSystem* getByUserName(QString key);
    void load() ;
    QStringList* getListOfNames();
    SignalSystem* makeBean(QString name) ;
    void loadBean(DefaultSignalSystem* s, QDomElement root) ;


signals:

public slots:
private:
protected:
    /*protected*/ void registerSelf();
 Logger* log;
public:
    /**
     * XmlFile is abstract, so this extends for local use
     */
    /*static*/ class AspectFile : public XmlFile {
    };

};
Q_DECLARE_METATYPE(DefaultSignalSystemManager)
#endif // DEFAULTSIGNALSYSTEMMANAGER_H
