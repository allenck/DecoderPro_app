#include "abstractidtag.h"

AbstractIdTag::AbstractIdTag(QObject *parent) :
    IdTag(parent)
{
 init();
}
const int IdTag::UNSEEN = 0x02;
const int IdTag::SEEN = 0x03;


/**
 * Abstract implementation of {@link jmri.IdTag} containing code common
 * to all concrete implementations.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 22227 $
 * @since       2.11.4
 */
///*public*/ abstract class AbstractIdTag extends AbstractNamedBean implements IdTag {

/*public*/ AbstractIdTag::AbstractIdTag(QString systemName, QObject *parent)
    : IdTag(systemName,parent)
{
 init();
    //super(systemName.toUpperCase());
}

/*public*/ AbstractIdTag::AbstractIdTag(QString systemName, QString userName, QObject* parent)
    : IdTag(systemName, userName, parent)
{
 //super(systemName.toUpperCase(), userName);
 init();
}

void AbstractIdTag::init()
{
 setObjectName(getDisplayName());
 _whereLastSeen = NULL;

 _whenLastSeen = QDateTime();


}

//@Override
/*public*/ QString AbstractIdTag::getTagID() {
    // TODO: Convert this to allow for >1 char system name length
    // Or, is this really necessary as it will always be 'I'nternal???
    return this->mSystemName.mid(2);
}

//@Override
/*public*/ Reporter* AbstractIdTag::getWhereLastSeen() {
    return this->_whereLastSeen;
}

//@Override
/*public*/ QDateTime AbstractIdTag::getWhenLastSeen()
{
 if (this->_whenLastSeen.isNull()) return QDateTime();
 else
 {
  QDateTime d = this->_whenLastSeen;
     //return (QDateTime)this->_whenLastSeen/*.clone()*/;  // Date is mutable, so return copy
  return d;
 }
}

//@Override
/*public*/ QString AbstractIdTag::toString()
{
 return (mUserName==NULL || mUserName.length()==0)?getTagID():mUserName;
}

//    private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractIdTag.class.getName());

//}
