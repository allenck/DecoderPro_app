#include "namedbeancomparator.h"
#include "namedbean.h"

NamedBeanComparator::NamedBeanComparator(QObject *parent) :
    SystemNameComparator(parent)
{
}
/**
 * Comparator for JMRI System Names.
 * <P> A System Name is two letters
 * followed by either an alpha name or a number.
 * In the number case, this does a numeric comparison.
 * If the number is appended with letters, does the
 * numeric sort on the digits followed by a lexigraphic
 * sort on the remainder.
 *
 * @author	Pete Cressman   Copyright (C) 2009
 *
 */

///*public*/ class NamedBeanComparator extends SystemNameComparator {
//    /*public*/ NamedBeanComparator() {
//    }

    /*public*/ int NamedBeanComparator::compare(NamedBean* nb1, NamedBean* nb2) {
        return SystemNameComparator::compare( nb1->getSystemName(), nb2->getSystemName());
    }
