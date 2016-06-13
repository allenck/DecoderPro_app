#ifndef PLAINDOCUMENT_H
#define PLAINDOCUMENT_H
#include "abstractdocument.h"

class PlainDocument : public AbstractDocument
{
    Q_OBJECT
public:
    explicit PlainDocument(QObject *parent = 0);

signals:

public slots:
private:
    /*private*/ AbstractElement* defaultRoot;
    /*private*/ QVector<Element>* added = new QVector<Element>();
    /*private*/ QVector<Element>* removed = new QVector<Element>();
    /*private*/ /*transient*/ Segment* s;

protected:

};

#endif // PLAINDOCUMENT_H
