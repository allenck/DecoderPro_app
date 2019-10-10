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
    /*public*/ void handleException (
                QString description,
                QString operation,
                QString systemName,
                QString userName,
                Exception exception
            ) /*throw (JmriConfigureXmlException)*/;
    /*public*/ bool loadDeferred() ;
    /*public*/ int loadOrder();
    /*public*/ void setConfigXmlManager(ConfigXmlManager* c) ;
    QDomDocument doc;
    virtual void setDoc(QDomDocument doc);
    /*public*/ bool load(QDomElement e) throw (Exception);
    /*public*/ bool load(QDomElement shared, QDomElement perNode); //throws Exception
    /*public*/ void load(QDomElement shared, QDomElement perNode, QObject* o) throw (JmriConfigureXmlException);

signals:

public slots:
private:
    /*private*/ ConfigXmlManager* c;
  protected:
    /*protected*/ ConfigXmlManager* getConfigXmlManager() ;
 QObject *parent;
 /*private*/ ErrorHandler* errorHandler;// = XmlAdapter::getDefaultExceptionHandler();
};

#endif // ABSTRACTXMLADAPTER_H
