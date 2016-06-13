#ifndef ABSTRACTIDTAG_H
#define ABSTRACTIDTAG_H
#include "abstractnamedbean.h"
#include "idtag.h"

class LIBPR3SHARED_EXPORT AbstractIdTag : public AbstractNamedBean //, public IdTag
{
    Q_OBJECT
public:
    //explicit AbstractIdTag(QObject *parent = 0);
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
protected:
 /*protected*/ Reporter* _whereLastSeen;// = NULL;

 /*protected*/ QDateTime _whenLastSeen;// = NULL;


};

#endif // ABSTRACTIDTAG_H
