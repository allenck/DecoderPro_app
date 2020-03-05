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
    ~DefaultSignalSystemManager()  override{}
    DefaultSignalSystemManager(const DefaultSignalSystemManager&) : SignalSystemManager() {}
    /*public*/ int getXMLOrder()const  override;
    QString getSystemPrefix() ;
    /*public*/ char typeLetter() ;
    /*public*/ SignalSystem* getSystem(QString name)  override;
    /*public*/ SignalSystem* getBySystemName(QString key) const  override;
    /*public*/ SignalSystem* getByUserName(QString key)const  override;
    void load() ;
    QStringList* getListOfNames();
    SignalSystem* makeBean(QString name) ;
    void loadBean(DefaultSignalSystem* s, QDomElement root) ;
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalSystem";
    }


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
