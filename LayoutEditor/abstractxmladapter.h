#ifndef ABSTRACTXMLADAPTER_H
#define ABSTRACTXMLADAPTER_H
#include "xmladapter.h"
#include "configxmlmanager.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractXmlAdapter : public XmlAdapter
{
    Q_OBJECT
public:
    explicit AbstractXmlAdapter(QObject *parent = 0);
    /*public*/ void handleException (QString description,
                QString operation,
                QString systemName,
                QString userName,
                Exception *exception
            ) /*throw (JmriConfigureXmlException)*/ override;
    /*public*/ bool loadDeferred()const  override;
    /*public*/ int loadOrder()const override;
    /*public*/ void setConfigXmlManager(ConfigXmlManager* c)  override;
    QDomDocument doc;
    virtual void setDoc(QDomDocument doc);
    /*public*/ bool load(QDomElement e) throw (Exception) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) override; //throws Exception
    /*public*/ void load(QDomElement shared, QDomElement perNode, QObject* o) throw (JmriConfigureXmlException) override;
    /*public*/ QDomElement store(/*@Nonnull*/ QObject* o, bool shared);
    /*public*/ void setExceptionHandler(ErrorHandler* errorHandler);
    /*public*/ ErrorHandler* getExceptionHandler();
    /*final*/ /*public*/ bool getAttributeBooleanValue(/*@Nonnull*/ QDomElement element, /*@Nonnull*/ QString name, bool def) ;
    /*final*/ /*public*/ int getAttributeIntegerValue(/*@Nonnull*/ QDomElement element, /*@Nonnull*/ QString name, int def) ;

signals:

public slots:
private:
    /*private*/ ConfigXmlManager* c;
    /*private*/ ErrorHandler* errorHandler;// = XmlAdapter::getDefaultExceptionHandler();
    static Logger* log;
  protected:
    /*protected*/ ConfigXmlManager* getConfigXmlManager() ;
 QObject *parent;
};

#endif // ABSTRACTXMLADAPTER_H
