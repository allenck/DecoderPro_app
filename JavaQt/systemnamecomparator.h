#ifndef SYSTEMNAMECOMPARATOR_H
#define SYSTEMNAMECOMPARATOR_H

#include <QObject>
#include "comparator.h"
#include "javaqt_global.h"

class NamedBean;
class JAVAQTSHARED_EXPORT SystemNameComparator :public Comparator//: public Comparator<NamedBean*>
{
    //Q_OBJECT
public:
    explicit SystemNameComparator(QObject *parent = 0);
    /*public*/ static bool compare(const QString &o1, const QString &o2);

signals:

public slots:

};

#endif // SYSTEMNAMECOMPARATOR_H
