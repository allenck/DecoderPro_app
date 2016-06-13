#ifndef NAMEDBEANCOMPARATOR_H
#define NAMEDBEANCOMPARATOR_H
#include "systemnamecomparator.h"

class NamedBean;
class NamedBeanComparator : public SystemNameComparator
{
    Q_OBJECT
public:
    explicit NamedBeanComparator(QObject *parent = 0);
    /*public*/ int compare(NamedBean* nb1, NamedBean* nb2);

signals:

public slots:

};

#endif // NAMEDBEANCOMPARATOR_H
