#ifndef TRIPLETURNOUTSIGNALHEADXML_H
#define TRIPLETURNOUTSIGNALHEADXML_H
#include "doubleturnoutsignalheadxml.h"

class TripleTurnoutSignalHeadXml : public DoubleTurnoutSignalHeadXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TripleTurnoutSignalHeadXml(QObject *parent = 0);
    ~TripleTurnoutSignalHeadXml() {}
    TripleTurnoutSignalHeadXml(const TripleTurnoutSignalHeadXml&) : DoubleTurnoutSignalHeadXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(TripleTurnoutSignalHeadXml)
#endif // TRIPLETURNOUTSIGNALHEADXML_H
