#ifndef QUADOUTPUTSIGNALHEADXML_H
#define QUADOUTPUTSIGNALHEADXML_H
#include "tripleturnoutsignalheadxml.h"

class QuadOutputSignalHeadXml : public TripleTurnoutSignalHeadXml
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit QuadOutputSignalHeadXml(QObject *parent = 0);
 ~QuadOutputSignalHeadXml() {}
 QuadOutputSignalHeadXml(const QuadOutputSignalHeadXml&) : TripleTurnoutSignalHeadXml() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ bool load(QDomElement element) throw (Exception);

signals:

public slots:

};
Q_DECLARE_METATYPE(QuadOutputSignalHeadXml)
#endif // QUADOUTPUTSIGNALHEADXML_H
