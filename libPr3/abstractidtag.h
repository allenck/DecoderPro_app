#ifndef ABSTRACTIDTAG_H
#define ABSTRACTIDTAG_H
#include "abstractnamedbean.h"
#include "rfid/addressedidtag.h"
#include "reportable.h"
#include "reporter.h"


class LIBPR3SHARED_EXPORT AbstractIdTag : public AddressedIdTag//AbstractNamedBean, public Reportable, public IdTag
{
 Q_OBJECT
 //Q_INTERFACES(Reportable IdTag)
public:
    explicit AbstractIdTag(QObject *parent = 0);
 /*public*/ AbstractIdTag(QString systemName, QObject *parent);
 /*public*/ AbstractIdTag(QString systemName, QString userName, QObject *parent);
 /*public*/ QString getTagID();
 /*public*/ Reporter* getWhereLastSeen();
 /*public*/ QDateTime getWhenLastSeen();
 /*public*/ QString toString();

signals:
    
public slots:
private:
 void init();
 /*private*/ QString findPrefix();

protected:
 /*protected*/ Reporter* _whereLastSeen;// = NULL;

 /*protected*/ QDateTime _whenLastSeen;// = NULL;
 /*protected*/ QString prefix;// = null;

};

#endif // ABSTRACTIDTAG_H
