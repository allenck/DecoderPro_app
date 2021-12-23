#ifndef DEFAULTIDTAG_H
#define DEFAULTIDTAG_H
#include "abstractidtag.h"
#include "exceptions.h"

class LIBPR3SHARED_EXPORT DefaultIdTag : public AbstractIdTag
{
    Q_OBJECT
public:
    /*explicit*/ DefaultIdTag(QObject *parent = 0) : AbstractIdTag(parent) {}
    /*public*/ DefaultIdTag(QString systemName, QObject *parent = 0);
    /*public*/ DefaultIdTag(QString systemName, QString userName, QObject *parent = 0);
    ~DefaultIdTag() {}
    DefaultIdTag(const DefaultIdTag&): AbstractIdTag() {}
    /*public*/ void setState(int s) /*throw (JmriException)*/;
    /*public*/ int getState() ;
    /*public*/ QDomElement store(QDomDocument doc, bool storeState) ;
    /*public*/ void load(QDomElement e);
    /*public*/ /*final*/ void setWhereLastSeen(Reporter* r);
    void setRosterId(int id);
    int rosterId();

signals:
    //void propertyChange(DefaultIdTag* tag, QString propertyName, QObject* o, QObject* n);
    void propertyChange(PropertyChangeEvent *);

public slots:
private:
    /*private*/ int _currentState;// = UNKNOWN;
    void init();
    /*private*/ void setCurrentState(int state);
    int _rosterId;
Logger log;
};
Q_DECLARE_METATYPE(DefaultIdTag)
#endif // DEFAULTIDTAG_H
