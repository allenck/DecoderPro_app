#include "namedbeanusernamecomparator.h"
#include <QDebug>
/**
 * Comparator for JMRI NamedBeans via their User Names.
 * <p>
 * If the User Names are both non-null and are not equal, uses the {@link AlphanumComparator},
 * otherwise uses the {@link NamedBeanComparator}.
 *
 * @param <B> supported type of NamedBean
 */
// /*public*/ class NamedBeanUserNameComparator<B extends NamedBean> implements java.util.Comparator<B> {

template<class B>
/*public*/ NamedBeanUserNameComparator<B>::NamedBeanUserNameComparator() : ComparatorT<B>()
{
 qDebug() << "NamedBeanUserNameComparator";
}

//@Override
template<class B>
/*public*/ int NamedBeanUserNameComparator<B>::compare(B n1, B n2) {
    QString s1 = n1.getUserName();
    QString s2 = n2.getUserName();
//    int comparison = 0;
    //AlphanumComparator comparator = new AlphanumComparator();
    // handle both usernames being null or empty
    if ((s1 == "" || s1.isEmpty()) && (s2 == "" || s2.isEmpty())) {
        return n1.compareTo(n2);
    }
    if (s1 == "" || s1.isEmpty()) {
        s1 = n1.getSystemName();
    }
    if (s2 == "" || s2.isEmpty()) {
        s2 = n1.getSystemName();
    }
    //return comparison != 0 ? comparison : comparator.compare(s1, s2);
    return s1.compare(s2);
}
