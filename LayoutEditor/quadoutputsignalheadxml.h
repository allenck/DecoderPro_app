#ifndef QUADOUTPUTSIGNALHEADXML_H
#define QUADOUTPUTSIGNALHEADXML_H
#include "tripleturnoutsignalheadxml.h"

class QuadOutputSignalHeadXml : public TripleTurnoutSignalHeadXml
{
    Q_OBJECT
public:
    explicit QuadOutputSignalHeadXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);

signals:

public slots:

};

#endif // QUADOUTPUTSIGNALHEADXML_H
