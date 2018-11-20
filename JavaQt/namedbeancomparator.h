#ifndef NAMEDBEANCOMPARATOR_H
#define NAMEDBEANCOMPARATOR_H
#include "comparator.h"

class NamedBean;
class NamedBeanComparator : public Comparator
{
public:
 NamedBeanComparator();
 /*public*/ static int compare(NamedBean* n1, NamedBean* n2);
};

#endif // NAMEDBEANCOMPARATOR_H
