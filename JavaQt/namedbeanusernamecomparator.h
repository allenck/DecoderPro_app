#ifndef NAMEDBEANUSERNAMECOMPARATOR_H
#define NAMEDBEANUSERNAMECOMPARATOR_H
#include "comparatort.h"
#include "alphanumcomparator.h"

template<class B>
class NamedBeanUserNameComparator : public ComparatorT<B>
{
public:
 NamedBeanUserNameComparator() {}
 /*public*/ int compare(B n1, B n2) {
     QString s1 = n1->getUserName();
     QString s2 = n2->getUserName();
     int comparison = 0;
     AlphanumComparator* comparator = new AlphanumComparator();
     // handle both usernames being null or empty
     if ((s1 == "" || s1.isEmpty()) && (s2 == "" || s2.isEmpty())) {
         return n1->compareTo(n2);
     }
     if (s1 == "" || s1.isEmpty()) {
         s1 = n1->getSystemName();
     }
     if (s2 == "" || s2.isEmpty()) {
         s2 = n1->getSystemName();
     }
     return comparison != 0 ? comparison : comparator->compare(s1, s2);
 }


};

#endif // NAMECBEANUSERNAMECOMPARATOR_H
