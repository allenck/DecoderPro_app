#ifndef ABSTRACTIDTAG_H
#define ABSTRACTIDTAG_H
#include "abstractnamedbean.h"
#include "rfid/addressedidtag.h"
#include "reportable.h"
#include "reporter.h"
#include "idtag.h"

class LIBPR3SHARED_EXPORT AbstractIdTag : public IdTag, public Reportable
{
 Q_OBJECT
 Q_INTERFACES(Reportable)
public:
 /*explicit*/ AbstractIdTag(QObject *parent = 0);
 /*public*/ AbstractIdTag(QString systemName, QObject *parent);
 /*public*/ AbstractIdTag(QString systemName, QString userName, QObject *parent);
 /*public*/ QString getTagID() override;
 /*public*/ Reporter* getWhereLastSeen() override;
 /*public*/ QDateTime getWhenLastSeen() override;
 /*public*/ QString toString() override;
 /*public*/ QObject* self() override{return this;}

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
