#ifndef DEFAULTSIGNALSYSTEMMANAGER_H
#define DEFAULTSIGNALSYSTEMMANAGER_H
#include "abstractmanager.h"
#include "xmlfile.h"

class XmlFile;
class SignalSystem;
class QDomElement;
class DefaultSignalSystem;
class LIBPR3SHARED_EXPORT DefaultSignalSystemManager : public AbstractManager
{
    Q_OBJECT
public:
    //explicit DefaultSignalSystemManager(QObject *parent = 0);
    /*public*/ DefaultSignalSystemManager(QObject *parent = 0);
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

#endif // DEFAULTSIGNALSYSTEMMANAGER_H
