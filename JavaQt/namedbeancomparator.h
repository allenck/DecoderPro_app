#ifndef NAMEDBEANCOMPARATOR_H
#define NAMEDBEANCOMPARATOR_H
#include "comparatort.h"

class NamedBean;
template<class B>
class NamedBeanComparator : public ComparatorT<B>
{
public:
 NamedBeanComparator() {}
 /*public*/ /*static*/ int compare(B n1, B n2){
  return n1->compareTo(n2);
 }
};

#endif // NAMEDBEANCOMPARATOR_H
