#ifndef ABSTRACTTURNOUTMANAGERCONFIGXML_H
#define ABSTRACTTURNOUTMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractTurnoutManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractTurnoutManagerConfigXML(QObject *parent = 0);
    ~AbstractTurnoutManagerConfigXML();
    /*public*/ QDomElement store(QObject* o) override;
    /*abstract*/ /*public*/ virtual void setStoreElementClass(QDomElement turnouts) = 0 ;
    /*abstract*/ /*public*/ virtual bool load(QDomElement turnouts, QDomElement perNode) throw (Exception) = 0;
    /*public*/ bool loadTurnouts(QDomElement turnouts, QDomElement perNode);
    /*public*/ int loadOrder()const override;

signals:

public slots:
private:
    Logger* log;
};

#endif // ABSTRACTTURNOUTMANAGERCONFIGXML_H
