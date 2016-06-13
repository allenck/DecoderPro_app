#include "activeflag.h"

ActiveFlag::ActiveFlag(QObject *parent) :
    QObject(parent)
{
    flag = false;
}

/**
 * Provide a flag to indicate that the system provided by
 * this package is active.
 * <P>
 * This is a very light-weight class, carrying only the flag,
 * so as to limit the number of unneeded class loadings.
 *
 * @author		Bob Jacobsen  Copyright (C) 2003
 * @version             $Revision: 17977 $
 */
//abstract public class ActiveFlag {
bool ActiveFlag::flag;

    /*static public*/ void ActiveFlag::setActive() {
        flag = true;
    }
   /* static public*/ bool ActiveFlag::isActive() {
        return flag;
    }
