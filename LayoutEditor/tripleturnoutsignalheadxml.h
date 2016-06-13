#ifndef TRIPLETURNOUTSIGNALHEADXML_H
#define TRIPLETURNOUTSIGNALHEADXML_H
#include "doubleturnoutsignalheadxml.h"

class TripleTurnoutSignalHeadXml : public DoubleTurnoutSignalHeadXml
{
    Q_OBJECT
public:
    explicit TripleTurnoutSignalHeadXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};

#endif // TRIPLETURNOUTSIGNALHEADXML_H
