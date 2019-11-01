#include "buildfailedexception.h"

BuildFailedException::BuildFailedException()
{
 type = NORMAL;
}
/**
 * Build failed exception.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 * 2014
 */
//class BuildFailedException extends Exception {

/*public*/ /*final*/ /*static*/ QString BuildFailedException::NORMAL = "normal"; // NOI18N
/*public*/ /*final*/ /*static*/ QString BuildFailedException::STAGING = "staging"; // NOI18N

/*public*/ BuildFailedException::BuildFailedException(QString s, QString type) : Exception(s)
{
   // super(s);
    this->type = type;
}

/*public*/ BuildFailedException::BuildFailedException(QString s): Exception(s) {
    //super(s);
}

/*public*/ BuildFailedException::BuildFailedException(Exception ex) : Exception(ex)
{
    //super(ex);
}

/*public*/ QString BuildFailedException::getExceptionType() {
    return type;
}
